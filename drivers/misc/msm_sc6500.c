/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/wakelock.h>
#include <linux/msm_sc6500.h>
#include <linux/irq.h>
#include <linux/interrupt.h>


static unsigned char sc6500_power_state = MSM_SC6500_SHUTDOWN;
static struct wake_lock modem_sc6500_wake_lock;
static struct timer_list mdm_wake_lock_timer;
static unsigned int mdm_wake_lock_count;

//extern uint32_t		platform_ver;  //huangqh2

static DEFINE_SPINLOCK(mdm_slock);

void ap_wakeup_modem_keep(void)
{
    printk("%s\n",__func__);
	
    gpio_set_value(SC6500_AP_WAKEUP_MDM,0);
    //mdelay(25);
    mdelay(6);
    gpio_set_value(SC6500_AP_WAKEUP_MDM,1);
	
    return;
}

int ap_wakeup_modem_wake(void)
{
    int counter = 100;

    gpio_set_value(SC6500_AP_WAKEUP_MDM,0);
	//mdelay(200);
    while ((!gpio_get_value(SC6500_MDM_READY_AP)) && (counter >= 0)) {
        mdelay(1);
        counter--;
    }
    if (counter < 0) {
        pr_err("ap_wakeup_modem_wake time out\n");
    }
    gpio_set_value(SC6500_AP_WAKEUP_MDM,1);
    
    printk("%s %d\n", __func__, counter);
    return counter;
}

static void mdm_wake_lock_timer_func(unsigned long data)
{   
    pr_debug("%s\n", __func__);
    if (!gpio_get_value(SC6500_MDM_READY_AP)) {
        ap_wakeup_modem_wake();
    }
    else {
        ap_wakeup_modem_keep();
    }
    mod_timer(&mdm_wake_lock_timer, jiffies + HZ*17/10);
}

void wake_lock_mdm(void)
{
	unsigned long flags;
   
    spin_lock_irqsave(&mdm_slock, flags);
    pr_debug("[sc6500]%s %d\n", __func__, mdm_wake_lock_count);
    printk("[sc6500]%s %d\n", __func__, mdm_wake_lock_count);
    if (!mdm_wake_lock_count) {
	 /* zengwen1, 20130521, modem ap sleep wakeup*/
    	//printk("%s, get SC6500_MDM_READY_AP %d \n",__func__,gpio_get_value(SC6500_MDM_READY_AP));
        mdm_wake_lock_timer_func(0);
    }
    mdm_wake_lock_count++;
    spin_unlock_irqrestore(&mdm_slock, flags);
}
EXPORT_SYMBOL(wake_lock_mdm);

void wake_unlock_mdm(void)
{   
	unsigned long flags;
    
    spin_lock_irqsave(&mdm_slock, flags);
    pr_debug("[sc6500]%s %d\n", __func__, mdm_wake_lock_count);
    printk("[sc6500]%s %d\n", __func__, mdm_wake_lock_count);

    if (mdm_wake_lock_count) {
        mdm_wake_lock_count--;
        if (!mdm_wake_lock_count)
            del_timer(&mdm_wake_lock_timer);
    }
    else {
    	WARN(1, "Unbalanced wake_unlock_mdm\n");
    }
    spin_unlock_irqrestore(&mdm_slock, flags);
}
EXPORT_SYMBOL(wake_unlock_mdm);

void modem_power_ctrl(unsigned char on_off)
{
    printk("sc6500 %s,on_off = %d\n",__func__, on_off);

    if (sc6500_power_state == on_off)
        return;
     
    if(on_off)  
    {
        gpio_set_value(SC6500_MDM_PWRON, 1);
    }
    else {
        gpio_set_value(SC6500_MDM_PWRON, 0);  
    }
    sc6500_power_state = on_off;

    return;
}

void modem_poweron_recovery(void)
{
	//pull up cts,prevent into spread's usb download
	gpio_tlmm_config(GPIO_CFG(SC6500_MDM_NBOOT, 0,
		GPIO_CFG_INPUT, GPIO_CFG_PULL_UP,
		GPIO_CFG_8MA), GPIO_CFG_ENABLE);

	//powerup spread modem
	gpio_tlmm_config(GPIO_CFG(SC6500_MDM_PWRON, 0,
		GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,
		GPIO_CFG_8MA), GPIO_CFG_ENABLE);

	gpio_set_value(SC6500_MDM_PWRON, 1);
}

void modem_poweroff_recovery(void)
{
	gpio_direction_output(SC6500_MDM_PWRON, 0);  
	msleep(200);
}


void modem_usbdownload(void)
{
	/*poweroff first*/
	printk("modem power off first\n");
	modem_power_ctrl(MSM_SC6500_SHUTDOWN);

	/*pull down NBOOT then poweron */	
	printk("pull down NBOOT then poweron\n");
	gpio_tlmm_config(GPIO_CFG(SC6500_MDM_NBOOT, 0,
			GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,
			GPIO_CFG_8MA), GPIO_CFG_ENABLE);
	gpio_set_value(SC6500_MDM_NBOOT, 0);  
	//modem_power_ctrl(MSM_SC6500_POWERON);
	gpio_tlmm_config(GPIO_CFG(SC6500_MDM_PWRON, 0,
			GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,
			GPIO_CFG_8MA), GPIO_CFG_ENABLE);
	gpio_set_value(SC6500_MDM_PWRON, 1);
	msleep(200);
}




/*  ioctl command for sc6500 device file    */
static long sc6500_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    unsigned char gpio_value  = 0;
    int modem_state              = 0;
    
    printk(KERN_ERR"%s cmd is %d!\n", __func__,cmd);

    /* check cmd */
    if(_IOC_TYPE(cmd) != MSM_SC6500_IOC_MAGIC)  
    {
        printk("sc6500 cmd magic type error!\n");
        return -ENOTTY;
    }

    if(_IOC_NR(cmd) > MSM_SC6500_IOC_MAXNR)
    {
        printk("sc6500 cmd number error!\n");
        return -ENOTTY;
    }

    switch(cmd)
    {
        case    MSM_SC6500_HARD_RESET:
        {
            if(MSM_SC6500_POWERON == sc6500_power_state)
            {
                // sc6500 will restart if pwrkey pull down for more than 3 seconds
                //sc6500_pwrkey_control(3800);
                printk("MSM_SC6500_RESET!\n ");
            }
            else
            {
                printk("sc6500 is in power down state and can't restart!!!\n");
            }
        }
        break;

        case    MSM_SC6500_SET_UART_FUNCTION:
        {
            if (arg < 0 || arg > 1)
            {
                printk("MSM_SC6500_SET_UART_FUNCTION arg is invalid: %d!\n", (unsigned int)arg);
                return -EINVAL;
            }
            
            //usb_switch high for mtk at command, low for mtk uart debug
            //gpio_set_value(USB_SWITCH_GPIO, (int)arg);    
            printk("MSM_SC6500 %s!!!\n", arg ? "at command" : "uart debug");
        }
        break;
        
        case    MSM_SC6500_GET_UART_FUNCTION:
        {   
            //gpio_value =gpio_get_value(USB_SWITCH_GPIO);
            if(put_user(gpio_value, (unsigned int __user *)arg))
            {
                printk("MSM_SC6500 put_user failed!\n");
                return -EFAULT;
            }
            else
            {
                printk("MSM_SC6500 uart function is in %s mode!!!\n", gpio_value? "data" : "debug");
            }

        }
        break;  

        case    MSM_SC6500_AP_WAKEUP_MDM:   
        {
            ap_wakeup_modem_wake();
        }
        break;

        case    MSM_SC6500_AP_GET_MDM_STATUS:   
        {
            modem_state = !!gpio_get_value(SC6500_MDM_READY_AP);
			put_user(modem_state, (unsigned int __user *)arg);
            printk("[%s] modem_state is %s\n",__func__,(modem_state?"wakeup":"sleep"));
        }
        break;

        case    MSM_SC6500_MDM_PWR_ON:  
        {
            modem_power_ctrl(MSM_SC6500_POWERON);
        }
        break;
        
        case    MSM_SC6500_MDM_PWR_OFF: 
        {
            modem_power_ctrl(MSM_SC6500_SHUTDOWN);
        }
        break;      

        case    MSM_SC6500_MDM_PWR_ON_RECOVERY:
        {
            modem_poweron_recovery();
        }
        break;

        case    MSM_SC6500_MDM_PWR_OFF_RECOVERY:
        {
            modem_poweroff_recovery();
        }
        break;

        case    MSM_SC6500_MDM_GET_VERSION_RECOVERY:
        {
            if(false/*put_user(platform_ver, (unsigned int __user *)arg)*/)//huangqh2
            {
                printk("MSM_SC6500 put_user failed!\n");
                return -EFAULT;
            }
            else
            {
                //printk("MSM_SC6500 uart platform_ver is 0x%x !\n", platform_ver); //huangqh2
            }
        }
        break;

		case MSM_SC6500_MDM_USB_DOWNLOAD:
		{
			modem_usbdownload();
		}
		break;

		case MSM_SC6500_GET_FACTORY_MODE:
		{
			gpio_value = !!gpio_get_value(SC6500_FACTORY_GPIO);
			printk("[MODEM]MSM_SC6500_GET_FACTORY_MODE, value = %d\n", gpio_value);
			put_user(gpio_value, (unsigned int __user *)arg);			
		}
		break;

		case MSM_SC6500_GET_ASSERT_STATUAS:
		{
			gpio_value = !!gpio_get_value(SC6500_MDM_ASSERT);
			printk("[MODEM]MSM_SC6500_GET_ASSERT_STATUAS, value = %d\n", gpio_value);
			put_user(gpio_value, (unsigned int __user *)arg);			
		}
		break;

        // liqiang11, add for SIM Smart Switch Feature.
        case MSM_SC6500_SIM_SWITCH:
        {
            if (1 == arg)
            {
                printk("MSM_SC6500_SIM_SWITCH arg is valid: %d!(the inner is 8674, the outer is 6500)\n", (unsigned int)arg);

                // "echo 51 0 D O 16 0 > /sys/private/tlmm" （拉低，模拟拔出SIM卡托）
                gpio_tlmm_config(GPIO_CFG(51, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_16MA), GPIO_CFG_ENABLE);
                gpio_set_value(51, 0);
                msleep(100);

                // "echo 58 0 D O 16 0 > /sys/private/tlmm" （里8974外6500）
                gpio_tlmm_config(GPIO_CFG(58, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_16MA), GPIO_CFG_ENABLE);
                gpio_set_value(58, 0);
                msleep(100);

                // "echo 51 0 N I 16 1 > /sys/private/tlmm" （高阻，模拟插入SIM卡托）
                gpio_tlmm_config(GPIO_CFG(51, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_16MA), GPIO_CFG_ENABLE);
                gpio_set_value(51, 1);
            }
            else if (2 == arg)
            {
                printk("MSM_SC6500_SIM_SWITCH arg is valid: %d!(the inner is 6500, the outer is 8674)\n", (unsigned int)arg);

                // "echo 51 0 D O 16 0 > /sys/private/tlmm" （拉低，模拟拔出SIM卡托）
                gpio_tlmm_config(GPIO_CFG(51, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_16MA), GPIO_CFG_ENABLE);
                gpio_set_value(51, 0);
                msleep(100);

                // "echo 58 0 U O 16 1 > /sys/private/tlmm" （里6500外8974）
                gpio_tlmm_config(GPIO_CFG(58, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_16MA), GPIO_CFG_ENABLE);
                gpio_set_value(58, 1);
                msleep(100);

                // "echo 51 0 N I 16 1 > /sys/private/tlmm" （高阻，模拟插入SIM卡托）
                gpio_tlmm_config(GPIO_CFG(51, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_16MA), GPIO_CFG_ENABLE);
                gpio_set_value(51, 1);
            }
            else
            {
                printk("MSM_SC6500_SIM_SWITCH arg is invalid: %d!\n", (unsigned int)arg);
                return -EINVAL;
            }
        }
        break;
	case MSM_SC6500_GET_GPIO_100_STATUS:
	{
		gpio_value = !!gpio_get_value(100);
		printk("[MODEM]MSM_SC6500_GET_GPIO_100_STATUS, value = %d\n", gpio_value);
		put_user(gpio_value, (unsigned int __user *)arg);			
	}
	break;
        default:
            printk("Unsupported sc6500 ioctl cmd!\n");
        break;
    }
    return 0;
}


static irqreturn_t sc6500_wakeup_ap_irq(int irq, void *dev_id)
{
    //extern volatile bool modem_irq_done;

    //modem_irq_done = true;
    printk("sc6500_wakeup_ap_irq !!!\n");
   #if 0
    if(!gpio_get_value(SC6500_AP_READY_MDM)){
   		gpio_set_value(SC6500_AP_READY_MDM,1);
    		printk("%s, zw set SC6500_AP_READY_MDM 1 \n",__func__);
    }
    #endif
    return IRQ_HANDLED;
}

static irqreturn_t sc6500_MDM_assert_irq(int irq, void *dev_id)
{
    //char *assert_msg[2] = { "sc6500_assert", NULL };//DO NOT change this message!
    //struct platform_device *pdev = NULL;

    printk("sc6500_MDM_assert_irq !!!\n");
    //pdev = (struct platform_device *)dev_id;
    //kobject_uevent_env(&pdev->dev.kobj, KOBJ_CHANGE, assert_msg);
    return IRQ_HANDLED;
}


#if 1//def sc6500_systfs_feature
static ssize_t sc6500_uart_function_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    unsigned int gpio_value =0;
    char *uart_state[] = {"UART_DEBUG_MODE", "UART_DATA_MODE",};
    char *echo_tips[] = {"Use echo 1 > uart_function to config uart funcion as data mode!",
                         "Use echo 0 > uart_function to config uart funcion as debug mode!"};

    printk(KERN_ERR"%s!\n", __func__);
    //gpio_value = gpio_get_value(USB_SWITCH_GPIO) ? 1 : 0;
    return scnprintf(buf, PAGE_SIZE, "%s\n%s\n", uart_state[gpio_value], echo_tips[gpio_value]);
}

static ssize_t sc6500_uart_function_store(struct device *dev, struct device_attribute *attr, const char *buf,
        size_t count)
{
    int tmp;

    tmp = simple_strtol(buf, NULL, 10);
    printk(KERN_ERR "%s argment is %d\n", __func__, tmp);    
    
    if (1 == tmp ) {
        return count;
    } else {
        return -EINVAL;
    }
}

static struct device_attribute dev_attr_uart_function = {
    .attr = {
         .name = "sc6500_uart",
         .mode = 0644,
         },
    .show = sc6500_uart_function_show,
    .store = sc6500_uart_function_store,
};

static ssize_t wake_lock_mdm_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", mdm_wake_lock_count);
}

static ssize_t wake_lock_mdm_store(struct device *dev, struct device_attribute *attr, const char *buf,
        size_t count)
{
    int lock, ret;
    ret = sscanf(buf, "%d", &lock);
    if (1 == ret) {
    
        printk("%s argment is %d\n", __func__, lock); 
        
        if (lock) {
            // keep modem always awake
            wake_lock_mdm();
        } else {
            // allow modem to sleep if there is no communication on uart3
            wake_unlock_mdm();
        }
        ret = count;
    }
    else {
        ret = -EINVAL;
    }
    return ret;
}

static struct device_attribute dev_attr_wake_lock_mdm = {
    .attr = {
         .name = "wake_lock_mdm",
         .mode = 0644,
         },
    .show = wake_lock_mdm_show,
    .store = wake_lock_mdm_store,
};

static ssize_t mdm_pw_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", sc6500_power_state);
}

static ssize_t mdm_pw_store(struct device *dev, struct device_attribute *attr, const char *buf,
        size_t count)
{
    int pw, ret;
    ret = sscanf(buf, "%d", &pw);
    if (1 == ret) {
    
        printk("%s argment is %d\n", __func__, pw); 
        
        modem_power_ctrl(!!pw);
        ret = count;
    }
    else {
        ret = -EINVAL;
    }
    return ret;
}

static struct device_attribute dev_attr_mdm_pw = {
    .attr = {
         .name = "mdm_pw",
         .mode = 0644,
         },
    .show = mdm_pw_show,
    .store = mdm_pw_store,
};

static ssize_t get_mdm_status_function_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
       unsigned int gpio_value =0;

    char *modem_status[] = {"sleep","wakeup"};

    printk(KERN_ERR"%s!\n", __func__);

    gpio_value = (!!gpio_get_value(SC6500_MDM_READY_AP) )? 1 : 0;
    return scnprintf(buf, PAGE_SIZE, "modem is %s\n", modem_status[gpio_value]);
}

 /* zengwen1, 20130522, modem ap sleep wakeup*/
static ssize_t get_ap_status_function_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
       unsigned int gpio_value =0;

    char *ap_status[] = {"sleep","wakeup"};

    printk(KERN_ERR"%s!\n", __func__);

    gpio_value = (!!gpio_get_value(SC6500_AP_READY_MDM) )? 1 : 0;
    return scnprintf(buf, PAGE_SIZE, "ap is %s\n", ap_status[gpio_value]);
}
/*zengwen1, 20130529, get four gpio status*/
static ssize_t get_four_gpio_status_function_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    unsigned int ap_wake_bp =0;
    unsigned int bp_wake_ap =0;
    unsigned int ap_rdy_mdm =0;
    unsigned int mdm_rdy_ap =0;

    printk(KERN_ERR"%s!\n", __func__);

    ap_wake_bp = (!!gpio_get_value(SC6500_AP_WAKEUP_MDM) )? 1 : 0;
    bp_wake_ap = (!!gpio_get_value(SC6500_MDM_WAKEUP_AP) )? 1 : 0;
    ap_rdy_mdm = (!!gpio_get_value(SC6500_AP_READY_MDM) )? 1 : 0;
    mdm_rdy_ap = (!!gpio_get_value(SC6500_MDM_READY_AP) )? 1 : 0;

    return scnprintf(buf, PAGE_SIZE, "SC6500_AP_WAKEUP_MDM is %d, SC6500_MDM_WAKEUP_AP is %d,  	SC6500_AP_READY_MDM is %d, SC6500_MDM_READY_AP is %d\n", ap_wake_bp,bp_wake_ap,ap_rdy_mdm,mdm_rdy_ap);
}

static ssize_t set_ap_ready_modem(struct device *dev, struct device_attribute *attr, const char *buf,
        size_t count)
{
    int lock, ret = 1;
    ret = sscanf(buf, "%d", &lock);
    if (1 == ret) {
    
        printk("%s argment is %d\n", __func__, lock); 
        
        if (lock) {
            // keep modem always awake
            //wake_lock_mdm();
            printk("set SC6500_AP_READY_MDM 1"); 
            gpio_set_value(SC6500_AP_READY_MDM,1);
        } else {
            // allow modem to sleep if there is no communication on uart3
            //wake_unlock_mdm();
          printk("set SC6500_AP_READY_MDM 0"); 
          gpio_set_value(SC6500_AP_READY_MDM,0);
        }
        //ret = count;
    }
    else {
        ret = -EINVAL;
    }
    return ret;
}
static struct device_attribute dev_attr_get_ap_status_function = {
    .attr = {
         .name = "ap_status",
         .mode = 0644,
         },
    .store = set_ap_ready_modem,
    .show = get_ap_status_function_show,
};

static struct device_attribute dev_attr_get_mdm_status_function = {
    .attr = {
         .name = "mdm_status",
         .mode = 0444,
         },
    .show = get_mdm_status_function_show,
};
/*zengwen1, 20130529, get four gpio status*/
static struct device_attribute dev_attr_get_four_gpio_status_function = {
    .attr = {
         .name = "four_status",
         .mode = 0644,
         },
    .show = get_four_gpio_status_function_show,
};
static int sc6500_create_sysfs_attr(struct platform_device *pdev)
{
    int ret ;

    ret = device_create_file(&pdev->dev, &dev_attr_uart_function);
    if (ret != 0)
        dev_err(&pdev->dev,
            "failed to create sysfs entry(sc6500_uart_function):"
            "err:(%d)\n", ret);

    ret = device_create_file(&pdev->dev, &dev_attr_wake_lock_mdm);
    if (ret != 0)
        dev_err(&pdev->dev,
            "failed to create sysfs entry(wake_lock_mdm):"
            "err:(%d)\n", ret); 

    ret = device_create_file(&pdev->dev, &dev_attr_get_mdm_status_function);
    if (ret != 0)
        dev_err(&pdev->dev,
            "failed to create sysfs entry(mdm_status):"
            "err:(%d)\n", ret);
    
    ret = device_create_file(&pdev->dev, &dev_attr_mdm_pw);
    if (ret != 0)
        dev_err(&pdev->dev,
            "failed to create sysfs entry(mdm_pw):"
            "err:(%d)\n", ret);
	
   /* zengwen1, 20130522, modem ap sleep wakeup*/
   ret = device_create_file(&pdev->dev, &dev_attr_get_ap_status_function);
    if (ret != 0)
        dev_err(&pdev->dev,
            "failed to create sysfs entry(mdm_pw):"
            "err:(%d)\n", ret);
   /* zengwen1, 20130529, modem ap sleep wakeup*/
    ret = device_create_file(&pdev->dev, &dev_attr_get_four_gpio_status_function);
    if (ret != 0)
        dev_err(&pdev->dev,
            "failed to create sysfs entry(mdm_pw):"
            "err:(%d)\n", ret);

    return ret;
}
#endif







#ifdef CONFIG_PM
static int sc6500_suspend(struct device *dev)
{
    static int s_first_suspend = 1;
    printk("sc6500_suspend!\n");

    // workaround 
    // ap need to do "wakeup" action before sc6500 first sleep,
    // otherwise sc6500 will have current leak.
    if (s_first_suspend) {
        ap_wakeup_modem_keep();
        s_first_suspend = 0;
    }
    gpio_direction_output(SC6500_AP_READY_MDM,0);  // It indicates that ap sleeps
    //gpio_set_value(SC6500_AP_READY_MDM,0);
    return 0;
}

static int sc6500_resume(struct device *dev)
{
    printk("sc6500_resume!\n");

    if(!gpio_get_value(SC6500_MDM_WAKEUP_AP))
    {
        printk("sc6500_resume wake lock!\n");
        wake_lock_timeout(&modem_sc6500_wake_lock, 3 * HZ);
    }
    
    gpio_direction_output(SC6500_AP_READY_MDM,1);  // It indicates that ap is waken
    //gpio_set_value(SC6500_AP_READY_MDM,1);

    return 0;
}
#else
#define sc6500_suspend NULL
#define sc6500_resume NULL
#endif

static struct dev_pm_ops sc6500_dev_pm_ops = {
    .suspend = sc6500_suspend,
    .resume = sc6500_resume,
};

#ifdef CONFIG_OF
static struct of_device_id sc6500_table[] = {
	        { .compatible = "qcom,sc6500",},
		{ },
};
#else
#define sc6500_table NULL
#endif

static const struct file_operations sc6500_fops = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = sc6500_ioctl,
};

static struct miscdevice sc6500 = {
    .minor      = MISC_DYNAMIC_MINOR,
    .name       = "sc6500",
    .fops       = &sc6500_fops,
};



static int __devexit sc6500_remove(struct platform_device *pdev)
{   
    printk("sc6500_remove!\n");
    
    del_timer(&mdm_wake_lock_timer);
    
    misc_deregister(&sc6500);
    return 0;
}


static struct platform_driver sc6500_platform_driver = {
    .remove = sc6500_remove,
    .driver = {
        .name = "sc6500",
        .owner = THIS_MODULE,
        .of_match_table = sc6500_table,
        .pm = &sc6500_dev_pm_ops,
    },
};




static int __init sc6500_probe(struct platform_device *pdev)
{
    int ret = -1;
    int irq_wakeup = 0;
    int irq_assert = 0;
    int factory_gpio_val = 0;

    printk("sc6500_probe: called!\n");
    
    wake_lock_init(&modem_sc6500_wake_lock, WAKE_LOCK_SUSPEND, "sc6500_wlock");
    /* zengwen1, 20130530, modem ap sleep wakeup*/
    //gpio_tlmm_config(GPIO_CFG(SC6500_MDM_WAKEUP_AP, 0,
	//		GPIO_CFG_INPUT, GPIO_CFG_PULL_UP,
	//		GPIO_CFG_2MA), GPIO_CFG_ENABLE);
    gpio_request(SC6500_MDM_WAKEUP_AP, "WAKE UP"); 
    //gpio_direction_input(SC6500_MDM_WAKEUP_AP); 
    //gpio_set_value(SC6500_MDM_WAKEUP_AP, 0);
    irq_wakeup = gpio_to_irq(SC6500_MDM_WAKEUP_AP); 

    printk("%s, get SC6500_AP_WAKEUP_MDM %d \n",__func__,gpio_get_value(SC6500_AP_WAKEUP_MDM));
    printk("%s, get SC6500_AP_READY_MDM %d, io num: %d \n",__func__,gpio_get_value(SC6500_AP_READY_MDM),SC6500_AP_READY_MDM);
    printk("%s, get SC6500_MDM_WAKEUP_AP %d \n",__func__,gpio_get_value(SC6500_MDM_WAKEUP_AP));
    printk("%s, get SC6500_MDM_READY_AP %d, io num: %d \n",__func__,gpio_get_value(SC6500_MDM_READY_AP),SC6500_MDM_READY_AP);
    init_timer(&mdm_wake_lock_timer);
    mdm_wake_lock_timer.function = mdm_wake_lock_timer_func;

    ret = misc_register(&sc6500);
    
    if(!sc6500_create_sysfs_attr(pdev))
    {
        printk("sc6500 sysfs device attribute file add successfully!!!\n");

    }

    /* zengwen1, 20130529, modem ap sleep wakeup*/
    if (request_irq(irq_wakeup, sc6500_wakeup_ap_irq, IRQF_TRIGGER_RISING, "sc6500_wakeup_ap", pdev) >= 0) //huangqh2
    {
        printk("sc6500 request_irq irq_num= %d successfully\n", irq_wakeup);
    }
    else
    {
        printk("sc6500 request_irq error!!!\n");
        ret =-1;
        return ret;
    }
    enable_irq_wake(irq_wakeup);

    gpio_request(SC6500_MDM_ASSERT, "MDM ASSERT"); 
     irq_assert = gpio_to_irq(SC6500_MDM_ASSERT); 
    if (request_irq(irq_assert, sc6500_MDM_assert_irq, IRQF_TRIGGER_RISING, "sc6500_MDM_assert", pdev) >= 0)
    {
        printk("sc6500 request_irq irq_num= %d successfully\n", irq_assert);
    }


    msleep(50);//sleep 50ms because SC6500_FACTORY_GPIO may have latency;
    factory_gpio_val = !!gpio_get_value(SC6500_FACTORY_GPIO);
    printk("%s, get factory GPIO, value = %d\n", __FUNCTION__, factory_gpio_val);
    if(factory_gpio_val) {  //for SC6500 calibration purpose
        printk("%s, according to factory GPIO, set gpio8,9 to high resistence\n", __FUNCTION__);
        gpio_tlmm_config(GPIO_CFG(8, 0,
                GPIO_CFG_INPUT, GPIO_CFG_NO_PULL,
                GPIO_CFG_16MA), GPIO_CFG_ENABLE);
        gpio_tlmm_config(GPIO_CFG(9, 0,
                GPIO_CFG_INPUT, GPIO_CFG_NO_PULL,
                GPIO_CFG_16MA), GPIO_CFG_ENABLE);
    }


    gpio_tlmm_config(GPIO_CFG(SC6500_MDM_PWRON, 0,
                GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN,
                GPIO_CFG_16MA), GPIO_CFG_ENABLE);
    modem_power_ctrl(MSM_SC6500_POWERON);

    return ret;
    
}


static int __init sc6500_init(void)
{
    int ret;

    ret = platform_driver_probe(&sc6500_platform_driver, sc6500_probe);

    printk("sc6500_init: driver initialized!\n");
    return ret;
}


static void __exit sc6500_exit(void)
{
    printk("sc6500_exit!!!\n");
    platform_driver_unregister(&sc6500_platform_driver);
}

module_init(sc6500_init);
module_exit(sc6500_exit);

MODULE_AUTHOR("xxxx <xxx.xx@xx.com>");
MODULE_DESCRIPTION("sc6500 GSM modem driver");
MODULE_LICENSE("GPL");

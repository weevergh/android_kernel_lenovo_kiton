/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include "msm_sensor.h"
#include "msm_cci.h"
#include <linux/proc_fs.h>

#define IMX135_SENSOR_NAME "imx135"
DEFINE_MSM_MUTEX(imx135_mut);

//#define IMX135_SENSOR_REG_DEBUG

static struct msm_sensor_ctrl_t imx135_s_ctrl;
#define imx135_INFO				2
#define imx135_DEBUG				1

#define IMX135_EEPROM_SIZE_FOR_DRIVER 578
#define IMX135_LSC_TABLE_HIGH_BYTE_IDX 0x0025
#define IMX135_LSC_TABLE_LOW_BYTE_IDX 0x0026
#define IMX135_LSC_TABLE_START_IDX 0x0027
#define IMX135_EEPROM_BLOCK_SIZE 256
#define IMX135_LSC_TABLE_SIZE_LIM 504
#define IMX135_I2C_WRITE_BYTES_EACH 7
#define IMX135_LSC_SIZE_FOR_DRIVER 544

static int debug = 2;
module_param(debug, int, 0644);
MODULE_PARM_DESC(debug, "imx135 debug output");

static int LSC_close=0;
module_param(LSC_close, int, 0644);
MODULE_PARM_DESC(LSC_close, "imx135 debug output");


#define imx135_debug(level, fmt, arg...) \
  do{ \
	  if (level > debug) \
		printk( fmt , ## arg); \
	}while(0)
struct imx135_otp_struct {
  uint16_t LSC_length;
  int otp_lenc_readed; // 1, lenc is already read out; 0, not
  uint8_t *LSC_data;
};
static struct imx135_otp_struct  imx135_otp;

int imx135_eeprom_sid = 0xA0>>1;
static struct msm_sensor_power_setting imx135_power_setting[] = {
	{
		.seq_type = SENSOR_VREG,
		.seq_val = CAM_VDIG,
		.config_val = 0,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_VREG,
		.seq_val = CAM_VANA,
		.config_val = 0,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_VREG,
		.seq_val = CAM_VIO,
		.config_val = 0,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_IMG_EN,
		.config_val = GPIO_OUT_HIGH,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_VREG,
		.seq_val = CAM_VAF,
		.config_val = 0,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_CLK,
		.seq_val = SENSOR_CAM_MCLK,
		//.config_val = 24000000
		.config_val = 19200000,
		.delay = 1,
	},

	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_RESET,
		.config_val = GPIO_OUT_LOW,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_RESET,
		.config_val = GPIO_OUT_HIGH,
		.delay = 30,
	},
#if 0
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_STANDBY,
		.config_val = GPIO_OUT_LOW,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_STANDBY,
		.config_val = GPIO_OUT_HIGH,
		.delay = 30,
	},
	{
		.seq_type = SENSOR_CLK,
		.seq_val = SENSOR_CAM_MCLK,
		//.config_val = 24000000
		.config_val = 19200000,
		.delay = 1,
	},
#endif
	{
		.seq_type = SENSOR_I2C_MUX,
		.seq_val = 0,
		.config_val = 0,
		.delay = 0,
	},
};
uint16_t imx135_read_i2c(struct msm_sensor_ctrl_t *s_ctrl,uint32_t address,uint16_t *data )
{
	int rc=0;

	rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_read(
			s_ctrl->sensor_i2c_client,
			address, data,MSM_CAMERA_I2C_BYTE_DATA);
	imx135_debug(imx135_INFO,"%s:data=%d\n", __func__, *data);
	if(rc<0)
		printk("read otp register addrees[0x%x] fail, rc=%d\n", address, rc);
	return rc;
	

}
int imx135_write_i2c(struct msm_sensor_ctrl_t *s_ctrl,int address, int val)
{
	int ret=0;
	ret = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client, address, val, MSM_CAMERA_I2C_BYTE_DATA);
	return ret;
	

}
uint16_t imx135_read_i2c_seq(struct msm_sensor_ctrl_t *s_ctrl,uint32_t address, uint8_t *data, uint16_t data_len )
{
	int rc=0;
	rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_read_seq(
			s_ctrl->sensor_i2c_client,
			address, data, data_len);
	if(rc<0)
		printk("read otp register addrees[0x%x] fail, rc=%d\n", address, rc);
	return rc;
	

}
int imx135_write_i2c_seq(struct msm_sensor_ctrl_t *s_ctrl,int address, uint8_t *data, int data_len)
{
	int ret=0;
//{
//	int i=0;
//	for(i=0;i<data_len;i++)
//	printk("[0x%x,0x%x] \n", address+i,*(data+i) );
//}
	ret = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_seq(
			s_ctrl->sensor_i2c_client, address, data, data_len);
	return ret;
	

}

int32_t imx135_read_out_LSC_from_sensor(struct msm_sensor_ctrl_t *s_ctrl)
{
	//uint16_t reg_val1=0;
	//uint16_t reg_val2=0;
	uint8_t data[IMX135_EEPROM_BLOCK_SIZE];
	int ret=0;
	int i=0;
	unsigned int sum =0;
	int h_mod = 0;
	int l_mod = 0;

	//uint16_t data_test;
	imx135_debug(imx135_INFO,"%s:Start!\n", __func__);	

	if(imx135_otp.otp_lenc_readed ==1)
	{
		imx135_debug(imx135_INFO,"%s:LSC is readed out already, return directly!\n", __func__);
		return 0;
	}

	imx135_otp.LSC_data = kzalloc(IMX135_EEPROM_SIZE_FOR_DRIVER*sizeof(uint8_t),GFP_KERNEL);
	if(imx135_otp.LSC_data == NULL)
	{
		imx135_debug(imx135_INFO,"%s:There is not enough memory for imx135 LSC table!\n", __func__);	
		return -1;
	}

	imx135_debug(imx135_INFO,"%s:kzalloc memory success!\n", __func__);	
	memset(imx135_otp.LSC_data, 0, IMX135_EEPROM_SIZE_FOR_DRIVER);


	imx135_debug(imx135_INFO,"%s:read first eeprom block start!\n", __func__); 
	memset(data, 0 , IMX135_EEPROM_BLOCK_SIZE);
	s_ctrl->sensor_i2c_client->cci_client->sid = (uint16_t)(0xA0 >>1); //first device for eeprom
	ret=imx135_read_i2c_seq(s_ctrl,0, data, IMX135_EEPROM_BLOCK_SIZE);
	if(ret<0)
	{
		imx135_debug(imx135_DEBUG,"%s: read eeprom 0 block fail! ret=%d\n", __func__, ret);
		return -1;		
	}

	for( i = 0; i < IMX135_EEPROM_BLOCK_SIZE ; i++ )
	{
		sum += data[i];
	}

	imx135_debug(imx135_INFO,"%s:read first eeprom block success! sum = %d\n", __func__,sum); 
	memcpy( imx135_otp.LSC_data, data, IMX135_EEPROM_BLOCK_SIZE);
	imx135_debug(imx135_INFO,"%s:read second eeprom block start!\n", __func__); 


	memset(data, 0 , IMX135_EEPROM_BLOCK_SIZE);
	s_ctrl->sensor_i2c_client->cci_client->sid = 0xA2>>1;
	ret=imx135_read_i2c_seq(s_ctrl,0, data, IMX135_EEPROM_BLOCK_SIZE);
	if(ret<0)
	{
		imx135_debug(imx135_DEBUG,"%s: read eeprom 1 block fail! ret =%d\n", __func__, ret);
		return -1;		
	}
	for( i = 0; i < IMX135_EEPROM_BLOCK_SIZE ; i++ )
	{
		sum += data[i];
	}


	imx135_debug(imx135_INFO,"%s:read second eeprom block success! sum = %d\n", __func__,sum); 
	memcpy( imx135_otp.LSC_data+IMX135_EEPROM_BLOCK_SIZE, data, IMX135_EEPROM_BLOCK_SIZE);
	

	imx135_debug(imx135_INFO,"%s:read third eeprom block start!\n", __func__); 
	memset(data, 0 , IMX135_EEPROM_BLOCK_SIZE);
	s_ctrl->sensor_i2c_client->cci_client->sid = 0xA4>>1;
	ret=imx135_read_i2c_seq(s_ctrl,0, data,  IMX135_EEPROM_SIZE_FOR_DRIVER-IMX135_EEPROM_BLOCK_SIZE*2);
	if(ret<0)
	{
		imx135_debug(imx135_DEBUG,"%s: read eeprom 2 block fail! ret=%d\n", __func__, ret);
		return -1;		
	}
	imx135_debug(imx135_INFO,"%s:read third eeprom block success!\n", __func__);
	memcpy(imx135_otp.LSC_data+IMX135_EEPROM_BLOCK_SIZE*2,data, IMX135_EEPROM_SIZE_FOR_DRIVER-IMX135_EEPROM_BLOCK_SIZE*2);
	 

	
	if(*(imx135_otp.LSC_data+IMX135_LSC_SIZE_FOR_DRIVER-1)!=1)
	{
		imx135_debug(imx135_DEBUG,"%s:the LSC eeprom check data fail reg_val1=%d\n", __func__, 
			*(imx135_otp.LSC_data+IMX135_LSC_SIZE_FOR_DRIVER));
		return -1;

	}	
	imx135_debug(imx135_INFO,"%s:read check data success!\n", __func__); 
		//{int i;
//for(i=0;i<504;i++)
//	printk("[0x%x,0x%x] \n", 0x4800+i,*(imx135_otp.LSC_data+i+IMX135_LSC_TABLE_START_IDX) );
//		}
	imx135_debug(imx135_INFO,"%s:LSC table high byte=0x%x!\n", __func__,*(imx135_otp.LSC_data+IMX135_LSC_TABLE_HIGH_BYTE_IDX) ); 
	imx135_debug(imx135_INFO,"%s:LSC table low byte=0x%x!\n", __func__,*(imx135_otp.LSC_data+IMX135_LSC_TABLE_LOW_BYTE_IDX) ); 



	for( i = 0; i < (IMX135_EEPROM_SIZE_FOR_DRIVER-IMX135_EEPROM_BLOCK_SIZE*2-2) ; i++ )
	{
		sum += data[i];
	}

       if(sum > 65535)
       {
              h_mod = (sum%65535) >> 8;
              l_mod = (sum%65535) & 0xff;
       }
       else
       {
              h_mod = sum >> 8;
              l_mod = sum & 0xff;
       }

	imx135_otp.LSC_length = (*(imx135_otp.LSC_data+IMX135_LSC_TABLE_HIGH_BYTE_IDX)<<8)&(0xFF00);
	
	imx135_otp.LSC_length = imx135_otp.LSC_length |(*(imx135_otp.LSC_data+IMX135_LSC_TABLE_LOW_BYTE_IDX)&0x00FF);
	imx135_debug(imx135_INFO,"%s:LSC the table size LSC_length=%d!\n", 
		__func__, imx135_otp.LSC_length);	


       if(h_mod != data[IMX135_EEPROM_SIZE_FOR_DRIVER-IMX135_EEPROM_BLOCK_SIZE*2-2]
           ||l_mod != data[IMX135_EEPROM_SIZE_FOR_DRIVER-IMX135_EEPROM_BLOCK_SIZE*2-1])
       {
           printk(" %s:check sum error: sum = 0x%x h_mod = 0x%x l_mod = 0x%x \n",__func__,sum,h_mod,l_mod);
           printk(" %s:check sum error: the right high byte should be 0x%x!\n", __func__, data[IMX135_EEPROM_SIZE_FOR_DRIVER-IMX135_EEPROM_BLOCK_SIZE*2-2]); 
           printk(" %s:check sum error: the right low byte should be =0x%x!\n", __func__, data[IMX135_EEPROM_SIZE_FOR_DRIVER-IMX135_EEPROM_BLOCK_SIZE*2-1]); 

           return -1;
       }
       else
   	{
           imx135_otp.otp_lenc_readed=1;
           
           imx135_debug(imx135_INFO,"%s:End!\n", __func__);	
           return 0;
   	}
}
int32_t imx135_write_LSC_to_sensor(struct msm_sensor_ctrl_t *s_ctrl)
{
	int ret=0;
	int LSC_len=0;
	imx135_debug(imx135_INFO,"%s:Start!\n", __func__);	
	if(imx135_otp.otp_lenc_readed !=1)
	{
		imx135_debug(imx135_DEBUG,"%s: the LSC data has not prepared! ret=%d\n", __func__, ret);
		return -1;
	}
	LSC_len=imx135_otp.LSC_length;
	if(LSC_len>IMX135_LSC_TABLE_SIZE_LIM)
		LSC_len=IMX135_LSC_TABLE_SIZE_LIM;
	imx135_debug(imx135_INFO,"%s:LSC_len=%d\n", __func__, LSC_len);	


/*===========need optimize the following i2c writting process==============================================*/
	if(1)
	{
		int i=0;
		int write_bytes_to=LSC_len;
		while(write_bytes_to)
		{
	
			if((write_bytes_to-IMX135_I2C_WRITE_BYTES_EACH)<0)
			{
				ret=imx135_write_i2c_seq(s_ctrl,0x4800+i*IMX135_I2C_WRITE_BYTES_EACH, imx135_otp.LSC_data+IMX135_LSC_TABLE_START_IDX+i*IMX135_I2C_WRITE_BYTES_EACH,write_bytes_to);
				if(ret<0)
				{
					printk("%s write i2c command for LSC failed!\n", __func__);
				}	
				break;
			}
			ret=imx135_write_i2c_seq(s_ctrl,0x4800+i*IMX135_I2C_WRITE_BYTES_EACH, imx135_otp.LSC_data+IMX135_LSC_TABLE_START_IDX+i*IMX135_I2C_WRITE_BYTES_EACH,IMX135_I2C_WRITE_BYTES_EACH);
			if(ret<0)
			{
				printk("%s write i2c command for LSC failed!\n", __func__);
			}	
			i++;
			write_bytes_to-=IMX135_I2C_WRITE_BYTES_EACH;

		}
		/*
		ret=imx135_write_i2c_seq(s_ctrl,0x4800, imx135_otp.LSC_data+IMX135_LSC_TABLE_START_IDX,LSC_len);
		if(ret<0)
		{
			printk("%s write i2c command for LSC failed!\n", __func__);
		}
*/
	}
	else
	{
		int i=0;
		uint8_t val=0;
		for(i=0;i<LSC_len;i++)
		{
			val=*(imx135_otp.LSC_data+IMX135_LSC_TABLE_START_IDX+i);
			ret=imx135_write_i2c(s_ctrl, 0x4800+i,val);
			if(ret<0)
			{
				printk("%s write i2c command for LSC failed!\n", __func__);
			}
		}
	}
	imx135_debug(imx135_INFO,"%s: after LSC wirtting ret=%d\n", __func__, ret);	
	if(ret<0)
	{
		imx135_debug(imx135_DEBUG,"%s: write the LSC to sensor fail ret=%d\n", __func__, ret);
		return -1;
	}
	ret=imx135_write_i2c(s_ctrl,0x4500, 0x1F);
	if(ret<0)
	{
		imx135_debug(imx135_DEBUG,"%s: write the EN_LSC to sensor fail ret=%d\n", __func__, ret);
		return -1;
	}	
	ret=imx135_write_i2c(s_ctrl,0x0700, 1);
	if(ret<0)
	{
		imx135_debug(imx135_DEBUG,"%s: write the LSC Enable to sensor fail ret=%d\n", __func__, ret);
		return -1;
	}	
	ret=imx135_write_i2c(s_ctrl,0x3A63, 1);
	if(ret<0)
	{
		imx135_debug(imx135_DEBUG,"%s: write the RAM sel toggle to sensor fail ret=%d\n", __func__, ret);
		return -1;
	}	
	imx135_debug(imx135_INFO,"%s:End!\n", __func__);	

	return 0;

}

int32_t imx135_sensor_otp_proc(struct msm_sensor_ctrl_t *s_ctrl)
{
	int rc=0;
	int i = 0;
	int sensor_sid=0;
	printk("imx135_sensor_otp_proc start\n");
	if(LSC_close>0)
		return 0;

	if(!s_ctrl->sensor_i2c_client)
	{
	  printk("imx135_i2c_client is null fail\n");
	  return 0;

	}
	if(!s_ctrl->sensor_i2c_client->i2c_func_tbl)
	{
	  printk("i2c_func_tbl is null fail\n");
	  return 0;

	}
	if(!s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_read)
	{
	  printk("i2c_read is null fail\n");
	  return 0;

	}
	if(!s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write)
	{
	  printk("i2c_write is null fail\n");
	  return 0;

	}
	sensor_sid=s_ctrl->sensor_i2c_client->cci_client->sid;
	s_ctrl->sensor_i2c_client->cci_client->sid=imx135_eeprom_sid;
	s_ctrl->sensor_i2c_client->addr_type = MSM_CAMERA_I2C_BYTE_ADDR;
	
        for (i = 0;i < 3;i++)//retry,weichenli modified,2013.8.27
        {
            rc=imx135_read_out_LSC_from_sensor(s_ctrl);
            printk(" %s:weichenli test retry %d times\n",__func__,i);

            if(!rc)
            {
                break;
            }
        }
	s_ctrl->sensor_i2c_client->cci_client->sid = sensor_sid;
	s_ctrl->sensor_i2c_client->addr_type = MSM_CAMERA_I2C_WORD_ADDR;

	if(rc!=0)
	{
	  printk("no valid wb otp data rc=%d\n", rc);
	  return 0;
	}


	rc=imx135_write_LSC_to_sensor(s_ctrl);
	printk("imx135_sensor_otp_proc end\n");

	return rc;

}

static struct v4l2_subdev_info imx135_subdev_info[] = {
	{
		.code = V4L2_MBUS_FMT_SBGGR10_1X10,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.fmt = 1,
		.order = 0,
	},
};

static const struct i2c_device_id imx135_i2c_id[] = {
	{IMX135_SENSOR_NAME, (kernel_ulong_t)&imx135_s_ctrl},
	{ }
};

static int32_t msm_imx135_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	return msm_sensor_i2c_probe(client, id, &imx135_s_ctrl);
}

static struct i2c_driver imx135_i2c_driver = {
	.id_table = imx135_i2c_id,
	.probe  = msm_imx135_i2c_probe,
	.driver = {
		.name = IMX135_SENSOR_NAME,
	},
};

static struct msm_camera_i2c_client imx135_sensor_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_WORD_ADDR,
};

static const struct of_device_id imx135_dt_match[] = {
	{.compatible = "qcom,imx135", .data = &imx135_s_ctrl},
	{}
};

MODULE_DEVICE_TABLE(of, imx135_dt_match);

static struct platform_driver imx135_platform_driver = {
	.driver = {
		.name = "qcom,imx135",
		.owner = THIS_MODULE,
		.of_match_table = imx135_dt_match,
	},
};
#ifdef IMX135_SENSOR_REG_DEBUG
static const struct file_operations proc_reg_read_operations;
#endif
static int32_t imx135_platform_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	const struct of_device_id *match;
	match = of_match_device(imx135_dt_match, &pdev->dev);
	rc = msm_sensor_platform_probe(pdev, match->data);
#ifdef IMX135_SENSOR_REG_DEBUG
	proc_create_data("reg_read", S_IFREG | S_IWUGO | S_IWUSR, NULL, &proc_reg_read_operations, NULL);
#endif
	return rc;
}

static int __init imx135_init_module(void)
{
	int32_t rc = 0;
	pr_info("%s:%d\n", __func__, __LINE__);
	rc = platform_driver_probe(&imx135_platform_driver,
		imx135_platform_probe);
	if (!rc)
		return rc;
	pr_err("%s:%d rc %d\n", __func__, __LINE__, rc);
	imx135_otp.otp_lenc_readed=0;
	return i2c_add_driver(&imx135_i2c_driver);
}

static void __exit imx135_exit_module(void)
{
	pr_info("%s:%d\n", __func__, __LINE__);
	if (imx135_s_ctrl.pdev) {
		msm_sensor_free_sensor_data(&imx135_s_ctrl);
		platform_driver_unregister(&imx135_platform_driver);
	} else
		i2c_del_driver(&imx135_i2c_driver);
	return;
}

static struct msm_sensor_ctrl_t imx135_s_ctrl = {
	.sensor_i2c_client = &imx135_sensor_i2c_client,
	.power_setting_array.power_setting = imx135_power_setting,
	.power_setting_array.size = ARRAY_SIZE(imx135_power_setting),
	.msm_sensor_mutex = &imx135_mut,
	.sensor_v4l2_subdev_info = imx135_subdev_info,
	.sensor_v4l2_subdev_info_size = ARRAY_SIZE(imx135_subdev_info),
	.sensor_otp_proc = imx135_sensor_otp_proc,

};
#ifdef IMX135_SENSOR_REG_DEBUG
int imx135_strlen(char *string)
{
	int i=0;
	char *p=string;
	while(*p++)
		i++;
	return i;

}

int imx135_strtoint(char *string)
{
	int ret_val=0;
	int i=0;
	int strlen=imx135_strlen(string);
	char *p=string;
	printk("=====================imx135_strtoint strlen=%d\n", strlen);
	for(i=0;i<strlen;i++)
	{
	printk("p[%d]=%d ,", i, *(p+i));
		if(*(p+i)<'0' || *(p+i)>'9')
			return ret_val;
		ret_val=ret_val*10+(*(p+i)-'0');
		
		if(i>64)
		{
			printk("the string is too long %s\n",__func__);
			break;
		}
	}
	printk("\n ret_val=%d\n", ret_val);
	return ret_val;

}
static ssize_t proc_reg_read (struct file *file, const char __user *buf, size_t nbytes, loff_t *ppos)
{
	char string[64];
	int reg_addr=0;
	uint16_t reg_val=0;
	if(copy_from_user(string, buf,10))
	{
		printk("===================>copy_from_user fail\n");
		return -1;
	}
	printk("=====================>input reg=%s\n", string);
	nbytes=imx135_strlen(string);
	reg_addr=imx135_strtoint(string);
	
	printk("=====================>reg_addr=%d\n", reg_addr);
	imx135_read_i2c(&imx135_s_ctrl, reg_addr, &reg_val);

	
	printk(" %s : %d reg_addr=%d, reg_val=%d\n"
		,__func__,__LINE__,
		reg_addr,reg_val);

	return nbytes;
}
static const struct file_operations proc_reg_read_operations = {
	.owner	= THIS_MODULE,
	.write	= proc_reg_read,
};
#endif
module_init(imx135_init_module);
module_exit(imx135_exit_module);
MODULE_DESCRIPTION("imx135");
MODULE_LICENSE("GPL v2");

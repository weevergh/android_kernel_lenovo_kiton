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
#include <linux/wakelock.h>

static struct wake_lock reset_modem_wake_lock;

static int __init rildsp_wakelock_init(void)
{
    printk("rildsp_wakelock_init: called!\n");
    wake_lock_init(&reset_modem_wake_lock, WAKE_LOCK_SUSPEND, "rildsp_resetmodem_wlock");
    wake_lock_timeout(&reset_modem_wake_lock,120 * HZ);
    printk("rildsp_wakelock_init: driver initialized!\n");
    return 0;
}
static void __exit rildsp_wakelock_exit(void)
{
    printk("rildsp_wakelock_exit!!!\n");
    wake_unlock(&reset_modem_wake_lock);
    wake_lock_destroy(&reset_modem_wake_lock);
}

module_init(rildsp_wakelock_init);
module_exit(rildsp_wakelock_exit);

MODULE_AUTHOR("xxxx <xxx.xx@xx.com>");
MODULE_DESCRIPTION("RILD-SP reset modem wake lock");
MODULE_LICENSE("GPL");



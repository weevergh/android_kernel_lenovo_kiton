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
#ifndef MSM_SC6500_H
#define MSM_SC6500_H

#include <linux/ioctl.h>


/*
	pwrkey is used to poweron shutdown or restart the gsm modem 
	based on different pull down time.

	1. If msm_sc6500 is in powerdown state, pulldown pwrkey for more than 1 sec then release, msm_sc6500 will poweron.
	2. If msm_sc6500 is powered up, pulldown pwrkey for about 1.5s to 3s, msm_sc6500 will shutdown.
	3. If msm_sc6500 is powered up, pulldown pwrkey for more than 3s, , msm_sc6500 will restart.

	For detailed infomation about sim800e GSM modem,
	please refer to msm_sc6500 Hardware Design Manual V1.00
*/	

#define MSM_SC6500_POWERON	 	1
#define MSM_SC6500_SHUTDOWN 	0


/* POWON GPIO */
#define SC6500_MDM_PWRON		48


/* MDM_ASSERT */
#define SC6500_MDM_ASSERT 		1	


/* AP_WAKEUP_MDM */
#define SC6500_AP_WAKEUP_MDM	45
/* MDM_WAKEUP_AP */
#define SC6500_MDM_WAKEUP_AP	46


/* MDM_NBOOT */
#define SC6500_MDM_NBOOT		55

/*zengwen1, 20130516, modify, new HW version GPIO has changed*/
//MDM_READY_AP
//#define SC6500_MDM_READY_AP		27
#define SC6500_MDM_READY_AP		28
/*zengwen1, 20130516, modify, new HW version GPIO has changed*/
//AP_READY_MDM
//#define SC6500_AP_READY_MDM		28
#define SC6500_AP_READY_MDM		27


#define SC6500_USB_DBG_SW		26

//for factory test
#define SC6500_FACTORY_GPIO 	34




// Use 'S' as magic number for msm_sc6500
#define MSM_SC6500_IOC_MAGIC 	'S'

/* IOCTLs for sc6500  gsm modem*/
#define MSM_SC6500_HARD_RESET				_IO(MSM_SC6500_IOC_MAGIC, 0)
#define MSM_SC6500_SET_UART_FUNCTION      	_IOW(MSM_SC6500_IOC_MAGIC, 1, unsigned char)
#define MSM_SC6500_GET_UART_FUNCTION      	_IOR(MSM_SC6500_IOC_MAGIC, 2, unsigned char)
#define MSM_SC6500_AP_WAKEUP_MDM      		_IOW(MSM_SC6500_IOC_MAGIC, 3, unsigned char)
#define MSM_SC6500_AP_GET_MDM_STATUS      	_IOR(MSM_SC6500_IOC_MAGIC, 4, unsigned char)
#define MSM_SC6500_MDM_PWR_OFF      		_IOW(MSM_SC6500_IOC_MAGIC, 5, unsigned char)
#define MSM_SC6500_MDM_PWR_ON      			_IOW(MSM_SC6500_IOC_MAGIC, 6, unsigned char)
#define MSM_SC6500_MDM_PWR_ON_RECOVERY		_IOW(MSM_SC6500_IOC_MAGIC, 7, unsigned char)
#define MSM_SC6500_MDM_PWR_OFF_RECOVERY		_IOW(MSM_SC6500_IOC_MAGIC, 8, unsigned char)
#define MSM_SC6500_MDM_USB_DOWNLOAD			_IOW(MSM_SC6500_IOC_MAGIC, 9, unsigned char)
#define MSM_SC6500_MDM_GET_VERSION_RECOVERY	_IOR(MSM_SC6500_IOC_MAGIC, 10, unsigned char)
#define MSM_SC6500_GET_FACTORY_MODE			_IOR(MSM_SC6500_IOC_MAGIC, 11, unsigned char)
#define MSM_SC6500_GET_ASSERT_STATUAS		_IOR(MSM_SC6500_IOC_MAGIC, 12, unsigned char)
// liqiang11, add for SIM Smart Switch Feature.
#define MSM_SC6500_SIM_SWITCH			_IOW(MSM_SC6500_IOC_MAGIC, 13, unsigned char)

// zengwen1, add for get gpio 100 status. 2013-9-27
#define MSM_SC6500_GET_GPIO_100_STATUS   _IOW(MSM_SC6500_IOC_MAGIC, 14, unsigned char) 
/*
    Don't forget  to increase or decrease below MAXNR
    if you changed the number of above ioctl commands.
*/
#define MSM_SC6500_IOC_MAXNR	14

extern void wake_lock_mdm(void);
extern void wake_unlock_mdm(void);

#endif

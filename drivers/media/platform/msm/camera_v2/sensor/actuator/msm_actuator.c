/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
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

#define pr_fmt(fmt) "%s:%d " fmt, __func__, __LINE__

#include <linux/module.h>
#include "msm_sd.h"
#include "msm_actuator.h"
#include "msm_cci.h"
//#define LENOVO_PATCH
#define QUALCOMM_PATCH

DEFINE_MSM_MUTEX(msm_actuator_mutex);

/*#define MSM_ACUTUATOR_DEBUG*/
#undef CDBG
#ifdef MSM_ACUTUATOR_DEBUG
#define CDBG(fmt, args...) pr_err(fmt, ##args)
#else
#define CDBG(fmt, args...) pr_debug(fmt, ##args)
#endif
static int debug = 2;
module_param(debug, int, 0644);
MODULE_PARM_DESC(debug, "msm actuator debug output");


#define ACTUATOR_INFO				2
#define ACTUATOR_DEBUG				1
//#define MSM_ACTUATOR_LC_INFI_ADDITIONAL	2
#define MSM_ACTUATOR_LC_INFI_ADDITIONAL	6
#define MSM_ACTUATOR_LC_MACRO_ADDITIONAL 3
static int need_init_lc=0;
#define msm_actuator_debug(level, fmt, arg...) \
  do{ \
	  if (level > debug) \
		printk( fmt , ## arg); \
	}while(0)

static struct msm_actuator msm_vcm_actuator_table;
static struct msm_actuator msm_piezo_actuator_table;

static struct i2c_driver msm_actuator_i2c_driver;
static struct msm_actuator *actuators[] = {
	&msm_vcm_actuator_table,
	&msm_piezo_actuator_table,
};

static int32_t msm_actuator_piezo_set_default_focus(
	struct msm_actuator_ctrl_t *a_ctrl,
	struct msm_actuator_move_params_t *move_params)
{
	int32_t rc = 0;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);

	if (a_ctrl->curr_step_pos != 0) {
		a_ctrl->i2c_tbl_index = 0;
		a_ctrl->func_tbl->actuator_parse_i2c_params(a_ctrl,
			a_ctrl->initial_code, 0, 0);
		a_ctrl->func_tbl->actuator_parse_i2c_params(a_ctrl,
			a_ctrl->initial_code, 0, 0);
		rc = a_ctrl->i2c_client.i2c_func_tbl->
			i2c_write_table_w_microdelay(
			&a_ctrl->i2c_client, a_ctrl->i2c_reg_tbl,
			a_ctrl->i2c_tbl_index, a_ctrl->i2c_data_type);
		if (rc < 0) {
			pr_err("%s: i2c write error:%d\n",
				__func__, rc);
			return rc;
		}
		a_ctrl->i2c_tbl_index = 0;
		a_ctrl->curr_step_pos = 0;
	}
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}
static void msm_actuator_lc_parse_i2c_params(struct msm_actuator_ctrl_t *a_ctrl,
	int16_t next_lens_position, uint16_t delay)
{
	uint16_t i2c_byte1 = 0, i2c_byte2 = 0;
	uint8_t value = 0;
	struct msm_camera_i2c_reg_tbl *i2c_tbl = a_ctrl->i2c_reg_tbl;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);


		value = ((next_lens_position >>8)& 0xFF);
		i2c_byte1 = 0xA1;
		i2c_byte2 = value;
		i2c_tbl[a_ctrl->i2c_tbl_index].reg_addr = i2c_byte1;
		i2c_tbl[a_ctrl->i2c_tbl_index].reg_data = i2c_byte2;
	    i2c_tbl[a_ctrl->i2c_tbl_index].delay=0;
		a_ctrl->i2c_tbl_index++;
		msm_actuator_debug(ACTUATOR_DEBUG,"A1 i2c_byte1:0x%x, i2c_byte2:0x%x\n", i2c_byte1, i2c_byte2);

		value = (next_lens_position & 0xFF);
		i2c_byte1 = 0xA2;
		i2c_byte2 = value;
		i2c_tbl[a_ctrl->i2c_tbl_index].reg_addr = i2c_byte1;
		i2c_tbl[a_ctrl->i2c_tbl_index].reg_data = i2c_byte2;
	    i2c_tbl[a_ctrl->i2c_tbl_index].delay=0;
		a_ctrl->i2c_tbl_index++;

		msm_actuator_debug(ACTUATOR_DEBUG,"A2 i2c_byte1:0x%x, i2c_byte2:0x%x\n", i2c_byte1, i2c_byte2);

	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
}

static void msm_actuator_parse_i2c_params(struct msm_actuator_ctrl_t *a_ctrl,
	int16_t next_lens_position, uint32_t hw_params, uint16_t delay)
{
	struct msm_actuator_reg_params_t *write_arr = a_ctrl->reg_tbl;
	uint32_t hw_dword = hw_params;
	uint16_t i2c_byte1 = 0, i2c_byte2 = 0;
	uint16_t value = 0;
	uint32_t size = a_ctrl->reg_tbl_size, i = 0;
	struct msm_camera_i2c_reg_tbl *i2c_tbl = a_ctrl->i2c_reg_tbl;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);
	for (i = 0; i < size; i++) {
		if (write_arr[i].reg_write_type == MSM_ACTUATOR_WRITE_DAC) {
			value = (next_lens_position <<
				write_arr[i].data_shift) |
				((hw_dword & write_arr[i].hw_mask) >>
				write_arr[i].hw_shift);

			if (write_arr[i].reg_addr != 0xFFFF) {
				i2c_byte1 = write_arr[i].reg_addr;
				i2c_byte2 = value;
				if (size != (i+1)) {
					i2c_byte2 = value & 0xFF;
					msm_actuator_debug(ACTUATOR_DEBUG,"byte1:0x%x, byte2:0x%x\n",
						i2c_byte1, i2c_byte2);
					i2c_tbl[a_ctrl->i2c_tbl_index].
						reg_addr = i2c_byte1;
					i2c_tbl[a_ctrl->i2c_tbl_index].
						reg_data = i2c_byte2;
					i2c_tbl[a_ctrl->i2c_tbl_index].
						delay = 0;
					a_ctrl->i2c_tbl_index++;
					i++;
					i2c_byte1 = write_arr[i].reg_addr;
					i2c_byte2 = (value & 0xFF00) >> 8;
				}
			} else {
				i2c_byte1 = (value & 0xFF00) >> 8;
				i2c_byte2 = value & 0xFF;
			}
		} else {
			i2c_byte1 = write_arr[i].reg_addr;
			i2c_byte2 = (hw_dword & write_arr[i].hw_mask) >>
				write_arr[i].hw_shift;
		}
		msm_actuator_debug(ACTUATOR_DEBUG,"i2c_byte1:0x%x, i2c_byte2:0x%x\n", i2c_byte1, i2c_byte2);
		i2c_tbl[a_ctrl->i2c_tbl_index].reg_addr = i2c_byte1;
		i2c_tbl[a_ctrl->i2c_tbl_index].reg_data = i2c_byte2;
		i2c_tbl[a_ctrl->i2c_tbl_index].delay = delay;
		a_ctrl->i2c_tbl_index++;
	}
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
}
#ifdef ONSEMI_LC_MODULE
struct lc_cal_data lc_cal_data_eeprom;
uint16_t inital_pos_val = 0;
struct lc_reg_settings_t lc_reg_setting1[]=
{
	{0x80, 0x34, MSM_CAMERA_I2C_BYTE_DATA},
	{0x81, 0x20, MSM_CAMERA_I2C_BYTE_DATA},
	{0x84, 0xE0, MSM_CAMERA_I2C_BYTE_DATA},
	{0x87, 0x05, MSM_CAMERA_I2C_BYTE_DATA},
	{0xA4, 0x24, MSM_CAMERA_I2C_BYTE_DATA},
	{0x3A, 0x0000, MSM_CAMERA_I2C_WORD_DATA},
	{0x04, 0x0000, MSM_CAMERA_I2C_WORD_DATA},
	{0x02, 0x0000, MSM_CAMERA_I2C_WORD_DATA},
	{0x18, 0x0000, MSM_CAMERA_I2C_WORD_DATA},
	{0x88, 0x70, MSM_CAMERA_I2C_BYTE_DATA},
	{0x28, 0x8080, MSM_CAMERA_I2C_WORD_DATA},
	{0x4C, 0x4000, MSM_CAMERA_I2C_WORD_DATA},
	{0x83, 0x2C, MSM_CAMERA_I2C_BYTE_DATA},
	{0x85, 0xC0, MSM_CAMERA_I2C_BYTE_DATA},

};
struct lc_reg_settings_t lc_reg_setting2[]=
{
	{0x84, 0xE3, MSM_CAMERA_I2C_BYTE_DATA},
	{0x97, 0x00, MSM_CAMERA_I2C_BYTE_DATA},
	{0x98, 0x42, MSM_CAMERA_I2C_BYTE_DATA},
	{0x99, 0x00, MSM_CAMERA_I2C_BYTE_DATA},
	{0x9A, 0x00, MSM_CAMERA_I2C_BYTE_DATA},

};
struct lc_reg_settings_t CsHalReg[]=
{
	{ 0x76, 0x0C, MSM_CAMERA_I2C_BYTE_DATA},	/*0C,0076,0dB*/
	{ 0x77, 0x50, MSM_CAMERA_I2C_BYTE_DATA},	/*50,0077,30dB*/
	{ 0x78, 0x40, MSM_CAMERA_I2C_BYTE_DATA},	/*40,0078,12dB*/
	{ 0x86, 0x40, MSM_CAMERA_I2C_BYTE_DATA},	/*40,0086*/
	{ 0xF0, 0x00, MSM_CAMERA_I2C_BYTE_DATA},	/*00,00F0,Through,0dB,fs/1,invert=0*/
	{ 0xF1, 0x00, MSM_CAMERA_I2C_BYTE_DATA},	/*00,00F1,LPF,1800Hz,0dB,fs/1,invert=0*/


};
struct lc_reg_settings_t CsHalFil[]=
{
	{ 0x30, 0x0000, MSM_CAMERA_I2C_WORD_DATA},	/*0000,0030,LPF,1800Hz,0dB,fs/1,invert=0*/
	{ 0x40, 0x8010, MSM_CAMERA_I2C_WORD_DATA},	/*8010,0040,0dB,invert=1*/
	{ 0x42, 0x7150, MSM_CAMERA_I2C_WORD_DATA},	/*7150,0042,HBF,30Hz,1000Hz,0dB,fs/1,invert=0*/
	{ 0x44, 0x8F90, MSM_CAMERA_I2C_WORD_DATA},	/*8F90,0044,HBF,30Hz,1000Hz,0dB,fs/1,invert=0*/
	{ 0x46, 0x61B0, MSM_CAMERA_I2C_WORD_DATA},	/*61B0,0046,HBF,30Hz,1000Hz,0dB,fs/1,invert=0*/
	{ 0x48, 0x65B0, MSM_CAMERA_I2C_WORD_DATA},	/*65B0,0048,-2dB,invert=0*/
	{ 0x4A, 0x2870, MSM_CAMERA_I2C_WORD_DATA},	/*2870,004A,-10dB,invert=0*/
	{ 0x4C, 0x4030, MSM_CAMERA_I2C_WORD_DATA},	/*4030,004C,-6dB,invert=0*/
	{ 0x4E, 0x7FF0, MSM_CAMERA_I2C_WORD_DATA},	/*7FF0,004E,0dB,invert=0*/
	{ 0x50, 0x04F0, MSM_CAMERA_I2C_WORD_DATA},	/*04F0,0050,LPF,300Hz,0dB,fs/1,invert=0*/
	{ 0x52, 0x7610, MSM_CAMERA_I2C_WORD_DATA},	/*7610,0052,LPF,300Hz,0dB,fs/1,invert=0*/
	{ 0x54, 0x16C0, MSM_CAMERA_I2C_WORD_DATA},	/*16C0,0054,DI,-15dB,fs/16,invert=0*/
	{ 0x56, 0x0000, MSM_CAMERA_I2C_WORD_DATA},	/*0000,0056,DI,-15dB,fs/16,invert=0*/
	{ 0x58, 0x7FF0, MSM_CAMERA_I2C_WORD_DATA},	/*7FF0,0058,DI,-15dB,fs/16,invert=0*/
	{ 0x5A, 0x0680, MSM_CAMERA_I2C_WORD_DATA},	/*0680,005A,LPF,400Hz,0dB,fs/1,invert=0*/
	{ 0x5C, 0x72F0, MSM_CAMERA_I2C_WORD_DATA},	/*72F0,005C,LPF,400Hz,0dB,fs/1,invert=0*/
	{ 0x5E, 0x7F70, MSM_CAMERA_I2C_WORD_DATA},	/*7F70,005E,HPF,35Hz,0dB,fs/1,invert=0*/
	{ 0x60, 0x7ED0, MSM_CAMERA_I2C_WORD_DATA},	/*7ED0,0060,HPF,35Hz,0dB,fs/1,invert=0*/
	{ 0x62, 0x7FF0, MSM_CAMERA_I2C_WORD_DATA},	/*7FF0,0062,Through,0dB,fs/1,invert=0*/
	{ 0x64, 0x0000, MSM_CAMERA_I2C_WORD_DATA},	/*0000,0064,Through,0dB,fs/1,invert=0*/
	{ 0x66, 0x0000, MSM_CAMERA_I2C_WORD_DATA},	/*0000,0066,Through,0dB,fs/1,invert=0*/
	{ 0x68, 0x5130, MSM_CAMERA_I2C_WORD_DATA},	/*5130,0068,HPF,400Hz,-3.5dB,fs/1,invert=0*/
	{ 0x6A, 0x72F0, MSM_CAMERA_I2C_WORD_DATA},	/*72F0,006A,HPF,400Hz,-3.5dB,fs/1,invert=0*/
	{ 0x6C, 0x8010, MSM_CAMERA_I2C_WORD_DATA},	/*8010,006C,0dB,invert=1*/
	{ 0x6E, 0x0000, MSM_CAMERA_I2C_WORD_DATA},	/*0000,006E,Cutoff,invert=0*/
	{ 0x70, 0x0000, MSM_CAMERA_I2C_WORD_DATA},	/*0000,0070,Cutoff,invert=0*/
	{ 0x72, 0x18E0, MSM_CAMERA_I2C_WORD_DATA},	/*18E0,0072,LPF,1800Hz,0dB,fs/1,invert=0*/
	{ 0x74, 0x4E30, MSM_CAMERA_I2C_WORD_DATA},	/*4E30,0074,LPF,1800Hz,0dB,fs/1,invert=0*/


};
#define ONSEMI_LC_BIAS_START	0
#define ONSEMI_LC_OFFSET_START	1
#define ONSEMI_LC_INFINITY_H_BYTE 2
#define ONSEMI_LC_INFINITY_L_BYTE 3
#define ONSEMI_LC_MACRO_H_BYTE 4
#define ONSEMI_LC_MACRO_L_BYTE 5
#define ONSEMI_LC_DATA_EEPROM_START 0x23

static int32_t msm_lc_actuator_init_focus(struct msm_actuator_ctrl_t *a_ctrl)
{
	int32_t rc=-EFAULT;
	int i=0;
	int size_array_setting;
	struct lc_reg_settings_t *lc_reg_settings=NULL;
	int loop=0;
	uint16_t val=0;
	int lc_sid=0;
	uint8_t lc_eeprom_data[7];
	msm_actuator_debug(ACTUATOR_INFO,"%s:Enter\n", __func__);
	lc_reg_settings=lc_reg_setting1;
	size_array_setting=sizeof(lc_reg_setting1)/sizeof(struct lc_reg_settings_t);
	msm_actuator_debug(ACTUATOR_INFO,"%s:size of setting1=%d\n", __func__, size_array_setting);
	for(i=0;i<size_array_setting;i++)
	{
		rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
										&a_ctrl->i2c_client,
										lc_reg_settings->reg_addr,
										lc_reg_settings->reg_data,
										lc_reg_settings->reg_data_type);
		if(rc<0)
		{
			printk("%s : %d write lc_reg_setting1 fail\n", __func__, __LINE__);
			return rc;
		}
		lc_reg_settings++;
		
	}
	loop=10;
	while(loop--)
	{
		val =-1;
		rc=a_ctrl->i2c_client.i2c_func_tbl->i2c_read(
										&a_ctrl->i2c_client,
										0x85,
										&val,
										MSM_CAMERA_I2C_BYTE_DATA);
		if(rc<0)
		{
			printk("%s : %d read status reg[0x85] fail\n", __func__, __LINE__);
			return rc;
		}		
		if(val==0)
		{
			break;
		}
		msleep(1);
	}
	msm_actuator_debug(ACTUATOR_INFO,"%s :%d  loop=%d, val=%d\n", __func__, __LINE__,loop,val);
	
	lc_reg_settings=lc_reg_setting2;
	size_array_setting=sizeof(lc_reg_setting2)/sizeof(struct lc_reg_settings_t);
	msm_actuator_debug(ACTUATOR_INFO,"%s:size of setting2=%d\n", __func__, size_array_setting);
	for(i=0;i<size_array_setting;i++)
	{
		rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
										&a_ctrl->i2c_client,
										lc_reg_settings->reg_addr,
										lc_reg_settings->reg_data,
										lc_reg_settings->reg_data_type);
		if(rc<0)
		{
			printk("%s : %d write lc_reg_setting2 fail\n", __func__, __LINE__);
			return rc;
		}
		lc_reg_settings++;
		
	}
	lc_reg_settings=CsHalReg;
	size_array_setting=sizeof(CsHalReg)/sizeof(struct lc_reg_settings_t);
	msm_actuator_debug(ACTUATOR_INFO,"%s:size of CsHalReg=%d\n", __func__, size_array_setting);
	for(i=0;i<size_array_setting;i++)
	{
		rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
										&a_ctrl->i2c_client,
										lc_reg_settings->reg_addr,
										lc_reg_settings->reg_data,
										lc_reg_settings->reg_data_type);
		if(rc<0)
		{
			printk("%s : %d write CsHalReg fail\n", __func__, __LINE__);
			return rc;
		}
		lc_reg_settings++;
		
	}

	lc_reg_settings=CsHalFil;
	size_array_setting=sizeof(CsHalFil)/sizeof(struct lc_reg_settings_t);
	msm_actuator_debug(ACTUATOR_INFO,"%s:size of CsHalFil=%d\n", __func__, size_array_setting);
	for(i=0;i<size_array_setting;i++)
	{
		rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
										&a_ctrl->i2c_client,
										lc_reg_settings->reg_addr,
										lc_reg_settings->reg_data,
										lc_reg_settings->reg_data_type);
		if(rc<0)
		{
			printk("%s : %d write CsHalFil fail\n", __func__, __LINE__);
			return rc;
		}
		lc_reg_settings++;
		
	}
	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0x86,
									0x60,
									MSM_CAMERA_I2C_BYTE_DATA);
	if(rc<0)
	{
		printk("%s : %d write DSSEL 1/16 INTON \n", __func__, __LINE__);
		return rc;
	}	

	//if(lc_cal_data_eeprom.readed!=0x01)
	{
		lc_sid=a_ctrl->i2c_client.cci_client->sid;
		a_ctrl->i2c_client.cci_client->sid = 0xA4>>1; //eeprom sid
		rc=a_ctrl->i2c_client.i2c_func_tbl->i2c_read_seq(
									&a_ctrl->i2c_client,
									ONSEMI_LC_DATA_EEPROM_START,
									lc_eeprom_data,
									7);
		a_ctrl->i2c_client.cci_client->sid = lc_sid;
		if(rc<0)
		{
			printk("%s : %d read close loop data fail\n", __func__, __LINE__);
			return rc;
		}	
		lc_cal_data_eeprom.lc_bias = lc_eeprom_data[ONSEMI_LC_BIAS_START];
		lc_cal_data_eeprom.lc_offset= lc_eeprom_data[ONSEMI_LC_OFFSET_START];
		lc_cal_data_eeprom.lc_infinity= ((lc_eeprom_data[ONSEMI_LC_INFINITY_H_BYTE]<<8)&0xff00)|
										lc_eeprom_data[ONSEMI_LC_INFINITY_L_BYTE];
		lc_cal_data_eeprom.lc_macro= ((lc_eeprom_data[ONSEMI_LC_MACRO_H_BYTE]<<8)&0xff00)|
										lc_eeprom_data[ONSEMI_LC_MACRO_L_BYTE];	
		//lc_cal_data_eeprom.readed=0x01;

	}


	for(i=0;i<7;i++)
		msm_actuator_debug(ACTUATOR_INFO,"the lc data[%d]=0x%x\n",i, lc_eeprom_data[i]);
		msm_actuator_debug(ACTUATOR_INFO,"%s bias=0x%x,offset=0x%x,macro pos=0x%x, infinity pos=0x%x, checksum=%d\n",__func__, 
		lc_cal_data_eeprom.lc_bias,
		lc_cal_data_eeprom.lc_offset,
		lc_cal_data_eeprom.lc_macro,
		lc_cal_data_eeprom.lc_infinity,
		lc_eeprom_data[6]);


	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0x28,
									lc_cal_data_eeprom.lc_offset,
									MSM_CAMERA_I2C_BYTE_DATA);
	if(rc<0)
	{
		printk("%s : %d write lc_bias fail\n", __func__, __LINE__);
		return rc;
	}	
	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0x29,
									lc_cal_data_eeprom.lc_bias,
									MSM_CAMERA_I2C_BYTE_DATA);
	if(rc<0)
	{
		printk("%s : %d write lc_offset fail\n", __func__, __LINE__);
		return rc;
	}	

	rc=a_ctrl->i2c_client.i2c_func_tbl->i2c_read(
									&a_ctrl->i2c_client,
									0x3C,
									&val,
									MSM_CAMERA_I2C_WORD_DATA);
	if(rc<0)
	{
		printk("%s : %d read direct move target pos fail\n", __func__, __LINE__);
		return rc;
	}	
#if 0
	msm_actuator_debug(ACTUATOR_DEBUG,"read direct move target pos val=0x%x\n", val);
	
	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0x04,
									val,
									MSM_CAMERA_I2C_WORD_DATA);
	if(rc<0)
	{
		printk("%s : %d write direct move target pos fail\n", __func__, __LINE__);
		return rc;
	}	
#endif
	msm_actuator_debug(ACTUATOR_INFO,"%s : current default pos value=0x%x\n", __func__,val );
	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0x18,
									val,
									MSM_CAMERA_I2C_WORD_DATA);
	if(rc<0)
	{
		printk("%s : %d write step move start pos fail\n", __func__, __LINE__);
		return rc;
	}	
	inital_pos_val = val;

	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0x5A,
									0x0800,
									MSM_CAMERA_I2C_WORD_DATA);
	if(rc<0)
	{
		printk("%s : %d  step move par setting ram fail\n", __func__, __LINE__);
		return rc;
	}	
	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0x83,
									0xAC,
									MSM_CAMERA_I2C_BYTE_DATA);
	if(rc<0)
	{
		printk("%s : %d write step move par setting reg fail\n", __func__, __LINE__);
		return rc;
	}	
	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0xA0,
									0x02,
									MSM_CAMERA_I2C_BYTE_DATA);
	if(rc<0)
	{
		printk("%s : %d write step move curret limitation(126us) fail\n", __func__, __LINE__);
		return rc;
	}
	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0x87,
									0x85,
									MSM_CAMERA_I2C_BYTE_DATA);
	if(rc<0)
	{
		printk("%s : %d write step move par setting reg fail\n", __func__, __LINE__);
		return rc;
	}	
	return 0;

}
#endif
static int32_t msm_actuator_init_focus(struct msm_actuator_ctrl_t *a_ctrl,
	uint16_t size, enum msm_actuator_data_type type,
	struct reg_settings_t *settings)
{
	int32_t rc = -EFAULT;
	int32_t i = 0;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);

	for (i = 0; i < size; i++) {
		switch (type) {
		case MSM_ACTUATOR_BYTE_DATA:
			rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
				&a_ctrl->i2c_client,
				settings[i].reg_addr,
				settings[i].reg_data, MSM_CAMERA_I2C_BYTE_DATA);
			break;
		case MSM_ACTUATOR_WORD_DATA:
			rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
				&a_ctrl->i2c_client,
				settings[i].reg_addr,
				settings[i].reg_data, MSM_CAMERA_I2C_WORD_DATA);
			break;
		default:
			pr_err("Unsupport data type: %d\n", type);
			break;
		}
		if (rc < 0)
			break;
	}
	if(a_ctrl->cam_name !=0)
	{
		a_ctrl->curr_step_pos = 0;
	}
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}

static void msm_actuator_write_focus(
	struct msm_actuator_ctrl_t *a_ctrl,
	uint16_t curr_lens_pos,
	struct damping_params_t *damping_params,
	int8_t sign_direction,
	int16_t code_boundary)
{
	int16_t next_lens_pos = 0;
	uint16_t damping_code_step = 0;
	uint16_t wait_time = 0;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);

	damping_code_step = damping_params->damping_step;
	wait_time = damping_params->damping_delay;

	/* Write code based on damping_code_step in a loop */
	if(a_ctrl->cam_name !=0)
	{
		for (next_lens_pos =
			curr_lens_pos + (sign_direction * damping_code_step);
			(sign_direction * next_lens_pos) <=
				(sign_direction * code_boundary);
			next_lens_pos =
				(next_lens_pos +
					(sign_direction * damping_code_step))) {
			a_ctrl->func_tbl->actuator_parse_i2c_params(a_ctrl,
				next_lens_pos, damping_params->hw_params, wait_time);
			curr_lens_pos = next_lens_pos;
		}
	}
	if (curr_lens_pos != code_boundary) {
		if(a_ctrl->cam_name !=0)
		{
			a_ctrl->func_tbl->actuator_parse_i2c_params(a_ctrl,
				code_boundary, damping_params->hw_params, wait_time);
		}
		else
		{
			a_ctrl->func_tbl->actuator_lc_parse_i2c_params(a_ctrl,
				code_boundary, wait_time);

		}
	}
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
}

static int32_t msm_actuator_piezo_move_focus(
	struct msm_actuator_ctrl_t *a_ctrl,
	struct msm_actuator_move_params_t *move_params)
{
	int32_t dest_step_position = move_params->dest_step_pos;
	int32_t rc = 0;
	int32_t num_steps = move_params->num_steps;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);

	if (num_steps == 0)
		return rc;

	a_ctrl->i2c_tbl_index = 0;
	a_ctrl->func_tbl->actuator_parse_i2c_params(a_ctrl,
		(num_steps *
		a_ctrl->region_params[0].code_per_step),
		move_params->ringing_params[0].hw_params, 0);

	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write_table_w_microdelay(
		&a_ctrl->i2c_client,
		a_ctrl->i2c_reg_tbl, a_ctrl->i2c_tbl_index,
		a_ctrl->i2c_data_type);
	if (rc < 0) {
		pr_err("i2c write error:%d\n", rc);
		return rc;
	}
	a_ctrl->i2c_tbl_index = 0;
	a_ctrl->curr_step_pos = dest_step_position;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}

static int32_t msm_actuator_move_focus(
	struct msm_actuator_ctrl_t *a_ctrl,
	struct msm_actuator_move_params_t *move_params)
{
	int32_t rc = 0;
	int8_t sign_dir = move_params->sign_dir;
	uint16_t step_boundary = 0;
	uint16_t target_step_pos = 0;
	uint16_t target_lens_pos = 0;
	int16_t dest_step_pos = move_params->dest_step_pos;
	uint16_t curr_lens_pos = 0;
	int dir = move_params->dir;
	int32_t num_steps = move_params->num_steps;
	uint16_t lc_direct_setting=0;

	msm_actuator_debug(ACTUATOR_INFO,"called, dir %d, num_steps %d\n", dir, num_steps);
	if (dest_step_pos == a_ctrl->curr_step_pos)
		return rc;

	curr_lens_pos = a_ctrl->step_position_table[a_ctrl->curr_step_pos];
	a_ctrl->i2c_tbl_index = 0;
	msm_actuator_debug(ACTUATOR_INFO,"curr_step_pos =%d dest_step_pos =%d curr_lens_pos=0x%x\n",
		a_ctrl->curr_step_pos, dest_step_pos, curr_lens_pos);

	while (a_ctrl->curr_step_pos != dest_step_pos) {
		step_boundary =
			a_ctrl->region_params[a_ctrl->curr_region_index].
			step_bound[dir];
		if ((dest_step_pos * sign_dir) <=
			(step_boundary * sign_dir)) {

			target_step_pos = dest_step_pos;
			target_lens_pos =
				a_ctrl->step_position_table[target_step_pos];
			a_ctrl->func_tbl->actuator_write_focus(a_ctrl,
					curr_lens_pos,
					&(move_params->
						ringing_params[a_ctrl->
						curr_region_index]),
					sign_dir,
					target_lens_pos);
			curr_lens_pos = target_lens_pos;

		} else {
			target_step_pos = step_boundary;
			target_lens_pos =
				a_ctrl->step_position_table[target_step_pos];
			a_ctrl->func_tbl->actuator_write_focus(a_ctrl,
					curr_lens_pos,
					&(move_params->ringing_params[a_ctrl->
						curr_region_index]),
					sign_dir,
					target_lens_pos);
			curr_lens_pos = target_lens_pos;

			a_ctrl->curr_region_index += sign_dir;
		}
		a_ctrl->curr_step_pos = target_step_pos;
	}
	msm_actuator_debug(ACTUATOR_INFO,"target_lens_pos =0x%x \n",target_lens_pos);
    //printk("xhx %s --------------before w_microdelay \n", __func__);

	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write_table_w_microdelay(
		&a_ctrl->i2c_client,
		a_ctrl->i2c_reg_tbl, a_ctrl->i2c_tbl_index,
		a_ctrl->i2c_data_type);
	if (rc < 0) {
		pr_err("i2c write error:%d\n", rc);
		return rc;
	}
	if(a_ctrl->cam_name ==0)
	{
		int loop=10;
		uint16_t val=0;
		if(sign_dir==1)
		{
			lc_direct_setting = 0xFE80;
		}
		else
		{
			lc_direct_setting = 0x0180;
		}
		msm_actuator_debug(ACTUATOR_DEBUG,"direction:sign_dir=%d setting=0x%x\n ", sign_dir,lc_direct_setting );
		rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
										&a_ctrl->i2c_client,
										0x16,
										lc_direct_setting,
										MSM_CAMERA_I2C_WORD_DATA);
		if(rc<0)
		{
			printk("%s : %d write lc_reg_setting1 fail\n", __func__, __LINE__);
			return rc;
		}

		rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
										&a_ctrl->i2c_client,
										0x8A,
										0x0D,
										MSM_CAMERA_I2C_BYTE_DATA);
		if(rc<0)
		{
			msm_actuator_debug(ACTUATOR_DEBUG,"%s : %d write lc_reg_setting1 fail\n", __func__, __LINE__);
			return rc;
		}
		while(loop--)
		{
			val =-1;
			rc=a_ctrl->i2c_client.i2c_func_tbl->i2c_read(
											&a_ctrl->i2c_client,
											0x8F,
											&val,
											MSM_CAMERA_I2C_BYTE_DATA);
			//printk("xhx loop=%d\n", loop);
			if(rc<0)
			{
				printk("%s : %d read status reg[0x85] fail\n", __func__, __LINE__);
				return rc;
			}	
			msm_actuator_debug(ACTUATOR_DEBUG,"val=%d\n", val);
			if((val & 0x01)==0)
			{
				printk("move focus finish \n");
				break;
			}
			//udelay(50);
			usleep_range(1000, 2000);
		}


	}
    //printk("xhx %s --------------Exit \n", __func__);
	a_ctrl->i2c_tbl_index = 0;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);

	return rc;
}

static int32_t msm_actuator_init_step_table(struct msm_actuator_ctrl_t *a_ctrl,
	struct msm_actuator_set_info_t *set_info)
{
	int16_t code_per_step = 0;
	int16_t cur_code = 0;
	int16_t lc_cur_code = 0;
	int16_t step_index = 0, region_index = 0;
	uint16_t step_boundary = 0;
	uint32_t max_code_size = 1;
	uint16_t data_size = set_info->actuator_params.data_size;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);
	if(a_ctrl->cam_name !=0)
	{
		for (; data_size > 0; data_size--)
			max_code_size *= 2;
		msm_actuator_debug(ACTUATOR_DEBUG,"open loop step code init\n");

		kfree(a_ctrl->step_position_table);
		a_ctrl->step_position_table = NULL;

		/* Fill step position table */
		a_ctrl->step_position_table =
			kmalloc(sizeof(uint16_t) *
			(set_info->af_tuning_params.total_steps + 1), GFP_KERNEL);

		if (a_ctrl->step_position_table == NULL)
			return -ENOMEM;

		cur_code = set_info->af_tuning_params.initial_code;
		a_ctrl->step_position_table[step_index++] = cur_code;
		for (region_index = 0;
			region_index < a_ctrl->region_size;
			region_index++) {
			code_per_step =
				a_ctrl->region_params[region_index].code_per_step;
			step_boundary =
				a_ctrl->region_params[region_index].
				step_bound[MOVE_NEAR];
			for (; step_index <= step_boundary;
				step_index++) {
				cur_code += code_per_step;
				if (cur_code < max_code_size)
					a_ctrl->step_position_table[step_index] =
						cur_code;
				else {
					for (; step_index <
						set_info->af_tuning_params.total_steps;
						step_index++)
						a_ctrl->
							step_position_table[
							step_index] =
							max_code_size;
				}
			}
		}
	}
	else //close loop step code
	{

		//int16_t macro_code=lc_cal_data_eeprom.lc_macro;
		int16_t macro_limit = 0x8000;
		int16_t infinity_code = lc_cal_data_eeprom.lc_infinity;
		int loop=0;
		kfree(a_ctrl->step_position_table);
		a_ctrl->step_position_table = NULL;
		msm_actuator_debug(ACTUATOR_DEBUG,"close loop step code init\n");
		a_ctrl->step_position_table =
			kmalloc(sizeof(uint16_t) *
			(set_info->af_tuning_params.total_steps + 1), GFP_KERNEL);
		if (a_ctrl->step_position_table == NULL)
			return -ENOMEM;
		lc_cur_code = infinity_code;
		a_ctrl->step_position_table[step_index++] = lc_cur_code;
		for (region_index = 0;
			region_index < a_ctrl->region_size;
			region_index++) {
			code_per_step =
				a_ctrl->region_params[region_index].code_per_step;
			step_boundary =
				a_ctrl->region_params[region_index].
				step_bound[MOVE_NEAR];
			msm_actuator_debug(ACTUATOR_DEBUG,"code per step=%d, macro_limit=%d\n", 
				a_ctrl->region_params[region_index].code_per_step,macro_limit);
			for (; step_index <= step_boundary+1;
				step_index++) {
				lc_cur_code -= code_per_step;
				if (lc_cur_code >= macro_limit)
					a_ctrl->step_position_table[step_index] =
						lc_cur_code;
				else {
					for (; step_index <=
						set_info->af_tuning_params.total_steps;
						step_index++)
						a_ctrl->
							step_position_table[
							step_index] =
							macro_limit;
				}
			}


			
			for(loop=0;loop<=set_info->af_tuning_params.total_steps;loop++)
			{
				msm_actuator_debug(ACTUATOR_INFO,"step[%d]=Hex:0x%x Dec:%d\n", loop,a_ctrl->step_position_table[loop],a_ctrl->step_position_table[loop]);
			}		
		}	

	}
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return 0;
}
static int32_t msm_actuator_move_lc_default_pos(struct msm_actuator_ctrl_t *a_ctrl)
{
	uint16_t reg_default_pos = lc_cal_data_eeprom.lc_infinity;
	int16_t  real_default_pos =reg_default_pos; // lc_cal_data_eeprom.lc_infinity;
	int16_t cur_pos = inital_pos_val;
	uint16_t lc_direct_setting=0;
	int rc=0;
	uint8_t val=0;
	
	msm_actuator_debug(ACTUATOR_DEBUG,"%s default_pos=0x%x:%d,cur_pos=0x%x:%d\n", __func__,
		   reg_default_pos,real_default_pos,inital_pos_val, cur_pos);
	if(cur_pos == real_default_pos)
	{
		printk("%s pos is same as default return\n", __func__);
		return 0;
	}
	val = (reg_default_pos >>8) & 0xFF;
	msm_actuator_debug(ACTUATOR_DEBUG,"set 0xA1=0x%x\n", val);
	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0xA1,
									val,
									MSM_CAMERA_I2C_BYTE_DATA);
	if(rc<0)
	{
		printk("%s : %d write pos high byte reg fail\n", __func__, __LINE__);
		return rc;
	}	


	val = (reg_default_pos) & 0xFF;
	msm_actuator_debug(ACTUATOR_DEBUG,"set 0xA2=0x%x\n", val);
	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0xA2,
									val,
									MSM_CAMERA_I2C_BYTE_DATA);
	if(rc<0)
	{
		printk("%s : %d  write pos low byte reg  fail\n", __func__, __LINE__);
		return rc;
	}
	

	
	//infinity is larger
	if(real_default_pos >cur_pos)
	{
		lc_direct_setting = 0x0180;
	}
	else
	{
		lc_direct_setting = 0xFE80;
	}
	msm_actuator_debug(ACTUATOR_DEBUG,"direction:setting=0x%x\n ", lc_direct_setting );
	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0x16,
									lc_direct_setting,
									MSM_CAMERA_I2C_WORD_DATA);
	if(rc<0)
	{
		msm_actuator_debug(ACTUATOR_DEBUG,"%s : %d write lc_reg_setting1 fail\n", __func__, __LINE__);
		return rc;
	}

	rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_write(
									&a_ctrl->i2c_client,
									0x8A,
									0x0D,
									MSM_CAMERA_I2C_BYTE_DATA);
	if(rc<0)
	{
		msm_actuator_debug(ACTUATOR_DEBUG,"%s : %d write lc_reg_setting1 fail\n", __func__, __LINE__);
		return rc;
	}

	return 0;
		

}
static int32_t msm_actuator_set_default_focus(
	struct msm_actuator_ctrl_t *a_ctrl,
	struct msm_actuator_move_params_t *move_params)
{
	int32_t rc = 0;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter curr_step_pos=%d\n",
			__func__,a_ctrl->curr_step_pos);

	if (a_ctrl->curr_step_pos != 0)
	{
		if(a_ctrl->cam_name !=0)
		{
				rc = a_ctrl->func_tbl->actuator_move_focus(a_ctrl, move_params);
		}
		else{
			msm_actuator_move_lc_default_pos(a_ctrl);
			a_ctrl->curr_step_pos =0;
		}
	}
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}

static int32_t msm_actuator_power_down(struct msm_actuator_ctrl_t *a_ctrl)
{
	int32_t rc = 0;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);
	if (a_ctrl->vcm_enable) {
		rc = gpio_direction_output(a_ctrl->vcm_pwd, 0);
		if (!rc)
			gpio_free(a_ctrl->vcm_pwd);
	}

	kfree(a_ctrl->step_position_table);
	a_ctrl->step_position_table = NULL;
	kfree(a_ctrl->i2c_reg_tbl);
	a_ctrl->i2c_reg_tbl = NULL;
	a_ctrl->i2c_tbl_index = 0;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}

static int32_t msm_actuator_init_lc_tune_data(struct msm_actuator_ctrl_t *a_ctrl,
	struct msm_actuator_set_info_t *set_info) 
{
	int32_t rc = -EFAULT;
	int16_t infinity_signed_value=0;
	int16_t macro_signed_value=0;
	msm_actuator_debug(ACTUATOR_INFO,"%s start\n", __func__);
	a_ctrl->func_tbl->lc_actuator_init_focus(a_ctrl);
	infinity_signed_value=lc_cal_data_eeprom.lc_infinity;
	macro_signed_value=lc_cal_data_eeprom.lc_macro;	
	msm_actuator_debug(ACTUATOR_INFO,"%s before init step table\n", __func__);
	msm_actuator_debug(ACTUATOR_INFO,"%s total_steps=%d.step_bound[0]=%d\n",__func__, set_info->af_tuning_params.total_steps,a_ctrl->region_params[0].step_bound[0]);
#if 0
	//thease source should be sync with the eeprom->eeprom_autofocus_calibration()
	if((lc_cal_data_eeprom.lc_infinity >=0 && lc_cal_data_eeprom.lc_infinity <= 0x7FFF)&&
		(lc_cal_data_eeprom.lc_macro >= 0x8000 && lc_cal_data_eeprom.lc_macro <=0xFFFF))
	{
		a_ctrl->region_params[0].code_per_step = (lc_cal_data_eeprom.lc_infinity+(0xFFFF-lc_cal_data_eeprom.lc_macro)+2)/
												(a_ctrl->region_params[0].step_bound[0]-a_ctrl->region_params[0].step_bound[1]-2);

	}
	else
	{
		a_ctrl->region_params[0].code_per_step =  (lc_cal_data_eeprom.lc_infinity-lc_cal_data_eeprom.lc_macro+1)/
													(a_ctrl->region_params[0].step_bound[0]-a_ctrl->region_params[0].step_bound[1]);
	}
#else
#if 0
	if((lc_cal_data_eeprom.lc_infinity >=0 && lc_cal_data_eeprom.lc_infinity <= 0x7FFF)&&
		(lc_cal_data_eeprom.lc_macro >= 0x8000 && lc_cal_data_eeprom.lc_macro <=0xFFFF))
	{
		a_ctrl->region_params[0].code_per_step = (lc_cal_data_eeprom.lc_infinity+(0xFFFF-lc_cal_data_eeprom.lc_macro)+2)/
												(set_info->af_tuning_params.total_steps-1-MSM_ACTUATOR_LC_INFI_ADDITIONAL-MSM_ACTUATOR_LC_MACRO_ADDITIONAL);

	}
	else
	{
		a_ctrl->region_params[0].code_per_step =  (lc_cal_data_eeprom.lc_infinity-lc_cal_data_eeprom.lc_macro+1)/
													(set_info->af_tuning_params.total_steps-1-MSM_ACTUATOR_LC_INFI_ADDITIONAL-MSM_ACTUATOR_LC_MACRO_ADDITIONAL);
		
	}
#else
	a_ctrl->region_params[0].code_per_step = ( infinity_signed_value - macro_signed_value )/
												(set_info->af_tuning_params.total_steps-1-MSM_ACTUATOR_LC_INFI_ADDITIONAL-MSM_ACTUATOR_LC_MACRO_ADDITIONAL);

#endif
#endif
	msm_actuator_debug(ACTUATOR_INFO,"%s , code_per_step=0x%x(%d)\n", __func__,
	a_ctrl->region_params[0].code_per_step,
	a_ctrl->region_params[0].code_per_step);

	/*addtional for infinity and macro ends*/
	msm_actuator_debug(ACTUATOR_INFO,"%s,old signed infi=%d signed macro=%d\n", __func__, 
	infinity_signed_value,
	macro_signed_value);

	infinity_signed_value += a_ctrl->region_params[0].code_per_step*MSM_ACTUATOR_LC_INFI_ADDITIONAL;
	macro_signed_value -= a_ctrl->region_params[0].code_per_step*MSM_ACTUATOR_LC_MACRO_ADDITIONAL;
	
	msm_actuator_debug(ACTUATOR_INFO,"%s,new signed infi=%d signed macro=%d\n", __func__, 
		infinity_signed_value,
		macro_signed_value);
	
	lc_cal_data_eeprom.lc_infinity = infinity_signed_value;
	lc_cal_data_eeprom.lc_macro = macro_signed_value;
	
	msm_actuator_debug(ACTUATOR_INFO,"%s new unsigned infi=0x%x, unsigned macro=0x%x\n", __func__, 
		lc_cal_data_eeprom.lc_infinity,
		lc_cal_data_eeprom.lc_macro);
	/*addtional for infinity and macro ends*/


	if(lc_cal_data_eeprom.lc_macro >=lc_cal_data_eeprom.lc_infinity && 
		(( lc_cal_data_eeprom.lc_macro >=0 && lc_cal_data_eeprom.lc_macro<=0x7FFF)
		||(lc_cal_data_eeprom.lc_infinity<=0xFFFF && lc_cal_data_eeprom.lc_infinity>=0x8000)))
		a_ctrl->region_params[0].code_per_step =0;
	
	if (a_ctrl->func_tbl->actuator_init_step_table)
		rc = a_ctrl->func_tbl->
			actuator_init_step_table(a_ctrl, set_info);
	msm_actuator_move_lc_default_pos(a_ctrl);
	a_ctrl->curr_step_pos = 0;
	a_ctrl->curr_region_index = 0;
	return rc;

}

static int32_t msm_actuator_init(struct msm_actuator_ctrl_t *a_ctrl,
	struct msm_actuator_set_info_t *set_info) {
	struct reg_settings_t *init_settings = NULL;
	int32_t rc = -EFAULT;
	uint16_t i = 0;
	struct msm_camera_cci_client *cci_client = NULL;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);

	for (i = 0; i < ARRAY_SIZE(actuators); i++) {
		if (set_info->actuator_params.act_type ==
			actuators[i]->act_type) {
			a_ctrl->func_tbl = &actuators[i]->func_tbl;
			rc = 0;
		}
	}

	if (rc < 0) {
		pr_err("Actuator function table not found\n");
		return rc;
	}

	a_ctrl->region_size = set_info->af_tuning_params.region_size;
	if (a_ctrl->region_size > MAX_ACTUATOR_REGION) {
		pr_err("MAX_ACTUATOR_REGION is exceeded.\n");
		return -EFAULT;
	}
	a_ctrl->pwd_step = set_info->af_tuning_params.pwd_step;
	a_ctrl->total_steps = set_info->af_tuning_params.total_steps;

	if (copy_from_user(&a_ctrl->region_params,
		(void *)set_info->af_tuning_params.region_params,
		a_ctrl->region_size * sizeof(struct region_params_t)))
		return -EFAULT;

	if (a_ctrl->act_device_type == MSM_CAMERA_PLATFORM_DEVICE) {
		cci_client = a_ctrl->i2c_client.cci_client;
		cci_client->sid =
			set_info->actuator_params.i2c_addr >> 1;
		cci_client->retries = 3;
		cci_client->id_map = 0;
		cci_client->cci_i2c_master = a_ctrl->cci_master;
	} else {
		a_ctrl->i2c_client.client->addr =
			set_info->actuator_params.i2c_addr;
	}

	a_ctrl->i2c_data_type = set_info->actuator_params.i2c_data_type;
	a_ctrl->i2c_client.addr_type = set_info->actuator_params.i2c_addr_type;
	a_ctrl->reg_tbl_size = set_info->actuator_params.reg_tbl_size;
	if (a_ctrl->reg_tbl_size > MAX_ACTUATOR_REG_TBL_SIZE) {
		pr_err("MAX_ACTUATOR_REG_TBL_SIZE is exceeded.\n");
		return -EFAULT;
	}

	kfree(a_ctrl->i2c_reg_tbl);

	a_ctrl->i2c_reg_tbl =
		kmalloc(sizeof(struct msm_camera_i2c_reg_tbl) *
		(set_info->af_tuning_params.total_steps + 1), GFP_KERNEL);
	if (!a_ctrl->i2c_reg_tbl) {
		pr_err("kmalloc fail\n");
		return -ENOMEM;
	}

	if (copy_from_user(&a_ctrl->reg_tbl,
		(void *)set_info->actuator_params.reg_tbl_params,
		a_ctrl->reg_tbl_size *
		sizeof(struct msm_actuator_reg_params_t))) {
		kfree(a_ctrl->i2c_reg_tbl);
		return -EFAULT;
	}

	if (set_info->actuator_params.init_setting_size) {
		if (a_ctrl->func_tbl->actuator_init_focus) {
			init_settings = kmalloc(sizeof(struct reg_settings_t) *
				(set_info->actuator_params.init_setting_size),
				GFP_KERNEL);
			if (init_settings == NULL) {
				kfree(a_ctrl->i2c_reg_tbl);
				pr_err("Error allocating memory for init_settings\n");
				return -EFAULT;
			}
			if (copy_from_user(init_settings,
				(void *)set_info->actuator_params.init_settings,
				set_info->actuator_params.init_setting_size *
				sizeof(struct reg_settings_t))) {
				kfree(init_settings);
				kfree(a_ctrl->i2c_reg_tbl);
				pr_err("Error copying init_settings\n");
				return -EFAULT;
			}
			rc = a_ctrl->func_tbl->actuator_init_focus(a_ctrl,
				set_info->actuator_params.init_setting_size,
				a_ctrl->i2c_data_type,
				init_settings);
			kfree(init_settings);
			if (rc < 0) {
				kfree(a_ctrl->i2c_reg_tbl);
				pr_err("Error actuator_init_focus\n");
				return -EFAULT;
			}
		}
	}

	if(a_ctrl->cam_name !=0)
	{
		a_ctrl->initial_code = set_info->af_tuning_params.initial_code;
		if (a_ctrl->func_tbl->actuator_init_step_table)
			rc = a_ctrl->func_tbl->
				actuator_init_step_table(a_ctrl, set_info);

		a_ctrl->curr_step_pos = 0;
		a_ctrl->curr_region_index = 0;
	}
	else
	{
		if(need_init_lc==1)
		{
			msm_actuator_init_lc_tune_data(a_ctrl, set_info);
			need_init_lc=0;
		}

	}
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);

	return rc;
}

static int32_t msm_actuator_config(struct msm_actuator_ctrl_t *a_ctrl,
	void __user *argp)
{
	struct msm_actuator_cfg_data *cdata =
		(struct msm_actuator_cfg_data *)argp;
	int32_t rc = 0;
	mutex_lock(a_ctrl->actuator_mutex);
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);
	msm_actuator_debug(ACTUATOR_DEBUG,"%s type %d\n", __func__, cdata->cfgtype);
	switch (cdata->cfgtype) {
	case CFG_GET_ACTUATOR_INFO:
		msm_actuator_debug(ACTUATOR_DEBUG,"%s CFG_GET_ACTUATOR_INFO\n", __func__);
		cdata->is_af_supported = 1;
		cdata->cfg.cam_name = a_ctrl->cam_name;
		need_init_lc=1;
		break;

	case CFG_SET_ACTUATOR_INFO:
		msm_actuator_debug(ACTUATOR_DEBUG,"%s CFG_SET_ACTUATOR_INFO\n", __func__);
		rc = msm_actuator_init(a_ctrl, &cdata->cfg.set_info);
		if (rc < 0)
			pr_err("init table failed %d\n", rc);
		break;

	case CFG_SET_DEFAULT_FOCUS:
		msm_actuator_debug(ACTUATOR_DEBUG,"%s CFG_SET_DEFAULT_FOCUS\n", __func__);
		rc = a_ctrl->func_tbl->actuator_set_default_focus(a_ctrl,
			&cdata->cfg.move);
		if (rc < 0)
			pr_err("move focus failed %d\n", rc);
		break;

	case CFG_MOVE_FOCUS:
		msm_actuator_debug(ACTUATOR_DEBUG,"%s CFG_MOVE_FOCUS\n", __func__);
		rc = a_ctrl->func_tbl->actuator_move_focus(a_ctrl,
			&cdata->cfg.move);
		if (rc < 0)
			pr_err("move focus failed %d\n", rc);
		break;

	default:
		break;
	}
	mutex_unlock(a_ctrl->actuator_mutex);
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}

static int32_t msm_actuator_get_subdev_id(struct msm_actuator_ctrl_t *a_ctrl,
	void *arg)
{
	uint32_t *subdev_id = (uint32_t *)arg;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);
	if (!subdev_id) {
		pr_err("failed\n");
		return -EINVAL;
	}
	if (a_ctrl->act_device_type == MSM_CAMERA_PLATFORM_DEVICE)
		*subdev_id = a_ctrl->pdev->id;
	else
		*subdev_id = a_ctrl->subdev_id;

	msm_actuator_debug(ACTUATOR_DEBUG,"subdev_id %d\n", *subdev_id);
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return 0;
}

static struct msm_camera_i2c_fn_t msm_sensor_cci_func_tbl = {
	.i2c_read = msm_camera_cci_i2c_read,
	.i2c_read_seq = msm_camera_cci_i2c_read_seq,
	.i2c_write = msm_camera_cci_i2c_write,
	.i2c_write_table = msm_camera_cci_i2c_write_table,
	.i2c_write_seq_table = msm_camera_cci_i2c_write_seq_table,
	.i2c_write_table_w_microdelay =
		msm_camera_cci_i2c_write_table_w_microdelay,
	.i2c_util = msm_sensor_cci_i2c_util,
};

static struct msm_camera_i2c_fn_t msm_sensor_qup_func_tbl = {
	.i2c_read = msm_camera_qup_i2c_read,
	.i2c_read_seq = msm_camera_qup_i2c_read_seq,
	.i2c_write = msm_camera_qup_i2c_write,
	.i2c_write_table = msm_camera_qup_i2c_write_table,
	.i2c_write_seq_table = msm_camera_qup_i2c_write_seq_table,
	.i2c_write_table_w_microdelay =
		msm_camera_qup_i2c_write_table_w_microdelay,
};
#ifdef LENOVO_PATCH
static int msm_actuator_get_dt_data(struct msm_actuator_ctrl_t *a_ctrl)
{
	int rc = 0;
	struct msm_camera_power_ctrl_t *power_info = &(a_ctrl->power_info);
	struct device_node *of_node = NULL;
	printk("%s :%d\n", __func__,__LINE__);

	 of_node = a_ctrl->pdev->dev.of_node;
	rc = msm_camera_get_dt_vreg_data(of_node, &(power_info->cam_vreg),
					     &(power_info->num_vreg));
	printk("%s :%d\n", __func__,__LINE__);

	if (rc)
		return rc;

	printk("%s :%d\n", __func__,__LINE__);
	rc = msm_camera_get_dt_power_setting_data(of_node,
		  power_info->cam_vreg, power_info->num_vreg,
		  &(power_info->power_setting), &(power_info->power_setting_size));
	if (rc)
		goto  ERROR1;
	printk("%s :%d\n", __func__,__LINE__);


	
	return rc;


ERROR1:
	kfree(power_info->power_setting);
	return rc;
}
#endif
int actuator_open_flag=0;

static int msm_actuator_open(struct v4l2_subdev *sd,
	struct v4l2_subdev_fh *fh) {
	int rc = 0;
	struct msm_actuator_ctrl_t *a_ctrl =  v4l2_get_subdevdata(sd);
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);
	if (!a_ctrl) {
		pr_err("failed\n");
		return -EINVAL;
	}
	actuator_open_flag=1;
#ifdef LENOVO_PATCH
	rc = msm_camera_power_up(&(a_ctrl->power_info), a_ctrl->act_device_type,
	&a_ctrl->i2c_client);
	if (rc) {
		pr_err("=============================%s failed rc %d\n",__func__, rc);
	}
#endif
	if (a_ctrl->act_device_type == MSM_CAMERA_PLATFORM_DEVICE) {
		rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_util(
			&a_ctrl->i2c_client, MSM_CCI_INIT);
		if (rc < 0)
			pr_err("cci_init failed\n");
	}
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}

static int msm_actuator_close(struct v4l2_subdev *sd,
	struct v4l2_subdev_fh *fh) {
	int rc = 0;
	struct msm_actuator_ctrl_t *a_ctrl =  v4l2_get_subdevdata(sd);
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);
	if (!a_ctrl) {
		pr_err("failed\n");
		return -EINVAL;
	}
	if (a_ctrl->act_device_type == MSM_CAMERA_PLATFORM_DEVICE) {
		rc = a_ctrl->i2c_client.i2c_func_tbl->i2c_util(
			&a_ctrl->i2c_client, MSM_CCI_RELEASE);
		if (rc < 0)
			pr_err("cci_init failed\n");
	}
#ifdef LENOVO_PATCH
	rc=msm_camera_power_down(&(a_ctrl->power_info),  a_ctrl->act_device_type,
		&a_ctrl->i2c_client);
	if (rc) {
		pr_err("=====================%s failed rc %d\n",__func__, rc);
	}
#endif
	kfree(a_ctrl->i2c_reg_tbl);
	a_ctrl->i2c_reg_tbl = NULL;

	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}

static const struct v4l2_subdev_internal_ops msm_actuator_internal_ops = {
	.open = msm_actuator_open,
	.close = msm_actuator_close,
};

static long msm_actuator_subdev_ioctl(struct v4l2_subdev *sd,
			unsigned int cmd, void *arg)
{
	struct msm_actuator_ctrl_t *a_ctrl = v4l2_get_subdevdata(sd);
	void __user *argp = (void __user *)arg;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);
	msm_actuator_debug(ACTUATOR_DEBUG,"%s:%d a_ctrl %p argp %p\n", __func__, __LINE__, a_ctrl, argp);
	switch (cmd) {
	case VIDIOC_MSM_SENSOR_GET_SUBDEV_ID:
		return msm_actuator_get_subdev_id(a_ctrl, argp);
	case VIDIOC_MSM_ACTUATOR_CFG:
		return msm_actuator_config(a_ctrl, argp);
	case MSM_SD_SHUTDOWN:
		msm_actuator_close(sd, NULL);
		return 0;
	default:
		return -ENOIOCTLCMD;
	}
}

static int32_t msm_actuator_power_up(struct msm_actuator_ctrl_t *a_ctrl)
{
	int rc = 0;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s called\n", __func__);

	msm_actuator_debug(ACTUATOR_DEBUG,"vcm info: %x %x\n", a_ctrl->vcm_pwd,
		a_ctrl->vcm_enable);
	if (a_ctrl->vcm_enable) {
		rc = gpio_request(a_ctrl->vcm_pwd, "msm_actuator");
		if (!rc) {
			msm_actuator_debug(ACTUATOR_DEBUG,"Enable VCM PWD\n");
			gpio_direction_output(a_ctrl->vcm_pwd, 1);
		}
	}
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}

static int32_t msm_actuator_power(struct v4l2_subdev *sd, int on)
{
	int rc = 0;
	struct msm_actuator_ctrl_t *a_ctrl = v4l2_get_subdevdata(sd);
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);
	mutex_lock(a_ctrl->actuator_mutex);
	if (on)
		rc = msm_actuator_power_up(a_ctrl);
	else
		rc = msm_actuator_power_down(a_ctrl);
	mutex_unlock(a_ctrl->actuator_mutex);
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}

static struct v4l2_subdev_core_ops msm_actuator_subdev_core_ops = {
	.ioctl = msm_actuator_subdev_ioctl,
	.s_power = msm_actuator_power,
};

static struct v4l2_subdev_ops msm_actuator_subdev_ops = {
	.core = &msm_actuator_subdev_core_ops,
};

static const struct i2c_device_id msm_actuator_i2c_id[] = {
	{"qcom,actuator", (kernel_ulong_t)NULL},
	{ }
};

static int32_t msm_actuator_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;
	struct msm_actuator_ctrl_t *act_ctrl_t = NULL;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);

	if (client == NULL) {
		pr_err("msm_actuator_i2c_probe: client is null\n");
		rc = -EINVAL;
		goto probe_failure;
	}

	act_ctrl_t = kzalloc(sizeof(struct msm_actuator_ctrl_t),
		GFP_KERNEL);
	if (!act_ctrl_t) {
		pr_err("%s:%d failed no memory\n", __func__, __LINE__);
		return -ENOMEM;
	}

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		pr_err("i2c_check_functionality failed\n");
		goto probe_failure;
	}

	msm_actuator_debug(ACTUATOR_DEBUG,"client = %x\n", (unsigned int) client);

	rc = of_property_read_u32(client->dev.of_node, "cell-index",
		&act_ctrl_t->subdev_id);
	msm_actuator_debug(ACTUATOR_DEBUG,"cell-index %d, rc %d\n", act_ctrl_t->subdev_id, rc);
	if (rc < 0) {
		pr_err("failed rc %d\n", rc);
		return rc;
	}

	act_ctrl_t->i2c_driver = &msm_actuator_i2c_driver;
    msm_actuator_debug(ACTUATOR_DEBUG,"client = %x\n", (unsigned int) client);
	act_ctrl_t->i2c_client.client = client;
	act_ctrl_t->curr_step_pos = 0,
	act_ctrl_t->curr_region_index = 0,
	/* Set device type as I2C */
	act_ctrl_t->act_device_type = MSM_CAMERA_I2C_DEVICE;
	act_ctrl_t->i2c_client.i2c_func_tbl = &msm_sensor_qup_func_tbl;
	act_ctrl_t->act_v4l2_subdev_ops = &msm_actuator_subdev_ops;
	act_ctrl_t->actuator_mutex = &msm_actuator_mutex;

	act_ctrl_t->cam_name = act_ctrl_t->subdev_id;
	msm_actuator_debug(ACTUATOR_DEBUG,"act_ctrl_t->cam_name: %d", act_ctrl_t->cam_name);
	/* Assign name for sub device */
	snprintf(act_ctrl_t->msm_sd.sd.name, sizeof(act_ctrl_t->msm_sd.sd.name),
		"%s", act_ctrl_t->i2c_driver->driver.name);

	/* Initialize sub device */
	v4l2_i2c_subdev_init(&act_ctrl_t->msm_sd.sd,
		act_ctrl_t->i2c_client.client,
		act_ctrl_t->act_v4l2_subdev_ops);
	v4l2_set_subdevdata(&act_ctrl_t->msm_sd.sd, act_ctrl_t);
	act_ctrl_t->msm_sd.sd.internal_ops = &msm_actuator_internal_ops;
	act_ctrl_t->msm_sd.sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	media_entity_init(&act_ctrl_t->msm_sd.sd.entity, 0, NULL, 0);
	act_ctrl_t->msm_sd.sd.entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
	act_ctrl_t->msm_sd.sd.entity.group_id = MSM_CAMERA_SUBDEV_ACTUATOR;
	act_ctrl_t->msm_sd.close_seq = MSM_SD_CLOSE_2ND_CATEGORY | 0x2;
	msm_sd_register(&act_ctrl_t->msm_sd);
	msm_actuator_debug(ACTUATOR_DEBUG,"succeeded\n");
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);

probe_failure:
	return rc;
}
#ifdef LENOVO_PATCH
static struct msm_cam_clk_info cam_8974_clk_info[] = {
	[SENSOR_CAM_MCLK] = {"cam_src_clk", 19200000},
	[SENSOR_CAM_CLK] = {"cam_clk", 0},
};
#endif
static int32_t msm_actuator_platform_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	struct msm_camera_cci_client *cci_client = NULL;
	struct msm_actuator_ctrl_t *msm_actuator_t = NULL;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Enter\n", __func__);

	if (!pdev->dev.of_node) {
		pr_err("of_node NULL\n");
		return -EINVAL;
	}

	msm_actuator_t = kzalloc(sizeof(struct msm_actuator_ctrl_t),
		GFP_KERNEL);
	if (!msm_actuator_t) {
		pr_err("%s:%d failed no memory\n", __func__, __LINE__);
		return -ENOMEM;
	}
	rc = of_property_read_u32((&pdev->dev)->of_node, "cell-index",
		&pdev->id);
	msm_actuator_debug(ACTUATOR_DEBUG,"cell-index %d, rc %d\n", pdev->id, rc);
	if (rc < 0) {
		pr_err("failed rc %d\n", rc);
		return rc;
	}

	rc = of_property_read_u32((&pdev->dev)->of_node, "qcom,cci-master",
		&msm_actuator_t->cci_master);
	msm_actuator_debug(ACTUATOR_DEBUG,"qcom,cci-master %d, rc %d\n", msm_actuator_t->cci_master, rc);
	if (rc < 0) {
		pr_err("failed rc %d\n", rc);
		return rc;
	}

	msm_actuator_t->act_v4l2_subdev_ops = &msm_actuator_subdev_ops;
	msm_actuator_t->actuator_mutex = &msm_actuator_mutex;
	msm_actuator_t->cam_name = pdev->id;

	/* Set platform device handle */
	msm_actuator_t->pdev = pdev;
	/* Set device type as platform device */
	msm_actuator_t->act_device_type = MSM_CAMERA_PLATFORM_DEVICE;
#ifdef LENOVO_PATCH
	msm_actuator_t->power_info.clk_info = cam_8974_clk_info;
	msm_actuator_t->power_info.clk_info_size = ARRAY_SIZE(cam_8974_clk_info);

	msm_actuator_t->power_info.dev = &pdev->dev;
#endif
	msm_actuator_t->i2c_client.i2c_func_tbl = &msm_sensor_cci_func_tbl;
	msm_actuator_t->i2c_client.cci_client = kzalloc(sizeof(
		struct msm_camera_cci_client), GFP_KERNEL);
	if (!msm_actuator_t->i2c_client.cci_client) {
		pr_err("failed no memory\n");
		return -ENOMEM;
	}

	cci_client = msm_actuator_t->i2c_client.cci_client;
	cci_client->cci_subdev = msm_cci_get_subdev();
#ifdef QUALCOMM_PATCH
       cci_client->cci_i2c_master = MASTER_MAX;
#endif
#ifdef LENOVO_PATCH
	msm_actuator_get_dt_data(msm_actuator_t);
#endif
	v4l2_subdev_init(&msm_actuator_t->msm_sd.sd,
		msm_actuator_t->act_v4l2_subdev_ops);
	v4l2_set_subdevdata(&msm_actuator_t->msm_sd.sd, msm_actuator_t);
	msm_actuator_t->msm_sd.sd.internal_ops = &msm_actuator_internal_ops;
	msm_actuator_t->msm_sd.sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	snprintf(msm_actuator_t->msm_sd.sd.name,
		ARRAY_SIZE(msm_actuator_t->msm_sd.sd.name), "msm_actuator");
	media_entity_init(&msm_actuator_t->msm_sd.sd.entity, 0, NULL, 0);
	msm_actuator_t->msm_sd.sd.entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
	msm_actuator_t->msm_sd.sd.entity.group_id = MSM_CAMERA_SUBDEV_ACTUATOR;
	msm_actuator_t->msm_sd.close_seq = MSM_SD_CLOSE_2ND_CATEGORY | 0x2;
	msm_sd_register(&msm_actuator_t->msm_sd);
	//lc_cal_data_eeprom.readed=0;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s Exit\n", __func__);
	return rc;
}

static const struct of_device_id msm_actuator_i2c_dt_match[] = {
	{.compatible = "qcom,actuator"},
	{}
};

MODULE_DEVICE_TABLE(of, msm_actuator_i2c_dt_match);

static struct i2c_driver msm_actuator_i2c_driver = {
	.id_table = msm_actuator_i2c_id,
	.probe  = msm_actuator_i2c_probe,
	.remove = __exit_p(msm_actuator_i2c_remove),
	.driver = {
		.name = "qcom,actuator",
		.owner = THIS_MODULE,
		.of_match_table = msm_actuator_i2c_dt_match,
	},
};

static const struct of_device_id msm_actuator_dt_match[] = {
	{.compatible = "qcom,actuator", .data = NULL},
	{}
};

MODULE_DEVICE_TABLE(of, msm_actuator_dt_match);

static struct platform_driver msm_actuator_platform_driver = {
	.driver = {
		.name = "qcom,actuator",
		.owner = THIS_MODULE,
		.of_match_table = msm_actuator_dt_match,
	},
};

static int __init msm_actuator_init_module(void)
{
	int32_t rc = 0;
	msm_actuator_debug(ACTUATOR_DEBUG,"Enter\n");
	rc = platform_driver_probe(&msm_actuator_platform_driver,
		msm_actuator_platform_probe);
	if (!rc)
		return rc;
	msm_actuator_debug(ACTUATOR_DEBUG,"%s:%d rc %d\n", __func__, __LINE__, rc);
	return i2c_add_driver(&msm_actuator_i2c_driver);
}

static struct msm_actuator msm_vcm_actuator_table = {
	.act_type = ACTUATOR_VCM,
	.func_tbl = {
		.actuator_init_step_table = msm_actuator_init_step_table,
		.actuator_move_focus = msm_actuator_move_focus,
		.actuator_write_focus = msm_actuator_write_focus,
		.actuator_set_default_focus = msm_actuator_set_default_focus,
		.actuator_init_focus = msm_actuator_init_focus,
		.actuator_parse_i2c_params = msm_actuator_parse_i2c_params,
		.actuator_lc_parse_i2c_params = msm_actuator_lc_parse_i2c_params,
		.lc_actuator_init_focus = msm_lc_actuator_init_focus,
	},
};

static struct msm_actuator msm_piezo_actuator_table = {
	.act_type = ACTUATOR_PIEZO,
	.func_tbl = {
		.actuator_init_step_table = NULL,
		.actuator_move_focus = msm_actuator_piezo_move_focus,
		.actuator_write_focus = NULL,
		.actuator_set_default_focus =
			msm_actuator_piezo_set_default_focus,
		.actuator_init_focus = msm_actuator_init_focus,
		.actuator_parse_i2c_params = msm_actuator_parse_i2c_params,
	},
};

module_init(msm_actuator_init_module);
MODULE_DESCRIPTION("MSM ACTUATOR");
MODULE_LICENSE("GPL v2");

/* Copyright (c) 2008-2013, The Linux Foundation. All rights reserved.
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
static char nt35596_sleepout12[] = {0xFF, 0x00};
static char nt355596_sleepout1[] = {0x11, 0x00};
static char nt355596_sleepout2[] = {0x29, 0x00};

static char nt35596_ce_set1_cabcoff[] = {0x55,0x80};
static char nt35596_ce_set1_cabcon[] = {0x55,0x83};
//static char nt35596_ce_set2[] = {0x55,0x80};
static char nt35596_ce_set3_cabcoff[] = {0x55,0x90};
static char nt35596_ce_set3_cabcon[] = {0x55,0x93};
//static char nt35596_ce_set4[] = {0x55,0xB0};
static char nt35596_ce_set5_cabcoff[] = {0x55,0xB0};
static char nt35596_ce_set5_cabcon[] = {0x55,0xB3};
//static char nt35596_ce_set6[] = {0x55,0x50};
//static char nt35596_ce_set7[] = {0x55,0x60};

static char nt35596_page3_set[] = {0xFF,0x00};
static char nt35596_pwm_on[] = {0x53,0x2c};
static char nt35596_pwm_off[] = {0x53,0x24};

static char nt35596_sleepout_test1[] = {0xFF,0x01};
static char nt35596_sleepout_test2[] = {0x01,0x55};
static char nt35596_sleepout_test3[] = {0x15,0x0F};
static char nt35596_sleepout_test4[] = {0x16,0x0F};
static char nt35596_sleepout_test5[] = {0x1B,0x1B};
static char nt35596_sleepout_test6[] = {0x1C,0xF7};
static char nt35596_sleepout_test7[] = {0x60,0x0F};
static char nt35596_sleepout_test8[] = {0x58,0x82};
static char nt35596_sleepout_test9[] = {0x59,0x00};
static char nt35596_sleepout_test10[] = {0x5A,0x02};
static char nt35596_sleepout_test11[] = {0x5B,0x00};
static char nt35596_sleepout_test12[] = {0x5C,0x82};
static char nt35596_sleepout_test13[] = {0x5D,0x80};
static char nt35596_sleepout_test14[] = {0x5E,0x02};
static char nt35596_sleepout_test15[] = {0x5F,0x00};
static char nt35596_sleepout_test16[] = {0x66,0x01};
static char nt35596_sleepout_test17[] = {0xFB,0x01};
static char nt35596_sleepout_test18[] = {0xFF,0x05};
static char nt35596_sleepout_test19[] = {0x54,0x75};
static char nt35596_sleepout_test20[] = {0x85,0x05};
static char nt35596_sleepout_test21[] = {0xA6,0x04};
static char nt35596_sleepout_test22[] = {0xFB,0x01};
static char nt35596_sleepout_test23[] = {0xFF,0xFF};
static char nt35596_sleepout_test24[] = {0x4F,0x03};
static char nt35596_sleepout_test25[] = {0xFB,0x01};
static char nt35596_sleepout_test26[] = {0xFF,0x00};

static struct dsi_cmd_desc dsi_nt36696_enable_pwm_on[] = {
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_page3_set)}, nt35596_page3_set},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_pwm_on)}, nt35596_pwm_on},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};
static struct dsi_cmd_desc dsi_nt36696_enable_pwm_off[] = {
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_page3_set)}, nt35596_page3_set},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_pwm_off)}, nt35596_pwm_off},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};

static struct dsi_cmd_desc dsi_nt36696_sleepout[] = {
      {{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test1)}, nt35596_sleepout_test1},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test2)}, nt35596_sleepout_test2},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test3)}, nt35596_sleepout_test3},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test4)}, nt35596_sleepout_test4},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test5)}, nt35596_sleepout_test5},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test6)}, nt35596_sleepout_test6},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test7)}, nt35596_sleepout_test7},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test8)}, nt35596_sleepout_test8},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test9)}, nt35596_sleepout_test9},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test10)}, nt35596_sleepout_test10},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test11)}, nt35596_sleepout_test11},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test12)}, nt35596_sleepout_test12},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test13)}, nt35596_sleepout_test13},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test14)}, nt35596_sleepout_test14},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test15)}, nt35596_sleepout_test15},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test16)}, nt35596_sleepout_test16},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test17)}, nt35596_sleepout_test17},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test18)}, nt35596_sleepout_test18},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test19)}, nt35596_sleepout_test19},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test20)}, nt35596_sleepout_test20},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test21)}, nt35596_sleepout_test21},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test22)}, nt35596_sleepout_test22},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test23)}, nt35596_sleepout_test23},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test24)}, nt35596_sleepout_test24},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test25)}, nt35596_sleepout_test25},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout_test26)}, nt35596_sleepout_test26},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
	{{DTYPE_DCS_WRITE, 1, 0, 0, 200, sizeof(nt355596_sleepout1)}, nt355596_sleepout1},
	{{DTYPE_DCS_WRITE, 1, 0, 0, 200, sizeof(nt355596_sleepout2)}, nt355596_sleepout2},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};

static struct dsi_cmd_desc dsi_nt36696_ce_soft_cabcoff[] = {
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_ce_set1_cabcoff)}, nt35596_ce_set1_cabcoff},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};
static struct dsi_cmd_desc dsi_nt36696_ce_normal_cabcoff[] = {
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_ce_set3_cabcoff)}, nt35596_ce_set3_cabcoff},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};
static struct dsi_cmd_desc dsi_nt36696_ce_brilliancy_cabcoff[] = {
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_ce_set5_cabcoff)}, nt35596_ce_set5_cabcoff},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};

static struct dsi_cmd_desc dsi_nt36696_ce_soft_cabcon[] = {
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_ce_set1_cabcon)}, nt35596_ce_set1_cabcon},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};
static struct dsi_cmd_desc dsi_nt36696_ce_normal_cabcon[] = {
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_ce_set3_cabcon)}, nt35596_ce_set3_cabcon},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};
static struct dsi_cmd_desc dsi_nt36696_ce_brilliancy_cabcon[] = {
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_ce_set5_cabcon)}, nt35596_ce_set5_cabcon},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};

static char nt35596_sharpness1[] = {0xFF,0x03};
static char nt35596_sharpness3_off[] = {0x63,0x00};
static char nt35596_sharpness3_on[] = {0x63,0x77};

static struct dsi_cmd_desc dsi_nt35596_sharpness_setting[] = {
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sharpness1)}, nt35596_sharpness1},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sharpness3_on)}, nt35596_sharpness3_on},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};

static struct dsi_cmd_desc dsi_nt35596_sharpness_off[] = {
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sharpness1)}, nt35596_sharpness1},
	{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_sharpness3_off)}, nt35596_sharpness3_off},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};

static char nt35596_gamma_warm1[] = {0xFF, 0x01};
static char nt35596_gamma_warm2[] = {0xFB, 0x01};
static char nt35596_gamma_warm3[] = {0x75, 0x01};
static char nt35596_gamma_warm4[] = {0x76, 0x2D};
static char nt35596_gamma_warm5[] = {0x77, 0x01};
static char nt35596_gamma_warm6[] = {0x78, 0x31};
static char nt35596_gamma_warm7[] = {0x79, 0x01};
static char nt35596_gamma_warm8[] = {0x7A, 0x36};
static char nt35596_gamma_warm9[] = {0x7B, 0x01};
static char nt35596_gamma_warm10[] = {0x7C, 0x3D};
static char nt35596_gamma_warm11[] = {0x7D, 0x01};
static char nt35596_gamma_warm12[] = {0x7E, 0x43};
static char nt35596_gamma_warm13[] = {0x7F, 0x01};
static char nt35596_gamma_warm14[] = {0x80, 0x49};
static char nt35596_gamma_warm15[] = {0x81, 0x01};
static char nt35596_gamma_warm16[] = {0x82, 0x4F};
static char nt35596_gamma_warm17[] = {0x83, 0x01};
static char nt35596_gamma_warm18[] = {0x84, 0x55};
static char nt35596_gamma_warm19[] = {0x85, 0x01};
static char nt35596_gamma_warm20[] = {0x86, 0x5B};
static char nt35596_gamma_warm21[] = {0x87, 0x01};
static char nt35596_gamma_warm22[] = {0x88, 0x70};
static char nt35596_gamma_warm23[] = {0x89, 0x01};
static char nt35596_gamma_warm24[] = {0x8A, 0x84};
static char nt35596_gamma_warm25[] = {0x8B, 0x01};
static char nt35596_gamma_warm26[] = {0x8C, 0xA9};
static char nt35596_gamma_warm27[] = {0x8D, 0x01};
static char nt35596_gamma_warm28[] = {0x8E, 0xC9};
static char nt35596_gamma_warm29[] = {0x8F, 0x02};
static char nt35596_gamma_warm30[] = {0x90, 0x00};
static char nt35596_gamma_warm31[] = {0x91, 0x02};
static char nt35596_gamma_warm32[] = {0x92, 0x30};
static char nt35596_gamma_warm33[] = {0x93, 0x02};
static char nt35596_gamma_warm34[] = {0x94, 0x31};
static char nt35596_gamma_warm35[] = {0x95, 0x02};
static char nt35596_gamma_warm36[] = {0x96, 0x62};
static char nt35596_gamma_warm37[] = {0x97, 0x02};
static char nt35596_gamma_warm38[] = {0x98, 0x97};
static char nt35596_gamma_warm39[] = {0x99, 0x02};
static char nt35596_gamma_warm40[] = {0x9A, 0xB9};
static char nt35596_gamma_warm41[] = {0x9B, 0x02};
static char nt35596_gamma_warm42[] = {0x9C, 0xED};
static char nt35596_gamma_warm43[] = {0x9D, 0x03};
static char nt35596_gamma_warm44[] = {0x9E, 0x12};
static char nt35596_gamma_warm45[] = {0x9F, 0x03};
static char nt35596_gamma_warm46[] = {0xA0, 0x4F};
static char nt35596_gamma_warm47[] = {0xA2, 0x03};
static char nt35596_gamma_warm48[] = {0xA3, 0x5D};
static char nt35596_gamma_warm49[] = {0xA4, 0x03};
static char nt35596_gamma_warm50[] = {0xA5, 0x6B};
static char nt35596_gamma_warm51[] = {0xA6, 0x03};
static char nt35596_gamma_warm52[] = {0xA7, 0x7A};
static char nt35596_gamma_warm53[] = {0xA9, 0x03};
static char nt35596_gamma_warm54[] = {0xAA, 0x8B};
static char nt35596_gamma_warm55[] = {0xAB, 0x03};
static char nt35596_gamma_warm56[] = {0xAC, 0x9B};
static char nt35596_gamma_warm57[] = {0xAD, 0x03};
static char nt35596_gamma_warm58[] = {0xAE, 0xAB};
static char nt35596_gamma_warm59[] = {0xAF, 0x03};
static char nt35596_gamma_warm60[] = {0xB0, 0xB8};
static char nt35596_gamma_warm61[] = {0xB1, 0x03};
static char nt35596_gamma_warm62[] = {0xB2, 0xCB};
static char nt35596_gamma_warm63[] = {0xB3, 0x01};
static char nt35596_gamma_warm64[] = {0xB4, 0x2D};
static char nt35596_gamma_warm65[] = {0xB5, 0x01};
static char nt35596_gamma_warm66[] = {0xB6, 0x31};
static char nt35596_gamma_warm67[] = {0xB7, 0x01};
static char nt35596_gamma_warm68[] = {0xB8, 0x36};
static char nt35596_gamma_warm69[] = {0xB9, 0x01};
static char nt35596_gamma_warm70[] = {0xBA, 0x3D};
static char nt35596_gamma_warm71[] = {0xBB, 0x01};
static char nt35596_gamma_warm72[] = {0xBC, 0x43};
static char nt35596_gamma_warm73[] = {0xBD, 0x01};
static char nt35596_gamma_warm74[] = {0xBE, 0x49};
static char nt35596_gamma_warm75[] = {0xBF, 0x01};
static char nt35596_gamma_warm76[] = {0xC0, 0x4F};
static char nt35596_gamma_warm77[] = {0xC1, 0x01};
static char nt35596_gamma_warm78[] = {0xC2, 0x55};
static char nt35596_gamma_warm79[] = {0xC3, 0x01};
static char nt35596_gamma_warm80[] = {0xC4, 0x5B};
static char nt35596_gamma_warm81[] = {0xC5, 0x01};
static char nt35596_gamma_warm82[] = {0xC6, 0x70};
static char nt35596_gamma_warm83[] = {0xC7, 0x01};
static char nt35596_gamma_warm84[] = {0xC8, 0x84};
static char nt35596_gamma_warm85[] = {0xC9, 0x01};
static char nt35596_gamma_warm86[] = {0xCA, 0xA9};
static char nt35596_gamma_warm87[] = {0xCB, 0x01};
static char nt35596_gamma_warm88[] = {0xCC, 0xC9};
static char nt35596_gamma_warm89[] = {0xCD, 0x02};
static char nt35596_gamma_warm90[] = {0xCE, 0x00};
static char nt35596_gamma_warm91[] = {0xCF, 0x02};
static char nt35596_gamma_warm92[] = {0xD0, 0x30};
static char nt35596_gamma_warm93[] = {0xD1, 0x02};
static char nt35596_gamma_warm94[] = {0xD2, 0x31};
static char nt35596_gamma_warm95[] = {0xD3, 0x02};
static char nt35596_gamma_warm96[] = {0xD4, 0x62};
static char nt35596_gamma_warm97[] = {0xD5, 0x02};
static char nt35596_gamma_warm98[] = {0xD6, 0x97};
static char nt35596_gamma_warm99[] = {0xD7, 0x02};
static char nt35596_gamma_warm100[] = {0xD8, 0xB9};
static char nt35596_gamma_warm101[] = {0xD9, 0x02};
static char nt35596_gamma_warm102[] = {0xDA, 0xED};
static char nt35596_gamma_warm103[] = {0xDB, 0x03};
static char nt35596_gamma_warm104[] = {0xDC, 0x12};
static char nt35596_gamma_warm105[] = {0xDD, 0x03};
static char nt35596_gamma_warm106[] = {0xDE, 0x4F};
static char nt35596_gamma_warm107[] = {0xDF, 0x03};
static char nt35596_gamma_warm108[] = {0xE0, 0x5D};
static char nt35596_gamma_warm109[] = {0xE1, 0x03};
static char nt35596_gamma_warm110[] = {0xE2, 0x6B};
static char nt35596_gamma_warm111[] = {0xE3, 0x03};
static char nt35596_gamma_warm112[] = {0xE4, 0x7A};
static char nt35596_gamma_warm113[] = {0xE5, 0x03};
static char nt35596_gamma_warm114[] = {0xE6, 0x8B};
static char nt35596_gamma_warm115[] = {0xE7, 0x03};
static char nt35596_gamma_warm116[] = {0xE8, 0x9B};
static char nt35596_gamma_warm117[] = {0xE9, 0x03};
static char nt35596_gamma_warm118[] = {0xEA, 0xAB};
static char nt35596_gamma_warm119[] = {0xEB, 0x03};
static char nt35596_gamma_warm120[] = {0xEC, 0xB8};
static char nt35596_gamma_warm121[] = {0xED, 0x03};
static char nt35596_gamma_warm122[] = {0xEE, 0xCB};
static char nt35596_gamma_warm123[] = {0xEF, 0x00};
static char nt35596_gamma_warm124[] = {0xF0, 0xE2};
static char nt35596_gamma_warm125[] = {0xF1, 0x00};
static char nt35596_gamma_warm126[] = {0xF2, 0xE8};
static char nt35596_gamma_warm127[] = {0xF3, 0x00};
static char nt35596_gamma_warm128[] = {0xF4, 0xF0};
static char nt35596_gamma_warm129[] = {0xF5, 0x00};
static char nt35596_gamma_warm130[] = {0xF6, 0xF9};
static char nt35596_gamma_warm131[] = {0xF7, 0x01};
static char nt35596_gamma_warm132[] = {0xF8, 0x01};
static char nt35596_gamma_warm133[] = {0xF9, 0x01};
static char nt35596_gamma_warm134[] = {0xFA, 0x0A};
static char nt35596_gamma_warm135[] = {0xFF, 0x02};
static char nt35596_gamma_warm136[] = {0xFB, 0x01};
static char nt35596_gamma_warm137[] = {0x00, 0x01};
static char nt35596_gamma_warm138[] = {0x01, 0x12};
static char nt35596_gamma_warm139[] = {0x02, 0x01};
static char nt35596_gamma_warm140[] = {0x03, 0x1A};
static char nt35596_gamma_warm141[] = {0x04, 0x01};
static char nt35596_gamma_warm142[] = {0x05, 0x22};
static char nt35596_gamma_warm143[] = {0x06, 0x01};
static char nt35596_gamma_warm144[] = {0x07, 0x3E};
static char nt35596_gamma_warm145[] = {0x08, 0x01};
static char nt35596_gamma_warm146[] = {0x09, 0x58};
static char nt35596_gamma_warm147[] = {0x0A, 0x01};
static char nt35596_gamma_warm148[] = {0x0B, 0x85};
static char nt35596_gamma_warm149[] = {0x0C, 0x01};
static char nt35596_gamma_warm150[] = {0x0D, 0xAC};
static char nt35596_gamma_warm151[] = {0x0E, 0x01};
static char nt35596_gamma_warm152[] = {0x0F, 0xEC};
static char nt35596_gamma_warm153[] = {0x10, 0x02};
static char nt35596_gamma_warm154[] = {0x11, 0x21};
static char nt35596_gamma_warm155[] = {0x12, 0x02};
static char nt35596_gamma_warm156[] = {0x13, 0x22};
static char nt35596_gamma_warm157[] = {0x14, 0x02};
static char nt35596_gamma_warm158[] = {0x15, 0x54};
static char nt35596_gamma_warm159[] = {0x16, 0x02};
static char nt35596_gamma_warm160[] = {0x17, 0x8A};
static char nt35596_gamma_warm161[] = {0x18, 0x02};
static char nt35596_gamma_warm162[] = {0x19, 0xAE};
static char nt35596_gamma_warm163[] = {0x1A, 0x02};
static char nt35596_gamma_warm164[] = {0x1B, 0xDE};
static char nt35596_gamma_warm165[] = {0x1C, 0x02};
static char nt35596_gamma_warm166[] = {0x1D, 0xFF};
static char nt35596_gamma_warm167[] = {0x1E, 0x03};
static char nt35596_gamma_warm168[] = {0x1F, 0x2A};
static char nt35596_gamma_warm169[] = {0x20, 0x03};
static char nt35596_gamma_warm170[] = {0x21, 0x37};
static char nt35596_gamma_warm171[] = {0x22, 0x03};
static char nt35596_gamma_warm172[] = {0x23, 0x45};
static char nt35596_gamma_warm173[] = {0x24, 0x03};
static char nt35596_gamma_warm174[] = {0x25, 0x54};
static char nt35596_gamma_warm175[] = {0x26, 0x03};
static char nt35596_gamma_warm176[] = {0x27, 0x64};
static char nt35596_gamma_warm177[] = {0x28, 0x03};
static char nt35596_gamma_warm178[] = {0x29, 0x76};
static char nt35596_gamma_warm179[] = {0x2A, 0x03};
static char nt35596_gamma_warm180[] = {0x2B, 0x86};
static char nt35596_gamma_warm181[] = {0x2D, 0x03};
static char nt35596_gamma_warm182[] = {0x2F, 0x8F};
static char nt35596_gamma_warm183[] = {0x30, 0x03};
static char nt35596_gamma_warm184[] = {0x31, 0xCB};
static char nt35596_gamma_warm185[] = {0x32, 0x00};
static char nt35596_gamma_warm186[] = {0x33, 0xE2};
static char nt35596_gamma_warm187[] = {0x34, 0x00};
static char nt35596_gamma_warm188[] = {0x35, 0xE8};
static char nt35596_gamma_warm189[] = {0x36, 0x00};
static char nt35596_gamma_warm190[] = {0x37, 0xF0};
static char nt35596_gamma_warm191[] = {0x38, 0x00};
static char nt35596_gamma_warm192[] = {0x39, 0xF9};
static char nt35596_gamma_warm193[] = {0x3A, 0x01};
static char nt35596_gamma_warm194[] = {0x3B, 0x01};
static char nt35596_gamma_warm195[] = {0x3D, 0x01};
static char nt35596_gamma_warm196[] = {0x3F, 0x0A};
static char nt35596_gamma_warm197[] = {0x40, 0x01};
static char nt35596_gamma_warm198[] = {0x41, 0x12};
static char nt35596_gamma_warm199[] = {0x42, 0x01};
static char nt35596_gamma_warm200[] = {0x43, 0x1A};
static char nt35596_gamma_warm201[] = {0x44, 0x01};
static char nt35596_gamma_warm202[] = {0x45, 0x22};
static char nt35596_gamma_warm203[] = {0x46, 0x01};
static char nt35596_gamma_warm204[] = {0x47, 0x3E};
static char nt35596_gamma_warm205[] = {0x48, 0x01};
static char nt35596_gamma_warm206[] = {0x49, 0x58};
static char nt35596_gamma_warm207[] = {0x4A, 0x01};
static char nt35596_gamma_warm208[] = {0x4B, 0x85};
static char nt35596_gamma_warm209[] = {0x4C, 0x01};
static char nt35596_gamma_warm210[] = {0x4D, 0xAC};
static char nt35596_gamma_warm211[] = {0x4E, 0x01};
static char nt35596_gamma_warm212[] = {0x4F, 0xEC};
static char nt35596_gamma_warm213[] = {0x50, 0x02};
static char nt35596_gamma_warm214[] = {0x51, 0x21};
static char nt35596_gamma_warm215[] = {0x52, 0x02};
static char nt35596_gamma_warm216[] = {0x53, 0x22};
static char nt35596_gamma_warm217[] = {0x54, 0x02};
static char nt35596_gamma_warm218[] = {0x55, 0x54};
static char nt35596_gamma_warm219[] = {0x56, 0x02};
static char nt35596_gamma_warm220[] = {0x58, 0x8A};
static char nt35596_gamma_warm221[] = {0x59, 0x02};
static char nt35596_gamma_warm222[] = {0x5A, 0xAE};
static char nt35596_gamma_warm223[] = {0x5B, 0x02};
static char nt35596_gamma_warm224[] = {0x5C, 0xDE};
static char nt35596_gamma_warm225[] = {0x5D, 0x02};
static char nt35596_gamma_warm226[] = {0x5E, 0xFF};
static char nt35596_gamma_warm227[] = {0x5F, 0x03};
static char nt35596_gamma_warm228[] = {0x60, 0x2A};
static char nt35596_gamma_warm229[] = {0x61, 0x03};
static char nt35596_gamma_warm230[] = {0x62, 0x37};
static char nt35596_gamma_warm231[] = {0x63, 0x03};
static char nt35596_gamma_warm232[] = {0x64, 0x45};
static char nt35596_gamma_warm233[] = {0x65, 0x03};
static char nt35596_gamma_warm234[] = {0x66, 0x54};
static char nt35596_gamma_warm235[] = {0x67, 0x03};
static char nt35596_gamma_warm236[] = {0x68, 0x64};
static char nt35596_gamma_warm237[] = {0x69, 0x03};
static char nt35596_gamma_warm238[] = {0x6A, 0x76};
static char nt35596_gamma_warm239[] = {0x6B, 0x03};
static char nt35596_gamma_warm240[] = {0x6C, 0x86};
static char nt35596_gamma_warm241[] = {0x6D, 0x03};
static char nt35596_gamma_warm242[] = {0x6E, 0x8F};
static char nt35596_gamma_warm243[] = {0x6F, 0x03};
static char nt35596_gamma_warm244[] = {0x70, 0xCB};
static char nt35596_gamma_warm245[] = {0x71, 0x00};
static char nt35596_gamma_warm246[] = {0x72, 0x00};
static char nt35596_gamma_warm247[] = {0x73, 0x00};
static char nt35596_gamma_warm248[] = {0x74, 0x0A};
static char nt35596_gamma_warm249[] = {0x75, 0x00};
static char nt35596_gamma_warm250[] = {0x76, 0x2A};
static char nt35596_gamma_warm251[] = {0x77, 0x00};
static char nt35596_gamma_warm252[] = {0x78, 0x41};
static char nt35596_gamma_warm253[] = {0x79, 0x00};
static char nt35596_gamma_warm254[] = {0x7A, 0x56};
static char nt35596_gamma_warm255[] = {0x7B, 0x00};
static char nt35596_gamma_warm256[] = {0x7C, 0x69};
static char nt35596_gamma_warm257[] = {0x7D, 0x00};
static char nt35596_gamma_warm258[] = {0x7E, 0x7A};
static char nt35596_gamma_warm259[] = {0x7F, 0x00};
static char nt35596_gamma_warm260[] = {0x80, 0x8A};
static char nt35596_gamma_warm261[] = {0x81, 0x00};
static char nt35596_gamma_warm262[] = {0x82, 0x98};
static char nt35596_gamma_warm263[] = {0x83, 0x00};
static char nt35596_gamma_warm264[] = {0x84, 0xCB};
static char nt35596_gamma_warm265[] = {0x85, 0x00};
static char nt35596_gamma_warm266[] = {0x86, 0xF5};
static char nt35596_gamma_warm267[] = {0x87, 0x01};
static char nt35596_gamma_warm268[] = {0x88, 0x38};
static char nt35596_gamma_warm269[] = {0x89, 0x01};
static char nt35596_gamma_warm270[] = {0x8A, 0x6F};
static char nt35596_gamma_warm271[] = {0x8B, 0x01};
static char nt35596_gamma_warm272[] = {0x8C, 0xC6};
static char nt35596_gamma_warm273[] = {0x8D, 0x02};
static char nt35596_gamma_warm274[] = {0x8E, 0x07};
static char nt35596_gamma_warm275[] = {0x8F, 0x02};
static char nt35596_gamma_warm276[] = {0x90, 0x08};
static char nt35596_gamma_warm277[] = {0x91, 0x02};
static char nt35596_gamma_warm278[] = {0x92, 0x43};
static char nt35596_gamma_warm279[] = {0x93, 0x02};
static char nt35596_gamma_warm280[] = {0x94, 0x7E};
static char nt35596_gamma_warm281[] = {0x95, 0x02};
static char nt35596_gamma_warm282[] = {0x96, 0xA3};
static char nt35596_gamma_warm283[] = {0x97, 0x02};
static char nt35596_gamma_warm284[] = {0x98, 0xD7};
static char nt35596_gamma_warm285[] = {0x99, 0x02};
static char nt35596_gamma_warm286[] = {0x9A, 0xFE};
static char nt35596_gamma_warm287[] = {0x9B, 0x03};
static char nt35596_gamma_warm288[] = {0x9C, 0x3D};
static char nt35596_gamma_warm289[] = {0x9D, 0x03};
static char nt35596_gamma_warm290[] = {0x9E, 0x59};
static char nt35596_gamma_warm291[] = {0x9F, 0x03};
static char nt35596_gamma_warm292[] = {0xA0, 0x85};
static char nt35596_gamma_warm293[] = {0xA2, 0x03};
static char nt35596_gamma_warm294[] = {0xA3, 0xA1};
static char nt35596_gamma_warm295[] = {0xA4, 0x03};
static char nt35596_gamma_warm296[] = {0xA5, 0xBF};
static char nt35596_gamma_warm297[] = {0xA6, 0x03};
static char nt35596_gamma_warm298[] = {0xA7, 0xC7};
static char nt35596_gamma_warm299[] = {0xA9, 0x03};
static char nt35596_gamma_warm300[] = {0xAA, 0xC9};
static char nt35596_gamma_warm301[] = {0xAB, 0x03};
static char nt35596_gamma_warm302[] = {0xAC, 0xCA};
static char nt35596_gamma_warm303[] = {0xAD, 0x03};
static char nt35596_gamma_warm304[] = {0xAE, 0xCB};
static char nt35596_gamma_warm305[] = {0xAF, 0x00};
static char nt35596_gamma_warm306[] = {0xB0, 0x00};
static char nt35596_gamma_warm307[] = {0xB1, 0x00};
static char nt35596_gamma_warm308[] = {0xB2, 0x0A};
static char nt35596_gamma_warm309[] = {0xB3, 0x00};
static char nt35596_gamma_warm310[] = {0xB4, 0x2A};
static char nt35596_gamma_warm311[] = {0xB5, 0x00};
static char nt35596_gamma_warm312[] = {0xB6, 0x41};
static char nt35596_gamma_warm313[] = {0xB7, 0x00};
static char nt35596_gamma_warm314[] = {0xB8, 0x56};
static char nt35596_gamma_warm315[] = {0xB9, 0x00};
static char nt35596_gamma_warm316[] = {0xBA, 0x69};
static char nt35596_gamma_warm317[] = {0xBB, 0x00};
static char nt35596_gamma_warm318[] = {0xBC, 0x7A};
static char nt35596_gamma_warm319[] = {0xBD, 0x00};
static char nt35596_gamma_warm320[] = {0xBE, 0x8A};
static char nt35596_gamma_warm321[] = {0xBF, 0x00};
static char nt35596_gamma_warm322[] = {0xC0, 0x98};
static char nt35596_gamma_warm323[] = {0xC1, 0x00};
static char nt35596_gamma_warm324[] = {0xC2, 0xCB};
static char nt35596_gamma_warm325[] = {0xC3, 0x00};
static char nt35596_gamma_warm326[] = {0xC4, 0xF5};
static char nt35596_gamma_warm327[] = {0xC5, 0x01};
static char nt35596_gamma_warm328[] = {0xC6, 0x38};
static char nt35596_gamma_warm329[] = {0xC7, 0x01};
static char nt35596_gamma_warm330[] = {0xC8, 0x6F};
static char nt35596_gamma_warm331[] = {0xC9, 0x01};
static char nt35596_gamma_warm332[] = {0xCA, 0xC6};
static char nt35596_gamma_warm333[] = {0xCB, 0x02};
static char nt35596_gamma_warm334[] = {0xCC, 0x07};
static char nt35596_gamma_warm335[] = {0xCD, 0x02};
static char nt35596_gamma_warm336[] = {0xCE, 0x08};
static char nt35596_gamma_warm337[] = {0xCF, 0x02};
static char nt35596_gamma_warm338[] = {0xD0, 0x43};
static char nt35596_gamma_warm339[] = {0xD1, 0x02};
static char nt35596_gamma_warm340[] = {0xD2, 0x7E};
static char nt35596_gamma_warm341[] = {0xD3, 0x02};
static char nt35596_gamma_warm342[] = {0xD4, 0xA3};
static char nt35596_gamma_warm343[] = {0xD5, 0x02};
static char nt35596_gamma_warm344[] = {0xD6, 0xD7};
static char nt35596_gamma_warm345[] = {0xD7, 0x02};
static char nt35596_gamma_warm346[] = {0xD8, 0xFE};
static char nt35596_gamma_warm347[] = {0xD9, 0x03};
static char nt35596_gamma_warm348[] = {0xDA, 0x3D};
static char nt35596_gamma_warm349[] = {0xDB, 0x03};
static char nt35596_gamma_warm350[] = {0xDC, 0x59};
static char nt35596_gamma_warm351[] = {0xDD, 0x03};
static char nt35596_gamma_warm352[] = {0xDE, 0x85};
static char nt35596_gamma_warm353[] = {0xDF, 0x03};
static char nt35596_gamma_warm354[] = {0xE0, 0xA1};
static char nt35596_gamma_warm355[] = {0xE1, 0x03};
static char nt35596_gamma_warm356[] = {0xE2, 0xBF};
static char nt35596_gamma_warm357[] = {0xE3, 0x03};
static char nt35596_gamma_warm358[] = {0xE4, 0xC7};
static char nt35596_gamma_warm359[] = {0xE5, 0x03};
static char nt35596_gamma_warm360[] = {0xE6, 0xC9};
static char nt35596_gamma_warm361[] = {0xE7, 0x03};
static char nt35596_gamma_warm362[] = {0xE8, 0xCA};
static char nt35596_gamma_warm363[] = {0xE9, 0x03};
static char nt35596_gamma_warm364[] = {0xEA, 0xCB};

static struct dsi_cmd_desc dsi_nt35596_gamma_warm[] = {
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm1)}, nt35596_gamma_warm1},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm2)}, nt35596_gamma_warm2},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm3)}, nt35596_gamma_warm3},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm4)}, nt35596_gamma_warm4},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm5)}, nt35596_gamma_warm5},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm6)}, nt35596_gamma_warm6},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm7)}, nt35596_gamma_warm7},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm8)}, nt35596_gamma_warm8},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm9)}, nt35596_gamma_warm9},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm10)}, nt35596_gamma_warm10},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm11)}, nt35596_gamma_warm11},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm12)}, nt35596_gamma_warm12},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm13)}, nt35596_gamma_warm13},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm14)}, nt35596_gamma_warm14},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm15)}, nt35596_gamma_warm15},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm16)}, nt35596_gamma_warm16},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm17)}, nt35596_gamma_warm17},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm18)}, nt35596_gamma_warm18},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm19)}, nt35596_gamma_warm19},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm20)}, nt35596_gamma_warm20},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm21)}, nt35596_gamma_warm21},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm22)}, nt35596_gamma_warm22},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm23)}, nt35596_gamma_warm23},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm24)}, nt35596_gamma_warm24},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm25)}, nt35596_gamma_warm25},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm26)}, nt35596_gamma_warm26},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm27)}, nt35596_gamma_warm27},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm28)}, nt35596_gamma_warm28},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm29)}, nt35596_gamma_warm29},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm30)}, nt35596_gamma_warm30},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm31)}, nt35596_gamma_warm31},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm32)}, nt35596_gamma_warm32},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm33)}, nt35596_gamma_warm33},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm34)}, nt35596_gamma_warm34},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm35)}, nt35596_gamma_warm35},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm36)}, nt35596_gamma_warm36},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm37)}, nt35596_gamma_warm37},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm38)}, nt35596_gamma_warm38},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm39)}, nt35596_gamma_warm39},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm40)}, nt35596_gamma_warm40},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm41)}, nt35596_gamma_warm41},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm42)}, nt35596_gamma_warm42},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm43)}, nt35596_gamma_warm43},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm44)}, nt35596_gamma_warm44},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm45)}, nt35596_gamma_warm45},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm46)}, nt35596_gamma_warm46},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm47)}, nt35596_gamma_warm47},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm48)}, nt35596_gamma_warm48},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm49)}, nt35596_gamma_warm49},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm50)}, nt35596_gamma_warm50},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm51)}, nt35596_gamma_warm51},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm52)}, nt35596_gamma_warm52},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm53)}, nt35596_gamma_warm53},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm54)}, nt35596_gamma_warm54},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm55)}, nt35596_gamma_warm55},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm56)}, nt35596_gamma_warm56},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm57)}, nt35596_gamma_warm57},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm58)}, nt35596_gamma_warm58},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm59)}, nt35596_gamma_warm59},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm60)}, nt35596_gamma_warm60},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm61)}, nt35596_gamma_warm61},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm62)}, nt35596_gamma_warm62},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm63)}, nt35596_gamma_warm63},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm64)}, nt35596_gamma_warm64},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm65)}, nt35596_gamma_warm65},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm66)}, nt35596_gamma_warm66},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm67)}, nt35596_gamma_warm67},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm68)}, nt35596_gamma_warm68},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm69)}, nt35596_gamma_warm69},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm70)}, nt35596_gamma_warm70},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm71)}, nt35596_gamma_warm71},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm72)}, nt35596_gamma_warm72},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm73)}, nt35596_gamma_warm73},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm74)}, nt35596_gamma_warm74},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm75)}, nt35596_gamma_warm75},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm76)}, nt35596_gamma_warm76},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm77)}, nt35596_gamma_warm77},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm78)}, nt35596_gamma_warm78},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm79)}, nt35596_gamma_warm79},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm80)}, nt35596_gamma_warm80},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm81)}, nt35596_gamma_warm81},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm82)}, nt35596_gamma_warm82},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm83)}, nt35596_gamma_warm83},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm84)}, nt35596_gamma_warm84},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm85)}, nt35596_gamma_warm85},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm86)}, nt35596_gamma_warm86},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm87)}, nt35596_gamma_warm87},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm88)}, nt35596_gamma_warm88},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm89)}, nt35596_gamma_warm89},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm90)}, nt35596_gamma_warm90},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm91)}, nt35596_gamma_warm91},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm92)}, nt35596_gamma_warm92},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm93)}, nt35596_gamma_warm93},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm94)}, nt35596_gamma_warm94},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm95)}, nt35596_gamma_warm95},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm96)}, nt35596_gamma_warm96},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm97)}, nt35596_gamma_warm97},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm98)}, nt35596_gamma_warm98},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm99)}, nt35596_gamma_warm99},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm100)}, nt35596_gamma_warm100},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm101)}, nt35596_gamma_warm101},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm102)}, nt35596_gamma_warm102},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm103)}, nt35596_gamma_warm103},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm104)}, nt35596_gamma_warm104},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm105)}, nt35596_gamma_warm105},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm106)}, nt35596_gamma_warm106},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm107)}, nt35596_gamma_warm107},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm108)}, nt35596_gamma_warm108},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm109)}, nt35596_gamma_warm109},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm110)}, nt35596_gamma_warm110},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm111)}, nt35596_gamma_warm111},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm112)}, nt35596_gamma_warm112},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm113)}, nt35596_gamma_warm113},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm114)}, nt35596_gamma_warm114},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm115)}, nt35596_gamma_warm115},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm116)}, nt35596_gamma_warm116},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm117)}, nt35596_gamma_warm117},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm118)}, nt35596_gamma_warm118},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm119)}, nt35596_gamma_warm119},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm120)}, nt35596_gamma_warm120},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm121)}, nt35596_gamma_warm121},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm122)}, nt35596_gamma_warm122},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm123)}, nt35596_gamma_warm123},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm124)}, nt35596_gamma_warm124},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm125)}, nt35596_gamma_warm125},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm126)}, nt35596_gamma_warm126},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm127)}, nt35596_gamma_warm127},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm128)}, nt35596_gamma_warm128},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm129)}, nt35596_gamma_warm129},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm130)}, nt35596_gamma_warm130},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm131)}, nt35596_gamma_warm131},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm132)}, nt35596_gamma_warm132},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm133)}, nt35596_gamma_warm133},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm134)}, nt35596_gamma_warm134},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm135)}, nt35596_gamma_warm135},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm136)}, nt35596_gamma_warm136},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm137)}, nt35596_gamma_warm137},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm138)}, nt35596_gamma_warm138},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm139)}, nt35596_gamma_warm139},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm140)}, nt35596_gamma_warm140},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm141)}, nt35596_gamma_warm141},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm142)}, nt35596_gamma_warm142},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm143)}, nt35596_gamma_warm143},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm144)}, nt35596_gamma_warm144},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm145)}, nt35596_gamma_warm145},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm146)}, nt35596_gamma_warm146},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm147)}, nt35596_gamma_warm147},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm148)}, nt35596_gamma_warm148},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm149)}, nt35596_gamma_warm149},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm150)}, nt35596_gamma_warm150},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm151)}, nt35596_gamma_warm151},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm152)}, nt35596_gamma_warm152},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm153)}, nt35596_gamma_warm153},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm154)}, nt35596_gamma_warm154},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm155)}, nt35596_gamma_warm155},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm156)}, nt35596_gamma_warm156},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm157)}, nt35596_gamma_warm157},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm158)}, nt35596_gamma_warm158},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm159)}, nt35596_gamma_warm159},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm160)}, nt35596_gamma_warm160},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm161)}, nt35596_gamma_warm161},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm162)}, nt35596_gamma_warm162},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm163)}, nt35596_gamma_warm163},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm164)}, nt35596_gamma_warm164},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm165)}, nt35596_gamma_warm165},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm166)}, nt35596_gamma_warm166},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm167)}, nt35596_gamma_warm167},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm168)}, nt35596_gamma_warm168},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm169)}, nt35596_gamma_warm169},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm170)}, nt35596_gamma_warm170},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm171)}, nt35596_gamma_warm171},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm172)}, nt35596_gamma_warm172},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm173)}, nt35596_gamma_warm173},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm174)}, nt35596_gamma_warm174},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm175)}, nt35596_gamma_warm175},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm176)}, nt35596_gamma_warm176},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm177)}, nt35596_gamma_warm177},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm178)}, nt35596_gamma_warm178},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm179)}, nt35596_gamma_warm179},
{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_gamma_warm180)}, nt35596_gamma_warm180},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm181)}, nt35596_gamma_warm181},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm182)}, nt35596_gamma_warm182},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm183)}, nt35596_gamma_warm183},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm184)}, nt35596_gamma_warm184},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm185)}, nt35596_gamma_warm185},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm186)}, nt35596_gamma_warm186},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm187)}, nt35596_gamma_warm187},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm188)}, nt35596_gamma_warm188},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm189)}, nt35596_gamma_warm189},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm190)}, nt35596_gamma_warm190},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm191)}, nt35596_gamma_warm191},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm192)}, nt35596_gamma_warm192},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm193)}, nt35596_gamma_warm193},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm194)}, nt35596_gamma_warm194},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm195)}, nt35596_gamma_warm195},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm196)}, nt35596_gamma_warm196},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm197)}, nt35596_gamma_warm197},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm198)}, nt35596_gamma_warm198},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm199)}, nt35596_gamma_warm199},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm200)}, nt35596_gamma_warm200},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm201)}, nt35596_gamma_warm201},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm202)}, nt35596_gamma_warm202},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm203)}, nt35596_gamma_warm203},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm204)}, nt35596_gamma_warm204},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm205)}, nt35596_gamma_warm205},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm206)}, nt35596_gamma_warm206},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm207)}, nt35596_gamma_warm207},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm208)}, nt35596_gamma_warm208},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm209)}, nt35596_gamma_warm209},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm210)}, nt35596_gamma_warm210},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm211)}, nt35596_gamma_warm211},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm212)}, nt35596_gamma_warm212},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm213)}, nt35596_gamma_warm213},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm214)}, nt35596_gamma_warm214},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm215)}, nt35596_gamma_warm215},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm216)}, nt35596_gamma_warm216},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm217)}, nt35596_gamma_warm217},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm218)}, nt35596_gamma_warm218},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm219)}, nt35596_gamma_warm219},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm220)}, nt35596_gamma_warm220},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm221)}, nt35596_gamma_warm221},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm222)}, nt35596_gamma_warm222},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm223)}, nt35596_gamma_warm223},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm224)}, nt35596_gamma_warm224},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm225)}, nt35596_gamma_warm225},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm226)}, nt35596_gamma_warm226},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm227)}, nt35596_gamma_warm227},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm228)}, nt35596_gamma_warm228},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm229)}, nt35596_gamma_warm229},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm230)}, nt35596_gamma_warm230},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm231)}, nt35596_gamma_warm231},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm232)}, nt35596_gamma_warm232},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm233)}, nt35596_gamma_warm233},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm234)}, nt35596_gamma_warm234},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm235)}, nt35596_gamma_warm235},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm236)}, nt35596_gamma_warm236},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm237)}, nt35596_gamma_warm237},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm238)}, nt35596_gamma_warm238},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm239)}, nt35596_gamma_warm239},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm240)}, nt35596_gamma_warm240},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm241)}, nt35596_gamma_warm241},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm242)}, nt35596_gamma_warm242},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm243)}, nt35596_gamma_warm243},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm244)}, nt35596_gamma_warm244},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm245)}, nt35596_gamma_warm245},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm246)}, nt35596_gamma_warm246},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm247)}, nt35596_gamma_warm247},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm248)}, nt35596_gamma_warm248},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm249)}, nt35596_gamma_warm249},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm250)}, nt35596_gamma_warm250},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm251)}, nt35596_gamma_warm251},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm252)}, nt35596_gamma_warm252},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm253)}, nt35596_gamma_warm253},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm254)}, nt35596_gamma_warm254},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm255)}, nt35596_gamma_warm255},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm256)}, nt35596_gamma_warm256},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm257)}, nt35596_gamma_warm257},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm258)}, nt35596_gamma_warm258},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm259)}, nt35596_gamma_warm259},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm260)}, nt35596_gamma_warm260},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm261)}, nt35596_gamma_warm261},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm262)}, nt35596_gamma_warm262},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm263)}, nt35596_gamma_warm263},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm264)}, nt35596_gamma_warm264},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm265)}, nt35596_gamma_warm265},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm266)}, nt35596_gamma_warm266},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm267)}, nt35596_gamma_warm267},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm268)}, nt35596_gamma_warm268},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm269)}, nt35596_gamma_warm269},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm270)}, nt35596_gamma_warm270},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm271)}, nt35596_gamma_warm271},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm272)}, nt35596_gamma_warm272},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm273)}, nt35596_gamma_warm273},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm274)}, nt35596_gamma_warm274},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm275)}, nt35596_gamma_warm275},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm276)}, nt35596_gamma_warm276},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm277)}, nt35596_gamma_warm277},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm278)}, nt35596_gamma_warm278},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm279)}, nt35596_gamma_warm279},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm280)}, nt35596_gamma_warm280},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm281)}, nt35596_gamma_warm281},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm282)}, nt35596_gamma_warm282},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm283)}, nt35596_gamma_warm283},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm284)}, nt35596_gamma_warm284},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm285)}, nt35596_gamma_warm285},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm286)}, nt35596_gamma_warm286},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm287)}, nt35596_gamma_warm287},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm288)}, nt35596_gamma_warm288},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm289)}, nt35596_gamma_warm289},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm290)}, nt35596_gamma_warm290},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm291)}, nt35596_gamma_warm291},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm292)}, nt35596_gamma_warm292},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm293)}, nt35596_gamma_warm293},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm294)}, nt35596_gamma_warm294},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm295)}, nt35596_gamma_warm295},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm296)}, nt35596_gamma_warm296},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm297)}, nt35596_gamma_warm297},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm298)}, nt35596_gamma_warm298},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm299)}, nt35596_gamma_warm299},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm300)}, nt35596_gamma_warm300},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm301)}, nt35596_gamma_warm301},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm302)}, nt35596_gamma_warm302},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm303)}, nt35596_gamma_warm303},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm304)}, nt35596_gamma_warm304},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm305)}, nt35596_gamma_warm305},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm306)}, nt35596_gamma_warm306},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm307)}, nt35596_gamma_warm307},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm308)}, nt35596_gamma_warm308},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm309)}, nt35596_gamma_warm309},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm310)}, nt35596_gamma_warm310},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm311)}, nt35596_gamma_warm311},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm312)}, nt35596_gamma_warm312},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm313)}, nt35596_gamma_warm313},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm314)}, nt35596_gamma_warm314},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm315)}, nt35596_gamma_warm315},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm316)}, nt35596_gamma_warm316},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm317)}, nt35596_gamma_warm317},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm318)}, nt35596_gamma_warm318},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm319)}, nt35596_gamma_warm319},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm320)}, nt35596_gamma_warm320},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm321)}, nt35596_gamma_warm321},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm322)}, nt35596_gamma_warm322},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm323)}, nt35596_gamma_warm323},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm324)}, nt35596_gamma_warm324},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm325)}, nt35596_gamma_warm325},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm326)}, nt35596_gamma_warm326},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm327)}, nt35596_gamma_warm327},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm328)}, nt35596_gamma_warm328},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm329)}, nt35596_gamma_warm329},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm330)}, nt35596_gamma_warm330},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm331)}, nt35596_gamma_warm331},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm332)}, nt35596_gamma_warm332},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm333)}, nt35596_gamma_warm333},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm334)}, nt35596_gamma_warm334},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm335)}, nt35596_gamma_warm335},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm336)}, nt35596_gamma_warm336},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm337)}, nt35596_gamma_warm337},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm338)}, nt35596_gamma_warm338},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm339)}, nt35596_gamma_warm339},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm340)}, nt35596_gamma_warm340},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm341)}, nt35596_gamma_warm341},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm342)}, nt35596_gamma_warm342},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm343)}, nt35596_gamma_warm343},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm344)}, nt35596_gamma_warm344},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm345)}, nt35596_gamma_warm345},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm346)}, nt35596_gamma_warm346},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm347)}, nt35596_gamma_warm347},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm348)}, nt35596_gamma_warm348},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm349)}, nt35596_gamma_warm349},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm350)}, nt35596_gamma_warm350},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm351)}, nt35596_gamma_warm351},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm352)}, nt35596_gamma_warm352},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm353)}, nt35596_gamma_warm353},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm354)}, nt35596_gamma_warm354},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm355)}, nt35596_gamma_warm355},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm356)}, nt35596_gamma_warm356},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm357)}, nt35596_gamma_warm357},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm358)}, nt35596_gamma_warm358},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm359)}, nt35596_gamma_warm359},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm360)}, nt35596_gamma_warm360},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm361)}, nt35596_gamma_warm361},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm362)}, nt35596_gamma_warm362},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm363)}, nt35596_gamma_warm363},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_warm364)}, nt35596_gamma_warm364},
{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};

static char nt35596_gamma_normal1[] = {0xFF, 0x01};
static char nt35596_gamma_normal2[] = {0xFB, 0x01};
static char nt35596_gamma_normal3[] = {0x75, 0x01};
static char nt35596_gamma_normal4[] = {0x76, 0x50};
static char nt35596_gamma_normal5[] = {0x77, 0x01};
static char nt35596_gamma_normal6[] = {0x78, 0x52};
static char nt35596_gamma_normal7[] = {0x79, 0x01};
static char nt35596_gamma_normal8[] = {0x7A, 0x58};
static char nt35596_gamma_normal9[] = {0x7B, 0x01};
static char nt35596_gamma_normal10[] = {0x7C, 0x5D};
static char nt35596_gamma_normal11[] = {0x7D, 0x01};
static char nt35596_gamma_normal12[] = {0x7E, 0x62};
static char nt35596_gamma_normal13[] = {0x7F, 0x01};
static char nt35596_gamma_normal14[] = {0x80, 0x67};
static char nt35596_gamma_normal15[] = {0x81, 0x01};
static char nt35596_gamma_normal16[] = {0x82, 0x6C};
static char nt35596_gamma_normal17[] = {0x83, 0x01};
static char nt35596_gamma_normal18[] = {0x84, 0x71};
static char nt35596_gamma_normal19[] = {0x85, 0x01};
static char nt35596_gamma_normal20[] = {0x86, 0x76};
static char nt35596_gamma_normal21[] = {0x87, 0x01};
static char nt35596_gamma_normal22[] = {0x88, 0x89};
static char nt35596_gamma_normal23[] = {0x89, 0x01};
static char nt35596_gamma_normal24[] = {0x8A, 0x9A};
static char nt35596_gamma_normal25[] = {0x8B, 0x01};
static char nt35596_gamma_normal26[] = {0x8C, 0xBA};
static char nt35596_gamma_normal27[] = {0x8D, 0x01};
static char nt35596_gamma_normal28[] = {0x8E, 0xD7};
static char nt35596_gamma_normal29[] = {0x8F, 0x02};
static char nt35596_gamma_normal30[] = {0x90, 0x0A};
static char nt35596_gamma_normal31[] = {0x91, 0x02};
static char nt35596_gamma_normal32[] = {0x92, 0x3A};
static char nt35596_gamma_normal33[] = {0x93, 0x02};
static char nt35596_gamma_normal34[] = {0x94, 0x3B};
static char nt35596_gamma_normal35[] = {0x95, 0x02};
static char nt35596_gamma_normal36[] = {0x96, 0x68};
static char nt35596_gamma_normal37[] = {0x97, 0x02};
static char nt35596_gamma_normal38[] = {0x98, 0x9C};
static char nt35596_gamma_normal39[] = {0x99, 0x02};
static char nt35596_gamma_normal40[] = {0x9A, 0xBE};
static char nt35596_gamma_normal41[] = {0x9B, 0x02};
static char nt35596_gamma_normal42[] = {0x9C, 0xF0};
static char nt35596_gamma_normal43[] = {0x9D, 0x03};
static char nt35596_gamma_normal44[] = {0x9E, 0x17};
static char nt35596_gamma_normal45[] = {0x9F, 0x03};
static char nt35596_gamma_normal46[] = {0xA0, 0x5E};
static char nt35596_gamma_normal47[] = {0xA2, 0x03};
static char nt35596_gamma_normal48[] = {0xA3, 0x76};
static char nt35596_gamma_normal49[] = {0xA4, 0x03};
static char nt35596_gamma_normal50[] = {0xA5, 0x84};
static char nt35596_gamma_normal51[] = {0xA6, 0x03};
static char nt35596_gamma_normal52[] = {0xA7, 0x94};
static char nt35596_gamma_normal53[] = {0xA9, 0x03};
static char nt35596_gamma_normal54[] = {0xAA, 0xA5};
static char nt35596_gamma_normal55[] = {0xAB, 0x03};
static char nt35596_gamma_normal56[] = {0xAC, 0xB9};
static char nt35596_gamma_normal57[] = {0xAD, 0x03};
static char nt35596_gamma_normal58[] = {0xAE, 0xC1};
static char nt35596_gamma_normal59[] = {0xAF, 0x03};
static char nt35596_gamma_normal60[] = {0xB0, 0xC6};
static char nt35596_gamma_normal61[] = {0xB1, 0x03};
static char nt35596_gamma_normal62[] = {0xB2, 0xCB};
static char nt35596_gamma_normal63[] = {0xB3, 0x01};
static char nt35596_gamma_normal64[] = {0xB4, 0x50};
static char nt35596_gamma_normal65[] = {0xB5, 0x01};
static char nt35596_gamma_normal66[] = {0xB6, 0x52};
static char nt35596_gamma_normal67[] = {0xB7, 0x01};
static char nt35596_gamma_normal68[] = {0xB8, 0x58};
static char nt35596_gamma_normal69[] = {0xB9, 0x01};
static char nt35596_gamma_normal70[] = {0xBA, 0x5D};
static char nt35596_gamma_normal71[] = {0xBB, 0x01};
static char nt35596_gamma_normal72[] = {0xBC, 0x62};
static char nt35596_gamma_normal73[] = {0xBD, 0x01};
static char nt35596_gamma_normal74[] = {0xBE, 0x67};
static char nt35596_gamma_normal75[] = {0xBF, 0x01};
static char nt35596_gamma_normal76[] = {0xC0, 0x6C};
static char nt35596_gamma_normal77[] = {0xC1, 0x01};
static char nt35596_gamma_normal78[] = {0xC2, 0x71};
static char nt35596_gamma_normal79[] = {0xC3, 0x01};
static char nt35596_gamma_normal80[] = {0xC4, 0x76};
static char nt35596_gamma_normal81[] = {0xC5, 0x01};
static char nt35596_gamma_normal82[] = {0xC6, 0x89};
static char nt35596_gamma_normal83[] = {0xC7, 0x01};
static char nt35596_gamma_normal84[] = {0xC8, 0x9A};
static char nt35596_gamma_normal85[] = {0xC9, 0x01};
static char nt35596_gamma_normal86[] = {0xCA, 0xBA};
static char nt35596_gamma_normal87[] = {0xCB, 0x01};
static char nt35596_gamma_normal88[] = {0xCC, 0xD7};
static char nt35596_gamma_normal89[] = {0xCD, 0x02};
static char nt35596_gamma_normal90[] = {0xCE, 0x0A};
static char nt35596_gamma_normal91[] = {0xCF, 0x02};
static char nt35596_gamma_normal92[] = {0xD0, 0x3A};
static char nt35596_gamma_normal93[] = {0xD1, 0x02};
static char nt35596_gamma_normal94[] = {0xD2, 0x3B};
static char nt35596_gamma_normal95[] = {0xD3, 0x02};
static char nt35596_gamma_normal96[] = {0xD4, 0x68};
static char nt35596_gamma_normal97[] = {0xD5, 0x02};
static char nt35596_gamma_normal98[] = {0xD6, 0x9C};
static char nt35596_gamma_normal99[] = {0xD7, 0x02};
static char nt35596_gamma_normal100[] = {0xD8, 0xBE};
static char nt35596_gamma_normal101[] = {0xD9, 0x02};
static char nt35596_gamma_normal102[] = {0xDA, 0xF0};
static char nt35596_gamma_normal103[] = {0xDB, 0x03};
static char nt35596_gamma_normal104[] = {0xDC, 0x17};
static char nt35596_gamma_normal105[] = {0xDD, 0x03};
static char nt35596_gamma_normal106[] = {0xDE, 0x5E};
static char nt35596_gamma_normal107[] = {0xDF, 0x03};
static char nt35596_gamma_normal108[] = {0xE0, 0x76};
static char nt35596_gamma_normal109[] = {0xE1, 0x03};
static char nt35596_gamma_normal110[] = {0xE2, 0x84};
static char nt35596_gamma_normal111[] = {0xE3, 0x03};
static char nt35596_gamma_normal112[] = {0xE4, 0x94};
static char nt35596_gamma_normal113[] = {0xE5, 0x03};
static char nt35596_gamma_normal114[] = {0xE6, 0xA5};
static char nt35596_gamma_normal115[] = {0xE7, 0x03};
static char nt35596_gamma_normal116[] = {0xE8, 0xB9};
static char nt35596_gamma_normal117[] = {0xE9, 0x03};
static char nt35596_gamma_normal118[] = {0xEA, 0xC1};
static char nt35596_gamma_normal119[] = {0xEB, 0x03};
static char nt35596_gamma_normal120[] = {0xEC, 0xC6};
static char nt35596_gamma_normal121[] = {0xED, 0x03};
static char nt35596_gamma_normal122[] = {0xEE, 0xCB};
static char nt35596_gamma_normal123[] = {0xEF, 0x01};
static char nt35596_gamma_normal124[] = {0xF0, 0x00};
static char nt35596_gamma_normal125[] = {0xF1, 0x01};
static char nt35596_gamma_normal126[] = {0xF2, 0x04};
static char nt35596_gamma_normal127[] = {0xF3, 0x01};
static char nt35596_gamma_normal128[] = {0xF4, 0x0C};
static char nt35596_gamma_normal129[] = {0xF5, 0x01};
static char nt35596_gamma_normal130[] = {0xF6, 0x13};
static char nt35596_gamma_normal131[] = {0xF7, 0x01};
static char nt35596_gamma_normal132[] = {0xF8, 0x1B};
static char nt35596_gamma_normal133[] = {0xF9, 0x01};
static char nt35596_gamma_normal134[] = {0xFA, 0x23};
static char nt35596_gamma_normal135[] = {0xFF, 0x02};
static char nt35596_gamma_normal136[] = {0xFB, 0x01};
static char nt35596_gamma_normal137[] = {0x00, 0x01};
static char nt35596_gamma_normal138[] = {0x01, 0x2A};
static char nt35596_gamma_normal139[] = {0x02, 0x01};
static char nt35596_gamma_normal140[] = {0x03, 0x31};
static char nt35596_gamma_normal141[] = {0x04, 0x01};
static char nt35596_gamma_normal142[] = {0x05, 0x37};
static char nt35596_gamma_normal143[] = {0x06, 0x01};
static char nt35596_gamma_normal144[] = {0x07, 0x51};
static char nt35596_gamma_normal145[] = {0x08, 0x01};
static char nt35596_gamma_normal146[] = {0x09, 0x68};
static char nt35596_gamma_normal147[] = {0x0A, 0x01};
static char nt35596_gamma_normal148[] = {0x0B, 0x91};
static char nt35596_gamma_normal149[] = {0x0C, 0x01};
static char nt35596_gamma_normal150[] = {0x0D, 0xB6};
static char nt35596_gamma_normal151[] = {0x0E, 0x01};
static char nt35596_gamma_normal152[] = {0x0F, 0xF2};
static char nt35596_gamma_normal153[] = {0x10, 0x02};
static char nt35596_gamma_normal154[] = {0x11, 0x26};
static char nt35596_gamma_normal155[] = {0x12, 0x02};
static char nt35596_gamma_normal156[] = {0x13, 0x27};
static char nt35596_gamma_normal157[] = {0x14, 0x02};
static char nt35596_gamma_normal158[] = {0x15, 0x57};
static char nt35596_gamma_normal159[] = {0x16, 0x02};
static char nt35596_gamma_normal160[] = {0x17, 0x8D};
static char nt35596_gamma_normal161[] = {0x18, 0x02};
static char nt35596_gamma_normal162[] = {0x19, 0xB0};
static char nt35596_gamma_normal163[] = {0x1A, 0x02};
static char nt35596_gamma_normal164[] = {0x1B, 0xDF};
static char nt35596_gamma_normal165[] = {0x1C, 0x03};
static char nt35596_gamma_normal166[] = {0x1D, 0x00};
static char nt35596_gamma_normal167[] = {0x1E, 0x03};
static char nt35596_gamma_normal168[] = {0x1F, 0x2B};
static char nt35596_gamma_normal169[] = {0x20, 0x03};
static char nt35596_gamma_normal170[] = {0x21, 0x38};
static char nt35596_gamma_normal171[] = {0x22, 0x03};
static char nt35596_gamma_normal172[] = {0x23, 0x46};
static char nt35596_gamma_normal173[] = {0x24, 0x03};
static char nt35596_gamma_normal174[] = {0x25, 0x55};
static char nt35596_gamma_normal175[] = {0x26, 0x03};
static char nt35596_gamma_normal176[] = {0x27, 0x64};
static char nt35596_gamma_normal177[] = {0x28, 0x03};
static char nt35596_gamma_normal178[] = {0x29, 0x75};
static char nt35596_gamma_normal179[] = {0x2A, 0x03};
static char nt35596_gamma_normal180[] = {0x2B, 0x85};
static char nt35596_gamma_normal181[] = {0x2D, 0x03};
static char nt35596_gamma_normal182[] = {0x2F, 0x90};
static char nt35596_gamma_normal183[] = {0x30, 0x03};
static char nt35596_gamma_normal184[] = {0x31, 0xCB};
static char nt35596_gamma_normal185[] = {0x32, 0x01};
static char nt35596_gamma_normal186[] = {0x33, 0x00};
static char nt35596_gamma_normal187[] = {0x34, 0x01};
static char nt35596_gamma_normal188[] = {0x35, 0x04};
static char nt35596_gamma_normal189[] = {0x36, 0x01};
static char nt35596_gamma_normal190[] = {0x37, 0x0C};
static char nt35596_gamma_normal191[] = {0x38, 0x01};
static char nt35596_gamma_normal192[] = {0x39, 0x13};
static char nt35596_gamma_normal193[] = {0x3A, 0x01};
static char nt35596_gamma_normal194[] = {0x3B, 0x1B};
static char nt35596_gamma_normal195[] = {0x3D, 0x01};
static char nt35596_gamma_normal196[] = {0x3F, 0x23};
static char nt35596_gamma_normal197[] = {0x40, 0x01};
static char nt35596_gamma_normal198[] = {0x41, 0x2A};
static char nt35596_gamma_normal199[] = {0x42, 0x01};
static char nt35596_gamma_normal200[] = {0x43, 0x31};
static char nt35596_gamma_normal201[] = {0x44, 0x01};
static char nt35596_gamma_normal202[] = {0x45, 0x37};
static char nt35596_gamma_normal203[] = {0x46, 0x01};
static char nt35596_gamma_normal204[] = {0x47, 0x51};
static char nt35596_gamma_normal205[] = {0x48, 0x01};
static char nt35596_gamma_normal206[] = {0x49, 0x68};
static char nt35596_gamma_normal207[] = {0x4A, 0x01};
static char nt35596_gamma_normal208[] = {0x4B, 0x91};
static char nt35596_gamma_normal209[] = {0x4C, 0x01};
static char nt35596_gamma_normal210[] = {0x4D, 0xB6};
static char nt35596_gamma_normal211[] = {0x4E, 0x01};
static char nt35596_gamma_normal212[] = {0x4F, 0xF2};
static char nt35596_gamma_normal213[] = {0x50, 0x02};
static char nt35596_gamma_normal214[] = {0x51, 0x26};
static char nt35596_gamma_normal215[] = {0x52, 0x02};
static char nt35596_gamma_normal216[] = {0x53, 0x27};
static char nt35596_gamma_normal217[] = {0x54, 0x02};
static char nt35596_gamma_normal218[] = {0x55, 0x57};
static char nt35596_gamma_normal219[] = {0x56, 0x02};
static char nt35596_gamma_normal220[] = {0x58, 0x8D};
static char nt35596_gamma_normal221[] = {0x59, 0x02};
static char nt35596_gamma_normal222[] = {0x5A, 0xB0};
static char nt35596_gamma_normal223[] = {0x5B, 0x02};
static char nt35596_gamma_normal224[] = {0x5C, 0xDF};
static char nt35596_gamma_normal225[] = {0x5D, 0x03};
static char nt35596_gamma_normal226[] = {0x5E, 0x00};
static char nt35596_gamma_normal227[] = {0x5F, 0x03};
static char nt35596_gamma_normal228[] = {0x60, 0x2B};
static char nt35596_gamma_normal229[] = {0x61, 0x03};
static char nt35596_gamma_normal230[] = {0x62, 0x38};
static char nt35596_gamma_normal231[] = {0x63, 0x03};
static char nt35596_gamma_normal232[] = {0x64, 0x46};
static char nt35596_gamma_normal233[] = {0x65, 0x03};
static char nt35596_gamma_normal234[] = {0x66, 0x55};
static char nt35596_gamma_normal235[] = {0x67, 0x03};
static char nt35596_gamma_normal236[] = {0x68, 0x64};
static char nt35596_gamma_normal237[] = {0x69, 0x03};
static char nt35596_gamma_normal238[] = {0x6A, 0x75};
static char nt35596_gamma_normal239[] = {0x6B, 0x03};
static char nt35596_gamma_normal240[] = {0x6C, 0x85};
static char nt35596_gamma_normal241[] = {0x6D, 0x03};
static char nt35596_gamma_normal242[] = {0x6E, 0x90};
static char nt35596_gamma_normal243[] = {0x6F, 0x03};
static char nt35596_gamma_normal244[] = {0x70, 0xCB};
static char nt35596_gamma_normal245[] = {0x71, 0x00};
static char nt35596_gamma_normal246[] = {0x72, 0x00};
static char nt35596_gamma_normal247[] = {0x73, 0x00};
static char nt35596_gamma_normal248[] = {0x74, 0x0A};
static char nt35596_gamma_normal249[] = {0x75, 0x00};
static char nt35596_gamma_normal250[] = {0x76, 0x2A};
static char nt35596_gamma_normal251[] = {0x77, 0x00};
static char nt35596_gamma_normal252[] = {0x78, 0x41};
static char nt35596_gamma_normal253[] = {0x79, 0x00};
static char nt35596_gamma_normal254[] = {0x7A, 0x56};
static char nt35596_gamma_normal255[] = {0x7B, 0x00};
static char nt35596_gamma_normal256[] = {0x7C, 0x69};
static char nt35596_gamma_normal257[] = {0x7D, 0x00};
static char nt35596_gamma_normal258[] = {0x7E, 0x7A};
static char nt35596_gamma_normal259[] = {0x7F, 0x00};
static char nt35596_gamma_normal260[] = {0x80, 0x8A};
static char nt35596_gamma_normal261[] = {0x81, 0x00};
static char nt35596_gamma_normal262[] = {0x82, 0x98};
static char nt35596_gamma_normal263[] = {0x83, 0x00};
static char nt35596_gamma_normal264[] = {0x84, 0xCB};
static char nt35596_gamma_normal265[] = {0x85, 0x00};
static char nt35596_gamma_normal266[] = {0x86, 0xF5};
static char nt35596_gamma_normal267[] = {0x87, 0x01};
static char nt35596_gamma_normal268[] = {0x88, 0x38};
static char nt35596_gamma_normal269[] = {0x89, 0x01};
static char nt35596_gamma_normal270[] = {0x8A, 0x6E};
static char nt35596_gamma_normal271[] = {0x8B, 0x01};
static char nt35596_gamma_normal272[] = {0x8C, 0xC4};
static char nt35596_gamma_normal273[] = {0x8D, 0x02};
static char nt35596_gamma_normal274[] = {0x8E, 0x07};
static char nt35596_gamma_normal275[] = {0x8F, 0x02};
static char nt35596_gamma_normal276[] = {0x90, 0x09};
static char nt35596_gamma_normal277[] = {0x91, 0x02};
static char nt35596_gamma_normal278[] = {0x92, 0x43};
static char nt35596_gamma_normal279[] = {0x93, 0x02};
static char nt35596_gamma_normal280[] = {0x94, 0x7E};
static char nt35596_gamma_normal281[] = {0x95, 0x02};
static char nt35596_gamma_normal282[] = {0x96, 0xA2};
static char nt35596_gamma_normal283[] = {0x97, 0x02};
static char nt35596_gamma_normal284[] = {0x98, 0xD4};
static char nt35596_gamma_normal285[] = {0x99, 0x02};
static char nt35596_gamma_normal286[] = {0x9A, 0xFC};
static char nt35596_gamma_normal287[] = {0x9B, 0x03};
static char nt35596_gamma_normal288[] = {0x9C, 0x38};
static char nt35596_gamma_normal289[] = {0x9D, 0x03};
static char nt35596_gamma_normal290[] = {0x9E, 0x58};
static char nt35596_gamma_normal291[] = {0x9F, 0x03};
static char nt35596_gamma_normal292[] = {0xA0, 0x70};
static char nt35596_gamma_normal293[] = {0xA2, 0x03};
static char nt35596_gamma_normal294[] = {0xA3, 0x81};
static char nt35596_gamma_normal295[] = {0xA4, 0x03};
static char nt35596_gamma_normal296[] = {0xA5, 0x93};
static char nt35596_gamma_normal297[] = {0xA6, 0x03};
static char nt35596_gamma_normal298[] = {0xA7, 0xA8};
static char nt35596_gamma_normal299[] = {0xA9, 0x03};
static char nt35596_gamma_normal300[] = {0xAA, 0xB0};
static char nt35596_gamma_normal301[] = {0xAB, 0x03};
static char nt35596_gamma_normal302[] = {0xAC, 0xC0};
static char nt35596_gamma_normal303[] = {0xAD, 0x03};
static char nt35596_gamma_normal304[] = {0xAE, 0xCB};
static char nt35596_gamma_normal305[] = {0xAF, 0x00};
static char nt35596_gamma_normal306[] = {0xB0, 0x00};
static char nt35596_gamma_normal307[] = {0xB1, 0x00};
static char nt35596_gamma_normal308[] = {0xB2, 0x0A};
static char nt35596_gamma_normal309[] = {0xB3, 0x00};
static char nt35596_gamma_normal310[] = {0xB4, 0x2A};
static char nt35596_gamma_normal311[] = {0xB5, 0x00};
static char nt35596_gamma_normal312[] = {0xB6, 0x41};
static char nt35596_gamma_normal313[] = {0xB7, 0x00};
static char nt35596_gamma_normal314[] = {0xB8, 0x56};
static char nt35596_gamma_normal315[] = {0xB9, 0x00};
static char nt35596_gamma_normal316[] = {0xBA, 0x69};
static char nt35596_gamma_normal317[] = {0xBB, 0x00};
static char nt35596_gamma_normal318[] = {0xBC, 0x7A};
static char nt35596_gamma_normal319[] = {0xBD, 0x00};
static char nt35596_gamma_normal320[] = {0xBE, 0x8A};
static char nt35596_gamma_normal321[] = {0xBF, 0x00};
static char nt35596_gamma_normal322[] = {0xC0, 0x98};
static char nt35596_gamma_normal323[] = {0xC1, 0x00};
static char nt35596_gamma_normal324[] = {0xC2, 0xCB};
static char nt35596_gamma_normal325[] = {0xC3, 0x00};
static char nt35596_gamma_normal326[] = {0xC4, 0xF5};
static char nt35596_gamma_normal327[] = {0xC5, 0x01};
static char nt35596_gamma_normal328[] = {0xC6, 0x38};
static char nt35596_gamma_normal329[] = {0xC7, 0x01};
static char nt35596_gamma_normal330[] = {0xC8, 0x6E};
static char nt35596_gamma_normal331[] = {0xC9, 0x01};
static char nt35596_gamma_normal332[] = {0xCA, 0xC4};
static char nt35596_gamma_normal333[] = {0xCB, 0x02};
static char nt35596_gamma_normal334[] = {0xCC, 0x07};
static char nt35596_gamma_normal335[] = {0xCD, 0x02};
static char nt35596_gamma_normal336[] = {0xCE, 0x09};
static char nt35596_gamma_normal337[] = {0xCF, 0x02};
static char nt35596_gamma_normal338[] = {0xD0, 0x43};
static char nt35596_gamma_normal339[] = {0xD1, 0x02};
static char nt35596_gamma_normal340[] = {0xD2, 0x7E};
static char nt35596_gamma_normal341[] = {0xD3, 0x02};
static char nt35596_gamma_normal342[] = {0xD4, 0xA2};
static char nt35596_gamma_normal343[] = {0xD5, 0x02};
static char nt35596_gamma_normal344[] = {0xD6, 0xD4};
static char nt35596_gamma_normal345[] = {0xD7, 0x02};
static char nt35596_gamma_normal346[] = {0xD8, 0xFC};
static char nt35596_gamma_normal347[] = {0xD9, 0x03};
static char nt35596_gamma_normal348[] = {0xDA, 0x38};
static char nt35596_gamma_normal349[] = {0xDB, 0x03};
static char nt35596_gamma_normal350[] = {0xDC, 0x58};
static char nt35596_gamma_normal351[] = {0xDD, 0x03};
static char nt35596_gamma_normal352[] = {0xDE, 0x70};
static char nt35596_gamma_normal353[] = {0xDF, 0x03};
static char nt35596_gamma_normal354[] = {0xE0, 0x81};
static char nt35596_gamma_normal355[] = {0xE1, 0x03};
static char nt35596_gamma_normal356[] = {0xE2, 0x93};
static char nt35596_gamma_normal357[] = {0xE3, 0x03};
static char nt35596_gamma_normal358[] = {0xE4, 0xA8};
static char nt35596_gamma_normal359[] = {0xE5, 0x03};
static char nt35596_gamma_normal360[] = {0xE6, 0xB0};
static char nt35596_gamma_normal361[] = {0xE7, 0x03};
static char nt35596_gamma_normal362[] = {0xE8, 0xC0};
static char nt35596_gamma_normal363[] = {0xE9, 0x03};
static char nt35596_gamma_normal364[] = {0xEA, 0xCB};

static struct dsi_cmd_desc dsi_nt35596_gamma_normal[] = {
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal1)}, nt35596_gamma_normal1},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal2)}, nt35596_gamma_normal2},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal3)}, nt35596_gamma_normal3},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal4)}, nt35596_gamma_normal4},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal5)}, nt35596_gamma_normal5},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal6)}, nt35596_gamma_normal6},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal7)}, nt35596_gamma_normal7},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal8)}, nt35596_gamma_normal8},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal9)}, nt35596_gamma_normal9},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal10)}, nt35596_gamma_normal10},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal11)}, nt35596_gamma_normal11},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal12)}, nt35596_gamma_normal12},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal13)}, nt35596_gamma_normal13},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal14)}, nt35596_gamma_normal14},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal15)}, nt35596_gamma_normal15},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal16)}, nt35596_gamma_normal16},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal17)}, nt35596_gamma_normal17},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal18)}, nt35596_gamma_normal18},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal19)}, nt35596_gamma_normal19},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal20)}, nt35596_gamma_normal20},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal21)}, nt35596_gamma_normal21},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal22)}, nt35596_gamma_normal22},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal23)}, nt35596_gamma_normal23},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal24)}, nt35596_gamma_normal24},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal25)}, nt35596_gamma_normal25},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal26)}, nt35596_gamma_normal26},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal27)}, nt35596_gamma_normal27},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal28)}, nt35596_gamma_normal28},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal29)}, nt35596_gamma_normal29},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal30)}, nt35596_gamma_normal30},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal31)}, nt35596_gamma_normal31},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal32)}, nt35596_gamma_normal32},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal33)}, nt35596_gamma_normal33},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal34)}, nt35596_gamma_normal34},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal35)}, nt35596_gamma_normal35},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal36)}, nt35596_gamma_normal36},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal37)}, nt35596_gamma_normal37},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal38)}, nt35596_gamma_normal38},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal39)}, nt35596_gamma_normal39},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal40)}, nt35596_gamma_normal40},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal41)}, nt35596_gamma_normal41},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal42)}, nt35596_gamma_normal42},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal43)}, nt35596_gamma_normal43},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal44)}, nt35596_gamma_normal44},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal45)}, nt35596_gamma_normal45},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal46)}, nt35596_gamma_normal46},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal47)}, nt35596_gamma_normal47},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal48)}, nt35596_gamma_normal48},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal49)}, nt35596_gamma_normal49},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal50)}, nt35596_gamma_normal50},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal51)}, nt35596_gamma_normal51},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal52)}, nt35596_gamma_normal52},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal53)}, nt35596_gamma_normal53},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal54)}, nt35596_gamma_normal54},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal55)}, nt35596_gamma_normal55},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal56)}, nt35596_gamma_normal56},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal57)}, nt35596_gamma_normal57},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal58)}, nt35596_gamma_normal58},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal59)}, nt35596_gamma_normal59},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal60)}, nt35596_gamma_normal60},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal61)}, nt35596_gamma_normal61},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal62)}, nt35596_gamma_normal62},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal63)}, nt35596_gamma_normal63},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal64)}, nt35596_gamma_normal64},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal65)}, nt35596_gamma_normal65},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal66)}, nt35596_gamma_normal66},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal67)}, nt35596_gamma_normal67},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal68)}, nt35596_gamma_normal68},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal69)}, nt35596_gamma_normal69},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal70)}, nt35596_gamma_normal70},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal71)}, nt35596_gamma_normal71},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal72)}, nt35596_gamma_normal72},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal73)}, nt35596_gamma_normal73},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal74)}, nt35596_gamma_normal74},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal75)}, nt35596_gamma_normal75},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal76)}, nt35596_gamma_normal76},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal77)}, nt35596_gamma_normal77},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal78)}, nt35596_gamma_normal78},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal79)}, nt35596_gamma_normal79},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal80)}, nt35596_gamma_normal80},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal81)}, nt35596_gamma_normal81},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal82)}, nt35596_gamma_normal82},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal83)}, nt35596_gamma_normal83},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal84)}, nt35596_gamma_normal84},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal85)}, nt35596_gamma_normal85},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal86)}, nt35596_gamma_normal86},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal87)}, nt35596_gamma_normal87},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal88)}, nt35596_gamma_normal88},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal89)}, nt35596_gamma_normal89},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal90)}, nt35596_gamma_normal90},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal91)}, nt35596_gamma_normal91},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal92)}, nt35596_gamma_normal92},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal93)}, nt35596_gamma_normal93},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal94)}, nt35596_gamma_normal94},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal95)}, nt35596_gamma_normal95},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal96)}, nt35596_gamma_normal96},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal97)}, nt35596_gamma_normal97},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal98)}, nt35596_gamma_normal98},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal99)}, nt35596_gamma_normal99},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal100)}, nt35596_gamma_normal100},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal101)}, nt35596_gamma_normal101},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal102)}, nt35596_gamma_normal102},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal103)}, nt35596_gamma_normal103},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal104)}, nt35596_gamma_normal104},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal105)}, nt35596_gamma_normal105},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal106)}, nt35596_gamma_normal106},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal107)}, nt35596_gamma_normal107},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal108)}, nt35596_gamma_normal108},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal109)}, nt35596_gamma_normal109},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal110)}, nt35596_gamma_normal110},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal111)}, nt35596_gamma_normal111},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal112)}, nt35596_gamma_normal112},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal113)}, nt35596_gamma_normal113},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal114)}, nt35596_gamma_normal114},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal115)}, nt35596_gamma_normal115},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal116)}, nt35596_gamma_normal116},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal117)}, nt35596_gamma_normal117},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal118)}, nt35596_gamma_normal118},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal119)}, nt35596_gamma_normal119},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal120)}, nt35596_gamma_normal120},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal121)}, nt35596_gamma_normal121},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal122)}, nt35596_gamma_normal122},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal123)}, nt35596_gamma_normal123},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal124)}, nt35596_gamma_normal124},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal125)}, nt35596_gamma_normal125},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal126)}, nt35596_gamma_normal126},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal127)}, nt35596_gamma_normal127},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal128)}, nt35596_gamma_normal128},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal129)}, nt35596_gamma_normal129},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal130)}, nt35596_gamma_normal130},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal131)}, nt35596_gamma_normal131},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal132)}, nt35596_gamma_normal132},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal133)}, nt35596_gamma_normal133},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal134)}, nt35596_gamma_normal134},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal135)}, nt35596_gamma_normal135},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal136)}, nt35596_gamma_normal136},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal137)}, nt35596_gamma_normal137},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal138)}, nt35596_gamma_normal138},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal139)}, nt35596_gamma_normal139},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal140)}, nt35596_gamma_normal140},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal141)}, nt35596_gamma_normal141},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal142)}, nt35596_gamma_normal142},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal143)}, nt35596_gamma_normal143},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal144)}, nt35596_gamma_normal144},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal145)}, nt35596_gamma_normal145},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal146)}, nt35596_gamma_normal146},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal147)}, nt35596_gamma_normal147},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal148)}, nt35596_gamma_normal148},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal149)}, nt35596_gamma_normal149},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal150)}, nt35596_gamma_normal150},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal151)}, nt35596_gamma_normal151},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal152)}, nt35596_gamma_normal152},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal153)}, nt35596_gamma_normal153},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal154)}, nt35596_gamma_normal154},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal155)}, nt35596_gamma_normal155},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal156)}, nt35596_gamma_normal156},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal157)}, nt35596_gamma_normal157},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal158)}, nt35596_gamma_normal158},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal159)}, nt35596_gamma_normal159},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal160)}, nt35596_gamma_normal160},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal161)}, nt35596_gamma_normal161},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal162)}, nt35596_gamma_normal162},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal163)}, nt35596_gamma_normal163},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal164)}, nt35596_gamma_normal164},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal165)}, nt35596_gamma_normal165},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal166)}, nt35596_gamma_normal166},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal167)}, nt35596_gamma_normal167},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal168)}, nt35596_gamma_normal168},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal169)}, nt35596_gamma_normal169},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal170)}, nt35596_gamma_normal170},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal171)}, nt35596_gamma_normal171},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal172)}, nt35596_gamma_normal172},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal173)}, nt35596_gamma_normal173},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal174)}, nt35596_gamma_normal174},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal175)}, nt35596_gamma_normal175},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal176)}, nt35596_gamma_normal176},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal177)}, nt35596_gamma_normal177},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal178)}, nt35596_gamma_normal178},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal179)}, nt35596_gamma_normal179},
{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_gamma_normal180)}, nt35596_gamma_normal180},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal181)}, nt35596_gamma_normal181},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal182)}, nt35596_gamma_normal182},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal183)}, nt35596_gamma_normal183},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal184)}, nt35596_gamma_normal184},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal185)}, nt35596_gamma_normal185},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal186)}, nt35596_gamma_normal186},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal187)}, nt35596_gamma_normal187},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal188)}, nt35596_gamma_normal188},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal189)}, nt35596_gamma_normal189},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal190)}, nt35596_gamma_normal190},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal191)}, nt35596_gamma_normal191},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal192)}, nt35596_gamma_normal192},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal193)}, nt35596_gamma_normal193},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal194)}, nt35596_gamma_normal194},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal195)}, nt35596_gamma_normal195},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal196)}, nt35596_gamma_normal196},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal197)}, nt35596_gamma_normal197},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal198)}, nt35596_gamma_normal198},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal199)}, nt35596_gamma_normal199},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal200)}, nt35596_gamma_normal200},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal201)}, nt35596_gamma_normal201},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal202)}, nt35596_gamma_normal202},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal203)}, nt35596_gamma_normal203},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal204)}, nt35596_gamma_normal204},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal205)}, nt35596_gamma_normal205},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal206)}, nt35596_gamma_normal206},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal207)}, nt35596_gamma_normal207},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal208)}, nt35596_gamma_normal208},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal209)}, nt35596_gamma_normal209},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal210)}, nt35596_gamma_normal210},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal211)}, nt35596_gamma_normal211},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal212)}, nt35596_gamma_normal212},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal213)}, nt35596_gamma_normal213},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal214)}, nt35596_gamma_normal214},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal215)}, nt35596_gamma_normal215},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal216)}, nt35596_gamma_normal216},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal217)}, nt35596_gamma_normal217},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal218)}, nt35596_gamma_normal218},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal219)}, nt35596_gamma_normal219},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal220)}, nt35596_gamma_normal220},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal221)}, nt35596_gamma_normal221},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal222)}, nt35596_gamma_normal222},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal223)}, nt35596_gamma_normal223},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal224)}, nt35596_gamma_normal224},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal225)}, nt35596_gamma_normal225},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal226)}, nt35596_gamma_normal226},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal227)}, nt35596_gamma_normal227},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal228)}, nt35596_gamma_normal228},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal229)}, nt35596_gamma_normal229},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal230)}, nt35596_gamma_normal230},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal231)}, nt35596_gamma_normal231},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal232)}, nt35596_gamma_normal232},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal233)}, nt35596_gamma_normal233},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal234)}, nt35596_gamma_normal234},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal235)}, nt35596_gamma_normal235},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal236)}, nt35596_gamma_normal236},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal237)}, nt35596_gamma_normal237},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal238)}, nt35596_gamma_normal238},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal239)}, nt35596_gamma_normal239},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal240)}, nt35596_gamma_normal240},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal241)}, nt35596_gamma_normal241},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal242)}, nt35596_gamma_normal242},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal243)}, nt35596_gamma_normal243},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal244)}, nt35596_gamma_normal244},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal245)}, nt35596_gamma_normal245},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal246)}, nt35596_gamma_normal246},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal247)}, nt35596_gamma_normal247},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal248)}, nt35596_gamma_normal248},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal249)}, nt35596_gamma_normal249},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal250)}, nt35596_gamma_normal250},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal251)}, nt35596_gamma_normal251},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal252)}, nt35596_gamma_normal252},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal253)}, nt35596_gamma_normal253},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal254)}, nt35596_gamma_normal254},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal255)}, nt35596_gamma_normal255},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal256)}, nt35596_gamma_normal256},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal257)}, nt35596_gamma_normal257},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal258)}, nt35596_gamma_normal258},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal259)}, nt35596_gamma_normal259},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal260)}, nt35596_gamma_normal260},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal261)}, nt35596_gamma_normal261},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal262)}, nt35596_gamma_normal262},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal263)}, nt35596_gamma_normal263},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal264)}, nt35596_gamma_normal264},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal265)}, nt35596_gamma_normal265},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal266)}, nt35596_gamma_normal266},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal267)}, nt35596_gamma_normal267},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal268)}, nt35596_gamma_normal268},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal269)}, nt35596_gamma_normal269},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal270)}, nt35596_gamma_normal270},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal271)}, nt35596_gamma_normal271},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal272)}, nt35596_gamma_normal272},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal273)}, nt35596_gamma_normal273},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal274)}, nt35596_gamma_normal274},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal275)}, nt35596_gamma_normal275},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal276)}, nt35596_gamma_normal276},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal277)}, nt35596_gamma_normal277},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal278)}, nt35596_gamma_normal278},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal279)}, nt35596_gamma_normal279},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal280)}, nt35596_gamma_normal280},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal281)}, nt35596_gamma_normal281},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal282)}, nt35596_gamma_normal282},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal283)}, nt35596_gamma_normal283},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal284)}, nt35596_gamma_normal284},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal285)}, nt35596_gamma_normal285},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal286)}, nt35596_gamma_normal286},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal287)}, nt35596_gamma_normal287},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal288)}, nt35596_gamma_normal288},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal289)}, nt35596_gamma_normal289},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal290)}, nt35596_gamma_normal290},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal291)}, nt35596_gamma_normal291},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal292)}, nt35596_gamma_normal292},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal293)}, nt35596_gamma_normal293},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal294)}, nt35596_gamma_normal294},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal295)}, nt35596_gamma_normal295},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal296)}, nt35596_gamma_normal296},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal297)}, nt35596_gamma_normal297},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal298)}, nt35596_gamma_normal298},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal299)}, nt35596_gamma_normal299},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal300)}, nt35596_gamma_normal300},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal301)}, nt35596_gamma_normal301},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal302)}, nt35596_gamma_normal302},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal303)}, nt35596_gamma_normal303},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal304)}, nt35596_gamma_normal304},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal305)}, nt35596_gamma_normal305},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal306)}, nt35596_gamma_normal306},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal307)}, nt35596_gamma_normal307},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal308)}, nt35596_gamma_normal308},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal309)}, nt35596_gamma_normal309},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal310)}, nt35596_gamma_normal310},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal311)}, nt35596_gamma_normal311},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal312)}, nt35596_gamma_normal312},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal313)}, nt35596_gamma_normal313},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal314)}, nt35596_gamma_normal314},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal315)}, nt35596_gamma_normal315},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal316)}, nt35596_gamma_normal316},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal317)}, nt35596_gamma_normal317},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal318)}, nt35596_gamma_normal318},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal319)}, nt35596_gamma_normal319},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal320)}, nt35596_gamma_normal320},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal321)}, nt35596_gamma_normal321},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal322)}, nt35596_gamma_normal322},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal323)}, nt35596_gamma_normal323},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal324)}, nt35596_gamma_normal324},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal325)}, nt35596_gamma_normal325},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal326)}, nt35596_gamma_normal326},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal327)}, nt35596_gamma_normal327},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal328)}, nt35596_gamma_normal328},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal329)}, nt35596_gamma_normal329},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal330)}, nt35596_gamma_normal330},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal331)}, nt35596_gamma_normal331},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal332)}, nt35596_gamma_normal332},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal333)}, nt35596_gamma_normal333},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal334)}, nt35596_gamma_normal334},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal335)}, nt35596_gamma_normal335},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal336)}, nt35596_gamma_normal336},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal337)}, nt35596_gamma_normal337},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal338)}, nt35596_gamma_normal338},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal339)}, nt35596_gamma_normal339},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal340)}, nt35596_gamma_normal340},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal341)}, nt35596_gamma_normal341},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal342)}, nt35596_gamma_normal342},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal343)}, nt35596_gamma_normal343},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal344)}, nt35596_gamma_normal344},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal345)}, nt35596_gamma_normal345},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal346)}, nt35596_gamma_normal346},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal347)}, nt35596_gamma_normal347},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal348)}, nt35596_gamma_normal348},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal349)}, nt35596_gamma_normal349},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal350)}, nt35596_gamma_normal350},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal351)}, nt35596_gamma_normal351},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal352)}, nt35596_gamma_normal352},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal353)}, nt35596_gamma_normal353},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal354)}, nt35596_gamma_normal354},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal355)}, nt35596_gamma_normal355},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal356)}, nt35596_gamma_normal356},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal357)}, nt35596_gamma_normal357},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal358)}, nt35596_gamma_normal358},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal359)}, nt35596_gamma_normal359},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal360)}, nt35596_gamma_normal360},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal361)}, nt35596_gamma_normal361},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal362)}, nt35596_gamma_normal362},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal363)}, nt35596_gamma_normal363},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_normal364)}, nt35596_gamma_normal364},
{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};

static char nt35596_gamma_cool1[] =  {0xFF, 0x01};
static char nt35596_gamma_cool2[] =  {0xFB, 0x01};
static char nt35596_gamma_cool3[] =  {0x75, 0x01};
static char nt35596_gamma_cool4[] =  {0x76, 0x6A};
static char nt35596_gamma_cool5[] =  {0x77, 0x01};
static char nt35596_gamma_cool6[] =  {0x78, 0x6C};
static char nt35596_gamma_cool7[] =  {0x79, 0x01};
static char nt35596_gamma_cool8[] =  {0x7A, 0x71};
static char nt35596_gamma_cool9[] =  {0x7B, 0x01};
static char nt35596_gamma_cool10[] =  {0x7C, 0x75};
static char nt35596_gamma_cool11[] =  {0x7D, 0x01};
static char nt35596_gamma_cool12[] =  {0x7E, 0x7A};
static char nt35596_gamma_cool13[] =  {0x7F, 0x01};
static char nt35596_gamma_cool14[] =  {0x80, 0x7F};
static char nt35596_gamma_cool15[] =  {0x81, 0x01};
static char nt35596_gamma_cool16[] =  {0x82, 0x83};
static char nt35596_gamma_cool17[] =  {0x83, 0x01};
static char nt35596_gamma_cool18[] =  {0x84, 0x88};
static char nt35596_gamma_cool19[] =  {0x85, 0x01};
static char nt35596_gamma_cool20[] =  {0x86, 0x8C};
static char nt35596_gamma_cool21[] =  {0x87, 0x01};
static char nt35596_gamma_cool22[] =  {0x88, 0x9D};
static char nt35596_gamma_cool23[] =  {0x89, 0x01};
static char nt35596_gamma_cool24[] =  {0x8A, 0xAD};
static char nt35596_gamma_cool25[] =  {0x8B, 0x01};
static char nt35596_gamma_cool26[] =  {0x8C, 0xCA};
static char nt35596_gamma_cool27[] =  {0x8D, 0x01};
static char nt35596_gamma_cool28[] =  {0x8E, 0xE5};
static char nt35596_gamma_cool29[] =  {0x8F, 0x02};
static char nt35596_gamma_cool30[] =  {0x90, 0x14};
static char nt35596_gamma_cool31[] =  {0x91, 0x02};
static char nt35596_gamma_cool32[] =  {0x92, 0x40};
static char nt35596_gamma_cool33[] =  {0x93, 0x02};
static char nt35596_gamma_cool34[] =  {0x94, 0x41};
static char nt35596_gamma_cool35[] =  {0x95, 0x02};
static char nt35596_gamma_cool36[] =  {0x96, 0x6C};
static char nt35596_gamma_cool37[] =  {0x97, 0x02};
static char nt35596_gamma_cool38[] =  {0x98, 0xA0};
static char nt35596_gamma_cool39[] =  {0x99, 0x02};
static char nt35596_gamma_cool40[] =  {0x9A, 0xC4};
static char nt35596_gamma_cool41[] =  {0x9B, 0x02};
static char nt35596_gamma_cool42[] =  {0x9C, 0xF8};
static char nt35596_gamma_cool43[] =  {0x9D, 0x03};
static char nt35596_gamma_cool44[] =  {0x9E, 0x1E};
static char nt35596_gamma_cool45[] =  {0x9F, 0x03};
static char nt35596_gamma_cool46[] =  {0xA0, 0x65};
static char nt35596_gamma_cool47[] =  {0xA2, 0x03};
static char nt35596_gamma_cool48[] =  {0xA3, 0x7F};
static char nt35596_gamma_cool49[] =  {0xA4, 0x03};
static char nt35596_gamma_cool50[] =  {0xA5, 0x89};
static char nt35596_gamma_cool51[] =  {0xA6, 0x03};
static char nt35596_gamma_cool52[] =  {0xA7, 0x8F};
static char nt35596_gamma_cool53[] =  {0xA9, 0x03};
static char nt35596_gamma_cool54[] =  {0xAA, 0x93};
static char nt35596_gamma_cool55[] =  {0xAB, 0x03};
static char nt35596_gamma_cool56[] =  {0xAC, 0x9F};
static char nt35596_gamma_cool57[] =  {0xAD, 0x03};
static char nt35596_gamma_cool58[] =  {0xAE, 0xA7};
static char nt35596_gamma_cool59[] =  {0xAF, 0x03};
static char nt35596_gamma_cool60[] =  {0xB0, 0xB8};
static char nt35596_gamma_cool61[] =  {0xB1, 0x03};
static char nt35596_gamma_cool62[] =  {0xB2, 0xCB};
static char nt35596_gamma_cool63[] =  {0xB3, 0x01};
static char nt35596_gamma_cool64[] =  {0xB4, 0x6A};
static char nt35596_gamma_cool65[] =  {0xB5, 0x01};
static char nt35596_gamma_cool66[] =  {0xB6, 0x6C};
static char nt35596_gamma_cool67[] =  {0xB7, 0x01};
static char nt35596_gamma_cool68[] =  {0xB8, 0x71};
static char nt35596_gamma_cool69[] =  {0xB9, 0x01};
static char nt35596_gamma_cool70[] =  {0xBA, 0x75};
static char nt35596_gamma_cool71[] =  {0xBB, 0x01};
static char nt35596_gamma_cool72[] =  {0xBC, 0x7A};
static char nt35596_gamma_cool73[] =  {0xBD, 0x01};
static char nt35596_gamma_cool74[] =  {0xBE, 0x7F};
static char nt35596_gamma_cool75[] =  {0xBF, 0x01};
static char nt35596_gamma_cool76[] =  {0xC0, 0x83};
static char nt35596_gamma_cool77[] =  {0xC1, 0x01};
static char nt35596_gamma_cool78[] =  {0xC2, 0x88};
static char nt35596_gamma_cool79[] =  {0xC3, 0x01};
static char nt35596_gamma_cool80[] =  {0xC4, 0x8C};
static char nt35596_gamma_cool81[] =  {0xC5, 0x01};
static char nt35596_gamma_cool82[] =  {0xC6, 0x9D};
static char nt35596_gamma_cool83[] =  {0xC7, 0x01};
static char nt35596_gamma_cool84[] =  {0xC8, 0xAD};
static char nt35596_gamma_cool85[] =  {0xC9, 0x01};
static char nt35596_gamma_cool86[] =  {0xCA, 0xCA};
static char nt35596_gamma_cool87[] =  {0xCB, 0x01};
static char nt35596_gamma_cool88[] =  {0xCC, 0xE5};
static char nt35596_gamma_cool89[] =  {0xCD, 0x02};
static char nt35596_gamma_cool90[] =  {0xCE, 0x14};
static char nt35596_gamma_cool91[] =  {0xCF, 0x02};
static char nt35596_gamma_cool92[] =  {0xD0, 0x40};
static char nt35596_gamma_cool93[] =  {0xD1, 0x02};
static char nt35596_gamma_cool94[] =  {0xD2, 0x41};
static char nt35596_gamma_cool95[] =  {0xD3, 0x02};
static char nt35596_gamma_cool96[] =  {0xD4, 0x6C};
static char nt35596_gamma_cool97[] =  {0xD5, 0x02};
static char nt35596_gamma_cool98[] =  {0xD6, 0xA0};
static char nt35596_gamma_cool99[] =  {0xD7, 0x02};
static char nt35596_gamma_cool100[] =  {0xD8, 0xC4};
static char nt35596_gamma_cool101[] =  {0xD9, 0x02};
static char nt35596_gamma_cool102[] =  {0xDA, 0xF8};
static char nt35596_gamma_cool103[] =  {0xDB, 0x03};
static char nt35596_gamma_cool104[] =  {0xDC, 0x1E};
static char nt35596_gamma_cool105[] =  {0xDD, 0x03};
static char nt35596_gamma_cool106[] =  {0xDE, 0x65};
static char nt35596_gamma_cool107[] =  {0xDF, 0x03};
static char nt35596_gamma_cool108[] =  {0xE0, 0x7F};
static char nt35596_gamma_cool109[] =  {0xE1, 0x03};
static char nt35596_gamma_cool110[] =  {0xE2, 0x89};
static char nt35596_gamma_cool111[] =  {0xE3, 0x03};
static char nt35596_gamma_cool112[] =  {0xE4, 0x8F};
static char nt35596_gamma_cool113[] =  {0xE5, 0x03};
static char nt35596_gamma_cool114[] =  {0xE6, 0x93};
static char nt35596_gamma_cool115[] =  {0xE7, 0x03};
static char nt35596_gamma_cool116[] =  {0xE8, 0x9F};
static char nt35596_gamma_cool117[] =  {0xE9, 0x03};
static char nt35596_gamma_cool118[] =  {0xEA, 0xA7};
static char nt35596_gamma_cool119[] =  {0xEB, 0x03};
static char nt35596_gamma_cool120[] =  {0xEC, 0xB8};
static char nt35596_gamma_cool121[] =  {0xED, 0x03};
static char nt35596_gamma_cool122[] =  {0xEE, 0xCB};
static char nt35596_gamma_cool123[] =  {0xEF, 0x01};
static char nt35596_gamma_cool124[] =  {0xF0, 0x0B};
static char nt35596_gamma_cool125[] =  {0xF1, 0x01};
static char nt35596_gamma_cool126[] =  {0xF2, 0x0F};
static char nt35596_gamma_cool127[] =  {0xF3, 0x01};
static char nt35596_gamma_cool128[] =  {0xF4, 0x16};
static char nt35596_gamma_cool129[] =  {0xF5, 0x01};
static char nt35596_gamma_cool130[] =  {0xF6, 0x1D};
static char nt35596_gamma_cool131[] =  {0xF7, 0x01};
static char nt35596_gamma_cool132[] =  {0xF8, 0x25};
static char nt35596_gamma_cool133[] =  {0xF9, 0x01};
static char nt35596_gamma_cool134[] =  {0xFA, 0x2C};
static char nt35596_gamma_cool135[] =  {0xFF, 0x02};
static char nt35596_gamma_cool136[] =  {0xFB, 0x01};
static char nt35596_gamma_cool137[] =  {0x00, 0x01};
static char nt35596_gamma_cool138[] =  {0x01, 0x33};
static char nt35596_gamma_cool139[] =  {0x02, 0x01};
static char nt35596_gamma_cool140[] =  {0x03, 0x39};
static char nt35596_gamma_cool141[] =  {0x04, 0x01};
static char nt35596_gamma_cool142[] =  {0x05, 0x40};
static char nt35596_gamma_cool143[] =  {0x06, 0x01};
static char nt35596_gamma_cool144[] =  {0x07, 0x59};
static char nt35596_gamma_cool145[] =  {0x08, 0x01};
static char nt35596_gamma_cool146[] =  {0x09, 0x6F};
static char nt35596_gamma_cool147[] =  {0x0A, 0x01};
static char nt35596_gamma_cool148[] =  {0x0B, 0x98};
static char nt35596_gamma_cool149[] =  {0x0C, 0x01};
static char nt35596_gamma_cool150[] =  {0x0D, 0xBB};
static char nt35596_gamma_cool151[] =  {0x0E, 0x01};
static char nt35596_gamma_cool152[] =  {0x0F, 0xF6};
static char nt35596_gamma_cool153[] =  {0x10, 0x02};
static char nt35596_gamma_cool154[] =  {0x11, 0x29};
static char nt35596_gamma_cool155[] =  {0x12, 0x02};
static char nt35596_gamma_cool156[] =  {0x13, 0x2A};
static char nt35596_gamma_cool157[] =  {0x14, 0x02};
static char nt35596_gamma_cool158[] =  {0x15, 0x5A};
static char nt35596_gamma_cool159[] =  {0x16, 0x02};
static char nt35596_gamma_cool160[] =  {0x17, 0x8F};
static char nt35596_gamma_cool161[] =  {0x18, 0x02};
static char nt35596_gamma_cool162[] =  {0x19, 0xB2};
static char nt35596_gamma_cool163[] =  {0x1A, 0x02};
static char nt35596_gamma_cool164[] =  {0x1B, 0xE2};
static char nt35596_gamma_cool165[] =  {0x1C, 0x03};
static char nt35596_gamma_cool166[] =  {0x1D, 0x02};
static char nt35596_gamma_cool167[] =  {0x1E, 0x03};
static char nt35596_gamma_cool168[] =  {0x1F, 0x2E};
static char nt35596_gamma_cool169[] =  {0x20, 0x03};
static char nt35596_gamma_cool170[] =  {0x21, 0x3A};
static char nt35596_gamma_cool171[] =  {0x22, 0x03};
static char nt35596_gamma_cool172[] =  {0x23, 0x48};
static char nt35596_gamma_cool173[] =  {0x24, 0x03};
static char nt35596_gamma_cool174[] =  {0x25, 0x58};
static char nt35596_gamma_cool175[] =  {0x26, 0x03};
static char nt35596_gamma_cool176[] =  {0x27, 0x68};
static char nt35596_gamma_cool177[] =  {0x28, 0x03};
static char nt35596_gamma_cool178[] =  {0x29, 0x7A};
static char nt35596_gamma_cool179[] =  {0x2A, 0x03};
static char nt35596_gamma_cool180[] =  {0x2B, 0x8B};
static char nt35596_gamma_cool181[] =  {0x2D, 0x03};
static char nt35596_gamma_cool182[] =  {0x2F, 0x98};
static char nt35596_gamma_cool183[] =  {0x30, 0x03};
static char nt35596_gamma_cool184[] =  {0x31, 0xCB};
static char nt35596_gamma_cool185[] =  {0x32, 0x01};
static char nt35596_gamma_cool186[] =  {0x33, 0x0B};
static char nt35596_gamma_cool187[] =  {0x34, 0x01};
static char nt35596_gamma_cool188[] =  {0x35, 0x0F};
static char nt35596_gamma_cool189[] =  {0x36, 0x01};
static char nt35596_gamma_cool190[] =  {0x37, 0x16};
static char nt35596_gamma_cool191[] =  {0x38, 0x01};
static char nt35596_gamma_cool192[] =  {0x39, 0x1D};
static char nt35596_gamma_cool193[] =  {0x3A, 0x01};
static char nt35596_gamma_cool194[] =  {0x3B, 0x25};
static char nt35596_gamma_cool195[] =  {0x3D, 0x01};
static char nt35596_gamma_cool196[] =  {0x3F, 0x2C};
static char nt35596_gamma_cool197[] =  {0x40, 0x01};
static char nt35596_gamma_cool198[] =  {0x41, 0x33};
static char nt35596_gamma_cool199[] =  {0x42, 0x01};
static char nt35596_gamma_cool200[] =  {0x43, 0x39};
static char nt35596_gamma_cool201[] =  {0x44, 0x01};
static char nt35596_gamma_cool202[] =  {0x45, 0x40};
static char nt35596_gamma_cool203[] =  {0x46, 0x01};
static char nt35596_gamma_cool204[] =  {0x47, 0x59};
static char nt35596_gamma_cool205[] =  {0x48, 0x01};
static char nt35596_gamma_cool206[] =  {0x49, 0x6F};
static char nt35596_gamma_cool207[] =  {0x4A, 0x01};
static char nt35596_gamma_cool208[] =  {0x4B, 0x98};
static char nt35596_gamma_cool209[] =  {0x4C, 0x01};
static char nt35596_gamma_cool210[] =  {0x4D, 0xBB};
static char nt35596_gamma_cool211[] =  {0x4E, 0x01};
static char nt35596_gamma_cool212[] =  {0x4F, 0xF6};
static char nt35596_gamma_cool213[] =  {0x50, 0x02};
static char nt35596_gamma_cool214[] =  {0x51, 0x29};
static char nt35596_gamma_cool215[] =  {0x52, 0x02};
static char nt35596_gamma_cool216[] =  {0x53, 0x2A};
static char nt35596_gamma_cool217[] =  {0x54, 0x02};
static char nt35596_gamma_cool218[] =  {0x55, 0x5A};
static char nt35596_gamma_cool219[] =  {0x56, 0x02};
static char nt35596_gamma_cool220[] =  {0x58, 0x8F};
static char nt35596_gamma_cool221[] =  {0x59, 0x02};
static char nt35596_gamma_cool222[] =  {0x5A, 0xB2};
static char nt35596_gamma_cool223[] =  {0x5B, 0x02};
static char nt35596_gamma_cool224[] =  {0x5C, 0xE2};
static char nt35596_gamma_cool225[] =  {0x5D, 0x03};
static char nt35596_gamma_cool226[] =  {0x5E, 0x02};
static char nt35596_gamma_cool227[] =  {0x5F, 0x03};
static char nt35596_gamma_cool228[] =  {0x60, 0x2E};
static char nt35596_gamma_cool229[] =  {0x61, 0x03};
static char nt35596_gamma_cool230[] =  {0x62, 0x3A};
static char nt35596_gamma_cool231[] =  {0x63, 0x03};
static char nt35596_gamma_cool232[] =  {0x64, 0x48};
static char nt35596_gamma_cool233[] =  {0x65, 0x03};
static char nt35596_gamma_cool234[] =  {0x66, 0x58};
static char nt35596_gamma_cool235[] =  {0x67, 0x03};
static char nt35596_gamma_cool236[] =  {0x68, 0x68};
static char nt35596_gamma_cool237[] =  {0x69, 0x03};
static char nt35596_gamma_cool238[] =  {0x6A, 0x7A};
static char nt35596_gamma_cool239[] =  {0x6B, 0x03};
static char nt35596_gamma_cool240[] =  {0x6C, 0x8B};
static char nt35596_gamma_cool241[] =  {0x6D, 0x03};
static char nt35596_gamma_cool242[] =  {0x6E, 0x98};
static char nt35596_gamma_cool243[] =  {0x6F, 0x03};
static char nt35596_gamma_cool244[] =  {0x70, 0xCB};
static char nt35596_gamma_cool245[] =  {0x71, 0x00};
static char nt35596_gamma_cool246[] =  {0x72, 0x00};
static char nt35596_gamma_cool247[] =  {0x73, 0x00};
static char nt35596_gamma_cool248[] =  {0x74, 0x0A};
static char nt35596_gamma_cool249[] =  {0x75, 0x00};
static char nt35596_gamma_cool250[] =  {0x76, 0x2A};
static char nt35596_gamma_cool251[] =  {0x77, 0x00};
static char nt35596_gamma_cool252[] =  {0x78, 0x41};
static char nt35596_gamma_cool253[] =  {0x79, 0x00};
static char nt35596_gamma_cool254[] =  {0x7A, 0x56};
static char nt35596_gamma_cool255[] =  {0x7B, 0x00};
static char nt35596_gamma_cool256[] =  {0x7C, 0x69};
static char nt35596_gamma_cool257[] =  {0x7D, 0x00};
static char nt35596_gamma_cool258[] =  {0x7E, 0x7A};
static char nt35596_gamma_cool259[] =  {0x7F, 0x00};
static char nt35596_gamma_cool260[] =  {0x80, 0x8A};
static char nt35596_gamma_cool261[] =  {0x81, 0x00};
static char nt35596_gamma_cool262[] =  {0x82, 0x98};
static char nt35596_gamma_cool263[] =  {0x83, 0x00};
static char nt35596_gamma_cool264[] =  {0x84, 0xCB};
static char nt35596_gamma_cool265[] =  {0x85, 0x00};
static char nt35596_gamma_cool266[] =  {0x86, 0xF5};
static char nt35596_gamma_cool267[] =  {0x87, 0x01};
static char nt35596_gamma_cool268[] =  {0x88, 0x38};
static char nt35596_gamma_cool269[] =  {0x89, 0x01};
static char nt35596_gamma_cool270[] =  {0x8A, 0x6F};
static char nt35596_gamma_cool271[] =  {0x8B, 0x01};
static char nt35596_gamma_cool272[] =  {0x8C, 0xC5};
static char nt35596_gamma_cool273[] =  {0x8D, 0x02};
static char nt35596_gamma_cool274[] =  {0x8E, 0x09};
static char nt35596_gamma_cool275[] =  {0x8F, 0x02};
static char nt35596_gamma_cool276[] =  {0x90, 0x0A};
static char nt35596_gamma_cool277[] =  {0x91, 0x02};
static char nt35596_gamma_cool278[] =  {0x92, 0x43};
static char nt35596_gamma_cool279[] =  {0x93, 0x02};
static char nt35596_gamma_cool280[] =  {0x94, 0x7E};
static char nt35596_gamma_cool281[] =  {0x95, 0x02};
static char nt35596_gamma_cool282[] =  {0x96, 0xA3};
static char nt35596_gamma_cool283[] =  {0x97, 0x02};
static char nt35596_gamma_cool284[] =  {0x98, 0xD7};
static char nt35596_gamma_cool285[] =  {0x99, 0x02};
static char nt35596_gamma_cool286[] =  {0x9A, 0xFD};
static char nt35596_gamma_cool287[] =  {0x9B, 0x03};
static char nt35596_gamma_cool288[] =  {0x9C, 0x39};
static char nt35596_gamma_cool289[] =  {0x9D, 0x03};
static char nt35596_gamma_cool290[] =  {0x9E, 0x53};
static char nt35596_gamma_cool291[] =  {0x9F, 0x03};
static char nt35596_gamma_cool292[] =  {0xA0, 0x85};
static char nt35596_gamma_cool293[] =  {0xA2, 0x03};
static char nt35596_gamma_cool294[] =  {0xA3, 0xA1};
static char nt35596_gamma_cool295[] =  {0xA4, 0x03};
static char nt35596_gamma_cool296[] =  {0xA5, 0xBF};
static char nt35596_gamma_cool297[] =  {0xA6, 0x03};
static char nt35596_gamma_cool298[] =  {0xA7, 0xC7};
static char nt35596_gamma_cool299[] =  {0xA9, 0x03};
static char nt35596_gamma_cool300[] =  {0xAA, 0xC9};
static char nt35596_gamma_cool301[] =  {0xAB, 0x03};
static char nt35596_gamma_cool302[] =  {0xAC, 0xCA};
static char nt35596_gamma_cool303[] =  {0xAD, 0x03};
static char nt35596_gamma_cool304[] =  {0xAE, 0xCB};
static char nt35596_gamma_cool305[] =  {0xAF, 0x00};
static char nt35596_gamma_cool306[] =  {0xB0, 0x00};
static char nt35596_gamma_cool307[] =  {0xB1, 0x00};
static char nt35596_gamma_cool308[] =  {0xB2, 0x0A};
static char nt35596_gamma_cool309[] =  {0xB3, 0x00};
static char nt35596_gamma_cool310[] =  {0xB4, 0x2A};
static char nt35596_gamma_cool311[] =  {0xB5, 0x00};
static char nt35596_gamma_cool312[] =  {0xB6, 0x41};
static char nt35596_gamma_cool313[] =  {0xB7, 0x00};
static char nt35596_gamma_cool314[] =  {0xB8, 0x56};
static char nt35596_gamma_cool315[] =  {0xB9, 0x00};
static char nt35596_gamma_cool316[] =  {0xBA, 0x69};
static char nt35596_gamma_cool317[] =  {0xBB, 0x00};
static char nt35596_gamma_cool318[] =  {0xBC, 0x7A};
static char nt35596_gamma_cool319[] =  {0xBD, 0x00};
static char nt35596_gamma_cool320[] =  {0xBE, 0x8A};
static char nt35596_gamma_cool321[] =  {0xBF, 0x00};
static char nt35596_gamma_cool322[] =  {0xC0, 0x98};
static char nt35596_gamma_cool323[] =  {0xC1, 0x00};
static char nt35596_gamma_cool324[] =  {0xC2, 0xCB};
static char nt35596_gamma_cool325[] =  {0xC3, 0x00};
static char nt35596_gamma_cool326[] =  {0xC4, 0xF5};
static char nt35596_gamma_cool327[] =  {0xC5, 0x01};
static char nt35596_gamma_cool328[] =  {0xC6, 0x38};
static char nt35596_gamma_cool329[] =  {0xC7, 0x01};
static char nt35596_gamma_cool330[] =  {0xC8, 0x6F};
static char nt35596_gamma_cool331[] =  {0xC9, 0x01};
static char nt35596_gamma_cool332[] =  {0xCA, 0xC5};
static char nt35596_gamma_cool333[] =  {0xCB, 0x02};
static char nt35596_gamma_cool334[] =  {0xCC, 0x09};
static char nt35596_gamma_cool335[] =  {0xCD, 0x02};
static char nt35596_gamma_cool336[] =  {0xCE, 0x0A};
static char nt35596_gamma_cool337[] =  {0xCF, 0x02};
static char nt35596_gamma_cool338[] =  {0xD0, 0x43};
static char nt35596_gamma_cool339[] =  {0xD1, 0x02};
static char nt35596_gamma_cool340[] =  {0xD2, 0x7E};
static char nt35596_gamma_cool341[] =  {0xD3, 0x02};
static char nt35596_gamma_cool342[] =  {0xD4, 0xA3};
static char nt35596_gamma_cool343[] =  {0xD5, 0x02};
static char nt35596_gamma_cool344[] =  {0xD6, 0xD7};
static char nt35596_gamma_cool345[] =  {0xD7, 0x02};
static char nt35596_gamma_cool346[] =  {0xD8, 0xFD};
static char nt35596_gamma_cool347[] =  {0xD9, 0x03};
static char nt35596_gamma_cool348[] =  {0xDA, 0x39};
static char nt35596_gamma_cool349[] =  {0xDB, 0x03};
static char nt35596_gamma_cool350[] =  {0xDC, 0x53};
static char nt35596_gamma_cool351[] =  {0xDD, 0x03};
static char nt35596_gamma_cool352[] =  {0xDE, 0x85};
static char nt35596_gamma_cool353[] =  {0xDF, 0x03};
static char nt35596_gamma_cool354[] =  {0xE0, 0xA1};
static char nt35596_gamma_cool355[] =  {0xE1, 0x03};
static char nt35596_gamma_cool356[] =  {0xE2, 0xBF};
static char nt35596_gamma_cool357[] =  {0xE3, 0x03};
static char nt35596_gamma_cool358[] =  {0xE4, 0xC7};
static char nt35596_gamma_cool359[] =  {0xE5, 0x03};
static char nt35596_gamma_cool360[] =  {0xE6, 0xC9};
static char nt35596_gamma_cool361[] =  {0xE7, 0x03};
static char nt35596_gamma_cool362[] =  {0xE8, 0xCA};
static char nt35596_gamma_cool363[] =  {0xE9, 0x03};
static char nt35596_gamma_cool364[] =  {0xEA, 0xCB};

static struct dsi_cmd_desc dsi_nt35596_gamma_cool[] = {
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool1)}, nt35596_gamma_cool1},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool2)}, nt35596_gamma_cool2},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool3)}, nt35596_gamma_cool3},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool4)}, nt35596_gamma_cool4},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool5)}, nt35596_gamma_cool5},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool6)}, nt35596_gamma_cool6},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool7)}, nt35596_gamma_cool7},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool8)}, nt35596_gamma_cool8},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool9)}, nt35596_gamma_cool9},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool10)}, nt35596_gamma_cool10},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool11)}, nt35596_gamma_cool11},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool12)}, nt35596_gamma_cool12},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool13)}, nt35596_gamma_cool13},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool14)}, nt35596_gamma_cool14},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool15)}, nt35596_gamma_cool15},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool16)}, nt35596_gamma_cool16},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool17)}, nt35596_gamma_cool17},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool18)}, nt35596_gamma_cool18},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool19)}, nt35596_gamma_cool19},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool20)}, nt35596_gamma_cool20},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool21)}, nt35596_gamma_cool21},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool22)}, nt35596_gamma_cool22},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool23)}, nt35596_gamma_cool23},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool24)}, nt35596_gamma_cool24},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool25)}, nt35596_gamma_cool25},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool26)}, nt35596_gamma_cool26},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool27)}, nt35596_gamma_cool27},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool28)}, nt35596_gamma_cool28},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool29)}, nt35596_gamma_cool29},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool30)}, nt35596_gamma_cool30},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool31)}, nt35596_gamma_cool31},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool32)}, nt35596_gamma_cool32},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool33)}, nt35596_gamma_cool33},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool34)}, nt35596_gamma_cool34},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool35)}, nt35596_gamma_cool35},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool36)}, nt35596_gamma_cool36},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool37)}, nt35596_gamma_cool37},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool38)}, nt35596_gamma_cool38},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool39)}, nt35596_gamma_cool39},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool40)}, nt35596_gamma_cool40},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool41)}, nt35596_gamma_cool41},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool42)}, nt35596_gamma_cool42},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool43)}, nt35596_gamma_cool43},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool44)}, nt35596_gamma_cool44},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool45)}, nt35596_gamma_cool45},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool46)}, nt35596_gamma_cool46},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool47)}, nt35596_gamma_cool47},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool48)}, nt35596_gamma_cool48},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool49)}, nt35596_gamma_cool49},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool50)}, nt35596_gamma_cool50},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool51)}, nt35596_gamma_cool51},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool52)}, nt35596_gamma_cool52},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool53)}, nt35596_gamma_cool53},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool54)}, nt35596_gamma_cool54},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool55)}, nt35596_gamma_cool55},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool56)}, nt35596_gamma_cool56},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool57)}, nt35596_gamma_cool57},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool58)}, nt35596_gamma_cool58},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool59)}, nt35596_gamma_cool59},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool60)}, nt35596_gamma_cool60},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool61)}, nt35596_gamma_cool61},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool62)}, nt35596_gamma_cool62},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool63)}, nt35596_gamma_cool63},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool64)}, nt35596_gamma_cool64},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool65)}, nt35596_gamma_cool65},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool66)}, nt35596_gamma_cool66},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool67)}, nt35596_gamma_cool67},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool68)}, nt35596_gamma_cool68},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool69)}, nt35596_gamma_cool69},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool70)}, nt35596_gamma_cool70},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool71)}, nt35596_gamma_cool71},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool72)}, nt35596_gamma_cool72},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool73)}, nt35596_gamma_cool73},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool74)}, nt35596_gamma_cool74},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool75)}, nt35596_gamma_cool75},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool76)}, nt35596_gamma_cool76},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool77)}, nt35596_gamma_cool77},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool78)}, nt35596_gamma_cool78},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool79)}, nt35596_gamma_cool79},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool80)}, nt35596_gamma_cool80},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool81)}, nt35596_gamma_cool81},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool82)}, nt35596_gamma_cool82},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool83)}, nt35596_gamma_cool83},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool84)}, nt35596_gamma_cool84},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool85)}, nt35596_gamma_cool85},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool86)}, nt35596_gamma_cool86},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool87)}, nt35596_gamma_cool87},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool88)}, nt35596_gamma_cool88},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool89)}, nt35596_gamma_cool89},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool90)}, nt35596_gamma_cool90},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool91)}, nt35596_gamma_cool91},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool92)}, nt35596_gamma_cool92},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool93)}, nt35596_gamma_cool93},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool94)}, nt35596_gamma_cool94},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool95)}, nt35596_gamma_cool95},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool96)}, nt35596_gamma_cool96},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool97)}, nt35596_gamma_cool97},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool98)}, nt35596_gamma_cool98},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool99)}, nt35596_gamma_cool99},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool100)}, nt35596_gamma_cool100},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool101)}, nt35596_gamma_cool101},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool102)}, nt35596_gamma_cool102},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool103)}, nt35596_gamma_cool103},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool104)}, nt35596_gamma_cool104},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool105)}, nt35596_gamma_cool105},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool106)}, nt35596_gamma_cool106},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool107)}, nt35596_gamma_cool107},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool108)}, nt35596_gamma_cool108},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool109)}, nt35596_gamma_cool109},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool110)}, nt35596_gamma_cool110},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool111)}, nt35596_gamma_cool111},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool112)}, nt35596_gamma_cool112},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool113)}, nt35596_gamma_cool113},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool114)}, nt35596_gamma_cool114},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool115)}, nt35596_gamma_cool115},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool116)}, nt35596_gamma_cool116},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool117)}, nt35596_gamma_cool117},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool118)}, nt35596_gamma_cool118},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool119)}, nt35596_gamma_cool119},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool120)}, nt35596_gamma_cool120},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool121)}, nt35596_gamma_cool121},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool122)}, nt35596_gamma_cool122},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool123)}, nt35596_gamma_cool123},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool124)}, nt35596_gamma_cool124},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool125)}, nt35596_gamma_cool125},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool126)}, nt35596_gamma_cool126},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool127)}, nt35596_gamma_cool127},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool128)}, nt35596_gamma_cool128},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool129)}, nt35596_gamma_cool129},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool130)}, nt35596_gamma_cool130},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool131)}, nt35596_gamma_cool131},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool132)}, nt35596_gamma_cool132},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool133)}, nt35596_gamma_cool133},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool134)}, nt35596_gamma_cool134},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool135)}, nt35596_gamma_cool135},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool136)}, nt35596_gamma_cool136},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool137)}, nt35596_gamma_cool137},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool138)}, nt35596_gamma_cool138},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool139)}, nt35596_gamma_cool139},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool140)}, nt35596_gamma_cool140},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool141)}, nt35596_gamma_cool141},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool142)}, nt35596_gamma_cool142},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool143)}, nt35596_gamma_cool143},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool144)}, nt35596_gamma_cool144},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool145)}, nt35596_gamma_cool145},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool146)}, nt35596_gamma_cool146},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool147)}, nt35596_gamma_cool147},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool148)}, nt35596_gamma_cool148},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool149)}, nt35596_gamma_cool149},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool150)}, nt35596_gamma_cool150},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool151)}, nt35596_gamma_cool151},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool152)}, nt35596_gamma_cool152},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool153)}, nt35596_gamma_cool153},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool154)}, nt35596_gamma_cool154},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool155)}, nt35596_gamma_cool155},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool156)}, nt35596_gamma_cool156},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool157)}, nt35596_gamma_cool157},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool158)}, nt35596_gamma_cool158},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool159)}, nt35596_gamma_cool159},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool160)}, nt35596_gamma_cool160},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool161)}, nt35596_gamma_cool161},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool162)}, nt35596_gamma_cool162},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool163)}, nt35596_gamma_cool163},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool164)}, nt35596_gamma_cool164},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool165)}, nt35596_gamma_cool165},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool166)}, nt35596_gamma_cool166},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool167)}, nt35596_gamma_cool167},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool168)}, nt35596_gamma_cool168},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool169)}, nt35596_gamma_cool169},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool170)}, nt35596_gamma_cool170},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool171)}, nt35596_gamma_cool171},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool172)}, nt35596_gamma_cool172},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool173)}, nt35596_gamma_cool173},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool174)}, nt35596_gamma_cool174},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool175)}, nt35596_gamma_cool175},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool176)}, nt35596_gamma_cool176},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool177)}, nt35596_gamma_cool177},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool178)}, nt35596_gamma_cool178},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool179)}, nt35596_gamma_cool179},
{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_gamma_cool180)}, nt35596_gamma_cool180},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool181)}, nt35596_gamma_cool181},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool182)}, nt35596_gamma_cool182},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool183)}, nt35596_gamma_cool183},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool184)}, nt35596_gamma_cool184},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool185)}, nt35596_gamma_cool185},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool186)}, nt35596_gamma_cool186},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool187)}, nt35596_gamma_cool187},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool188)}, nt35596_gamma_cool188},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool189)}, nt35596_gamma_cool189},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool190)}, nt35596_gamma_cool190},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool191)}, nt35596_gamma_cool191},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool192)}, nt35596_gamma_cool192},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool193)}, nt35596_gamma_cool193},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool194)}, nt35596_gamma_cool194},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool195)}, nt35596_gamma_cool195},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool196)}, nt35596_gamma_cool196},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool197)}, nt35596_gamma_cool197},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool198)}, nt35596_gamma_cool198},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool199)}, nt35596_gamma_cool199},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool200)}, nt35596_gamma_cool200},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool201)}, nt35596_gamma_cool201},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool202)}, nt35596_gamma_cool202},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool203)}, nt35596_gamma_cool203},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool204)}, nt35596_gamma_cool204},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool205)}, nt35596_gamma_cool205},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool206)}, nt35596_gamma_cool206},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool207)}, nt35596_gamma_cool207},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool208)}, nt35596_gamma_cool208},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool209)}, nt35596_gamma_cool209},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool210)}, nt35596_gamma_cool210},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool211)}, nt35596_gamma_cool211},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool212)}, nt35596_gamma_cool212},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool213)}, nt35596_gamma_cool213},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool214)}, nt35596_gamma_cool214},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool215)}, nt35596_gamma_cool215},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool216)}, nt35596_gamma_cool216},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool217)}, nt35596_gamma_cool217},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool218)}, nt35596_gamma_cool218},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool219)}, nt35596_gamma_cool219},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool220)}, nt35596_gamma_cool220},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool221)}, nt35596_gamma_cool221},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool222)}, nt35596_gamma_cool222},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool223)}, nt35596_gamma_cool223},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool224)}, nt35596_gamma_cool224},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool225)}, nt35596_gamma_cool225},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool226)}, nt35596_gamma_cool226},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool227)}, nt35596_gamma_cool227},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool228)}, nt35596_gamma_cool228},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool229)}, nt35596_gamma_cool229},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool230)}, nt35596_gamma_cool230},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool231)}, nt35596_gamma_cool231},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool232)}, nt35596_gamma_cool232},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool233)}, nt35596_gamma_cool233},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool234)}, nt35596_gamma_cool234},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool235)}, nt35596_gamma_cool235},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool236)}, nt35596_gamma_cool236},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool237)}, nt35596_gamma_cool237},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool238)}, nt35596_gamma_cool238},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool239)}, nt35596_gamma_cool239},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool240)}, nt35596_gamma_cool240},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool241)}, nt35596_gamma_cool241},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool242)}, nt35596_gamma_cool242},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool243)}, nt35596_gamma_cool243},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool244)}, nt35596_gamma_cool244},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool245)}, nt35596_gamma_cool245},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool246)}, nt35596_gamma_cool246},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool247)}, nt35596_gamma_cool247},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool248)}, nt35596_gamma_cool248},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool249)}, nt35596_gamma_cool249},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool250)}, nt35596_gamma_cool250},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool251)}, nt35596_gamma_cool251},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool252)}, nt35596_gamma_cool252},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool253)}, nt35596_gamma_cool253},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool254)}, nt35596_gamma_cool254},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool255)}, nt35596_gamma_cool255},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool256)}, nt35596_gamma_cool256},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool257)}, nt35596_gamma_cool257},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool258)}, nt35596_gamma_cool258},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool259)}, nt35596_gamma_cool259},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool260)}, nt35596_gamma_cool260},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool261)}, nt35596_gamma_cool261},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool262)}, nt35596_gamma_cool262},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool263)}, nt35596_gamma_cool263},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool264)}, nt35596_gamma_cool264},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool265)}, nt35596_gamma_cool265},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool266)}, nt35596_gamma_cool266},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool267)}, nt35596_gamma_cool267},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool268)}, nt35596_gamma_cool268},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool269)}, nt35596_gamma_cool269},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool270)}, nt35596_gamma_cool270},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool271)}, nt35596_gamma_cool271},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool272)}, nt35596_gamma_cool272},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool273)}, nt35596_gamma_cool273},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool274)}, nt35596_gamma_cool274},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool275)}, nt35596_gamma_cool275},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool276)}, nt35596_gamma_cool276},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool277)}, nt35596_gamma_cool277},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool278)}, nt35596_gamma_cool278},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool279)}, nt35596_gamma_cool279},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool280)}, nt35596_gamma_cool280},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool281)}, nt35596_gamma_cool281},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool282)}, nt35596_gamma_cool282},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool283)}, nt35596_gamma_cool283},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool284)}, nt35596_gamma_cool284},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool285)}, nt35596_gamma_cool285},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool286)}, nt35596_gamma_cool286},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool287)}, nt35596_gamma_cool287},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool288)}, nt35596_gamma_cool288},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool289)}, nt35596_gamma_cool289},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool290)}, nt35596_gamma_cool290},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool291)}, nt35596_gamma_cool291},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool292)}, nt35596_gamma_cool292},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool293)}, nt35596_gamma_cool293},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool294)}, nt35596_gamma_cool294},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool295)}, nt35596_gamma_cool295},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool296)}, nt35596_gamma_cool296},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool297)}, nt35596_gamma_cool297},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool298)}, nt35596_gamma_cool298},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool299)}, nt35596_gamma_cool299},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool300)}, nt35596_gamma_cool300},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool301)}, nt35596_gamma_cool301},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool302)}, nt35596_gamma_cool302},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool303)}, nt35596_gamma_cool303},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool304)}, nt35596_gamma_cool304},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool305)}, nt35596_gamma_cool305},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool306)}, nt35596_gamma_cool306},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool307)}, nt35596_gamma_cool307},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool308)}, nt35596_gamma_cool308},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool309)}, nt35596_gamma_cool309},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool310)}, nt35596_gamma_cool310},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool311)}, nt35596_gamma_cool311},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool312)}, nt35596_gamma_cool312},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool313)}, nt35596_gamma_cool313},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool314)}, nt35596_gamma_cool314},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool315)}, nt35596_gamma_cool315},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool316)}, nt35596_gamma_cool316},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool317)}, nt35596_gamma_cool317},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool318)}, nt35596_gamma_cool318},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool319)}, nt35596_gamma_cool319},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool320)}, nt35596_gamma_cool320},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool321)}, nt35596_gamma_cool321},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool322)}, nt35596_gamma_cool322},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool323)}, nt35596_gamma_cool323},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool324)}, nt35596_gamma_cool324},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool325)}, nt35596_gamma_cool325},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool326)}, nt35596_gamma_cool326},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool327)}, nt35596_gamma_cool327},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool328)}, nt35596_gamma_cool328},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool329)}, nt35596_gamma_cool329},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool330)}, nt35596_gamma_cool330},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool331)}, nt35596_gamma_cool331},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool332)}, nt35596_gamma_cool332},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool333)}, nt35596_gamma_cool333},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool334)}, nt35596_gamma_cool334},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool335)}, nt35596_gamma_cool335},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool336)}, nt35596_gamma_cool336},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool337)}, nt35596_gamma_cool337},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool338)}, nt35596_gamma_cool338},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool339)}, nt35596_gamma_cool339},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool340)}, nt35596_gamma_cool340},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool341)}, nt35596_gamma_cool341},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool342)}, nt35596_gamma_cool342},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool343)}, nt35596_gamma_cool343},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool344)}, nt35596_gamma_cool344},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool345)}, nt35596_gamma_cool345},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool346)}, nt35596_gamma_cool346},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool347)}, nt35596_gamma_cool347},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool348)}, nt35596_gamma_cool348},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool349)}, nt35596_gamma_cool349},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool350)}, nt35596_gamma_cool350},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool351)}, nt35596_gamma_cool351},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool352)}, nt35596_gamma_cool352},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool353)}, nt35596_gamma_cool353},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool354)}, nt35596_gamma_cool354},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool355)}, nt35596_gamma_cool355},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool356)}, nt35596_gamma_cool356},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool357)}, nt35596_gamma_cool357},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool358)}, nt35596_gamma_cool358},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool359)}, nt35596_gamma_cool359},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool360)}, nt35596_gamma_cool360},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool361)}, nt35596_gamma_cool361},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool362)}, nt35596_gamma_cool362},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool363)}, nt35596_gamma_cool363},
{{DTYPE_DCS_WRITE1, 0, 0, 0, 0, sizeof(nt35596_gamma_cool364)}, nt35596_gamma_cool364},
{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35596_sleepout12)}, nt35596_sleepout12},
};


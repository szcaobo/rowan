/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */

/****************************************************************
* Auto generated by DE, please DO NOT modify this file directly.
*****************************************************************/

#ifndef __MTK_SPM_PMIC_WRAP_H__
#define __MTK_SPM_PMIC_WRAP_H__

/*
 * PMIC_WRAP
 */
#define VOLT_TO_PMIC_VAL(volt)  (((volt) - 40000 + 625 - 1) / 625)	/* ((((volt) - 700 * 100 + 625 - 1) / 625) */
#define PMIC_VAL_TO_VOLT(pmic)  (((pmic) * 625) + 40000)	/* (((pmic) * 625) / 100 + 700) */

enum pmic_wrap_phase_id {
	PMIC_WRAP_PHASE_ALLINONE,
	NR_PMIC_WRAP_PHASE,
};

/* IDX mapping */
enum {
	IDX_ALL_1_VSRAM_PWR_ON,          /* 0 *//* PMIC_WRAP_PHASE_ALLINONE */
	IDX_ALL_1_VSRAM_SHUTDOWN,        /* 1 */
	IDX_ALL_1_VSRAM_NORMAL,          /* 2 */
	IDX_ALL_1_VSRAM_SLEEP,           /* 3 */
	IDX_ALL_DPIDLE_LEAVE,            /* 4 */
	IDX_ALL_DPIDLE_ENTER,            /* 5 */
	IDX_ALL_RESERVE_6,               /* 6 */
	IDX_ALL_VCORE_SUSPEND,           /* 7 */
	IDX_ALL_VCORE_LEVEL0,            /* 8 */
	IDX_ALL_VCORE_LEVEL1,            /* 9 */
	IDX_ALL_VCORE_LEVEL2,            /* A */
	IDX_ALL_VCORE_LEVEL3,            /* B */
	IDX_ALL_2_VSRAM_PWR_ON,          /* C */
	IDX_ALL_2_VSRAM_SHUTDOWN,        /* D */
	IDX_ALL_2_VSRAM_NORMAL,          /* E */
	IDX_ALL_2_VSRAM_SLEEP,           /* F */
	NR_IDX_ALL,
};

/* APIs */
extern int mt_spm_pmic_wrap_init(void);
extern void mt_spm_pmic_wrap_set_phase(enum pmic_wrap_phase_id phase);
extern void mt_spm_pmic_wrap_set_cmd(enum pmic_wrap_phase_id phase, int idx,
				     unsigned int cmd_wdata);
#if 1
extern void mt_spm_pmic_wrap_get_cmd_full(enum pmic_wrap_phase_id phase, int idx,
					  unsigned int *p_cmd_addr, unsigned int *p_cmd_wdata);
extern void mt_spm_pmic_wrap_set_cmd_full(enum pmic_wrap_phase_id phase, int idx,
					  unsigned int cmd_addr, unsigned int cmd_wdata);
#endif

#endif /* __MTK_SPM_PMIC_WRAP_H__ */

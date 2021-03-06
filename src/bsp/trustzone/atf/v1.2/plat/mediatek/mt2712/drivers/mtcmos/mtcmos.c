/*
 * Copyright (c) 2015, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <delay_timer.h>
#include <mmio.h>
#include <mt2712_def.h>
#include <mtcmos.h>
#include <spm.h>

void mtcmos_ctrl_little_off(unsigned int linear_id, unsigned int chk_wfi)
{
	uint32_t reg_pwr_con;
	uint32_t reg_srm_pdn;
	uint32_t reg_srm_sleep;
	uint32_t bit_cpu;
	uint32_t bit_wfi;

	reg_srm_sleep = SPM_MP0_CPUTOP_SRM_SLEEP;

	switch (linear_id) {
	case 1:
		reg_pwr_con = SPM_MP0_CPU1_PWR_CON;
		reg_srm_pdn = SPM_MP0_CPU1_SRM_PDN;
		bit_cpu = MP0_CPU1;
		bit_wfi = MP0_CPU1_STANDBYWFI;
		break;
	case 2:
		reg_pwr_con = SPM_MP0_CPU2_PWR_CON;
		reg_srm_pdn = SPM_MP0_CPU2_SRM_PDN;
		bit_cpu = MP0_CPU2;
		bit_wfi = MP0_CPU2_STANDBYWFI;
		break;
	case 3:
		reg_pwr_con = SPM_MP0_CPU3_PWR_CON;
		reg_srm_pdn = SPM_MP0_CPU3_SRM_PDN;
		bit_cpu = MP0_CPU3;
		bit_wfi = MP0_CPU3_STANDBYWFI;
		break;
	default:
		/* should never come to here */
		return;
	}

	/* enable register control */
	mmio_write_32(SPM_POWERON_CONFIG_SET,
			(SPM_PROJECT_CODE << 16) | (1U << 0));

	if (chk_wfi)
		while ((mmio_read_32(SPM_SLEEP_TIMER_STA) & bit_wfi) == 0)
			continue;

	mmio_setbits_32(reg_pwr_con, PWR_ISO);
	mmio_clrbits_32(reg_pwr_con, SRAM_ISOINT_B);
	mmio_setbits_32(reg_pwr_con, SRAM_CKISO);
	mmio_clrbits_32(reg_pwr_con, PWR_RST_B);
	mmio_setbits_32(reg_pwr_con, PWR_CLK_DIS);
	mmio_clrbits_32(reg_pwr_con, PWR_ON);
	mmio_clrbits_32(reg_pwr_con, PWR_ON_2ND);
	mmio_clrbits_32(reg_srm_sleep, MEM_SLP_B);

	/* Wait 1000ns for power off ready */
	udelay(1);

	while ((mmio_read_32(SPM_PWR_STATUS) & bit_cpu) ||
	       (mmio_read_32(SPM_PWR_STATUS_2ND) & bit_cpu))
		continue;

	mmio_setbits_32(reg_srm_pdn, MEM_PD);

	/* Wait 1500ns for memory power down */
	udelay(2);

	while (!(mmio_read_32(reg_srm_pdn) & MEM_PD_ACK))
		continue;

	mmio_setbits_32(reg_pwr_con, PD_SLPB_CLAMP);
}

void mtcmos_ctrl_little_on(unsigned int linear_id, unsigned int chk_wfi)
{
	uint32_t reg_pwr_con;
	uint32_t reg_srm_pdn;
	uint32_t reg_srm_sleep;
	uint32_t bit_cpu;

        reg_srm_sleep = SPM_MP0_CPUTOP_SRM_SLEEP;

	switch (linear_id) {
	case 1:
		reg_pwr_con = SPM_MP0_CPU1_PWR_CON;
		reg_srm_pdn = SPM_MP0_CPU1_SRM_PDN;
		bit_cpu = MP0_CPU1;
		break;
	case 2:
		reg_pwr_con = SPM_MP0_CPU2_PWR_CON;
		reg_srm_pdn = SPM_MP0_CPU2_SRM_PDN;
		bit_cpu = MP0_CPU2;
		break;
	case 3:
		reg_pwr_con = SPM_MP0_CPU3_PWR_CON;
		reg_srm_pdn = SPM_MP0_CPU3_SRM_PDN;
		bit_cpu = MP0_CPU3;
		break;
	default:
		/* should never come to here */
		return;
	}

	/* enable register control */
	mmio_write_32(SPM_POWERON_CONFIG_SET,
			(SPM_PROJECT_CODE << 16) | (1U << 0));

	mmio_clrbits_32(reg_pwr_con, PD_SLPB_CLAMP);

	mmio_clrbits_32(reg_srm_pdn, MEM_PD);

	while ((mmio_read_32(reg_srm_pdn) & MEM_PD_ACK) != 0)
		continue;

	mmio_setbits_32(reg_pwr_con, PWR_ON);

	/* Wait 200ns for power on ready */
	udelay(1);

	while ((mmio_read_32(SPM_PWR_STATUS) & bit_cpu) != bit_cpu)
		continue;

	mmio_setbits_32(reg_pwr_con, PWR_ON_2ND);
	while ((mmio_read_32(SPM_PWR_STATUS_2ND) & bit_cpu) != bit_cpu)
		continue;

	mmio_setbits_32(reg_srm_sleep, MEM_SLP_B);

	mmio_setbits_32(reg_pwr_con, SRAM_ISOINT_B);
	mmio_clrbits_32(reg_pwr_con, PWR_ISO);

	/* Wait 1000ns for memory power ready (defined in memory model) */
	udelay(1);

	mmio_clrbits_32(reg_pwr_con, SRAM_CKISO);
	mmio_clrbits_32(reg_pwr_con, PWR_CLK_DIS);
	mmio_setbits_32(reg_pwr_con, PWR_RST_B);
}

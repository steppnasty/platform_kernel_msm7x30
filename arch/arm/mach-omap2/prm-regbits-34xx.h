#ifndef __ARCH_ARM_MACH_OMAP2_PRM_REGBITS_34XX_H
#define __ARCH_ARM_MACH_OMAP2_PRM_REGBITS_34XX_H

/*
 * OMAP3430 Power/Reset Management register bits
 *
 * Copyright (C) 2007-2008 Texas Instruments, Inc.
 * Copyright (C) 2007-2008 Nokia Corporation
 *
 * Written by Paul Walmsley
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include "prm.h"

/* Shared register bits */

/* PRM_VC_CMD_VAL_0, PRM_VC_CMD_VAL_1 shared bits */
#define OMAP3430_ON_SHIFT				24
#define OMAP3430_ON_MASK				(0xff << 24)
#define OMAP3430_ONLP_SHIFT				16
#define OMAP3430_ONLP_MASK				(0xff << 16)
#define OMAP3430_RET_SHIFT				8
#define OMAP3430_RET_MASK				(0xff << 8)
#define OMAP3430_OFF_SHIFT				0
#define OMAP3430_OFF_MASK				(0xff << 0)

/* PRM_VP1_CONFIG, PRM_VP2_CONFIG shared bits */
#define OMAP3430_ERROROFFSET_SHIFT			24
#define OMAP3430_ERROROFFSET_MASK			(0xff << 24)
#define OMAP3430_ERRORGAIN_SHIFT			16
#define OMAP3430_ERRORGAIN_MASK				(0xff << 16)
#define OMAP3430_INITVOLTAGE_SHIFT			8
#define OMAP3430_INITVOLTAGE_MASK			(0xff << 8)
#define OMAP3430_TIMEOUTEN_MASK				(1 << 3)
#define OMAP3430_INITVDD_MASK				(1 << 2)
#define OMAP3430_FORCEUPDATE_MASK			(1 << 1)
#define OMAP3430_VPENABLE_MASK				(1 << 0)

/* PRM_VP1_VSTEPMIN, PRM_VP2_VSTEPMIN shared bits */
#define OMAP3430_SMPSWAITTIMEMIN_SHIFT			8
#define OMAP3430_SMPSWAITTIMEMIN_MASK			(0xffff << 8)
#define OMAP3430_VSTEPMIN_SHIFT				0
#define OMAP3430_VSTEPMIN_MASK				(0xff << 0)

/* PRM_VP1_VSTEPMAX, PRM_VP2_VSTEPMAX shared bits */
#define OMAP3430_SMPSWAITTIMEMAX_SHIFT			8
#define OMAP3430_SMPSWAITTIMEMAX_MASK			(0xffff << 8)
#define OMAP3430_VSTEPMAX_SHIFT				0
#define OMAP3430_VSTEPMAX_MASK				(0xff << 0)

/* PRM_VP1_VLIMITTO, PRM_VP2_VLIMITTO shared bits */
#define OMAP3430_VDDMAX_SHIFT				24
#define OMAP3430_VDDMAX_MASK				(0xff << 24)
#define OMAP3430_VDDMIN_SHIFT				16
#define OMAP3430_VDDMIN_MASK				(0xff << 16)
#define OMAP3430_TIMEOUT_SHIFT				0
#define OMAP3430_TIMEOUT_MASK				(0xffff << 0)

/* PRM_VP1_VOLTAGE, PRM_VP2_VOLTAGE shared bits */
#define OMAP3430_VPVOLTAGE_SHIFT			0
#define OMAP3430_VPVOLTAGE_MASK				(0xff << 0)

/* PRM_VP1_STATUS, PRM_VP2_STATUS shared bits */
#define OMAP3430_VPINIDLE_MASK				(1 << 0)

/* PM_WKDEP_IVA2, PM_WKDEP_MPU shared bits */
#define OMAP3430_EN_PER_SHIFT				7
#define OMAP3430_EN_PER_MASK				(1 << 7)

/* PM_PWSTCTRL_IVA2, PM_PWSTCTRL_MPU, PM_PWSTCTRL_CORE shared bits */
#define OMAP3430_MEMORYCHANGE_MASK			(1 << 3)

/* PM_PWSTST_IVA2, PM_PWSTST_CORE shared bits */
#define OMAP3430_LOGICSTATEST_MASK			(1 << 2)

/* PM_PREPWSTST_IVA2, PM_PREPWSTST_CORE shared bits */
#define OMAP3430_LASTLOGICSTATEENTERED_MASK		(1 << 2)

/*
 * PM_PREPWSTST_IVA2, PM_PREPWSTST_MPU, PM_PREPWSTST_CORE,
 * PM_PREPWSTST_GFX, PM_PREPWSTST_DSS, PM_PREPWSTST_CAM,
 * PM_PREPWSTST_PER, PM_PREPWSTST_NEON shared bits
 */
#define OMAP3430_LASTPOWERSTATEENTERED_SHIFT		0
#define OMAP3430_LASTPOWERSTATEENTERED_MASK		(0x3 << 0)

/* PRM_IRQSTATUS_IVA2, PRM_IRQSTATUS_MPU shared bits */
#define OMAP3430_WKUP_ST_MASK				(1 << 0)

/* PRM_IRQENABLE_IVA2, PRM_IRQENABLE_MPU shared bits */
#define OMAP3430_WKUP_EN_MASK				(1 << 0)

/* PM_MPUGRPSEL1_CORE, PM_IVA2GRPSEL1_CORE shared bits */
#define OMAP3430_GRPSEL_MMC2_MASK			(1 << 25)
#define OMAP3430_GRPSEL_MMC1_MASK			(1 << 24)
#define OMAP3430_GRPSEL_MCSPI4_MASK			(1 << 21)
#define OMAP3430_GRPSEL_MCSPI3_MASK			(1 << 20)
#define OMAP3430_GRPSEL_MCSPI2_MASK			(1 << 19)
#define OMAP3430_GRPSEL_MCSPI1_MASK			(1 << 18)
#define OMAP3430_GRPSEL_I2C3_SHIFT			17
#define OMAP3430_GRPSEL_I2C3_MASK			(1 << 17)
#define OMAP3430_GRPSEL_I2C2_SHIFT			16
#define OMAP3430_GRPSEL_I2C2_MASK			(1 << 16)
#define OMAP3430_GRPSEL_I2C1_SHIFT			15
#define OMAP3430_GRPSEL_I2C1_MASK			(1 << 15)
#define OMAP3430_GRPSEL_UART2_MASK			(1 << 14)
#define OMAP3430_GRPSEL_UART1_MASK			(1 << 13)
#define OMAP3430_GRPSEL_GPT11_MASK			(1 << 12)
#define OMAP3430_GRPSEL_GPT10_MASK			(1 << 11)
#define OMAP3430_GRPSEL_MCBSP5_MASK			(1 << 10)
#define OMAP3430_GRPSEL_MCBSP1_MASK			(1 << 9)
#define OMAP3430_GRPSEL_HSOTGUSB_MASK			(1 << 4)
#define OMAP3430_GRPSEL_D2D_MASK			(1 << 3)

/*
 * PM_PWSTCTRL_GFX, PM_PWSTCTRL_DSS, PM_PWSTCTRL_CAM,
 * PM_PWSTCTRL_PER shared bits
 */
#define OMAP3430_MEMONSTATE_SHIFT			16
#define OMAP3430_MEMONSTATE_MASK			(0x3 << 16)
#define OMAP3430_MEMRETSTATE_MASK			(1 << 8)

/* PM_MPUGRPSEL_PER, PM_IVA2GRPSEL_PER shared bits */
#define OMAP3630_GRPSEL_UART4_MASK			(1 << 18)
#define OMAP3430_GRPSEL_GPIO6_MASK			(1 << 17)
#define OMAP3430_GRPSEL_GPIO5_MASK			(1 << 16)
#define OMAP3430_GRPSEL_GPIO4_MASK			(1 << 15)
#define OMAP3430_GRPSEL_GPIO3_MASK			(1 << 14)
#define OMAP3430_GRPSEL_GPIO2_MASK			(1 << 13)
#define OMAP3430_GRPSEL_UART3_MASK			(1 << 11)
#define OMAP3430_GRPSEL_GPT9_MASK			(1 << 10)
#define OMAP3430_GRPSEL_GPT8_MASK			(1 << 9)
#define OMAP3430_GRPSEL_GPT7_MASK			(1 << 8)
#define OMAP3430_GRPSEL_GPT6_MASK			(1 << 7)
#define OMAP3430_GRPSEL_GPT5_MASK			(1 << 6)
#define OMAP3430_GRPSEL_GPT4_MASK			(1 << 5)
#define OMAP3430_GRPSEL_GPT3_MASK			(1 << 4)
#define OMAP3430_GRPSEL_GPT2_MASK			(1 << 3)
#define OMAP3430_GRPSEL_MCBSP4_MASK			(1 << 2)
#define OMAP3430_GRPSEL_MCBSP3_MASK			(1 << 1)
#define OMAP3430_GRPSEL_MCBSP2_MASK			(1 << 0)

/* PM_MPUGRPSEL_WKUP, PM_IVA2GRPSEL_WKUP shared bits */
#define OMAP3430_GRPSEL_IO_MASK				(1 << 8)
#define OMAP3430_GRPSEL_SR2_MASK			(1 << 7)
#define OMAP3430_GRPSEL_SR1_MASK			(1 << 6)
#define OMAP3430_GRPSEL_GPIO1_MASK			(1 << 3)
#define OMAP3430_GRPSEL_GPT12_MASK			(1 << 1)
#define OMAP3430_GRPSEL_GPT1_MASK			(1 << 0)

/* Bits specific to each register */

/* RM_RSTCTRL_IVA2 */
#define OMAP3430_RST3_IVA2_MASK				(1 << 2)
#define OMAP3430_RST2_IVA2_MASK				(1 << 1)
#define OMAP3430_RST1_IVA2_MASK				(1 << 0)

/* RM_RSTST_IVA2 specific bits */
#define OMAP3430_EMULATION_VSEQ_RST_MASK		(1 << 13)
#define OMAP3430_EMULATION_VHWA_RST_MASK		(1 << 12)
#define OMAP3430_EMULATION_IVA2_RST_MASK		(1 << 11)
#define OMAP3430_IVA2_SW_RST3_MASK			(1 << 10)
#define OMAP3430_IVA2_SW_RST2_MASK			(1 << 9)
#define OMAP3430_IVA2_SW_RST1_MASK			(1 << 8)

/* PM_WKDEP_IVA2 specific bits */

/* PM_PWSTCTRL_IVA2 specific bits */
#define OMAP3430_L2FLATMEMONSTATE_SHIFT			22
#define OMAP3430_L2FLATMEMONSTATE_MASK			(0x3 << 22)
#define OMAP3430_SHAREDL2CACHEFLATONSTATE_SHIFT		20
#define OMAP3430_SHAREDL2CACHEFLATONSTATE_MASK		(0x3 << 20)
#define OMAP3430_L1FLATMEMONSTATE_SHIFT			18
#define OMAP3430_L1FLATMEMONSTATE_MASK			(0x3 << 18)
#define OMAP3430_SHAREDL1CACHEFLATONSTATE_SHIFT		16
#define OMAP3430_SHAREDL1CACHEFLATONSTATE_MASK		(0x3 << 16)
#define OMAP3430_L2FLATMEMRETSTATE_MASK			(1 << 11)
#define OMAP3430_SHAREDL2CACHEFLATRETSTATE_MASK		(1 << 10)
#define OMAP3430_L1FLATMEMRETSTATE_MASK			(1 << 9)
#define OMAP3430_SHAREDL1CACHEFLATRETSTATE_MASK		(1 << 8)

/* PM_PWSTST_IVA2 specific bits */
#define OMAP3430_L2FLATMEMSTATEST_SHIFT			10
#define OMAP3430_L2FLATMEMSTATEST_MASK			(0x3 << 10)
#define OMAP3430_SHAREDL2CACHEFLATSTATEST_SHIFT		8
#define OMAP3430_SHAREDL2CACHEFLATSTATEST_MASK		(0x3 << 8)
#define OMAP3430_L1FLATMEMSTATEST_SHIFT			6
#define OMAP3430_L1FLATMEMSTATEST_MASK			(0x3 << 6)
#define OMAP3430_SHAREDL1CACHEFLATSTATEST_SHIFT		4
#define OMAP3430_SHAREDL1CACHEFLATSTATEST_MASK		(0x3 << 4)

/* PM_PREPWSTST_IVA2 specific bits */
#define OMAP3430_LASTL2FLATMEMSTATEENTERED_SHIFT		10
#define OMAP3430_LASTL2FLATMEMSTATEENTERED_MASK			(0x3 << 10)
#define OMAP3430_LASTSHAREDL2CACHEFLATSTATEENTERED_SHIFT	8
#define OMAP3430_LASTSHAREDL2CACHEFLATSTATEENTERED_MASK		(0x3 << 8)
#define OMAP3430_LASTL1FLATMEMSTATEENTERED_SHIFT		6
#define OMAP3430_LASTL1FLATMEMSTATEENTERED_MASK			(0x3 << 6)
#define OMAP3430_LASTSHAREDL1CACHEFLATSTATEENTERED_SHIFT	4
#define OMAP3430_LASTSHAREDL1CACHEFLATSTATEENTERED_MASK		(0x3 << 4)

/* PRM_IRQSTATUS_IVA2 specific bits */
#define OMAP3430_PRM_IRQSTATUS_IVA2_IVA2_DPLL_ST_MASK	(1 << 2)
#define OMAP3430_FORCEWKUP_ST_MASK			(1 << 1)

/* PRM_IRQENABLE_IVA2 specific bits */
#define OMAP3430_PRM_IRQENABLE_IVA2_IVA2_DPLL_RECAL_EN_MASK	(1 << 2)
#define OMAP3430_FORCEWKUP_EN_MASK				(1 << 1)

/* PRM_REVISION specific bits */

/* PRM_SYSCONFIG specific bits */

/* PRM_IRQSTATUS_MPU specific bits */
#define OMAP3430ES2_SND_PERIPH_DPLL_ST_SHIFT		25
#define OMAP3430ES2_SND_PERIPH_DPLL_ST_MASK		(1 << 25)
#define OMAP3430_VC_TIMEOUTERR_ST_MASK			(1 << 24)
#define OMAP3430_VC_RAERR_ST_MASK			(1 << 23)
#define OMAP3430_VC_SAERR_ST_MASK			(1 << 22)
#define OMAP3430_VP2_TRANXDONE_ST_MASK			(1 << 21)
#define OMAP3430_VP2_EQVALUE_ST_MASK			(1 << 20)
#define OMAP3430_VP2_NOSMPSACK_ST_MASK			(1 << 19)
#define OMAP3430_VP2_MAXVDD_ST_MASK			(1 << 18)
#define OMAP3430_VP2_MINVDD_ST_MASK			(1 << 17)
#define OMAP3430_VP2_OPPCHANGEDONE_ST_MASK		(1 << 16)
#define OMAP3430_VP1_TRANXDONE_ST_MASK			(1 << 15)
#define OMAP3430_VP1_EQVALUE_ST_MASK			(1 << 14)
#define OMAP3430_VP1_NOSMPSACK_ST_MASK			(1 << 13)
#define OMAP3430_VP1_MAXVDD_ST_MASK			(1 << 12)
#define OMAP3430_VP1_MINVDD_ST_MASK			(1 << 11)
#define OMAP3430_VP1_OPPCHANGEDONE_ST_MASK		(1 << 10)
#define OMAP3430_IO_ST_MASK				(1 << 9)
#define OMAP3430_PRM_IRQSTATUS_MPU_IVA2_DPLL_ST_MASK	(1 << 8)
#define OMAP3430_PRM_IRQSTATUS_MPU_IVA2_DPLL_ST_SHIFT	8
#define OMAP3430_MPU_DPLL_ST_MASK			(1 << 7)
#define OMAP3430_MPU_DPLL_ST_SHIFT			7
#define OMAP3430_PERIPH_DPLL_ST_MASK			(1 << 6)
#define OMAP3430_PERIPH_DPLL_ST_SHIFT			6
#define OMAP3430_CORE_DPLL_ST_MASK			(1 << 5)
#define OMAP3430_CORE_DPLL_ST_SHIFT			5
#define OMAP3430_TRANSITION_ST_MASK			(1 << 4)
#define OMAP3430_EVGENOFF_ST_MASK			(1 << 3)
#define OMAP3430_EVGENON_ST_MASK			(1 << 2)
#define OMAP3430_FS_USB_WKUP_ST_MASK			(1 << 1)

/* PRM_IRQENABLE_MPU specific bits */
#define OMAP3430ES2_SND_PERIPH_DPLL_RECAL_EN_SHIFT		25
#define OMAP3430ES2_SND_PERIPH_DPLL_RECAL_EN_MASK		(1 << 25)
#define OMAP3430_VC_TIMEOUTERR_EN_MASK				(1 << 24)
#define OMAP3430_VC_RAERR_EN_MASK				(1 << 23)
#define OMAP3430_VC_SAERR_EN_MASK				(1 << 22)
#define OMAP3430_VP2_TRANXDONE_EN_MASK				(1 << 21)
#define OMAP3430_VP2_EQVALUE_EN_MASK				(1 << 20)
#define OMAP3430_VP2_NOSMPSACK_EN_MASK				(1 << 19)
#define OMAP3430_VP2_MAXVDD_EN_MASK				(1 << 18)
#define OMAP3430_VP2_MINVDD_EN_MASK				(1 << 17)
#define OMAP3430_VP2_OPPCHANGEDONE_EN_MASK			(1 << 16)
#define OMAP3430_VP1_TRANXDONE_EN_MASK				(1 << 15)
#define OMAP3430_VP1_EQVALUE_EN_MASK				(1 << 14)
#define OMAP3430_VP1_NOSMPSACK_EN_MASK				(1 << 13)
#define OMAP3430_VP1_MAXVDD_EN_MASK				(1 << 12)
#define OMAP3430_VP1_MINVDD_EN_MASK				(1 << 11)
#define OMAP3430_VP1_OPPCHANGEDONE_EN_MASK			(1 << 10)
#define OMAP3430_IO_EN_MASK					(1 << 9)
#define OMAP3430_PRM_IRQENABLE_MPU_IVA2_DPLL_RECAL_EN_MASK	(1 << 8)
#define OMAP3430_PRM_IRQENABLE_MPU_IVA2_DPLL_RECAL_EN_SHIFT	8
#define OMAP3430_MPU_DPLL_RECAL_EN_MASK				(1 << 7)
#define OMAP3430_MPU_DPLL_RECAL_EN_SHIFT			7
#define OMAP3430_PERIPH_DPLL_RECAL_EN_MASK			(1 << 6)
#define OMAP3430_PERIPH_DPLL_RECAL_EN_SHIFT			6
#define OMAP3430_CORE_DPLL_RECAL_EN_MASK			(1 << 5)
#define OMAP3430_CORE_DPLL_RECAL_EN_SHIFT			5
#define OMAP3430_TRANSITION_EN_MASK				(1 << 4)
#define OMAP3430_EVGENOFF_EN_MASK				(1 << 3)
#define OMAP3430_EVGENON_EN_MASK				(1 << 2)
#define OMAP3430_FS_USB_WKUP_EN_MASK				(1 << 1)

/* RM_RSTST_MPU specific bits */
#define OMAP3430_EMULATION_MPU_RST_MASK			(1 << 11)

/* PM_WKDEP_MPU specific bits */
#define OMAP3430_PM_WKDEP_MPU_EN_DSS_SHIFT		5
#define OMAP3430_PM_WKDEP_MPU_EN_DSS_MASK		(1 << 5)
#define OMAP3430_PM_WKDEP_MPU_EN_IVA2_SHIFT		2
#define OMAP3430_PM_WKDEP_MPU_EN_IVA2_MASK		(1 << 2)

/* PM_EVGENCTRL_MPU */
#define OMAP3430_OFFLOADMODE_SHIFT			3
#define OMAP3430_OFFLOADMODE_MASK			(0x3 << 3)
#define OMAP3430_ONLOADMODE_SHIFT			1
#define OMAP3430_ONLOADMODE_MASK			(0x3 << 1)
#define OMAP3430_ENABLE_MASK				(1 << 0)

/* PM_EVGENONTIM_MPU */
#define OMAP3430_ONTIMEVAL_SHIFT			0
#define OMAP3430_ONTIMEVAL_MASK				(0xffffffff << 0)

/* PM_EVGENOFFTIM_MPU */
#define OMAP3430_OFFTIMEVAL_SHIFT			0
#define OMAP3430_OFFTIMEVAL_MASK			(0xffffffff << 0)

/* PM_PWSTCTRL_MPU specific bits */
#define OMAP3430_L2CACHEONSTATE_SHIFT			16
#define OMAP3430_L2CACHEONSTATE_MASK			(0x3 << 16)
#define OMAP3430_L2CACHERETSTATE_MASK			(1 << 8)
#define OMAP3430_LOGICL1CACHERETSTATE_MASK		(1 << 2)

/* PM_PWSTST_MPU specific bits */
#define OMAP3430_L2CACHESTATEST_SHIFT			6
#define OMAP3430_L2CACHESTATEST_MASK			(0x3 << 6)
#define OMAP3430_LOGICL1CACHESTATEST_MASK		(1 << 2)

/* PM_PREPWSTST_MPU specific bits */
#define OMAP3430_LASTL2CACHESTATEENTERED_SHIFT		6
#define OMAP3430_LASTL2CACHESTATEENTERED_MASK		(0x3 << 6)
#define OMAP3430_LASTLOGICL1CACHESTATEENTERED_MASK	(1 << 2)

/* RM_RSTCTRL_CORE */
#define OMAP3430_RM_RSTCTRL_CORE_MODEM_SW_RSTPWRON_MASK		(1 << 1)
#define OMAP3430_RM_RSTCTRL_CORE_MODEM_SW_RST_MASK		(1 << 0)

/* RM_RSTST_CORE specific bits */
#define OMAP3430_MODEM_SECURITY_VIOL_RST_MASK		(1 << 10)
#define OMAP3430_RM_RSTST_CORE_MODEM_SW_RSTPWRON_MASK	(1 << 9)
#define OMAP3430_RM_RSTST_CORE_MODEM_SW_RST_MASK	(1 << 8)

/* PM_WKEN1_CORE specific bits */

/* PM_MPUGRPSEL1_CORE specific bits */
#define OMAP3430_GRPSEL_FSHOSTUSB_MASK			(1 << 5)

/* PM_IVA2GRPSEL1_CORE specific bits */

/* PM_WKST1_CORE specific bits */

/* PM_PWSTCTRL_CORE specific bits */
#define OMAP3430_MEM2ONSTATE_SHIFT			18
#define OMAP3430_MEM2ONSTATE_MASK			(0x3 << 18)
#define OMAP3430_MEM1ONSTATE_SHIFT			16
#define OMAP3430_MEM1ONSTATE_MASK			(0x3 << 16)
#define OMAP3430_MEM2RETSTATE_MASK			(1 << 9)
#define OMAP3430_MEM1RETSTATE_MASK			(1 << 8)

/* PM_PWSTST_CORE specific bits */
#define OMAP3430_MEM2STATEST_SHIFT			6
#define OMAP3430_MEM2STATEST_MASK			(0x3 << 6)
#define OMAP3430_MEM1STATEST_SHIFT			4
#define OMAP3430_MEM1STATEST_MASK			(0x3 << 4)

/* PM_PREPWSTST_CORE specific bits */
#define OMAP3430_LASTMEM2STATEENTERED_SHIFT		6
#define OMAP3430_LASTMEM2STATEENTERED_MASK		(0x3 << 6)
#define OMAP3430_LASTMEM1STATEENTERED_SHIFT		4
#define OMAP3430_LASTMEM1STATEENTERED_MASK		(0x3 << 4)

/* RM_RSTST_GFX specific bits */

/* PM_WKDEP_GFX specific bits */
#define OMAP3430_PM_WKDEP_GFX_EN_IVA2_MASK		(1 << 2)

/* PM_PWSTCTRL_GFX specific bits */

/* PM_PWSTST_GFX specific bits */

/* PM_PREPWSTST_GFX specific bits */

/* PM_WKEN_WKUP specific bits */
#define OMAP3430_EN_IO_CHAIN_MASK			(1 << 16)
#define OMAP3430_EN_IO_MASK				(1 << 8)
#define OMAP3430_EN_GPIO1_MASK				(1 << 3)

/* PM_MPUGRPSEL_WKUP specific bits */

/* PM_IVA2GRPSEL_WKUP specific bits */

/* PM_WKST_WKUP specific bits */
#define OMAP3430_ST_IO_CHAIN_MASK			(1 << 16)
#define OMAP3430_ST_IO_MASK				(1 << 8)

/* PRM_CLKSEL */
#define OMAP3430_SYS_CLKIN_SEL_SHIFT			0
#define OMAP3430_SYS_CLKIN_SEL_MASK			(0x7 << 0)

/* PRM_CLKOUT_CTRL */
#define OMAP3430_CLKOUT_EN_MASK				(1 << 7)
#define OMAP3430_CLKOUT_EN_SHIFT			7

/* RM_RSTST_DSS specific bits */

/* PM_WKEN_DSS */
#define OMAP3430_PM_WKEN_DSS_EN_DSS_MASK		(1 << 0)

/* PM_WKDEP_DSS specific bits */
#define OMAP3430_PM_WKDEP_DSS_EN_IVA2_MASK		(1 << 2)

/* PM_PWSTCTRL_DSS specific bits */

/* PM_PWSTST_DSS specific bits */

/* PM_PREPWSTST_DSS specific bits */

/* RM_RSTST_CAM specific bits */

/* PM_WKDEP_CAM specific bits */
#define OMAP3430_PM_WKDEP_CAM_EN_IVA2_MASK		(1 << 2)

/* PM_PWSTCTRL_CAM specific bits */

/* PM_PWSTST_CAM specific bits */

/* PM_PREPWSTST_CAM specific bits */

/* PM_PWSTCTRL_USBHOST specific bits */
#define OMAP3430ES2_SAVEANDRESTORE_SHIFT		4

/* RM_RSTST_PER specific bits */

/* PM_WKEN_PER specific bits */

/* PM_MPUGRPSEL_PER specific bits */

/* PM_IVA2GRPSEL_PER specific bits */

/* PM_WKST_PER specific bits */

/* PM_WKDEP_PER specific bits */
#define OMAP3430_PM_WKDEP_PER_EN_IVA2_MASK		(1 << 2)

/* PM_PWSTCTRL_PER specific bits */

/* PM_PWSTST_PER specific bits */

/* PM_PREPWSTST_PER specific bits */

/* RM_RSTST_EMU specific bits */

/* PM_PWSTST_EMU specific bits */

/* PRM_VC_SMPS_SA */
#define OMAP3430_PRM_VC_SMPS_SA_SA1_SHIFT		16
#define OMAP3430_PRM_VC_SMPS_SA_SA1_MASK		(0x7f << 16)
#define OMAP3430_PRM_VC_SMPS_SA_SA0_SHIFT		0
#define OMAP3430_PRM_VC_SMPS_SA_SA0_MASK		(0x7f << 0)

/* PRM_VC_SMPS_VOL_RA */
#define OMAP3430_VOLRA1_SHIFT				16
#define OMAP3430_VOLRA1_MASK				(0xff << 16)
#define OMAP3430_VOLRA0_SHIFT				0
#define OMAP3430_VOLRA0_MASK				(0xff << 0)

/* PRM_VC_SMPS_CMD_RA */
#define OMAP3430_CMDRA1_SHIFT				16
#define OMAP3430_CMDRA1_MASK				(0xff << 16)
#define OMAP3430_CMDRA0_SHIFT				0
#define OMAP3430_CMDRA0_MASK				(0xff << 0)

/* PRM_VC_CMD_VAL_0 specific bits */
#define OMAP3430_VC_CMD_ON_SHIFT			24
#define OMAP3430_VC_CMD_ON_MASK				(0xFF << 24)
#define OMAP3430_VC_CMD_ONLP_SHIFT			16
#define OMAP3430_VC_CMD_ONLP_MASK			(0xFF << 16)
#define OMAP3430_VC_CMD_RET_SHIFT			8
#define OMAP3430_VC_CMD_RET_MASK			(0xFF << 8)
#define OMAP3430_VC_CMD_OFF_SHIFT			0
#define OMAP3430_VC_CMD_OFF_MASK			(0xFF << 0)

/* PRM_VC_CMD_VAL_1 specific bits */

/* PRM_VC_CH_CONF */
#define OMAP3430_CMD1_MASK				(1 << 20)
#define OMAP3430_RACEN1_MASK				(1 << 19)
#define OMAP3430_RAC1_MASK				(1 << 18)
#define OMAP3430_RAV1_MASK				(1 << 17)
#define OMAP3430_PRM_VC_CH_CONF_SA1_MASK		(1 << 16)
#define OMAP3430_CMD0_MASK				(1 << 4)
#define OMAP3430_RACEN0_MASK				(1 << 3)
#define OMAP3430_RAC0_MASK				(1 << 2)
#define OMAP3430_RAV0_MASK				(1 << 1)
#define OMAP3430_PRM_VC_CH_CONF_SA0_MASK		(1 << 0)

/* PRM_VC_I2C_CFG */
#define OMAP3430_HSMASTER_MASK				(1 << 5)
#define OMAP3430_SREN_MASK				(1 << 4)
#define OMAP3430_HSEN_MASK				(1 << 3)
#define OMAP3430_MCODE_SHIFT				0
#define OMAP3430_MCODE_MASK				(0x7 << 0)

/* PRM_VC_BYPASS_VAL */
#define OMAP3430_VALID_MASK				(1 << 24)
#define OMAP3430_DATA_SHIFT				16
#define OMAP3430_DATA_MASK				(0xff << 16)
#define OMAP3430_REGADDR_SHIFT				8
#define OMAP3430_REGADDR_MASK				(0xff << 8)
#define OMAP3430_SLAVEADDR_SHIFT			0
#define OMAP3430_SLAVEADDR_MASK				(0x7f << 0)

/* PRM_RSTCTRL */
#define OMAP3430_RST_DPLL3_MASK				(1 << 2)
#define OMAP3430_RST_GS_MASK				(1 << 1)

/* PRM_RSTTIME */
#define OMAP3430_RSTTIME2_SHIFT				8
#define OMAP3430_RSTTIME2_MASK				(0x1f << 8)
#define OMAP3430_RSTTIME1_SHIFT				0
#define OMAP3430_RSTTIME1_MASK				(0xff << 0)

/* PRM_RSTST */
#define OMAP3430_ICECRUSHER_RST_MASK			(1 << 10)
#define OMAP3430_ICEPICK_RST_MASK			(1 << 9)
#define OMAP3430_VDD2_VOLTAGE_MANAGER_RST_MASK		(1 << 8)
#define OMAP3430_VDD1_VOLTAGE_MANAGER_RST_MASK		(1 << 7)
#define OMAP3430_EXTERNAL_WARM_RST_MASK			(1 << 6)
#define OMAP3430_SECURE_WD_RST_MASK			(1 << 5)
#define OMAP3430_MPU_WD_RST_MASK			(1 << 4)
#define OMAP3430_SECURITY_VIOL_RST_MASK			(1 << 3)
#define OMAP3430_GLOBAL_SW_RST_MASK			(1 << 1)
#define OMAP3430_GLOBAL_COLD_RST_MASK			(1 << 0)

/* PRM_VOLTCTRL */
#define OMAP3430_SEL_VMODE_MASK				(1 << 4)
#define OMAP3430_SEL_OFF_MASK				(1 << 3)
#define OMAP3430_AUTO_OFF_MASK				(1 << 2)
#define OMAP3430_AUTO_RET_MASK				(1 << 1)
#define OMAP3430_AUTO_SLEEP_MASK			(1 << 0)

/* PRM_SRAM_PCHARGE */
#define OMAP3430_PCHARGE_TIME_SHIFT			0
#define OMAP3430_PCHARGE_TIME_MASK			(0xff << 0)

/* PRM_CLKSRC_CTRL */
#define OMAP3430_SYSCLKDIV_SHIFT			6
#define OMAP3430_SYSCLKDIV_MASK				(0x3 << 6)
#define OMAP3430_AUTOEXTCLKMODE_SHIFT			3
#define OMAP3430_AUTOEXTCLKMODE_MASK			(0x3 << 3)
#define OMAP3430_SYSCLKSEL_SHIFT			0
#define OMAP3430_SYSCLKSEL_MASK				(0x3 << 0)

/* PRM_VOLTSETUP1 */
#define OMAP3430_SETUP_TIME2_SHIFT			16
#define OMAP3430_SETUP_TIME2_MASK			(0xffff << 16)
#define OMAP3430_SETUP_TIME1_SHIFT			0
#define OMAP3430_SETUP_TIME1_MASK			(0xffff << 0)

/* PRM_VOLTOFFSET */
#define OMAP3430_OFFSET_TIME_SHIFT			0
#define OMAP3430_OFFSET_TIME_MASK			(0xffff << 0)

/* PRM_CLKSETUP */
#define OMAP3430_SETUP_TIME_SHIFT			0
#define OMAP3430_SETUP_TIME_MASK			(0xffff << 0)

/* PRM_POLCTRL */
#define OMAP3430_OFFMODE_POL_MASK			(1 << 3)
#define OMAP3430_CLKOUT_POL_MASK			(1 << 2)
#define OMAP3430_CLKREQ_POL_MASK			(1 << 1)
#define OMAP3430_EXTVOL_POL_MASK			(1 << 0)

/* PRM_VOLTSETUP2 */
#define OMAP3430_OFFMODESETUPTIME_SHIFT			0
#define OMAP3430_OFFMODESETUPTIME_MASK			(0xffff << 0)

/* PRM_VP1_CONFIG specific bits */

/* PRM_VP1_VSTEPMIN specific bits */

/* PRM_VP1_VSTEPMAX specific bits */

/* PRM_VP1_VLIMITTO specific bits */

/* PRM_VP1_VOLTAGE specific bits */

/* PRM_VP1_STATUS specific bits */

/* PRM_VP2_CONFIG specific bits */

/* PRM_VP2_VSTEPMIN specific bits */

/* PRM_VP2_VSTEPMAX specific bits */

/* PRM_VP2_VLIMITTO specific bits */

/* PRM_VP2_VOLTAGE specific bits */

/* PRM_VP2_STATUS specific bits */

/* RM_RSTST_NEON specific bits */

/* PM_WKDEP_NEON specific bits */

/* PM_PWSTCTRL_NEON specific bits */

/* PM_PWSTST_NEON specific bits */

/* PM_PREPWSTST_NEON specific bits */

#endif

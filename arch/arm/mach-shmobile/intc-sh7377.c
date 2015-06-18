/*
 * sh7377 processor support - INTC hardware block
 *
 * Copyright (C) 2010  Magnus Damm
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <linux/sh_intc.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>

enum {
	UNUSED_INTCA = 0,
	ENABLED,
	DISABLED,

	/* interrupt sources INTCA */
	IRQ0A, IRQ1A, IRQ2A, IRQ3A, IRQ4A, IRQ5A, IRQ6A, IRQ7A,
	IRQ8A, IRQ9A, IRQ10A, IRQ11A, IRQ12A, IRQ13A, IRQ14A, IRQ15A,
	IRQ16A, IRQ17A, IRQ18A, IRQ19A, IRQ20A, IRQ21A, IRQ22A, IRQ23A,
	IRQ24A, IRQ25A, IRQ26A, IRQ27A, IRQ28A, IRQ29A, IRQ30A, IRQ31A,
	DIRC,
	_2DG,
	CRYPT_STD,
	IIC1_ALI1, IIC1_TACKI1, IIC1_WAITI1, IIC1_DTEI1,
	AP_ARM_IRQPMU, AP_ARM_COMMTX, AP_ARM_COMMRX,
	MFI_MFIM, MFI_MFIS,
	BBIF1, BBIF2,
	USBDMAC_USHDMI,
	USBHS_USHI0, USBHS_USHI1,
	_3DG_SGX540,
	CMT1_CMT10, CMT1_CMT11, CMT1_CMT12, CMT1_CMT13, CMT2, CMT3,
	KEYSC_KEY,
	SCIFA0, SCIFA1, SCIFA2, SCIFA3,
	MSIOF2, MSIOF1,
	SCIFA4, SCIFA5, SCIFB,
	FLCTL_FLSTEI, FLCTL_FLTENDI, FLCTL_FLTREQ0I, FLCTL_FLTREQ1I,
	SDHI0,
	SDHI1,
	MSU_MSU, MSU_MSU2,
	IRREM,
	MSUG,
	IRDA,
	TPU0, TPU1, TPU2, TPU3, TPU4,
	LCRC,
	PINTCA_PINT1, PINTCA_PINT2,
	TTI20,
	MISTY,
	DDM,
	RWDT0, RWDT1,
	DMAC_1_DEI0, DMAC_1_DEI1, DMAC_1_DEI2, DMAC_1_DEI3,
	DMAC_2_DEI4, DMAC_2_DEI5, DMAC_2_DADERR,
	DMAC2_1_DEI0, DMAC2_1_DEI1, DMAC2_1_DEI2, DMAC2_1_DEI3,
	DMAC2_2_DEI4, DMAC2_2_DEI5, DMAC2_2_DADERR,
	DMAC3_1_DEI0, DMAC3_1_DEI1, DMAC3_1_DEI2, DMAC3_1_DEI3,
	DMAC3_2_DEI4, DMAC3_2_DEI5, DMAC3_2_DADERR,
	SHWYSTAT_RT, SHWYSTAT_HS, SHWYSTAT_COM,
	ICUSB_ICUSB0, ICUSB_ICUSB1,
	ICUDMC_ICUDMC1, ICUDMC_ICUDMC2,
	SPU2_SPU0, SPU2_SPU1,
	FSI,
	FMSI,
	SCUV,
	IPMMU_IPMMUB,
	AP_ARM_CTIIRQ, AP_ARM_DMAEXTERRIRQ, AP_ARM_DMAIRQ, AP_ARM_DMASIRQ,
	MFIS2,
	CPORTR2S,
	CMT14, CMT15,
	SCIFA6,

	/* interrupt groups INTCA */
	DMAC_1, DMAC_2,	DMAC2_1, DMAC2_2, DMAC3_1, DMAC3_2, SHWYSTAT,
	AP_ARM1, AP_ARM2, USBHS, SPU2, FLCTL, IIC1,
	ICUSB, ICUDMC
};

static struct intc_vect intca_vectors[] __initdata = {
	INTC_VECT(IRQ0A, 0x0200), INTC_VECT(IRQ1A, 0x0220),
	INTC_VECT(IRQ2A, 0x0240), INTC_VECT(IRQ3A, 0x0260),
	INTC_VECT(IRQ4A, 0x0280), INTC_VECT(IRQ5A, 0x02a0),
	INTC_VECT(IRQ6A, 0x02c0), INTC_VECT(IRQ7A, 0x02e0),
	INTC_VECT(IRQ8A, 0x0300), INTC_VECT(IRQ9A, 0x0320),
	INTC_VECT(IRQ10A, 0x0340), INTC_VECT(IRQ11A, 0x0360),
	INTC_VECT(IRQ12A, 0x0380), INTC_VECT(IRQ13A, 0x03a0),
	INTC_VECT(IRQ14A, 0x03c0), INTC_VECT(IRQ15A, 0x03e0),
	INTC_VECT(IRQ16A, 0x3200), INTC_VECT(IRQ17A, 0x3220),
	INTC_VECT(IRQ18A, 0x3240), INTC_VECT(IRQ19A, 0x3260),
	INTC_VECT(IRQ20A, 0x3280), INTC_VECT(IRQ31A, 0x32a0),
	INTC_VECT(IRQ22A, 0x32c0), INTC_VECT(IRQ23A, 0x32e0),
	INTC_VECT(IRQ24A, 0x3300), INTC_VECT(IRQ25A, 0x3320),
	INTC_VECT(IRQ26A, 0x3340), INTC_VECT(IRQ27A, 0x3360),
	INTC_VECT(IRQ28A, 0x3380), INTC_VECT(IRQ29A, 0x33a0),
	INTC_VECT(IRQ30A, 0x33c0), INTC_VECT(IRQ31A, 0x33e0),
	INTC_VECT(DIRC, 0x0560),
	INTC_VECT(_2DG, 0x05e0),
	INTC_VECT(CRYPT_STD, 0x0700),
	INTC_VECT(IIC1_ALI1, 0x0780), INTC_VECT(IIC1_TACKI1, 0x07a0),
	INTC_VECT(IIC1_WAITI1, 0x07c0), INTC_VECT(IIC1_DTEI1, 0x07e0),
	INTC_VECT(AP_ARM_IRQPMU, 0x0800), INTC_VECT(AP_ARM_COMMTX, 0x0840),
	INTC_VECT(AP_ARM_COMMRX, 0x0860),
	INTC_VECT(MFI_MFIM, 0x0900), INTC_VECT(MFI_MFIS, 0x0920),
	INTC_VECT(BBIF1, 0x0940), INTC_VECT(BBIF2, 0x0960),
	INTC_VECT(USBDMAC_USHDMI, 0x0a00),
	INTC_VECT(USBHS_USHI0, 0x0a20), INTC_VECT(USBHS_USHI1, 0x0a40),
	INTC_VECT(_3DG_SGX540, 0x0a60),
	INTC_VECT(CMT1_CMT10, 0x0b00), INTC_VECT(CMT1_CMT11, 0x0b20),
	INTC_VECT(CMT1_CMT12, 0x0b40), INTC_VECT(CMT1_CMT13, 0x0b60),
	INTC_VECT(CMT2, 0x0b80), INTC_VECT(CMT3, 0x0ba0),
	INTC_VECT(KEYSC_KEY, 0x0be0),
	INTC_VECT(SCIFA0, 0x0c00), INTC_VECT(SCIFA1, 0x0c20),
	INTC_VECT(SCIFA2, 0x0c40), INTC_VECT(SCIFA3, 0x0c60),
	INTC_VECT(MSIOF2, 0x0c80), INTC_VECT(MSIOF1, 0x0d00),
	INTC_VECT(SCIFA4, 0x0d20), INTC_VECT(SCIFA5, 0x0d40),
	INTC_VECT(SCIFB, 0x0d60),
	INTC_VECT(FLCTL_FLSTEI, 0x0d80), INTC_VECT(FLCTL_FLTENDI, 0x0da0),
	INTC_VECT(FLCTL_FLTREQ0I, 0x0dc0), INTC_VECT(FLCTL_FLTREQ1I, 0x0de0),
	INTC_VECT(SDHI0, 0x0e00), INTC_VECT(SDHI0, 0x0e20),
	INTC_VECT(SDHI0, 0x0e40), INTC_VECT(SDHI0, 0x0e60),
	INTC_VECT(SDHI1, 0x0e80), INTC_VECT(SDHI1, 0x0ea0),
	INTC_VECT(SDHI1, 0x0ec0), INTC_VECT(SDHI1, 0x0ee0),
	INTC_VECT(MSU_MSU, 0x0f20), INTC_VECT(MSU_MSU2, 0x0f40),
	INTC_VECT(IRREM, 0x0f60),
	INTC_VECT(MSUG, 0x0fa0),
	INTC_VECT(IRDA, 0x0480),
	INTC_VECT(TPU0, 0x04a0), INTC_VECT(TPU1, 0x04c0),
	INTC_VECT(TPU2, 0x04e0), INTC_VECT(TPU3, 0x0500),
	INTC_VECT(TPU4, 0x0520),
	INTC_VECT(LCRC, 0x0540),
	INTC_VECT(PINTCA_PINT1, 0x1000), INTC_VECT(PINTCA_PINT2, 0x1020),
	INTC_VECT(TTI20, 0x1100),
	INTC_VECT(MISTY, 0x1120),
	INTC_VECT(DDM, 0x1140),
	INTC_VECT(RWDT0, 0x1280), INTC_VECT(RWDT1, 0x12a0),
	INTC_VECT(DMAC_1_DEI0, 0x2000), INTC_VECT(DMAC_1_DEI1, 0x2020),
	INTC_VECT(DMAC_1_DEI2, 0x2040), INTC_VECT(DMAC_1_DEI3, 0x2060),
	INTC_VECT(DMAC_2_DEI4, 0x2080), INTC_VECT(DMAC_2_DEI5, 0x20a0),
	INTC_VECT(DMAC_2_DADERR, 0x20c0),
	INTC_VECT(DMAC2_1_DEI0, 0x2100), INTC_VECT(DMAC2_1_DEI1, 0x2120),
	INTC_VECT(DMAC2_1_DEI2, 0x2140), INTC_VECT(DMAC2_1_DEI3, 0x2160),
	INTC_VECT(DMAC2_2_DEI4, 0x2180), INTC_VECT(DMAC2_2_DEI5, 0x21a0),
	INTC_VECT(DMAC2_2_DADERR, 0x21c0),
	INTC_VECT(DMAC3_1_DEI0, 0x2200), INTC_VECT(DMAC3_1_DEI1, 0x2220),
	INTC_VECT(DMAC3_1_DEI2, 0x2240), INTC_VECT(DMAC3_1_DEI3, 0x2260),
	INTC_VECT(DMAC3_2_DEI4, 0x2280), INTC_VECT(DMAC3_2_DEI5, 0x22a0),
	INTC_VECT(DMAC3_2_DADERR, 0x22c0),
	INTC_VECT(SHWYSTAT_RT, 0x1300), INTC_VECT(SHWYSTAT_HS, 0x1d20),
	INTC_VECT(SHWYSTAT_COM, 0x1340),
	INTC_VECT(ICUSB_ICUSB0, 0x1700), INTC_VECT(ICUSB_ICUSB1, 0x1720),
	INTC_VECT(ICUDMC_ICUDMC1, 0x1780), INTC_VECT(ICUDMC_ICUDMC2, 0x17a0),
	INTC_VECT(SPU2_SPU0, 0x1800), INTC_VECT(SPU2_SPU1, 0x1820),
	INTC_VECT(FSI, 0x1840),
	INTC_VECT(FMSI, 0x1860),
	INTC_VECT(SCUV, 0x1880),
	INTC_VECT(IPMMU_IPMMUB, 0x1900),
	INTC_VECT(AP_ARM_CTIIRQ, 0x1980),
	INTC_VECT(AP_ARM_DMAEXTERRIRQ, 0x19a0),
	INTC_VECT(AP_ARM_DMAIRQ, 0x19c0),
	INTC_VECT(AP_ARM_DMASIRQ, 0x19e0),
	INTC_VECT(MFIS2, 0x1a00),
	INTC_VECT(CPORTR2S, 0x1a20),
	INTC_VECT(CMT14, 0x1a40), INTC_VECT(CMT15, 0x1a60),
	INTC_VECT(SCIFA6, 0x1a80),
};

static struct intc_group intca_groups[] __initdata = {
	INTC_GROUP(DMAC_1, DMAC_1_DEI0,
		   DMAC_1_DEI1, DMAC_1_DEI2, DMAC_1_DEI3),
	INTC_GROUP(DMAC_2, DMAC_2_DEI4,
		   DMAC_2_DEI5, DMAC_2_DADERR),
	INTC_GROUP(DMAC2_1, DMAC2_1_DEI0,
		   DMAC2_1_DEI1, DMAC2_1_DEI2, DMAC2_1_DEI3),
	INTC_GROUP(DMAC2_2, DMAC2_2_DEI4,
		   DMAC2_2_DEI5, DMAC2_2_DADERR),
	INTC_GROUP(DMAC3_1, DMAC3_1_DEI0,
		   DMAC3_1_DEI1, DMAC3_1_DEI2, DMAC3_1_DEI3),
	INTC_GROUP(DMAC3_2, DMAC3_2_DEI4,
		   DMAC3_2_DEI5, DMAC3_2_DADERR),
	INTC_GROUP(AP_ARM1, AP_ARM_IRQPMU, AP_ARM_COMMTX, AP_ARM_COMMTX),
	INTC_GROUP(USBHS, USBHS_USHI0, USBHS_USHI1),
	INTC_GROUP(SPU2, SPU2_SPU0, SPU2_SPU1),
	INTC_GROUP(FLCTL, FLCTL_FLSTEI, FLCTL_FLTENDI,
		   FLCTL_FLTREQ0I, FLCTL_FLTREQ1I),
	INTC_GROUP(IIC1, IIC1_ALI1, IIC1_TACKI1, IIC1_WAITI1, IIC1_DTEI1),
	INTC_GROUP(SHWYSTAT, SHWYSTAT_RT, SHWYSTAT_HS, SHWYSTAT_COM),
	INTC_GROUP(ICUSB, ICUSB_ICUSB0, ICUSB_ICUSB1),
	INTC_GROUP(ICUDMC, ICUDMC_ICUDMC1, ICUDMC_ICUDMC2),
};

static struct intc_mask_reg intca_mask_registers[] __initdata = {
	{ 0xe6900040, 0xe6900060, 8, /* INTMSK00A / INTMSKCLR00A */
	  { IRQ0A, IRQ1A, IRQ2A, IRQ3A, IRQ4A, IRQ5A, IRQ6A, IRQ7A } },
	{ 0xe6900044, 0xe6900064, 8, /* INTMSK10A / INTMSKCLR10A */
	  { IRQ8A, IRQ9A, IRQ10A, IRQ11A, IRQ12A, IRQ13A, IRQ14A, IRQ15A } },
	{ 0xe6900048, 0xe6900068, 8, /* INTMSK20A / INTMSKCLR20A */
	  { IRQ16A, IRQ17A, IRQ18A, IRQ19A, IRQ20A, IRQ21A, IRQ22A, IRQ23A } },
	{ 0xe690004c, 0xe690006c, 8, /* INTMSK30A / INTMSKCLR30A */
	  { IRQ24A, IRQ25A, IRQ26A, IRQ27A, IRQ28A, IRQ29A, IRQ30A, IRQ31A } },

	{ 0xe6940080, 0xe69400c0, 8, /* IMR0A / IMCR0A */
	  { DMAC2_1_DEI3, DMAC2_1_DEI2, DMAC2_1_DEI1, DMAC2_1_DEI0,
	    AP_ARM_IRQPMU, 0, AP_ARM_COMMTX, AP_ARM_COMMRX } },
	{ 0xe6940084, 0xe69400c4, 8, /* IMR1A / IMCR1A */
	  { _2DG, CRYPT_STD, DIRC, 0,
	    DMAC_1_DEI3, DMAC_1_DEI2, DMAC_1_DEI1, DMAC_1_DEI0 } },
	{ 0xe6940088, 0xe69400c8, 8, /* IMR2A / IMCR2A */
	  { PINTCA_PINT1, PINTCA_PINT2, 0, 0,
	    BBIF1, BBIF2, MFI_MFIS, MFI_MFIM } },
	{ 0xe694008c, 0xe69400cc, 8, /* IMR3A / IMCR3A */
	  { DMAC3_1_DEI3, DMAC3_1_DEI2, DMAC3_1_DEI1, DMAC3_1_DEI0,
	    DMAC3_2_DADERR, DMAC3_2_DEI5, DMAC3_2_DEI4, IRDA } },
	{ 0xe6940090, 0xe69400d0, 8, /* IMR4A / IMCR4A */
	  { DDM, 0, 0, 0,
	    0, 0, 0, 0 } },
	{ 0xe6940094, 0xe69400d4, 8, /* IMR5A / IMCR5A */
	  { KEYSC_KEY, DMAC_2_DADERR, DMAC_2_DEI5, DMAC_2_DEI4,
	    SCIFA3, SCIFA2, SCIFA1, SCIFA0 } },
	{ 0xe6940098, 0xe69400d8, 8, /* IMR6A / IMCR6A */
	  { SCIFB, SCIFA5, SCIFA4, MSIOF1,
	    0, 0, MSIOF2, 0 } },
	{ 0xe694009c, 0xe69400dc, 8, /* IMR7A / IMCR7A */
	  { DISABLED, DISABLED, ENABLED, ENABLED,
	    FLCTL_FLTREQ1I, FLCTL_FLTREQ0I, FLCTL_FLTENDI, FLCTL_FLSTEI } },
	{ 0xe69400a0, 0xe69400e0, 8, /* IMR8A / IMCR8A */
	  { DISABLED, DISABLED, ENABLED, ENABLED,
	    TTI20, USBDMAC_USHDMI, 0, MSUG } },
	{ 0xe69400a4, 0xe69400e4, 8, /* IMR9A / IMCR9A */
	  { CMT1_CMT13, CMT1_CMT12, CMT1_CMT11, CMT1_CMT10,
	    CMT2, USBHS_USHI1, USBHS_USHI0, _3DG_SGX540 } },
	{ 0xe69400a8, 0xe69400e8, 8, /* IMR10A / IMCR10A */
	  { 0, DMAC2_2_DADERR, DMAC2_2_DEI5, DMAC2_2_DEI4,
	    0, 0, 0, 0 } },
	{ 0xe69400ac, 0xe69400ec, 8, /* IMR11A / IMCR11A */
	  { IIC1_DTEI1, IIC1_WAITI1, IIC1_TACKI1, IIC1_ALI1,
	    LCRC, MSU_MSU2, IRREM, MSU_MSU } },
	{ 0xe69400b0, 0xe69400f0, 8, /* IMR12A / IMCR12A */
	  { 0, 0, TPU0, TPU1,
	    TPU2, TPU3, TPU4, 0 } },
	{ 0xe69400b4, 0xe69400f4, 8, /* IMR13A / IMCR13A */
	  { 0, 0, 0, 0,
	    MISTY, CMT3, RWDT1, RWDT0 } },
	{ 0xe6950080, 0xe69500c0, 8, /* IMR0A3 / IMCR0A3 */
	  { SHWYSTAT_RT, SHWYSTAT_HS, SHWYSTAT_COM, 0,
	    0, 0, 0, 0 } },
	{ 0xe6950090, 0xe69500d0, 8, /* IMR4A3 / IMCR4A3 */
	  { ICUSB_ICUSB0, ICUSB_ICUSB1, 0, 0,
	    ICUDMC_ICUDMC1, ICUDMC_ICUDMC2, 0, 0 } },
	{ 0xe6950094, 0xe69500d4, 8, /* IMR5A3 / IMCR5A3 */
	  { SPU2_SPU0, SPU2_SPU1, FSI, FMSI,
	    SCUV, 0, 0, 0 } },
	{ 0xe6950098, 0xe69500d8, 8, /* IMR6A3 / IMCR6A3 */
	  { IPMMU_IPMMUB, 0, 0, 0,
	    AP_ARM_CTIIRQ, AP_ARM_DMAEXTERRIRQ,
	    AP_ARM_DMAIRQ, AP_ARM_DMASIRQ } },
	{ 0xe695009c, 0xe69500dc, 8, /* IMR7A3 / IMCR7A3 */
	  { MFIS2, CPORTR2S, CMT14, CMT15,
	    SCIFA6, 0, 0, 0 } },
};

static struct intc_prio_reg intca_prio_registers[] __initdata = {
	{ 0xe6900010, 0, 32, 4, /* INTPRI00A */
	  { IRQ0A, IRQ1A, IRQ2A, IRQ3A, IRQ4A, IRQ5A, IRQ6A, IRQ7A } },
	{ 0xe6900014, 0, 32, 4, /* INTPRI10A */
	  { IRQ8A, IRQ9A, IRQ10A, IRQ11A, IRQ12A, IRQ13A, IRQ14A, IRQ15A } },
	{ 0xe6900018, 0, 32, 4, /* INTPRI10A */
	  { IRQ16A, IRQ17A, IRQ18A, IRQ19A, IRQ20A, IRQ21A, IRQ22A, IRQ23A } },
	{ 0xe690001c, 0, 32, 4, /* INTPRI30A */
	  { IRQ24A, IRQ25A, IRQ26A, IRQ27A, IRQ28A, IRQ29A, IRQ30A, IRQ31A } },

	{ 0xe6940000, 0, 16, 4, /* IPRAA */ { DMAC3_1, DMAC3_2, CMT2, LCRC } },
	{ 0xe6940004, 0, 16, 4, /* IPRBA */ { IRDA, 0, BBIF1, BBIF2 } },
	{ 0xe6940008, 0, 16, 4, /* IPRCA */ { _2DG, CRYPT_STD,
					      CMT1_CMT11, AP_ARM1 } },
	{ 0xe694000c, 0, 16, 4, /* IPRDA */ { PINTCA_PINT1, PINTCA_PINT2,
					      CMT1_CMT12, TPU4 } },
	{ 0xe6940010, 0, 16, 4, /* IPREA */ { DMAC_1, MFI_MFIS,
					      MFI_MFIM, USBHS } },
	{ 0xe6940014, 0, 16, 4, /* IPRFA */ { KEYSC_KEY, DMAC_2,
					      _3DG_SGX540, CMT1_CMT10 } },
	{ 0xe6940018, 0, 16, 4, /* IPRGA */ { SCIFA0, SCIFA1,
					      SCIFA2, SCIFA3 } },
	{ 0xe694001c, 0, 16, 4, /* IPRGH */ { MSIOF2, USBDMAC_USHDMI,
					      FLCTL, SDHI0 } },
	{ 0xe6940020, 0, 16, 4, /* IPRIA */ { MSIOF1, SCIFA4, MSU_MSU, IIC1 } },
	{ 0xe6940024, 0, 16, 4, /* IPRJA */ { DMAC2_1, DMAC2_2, MSUG, TTI20 } },
	{ 0xe6940028, 0, 16, 4, /* IPRKA */ { 0, CMT1_CMT13, IRREM, SDHI1 } },
	{ 0xe694002c, 0, 16, 4, /* IPRLA */ { TPU0, TPU1, TPU2, TPU3 } },
	{ 0xe6940030, 0, 16, 4, /* IPRMA */ { MISTY, CMT3, RWDT1, RWDT0 } },
	{ 0xe6940034, 0, 16, 4, /* IPRNA */ { SCIFB, SCIFA5, 0, DDM } },
	{ 0xe6940038, 0, 16, 4, /* IPROA */ { 0, 0, DIRC, 0 } },
	{ 0xe6950000, 0, 16, 4, /* IPRAA3 */ { SHWYSTAT, 0, 0, 0 } },
	{ 0xe6950020, 0, 16, 4, /* IPRIA3 */ { ICUSB, 0, 0, 0 } },
	{ 0xe6950024, 0, 16, 4, /* IPRJA3 */ { ICUDMC, 0, 0, 0 } },
	{ 0xe6950028, 0, 16, 4, /* IPRKA3 */ { SPU2, 0, FSI, FMSI } },
	{ 0xe695002c, 0, 16, 4, /* IPRLA3 */ { SCUV, 0, 0, 0 } },
	{ 0xe6950030, 0, 16, 4, /* IPRMA3 */ { IPMMU_IPMMUB, 0, 0, 0 } },
	{ 0xe6950034, 0, 16, 4, /* IPRNA3 */ { AP_ARM2, 0, 0, 0 } },
	{ 0xe6950038, 0, 16, 4, /* IPROA3 */ { MFIS2, CPORTR2S,
					       CMT14, CMT15 } },
	{ 0xe694003c, 0, 16, 4, /* IPRPA3 */ { SCIFA6, 0, 0, 0 } },
};

static struct intc_sense_reg intca_sense_registers[] __initdata = {
	{ 0xe6900000, 16, 2, /* ICR1A */
	  { IRQ0A, IRQ1A, IRQ2A, IRQ3A, IRQ4A, IRQ5A, IRQ6A, IRQ7A } },
	{ 0xe6900004, 16, 2, /* ICR2A */
	  { IRQ8A, IRQ9A, IRQ10A, IRQ11A, IRQ12A, IRQ13A, IRQ14A, IRQ15A } },
	{ 0xe6900008, 16, 2, /* ICR3A */
	  { IRQ16A, IRQ17A, IRQ18A, IRQ19A, IRQ20A, IRQ21A, IRQ22A, IRQ23A } },
	{ 0xe690000c, 16, 2, /* ICR4A */
	  { IRQ24A, IRQ25A, IRQ26A, IRQ27A, IRQ28A, IRQ29A, IRQ30A, IRQ31A } },
};

static struct intc_mask_reg intca_ack_registers[] __initdata = {
	{ 0xe6900020, 0, 8, /* INTREQ00A */
	  { IRQ0A, IRQ1A, IRQ2A, IRQ3A, IRQ4A, IRQ5A, IRQ6A, IRQ7A } },
	{ 0xe6900024, 0, 8, /* INTREQ10A */
	  { IRQ8A, IRQ9A, IRQ10A, IRQ11A, IRQ12A, IRQ13A, IRQ14A, IRQ15A } },
	{ 0xe6900028, 0, 8, /* INTREQ20A */
	  { IRQ16A, IRQ17A, IRQ18A, IRQ19A, IRQ20A, IRQ21A, IRQ22A, IRQ23A } },
	{ 0xe690002c, 0, 8, /* INTREQ30A */
	  { IRQ24A, IRQ25A, IRQ26A, IRQ27A, IRQ28A, IRQ29A, IRQ30A, IRQ31A } },
};

static struct intc_desc intca_desc __initdata = {
	.name = "sh7377-intca",
	.force_enable = ENABLED,
	.force_disable = DISABLED,
	.hw = INTC_HW_DESC(intca_vectors, intca_groups,
			   intca_mask_registers, intca_prio_registers,
			   intca_sense_registers, intca_ack_registers),
};

/* this macro ignore entry which is also in INTCA */
#define __IGNORE(a...)
#define __IGNORE0(a...) 0

enum {
	UNUSED_INTCS = 0,

	INTCS,

	/* interrupt sources INTCS */
	VEU_VEU0, VEU_VEU1, VEU_VEU2, VEU_VEU3,
	RTDMAC1_1_DEI0, RTDMAC1_1_DEI1, RTDMAC1_1_DEI2, RTDMAC1_1_DEI3,
	CEU,
	BEU_BEU0, BEU_BEU1, BEU_BEU2,
	__IGNORE(MFI)
	__IGNORE(BBIF2)
	VPU,
	TSIF1,
	__IGNORE(SGX540)
	_2DDMAC,
	IIC2_ALI2, IIC2_TACKI2, IIC2_WAITI2, IIC2_DTEI2,
	IPMMU_IPMMUR, IPMMU_IPMMUR2,
	RTDMAC1_2_DEI4, RTDMAC1_2_DEI5, RTDMAC1_2_DADERR,
	__IGNORE(KEYSC)
	__IGNORE(TTI20)
	__IGNORE(MSIOF)
	IIC0_ALI0, IIC0_TACKI0, IIC0_WAITI0, IIC0_DTEI0,
	TMU_TUNI0, TMU_TUNI1, TMU_TUNI2,
	CMT0,
	TSIF0,
	__IGNORE(CMT2)
	LMB,
	__IGNORE(MSUG)
	__IGNORE(MSU_MSU, MSU_MSU2)
	__IGNORE(CTI)
	MVI3,
	__IGNORE(RWDT0)
	__IGNORE(RWDT1)
	ICB,
	PEP,
	ASA,
	__IGNORE(_2DG)
	HQE,
	JPU,
	LCDC0,
	__IGNORE(LCRC)
	RTDMAC2_1_DEI0, RTDMAC2_1_DEI1, RTDMAC2_1_DEI2, RTDMAC2_1_DEI3,
	RTDMAC2_2_DEI4, RTDMAC2_2_DEI5, RTDMAC2_2_DADERR,
	FRC,
	LCDC1,
	CSIRX,
	DSITX_DSITX0, DSITX_DSITX1,
	__IGNORE(SPU2_SPU0, SPU2_SPU1)
	__IGNORE(FSI)
	__IGNORE(FMSI)
	__IGNORE(SCUV)
	TMU1_TUNI10, TMU1_TUNI11, TMU1_TUNI12,
	TSIF2,
	CMT4,
	__IGNORE(MFIS2)
	CPORTS2R,

	/* interrupt groups INTCS */
	RTDMAC1_1, RTDMAC1_2, VEU, BEU, IIC0, __IGNORE(MSU) IPMMU,
	IIC2, RTDMAC2_1, RTDMAC2_2, DSITX, __IGNORE(SPU2) TMU1,
};

#define INTCS_INTVECT 0x0F80
static struct intc_vect intcs_vectors[] __initdata = {
	INTCS_VECT(VEU_VEU0, 0x0700), INTCS_VECT(VEU_VEU1, 0x0720),
	INTCS_VECT(VEU_VEU2, 0x0740), INTCS_VECT(VEU_VEU3, 0x0760),
	INTCS_VECT(RTDMAC1_1_DEI0, 0x0800), INTCS_VECT(RTDMAC1_1_DEI1, 0x0820),
	INTCS_VECT(RTDMAC1_1_DEI2, 0x0840), INTCS_VECT(RTDMAC1_1_DEI3, 0x0860),
	INTCS_VECT(CEU, 0x0880),
	INTCS_VECT(BEU_BEU0, 0x08A0),
	INTCS_VECT(BEU_BEU1, 0x08C0),
	INTCS_VECT(BEU_BEU2, 0x08E0),
	__IGNORE(INTCS_VECT(MFI, 0x0900))
	__IGNORE(INTCS_VECT(BBIF2, 0x0960))
	INTCS_VECT(VPU, 0x0980),
	INTCS_VECT(TSIF1, 0x09A0),
	__IGNORE(INTCS_VECT(SGX540, 0x09E0))
	INTCS_VECT(_2DDMAC, 0x0A00),
	INTCS_VECT(IIC2_ALI2, 0x0A80), INTCS_VECT(IIC2_TACKI2, 0x0AA0),
	INTCS_VECT(IIC2_WAITI2, 0x0AC0), INTCS_VECT(IIC2_DTEI2, 0x0AE0),
	INTCS_VECT(IPMMU_IPMMUR, 0x0B00), INTCS_VECT(IPMMU_IPMMUR2, 0x0B20),
	INTCS_VECT(RTDMAC1_2_DEI4, 0x0B80),
	INTCS_VECT(RTDMAC1_2_DEI5, 0x0BA0),
	INTCS_VECT(RTDMAC1_2_DADERR, 0x0BC0),
	__IGNORE(INTCS_VECT(KEYSC 0x0BE0))
	__IGNORE(INTCS_VECT(TTI20, 0x0C80))
	__IGNORE(INTCS_VECT(MSIOF, 0x0D20))
	INTCS_VECT(IIC0_ALI0, 0x0E00), INTCS_VECT(IIC0_TACKI0, 0x0E20),
	INTCS_VECT(IIC0_WAITI0, 0x0E40), INTCS_VECT(IIC0_DTEI0, 0x0E60),
	INTCS_VECT(TMU_TUNI0, 0x0E80),
	INTCS_VECT(TMU_TUNI1, 0x0EA0),
	INTCS_VECT(TMU_TUNI2, 0x0EC0),
	INTCS_VECT(CMT0, 0x0F00),
	INTCS_VECT(TSIF0, 0x0F20),
	__IGNORE(INTCS_VECT(CMT2, 0x0F40))
	INTCS_VECT(LMB, 0x0F60),
	__IGNORE(INTCS_VECT(MSUG, 0x0F80))
	__IGNORE(INTCS_VECT(MSU_MSU, 0x0FA0))
	__IGNORE(INTCS_VECT(MSU_MSU2, 0x0FC0))
	__IGNORE(INTCS_VECT(CTI, 0x0400))
	INTCS_VECT(MVI3, 0x0420),
	__IGNORE(INTCS_VECT(RWDT0, 0x0440))
	__IGNORE(INTCS_VECT(RWDT1, 0x0460))
	INTCS_VECT(ICB, 0x0480),
	INTCS_VECT(PEP, 0x04A0),
	INTCS_VECT(ASA, 0x04C0),
	__IGNORE(INTCS_VECT(_2DG, 0x04E0))
	INTCS_VECT(HQE, 0x0540),
	INTCS_VECT(JPU, 0x0560),
	INTCS_VECT(LCDC0, 0x0580),
	__IGNORE(INTCS_VECT(LCRC, 0x05A0))
	INTCS_VECT(RTDMAC2_1_DEI0, 0x1300), INTCS_VECT(RTDMAC2_1_DEI1, 0x1320),
	INTCS_VECT(RTDMAC2_1_DEI2, 0x1340), INTCS_VECT(RTDMAC2_1_DEI3, 0x1360),
	INTCS_VECT(RTDMAC2_2_DEI4, 0x1380), INTCS_VECT(RTDMAC2_2_DEI5, 0x13A0),
	INTCS_VECT(RTDMAC2_2_DADERR, 0x13C0),
	INTCS_VECT(FRC, 0x1700),
	INTCS_VECT(LCDC1, 0x1780),
	INTCS_VECT(CSIRX, 0x17A0),
	INTCS_VECT(DSITX_DSITX0, 0x17C0), INTCS_VECT(DSITX_DSITX1, 0x17E0),
	__IGNORE(INTCS_VECT(SPU2_SPU0, 0x1800))
	__IGNORE(INTCS_VECT(SPU2_SPU1, 0x1820))
	__IGNORE(INTCS_VECT(FSI, 0x1840))
	__IGNORE(INTCS_VECT(FMSI, 0x1860))
	__IGNORE(INTCS_VECT(SCUV, 0x1880))
	INTCS_VECT(TMU1_TUNI10, 0x1900), INTCS_VECT(TMU1_TUNI11, 0x1920),
	INTCS_VECT(TMU1_TUNI12, 0x1940),
	INTCS_VECT(TSIF2, 0x1960),
	INTCS_VECT(CMT4, 0x1980),
	__IGNORE(INTCS_VECT(MFIS2, 0x1A00))
	INTCS_VECT(CPORTS2R, 0x1A20),

	INTC_VECT(INTCS, INTCS_INTVECT),
};

static struct intc_group intcs_groups[] __initdata = {
	INTC_GROUP(RTDMAC1_1,
		   RTDMAC1_1_DEI0, RTDMAC1_1_DEI1,
		   RTDMAC1_1_DEI2, RTDMAC1_1_DEI3),
	INTC_GROUP(RTDMAC1_2,
		   RTDMAC1_2_DEI4, RTDMAC1_2_DEI5, RTDMAC1_2_DADERR),
	INTC_GROUP(VEU, VEU_VEU0, VEU_VEU1, VEU_VEU2, VEU_VEU3),
	INTC_GROUP(BEU, BEU_BEU0, BEU_BEU1, BEU_BEU2),
	INTC_GROUP(IIC0, IIC0_ALI0, IIC0_TACKI0, IIC0_WAITI0, IIC0_DTEI0),
	__IGNORE(INTC_GROUP(MSU, MSU_MSU, MSU_MSU2))
	INTC_GROUP(IPMMU, IPMMU_IPMMUR, IPMMU_IPMMUR2),
	INTC_GROUP(IIC2, IIC2_ALI2, IIC2_TACKI2, IIC2_WAITI2, IIC2_DTEI2),
	INTC_GROUP(RTDMAC2_1,
		   RTDMAC2_1_DEI0, RTDMAC2_1_DEI1,
		   RTDMAC2_1_DEI2, RTDMAC2_1_DEI3),
	INTC_GROUP(RTDMAC2_2, RTDMAC2_2_DEI4, RTDMAC2_2_DEI5, RTDMAC2_2_DADERR),
	INTC_GROUP(DSITX, DSITX_DSITX0, DSITX_DSITX1),
	__IGNORE(INTC_GROUP(SPU2, SPU2_SPU0, SPU2_SPU1))
	INTC_GROUP(TMU1, TMU1_TUNI10, TMU1_TUNI11, TMU1_TUNI12),
};

static struct intc_mask_reg intcs_mask_registers[] __initdata = {
	{ 0xE6940184, 0xE69401C4, 8, /* IMR1AS / IMCR1AS  */
	  { BEU_BEU2, BEU_BEU1, BEU_BEU0, CEU,
	    VEU_VEU3, VEU_VEU2, VEU_VEU1, VEU_VEU0 } },
	{ 0xE6940188, 0xE69401C8, 8, /* IMR2AS / IMCR2AS */
	  { 0, 0, 0, VPU,
	    __IGNORE0(BBIF2), 0, 0, __IGNORE0(MFI) } },
	{ 0xE694018C, 0xE69401CC, 8, /* IMR3AS / IMCR3AS */
	  { 0, 0, 0, _2DDMAC,
	    __IGNORE0(_2DG), ASA, PEP, ICB } },
	{ 0xE6940190, 0xE69401D0, 8, /* IMR4AS / IMCR4AS */
	  { 0, 0, MVI3, __IGNORE0(CTI),
	    JPU, HQE, __IGNORE0(LCRC), LCDC0 } },
	{ 0xE6940194, 0xE69401D4, 8, /* IMR5AS / IMCR5AS */
	  { __IGNORE0(KEYSC), RTDMAC1_2_DADERR, RTDMAC1_2_DEI5, RTDMAC1_2_DEI4,
	    RTDMAC1_1_DEI3, RTDMAC1_1_DEI2, RTDMAC1_1_DEI1, RTDMAC1_1_DEI0 } },
	__IGNORE({ 0xE6940198, 0xE69401D8, 8, /* IMR6AS / IMCR6AS */
	  { 0, 0, MSIOF, 0,
	    SGX540, 0, TTI20, 0 } })
	{ 0xE694019C, 0xE69401DC, 8, /* IMR7AS / IMCR7AS */
	  { 0, TMU_TUNI2, TMU_TUNI1, TMU_TUNI0,
	    0, 0, 0, 0 } },
	__IGNORE({ 0xE69401A0, 0xE69401E0, 8, /* IMR8AS / IMCR8AS */
	  { 0, 0, 0, 0,
	    0, MSU_MSU, MSU_MSU2, MSUG } })
	{ 0xE69401A4, 0xE69401E4, 8, /* IMR9AS / IMCR9AS */
	  { __IGNORE0(RWDT1), __IGNORE0(RWDT0), __IGNORE0(CMT2), CMT0,
	    IIC2_DTEI2, IIC2_WAITI2, IIC2_TACKI2, IIC2_ALI2 } },
	{ 0xE69401A8, 0xE69401E8, 8, /* IMR10AS / IMCR10AS */
	  { 0, 0, IPMMU_IPMMUR, IPMMU_IPMMUR2,
	    0, 0, 0, 0 } },
	{ 0xE69401AC, 0xE69401EC, 8, /* IMR11AS / IMCR11AS */
	  { IIC0_DTEI0, IIC0_WAITI0, IIC0_TACKI0, IIC0_ALI0,
	    0, TSIF1, LMB, TSIF0 } },
	{ 0xE6950180, 0xE69501C0, 8, /* IMR0AS3 / IMCR0AS3 */
	  { RTDMAC2_1_DEI0, RTDMAC2_1_DEI1, RTDMAC2_1_DEI2, RTDMAC2_1_DEI3,
	    RTDMAC2_2_DEI4, RTDMAC2_2_DEI5, RTDMAC2_2_DADERR, 0 } },
	{ 0xE6950190, 0xE69501D0, 8, /* IMR4AS3 / IMCR4AS3 */
	  { FRC, 0, 0, 0,
	    LCDC1, CSIRX, DSITX_DSITX0, DSITX_DSITX1 } },
	__IGNORE({ 0xE6950194, 0xE69501D4, 8, /* IMR5AS3 / IMCR5AS3 */
	  {SPU2_SPU0, SPU2_SPU1, FSI, FMSI,
	   SCUV, 0, 0, 0 } })
	{ 0xE6950198, 0xE69501D8, 8, /* IMR6AS3 / IMCR6AS3 */
	  { TMU1_TUNI10, TMU1_TUNI11, TMU1_TUNI12, TSIF2,
	    CMT4, 0, 0, 0 } },
	{ 0xE695019C, 0xE69501DC, 8, /* IMR7AS3 / IMCR7AS3 */
	  { __IGNORE0(MFIS2), CPORTS2R, 0, 0,
	    0, 0, 0, 0 } },
	{ 0xFFD20104, 0, 16, /* INTAMASK */
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, INTCS } }
};

static struct intc_prio_reg intcs_prio_registers[] __initdata = {
	/* IPRAS */
	{ 0xFFD20000, 0, 16, 4, { __IGNORE0(CTI), MVI3, _2DDMAC, ICB } },
	/* IPRBS */
	{ 0xFFD20004, 0, 16, 4, { JPU, LCDC0, 0, __IGNORE0(LCRC) } },
	/* IPRCS */
	__IGNORE({ 0xFFD20008, 0, 16, 4, { BBIF2, 0, 0, 0 } })
	/* IPRES */
	{ 0xFFD20010, 0, 16, 4, { RTDMAC1_1, CEU, __IGNORE0(MFI), VPU } },
	/* IPRFS */
	{ 0xFFD20014, 0, 16, 4,
	  { __IGNORE0(KEYSC), RTDMAC1_2, __IGNORE0(CMT2), CMT0 } },
	/* IPRGS */
	{ 0xFFD20018, 0, 16, 4, { TMU_TUNI0, TMU_TUNI1, TMU_TUNI2, TSIF1 } },
	/* IPRHS */
	{ 0xFFD2001C, 0, 16, 4, { __IGNORE0(TTI20), 0, VEU, BEU } },
	/* IPRIS */
	{ 0xFFD20020, 0, 16, 4, { 0, __IGNORE0(MSIOF), TSIF0, IIC0 } },
	/* IPRJS */
	__IGNORE({ 0xFFD20024, 0, 16, 4, { 0, SGX540, MSUG, MSU } })
	/* IPRKS */
	{ 0xFFD20028, 0, 16, 4, { __IGNORE0(_2DG), ASA, LMB, PEP } },
	/* IPRLS */
	{ 0xFFD2002C, 0, 16, 4, { IPMMU, 0, 0, HQE } },
	/* IPRMS */
	{ 0xFFD20030, 0, 16, 4,
	  { IIC2, 0, __IGNORE0(RWDT1), __IGNORE0(RWDT0) } },
	/* IPRAS3 */
	{ 0xFFD50000, 0, 16, 4, { RTDMAC2_1, 0, 0, 0 } },
	/* IPRBS3 */
	{ 0xFFD50004, 0, 16, 4, { RTDMAC2_2, 0, 0, 0 } },
	/* IPRIS3 */
	{ 0xFFD50020, 0, 16, 4, { FRC, 0, 0, 0 } },
	/* IPRJS3 */
	{ 0xFFD50024, 0, 16, 4, { LCDC1, CSIRX, DSITX, 0 } },
	/* IPRKS3 */
	__IGNORE({ 0xFFD50028, 0, 16, 4, { SPU2, 0, FSI, FMSI } })
	/* IPRLS3 */
	__IGNORE({ 0xFFD5002C, 0, 16, 4, { SCUV, 0, 0, 0 } })
	/* IPRMS3 */
	{ 0xFFD50030, 0, 16, 4, { TMU1, 0, 0, TSIF2 } },
	/* IPRNS3 */
	{ 0xFFD50034, 0, 16, 4, { CMT4, 0, 0, 0 } },
	/* IPROS3 */
	{ 0xFFD50038, 0, 16, 4, { __IGNORE0(MFIS2), CPORTS2R, 0, 0 } },
};

static struct resource intcs_resources[] __initdata = {
	[0] = {
		.start	= 0xffd20000,
		.end	= 0xffd500ff,
		.flags	= IORESOURCE_MEM,
	}
};

static struct intc_desc intcs_desc __initdata = {
	.name = "sh7377-intcs",
	.resource = intcs_resources,
	.num_resources = ARRAY_SIZE(intcs_resources),
	.hw = INTC_HW_DESC(intcs_vectors, intcs_groups,
			   intcs_mask_registers, intcs_prio_registers,
			   NULL, NULL),
};

static void intcs_demux(unsigned int irq, struct irq_desc *desc)
{
	void __iomem *reg = (void *)get_irq_data(irq);
	unsigned int evtcodeas = ioread32(reg);

	generic_handle_irq(intcs_evt2irq(evtcodeas));
}

#define INTEVTSA 0xFFD20100
void __init sh7377_init_irq(void)
{
	void __iomem *intevtsa = ioremap_nocache(INTEVTSA, PAGE_SIZE);

	register_intc_controller(&intca_desc);
	register_intc_controller(&intcs_desc);

	/* demux using INTEVTSA */
	set_irq_data(evt2irq(INTCS_INTVECT), (void *)intevtsa);
	set_irq_chained_handler(evt2irq(INTCS_INTVECT), intcs_demux);
}

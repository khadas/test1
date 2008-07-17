/*
 * (C) Copyright 2000-2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2002 (440 port)
 * Scott McNutt, Artesyn Communication Producs, smcnutt@artsyncp.com
 *
 * (C) Copyright 2003 (440GX port)
 * Travis B. Sawyer, Sandburst Corporation, tsawyer@sandburst.com
 *
 * (C) Copyright 2008 (PPC440X05 port for Virtex 5 FX)
 * Ricardo Ribalda-Universidad Autonoma de Madrid-ricardo.ribalda@uam.es
 * Work supported by Qtechnology (htpp://qtec.com)
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <asm/processor.h>
#include <asm/interrupt.h>
#include <ppc4xx.h>
#include <ppc_asm.tmpl>
#include <commproc.h>

#if (UIC_MAX > 3)
#define UICB0_ALL	(UIC_MASK(VECNUM_UIC1CI) | UIC_MASK(VECNUM_UIC1NCI) | \
			 UIC_MASK(VECNUM_UIC2CI) | UIC_MASK(VECNUM_UIC2NCI) | \
			 UIC_MASK(VECNUM_UIC3CI) | UIC_MASK(VECNUM_UIC3NCI))
#elif (UIC_MAX > 2)
#define UICB0_ALL	(UIC_MASK(VECNUM_UIC1CI) | UIC_MASK(VECNUM_UIC1NCI) | \
			 UIC_MASK(VECNUM_UIC2CI) | UIC_MASK(VECNUM_UIC2NCI))
#elif (UIC_MAX > 1)
#define UICB0_ALL	(UIC_MASK(VECNUM_UIC1CI) | UIC_MASK(VECNUM_UIC1NCI))
#else
#define UICB0_ALL	0
#endif

u32 get_dcr(u16);

DECLARE_GLOBAL_DATA_PTR;

void pic_enable(void)
{

#if (UIC_MAX > 1)
	/* Install the UIC1 handlers */
	irq_install_handler(VECNUM_UIC1NCI, (void *)(void *)external_interrupt,
			    0);
	irq_install_handler(VECNUM_UIC1CI, (void *)(void *)external_interrupt,
			    0);
#endif
#if (UIC_MAX > 2)
	irq_install_handler(VECNUM_UIC2NCI, (void *)(void *)external_interrupt,
			    0);
	irq_install_handler(VECNUM_UIC2CI, (void *)(void *)external_interrupt,
			    0);
#endif
#if (UIC_MAX > 3)
	irq_install_handler(VECNUM_UIC3NCI, (void *)(void *)external_interrupt,
			    0);
	irq_install_handler(VECNUM_UIC3CI, (void *)(void *)external_interrupt,
			    0);
#endif

}

/* Handler for UIC interrupt */
static void uic_interrupt(u32 uic_base, int vec_base)
{
	u32 uic_msr;
	u32 msr_shift;
	int vec;

	/*
	 * Read masked interrupt status register to determine interrupt source
	 */
	uic_msr = get_dcr(uic_base + UIC_MSR);
	msr_shift = uic_msr;
	vec = vec_base;

	while (msr_shift != 0) {
		if (msr_shift & 0x80000000)
			interrupt_run_handler(vec);
		/*
		 * Shift msr to next position and increment vector
		 */
		msr_shift <<= 1;
		vec++;
	}
}

/*
 * Handle external interrupts
 */
void external_interrupt(struct pt_regs *regs)
{
	u32 uic_msr;

	/*
	 * Read masked interrupt status register to determine interrupt source
	 */
	uic_msr = mfdcr(uic0msr);

#if (UIC_MAX > 1)
	if ((UIC_MASK(VECNUM_UIC1CI) & uic_msr) ||
	    (UIC_MASK(VECNUM_UIC1NCI) & uic_msr))
		uic_interrupt(UIC1_DCR_BASE, 32);
#endif

#if (UIC_MAX > 2)
	if ((UIC_MASK(VECNUM_UIC2CI) & uic_msr) ||
	    (UIC_MASK(VECNUM_UIC2NCI) & uic_msr))
		uic_interrupt(UIC2_DCR_BASE, 64);
#endif

#if (UIC_MAX > 3)
	if ((UIC_MASK(VECNUM_UIC3CI) & uic_msr) ||
	    (UIC_MASK(VECNUM_UIC3NCI) & uic_msr))
		uic_interrupt(UIC3_DCR_BASE, 96);
#endif

	if (uic_msr & ~(UICB0_ALL))
		uic_interrupt(UIC0_DCR_BASE, 0);

	mtdcr(uic0sr, uic_msr);

	return;
}

void pic_irq_ack(unsigned int vec)
{

	if ((vec >= 0) && (vec < 32))
		mtdcr(uicsr, UIC_MASK(vec));
#if (UIC_MAX > 1)
	else if ((vec >= 32) && (vec < 64))
		mtdcr(uic1sr, UIC_MASK(vec));
#endif
#if (UIC_MAX > 2)
	else if ((vec >= 64) && (vec < 96))
		mtdcr(uic2sr, UIC_MASK(vec));
#endif
#if (UIC_MAX > 3)
	else if (vec >= 96)
		mtdcr(uic3sr, UIC_MASK(vec));
#endif
}

/*
 * Install and free a interrupt handler.
 */
void pic_irq_enable(unsigned int vec)
{

	if ((vec >= 0) && (vec < 32))
		mtdcr(uicer, mfdcr(uicer) | UIC_MASK(vec));
#if (UIC_MAX > 1)
	else if ((vec >= 32) && (vec < 64))
		mtdcr(uic1er, mfdcr(uic1er) | UIC_MASK(vec));
#endif
#if (UIC_MAX > 2)
	else if ((vec >= 64) && (vec < 96))
		mtdcr(uic2er, mfdcr(uic2er) | UIC_MASK(vec));
#endif
#if (UIC_MAX > 3)
	else if (vec >= 96)
		mtdcr(uic3er, mfdcr(uic3er) | UIC_MASK(vec));
#endif

	debug("Install interrupt for vector %d ==> %p\n", vec, handler);
}

void pic_irq_disable(unsigned int vec)
{

	if ((vec >= 0) && (vec < 32))
		mtdcr(uicer, mfdcr(uicer) & ~UIC_MASK(vec));
#if (UIC_MAX > 1)
	else if ((vec >= 32) && (vec < 64))
		mtdcr(uic1er, mfdcr(uic1er) & ~UIC_MASK(vec));
#endif
#if (UIC_MAX > 2)
	else if ((vec >= 64) && (vec < 96))
		mtdcr(uic2er, mfdcr(uic2er) & ~UIC_MASK(vec));
#endif
#if (UIC_MAX > 3)
	else if (vec >= 96)
		mtdcr(uic3er, mfdcr(uic3er) & ~UIC_MASK(vec));
#endif

}

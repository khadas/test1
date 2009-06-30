/*
 * Copyright 2004,2007,2008 Freescale Semiconductor, Inc.
 * (C) Copyright 2002, 2003 Motorola Inc.
 * Xianghua Xiao (X.Xiao@motorola.com)
 *
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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

#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <asm/fsl_dma.h>

/* Controller can only transfer 2^26 - 1 bytes at a time */
#define FSL_DMA_MAX_SIZE	(0x3ffffff)

#if defined(CONFIG_MPC85xx)
ccsr_dma_t *dma_base = (void *)(CONFIG_SYS_MPC85xx_DMA_ADDR);
#elif defined(CONFIG_MPC86xx)
ccsr_dma_t *dma_base = (void *)(CONFIG_SYS_MPC86xx_DMA_ADDR);
#else
#error "Freescale DMA engine not supported on your processor"
#endif

static void dma_sync(void)
{
#if defined(CONFIG_MPC85xx)
	asm("sync; isync; msync");
#elif defined(CONFIG_MPC86xx)
	asm("sync; isync");
#endif
}

static uint dma_check(void) {
	volatile fsl_dma_t *dma = &dma_base->dma[0];
	uint status;

	/* While the channel is busy, spin */
	do {
		status = in_be32(&dma->sr);
	} while (status & FSL_DMA_SR_CB);

	/* clear MR[CS] channel start bit */
	out_be32(&dma->mr, in_be32(&dma->mr) & ~FSL_DMA_MR_CS);
	dma_sync();

	if (status != 0)
		printf ("DMA Error: status = %x\n", status);

	return status;
}

void dma_init(void) {
	volatile fsl_dma_t *dma = &dma_base->dma[0];

	out_be32(&dma->satr, FSL_DMA_SATR_SREAD_SNOOP);
	out_be32(&dma->datr, FSL_DMA_DATR_DWRITE_SNOOP);
	out_be32(&dma->sr, 0xffffffff); /* clear any errors */
	dma_sync();
}

int dmacpy(phys_addr_t dest, phys_addr_t src, phys_size_t count) {
	volatile fsl_dma_t *dma = &dma_base->dma[0];
	uint xfer_size;

	while (count) {
		xfer_size = MIN(FSL_DMA_MAX_SIZE, count);

		out_be32(&dma->dar, (uint) dest);
		out_be32(&dma->sar, (uint) src);
		out_be32(&dma->bcr, xfer_size);

		/* Disable bandwidth control, use direct transfer mode */
		out_be32(&dma->mr, FSL_DMA_MR_BWC_DIS | FSL_DMA_MR_CTM_DIRECT);
		dma_sync();

		/* Start the transfer */
		out_be32(&dma->mr, FSL_DMA_MR_BWC_DIS |
				FSL_DMA_MR_CTM_DIRECT |
				FSL_DMA_MR_CS);

		count -= xfer_size;
		src += xfer_size;
		dest += xfer_size;

		dma_sync();

		if (dma_check())
			return -1;
	}

	return 0;
}

#if (defined(CONFIG_DDR_ECC) && !defined(CONFIG_ECC_INIT_VIA_DDRCONTROLLER))
void dma_meminit(uint val, uint size)
{
	uint *p = 0;
	uint i = 0;

	for (*p = 0; p < (uint *)(8 * 1024); p++) {
		if (((uint)p & 0x1f) == 0)
			ppcDcbz((ulong)p);

		*p = (uint)CONFIG_MEM_INIT_VALUE;

		if (((uint)p & 0x1c) == 0x1c)
			ppcDcbf((ulong)p);
	}

	dmacpy(0x002000, 0, 0x002000); /* 8K */
	dmacpy(0x004000, 0, 0x004000); /* 16K */
	dmacpy(0x008000, 0, 0x008000); /* 32K */
	dmacpy(0x010000, 0, 0x010000); /* 64K */
	dmacpy(0x020000, 0, 0x020000); /* 128K */
	dmacpy(0x040000, 0, 0x040000); /* 256K */
	dmacpy(0x080000, 0, 0x080000); /* 512K */
	dmacpy(0x100000, 0, 0x100000); /* 1M */
	dmacpy(0x200000, 0, 0x200000); /* 2M */
	dmacpy(0x400000, 0, 0x400000); /* 4M */

	for (i = 1; i < size / 0x800000; i++)
		dmacpy((0x800000 * i), 0, 0x800000);
}
#endif

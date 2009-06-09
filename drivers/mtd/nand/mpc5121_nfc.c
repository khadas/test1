/*
 * Copyright 2004-2008 Freescale Semiconductor, Inc.
 * Copyright 2009 Semihalf.
 * (C) Copyright 2009 Stefan Roese <sr@denx.de>
 *
 * Based on original driver from Freescale Semiconductor
 * written by John Rigby <jrigby@freescale.com> on basis
 * of drivers/mtd/nand/mxc_nand.c. Reworked and extended
 * Piotr Ziecik <kosmo@semihalf.com>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <common.h>
#include <malloc.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/compat.h>

#include <asm/errno.h>
#include <asm/io.h>
#include <asm/processor.h>
#include <nand.h>

#define DRV_NAME		"mpc5121_nfc"

/* Timeouts */
#define NFC_RESET_TIMEOUT	1000	/* 1 ms */
#define NFC_TIMEOUT		2000	/* 2000 us */

/* Addresses for NFC MAIN RAM BUFFER areas */
#define NFC_MAIN_AREA(n)	((n) *  0x200)

/* Addresses for NFC SPARE BUFFER areas */
#define NFC_SPARE_BUFFERS	8
#define NFC_SPARE_LEN		0x40
#define NFC_SPARE_AREA(n)	(0x1000 + ((n) * NFC_SPARE_LEN))

/* MPC5121 NFC registers */
#define NFC_BUF_ADDR		0x1E04
#define NFC_FLASH_ADDR		0x1E06
#define NFC_FLASH_CMD		0x1E08
#define NFC_CONFIG		0x1E0A
#define NFC_ECC_STATUS1		0x1E0C
#define NFC_ECC_STATUS2		0x1E0E
#define NFC_SPAS		0x1E10
#define NFC_WRPROT		0x1E12
#define NFC_NF_WRPRST		0x1E18
#define NFC_CONFIG1		0x1E1A
#define NFC_CONFIG2		0x1E1C
#define NFC_UNLOCKSTART_BLK0	0x1E20
#define NFC_UNLOCKEND_BLK0	0x1E22
#define NFC_UNLOCKSTART_BLK1	0x1E24
#define NFC_UNLOCKEND_BLK1	0x1E26
#define NFC_UNLOCKSTART_BLK2	0x1E28
#define NFC_UNLOCKEND_BLK2	0x1E2A
#define NFC_UNLOCKSTART_BLK3	0x1E2C
#define NFC_UNLOCKEND_BLK3	0x1E2E

/* Bit Definitions: NFC_BUF_ADDR */
#define NFC_RBA_MASK		(7 << 0)
#define NFC_ACTIVE_CS_SHIFT	5
#define NFC_ACTIVE_CS_MASK	(3 << NFC_ACTIVE_CS_SHIFT)

/* Bit Definitions: NFC_CONFIG */
#define NFC_BLS_UNLOCKED	(1 << 1)

/* Bit Definitions: NFC_CONFIG1 */
#define NFC_ECC_4BIT		(1 << 0)
#define NFC_FULL_PAGE_DMA	(1 << 1)
#define NFC_SPARE_ONLY		(1 << 2)
#define NFC_ECC_ENABLE		(1 << 3)
#define NFC_INT_MASK		(1 << 4)
#define NFC_BIG_ENDIAN		(1 << 5)
#define NFC_RESET		(1 << 6)
#define NFC_CE			(1 << 7)
#define NFC_ONE_CYCLE		(1 << 8)
#define NFC_PPB_32		(0 << 9)
#define NFC_PPB_64		(1 << 9)
#define NFC_PPB_128		(2 << 9)
#define NFC_PPB_256		(3 << 9)
#define NFC_PPB_MASK		(3 << 9)
#define NFC_FULL_PAGE_INT	(1 << 11)

/* Bit Definitions: NFC_CONFIG2 */
#define NFC_COMMAND		(1 << 0)
#define NFC_ADDRESS		(1 << 1)
#define NFC_INPUT		(1 << 2)
#define NFC_OUTPUT		(1 << 3)
#define NFC_ID			(1 << 4)
#define NFC_STATUS		(1 << 5)
#define NFC_CMD_FAIL		(1 << 15)
#define NFC_INT			(1 << 15)

/* Bit Definitions: NFC_WRPROT */
#define NFC_WPC_LOCK_TIGHT	(1 << 0)
#define NFC_WPC_LOCK		(1 << 1)
#define NFC_WPC_UNLOCK		(1 << 2)

struct mpc5121_nfc_prv {
	struct mtd_info mtd;
	struct nand_chip chip;
	int irq;
	void __iomem *regs;
	struct clk *clk;
	uint column;
	int spareonly;
	int chipsel;
};

int mpc5121_nfc_chip = 0;

static void mpc5121_nfc_done(struct mtd_info *mtd);

/* Read NFC register */
static inline u16 nfc_read(struct mtd_info *mtd, uint reg)
{
	struct nand_chip *chip = mtd->priv;
	struct mpc5121_nfc_prv *prv = chip->priv;

	return in_be16(prv->regs + reg);
}

/* Write NFC register */
static inline void nfc_write(struct mtd_info *mtd, uint reg, u16 val)
{
	struct nand_chip *chip = mtd->priv;
	struct mpc5121_nfc_prv *prv = chip->priv;

	out_be16(prv->regs + reg, val);
}

/* Set bits in NFC register */
static inline void nfc_set(struct mtd_info *mtd, uint reg, u16 bits)
{
	nfc_write(mtd, reg, nfc_read(mtd, reg) | bits);
}

/* Clear bits in NFC register */
static inline void nfc_clear(struct mtd_info *mtd, uint reg, u16 bits)
{
	nfc_write(mtd, reg, nfc_read(mtd, reg) & ~bits);
}

/* Invoke address cycle */
static inline void mpc5121_nfc_send_addr(struct mtd_info *mtd, u16 addr)
{
	nfc_write(mtd, NFC_FLASH_ADDR, addr);
	nfc_write(mtd, NFC_CONFIG2, NFC_ADDRESS);
	mpc5121_nfc_done(mtd);
}

/* Invoke command cycle */
static inline void mpc5121_nfc_send_cmd(struct mtd_info *mtd, u16 cmd)
{
	nfc_write(mtd, NFC_FLASH_CMD, cmd);
	nfc_write(mtd, NFC_CONFIG2, NFC_COMMAND);
	mpc5121_nfc_done(mtd);
}

/* Send data from NFC buffers to NAND flash */
static inline void mpc5121_nfc_send_prog_page(struct mtd_info *mtd)
{
	nfc_clear(mtd, NFC_BUF_ADDR, NFC_RBA_MASK);
	nfc_write(mtd, NFC_CONFIG2, NFC_INPUT);
	mpc5121_nfc_done(mtd);
}

/* Receive data from NAND flash */
static inline void mpc5121_nfc_send_read_page(struct mtd_info *mtd)
{
	nfc_clear(mtd, NFC_BUF_ADDR, NFC_RBA_MASK);
	nfc_write(mtd, NFC_CONFIG2, NFC_OUTPUT);
	mpc5121_nfc_done(mtd);
}

/* Receive ID from NAND flash */
static inline void mpc5121_nfc_send_read_id(struct mtd_info *mtd)
{
	nfc_clear(mtd, NFC_BUF_ADDR, NFC_RBA_MASK);
	nfc_write(mtd, NFC_CONFIG2, NFC_ID);
	mpc5121_nfc_done(mtd);
}

/* Receive status from NAND flash */
static inline void mpc5121_nfc_send_read_status(struct mtd_info *mtd)
{
	nfc_clear(mtd, NFC_BUF_ADDR, NFC_RBA_MASK);
	nfc_write(mtd, NFC_CONFIG2, NFC_STATUS);
	mpc5121_nfc_done(mtd);
}

static void mpc5121_nfc_done(struct mtd_info *mtd)
{
	int max_retries = NFC_TIMEOUT;

	while (1) {
		max_retries--;
		if (nfc_read(mtd, NFC_CONFIG2) & NFC_INT)
			break;
		udelay(1);
	}

	if (max_retries <= 0)
		printk(KERN_WARNING DRV_NAME
		       ": Timeout while waiting for completion.\n");
}

/* Do address cycle(s) */
static void mpc5121_nfc_addr_cycle(struct mtd_info *mtd, int column, int page)
{
	struct nand_chip *chip = mtd->priv;
	u32 pagemask = chip->pagemask;

	if (column != -1) {
		mpc5121_nfc_send_addr(mtd, column);
		if (mtd->writesize > 512)
			mpc5121_nfc_send_addr(mtd, column >> 8);
	}

	if (page != -1) {
		do {
			mpc5121_nfc_send_addr(mtd, page & 0xFF);
			page >>= 8;
			pagemask >>= 8;
		} while (pagemask);
	}
}

/* Control chip select signals */

/*
 * Selecting the active device:
 *
 * This is different than the linux version. Switching between chips
 * is done via board_nand_select_device(). The Linux select_chip
 * function used here in U-Boot has only 2 valid chip numbers:
 * 	0 select
 * 	-1 deselect
 */

/*
 * Implement it as a weak default, so that boards with a specific
 * chip-select routine can use their own function.
 */
void __mpc5121_nfc_select_chip(struct mtd_info *mtd, int chip)
{
	if (chip < 0) {
		nfc_clear(mtd, NFC_CONFIG1, NFC_CE);
		return;
	}

	nfc_clear(mtd, NFC_BUF_ADDR, NFC_ACTIVE_CS_MASK);
	nfc_set(mtd, NFC_BUF_ADDR, (chip << NFC_ACTIVE_CS_SHIFT) &
		NFC_ACTIVE_CS_MASK);
	nfc_set(mtd, NFC_CONFIG1, NFC_CE);
}
void mpc5121_nfc_select_chip(struct mtd_info *mtd, int chip)
	__attribute__((weak, alias("__mpc5121_nfc_select_chip")));

void board_nand_select_device(struct nand_chip *nand, int chip)
{
	/*
	 * Only save this chip number in global variable here. This
	 * will be used later in mpc5121_nfc_select_chip().
	 */
	mpc5121_nfc_chip = chip;
}

/* Read NAND Ready/Busy signal */
static int mpc5121_nfc_dev_ready(struct mtd_info *mtd)
{
	/*
	 * NFC handles ready/busy signal internally. Therefore, this function
	 * always returns status as ready.
	 */
	return 1;
}

/* Write command to NAND flash */
static void mpc5121_nfc_command(struct mtd_info *mtd, unsigned command,
				int column, int page)
{
	struct nand_chip *chip = mtd->priv;
	struct mpc5121_nfc_prv *prv = chip->priv;

	prv->column = (column >= 0) ? column : 0;
	prv->spareonly = 0;

	switch (command) {
	case NAND_CMD_PAGEPROG:
		mpc5121_nfc_send_prog_page(mtd);
		break;
		/*
		 * NFC does not support sub-page reads and writes,
		 * so emulate them using full page transfers.
		 */
	case NAND_CMD_READ0:
		column = 0;
		break;

	case NAND_CMD_READ1:
		prv->column += 256;
		command = NAND_CMD_READ0;
		column = 0;
		break;

	case NAND_CMD_READOOB:
		prv->spareonly = 1;
		command = NAND_CMD_READ0;
		column = 0;
		break;

	case NAND_CMD_SEQIN:
		mpc5121_nfc_command(mtd, NAND_CMD_READ0, column, page);
		column = 0;
		break;

	case NAND_CMD_ERASE1:
	case NAND_CMD_ERASE2:
	case NAND_CMD_READID:
	case NAND_CMD_STATUS:
		break;

	default:
		return;
	}

	mpc5121_nfc_send_cmd(mtd, command);
	mpc5121_nfc_addr_cycle(mtd, column, page);

	switch (command) {
	case NAND_CMD_READ0:
		if (mtd->writesize > 512)
			mpc5121_nfc_send_cmd(mtd, NAND_CMD_READSTART);
		mpc5121_nfc_send_read_page(mtd);
		break;

	case NAND_CMD_READID:
		mpc5121_nfc_send_read_id(mtd);
		break;

	case NAND_CMD_STATUS:
		mpc5121_nfc_send_read_status(mtd);
		if (chip->options & NAND_BUSWIDTH_16)
			prv->column = 1;
		else
			prv->column = 0;
		break;
	}
}

/* Copy data from/to NFC spare buffers. */
static void mpc5121_nfc_copy_spare(struct mtd_info *mtd, uint offset,
				   u8 * buffer, uint size, int wr)
{
	struct nand_chip *nand = mtd->priv;
	struct mpc5121_nfc_prv *prv = nand->priv;
	uint o, s, sbsize, blksize;

	/*
	 * NAND spare area is available through NFC spare buffers.
	 * The NFC divides spare area into (page_size / 512) chunks.
	 * Each chunk is placed into separate spare memory area, using
	 * first (spare_size / num_of_chunks) bytes of the buffer.
	 *
	 * For NAND device in which the spare area is not divided fully
	 * by the number of chunks, number of used bytes in each spare
	 * buffer is rounded down to the nearest even number of bytes,
	 * and all remaining bytes are added to the last used spare area.
	 *
	 * For more information read section 26.6.10 of MPC5121e
	 * Microcontroller Reference Manual, Rev. 3.
	 */

	/* Calculate number of valid bytes in each spare buffer */
	sbsize = (mtd->oobsize / (mtd->writesize / 512)) & ~1;

	while (size) {
		/* Calculate spare buffer number */
		s = offset / sbsize;
		if (s > NFC_SPARE_BUFFERS - 1)
			s = NFC_SPARE_BUFFERS - 1;

		/*
		 * Calculate offset to requested data block in selected spare
		 * buffer and its size.
		 */
		o = offset - (s * sbsize);
		blksize = min(sbsize - o, size);

		if (wr)
			memcpy_toio(prv->regs + NFC_SPARE_AREA(s) + o,
				    buffer, blksize);
		else
			memcpy_fromio(buffer,
				      prv->regs + NFC_SPARE_AREA(s) + o,
				      blksize);

		buffer += blksize;
		offset += blksize;
		size -= blksize;
	};
}

/* Copy data from/to NFC main and spare buffers */
static void mpc5121_nfc_buf_copy(struct mtd_info *mtd, u_char * buf, int len,
				 int wr)
{
	struct nand_chip *chip = mtd->priv;
	struct mpc5121_nfc_prv *prv = chip->priv;
	uint c = prv->column;
	uint l;

	/* Handle spare area access */
	if (prv->spareonly || c >= mtd->writesize) {
		/* Calculate offset from beginning of spare area */
		if (c >= mtd->writesize)
			c -= mtd->writesize;

		prv->column += len;
		mpc5121_nfc_copy_spare(mtd, c, buf, len, wr);
		return;
	}

	/*
	 * Handle main area access - limit copy length to prevent
	 * crossing main/spare boundary.
	 */
	l = min((uint) len, mtd->writesize - c);
	prv->column += l;

	if (wr)
		memcpy_toio(prv->regs + NFC_MAIN_AREA(0) + c, buf, l);
	else
		memcpy_fromio(buf, prv->regs + NFC_MAIN_AREA(0) + c, l);

	/* Handle crossing main/spare boundary */
	if (l != len) {
		buf += l;
		len -= l;
		mpc5121_nfc_buf_copy(mtd, buf, len, wr);
	}
}

/* Read data from NFC buffers */
static void mpc5121_nfc_read_buf(struct mtd_info *mtd, u_char * buf, int len)
{
	mpc5121_nfc_buf_copy(mtd, buf, len, 0);
}

/* Write data to NFC buffers */
static void mpc5121_nfc_write_buf(struct mtd_info *mtd,
				  const u_char * buf, int len)
{
	mpc5121_nfc_buf_copy(mtd, (u_char *) buf, len, 1);
}

/* Compare buffer with NAND flash */
static int mpc5121_nfc_verify_buf(struct mtd_info *mtd,
				  const u_char * buf, int len)
{
	u_char tmp[256];
	uint bsize;

	while (len) {
		bsize = min(len, 256);
		mpc5121_nfc_read_buf(mtd, tmp, bsize);

		if (memcmp(buf, tmp, bsize))
			return 1;

		buf += bsize;
		len -= bsize;
	}

	return 0;
}

/* Read byte from NFC buffers */
static u8 mpc5121_nfc_read_byte(struct mtd_info *mtd)
{
	u8 tmp;

	mpc5121_nfc_read_buf(mtd, &tmp, sizeof(tmp));

	return tmp;
}

/* Read word from NFC buffers */
static u16 mpc5121_nfc_read_word(struct mtd_info *mtd)
{
	u16 tmp;

	mpc5121_nfc_read_buf(mtd, (u_char *) & tmp, sizeof(tmp));

	return tmp;
}

/*
 * Read NFC configuration from Reset Config Word
 *
 * NFC is configured during reset in basis of information stored
 * in Reset Config Word. There is no other way to set NAND block
 * size, spare size and bus width.
 */
static int mpc5121_nfc_read_hw_config(struct mtd_info *mtd)
{
	immap_t *im = (immap_t *)CONFIG_SYS_IMMR;
	struct nand_chip *chip = mtd->priv;
	uint rcw_pagesize = 0;
	uint rcw_sparesize = 0;
	uint rcw_width;
	uint rcwh;
	uint romloc, ps;

	rcwh = in_be32(&(im->reset.rcwh));

	/* Bit 6: NFC bus width */
	rcw_width = ((rcwh >> 6) & 0x1) ? 2 : 1;

	/* Bit 7: NFC Page/Spare size */
	ps = (rcwh >> 7) & 0x1;

	/* Bits [22:21]: ROM Location */
	romloc = (rcwh >> 21) & 0x3;

	/* Decode RCW bits */
	switch ((ps << 2) | romloc) {
	case 0x00:
	case 0x01:
		rcw_pagesize = 512;
		rcw_sparesize = 16;
		break;
	case 0x02:
	case 0x03:
		rcw_pagesize = 4096;
		rcw_sparesize = 128;
		break;
	case 0x04:
	case 0x05:
		rcw_pagesize = 2048;
		rcw_sparesize = 64;
		break;
	case 0x06:
	case 0x07:
		rcw_pagesize = 4096;
		rcw_sparesize = 218;
		break;
	}

	mtd->writesize = rcw_pagesize;
	mtd->oobsize = rcw_sparesize;
	if (rcw_width == 2)
		chip->options |= NAND_BUSWIDTH_16;

	debug(KERN_NOTICE DRV_NAME ": Configured for "
	      "%u-bit NAND, page size %u with %u spare.\n",
	      rcw_width * 8, rcw_pagesize, rcw_sparesize);
	return 0;
}

int board_nand_init(struct nand_chip *chip)
{
	struct mpc5121_nfc_prv *prv;
	struct mtd_info *mtd;
	int resettime = 0;
	int retval = 0;
	int rev;
	static int chip_nr = 0;

	/*
	 * Check SoC revision. This driver supports only NFC
	 * in MPC5121 revision 2.
	 */
	rev = (mfspr(SPRN_SVR) >> 4) & 0xF;
	if (rev != 2) {
		printk(KERN_ERR DRV_NAME
		       ": SoC revision %u is not supported!\n", rev);
		return -ENXIO;
	}

	prv = malloc(sizeof(*prv));
	if (!prv) {
		printk(KERN_ERR DRV_NAME ": Memory exhausted!\n");
		return -ENOMEM;
	}

	mtd = &nand_info[chip_nr++];
	mtd->priv = chip;
	chip->priv = prv;

	/* Read NFC configuration from Reset Config Word */
	retval = mpc5121_nfc_read_hw_config(mtd);
	if (retval) {
		printk(KERN_ERR DRV_NAME ": Unable to read NFC config!\n");
		return retval;
	}

	prv->regs = (void __iomem *)CONFIG_SYS_NAND_BASE;
	chip->dev_ready = mpc5121_nfc_dev_ready;
	chip->cmdfunc = mpc5121_nfc_command;
	chip->read_byte = mpc5121_nfc_read_byte;
	chip->read_word = mpc5121_nfc_read_word;
	chip->read_buf = mpc5121_nfc_read_buf;
	chip->write_buf = mpc5121_nfc_write_buf;
	chip->verify_buf = mpc5121_nfc_verify_buf;
	chip->select_chip = mpc5121_nfc_select_chip;
	chip->options = NAND_NO_AUTOINCR | NAND_USE_FLASH_BBT;
	chip->ecc.mode = NAND_ECC_SOFT;

	/* Reset NAND Flash controller */
	nfc_set(mtd, NFC_CONFIG1, NFC_RESET);
	while (nfc_read(mtd, NFC_CONFIG1) & NFC_RESET) {
		if (resettime++ >= NFC_RESET_TIMEOUT) {
			printk(KERN_ERR DRV_NAME
			       ": Timeout while resetting NFC!\n");
			retval = -EINVAL;
			goto error;
		}

		udelay(1);
	}

	/* Enable write to NFC memory */
	nfc_write(mtd, NFC_CONFIG, NFC_BLS_UNLOCKED);

	/* Enable write to all NAND pages */
	nfc_write(mtd, NFC_UNLOCKSTART_BLK0, 0x0000);
	nfc_write(mtd, NFC_UNLOCKEND_BLK0, 0xFFFF);
	nfc_write(mtd, NFC_WRPROT, NFC_WPC_UNLOCK);

	/*
	 * Setup NFC:
	 *      - Big Endian transfers,
	 *      - Interrupt after full page read/write.
	 */
	nfc_write(mtd, NFC_CONFIG1, NFC_BIG_ENDIAN | NFC_INT_MASK |
		  NFC_FULL_PAGE_INT);

	/* Set spare area size */
	nfc_write(mtd, NFC_SPAS, mtd->oobsize >> 1);

	/* Detect NAND chips */
	if (nand_scan(mtd, 1)) {
		printk(KERN_ERR DRV_NAME ": NAND Flash not found !\n");
		retval = -ENXIO;
		goto error;
	}

	/* Set erase block size */
	switch (mtd->erasesize / mtd->writesize) {
	case 32:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_32);
		break;

	case 64:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_64);
		break;

	case 128:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_128);
		break;

	case 256:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_256);
		break;

	default:
		printk(KERN_ERR DRV_NAME ": Unsupported NAND flash!\n");
		retval = -ENXIO;
		goto error;
	}

	return 0;
error:
	return retval;
}

// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018 Macronix
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */

#ifndef __UBOOT__
#include <linux/device.h>
#include <linux/kernel.h>
#endif
#include <linux/mtd/spinand.h>

#define SPINAND_MFR_MACRONIX		0xC2
/* Read ECCSR (7Ch) command for ECC Status Read */
#define MACRONIX_CURRENT_ECCSR_MASK			0x0F
#define MACRONIX_ACCUMULATE_ECCSR_MASK		(0x0F << 4);

static SPINAND_OP_VARIANTS(read_cache_variants,
		SPINAND_PAGE_READ_FROM_CACHE_X4_OP(0, 1, NULL, 0),
		SPINAND_PAGE_READ_FROM_CACHE_X2_OP(0, 1, NULL, 0),
		SPINAND_PAGE_READ_FROM_CACHE_OP(true, 0, 1, NULL, 0),
		SPINAND_PAGE_READ_FROM_CACHE_OP(false, 0, 1, NULL, 0));

static SPINAND_OP_VARIANTS(write_cache_variants,
		SPINAND_PROG_LOAD_X4(true, 0, NULL, 0),
		SPINAND_PROG_LOAD(true, 0, NULL, 0));

static SPINAND_OP_VARIANTS(update_cache_variants,
		SPINAND_PROG_LOAD_X4(false, 0, NULL, 0),
		SPINAND_PROG_LOAD(false, 0, NULL, 0));

static int mx35lfxge4ab_ooblayout_ecc(struct mtd_info *mtd, int section,
				      struct mtd_oob_region *region)
{
	return -ERANGE;
}

static int mx35lfxge4ab_ooblayout_free(struct mtd_info *mtd, int section,
				       struct mtd_oob_region *region)
{
	if (section)
		return -ERANGE;

	region->offset = 2;
	region->length = mtd->oobsize - 2;

	return 0;
}

static int MX35LF2GE4AD_ooblayout_ecc(struct mtd_info *mtd, int section,
				      struct mtd_oob_region *region)
{
	return -ERANGE;
}

static int MX35LF2GE4AD_ooblayout_free(struct mtd_info *mtd, int section,
				       struct mtd_oob_region *region)
{
	if (section > 3)
		return -ERANGE;

	region->offset = (16 * section) + 2;
	region->length = 14;

	return 0;
}

static const struct mtd_ooblayout_ops mx35lfxge4ab_ooblayout = {
	.ecc = mx35lfxge4ab_ooblayout_ecc,
	.free = mx35lfxge4ab_ooblayout_free,
};

static const struct mtd_ooblayout_ops MX35LF2GE4AD_ooblayout = {
	.ecc = MX35LF2GE4AD_ooblayout_ecc,
	.free = MX35LF2GE4AD_ooblayout_free,
};

static int mx35lf1ge4ab_get_eccsr(struct spinand_device *spinand, u8 *eccsr)
{
	struct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(0x7c, 1),
					  SPI_MEM_OP_NO_ADDR,
					  SPI_MEM_OP_DUMMY(1, 1),
					  SPI_MEM_OP_DATA_IN(1, eccsr, 1));

	return spi_mem_exec_op(spinand->slave, &op);
}

static int mx35lf1ge4ab_ecc_get_status(struct spinand_device *spinand,
				       u8 status)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	u8 eccsr;

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFLIPS:
		return 0;

	case STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	case STATUS_ECC_HAS_BITFLIPS:
		/*
		 * Let's try to retrieve the real maximum number of bitflips
		 * in order to avoid forcing the wear-leveling layer to move
		 * data around if it's not necessary.
		 */
		if (mx35lf1ge4ab_get_eccsr(spinand, &eccsr))
			return nand->eccreq.strength;

		if (WARN_ON(eccsr > nand->eccreq.strength || !eccsr)) {
			return nand->eccreq.strength;
		}

		return eccsr;

	default:
		break;
	}

	return -EINVAL;
}

static int mx35lf2ge4ad_ecc_get_status(struct spinand_device *spinand,
				       u8 status)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	u8 eccsr;

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFLIPS:
		return 0;

	case STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	case STATUS_ECC_HAS_BITFLIPS:
		/*
		 * Let's try to retrieve the real maximum number of bitflips
		 * in order to avoid forcing the wear-leveling layer to move
		 * data around if it's not necessary.
		 */
		if (mx35lf1ge4ab_get_eccsr(spinand, &eccsr))
			return nand->eccreq.strength;

		/*
		 * note:
		 * bit0~3 ECC Status for the current page
		 * bit4~7 ECC Status for the accumulated page
		 */
		eccsr &= MACRONIX_CURRENT_ECCSR_MASK;
		if (WARN_ON(eccsr > nand->eccreq.strength || !eccsr))
			return nand->eccreq.strength;

		return eccsr;

	default:
		break;
	}

	return -EINVAL;
}

static const struct spinand_info macronix_spinand_table[] = {
	SPINAND_INFO("MX35LF1GE4AB 3.3v", 0x12,
		     NAND_MEMORG(1, 2048, 64, 64, 1024, 1, 1, 1),
		     NAND_ECCREQ(4, 512),
		     SPINAND_INFO_OP_VARIANTS(&read_cache_variants,
					      &write_cache_variants,
					      &update_cache_variants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&mx35lfxge4ab_ooblayout,
				     mx35lf1ge4ab_ecc_get_status)),

	SPINAND_INFO("MX35LF2GE4AD", 0x26,
		     NAND_MEMORG(1, 2048, 64, 64, 2048, 1, 1, 1),
		     NAND_ECCREQ(8, 512),
		     SPINAND_INFO_OP_VARIANTS(&read_cache_variants,
					      &write_cache_variants,
					      &update_cache_variants),
		     SPINAND_HAS_QE_BIT,
		     SPINAND_ECCINFO(&MX35LF2GE4AD_ooblayout,
				     mx35lf2ge4ad_ecc_get_status)),
};

static int macronix_spinand_detect(struct spinand_device *spinand)
{
	u8 *id = spinand->id.data;
	int ret;

	if (id[0] != SPINAND_MFR_MACRONIX)
		return 0;

	ret = spinand_match_and_init(spinand, macronix_spinand_table,
				     ARRAY_SIZE(macronix_spinand_table),
				     id[1]);
	if (ret)
		return ret;

	return 1;
}

static const struct spinand_manufacturer_ops macronix_spinand_manuf_ops = {
	.detect = macronix_spinand_detect,
};

const struct spinand_manufacturer macronix_spinand_manufacturer = {
	.id = SPINAND_MFR_MACRONIX,
	.name = "Macronix",
	.ops = &macronix_spinand_manuf_ops,
};

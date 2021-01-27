// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2016-2017 Micron Technology, Inc.
 *
 * Authors:
 *	Peter Pan <peterpandong@micron.com>
 *	Boris Brezillon <boris.brezillon@bootlin.com>
 */

#define pr_fmt(fmt)	"spi-nand: " fmt

#ifndef __UBOOT__
#include <linux/device.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mtd/spinand.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/spi/spi.h>
#include <linux/spi/spi-mem.h>
#else
#include <common.h>
#include <errno.h>
#include <spi.h>
#include <spi-mem.h>
#include <linux/mtd/spinand.h>
#include <linux/mtd/partitions.h>
#include <spi.h>
#include <amlogic/aml_rsv.h>
#include <amlogic/aml_mtd.h>
#include <linux/log2.h>
#include <asm/arch/cpu_config.h>
#include <amlogic/storage.h>
#include <amlogic/cpu_id.h>
#endif

/* SPI NAND index visible in MTD names */
static int spi_nand_idx;
#ifdef CONFIG_AML_STORAGE
extern int spinand_fit_storage(struct mtd_info *info, char *name, u8 *id);
#endif

static void spinand_cache_op_adjust_colum(struct spinand_device *spinand,
					  const struct nand_page_io_req *req,
					  u16 *column)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	unsigned int shift;

	if (nand->memorg.planes_per_lun < 2)
		return;

	/* The plane number is passed in MSB just above the column address */
	shift = fls(nand->memorg.pagesize);
	*column |= req->pos.plane << shift;
}

static int spinand_read_reg_op(struct spinand_device *spinand, u8 reg, u8 *val)
{
	struct spi_mem_op op = SPINAND_GET_FEATURE_OP(reg,
						      spinand->scratchbuf);
	int ret;

	ret = spi_mem_exec_op(spinand->slave, &op);
	if (ret)
		return ret;

	*val = *spinand->scratchbuf;
	return 0;
}

static int spinand_write_reg_op(struct spinand_device *spinand, u8 reg, u8 val)
{
	struct spi_mem_op op = SPINAND_SET_FEATURE_OP(reg,
						      spinand->scratchbuf);

	*spinand->scratchbuf = val;
	return spi_mem_exec_op(spinand->slave, &op);
}

static int spinand_read_status(struct spinand_device *spinand, u8 *status)
{
	return spinand_read_reg_op(spinand, REG_STATUS, status);
}

static int spinand_get_cfg(struct spinand_device *spinand, u8 *cfg)
{
	struct nand_device *nand = spinand_to_nand(spinand);

	if (WARN_ON(spinand->cur_target < 0 ||
		    spinand->cur_target >= nand->memorg.ntargets))
		return -EINVAL;

	*cfg = spinand->cfg_cache[spinand->cur_target];
	return 0;
}

static int spinand_set_cfg(struct spinand_device *spinand, u8 cfg)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	int ret;

	if (WARN_ON(spinand->cur_target < 0 ||
		    spinand->cur_target >= nand->memorg.ntargets))
		return -EINVAL;

	if (spinand->cfg_cache[spinand->cur_target] == cfg)
		return 0;

	ret = spinand_write_reg_op(spinand, REG_CFG, cfg);
	if (ret)
		return ret;

	spinand->cfg_cache[spinand->cur_target] = cfg;
	return 0;
}

/**
 * spinand_upd_cfg() - Update the configuration register
 * @spinand: the spinand device
 * @mask: the mask encoding the bits to update in the config reg
 * @val: the new value to apply
 *
 * Update the configuration register.
 *
 * Return: 0 on success, a negative error code otherwise.
 */
int spinand_upd_cfg(struct spinand_device *spinand, u8 mask, u8 val)
{
	int ret;
	u8 cfg;

	ret = spinand_get_cfg(spinand, &cfg);
	if (ret)
		return ret;

	cfg &= ~mask;
	cfg |= val;

	return spinand_set_cfg(spinand, cfg);
}

/**
 * spinand_select_target() - Select a specific NAND target/die
 * @spinand: the spinand device
 * @target: the target/die to select
 *
 * Select a new target/die. If chip only has one die, this function is a NOOP.
 *
 * Return: 0 on success, a negative error code otherwise.
 */
int spinand_select_target(struct spinand_device *spinand, unsigned int target)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	int ret;

	if (WARN_ON(target >= nand->memorg.ntargets))
		return -EINVAL;

	if (spinand->cur_target == target)
		return 0;

	if (nand->memorg.ntargets == 1) {
		spinand->cur_target = target;
		return 0;
	}

	ret = spinand->select_target(spinand, target);
	if (ret)
		return ret;

	spinand->cur_target = target;
	return 0;
}

static int spinand_init_cfg_cache(struct spinand_device *spinand)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	struct udevice *dev = spinand->slave->dev;
	unsigned int target;
	int ret;

	spinand->cfg_cache = devm_kzalloc(dev,
					  sizeof(*spinand->cfg_cache) *
					  nand->memorg.ntargets,
					  GFP_KERNEL);
	if (!spinand->cfg_cache)
		return -ENOMEM;

	for (target = 0; target < nand->memorg.ntargets; target++) {
		ret = spinand_select_target(spinand, target);
		if (ret)
			return ret;

		/*
		 * We use spinand_read_reg_op() instead of spinand_get_cfg()
		 * here to bypass the config cache.
		 */
		ret = spinand_read_reg_op(spinand, REG_CFG,
					  &spinand->cfg_cache[target]);
		if (ret)
			return ret;
	}

	return 0;
}

static int spinand_init_quad_enable(struct spinand_device *spinand)
{
	bool enable = false;

	if (!(spinand->flags & SPINAND_HAS_QE_BIT))
		return 0;

	if (spinand->op_templates.read_cache->data.buswidth == 4 ||
	    spinand->op_templates.write_cache->data.buswidth == 4 ||
	    spinand->op_templates.update_cache->data.buswidth == 4)
		enable = true;

	printf("spinand qe is %s\n",enable ? "enable" : "disabled");
	return spinand_upd_cfg(spinand, CFG_QUAD_ENABLE,
			       enable ? CFG_QUAD_ENABLE : 0);
}

static int spinand_ecc_enable(struct spinand_device *spinand,
			      bool enable)
{
	return spinand_upd_cfg(spinand, CFG_ECC_ENABLE,
			       enable ? CFG_ECC_ENABLE : 0);
}

static int spinand_write_enable_op(struct spinand_device *spinand)
{
	struct spi_mem_op op = SPINAND_WR_EN_DIS_OP(true);

	return spi_mem_exec_op(spinand->slave, &op);
}

static int spinand_load_page_op(struct spinand_device *spinand,
				const struct nand_page_io_req *req)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	unsigned int row = nanddev_pos_to_row(nand, &req->pos);
	struct spi_mem_op op = SPINAND_PAGE_READ_OP(row);

	return spi_mem_exec_op(spinand->slave, &op);
}

static int spinand_read_from_cache_op(struct spinand_device *spinand,
				      const struct nand_page_io_req *req)
{
	struct spi_mem_op op = *spinand->op_templates.read_cache;
	struct nand_device *nand = spinand_to_nand(spinand);
	struct mtd_info *mtd = nanddev_to_mtd(nand);
	struct nand_page_io_req adjreq = *req;
	unsigned int nbytes = 0;
	void *buf = NULL;
	u16 column = 0;
	int ret;

	if (req->datalen) {
		adjreq.datalen = nanddev_page_size(nand);
		adjreq.dataoffs = 0;
		adjreq.databuf.in = spinand->databuf;
		buf = spinand->databuf;
		nbytes = adjreq.datalen;
	}

	if (req->ooblen) {
		adjreq.ooblen = nanddev_per_page_oobsize(nand);
		adjreq.ooboffs = 0;
		adjreq.oobbuf.in = spinand->oobbuf;
		nbytes += nanddev_per_page_oobsize(nand);
		if (!buf) {
			buf = spinand->oobbuf;
			column = nanddev_page_size(nand);
		}
	}

	spinand_cache_op_adjust_colum(spinand, &adjreq, &column);
	op.addr.val = column;

	/*
	 * Some controllers are limited in term of max RX data size. In this
	 * case, just repeat the READ_CACHE operation after updating the
	 * column.
	 */
	while (nbytes) {
		op.data.buf.in = buf;
		op.data.nbytes = nbytes;
		ret = spi_mem_adjust_op_size(spinand->slave, &op);
		if (ret)
			return ret;

		ret = spi_mem_exec_op(spinand->slave, &op);
		if (ret)
			return ret;

		buf += op.data.nbytes;
		nbytes -= op.data.nbytes;
		op.addr.val += op.data.nbytes;
	}

	if (req->datalen)
		memcpy(req->databuf.in, spinand->databuf + req->dataoffs,
		       req->datalen);

	if (req->ooblen) {
		if (req->mode == MTD_OPS_AUTO_OOB)
			mtd_ooblayout_get_databytes(mtd, req->oobbuf.in,
						    spinand->oobbuf,
						    req->ooboffs,
						    req->ooblen);
		else
			memcpy(req->oobbuf.in, spinand->oobbuf + req->ooboffs,
			       req->ooblen);
	}

	return 0;
}

static int spinand_write_to_cache_op(struct spinand_device *spinand,
				     const struct nand_page_io_req *req)
{
	struct spi_mem_op op = *spinand->op_templates.write_cache;
	struct nand_device *nand = spinand_to_nand(spinand);
	struct mtd_info *mtd = nanddev_to_mtd(nand);
	struct nand_page_io_req adjreq = *req;
	unsigned int nbytes = 0;
	void *buf = NULL;
	u16 column = 0;
	int ret;

	memset(spinand->databuf, 0xff,
	       nanddev_page_size(nand) +
	       nanddev_per_page_oobsize(nand));

	if (req->datalen) {
		memcpy(spinand->databuf + req->dataoffs, req->databuf.out,
		       req->datalen);
		adjreq.dataoffs = 0;
		adjreq.datalen = nanddev_page_size(nand);
		adjreq.databuf.out = spinand->databuf;
		nbytes = adjreq.datalen;
		buf = spinand->databuf;
	}

	if (req->ooblen) {
		if (req->mode == MTD_OPS_AUTO_OOB)
			mtd_ooblayout_set_databytes(mtd, req->oobbuf.out,
						    spinand->oobbuf,
						    req->ooboffs,
						    req->ooblen);
		else
			memcpy(spinand->oobbuf + req->ooboffs, req->oobbuf.out,
			       req->ooblen);

		adjreq.ooblen = nanddev_per_page_oobsize(nand);
		adjreq.ooboffs = 0;
		nbytes += nanddev_per_page_oobsize(nand);
		if (!buf) {
			buf = spinand->oobbuf;
			column = nanddev_page_size(nand);
		}
	}

	spinand_cache_op_adjust_colum(spinand, &adjreq, &column);

	op = *spinand->op_templates.write_cache;
	op.addr.val = column;

	/*
	 * Some controllers are limited in term of max TX data size. In this
	 * case, split the operation into one LOAD CACHE and one or more
	 * LOAD RANDOM CACHE.
	 */
	while (nbytes) {
		op.data.buf.out = buf;
		op.data.nbytes = nbytes;

		ret = spi_mem_adjust_op_size(spinand->slave, &op);
		if (ret)
			return ret;

		ret = spi_mem_exec_op(spinand->slave, &op);
		if (ret)
			return ret;

		buf += op.data.nbytes;
		nbytes -= op.data.nbytes;
		op.addr.val += op.data.nbytes;

		/*
		 * We need to use the RANDOM LOAD CACHE operation if there's
		 * more than one iteration, because the LOAD operation resets
		 * the cache to 0xff.
		 */
		if (nbytes) {
			column = op.addr.val;
			op = *spinand->op_templates.update_cache;
			op.addr.val = column;
		}
	}

	return 0;
}

static int spinand_program_op(struct spinand_device *spinand,
			      const struct nand_page_io_req *req)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	unsigned int row = nanddev_pos_to_row(nand, &req->pos);
	struct spi_mem_op op = SPINAND_PROG_EXEC_OP(row);

	return spi_mem_exec_op(spinand->slave, &op);
}

static int spinand_erase_op(struct spinand_device *spinand,
			    const struct nand_pos *pos)
{
	struct nand_device *nand = &spinand->base;
	unsigned int row = nanddev_pos_to_row(nand, pos);
	struct spi_mem_op op = SPINAND_BLK_ERASE_OP(row);

	return spi_mem_exec_op(spinand->slave, &op);
}

static int spinand_wait(struct spinand_device *spinand, u8 *s)
{
	unsigned long start, stop;
	u8 status;
	int ret;

	start = get_timer(0);
	stop = 400;
	do {
		ret = spinand_read_status(spinand, &status);
		if (ret)
			return ret;

		if (!(status & STATUS_BUSY))
			goto out;
	} while (get_timer(start) < stop);

	/*
	 * Extra read, just in case the STATUS_READY bit has changed
	 * since our last check
	 */
	ret = spinand_read_status(spinand, &status);
	if (ret)
		return ret;

out:
	if (s)
		*s = status;

	return status & STATUS_BUSY ? -ETIMEDOUT : 0;
}

static int spinand_read_id_op(struct spinand_device *spinand, u8 *buf)
{
	struct spi_mem_op op = SPINAND_READID_OP(0, spinand->scratchbuf,
						 SPINAND_MAX_ID_LEN);
	int ret, i;

	ret = spi_mem_exec_op(spinand->slave, &op);
	if (!ret)
		memcpy(buf, spinand->scratchbuf, SPINAND_MAX_ID_LEN);

	/* Success or failure print id */
	printf("spinand id detect\n");
	for (i = 0; i < SPINAND_MAX_ID_LEN; i++)
		printf("id[%d] = 0x%x\n",i,spinand->id.data[i]);

	return ret;
}

static int spinand_reset_op(struct spinand_device *spinand)
{
	struct spi_mem_op op = SPINAND_RESET_OP;
	int ret;

	ret = spi_mem_exec_op(spinand->slave, &op);
	if (ret)
		return ret;

	return spinand_wait(spinand, NULL);
}

static int spinand_lock_block(struct spinand_device *spinand, u8 lock)
{
	return spinand_write_reg_op(spinand, REG_BLOCK_LOCK, lock);
}

static int spinand_check_ecc_status(struct spinand_device *spinand, u8 status)
{
	struct nand_device *nand = spinand_to_nand(spinand);

	if (spinand->eccinfo.get_status)
		return spinand->eccinfo.get_status(spinand, status);

	switch (status & STATUS_ECC_MASK) {
	case STATUS_ECC_NO_BITFLIPS:
		return 0;

	case STATUS_ECC_HAS_BITFLIPS:
		/*
		 * We have no way to know exactly how many bitflips have been
		 * fixed, so let's return the maximum possible value so that
		 * wear-leveling layers move the data immediately.
		 */
		return nand->eccreq.strength;

	case STATUS_ECC_UNCOR_ERROR:
		return -EBADMSG;

	default:
		break;
	}

	return -EINVAL;
}

static int spinand_read_page(struct spinand_device *spinand,
			     const struct nand_page_io_req *req,
			     bool ecc_enabled)
{
	u8 status;
	int ret;

	ret = spinand_load_page_op(spinand, req);
	if (ret)
		return ret;

	ret = spinand_wait(spinand, &status);
	if (ret < 0)
		return ret;

	ret = spinand_read_from_cache_op(spinand, req);
	if (ret)
		return ret;

	if (!ecc_enabled)
		return 0;

	return spinand_check_ecc_status(spinand, status);
}

static int spinand_write_page(struct spinand_device *spinand,
			      const struct nand_page_io_req *req)
{
	u8 status;
	int ret;

	ret = spinand_write_enable_op(spinand);
	if (ret)
		return ret;

	ret = spinand_write_to_cache_op(spinand, req);
	if (ret)
		return ret;

	ret = spinand_program_op(spinand, req);
	if (ret)
		return ret;

	ret = spinand_wait(spinand, &status);
	if (!ret && (status & STATUS_PROG_FAILED))
		ret = -EIO;

	return ret;
}

static int spinand_mtd_read(struct mtd_info *mtd, loff_t from,
			    struct mtd_oob_ops *ops)
{
	struct spinand_device *spinand = mtd_to_spinand(mtd);
	struct nand_device *nand = mtd_to_nanddev(mtd);
	unsigned int max_bitflips = 0;
	struct nand_io_iter iter;
	bool enable_ecc = false;
	bool ecc_failed = false;
	int ret = 0;

	if (ops->mode != MTD_OPS_RAW && spinand->eccinfo.ooblayout)
		enable_ecc = true;

#ifndef __UBOOT__
	mutex_lock(&spinand->lock);
#endif

	nanddev_io_for_each_page(nand, from, ops, &iter) {
		ret = spinand_select_target(spinand, iter.req.pos.target);
		if (ret)
			break;

		ret = spinand_ecc_enable(spinand, enable_ecc);
		if (ret)
			break;

		ret = spinand_read_page(spinand, &iter.req, enable_ecc);
		if (ret < 0 && ret != -EBADMSG)
			break;

		if (ret == -EBADMSG) {
			ecc_failed = true;
			mtd->ecc_stats.failed++;
			ret = 0;
		} else {
			mtd->ecc_stats.corrected += ret;
			max_bitflips = max_t(unsigned int, max_bitflips, ret);
		}

		ops->retlen += iter.req.datalen;
		ops->oobretlen += iter.req.ooblen;
	}

#ifndef __UBOOT__
	mutex_unlock(&spinand->lock);
#endif
	if (ecc_failed && !ret)
		ret = -EBADMSG;

	return ret ? ret : max_bitflips;
}

/* add for meson info_page */
#if SPINAND_MESON_INFO_PAGE
bool spinand_is_info_page(struct nand_device *nand, int page)
{
	return unlikely((page % 128) == ((BL2_SIZE / 2048) - 1) &&
			page < BOOT_TOTAL_PAGES);
}

int spinand_set_info_page(struct mtd_info *mtd, void *buf)
{
	u32 page_per_blk;
	struct mtd_oob_region region;
	struct nand_device* dev = mtd_to_nanddev(mtd);
	struct info_page *info_page = (struct info_page *)buf;

	page_per_blk = mtd->erasesize / mtd->writesize;
	memcpy(info_page->magic, SPINAND_MAGIC, strlen(SPINAND_MAGIC));
	info_page->version = SPINAND_INFO_VER;
	/* DISCRETE only */
	info_page->mode = 1;
	info_page->bl2_num = CONFIG_BL2_COPY_NUM;
	info_page->fip_num = CONFIG_NAND_TPL_COPY_NUM;
	info_page->dev.s.rd_max = 2;
	info_page->dev.s.fip_start =
		BOOT_TOTAL_PAGES + NAND_RSV_BLOCK_NUM * page_per_blk;
	info_page->dev.s.fip_pages = CONFIG_TPL_SIZE_PER_COPY / mtd->writesize;
	info_page->dev.s.page_size = mtd->writesize;
	info_page->dev.s.page_per_blk = page_per_blk;
	info_page->dev.s.oob_size = mtd->oobsize;
	mtd->ooblayout->free(mtd, 0, &region);
	info_page->dev.s.oob_offset = region.offset;
	info_page->dev.s.bbt_start = 0;
	info_page->dev.s.bbt_valid = 0;
	info_page->dev.s.bbt_size = 0;
	info_page->dev.s.planes_per_lun = dev->memorg.planes_per_lun;

	return 0;
}

static int spinand_append_info_page(struct mtd_info *mtd,
				    struct nand_page_io_req *last_req)
{
	struct spinand_device *spinand = mtd_to_spinand(mtd);
	struct nand_device *nand = mtd_to_nanddev(mtd);
	struct nand_page_io_req req;
	int page;
	u8 *buf;
	int ret = 0;

	page = nanddev_pos_to_row(nand, &last_req->pos);
	if (spinand_is_info_page(nand, page)) {
		req = *last_req;
		req.datalen = mtd->writesize;
		req.dataoffs = 0;
		req.ooblen = 0;
		buf = kzalloc(mtd->writesize, GFP_KERNEL);
		req.databuf.in = buf;
		spinand_set_info_page(mtd, buf);
		nanddev_pos_next_page(nand, &req.pos);
		ret = spinand_write_page(spinand, &req);
		kfree(buf);
		pr_info("%s: %d\n", __func__, page);
	}
	return ret;
}
#endif
static int spinand_mtd_write(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops)
{
	struct spinand_device *spinand = mtd_to_spinand(mtd);
	struct nand_device *nand = mtd_to_nanddev(mtd);
	struct nand_io_iter iter;
	bool enable_ecc = false;
	int ret = 0;

	if (ops->mode != MTD_OPS_RAW && mtd->ooblayout)
		enable_ecc = true;

#ifndef __UBOOT__
	mutex_lock(&spinand->lock);
#endif

	nanddev_io_for_each_page(nand, to, ops, &iter) {
		ret = spinand_select_target(spinand, iter.req.pos.target);
		if (ret)
			break;

		ret = spinand_ecc_enable(spinand, enable_ecc);
		if (ret)
			break;

		ret = spinand_write_page(spinand, &iter.req);
		if (ret)
			break;

		/* add for meson info page */
		#if SPINAND_MESON_INFO_PAGE
		ret = spinand_append_info_page(mtd, &iter.req);
		if (ret)
			break;
		#endif
		ops->retlen += iter.req.datalen;
		ops->oobretlen += iter.req.ooblen;
	}

#ifndef __UBOOT__
	mutex_unlock(&spinand->lock);
#endif

	return ret;
}

static bool spinand_isbad(struct nand_device *nand, const struct nand_pos *pos)
{
	struct spinand_device *spinand = nand_to_spinand(nand);
	struct nand_page_io_req req = {
		.pos = *pos,
		.ooblen = 2,
		.ooboffs = 0,
		.oobbuf.in = spinand->oobbuf,
		.mode = MTD_OPS_RAW,
	};
	int ret;

	memset(spinand->oobbuf, 0, 2);
	ret = spinand_select_target(spinand, pos->target);
	if (ret)
		return ret;

	ret = spinand_read_page(spinand, &req, false);
	if (ret)
		return ret;

	if (spinand->oobbuf[0] != 0xff || spinand->oobbuf[1] != 0xff)
		return true;

	return false;
}

static int spinand_mtd_block_isbad(struct mtd_info *mtd, loff_t offs)
{
	struct nand_device *nand = mtd_to_nanddev(mtd);
#ifndef __UBOOT__
	struct spinand_device *spinand = nand_to_spinand(nand);
#endif
	struct nand_pos pos;
	int ret;

	nanddev_offs_to_pos(nand, offs, &pos);
#ifndef __UBOOT__
	mutex_lock(&spinand->lock);
#endif
	ret = nanddev_isbad(nand, &pos);
#ifndef __UBOOT__
	mutex_unlock(&spinand->lock);
#endif
	return ret;
}

static int spinand_markbad(struct nand_device *nand, const struct nand_pos *pos)
{
	struct spinand_device *spinand = nand_to_spinand(nand);
	struct nand_page_io_req req = {
		.pos = *pos,
		.ooboffs = 0,
		.ooblen = 2,
		.oobbuf.out = spinand->oobbuf,
	};
	int ret;

	/* Erase block before marking it bad. */
	ret = spinand_select_target(spinand, pos->target);
	if (ret)
		return ret;

	ret = spinand_write_enable_op(spinand);
	if (ret)
		return ret;

	ret = spinand_erase_op(spinand, pos);
	if (ret)
		return ret;

	memset(spinand->oobbuf, 0, 2);
	return spinand_write_page(spinand, &req);
}

static int spinand_mtd_block_markbad(struct mtd_info *mtd, loff_t offs)
{
	struct nand_device *nand = mtd_to_nanddev(mtd);
#ifndef __UBOOT__
	struct spinand_device *spinand = nand_to_spinand(nand);
#endif
	struct nand_pos pos;
	int ret;

	nanddev_offs_to_pos(nand, offs, &pos);
#ifndef __UBOOT__
	mutex_lock(&spinand->lock);
#endif
	ret = nanddev_markbad(nand, &pos);
#ifndef __UBOOT__
	mutex_unlock(&spinand->lock);
#endif
	return ret;
}

static int spinand_erase(struct nand_device *nand, const struct nand_pos *pos)
{
	struct spinand_device *spinand = nand_to_spinand(nand);
	u8 status;
	int ret = 0;

#if SPINAND_MESON_RSV
	unsigned int block = nanddev_pos_to_offs(nand, pos) /
			(nand->memorg.pages_per_eraseblock * nand->memorg.pagesize);

	/* meson rsv protect */
	if (meson_rsv_erase_protect(spinand->rsv, block)) {
		pr_err("blk 0x%x is protected\n", block);
		return ret;
	}
#endif
	ret = spinand_select_target(spinand, pos->target);
	if (ret)
		return ret;

	ret = spinand_write_enable_op(spinand);
	if (ret)
		return ret;

	ret = spinand_erase_op(spinand, pos);
	if (ret)
		return ret;

	ret = spinand_wait(spinand, &status);
	if (!ret && (status & STATUS_ERASE_FAILED))
		ret = -EIO;

	return ret;
}

static int spinand_mtd_erase(struct mtd_info *mtd,
			     struct erase_info *einfo)
{
#ifndef __UBOOT__
	struct spinand_device *spinand = mtd_to_spinand(mtd);
#endif
	int ret;

#ifndef __UBOOT__
	mutex_lock(&spinand->lock);
#endif
	ret = nanddev_mtd_erase(mtd, einfo);
#ifndef __UBOOT__
	mutex_unlock(&spinand->lock);
#endif

	return ret;
}

static int spinand_mtd_block_isreserved(struct mtd_info *mtd, loff_t offs)
{
#ifndef __UBOOT__
	struct spinand_device *spinand = mtd_to_spinand(mtd);
#endif
	struct nand_device *nand = mtd_to_nanddev(mtd);
	struct nand_pos pos;
	int ret;

	nanddev_offs_to_pos(nand, offs, &pos);
#ifndef __UBOOT__
	mutex_lock(&spinand->lock);
#endif
	ret = nanddev_isreserved(nand, &pos);
#ifndef __UBOOT__
	mutex_unlock(&spinand->lock);
#endif

	return ret;
}

const struct spi_mem_op *
spinand_find_supported_op(struct spinand_device *spinand,
			  const struct spi_mem_op *ops,
			  unsigned int nops)
{
	unsigned int i;

	for (i = 0; i < nops; i++) {
		if (spi_mem_supports_op(spinand->slave, &ops[i]))
			return &ops[i];
	}

	return NULL;
}

static const struct nand_ops spinand_ops = {
	.erase = spinand_erase,
	.markbad = spinand_markbad,
	.isbad = spinand_isbad,
};

static const struct spinand_manufacturer *spinand_manufacturers[] = {
	&gigadevice_spinand_manufacturer,
	&toshiba_spinand_manufacturer,
	&macronix_spinand_manufacturer,
	&micron_spinand_manufacturer,
	&winbond_spinand_manufacturer,
	&zetta_spinand_manufacturer,
	&xtx_spinand_manufacturer,
};

static int spinand_manufacturer_detect(struct spinand_device *spinand)
{
	unsigned int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(spinand_manufacturers); i++) {
		ret = spinand_manufacturers[i]->ops->detect(spinand);
		if (ret > 0) {
			spinand->manufacturer = spinand_manufacturers[i];
			return 0;
		} else if (ret < 0) {
			return ret;
		}
	}

	return -ENOTSUPP;
}

static int spinand_manufacturer_init(struct spinand_device *spinand)
{
	if (spinand->manufacturer->ops->init)
		return spinand->manufacturer->ops->init(spinand);

	return 0;
}

static void spinand_manufacturer_cleanup(struct spinand_device *spinand)
{
	/* Release manufacturer private data */
	if (spinand->manufacturer->ops->cleanup)
		return spinand->manufacturer->ops->cleanup(spinand);
}

static const struct spi_mem_op *
spinand_select_op_variant(struct spinand_device *spinand,
			  const struct spinand_op_variants *variants)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	unsigned int i;

	for (i = 0; i < variants->nops; i++) {
		struct spi_mem_op op = variants->ops[i];
		unsigned int nbytes;
		int ret;

		nbytes = nanddev_per_page_oobsize(nand) +
			 nanddev_page_size(nand);

		while (nbytes) {
			op.data.nbytes = nbytes;
			ret = spi_mem_adjust_op_size(spinand->slave, &op);
			if (ret)
				break;

			if (!spi_mem_supports_op(spinand->slave, &op))
				break;

			nbytes -= op.data.nbytes;
		}

		if (!nbytes)
			return &variants->ops[i];
	}

	return NULL;
}

/**
 * spinand_match_and_init() - Try to find a match between a device ID and an
 *			      entry in a spinand_info table
 * @spinand: SPI NAND object
 * @table: SPI NAND device description table
 * @table_size: size of the device description table
 *
 * Should be used by SPI NAND manufacturer drivers when they want to find a
 * match between a device ID retrieved through the READ_ID command and an
 * entry in the SPI NAND description table. If a match is found, the spinand
 * object will be initialized with information provided by the matching
 * spinand_info entry.
 *
 * Return: 0 on success, a negative error code otherwise.
 */
int spinand_match_and_init(struct spinand_device *spinand,
			   const struct spinand_info *table,
			   unsigned int table_size, u8 devid)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	unsigned int i;

	for (i = 0; i < table_size; i++) {
		const struct spinand_info *info = &table[i];
		const struct spi_mem_op *op;

		if (devid != info->devid)
			continue;

		nand->memorg = table[i].memorg;
		nand->eccreq = table[i].eccreq;
		spinand->eccinfo = table[i].eccinfo;
		spinand->flags = table[i].flags;
		spinand->select_target = table[i].select_target;
		/* Record the current spinand */
		spinand->model = table[i].model;

		op = spinand_select_op_variant(spinand,
					       info->op_variants.read_cache);
		if (!op)
			return -ENOTSUPP;

		spinand->op_templates.read_cache = op;

		op = spinand_select_op_variant(spinand,
					       info->op_variants.write_cache);
		if (!op)
			return -ENOTSUPP;

		spinand->op_templates.write_cache = op;

		op = spinand_select_op_variant(spinand,
					       info->op_variants.update_cache);
		spinand->op_templates.update_cache = op;

		return 0;
	}

	return -ENOTSUPP;
}

static int spinand_detect(struct spinand_device *spinand)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	int ret;

	ret = spinand_reset_op(spinand);
	if (ret)
		return ret;

	ret = spinand_read_id_op(spinand, spinand->id.data);
	if (ret)
		return ret;

	spinand->id.len = SPINAND_MAX_ID_LEN;

	ret = spinand_manufacturer_detect(spinand);
	if (ret) {
		dev_err(dev, "unknown raw ID %*phN\n", SPINAND_MAX_ID_LEN,
			spinand->id.data);
		return ret;
	}

	if (nand->memorg.ntargets > 1 && !spinand->select_target) {
		dev_err(dev,
			"SPI NANDs with more than one die must implement ->select_target()\n");
		return -EINVAL;
	}

	printf("%s  %s SPI NAND was found.\n", spinand->manufacturer->name, spinand->model);
	printf("%llu MiB, block size: %zu KiB, page size: %zu, OOB size: %u\n",
		 nanddev_size(nand) >> 20, nanddev_eraseblock_size(nand) >> 10,
		 nanddev_page_size(nand), nanddev_per_page_oobsize(nand));
	printf("read cmd: 0x%x write cmd: 0x%x\n",spinand->op_templates.read_cache->cmd.opcode,
		 spinand->op_templates.write_cache->cmd.opcode);

	return 0;
}

static int spinand_noecc_ooblayout_ecc(struct mtd_info *mtd, int section,
				       struct mtd_oob_region *region)
{
	return -ERANGE;
}

static int spinand_noecc_ooblayout_free(struct mtd_info *mtd, int section,
					struct mtd_oob_region *region)
{
	if (section)
		return -ERANGE;

	/* Reserve 2 bytes for the BBM. */
	region->offset = 2;
	region->length = 62;

	return 0;
}

static const struct mtd_ooblayout_ops spinand_noecc_ooblayout = {
	.ecc = spinand_noecc_ooblayout_ecc,
	.free = spinand_noecc_ooblayout_free,
};

static int spinand_init(struct spinand_device *spinand)
{
	struct mtd_info *mtd = spinand_to_mtd(spinand);
	struct nand_device *nand = mtd_to_nanddev(mtd);
	int ret, i;

	/*
	 * We need a scratch buffer because the spi_mem interface requires that
	 * buf passed in spi_mem_op->data.buf be DMA-able.
	 */
	spinand->scratchbuf = kzalloc(SPINAND_MAX_ID_LEN, GFP_KERNEL);
	if (!spinand->scratchbuf)
		return -ENOMEM;

	ret = spinand_detect(spinand);
	if (ret)
		goto err_free_bufs;

	/*
	 * Use kzalloc() instead of devm_kzalloc() here, because some drivers
	 * may use this buffer for DMA access.
	 * Memory allocated by devm_ does not guarantee DMA-safe alignment.
	 */
	spinand->databuf = kzalloc(nanddev_page_size(nand) +
			       nanddev_per_page_oobsize(nand),
			       GFP_KERNEL);
	if (!spinand->databuf) {
		ret = -ENOMEM;
		goto err_free_bufs;
	}

	spinand->oobbuf = spinand->databuf + nanddev_page_size(nand);

	ret = spinand_init_cfg_cache(spinand);
	if (ret)
		goto err_free_bufs;

	ret = spinand_init_quad_enable(spinand);
	if (ret)
		goto err_free_bufs;

	ret = spinand_upd_cfg(spinand, CFG_OTP_ENABLE, 0);
	if (ret)
		goto err_free_bufs;

	ret = spinand_manufacturer_init(spinand);
	if (ret) {
		dev_err(dev,
			"Failed to initialize the SPI NAND chip (err = %d)\n",
			ret);
		goto err_free_bufs;
	}

	/* After power up, all blocks are locked, so unlock them here. */
	for (i = 0; i < nand->memorg.ntargets; i++) {
		ret = spinand_select_target(spinand, i);
		if (ret)
			goto err_free_bufs;

		ret = spinand_lock_block(spinand, BL_ALL_UNLOCKED);
		if (ret)
			goto err_free_bufs;
	}

	ret = nanddev_init(nand, &spinand_ops, THIS_MODULE);
	if (ret)
		goto err_manuf_cleanup;

	/*
	 * Right now, we don't support ECC, so let the whole oob
	 * area is available for user.
	 */
	mtd->_read_oob = spinand_mtd_read;
	mtd->_write_oob = spinand_mtd_write;
	mtd->_block_isbad = spinand_mtd_block_isbad;
	mtd->_block_markbad = spinand_mtd_block_markbad;
	mtd->_block_isreserved = spinand_mtd_block_isreserved;
	mtd->_erase = spinand_mtd_erase;

	if (spinand->eccinfo.ooblayout)
		mtd_set_ooblayout(mtd, spinand->eccinfo.ooblayout);
	else
		mtd_set_ooblayout(mtd, &spinand_noecc_ooblayout);

	ret = mtd_ooblayout_count_freebytes(mtd);
	if (ret < 0)
		goto err_cleanup_nanddev;

	mtd->oobavail = ret;

	return 0;

err_cleanup_nanddev:
	nanddev_cleanup(nand);

err_manuf_cleanup:
	spinand_manufacturer_cleanup(spinand);

err_free_bufs:
	kfree(spinand->databuf);
	kfree(spinand->scratchbuf);
	return ret;
}

static void spinand_cleanup(struct spinand_device *spinand)
{
	struct nand_device *nand = spinand_to_nand(spinand);

	nanddev_cleanup(nand);
	spinand_manufacturer_cleanup(spinand);
	kfree(spinand->databuf);
	kfree(spinand->scratchbuf);
}

#ifdef CONFIG_AML_MTDPART
/* The size of the partition must be block aligned */
int spinand_add_partitions(struct mtd_info *mtd,
				  const struct mtd_partition *parts,
				  int nbparts)
{
	int part_num = 0, i = 0;
	struct mtd_partition *temp, *parts_nm;
	loff_t off;
	cpu_id_t cpu_id = get_cpu_id();

	if (store_get_device_bootloader_mode() == DISCRETE_BOOTLOADER) {
	if (cpu_id.family_id == MESON_CPU_MAJOR_ID_SC2)
		part_num = nbparts + 5;
	else
		part_num = nbparts + 2;
	} else
		part_num = nbparts + 1;

	temp = kzalloc(sizeof(*temp) * part_num, GFP_KERNEL);
	memset(temp, 0, sizeof(*temp) * part_num);
	temp[0].name = BOOT_LOADER;
	temp[0].offset = 0;
	temp[0].size = BOOT_TOTAL_PAGES * mtd->writesize;
	if (temp[0].size % mtd->erasesize)
		WARN_ON(1);
	off = temp[0].size + NAND_RSV_BLOCK_NUM * mtd->erasesize;

	if (store_get_device_bootloader_mode() == DISCRETE_BOOTLOADER) {
		if (cpu_id.family_id == MESON_CPU_MAJOR_ID_SC2) {
			extern struct storage_startup_parameter g_ssp;
			temp[BOOT_AREA_BL2E].name = BOOT_BL2E;
			temp[BOOT_AREA_BL2E].offset =
				g_ssp.boot_entry[BOOT_AREA_BL2E].offset;
			temp[BOOT_AREA_BL2E].size =
				g_ssp.boot_entry[BOOT_AREA_BL2E].size * g_ssp.boot_bakups;
			if (temp[0].size % mtd->erasesize)
				WARN_ON(1);

			temp[BOOT_AREA_BL2X].name = BOOT_BL2X;
			temp[BOOT_AREA_BL2X].offset =
				g_ssp.boot_entry[BOOT_AREA_BL2X].offset;
			temp[BOOT_AREA_BL2X].size =
				g_ssp.boot_entry[BOOT_AREA_BL2X].size * g_ssp.boot_bakups;
			if (temp[0].size % mtd->erasesize)
				WARN_ON(1);

			temp[BOOT_AREA_DDRFIP].name = BOOT_DDRFIP;
			temp[BOOT_AREA_DDRFIP].offset =
				g_ssp.boot_entry[BOOT_AREA_DDRFIP].offset;
			temp[BOOT_AREA_DDRFIP].size =
				g_ssp.boot_entry[BOOT_AREA_DDRFIP].size * g_ssp.boot_bakups;
			if (temp[0].size % mtd->erasesize)
				WARN_ON(1);

			temp[BOOT_AREA_DEVFIP].name = BOOT_DEVFIP;
			temp[BOOT_AREA_DEVFIP].offset =
				g_ssp.boot_entry[BOOT_AREA_DEVFIP].offset;
			temp[BOOT_AREA_DEVFIP].size =
				g_ssp.boot_entry[BOOT_AREA_DEVFIP].size * CONFIG_NAND_TPL_COPY_NUM;
			if (temp[0].size % mtd->erasesize)
				WARN_ON(1);
			off = temp[BOOT_AREA_DEVFIP].offset + temp[BOOT_AREA_DEVFIP].size;
			parts_nm = &temp[5];
		} else {
			temp[1].name = BOOT_TPL;
			temp[1].offset = off;
			temp[1].size = CONFIG_TPL_SIZE_PER_COPY * CONFIG_NAND_TPL_COPY_NUM;
			if (temp[1].size % mtd->erasesize)
				WARN_ON(1);
			parts_nm = &temp[2];
			off += temp[1].size;
		}
	} else
		parts_nm = &temp[1];

	for (; i < nbparts; i++) {
		//printf("add_partitions ==== name = %s\n",parts[i].name);
		if (!parts[i].name) {
			pr_err("name can't be null! ");
			pr_err("please check your %d th partition name!\n",
				 i + 1);
			return 1;
		}
		if ((off + parts[i].size) > mtd->size) {
			pr_err("%s %d over nand size!\n",
				__func__, __LINE__);
			return 1;
		}
		parts_nm[i].name = parts[i].name;
#ifndef CONFIG_NOT_SKIP_BAD_BLOCK
		loff_t offset = off, end = off + parts[i].size;

		do {
			if (mtd->_block_isbad(mtd, offset)) {
				pr_err("%s %d found bad block in 0x%llx\n",
					__func__, __LINE__, offset);
				end += mtd->erasesize;
			}
			offset += mtd->erasesize;
		} while (offset < end && offset < mtd->size);
		parts_nm[i].size = end - off - parts[i].size;
#endif/* CONFIG_NOT_SKIP_BAD_BLOCK */
		parts_nm[i].offset = off;
		if (parts[i].size % mtd->erasesize) {
			pr_err("%s %d \"%s\" size auto align to block size\n",
				__func__, __LINE__, parts[i].name);
			parts_nm[i].size += parts[i].size % mtd->erasesize;
		}
		/* it's ok "+=" here because size has been set to 0 */
		parts_nm[i].size += parts[i].size;
		off += parts_nm[i].size;
		if (i == (nbparts - 1))
			parts_nm[i].size = mtd->size - off;
	}
	return add_mtd_partitions(mtd, temp, part_num);
}
#endif

#if SPINAND_MESON_RSV /* add for meson rsv */
static int spinand_scan_bbt(struct spinand_device *spinand, struct mtd_info *mtd)
{
	loff_t offset = 0;
	u64 block_cnt = mtd->size >> mtd->erasesize_shift;
	int i = 0, ret = 0;

	spinand->bbt_scan = 1;
	memset(spinand->bbt, 0, block_cnt);
	for (i = 0; i < block_cnt; i++) {
		offset = i * mtd->erasesize;
		ret = mtd->_block_isbad(mtd, offset);
		if (ret) {
			pr_err("%s %d detected a bad block at 0x%llx\n",
				 __func__, __LINE__, offset);
			spinand->bbt[i] = NAND_FACTORY_BAD;
		}
	}
	spinand->bbt_scan = 0;
	return 0;
}
#endif

static int spinand_probe(struct udevice *dev)
{
	struct spinand_device *spinand = dev_get_priv(dev);
	struct spi_slave *slave = dev_get_parent_priv(dev);
	struct mtd_info *mtd = dev_get_uclass_priv(dev);
	struct nand_device *nand = spinand_to_nand(spinand);
	int ret;

#ifndef __UBOOT__
	spinand = devm_kzalloc(&mem->spi->dev, sizeof(*spinand),
			       GFP_KERNEL);
	if (!spinand)
		return -ENOMEM;

	spinand->spimem = mem;
	spi_mem_set_drvdata(mem, spinand);
	spinand_set_of_node(spinand, mem->spi->dev.of_node);
	mutex_init(&spinand->lock);

	mtd = spinand_to_mtd(spinand);
	mtd->dev.parent = &mem->spi->dev;
#else
	nand->mtd = mtd;
	mtd->priv = nand;
	mtd->dev = dev;
	mtd->name = malloc(20);
	if (!mtd->name)
		return -ENOMEM;
	sprintf(mtd->name, "spi-nand%d", spi_nand_idx++);
	spinand->slave = slave;
	spinand_set_of_node(spinand, dev->node.np);
#endif

	ret = spinand_init(spinand);
	if (ret)
		return ret;

#ifndef __UBOOT__
	ret = mtd_device_register(mtd, NULL, 0);
/*#else
	ret = add_mtd_device(mtd);*/
#endif
	if (ret)
		goto err_spinand_cleanup;

#ifdef CONFIG_AML_STORAGE
	ret = spinand_fit_storage(mtd, mtd->name, spinand->id.data);
#endif

#if SPINAND_MESON_RSV /* add for meson rsv management */
	if (is_power_of_2(mtd->erasesize))
		mtd->erasesize_shift = ffs(mtd->erasesize) - 1;
	else
		mtd->erasesize_shift = 0;

	if (is_power_of_2(mtd->writesize))
		mtd->writesize_shift = ffs(mtd->writesize) - 1;
	else
		mtd->writesize_shift = 0;

	spinand->rsv = kzalloc(sizeof(*spinand->rsv), GFP_KERNEL);
	meson_rsv_init(mtd, spinand->rsv);
	spinand->bbt = kzalloc(mtd->size >> mtd->erasesize_shift, GFP_KERNEL);
	if (meson_rsv_check(spinand->rsv->bbt)) {
		pr_err("no valid bbt info, scanning!\n");
		spinand_scan_bbt(spinand, mtd);
		meson_rsv_save(spinand->rsv->bbt, spinand->bbt);
	} else {
		pr_err("reading bbt info from %s!\n", mtd->name);
		meson_rsv_read(spinand->rsv->bbt, spinand->bbt);
	}

	meson_rsv_check(spinand->rsv->env);
	meson_rsv_check(spinand->rsv->key);
	meson_rsv_check(spinand->rsv->dtb);
#endif

	return ret;

err_spinand_cleanup:
	spinand_cleanup(spinand);

	return ret;
}

#ifndef __UBOOT__
static int spinand_remove(struct udevice *slave)
{
	struct spinand_device *spinand;
	struct mtd_info *mtd;
	int ret;

	spinand = spi_mem_get_drvdata(slave);
	mtd = spinand_to_mtd(spinand);
	free(mtd->name);

	ret = mtd_device_unregister(mtd);
	if (ret)
		return ret;

	spinand_cleanup(spinand);

	return 0;
}

static const struct spi_device_id spinand_ids[] = {
	{ .name = "spi-nand" },
	{ /* sentinel */ },
};

#ifdef CONFIG_OF
static const struct of_device_id spinand_of_ids[] = {
	{ .compatible = "spi-nand" },
	{ /* sentinel */ },
};
#endif

static struct spi_mem_driver spinand_drv = {
	.spidrv = {
		.id_table = spinand_ids,
		.driver = {
			.name = "spi-nand",
			.of_match_table = of_match_ptr(spinand_of_ids),
		},
	},
	.probe = spinand_probe,
	.remove = spinand_remove,
};
module_spi_mem_driver(spinand_drv);

MODULE_DESCRIPTION("SPI NAND framework");
MODULE_AUTHOR("Peter Pan<peterpandong@micron.com>");
MODULE_LICENSE("GPL v2");
#endif /* __UBOOT__ */

static const struct udevice_id spinand_ids[] = {
	{ .compatible = "spi-nand" },
	{ /* sentinel */ },
};

U_BOOT_DRIVER(spinand) = {
	.name = "spi_nand",
	.id = UCLASS_MTD,
	.of_match = spinand_ids,
	.priv_auto_alloc_size = sizeof(struct spinand_device),
	.probe = spinand_probe,
};

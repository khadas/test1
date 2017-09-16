/*
 * Copyright 2014 Broadcom Corporation.
 * Copyright 2015 Free Electrons.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <common.h>

#include <fastboot.h>
#include <image-sparse.h>

#include <linux/mtd/mtd.h>
#include <jffs2/jffs2.h>
#include <nand.h>

struct fb_nand_sparse {
	struct mtd_info		*mtd;
	struct part_info	*part;
};

__weak int board_fastboot_erase_partition_setup(char *name)
{
	return 0;
}

__weak int board_fastboot_write_partition_setup(char *name)
{
	return 0;
}

static int fb_nand_lookup(const char *partname,
			  struct mtd_info **mtd,
			  struct part_info **part)
{
	struct mtd_device *dev;
	int ret;
	u8 pnum;

	ret = mtdparts_init();
	if (ret) {
		pr_err("Cannot initialize MTD partitions\n");
		fastboot_fail("cannot init mtdparts");
		return ret;
	}

	ret = find_dev_and_part(partname, &dev, &pnum, part);
	if (ret) {
		pr_err("cannot find partition: '%s'", partname);
		fastboot_fail("cannot find partition");
		return ret;
	}

	if (dev->id->type != MTD_DEV_TYPE_NAND) {
		pr_err("partition '%s' is not stored on a NAND device",
		      partname);
		fastboot_fail("not a NAND device");
		return -EINVAL;
	}

	*mtd = get_nand_dev_by_index(dev->id->num);

	return 0;
}

static int _fb_nand_erase(struct mtd_info *mtd, struct part_info *part)
{
	nand_erase_options_t opts;
	int ret;

	memset(&opts, 0, sizeof(opts));
	opts.offset = part->offset;
	opts.length = part->size;
	opts.quiet = 1;

	printf("Erasing blocks 0x%llx to 0x%llx\n",
	       part->offset, part->offset + part->size);

	ret = nand_erase_opts(mtd, &opts);
	if (ret)
		return ret;

	printf("........ erased 0x%llx bytes from '%s'\n",
	       part->size, part->name);

	return 0;
}

static int _fb_nand_write(struct mtd_info *mtd, struct part_info *part,
			  void *buffer, unsigned int offset,
			  unsigned int length, size_t *written)
{
	int flags = WITH_WR_VERIFY;

#ifdef CONFIG_FASTBOOT_FLASH_NAND_TRIMFFS
	flags |= WITH_DROP_FFS;
#endif

	return nand_write_skip_bad(mtd, offset, &length, written,
				   part->size - (offset - part->offset),
				   buffer, flags);
}

static lbaint_t fb_nand_sparse_write(struct sparse_storage *info,
		lbaint_t blk, lbaint_t blkcnt, const void *buffer)
{
	struct fb_nand_sparse *sparse = info->priv;
	size_t written;
	int ret;

	ret = _fb_nand_write(sparse->mtd, sparse->part, (void *)buffer,
			     blk * info->blksz,
			     blkcnt * info->blksz, &written);
	if (ret < 0) {
		printf("Failed to write sparse chunk\n");
		return ret;
	}

/* TODO - verify that the value "written" includes the "bad-blocks" ... */

	/*
	 * the return value must be 'blkcnt' ("good-blocks") plus the
	 * number of "bad-blocks" encountered within this space...
	 */
	return written / info->blksz;
}

static lbaint_t fb_nand_sparse_reserve(struct sparse_storage *info,
		lbaint_t blk, lbaint_t blkcnt)
{
	int bad_blocks = 0;

/*
 * TODO - implement a function to determine the total number
 * of blocks which must be used in order to reserve the specified
 * number ("blkcnt") of "good-blocks", starting at "blk"...
 * ( possibly something like the "check_skip_len()" function )
 */

	/*
	 * the return value must be 'blkcnt' ("good-blocks") plus the
	 * number of "bad-blocks" encountered within this space...
	 */
	return blkcnt + bad_blocks;
}

void fb_nand_flash_write(const char *cmd, void *download_buffer,
			 unsigned int download_bytes)
{
	struct part_info *part;
	struct mtd_info *mtd = NULL;
	int ret;

	ret = fb_nand_lookup(cmd, &mtd, &part);
	if (ret) {
		pr_err("invalid NAND device");
		fastboot_fail("invalid NAND device");
		return;
	}

	ret = board_fastboot_write_partition_setup(part->name);
	if (ret)
		return;

	if (is_sparse_image(download_buffer)) {
		struct fb_nand_sparse sparse_priv;
		struct sparse_storage sparse;

		sparse_priv.mtd = mtd;
		sparse_priv.part = part;

		sparse.blksz = mtd->writesize;
		sparse.start = part->offset / sparse.blksz;
		sparse.size = part->size / sparse.blksz;
		sparse.write = fb_nand_sparse_write;
		sparse.reserve = fb_nand_sparse_reserve;

		printf("Flashing sparse image at offset " LBAFU "\n",
		       sparse.start);

		sparse.priv = &sparse_priv;
		write_sparse_image(&sparse, cmd, download_buffer,
				   download_bytes);
	} else {
		printf("Flashing raw image at offset 0x%llx\n",
		       part->offset);

		ret = _fb_nand_write(mtd, part, download_buffer, part->offset,
				     download_bytes, NULL);

		printf("........ wrote %u bytes to '%s'\n",
		       download_bytes, part->name);
	}

	if (ret) {
		fastboot_fail("error writing the image");
		return;
	}

	fastboot_okay("");
}

void fb_nand_erase(const char *cmd)
{
	struct part_info *part;
	struct mtd_info *mtd = NULL;
	int ret;

	ret = fb_nand_lookup(cmd, &mtd, &part);
	if (ret) {
		pr_err("invalid NAND device");
		fastboot_fail("invalid NAND device");
		return;
	}

	ret = board_fastboot_erase_partition_setup(part->name);
	if (ret)
		return;

	ret = _fb_nand_erase(mtd, part);
	if (ret) {
		pr_err("failed erasing from device %s", mtd->name);
		fastboot_fail("failed erasing from device");
		return;
	}

	fastboot_okay("");
}

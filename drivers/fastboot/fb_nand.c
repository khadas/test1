// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2014 Broadcom Corporation.
 * Copyright 2015 Free Electrons.
 */

#include <config.h>
#include <common.h>

#include <fastboot.h>
#include <image-sparse.h>

#include <linux/mtd/mtd.h>
#include <jffs2/jffs2.h>
#include <nand.h>
#include <amlogic/storage.h>
#include <amlogic/aml_mtd.h>
#include <amlogic/aml_nand.h>
#include <amlogic/aml_rsv.h>

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
			  struct part_info **part,
			  char *response)
{
	struct mtd_device *dev;
	int ret;
	u8 pnum;

	ret = mtdparts_init();
	if (ret) {
		pr_err("Cannot initialize MTD partitions\n");
		fastboot_fail("cannot init mtdparts", response);
		return ret;
	}

	if (strcmp(partname, "dtb") == 0)
		return 0;
	ret = find_dev_and_part(partname, &dev, &pnum, part);
	if (ret) {
		pr_err("cannot find partition: '%s'", partname);
		fastboot_fail("cannot find partition", response);
		return ret;
	}

	if (dev->id->type != MTD_DEV_TYPE_NAND) {
		pr_err("partition '%s' is not stored on a NAND device",
		      partname);
		fastboot_fail("not a NAND device", response);
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
			  void *buffer, u32 offset,
			  size_t length, size_t *written)
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

/**
 * fastboot_nand_get_part_info() - Lookup NAND partion by name
 *
 * @part_name: Named device to lookup
 * @part_info: Pointer to returned part_info pointer
 * @response: Pointer to fastboot response buffer
 */
int fastboot_nand_get_part_info(char *part_name, struct part_info **part_info,
				char *response)
{
	struct mtd_info *mtd = NULL;

	return fb_nand_lookup(part_name, &mtd, part_info, response);
}

/**
 * fastboot_nand_flash_write() - Write image to NAND for fastboot
 *
 * @cmd: Named device to write image to
 * @download_buffer: Pointer to image data
 * @download_bytes: Size of image data
 * @response: Pointer to fastboot response buffer
 */
void fastboot_nand_flash_write(const char *cmd, void *download_buffer,
			       u32 download_bytes, char *response)
{
	struct part_info *part;
	struct mtd_info *mtd = NULL;
	int ret, err;
	int copy_num = 0, i = 0;
	u64 off = 0;
	size_t rwsize = 0, limit = 0;

	ret = fb_nand_lookup(cmd, &mtd, &part, response);
	if (ret) {
		pr_err("invalid NAND device");
		fastboot_fail("invalid NAND device", response);
		return;
	}

	if (strcmp(cmd, "bootloader") == 0) {
		rwsize = download_bytes;
#ifdef CONFIG_DISCRETE_BOOTLOADER
		copy_num = CONFIG_BL2_COPY_NUM;
		limit = mtd->size / copy_num;
#else
		copy_num = get_boot_num(mtd, rwsize);
		limit = mtd->size / copy_num;
#endif
		for (i = 0; i < copy_num; i++) {
			printf("off = 0x%llx,wsize = 0x%lx\n",
				off, rwsize);
			err = nand_write_skip_bad(mtd, off, &rwsize,
						NULL, limit,
						(u_char *)download_buffer, 0);
			if (err) {
				rwsize = download_bytes;
				printf("bootloader write err,code = %d\n",err);
			}
			off += limit;
		}
		fastboot_okay("write bootloader", response);
		return;
	}

#ifdef CONFIG_DISCRETE_BOOTLOADER
	if (strcmp(cmd, "tpl") == 0) {
		copy_num = CONFIG_TPL_COPY_NUM;
		rwsize = download_bytes;
		limit = CONFIG_TPL_SIZE_PER_COPY;
		off = 1024 * mtd->writesize +
			NAND_RSV_BLOCK_NUM * mtd->erasesize;

		for (i = 0; i < copy_num; i++) {
			printf("off = 0x%llx,wsize = 0x%lx\n", off, rwsize);
			err = nand_write_skip_bad(mtd, off, &rwsize,
						NULL, limit,
						(u_char *)download_buffer, 0);
			if (err) {
				rwsize = download_bytes;
				printf("tpl write err,code = %d\n",err);
			}
			off += CONFIG_TPL_SIZE_PER_COPY;
		}
		fastboot_okay("write tpl", response);
		return;
	}
#endif

	if (strcmp(cmd, "dtb") == 0) {
		ret = store_rsv_write("dtb", download_bytes, (u8 *)download_buffer);
		printf("Flashing dtb...len:0x%x\n", download_bytes);
		if (ret) {
			printf("write dtb fail,result code %d\n", ret);
			fastboot_fail("write dtb", response);
		} else {
			fastboot_okay("write dtb", response);
		}
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
		sparse.mssg = fastboot_fail;

		printf("Flashing sparse image at offset " LBAFU "\n",
		       sparse.start);

		sparse.priv = &sparse_priv;
		ret = write_sparse_image(&sparse, cmd, download_buffer,
					 response);
		if (!ret)
			fastboot_okay(NULL, response);
	} else {
		printf("Flashing raw image at offset 0x%llx\n",
		       part->offset);

		ret = _fb_nand_write(mtd, part, download_buffer, part->offset,
				     download_bytes, NULL);

		printf("........ wrote %u bytes to '%s'\n",
		       download_bytes, part->name);
	}

	if (ret) {
		fastboot_fail("error writing the image", response);
		return;
	}

	fastboot_okay(NULL, response);
}

/**
 * fastboot_nand_flash_erase() - Erase NAND for fastboot
 *
 * @cmd: Named device to erase
 * @response: Pointer to fastboot response buffer
 */
void fastboot_nand_erase(const char *cmd, char *response)
{
	struct part_info *part;
	struct mtd_info *mtd = NULL;
	int ret;

	ret = fb_nand_lookup(cmd, &mtd, &part, response);
	if (ret) {
		pr_err("invalid NAND device");
		fastboot_fail("invalid NAND device", response);
		return;
	}

	if (strcmp(cmd, "dtb") == 0) {
		ret = store_rsv_erase("dtb");
		if (ret) {
			pr_err("erase dtb fail,ret = %d\n", ret);
			fastboot_fail("erase dtb",
				response);
		} else {
			fastboot_okay("erase dtb", response);
		}
		return;
	}

	ret = board_fastboot_erase_partition_setup(part->name);
	if (ret)
		return;

	ret = _fb_nand_erase(mtd, part);
	if (ret) {
		pr_err("failed erasing from device %s", mtd->name);
		fastboot_fail("failed erasing from device", response);
		return;
	}

	fastboot_okay(NULL, response);
}

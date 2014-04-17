/*
 * (c) Copyright 2011 by Tigris Elektronik GmbH
 *
 * Author:
 *  Maximilian Schwerin <mvs@tigris.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>

#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <search.h>
#include <errno.h>
#include <fat.h>
#include <mmc.h>

char *env_name_spec = "FAT";

env_t *env_ptr;

DECLARE_GLOBAL_DATA_PTR;

int env_init(void)
{
	/* use default */
	gd->env_addr = (ulong)&default_environment[0];
	gd->env_valid = 1;

	return 0;
}

#ifdef CONFIG_CMD_SAVEENV
int saveenv(void)
{
	env_t	env_new;
	block_dev_desc_t *dev_desc = NULL;
	int dev = FAT_ENV_DEVICE;
	int part = FAT_ENV_PART;
	int err;

	err = env_export(&env_new);
	if (err)
		return err;

#ifdef CONFIG_MMC
	if (strcmp(FAT_ENV_INTERFACE, "mmc") == 0) {
		struct mmc *mmc = find_mmc_device(dev);

		if (!mmc) {
			printf("no mmc device at slot %x\n", dev);
			return 1;
		}

		mmc->has_init = 0;
		mmc_init(mmc);
	}
#endif /* CONFIG_MMC */

	dev_desc = get_dev(FAT_ENV_INTERFACE, dev);
	if (dev_desc == NULL) {
		printf("Failed to find %s%d\n",
			FAT_ENV_INTERFACE, dev);
		return 1;
	}

	err = fat_register_device(dev_desc, part);
	if (err) {
		printf("Failed to register %s%d:%d\n",
			FAT_ENV_INTERFACE, dev, part);
		return 1;
	}

	err = file_fat_write(FAT_ENV_FILE, (void *)&env_new, sizeof(env_t));
	if (err == -1) {
		printf("\n** Unable to write \"%s\" from %s%d:%d **\n",
			FAT_ENV_FILE, FAT_ENV_INTERFACE, dev, part);
		return 1;
	}

	puts("done\n");
	return 0;
}
#endif /* CONFIG_CMD_SAVEENV */

void env_relocate_spec(void)
{
	char buf[CONFIG_ENV_SIZE];
	block_dev_desc_t *dev_desc = NULL;
	int dev = FAT_ENV_DEVICE;
	int part = FAT_ENV_PART;
	int err;

#ifdef CONFIG_MMC
	if (strcmp(FAT_ENV_INTERFACE, "mmc") == 0) {
		struct mmc *mmc = find_mmc_device(dev);

		if (!mmc) {
			printf("no mmc device at slot %x\n", dev);
			set_default_env(NULL);
			return;
		}

		mmc->has_init = 0;
		mmc_init(mmc);
	}
#endif /* CONFIG_MMC */

	dev_desc = get_dev(FAT_ENV_INTERFACE, dev);
	if (dev_desc == NULL) {
		printf("Failed to find %s%d\n",
			FAT_ENV_INTERFACE, dev);
		set_default_env(NULL);
		return;
	}

	err = fat_register_device(dev_desc, part);
	if (err) {
		printf("Failed to register %s%d:%d\n",
			FAT_ENV_INTERFACE, dev, part);
		set_default_env(NULL);
		return;
	}

	err = file_fat_read(FAT_ENV_FILE, (uchar *)&buf, CONFIG_ENV_SIZE);
	if (err == -1) {
		printf("\n** Unable to read \"%s\" from %s%d:%d **\n",
			FAT_ENV_FILE, FAT_ENV_INTERFACE, dev, part);
		set_default_env(NULL);
		return;
	}

	env_import(buf, 1);
}

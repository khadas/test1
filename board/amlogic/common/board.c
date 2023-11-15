// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <asm/io.h>
#include <malloc.h>
#include <errno.h>
#include <environment.h>
#include <fdt_support.h>
#include <linux/libfdt.h>
#include <amlogic/cpu_id.h>
#include <cli.h>
#include <console.h>
#include <generated/version_autogenerated.h>
#include <amlogic/aml_v3_burning.h>
#include <amlogic/aml_v2_burning.h>
#include <amlogic/board.h>
#include <asm/arch/secure_apb.h>
#include <asm/arch/romboot.h>

DECLARE_GLOBAL_DATA_PTR;
#define UNUSED(x) (void)(x)

#ifdef CONFIG_MISC_INIT_R
#define _AML_MISC_INTERRUPT_KEY 0x09
static int _aml_interrupt_key_pressed;
static int ctrli(void)
{
	if (1/*gd->have_console*/) {
		if (tstc()) {
			switch (getc()) {
			case _AML_MISC_INTERRUPT_KEY:/* ^I - Control I */
				_aml_interrupt_key_pressed = 1;
				printf("Detect Ctrl I...\t\nInput yes to force stopped anyway:\t");
				return 1;
			default:
				break;
			}
		}
	}

	return 0;
}

static int aml_misc_confirm_yesno(const int tm/*timeout in ms*/)
{
	int i;
	unsigned long ts;
	char str_input[5];

	_aml_interrupt_key_pressed = 0;
	if (!ctrli()) {//not detect ctrl-I when bootup
		return 0;
	}
	ts = get_timer(0);

	for (i = 0; i < sizeof(str_input);) {
		int c = 0;

		while (!tstc()) {
			if (get_timer(ts) >= tm) {
				printf("Input timeout\n");
				return 0;
			}
		}
		c = getc();
		if (i == 0 && c == _AML_MISC_INTERRUPT_KEY) {//drop first duplicated ctrlI
			printf("Wait YES/y input\n");
			continue;
		}
		putc(c);
		str_input[i++] = c;
		if (c == '\r')
			break;
	}
	putc('\n');
	if (strncmp(str_input, "y\r", 2) == 0 ||
	    strncmp(str_input, "Y\r", 2) == 0 ||
	    strncmp(str_input, "yes\r", 4) == 0 ||
	    strncmp(str_input, "YES\r", 4) == 0)
		return 1;
	return 0;
}

int misc_init_r(void)
{
	printf("board common misc_init\n");
	if (!aml_misc_confirm_yesno(5000))
		return 0;

	cli_init();
	cli_loop();
	panic("No CLI available");
	return 0;
}
#endif // #ifdef CONFIG_MISC_INIT_R

#ifdef CONFIG_AB_UPDATE
#include <u-boot/sha256.h>
#include <emmc_partitions.h>
#include <amlogic/aml_efuse.h>
#include <amlogic/store_wrapper.h>
#include <asm/arch/bl31_apis.h>

int ab_mode(void)
{
	printf("\nchoice A/B upgrade\n");

	/*********************************************************************
	 * 1. read partition of fip_a and fip_b ddr then verify two partition;
	 * 2. read env form "active_slot" to choice boot from which partition.
	 ********************************************************************/

	char *p_env = NULL;
	unsigned int ret = 0;
	unsigned char buff[32];

	//run_command("run bcb_cmd", 0);

	p_env = env_get("active_slot");
	printf("p_env = %s\n", p_env);

	//extern void aml_u8_printf(void *pBuffer, int nSize);

	if (IS_FEAT_BOOT_VERIFY()) {
		/* verify partition of fi_a and fip_b */
		printf("\nneed to verify part of a/b\n");
		ret = store_logic_read((const char *)"fip_a", 0,
				FIP_LOAD_SIZE + 0x400, (unsigned char *)FIP_A_LOADADDR);
		if (ret)
			goto exit;
		printf("\nread pass form  part of a/b\n");
		ret = aml_sec_boot_check(AML_D_P_IMG_DECRYPT,
				FIP_A_LOADADDR, FIP_LOAD_SIZE + 0x400, GXB_IMG_DEC_ALL);
		if (ret) {
			printf("\nfip_a : Sig Check %d\n", ret);
			goto exit;
		}

		ret = store_logic_read((const char *)"fip_b", 0,
				FIP_LOAD_SIZE + 0x400, (unsigned char *)FIP_B_LOADADDR);
		if (ret)
			goto exit;
		ret = aml_sec_boot_check(AML_D_P_IMG_DECRYPT, FIP_B_LOADADDR,
				FIP_LOAD_SIZE + 0x400, GXB_IMG_DEC_ALL);
		if (ret) {
			printf("\nfip_b : Sig Check %d\n", ret);
			goto exit;
		}
		printf("\nfip_a and fip_b verify pass\n");
	} else {
		/* calculate SHA digest for fip_a and fip_b */
		ret = store_logic_read((const char *)"fip_a", 0, FIP_LOAD_SIZE,
				(unsigned char *)FIP_A_LOADADDR);
		if (ret)
			goto exit;

		sha256_csum_wd((unsigned char *)(FIP_A_LOADADDR), (FIP_LOAD_SIZE - 32),
				(unsigned char *)buff, 0);
#ifdef DEBUG
		printf("fip a buff sha is :\n");
		aml_u8_printf((void *)buff, 0x20);
		printf("fip a origin sha is :\n");
		aml_u8_printf((void *)(FIP_A_LOADADDR + FIP_LOAD_SIZE - 32), 0x20);
#endif
		if (memcmp(buff, (void *)(FIP_A_LOADADDR + FIP_LOAD_SIZE - 32), 32)) {
			printf("FIP_A SHA NOT OK\n");
			goto exit;
		}
		ret = store_logic_read((const char *)"fip_b",
				0, FIP_LOAD_SIZE, (unsigned char *)FIP_B_LOADADDR);
		if (ret)
			goto exit;
		sha256_csum_wd((unsigned char *)(FIP_B_LOADADDR),
				(FIP_LOAD_SIZE - 32), (unsigned char *)buff, 0);
#ifdef DEBUG
		printf("fip b buff sha is :\n");
		aml_u8_printf((void *)buff, 0x20);
		printf("fip b origin sha is :\n");
		aml_u8_printf((void *)(FIP_B_LOADADDR + FIP_LOAD_SIZE - 32), 0x20);
#endif
		if (memcmp(buff, (void *)(FIP_B_LOADADDR + FIP_LOAD_SIZE - 32), 32)) {
			printf("FIP_B SHA NOT OK\n");
			goto exit;
		}
	}

	if (strcmp(p_env, "_a") == 0) {
		printf("\nchoice fip A upgrade\n");
		if (IS_FEAT_BOOT_VERIFY())
			memmove((unsigned char *)CONFIG_SYS_TEXT_BASE,
					(unsigned char *)FIP_A_LOADADDR + 0x200, FIP_LOAD_SIZE);
		else
			memmove((unsigned char *)CONFIG_SYS_TEXT_BASE,
					(unsigned char *)FIP_A_LOADADDR, FIP_LOAD_SIZE);
	} else if (strcmp(p_env, "_b") == 0) {
		printf("\nset fip B upgrade\n");
		if (IS_FEAT_BOOT_VERIFY())
			memmove((unsigned char *)CONFIG_SYS_TEXT_BASE,
					(unsigned char *)FIP_B_LOADADDR + 0x200, FIP_LOAD_SIZE);
		else
			memmove((unsigned char *)CONFIG_SYS_TEXT_BASE,
					(unsigned char *)FIP_B_LOADADDR, FIP_LOAD_SIZE);
	} else {
		printf("Error (Need debug): active_slot(%s) is not ab mode\n", p_env);
		goto exit;
	}

	unsigned long bl33_entry = CONFIG_SYS_TEXT_BASE;
	/* run bl33 directly */
	typedef unsigned long (*FUNC_TPL)(void);
	printf("bl33 entry: 0x%lx\n", bl33_entry);
	FUNC_TPL func_tpl = (FUNC_TPL)bl33_entry;

	func_tpl();

exit:
	return 0;
}
#endif

#ifdef CONFIG_BOARD_LATE_INIT
int aml_board_late_init_front(void *arg)
{
	UNUSED(arg);
	printf("init front\n");
	run_command("aml_update_env", 0);
	/* ****************************************************
	 * 1.setup bootup resource
	 * ****************************************************
	 */
	board_init_mem();
	run_command("run bcb_cmd", 0);

#ifndef CONFIG_SYSTEM_RTOS //prue rtos not need dtb
	if (run_command("run common_dtb_load", 0)) {
		printf("Fail in load dtb with cmd[%s], try _aml_dtb\n", env_get("common_dtb_load"));
		//load dtb here then users can directly use 'fdt' command
		run_command("echo reboot_mode ${reboot_mode}; "
				"imgread dtb _aml_dtb ${dtb_mem_addr}; fi;", 0);
	}
	run_command("if fdt addr ${dtb_mem_addr}; then else echo no dtb at ${dtb_mem_addr};fi;", 0);
	/* load unifykey */
	run_command("keyman init 0x1234", 0);
#endif//#ifndef CONFIG_SYSTEM_RTOS //prue rtos not need dtb

	return 0;
}

#if !defined(SYSCTRL_SEC_STICKY_REG2) && defined(P_PREG_STICKY_REG2)
#define SYSCTRL_SEC_STICKY_REG2 P_PREG_STICKY_REG2
#endif//#if !defined(SYSCTRL_SEC_STICKY_REG2) && defined(P_PREG_STICKY_REG2)
int aml_board_late_init_tail(void *arg)
{
	unsigned char chipid[16];

	UNUSED(arg);
	printf("init tail\n");
	run_command("amlsecurecheck", 0);
	run_command("update_tries", 0);

	//Need save outputmode/connector_type to flash if changed after display drv init
	if (env_get("outputmode") || env_get("connector_type")) {
		run_command("printenv outputmode connector_type", 0);
		run_command("update_env_part -p -f outputmode connector_type", 0);
	}

	memset(chipid, 0, 16);
	env_set("cpu_id", "1234567890");
	if (get_chip_id(chipid, 16) != -1) {
		char chipid_str[32];
		int i, j;
		char buf_tmp[4];

		memset(chipid_str, 0, 32);

		char *buff = &chipid_str[0];

		for (i = 0, j = 0; i < 12; ++i) {
			sprintf(&buf_tmp[0], "%02x", chipid[15 - i]);
			if (strcmp(buf_tmp, "00") != 0) {
				sprintf(buff + j, "%02x", chipid[15 - i]);
				j = j + 2;
			}
		}
		env_set("cpu_id", chipid_str);
		printf("buff: %s\n", buff);
	}

//auto enter usb mode after board_late_init if 'adnl.exe setvar burnsteps 0x1b8ec003'
#if defined(CONFIG_AML_V3_FACTORY_BURN) && defined(CONFIG_AML_V3_USB_TOOl)
	if (readl(SYSCTRL_SEC_STICKY_REG2) == 0x1b8ec003)
		aml_v3_factory_usb_burning(0, gd->bd);
#endif//#if defined(CONFIG_AML_V3_FACTORY_BURN) && defined(CONFIG_AML_V3_USB_TOOl)
#ifdef CONFIG_AML_FACTORY_BURN_LOCAL_UPGRADE //try auto upgrade from ext-sdcard
	aml_try_factory_sdcard_burning(0, gd->bd);
#endif//#ifdef CONFIG_AML_FACTORY_BURN_LOCAL_UPGRADE

	return 0;
}
#endif//#ifdef CONFIG_BOARD_LATE_INIT

static int board_get_bootid(void)
{
	const cpu_id_t cpuid = get_cpu_id();
	const int familyId	 = cpuid.family_id;
	int boot_id = 0;

#ifdef SYSCTRL_SEC_STATUS_REG2
	if (MESON_CPU_MAJOR_ID_SC2 <= familyId && MESON_CPU_MAJOR_ID_C2 != familyId &&
		familyId != MESON_CPU_MAJOR_ID_T5W) {
		boot_id = readl(SYSCTRL_SEC_STATUS_REG2);
		boot_id = (boot_id >> 4) & 0xf;
	}
#endif// #ifdef SYSCTRL_SEC_STATUS_REG2

#if defined(P_AO_SEC_GP_CFG0)
	if ((familyId <= MESON_CPU_MAJOR_ID_T5D &&
		familyId != MESON_CPU_MAJOR_ID_SC2) ||
		familyId == MESON_CPU_MAJOR_ID_TXHD2 ||
		familyId == MESON_CPU_MAJOR_ID_T5W) {
		boot_id = readl(P_AO_SEC_GP_CFG0) & 0xf;
	}
#endif// #if defined(P_AO_SEC_GP_CFG0)

	return boot_id;
}

void board_set_boot_source(void)
{
	const char *source;

	switch (board_get_bootid()) {
	case BOOT_ID_EMMC:
		source = "emmc";
		break;

	case BOOT_ID_NAND:
		source = "nand";
		break;

	case BOOT_ID_SPI:
		source = "spi";
		break;

	case BOOT_ID_SDCARD:
		source = "sd";
		break;

	case BOOT_ID_USB:
		source = "usb";
		break;

	default:
		source = "unknown";
	}

	env_set("boot_source", source);
	printf("%s, boot_source: %s\n", __func__, source);
}

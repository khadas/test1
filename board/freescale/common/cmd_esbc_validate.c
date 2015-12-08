/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <fsl_validate.h>

static int do_esbc_halt(cmd_tbl_t *cmdtp, int flag, int argc,
				char * const argv[])
{
	printf("Core is entering spin loop.\n");
loop:
	goto loop;

	return 0;
}

static int do_esbc_validate(cmd_tbl_t *cmdtp, int flag, int argc,
				char * const argv[])
{
	char *hash_str = NULL;
	uintptr_t haddr;
	int ret;

	if (argc < 2)
		return cmd_usage(cmdtp);
	else if (argc > 2)
		/* Second arg - Optional - Hash Str*/
		hash_str = argv[2];

	/* First argument - header address -32/64bit */
	haddr = (uintptr_t)simple_strtoul(argv[1], NULL, 16);

	/* With esbc_validate command, Image address must be
	 * part of header. So, the function is called
	 * by passing this argument as 0.
	 */
	ret = fsl_secboot_validate(haddr, hash_str, 0);
	if (ret)
		return 1;

	printf("esbc_validate command successful\n");
	return 0;
}

/***************************************************/
static char esbc_validate_help_text[] =
	"esbc_validate hdr_addr <hash_val> - Validates signature using\n"
	"                          RSA verification\n"
	"                          $hdr_addr Address of header of the image\n"
	"                          to be validated.\n"
	"                          $hash_val -Optional\n"
	"                          It provides Hash of public/srk key to be\n"
	"                          used to verify signature.\n";

U_BOOT_CMD(
	esbc_validate,	3,	0,	do_esbc_validate,
	"Validates signature on a given image using RSA verification",
	esbc_validate_help_text
);

U_BOOT_CMD(
	esbc_halt,	1,	0,	do_esbc_halt,
	"Put the core in spin loop ",
	""
);

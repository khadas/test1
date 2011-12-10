/*
 * This file implements recording of each stage of the boot process. It is
 * intended to implement timing of each stage, reporting this information
 * to the user and passing it to the OS for logging / further analysis.
 *
 * Copyright (c) 2011 The Chromium OS Authors.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef _BOOTSTAGE_H
#define _BOOTSTAGE_H

/*
 * A list of boot stages that we know about. Each of these indicates the
 * state that we are at, and the action that we are about to perform. For
 * errors, we issue an error for an item when it fails. Therefore the
 * normal sequence is:
 *
 * progress action1
 * progress action2
 * progress action3
 *
 * and an error condition where action 3 failed would be:
 *
 * progress action1
 * progress action2
 * progress action3
 * error on action3
 */
enum bootstage_id {
	BOOTSTAGE_ID_START = 0,
	BOOTSTAGE_ID_CHECK_MAGIC,	/* Checking image magic */
	BOOTSTAGE_ID_CHECK_HEADER,	/* Checking image header */
	BOOTSTAGE_ID_CHECK_CHECKSUM,	/* Checking image checksum */
	BOOTSTAGE_ID_CHECK_ARCH,	/* Checking architecture */

	BOOTSTAGE_ID_CHECK_IMAGETYPE = 5,/* Checking image type */
	BOOTSTAGE_ID_DECOMP_IMAGE,	/* Decompressing image */
	BOOTSTAGE_ID_KERNEL_LOADED,	/* Kernel has been loaded */
	BOOTSTAGE_ID_DECOMP_UNIMPL = 7,	/* Odd decompression algorithm */
	BOOTSTAGE_ID_CHECK_BOOT_OS,	/* Calling OS-specific boot function */
	BOOTSTAGE_ID_BOOT_OS_RETURNED,	/* Tried to boot OS, but it returned */
	BOOTSTAGE_ID_CHECK_RAMDISK = 9,	/* Checking ram disk */

	BOOTSTAGE_ID_RD_MAGIC,		/* Checking ram disk magic */
	BOOTSTAGE_ID_RD_HDR_CHECKSUM,	/* Checking ram disk heder checksum */
	BOOTSTAGE_ID_RD_CHECKSUM,	/* Checking ram disk checksum */
	BOOTSTAGE_ID_COPY_RAMDISK = 12,	/* Copying ram disk into place */
	BOOTSTAGE_ID_RAMDISK,		/* Checking for valid ramdisk */
	BOOTSTAGE_ID_NO_RAMDISK,	/* No ram disk found (not an error) */

	BOOTSTAGE_ID_RUN_OS	= 15,	/* Exiting U-Boot, entering OS */

	BOOTSTAGE_ID_NEED_RESET = 30,
	BOOTSTAGE_ID_POST_FAIL,		/* Post failure */
	BOOTSTAGE_ID_POST_FAIL_R,	/* Post failure reported after reloc */

	/*
	 * This set is reported ony by x86, and the meaning is different. In
	 * this case we are reporting completion of a particular stage.
	 * This should probably change in he x86 code (which doesn't report
	 * errors in any case), but discussion this can perhaps wait until we
	 * have a generic board implementation.
	 */
	BOOTSTAGE_ID_BOARD_INIT_R,	/* We have relocated */
	BOOTSTAGE_ID_BOARD_GLOBAL_DATA,	/* Global data is set up */

	BOOTSTAGE_ID_BOARD_INIT_SEQ,	/* We completed the init sequence */
	BOOTSTAGE_ID_BOARD_FLASH,	/* We have configured flash banks */
	BOOTSTAGE_ID_BOARD_FLASH_37,	/* In case you didn't hear... */
	BOOTSTAGE_ID_BOARD_ENV,		/* Environment is relocated & ready */
	BOOTSTAGE_ID_BOARD_PCI,		/* PCI is up */

	BOOTSTAGE_ID_BOARD_INTERRUPTS,	/* Exceptions / interrupts ready */
	BOOTSTAGE_ID_BOARD_DONE,	/* Board init done, off to main loop */
	/* ^^^ here ends the x86 sequence */

};

/*
 * Board code can implement show_boot_progress() if needed.
 *
 * @param val	Progress state (enum bootstage_id), or -id if an error
 *		has occurred.
 */
void show_boot_progress(int val);
static inline void show_boot_error(int val)
{
	show_boot_progress(-val);
}

#endif

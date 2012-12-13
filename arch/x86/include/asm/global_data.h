/*
 * (C) Copyright 2002-2010
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

#ifndef	__ASM_GBL_DATA_H
#define __ASM_GBL_DATA_H

#ifndef __ASSEMBLY__

/* Architecture-specific global data */
struct arch_global_data {
	struct global_data *gd_addr;		/* Location of Global Data */
};

/*
 * The following data structure is placed in some memory wich is
 * available very early after boot (like DPRAM on MPC8xx/MPC82xx, or
 * some locked parts of the data cache) to allow for a minimum set of
 * global variables during system initialization (until we have set
 * up the memory controller so that we can use RAM).
 */

#include <asm/u-boot.h>

typedef struct global_data gd_t;

struct global_data {
	struct arch_global_data arch;	/* architecture-specific data */
	bd_t		*bd;
	unsigned long	flags;
	unsigned int	baudrate;
	unsigned long	have_console;	/* serial_init() was called */
#ifdef CONFIG_PRE_CONSOLE_BUFFER
	unsigned long	precon_buf_idx;	/* Pre-Console buffer index */
#endif
	unsigned long	reloc_off;	/* Relocation Offset */
	unsigned long	env_addr;	/* Address  of Environment struct */
	unsigned long	env_valid;	/* Checksum of Environment valid? */
	unsigned long	cpu_clk;	/* CPU clock in Hz!		*/
	unsigned long	bus_clk;
	unsigned long	relocaddr;	/* Start address of U-Boot in RAM */
	unsigned long	start_addr_sp;	/* start_addr_stackpointer */
	phys_size_t	ram_size;	/* RAM size */
	const void	*fdt_blob;	/* Our device tree, NULL if none */
	void		**jt;		/* jump table */
	char		env_buf[32];	/* buffer for getenv() before reloc. */
};

static inline gd_t *get_fs_gd_ptr(void)
{
	gd_t *gd_ptr;

	asm volatile("fs movl 0, %0\n" : "=r" (gd_ptr));

	return gd_ptr;
}

#define gd	get_fs_gd_ptr()

#endif

#include <asm-generic/global_data_flags.h>

/*
 * Our private Global Data Flags
 */
#define GD_FLG_COLD_BOOT	0x00100	/* Cold Boot */
#define GD_FLG_WARM_BOOT	0x00200	/* Warm Boot */

#define DECLARE_GLOBAL_DATA_PTR

#endif /* __ASM_GBL_DATA_H */

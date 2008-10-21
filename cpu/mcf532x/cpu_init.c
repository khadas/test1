/*
 *
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2007 Freescale Semiconductor, Inc.
 * TsiChung Liew (Tsi-Chung.Liew@freescale.com)
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

#include <common.h>
#include <watchdog.h>
#include <asm/immap.h>

#if defined(CONFIG_CMD_NET)
#include <config.h>
#include <net.h>
#include <asm/fec.h>
#endif

/*
 * Breath some life into the CPU...
 *
 * Set up the memory map,
 * initialize a bunch of registers,
 * initialize the UPM's
 */
void cpu_init_f(void)
{
	volatile scm1_t *scm1 = (scm1_t *) MMAP_SCM1;
	volatile scm2_t *scm2 = (scm2_t *) MMAP_SCM2;
	volatile gpio_t *gpio = (gpio_t *) MMAP_GPIO;
	volatile fbcs_t *fbcs = (fbcs_t *) MMAP_FBCS;
	volatile wdog_t *wdog = (wdog_t *) MMAP_WDOG;

	/* watchdog is enabled by default - disable the watchdog */
#ifndef CONFIG_WATCHDOG
	wdog->cr = 0;
#endif

	scm1->mpr0 = 0x77777777;
	scm2->pacra = 0;
	scm2->pacrb = 0;
	scm2->pacrc = 0;
	scm2->pacrd = 0;
	scm2->pacre = 0;
	scm2->pacrf = 0;
	scm2->pacrg = 0;
	scm1->pacrh = 0;

	/* Port configuration */
	gpio->par_cs = 0;

#if (defined(CONFIG_SYS_CS0_BASE) && defined(CONFIG_SYS_CS0_MASK) && defined(CONFIG_SYS_CS0_CTRL))
	fbcs->csar0 = CONFIG_SYS_CS0_BASE;
	fbcs->cscr0 = CONFIG_SYS_CS0_CTRL;
	fbcs->csmr0 = CONFIG_SYS_CS0_MASK;
#endif

#if (defined(CONFIG_SYS_CS1_BASE) && defined(CONFIG_SYS_CS1_MASK) && defined(CONFIG_SYS_CS1_CTRL))
	/* Latch chipselect */
	gpio->par_cs |= GPIO_PAR_CS1;
	fbcs->csar1 = CONFIG_SYS_CS1_BASE;
	fbcs->cscr1 = CONFIG_SYS_CS1_CTRL;
	fbcs->csmr1 = CONFIG_SYS_CS1_MASK;
#endif

#if (defined(CONFIG_SYS_CS2_BASE) && defined(CONFIG_SYS_CS2_MASK) && defined(CONFIG_SYS_CS2_CTRL))
	gpio->par_cs |= GPIO_PAR_CS2;
	fbcs->csar2 = CONFIG_SYS_CS2_BASE;
	fbcs->cscr2 = CONFIG_SYS_CS2_CTRL;
	fbcs->csmr2 = CONFIG_SYS_CS2_MASK;
#endif

#if (defined(CONFIG_SYS_CS3_BASE) && defined(CONFIG_SYS_CS3_MASK) && defined(CONFIG_SYS_CS3_CTRL))
	gpio->par_cs |= GPIO_PAR_CS3;
	fbcs->csar3 = CONFIG_SYS_CS3_BASE;
	fbcs->cscr3 = CONFIG_SYS_CS3_CTRL;
	fbcs->csmr3 = CONFIG_SYS_CS3_MASK;
#endif

#if (defined(CONFIG_SYS_CS4_BASE) && defined(CONFIG_SYS_CS4_MASK) && defined(CONFIG_SYS_CS4_CTRL))
	gpio->par_cs |= GPIO_PAR_CS4;
	fbcs->csar4 = CONFIG_SYS_CS4_BASE;
	fbcs->cscr4 = CONFIG_SYS_CS4_CTRL;
	fbcs->csmr4 = CONFIG_SYS_CS4_MASK;
#endif

#if (defined(CONFIG_SYS_CS5_BASE) && defined(CONFIG_SYS_CS5_MASK) && defined(CONFIG_SYS_CS5_CTRL))
	gpio->par_cs |= GPIO_PAR_CS5;
	fbcs->csar5 = CONFIG_SYS_CS5_BASE;
	fbcs->cscr5 = CONFIG_SYS_CS5_CTRL;
	fbcs->csmr5 = CONFIG_SYS_CS5_MASK;
#endif

#ifdef CONFIG_FSL_I2C
	gpio->par_feci2c = GPIO_PAR_FECI2C_SCL_SCL | GPIO_PAR_FECI2C_SDA_SDA;
#endif

	icache_enable();
}

/*
 * initialize higher level parts of CPU like timers
 */
int cpu_init_r(void)
{
	return (0);
}

void uart_port_conf(void)
{
	volatile gpio_t *gpio = (gpio_t *) MMAP_GPIO;

	/* Setup Ports: */
	switch (CONFIG_SYS_UART_PORT) {
	case 0:
		gpio->par_uart = (GPIO_PAR_UART_TXD0 | GPIO_PAR_UART_RXD0);
		break;
	case 1:
		gpio->par_uart =
		    (GPIO_PAR_UART_TXD1(3) | GPIO_PAR_UART_RXD1(3));
		break;
	case 2:
		gpio->par_timer &= 0x0F;
		gpio->par_timer |= (GPIO_PAR_TIN3_URXD2 | GPIO_PAR_TIN2_UTXD2);
		break;
	}
}

#if defined(CONFIG_CMD_NET)
int fecpin_setclear(struct eth_device *dev, int setclear)
{
	volatile gpio_t *gpio = (gpio_t *) MMAP_GPIO;

	if (setclear) {
		gpio->par_fec |= GPIO_PAR_FEC_7W_FEC | GPIO_PAR_FEC_MII_FEC;
		gpio->par_feci2c |=
		    GPIO_PAR_FECI2C_MDC_EMDC | GPIO_PAR_FECI2C_MDIO_EMDIO;
	} else {
		gpio->par_fec &= ~(GPIO_PAR_FEC_7W_FEC | GPIO_PAR_FEC_MII_FEC);
		gpio->par_feci2c &=
		    ~(GPIO_PAR_FECI2C_MDC_EMDC | GPIO_PAR_FECI2C_MDIO_EMDIO);
	}
	return 0;
}
#endif

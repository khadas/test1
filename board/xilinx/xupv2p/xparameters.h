/*
 * (C) Copyright 2007 Michal Simek
 *
 * Michal  SIMEK <monstr@monstr.eu>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * CAUTION: This file is automatically generated by libgen.
 * Version: Xilinx EDK 8.2.02 EDK_Im_Sp2.4
 */

/* System Clock Frequency */
#define XILINX_CLOCK_FREQ	100000000

/* Microblaze is microblaze_0 */
#define XILINX_USE_MSR_INSTR	1
#define XILINX_PVR	0
#define XILINX_FSL_NUMBER	0

/* Interrupt controller is opb_intc_0 */
#define XILINX_INTC_BASEADDR	0x41200000
#define XILINX_INTC_NUM_INTR_INPUTS	7

/* Timer pheriphery is opb_timer_1 */
#define XILINX_TIMER_BASEADDR	0x41c00000
#define XILINX_TIMER_IRQ	0

/* Uart pheriphery is RS232_Uart_1 */
#define XILINX_UARTLITE_BASEADDR	0x40600000
#define XILINX_UARTLITE_BAUDRATE	115200

/* IIC doesn't exist */

/* GPIO is LEDs_4Bit*/
#define XILINX_GPIO_BASEADDR	0x40000000

/* FLASH doesn't exist none */

/* Main Memory is DDR_256MB_32MX64_rank1_row13_col10_cl2_5 */
#define XILINX_RAM_START	0x30000000
#define XILINX_RAM_SIZE	0x10000000

/* Sysace Controller is SysACE_CompactFlash */
#define XILINX_SYSACE_BASEADDR	0x41800000
#define XILINX_SYSACE_MEM_WIDTH	16

/* Ethernet controller is Ethernet_MAC */
#define XILINX_EMAC_BASEADDR	0x40c00000
#define XILINX_EMAC_DMA_PRESENT	3
#define XILINX_EMAC_HALF_DUPLEX_EXIST	1
#define XILINX_EMAC_MII_EXIST	1

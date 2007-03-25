/*********************************************************************
#
# CAUTION: This file is automatically generated by libgen.
# Version: Xilinx EDK 6.3 EDK_Gmm.12.3
# Description: U-BOOT Configuration File
# Michal Simek - monstr@monstr.eu
#
**********************************************************************/

/* System Clock Frequency */
#define XILINX_CLOCK_FREQ	66666667

/* Interrupt controller is intc_0 */
#define XILINX_INTC_BASEADDR	0xd1000fc0
#define XILINX_INTC_NUM_INTR_INPUTS	12

/* Timer pheriphery is opb_timer_0 */
#define XILINX_TIMER_BASEADDR	0xa2000000
#define XILINX_TIMER_IRQ	0

/* Uart pheriphery is console_uart */
#define XILINX_UART_BASEADDR	0xa0000000
#define XILINX_UART_BAUDRATE	115200

/* GPIO is opb_gpio_0*/
#define XILINX_GPIO_BASEADDR	0x90000000

/* Flash Memory is opb_emc_0 */
#define XILINX_FLASH_START	0x28000000
#define XILINX_FLASH_SIZE	0x00800000

/* Main Memory is plb_ddr_0 */
#define XILINX_RAM_START	0x10000000
#define XILINX_RAM_SIZE	0x10000000

/* Sysace Controller is opb_sysace_0 */
#define XILINX_SYSACE_BASEADDR	0xCF000000
#define XILINX_SYSACE_HIGHADDR	0xCF0001FF
#define XILINX_SYSACE_MEM_WIDTH	16

/* Ethernet controller is opb_ethernet_0 */
#define XPAR_XEMAC_NUM_INSTANCES	1
#define XPAR_OPB_ETHERNET_0_DEVICE_ID	0
#define XPAR_OPB_ETHERNET_0_BASEADDR	0x60000000
#define XPAR_OPB_ETHERNET_0_HIGHADDR	0x60003FFF
#define XPAR_OPB_ETHERNET_0_DMA_PRESENT	1
#define XPAR_OPB_ETHERNET_0_ERR_COUNT_EXIST	1
#define XPAR_OPB_ETHERNET_0_MII_EXIST	1

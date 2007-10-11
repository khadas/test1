/*
 * (C) Copyright 2007
 * Stefan Roese, DENX Software Engineering, sr@denx.de.
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
#include <ppc4xx.h>
#include <ppc405.h>
#include <libfdt.h>
#include <asm/processor.h>
#include <asm-ppc/io.h>

#if defined(CONFIG_PCI)
#include <pci.h>
#include <asm/4xx_pcie.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

extern flash_info_t flash_info[CFG_MAX_FLASH_BANKS]; /* info for FLASH chips	*/

void fpga_init(void)
{
	/*
	 * Set FPGA regs
	 */
	out32(CFG_FPGA_BASE, 0xff570cc0);
}

/*
 * Board early initialization function
 */
int board_early_init_f (void)
{
	u32 val;

	/*--------------------------------------------------------------------+
	 | Interrupt controller setup for the AMCC 405EX(r) PINE evaluation board.
	 +--------------------------------------------------------------------+
	+---------------------------------------------------------------------+
	|Interrupt| Source                            | Pol.  | Sensi.| Crit. |
	+---------+-----------------------------------+-------+-------+-------+
	| IRQ 00  | UART0                             | High  | Level | Non   |
	| IRQ 01  | UART1                             | High  | Level | Non   |
	| IRQ 02  | IIC0                              | High  | Level | Non   |
	| IRQ 03  | TBD                               | High  | Level | Non   |
	| IRQ 04  | TBD                               | High  | Level | Non   |
	| IRQ 05  | EBM                               | High  | Level | Non   |
	| IRQ 06  | BGI                               | High  | Level | Non   |
	| IRQ 07  | IIC1                              | Rising| Edge  | Non   |
	| IRQ 08  | SPI                               | High  | Lvl/ed| Non   |
	| IRQ 09  | External IRQ 0 - (PCI-Express)    | pgm H | Pgm   | Non   |
	| IRQ 10  | MAL TX EOB                        | High  | Level | Non   |
	| IRQ 11  | MAL RX EOB                        | High  | Level | Non   |
	| IRQ 12  | DMA Channel 0 FIFO Full           | High  | Level | Non   |
	| IRQ 13  | DMA Channel 0 Stat FIFO           | High  | Level | Non   |
	| IRQ 14  | DMA Channel 1 FIFO Full           | High  | Level | Non   |
	| IRQ 15  | DMA Channel 1 Stat FIFO           | High  | Level | Non   |
	| IRQ 16  | PCIE0 AL                          | high  | Level | Non   |
	| IRQ 17  | PCIE0 VPD access                  | rising| Edge  | Non   |
	| IRQ 18  | PCIE0 hot reset request           | rising| Edge  | Non   |
	| IRQ 19  | PCIE0 hot reset request           | faling| Edge  | Non   |
	| IRQ 20  | PCIE0 TCR                         | High  | Level | Non   |
	| IRQ 21  | PCIE0 MSI level0                  | High  | Level | Non   |
	| IRQ 22  | PCIE0 MSI level1                  | High  | Level | Non   |
	| IRQ 23  | Security EIP-94                   | High  | Level | Non   |
	| IRQ 24  | EMAC0 interrupt                   | High  | Level | Non   |
	| IRQ 25  | EMAC1 interrupt                   | High  | Level | Non   |
	| IRQ 26  | PCIE0 MSI level2                  | High  | Level | Non   |
	| IRQ 27  | External IRQ 4                    | pgm H | Pgm   | Non   |
	| IRQ 28  | UIC2 Non-critical Int.            | High  | Level | Non   |
	| IRQ 29  | UIC2 Critical Interrupt           | High  | Level | Crit. |
	| IRQ 30  | UIC1 Non-critical Int.            | High  | Level | Non   |
	| IRQ 31  | UIC1 Critical Interrupt           | High  | Level | Crit. |
	|----------------------------------------------------------------------
	| IRQ 32  | MAL Serr                          | High  | Level | Non   |
	| IRQ 33  | MAL Txde                          | High  | Level | Non   |
	| IRQ 34  | MAL Rxde                          | High  | Level | Non   |
	| IRQ 35  | PCIE0 bus master VC0              |falling| Edge  | Non   |
	| IRQ 36  | PCIE0 DCR Error                   | High  | Level | Non   |
	| IRQ 37  | EBC                               | High  |Lvl Edg| Non   |
	| IRQ 38  | NDFC                              | High  | Level | Non   |
	| IRQ 39  | GPT Compare Timer 8               | Risin | Edge  | Non   |
	| IRQ 40  | GPT Compare Timer 9               | Risin | Edge  | Non   |
	| IRQ 41  | PCIE1 AL                          | high  | Level | Non   |
	| IRQ 42  | PCIE1 VPD access                  | rising| edge  | Non   |
	| IRQ 43  | PCIE1 hot reset request           | rising| Edge  | Non   |
	| IRQ 44  | PCIE1 hot reset request           | faling| Edge  | Non   |
	| IRQ 45  | PCIE1 TCR                         | High  | Level | Non   |
	| IRQ 46  | PCIE1 bus master VC0              |falling| Edge  | Non   |
	| IRQ 47  | GPT Compare Timer 3               | Risin | Edge  | Non   |
	| IRQ 48  | GPT Compare Timer 4               | Risin | Edge  | Non   |
	| IRQ 49  | Ext. IRQ 7                        |pgm/Fal|pgm/Lvl| Non   |
	| IRQ 50  | Ext. IRQ 8 -                      |pgm (H)|pgm/Lvl| Non   |
	| IRQ 51  | Ext. IRQ 9                        |pgm (H)|pgm/Lvl| Non   |
	| IRQ 52  | GPT Compare Timer 5               | high  | Edge  | Non   |
	| IRQ 53  | GPT Compare Timer 6               | high  | Edge  | Non   |
	| IRQ 54  | GPT Compare Timer 7               | high  | Edge  | Non   |
	| IRQ 55  | Serial ROM                        | High  | Level | Non   |
	| IRQ 56  | GPT Decrement Pulse               | High  | Level | Non   |
	| IRQ 57  | Ext. IRQ 2                        |pgm/Fal|pgm/Lvl| Non   |
	| IRQ 58  | Ext. IRQ 5                        |pgm/Fal|pgm/Lvl| Non   |
	| IRQ 59  | Ext. IRQ 6                        |pgm/Fal|pgm/Lvl| Non   |
	| IRQ 60  | EMAC0 Wake-up                     | High  | Level | Non   |
	| IRQ 61  | Ext. IRQ 1                        |pgm/Fal|pgm/Lvl| Non   |
	| IRQ 62  | EMAC1 Wake-up                     | High  | Level | Non   |
	|----------------------------------------------------------------------
	| IRQ 64  | PE0 AL                            | High  | Level | Non   |
	| IRQ 65  | PE0 VPD Access                    | Risin | Edge  | Non   |
	| IRQ 66  | PE0 Hot Reset Request             | Risin | Edge  | Non   |
	| IRQ 67  | PE0 Hot Reset Request             | Falli | Edge  | Non   |
	| IRQ 68  | PE0 TCR                           | High  | Level | Non   |
	| IRQ 69  | PE0 BusMaster VCO                 | Falli | Edge  | Non   |
	| IRQ 70  | PE0 DCR Error                     | High  | Level | Non   |
	| IRQ 71  | Reserved                          | N/A   | N/A   | Non   |
	| IRQ 72  | PE1 AL                            | High  | Level | Non   |
	| IRQ 73  | PE1 VPD Access                    | Risin | Edge  | Non   |
	| IRQ 74  | PE1 Hot Reset Request             | Risin | Edge  | Non   |
	| IRQ 75  | PE1 Hot Reset Request             | Falli | Edge  | Non   |
	| IRQ 76  | PE1 TCR                           | High  | Level | Non   |
	| IRQ 77  | PE1 BusMaster VCO                 | Falli | Edge  | Non   |
	| IRQ 78  | PE1 DCR Error                     | High  | Level | Non   |
	| IRQ 79  | Reserved                          | N/A   | N/A   | Non   |
	| IRQ 80  | PE2 AL                            | High  | Level | Non   |
	| IRQ 81  | PE2 VPD Access                    | Risin | Edge  | Non   |
	| IRQ 82  | PE2 Hot Reset Request             | Risin | Edge  | Non   |
	| IRQ 83  | PE2 Hot Reset Request             | Falli | Edge  | Non   |
	| IRQ 84  | PE2 TCR                           | High  | Level | Non   |
	| IRQ 85  | PE2 BusMaster VCO                 | Falli | Edge  | Non   |
	| IRQ 86  | PE2 DCR Error                     | High  | Level | Non   |
	| IRQ 87  | Reserved                          | N/A   | N/A   | Non   |
	| IRQ 88  | External IRQ(5)                   | Progr | Progr | Non   |
	| IRQ 89  | External IRQ 4 - Ethernet         | Progr | Progr | Non   |
	| IRQ 90  | External IRQ 3 - PCI-X            | Progr | Progr | Non   |
	| IRQ 91  | External IRQ 2 - PCI-X            | Progr | Progr | Non   |
	| IRQ 92  | External IRQ 1 - PCI-X            | Progr | Progr | Non   |
	| IRQ 93  | External IRQ 0 - PCI-X            | Progr | Progr | Non   |
	| IRQ 94  | Reserved                          | N/A   | N/A   | Non   |
	| IRQ 95  | Reserved                          | N/A   | N/A   | Non   |
	|---------------------------------------------------------------------
	+---------+-----------------------------------+-------+-------+------*/
	/*--------------------------------------------------------------------+
	 | Initialise UIC registers.  Clear all interrupts.  Disable all
	 | interrupts.
	 | Set critical interrupt values.  Set interrupt polarities.  Set
	 | interrupt trigger levels.  Make bit 0 High  priority.  Clear all
	 | interrupts again.
	 +-------------------------------------------------------------------*/

	mtdcr (uic2sr, 0xffffffff);	/* Clear all interrupts */
	mtdcr (uic2er, 0x00000000);	/* disable all interrupts */
	mtdcr (uic2cr, 0x00000000);	/* Set Critical / Non Critical interrupts */
	mtdcr (uic2pr, 0xf7ffffff);	/* Set Interrupt Polarities */
	mtdcr (uic2tr, 0x01e1fff8);	/* Set Interrupt Trigger Levels */
	mtdcr (uic2vr, 0x00000001);	/* Set Vect base=0,INT31 Highest priority */
	mtdcr (uic2sr, 0x00000000);	/* clear all interrupts */
	mtdcr (uic2sr, 0xffffffff);	/* clear all interrupts */

	mtdcr (uic1sr, 0xffffffff);	/* Clear all interrupts */
	mtdcr (uic1er, 0x00000000);	/* disable all interrupts */
	mtdcr (uic1cr, 0x00000000);	/* Set Critical / Non Critical interrupts */
	mtdcr (uic1pr, 0xfffac785);	/* Set Interrupt Polarities */
	mtdcr (uic1tr, 0x001d0040);	/* Set Interrupt Trigger Levels */
	mtdcr (uic1vr, 0x00000001);	/* Set Vect base=0,INT31 Highest priority */
	mtdcr (uic1sr, 0x00000000);	/* clear all interrupts */
	mtdcr (uic1sr, 0xffffffff);	/* clear all interrupts */

	mtdcr (uic0sr, 0xffffffff);	/* Clear all interrupts */
	mtdcr (uic0er, 0x0000000a);	/* Disable all interrupts */
					/* Except cascade UIC0 and UIC1 */
	mtdcr (uic0cr, 0x00000000);	/* Set Critical / Non Critical interrupts */
	mtdcr (uic0pr, 0xffbfefef);	/* Set Interrupt Polarities */
	mtdcr (uic0tr, 0x00007000);	/* Set Interrupt Trigger Levels */
	mtdcr (uic0vr, 0x00000001);	/* Set Vect base=0,INT31 Highest priority */
	mtdcr (uic0sr, 0x00000000);	/* clear all interrupts */
	mtdcr (uic0sr, 0xffffffff);	/* clear all interrupts */

	/*
	 * Note: Some cores are still in reset when the chip starts, so
	 * take them out of reset
	 */
	mtsdr(SDR0_SRST, 0);

	fpga_init();

	/* Configure 405EX for NAND usage */
	val = SDR0_CUST0_MUX_NDFC_SEL |
		SDR0_CUST0_NDFC_ENABLE |
		SDR0_CUST0_NDFC_BW_8_BIT |
		SDR0_CUST0_NRB_BUSY |
		(0x80000000 >> (28 + CFG_NAND_CS));
	mtsdr(SDR0_CUST0, val);

	return 0;
}

int misc_init_r(void)
{
#ifdef CFG_ENV_IS_IN_FLASH
	/* Monitor protection ON by default */
	flash_protect(FLAG_PROTECT_SET,
		      -CFG_MONITOR_LEN,
		      0xffffffff,
		      &flash_info[0]);
#endif

	return 0;
}

int checkboard (void)
{
	char *s = getenv("serial#");

	printf("Board: Kilauea - AMCC PPC405EX Evaluation Board");

	if (s != NULL) {
		puts(", serial# ");
		puts(s);
	}
	putc('\n');

	return (0);
}

/*************************************************************************
 *  pci_pre_init
 *
 *  This routine is called just prior to registering the hose and gives
 *  the board the opportunity to check things. Returning a value of zero
 *  indicates that things are bad & PCI initialization should be aborted.
 *
 *      Different boards may wish to customize the pci controller structure
 *      (add regions, override default access routines, etc) or perform
 *      certain pre-initialization actions.
 *
 ************************************************************************/
#if defined(CONFIG_PCI)
int pci_pre_init(struct pci_controller * hose )
{
	return 0;
}
#endif  /* defined(CONFIG_PCI) */

/*************************************************************************
 *  pci_target_init
 *
 *      The bootstrap configuration provides default settings for the pci
 *      inbound map (PIM). But the bootstrap config choices are limited and
 *      may not be sufficient for a given board.
 *
 ************************************************************************/
#if defined(CONFIG_PCI) && defined(CFG_PCI_TARGET_INIT)
void pci_target_init(struct pci_controller * hose )
{
	/*-------------------------------------------------------------------+
	 * Disable everything
	 *-------------------------------------------------------------------*/
	out32r( PCIX0_PIM0SA, 0 ); /* disable */
	out32r( PCIX0_PIM1SA, 0 ); /* disable */
	out32r( PCIX0_PIM2SA, 0 ); /* disable */
	out32r( PCIX0_EROMBA, 0 ); /* disable expansion rom */

	/*-------------------------------------------------------------------+
	 * Map all of SDRAM to PCI address 0x0000_0000. Note that the 440
	 * strapping options to not support sizes such as 128/256 MB.
	 *-------------------------------------------------------------------*/
	out32r( PCIX0_PIM0LAL, CFG_SDRAM_BASE );
	out32r( PCIX0_PIM0LAH, 0 );
	out32r( PCIX0_PIM0SA, ~(gd->ram_size - 1) | 1 );

	out32r( PCIX0_BAR0, 0 );

	/*-------------------------------------------------------------------+
	 * Program the board's subsystem id/vendor id
	 *-------------------------------------------------------------------*/
	out16r( PCIX0_SBSYSVID, CFG_PCI_SUBSYS_VENDORID );
	out16r( PCIX0_SBSYSID, CFG_PCI_SUBSYS_DEVICEID );

	out16r( PCIX0_CMD, in16r(PCIX0_CMD) | PCI_COMMAND_MEMORY );
}
#endif	/* defined(CONFIG_PCI) && defined(CFG_PCI_TARGET_INIT) */

#ifdef CONFIG_PCI
static int pcie_port_is_rootpoint(int port)
{
	return 1;
}

static struct pci_controller pcie_hose[2] = {{0},{0}};

void pcie_setup_hoses(int busno)
{
	struct pci_controller *hose;
	int i, bus;
	bus = busno;
	char *env;
	unsigned int delay;

	for (i = 0; i < 2; i++) {

		if (pcie_port_is_rootpoint(i)) {
			printf("PORT%d will be configured as root-complex\n", i);
			if (ppc4xx_init_pcie_rootport(i)) {
				printf("PCIE%d: initialization failed\n", i);
				continue;
			}
		} else {
			printf("PORT%d will be configured as endpoint\n", i);
			if (ppc4xx_init_pcie_endport(i)) {
				printf("PCIE%d: initialization failed\n", i);
				continue;
			}
		}

		hose = &pcie_hose[i];
		hose->first_busno = bus;
		hose->last_busno = bus;
		hose->current_busno = bus;

		/* setup mem resource */
		pci_set_region(hose->regions + 0,
			       CFG_PCIE_MEMBASE + i * CFG_PCIE_MEMSIZE,
			       CFG_PCIE_MEMBASE + i * CFG_PCIE_MEMSIZE,
			       CFG_PCIE_MEMSIZE,
			       PCI_REGION_MEM);
		hose->region_count = 1;
		pci_register_hose(hose);

		if (pcie_port_is_rootpoint(i))
			ppc4xx_setup_pcie_rootpoint(hose, i);
		else
			ppc4xx_setup_pcie_endpoint(hose, i);

		env = getenv("pciscandelay");
		if (env != NULL) {
			delay = simple_strtoul(env, NULL, 10);
			if (delay > 5)
				printf("Warning, expect noticable delay before PCIe"
				       "scan due to 'pciscandelay' value!\n");
			mdelay(delay * 1000);
		}

		/*
		 * Config access can only go down stream
		 */
		hose->last_busno = pci_hose_scan(hose);
		bus = hose->last_busno + 1;
	}
}
#endif

#if defined(CONFIG_POST)
/*
 * Returns 1 if keys pressed to start the power-on long-running tests
 * Called from board_init_f().
 */
int post_hotkeys_pressed(void)
{
	return 0;	/* No hotkeys supported */
}
#endif /* CONFIG_POST */

#if defined(CONFIG_OF_LIBFDT) && defined(CONFIG_OF_BOARD_SETUP)
void ft_board_setup(void *blob, bd_t *bd)
{
	u32 val[4];
	int rc;

	ft_cpu_setup(blob, bd);

	/* Fixup NOR mapping */
	val[0] = 0;				/* chip select number */
	val[1] = 0;				/* always 0 */
	val[2] = gd->bd->bi_flashstart;
	val[3] = gd->bd->bi_flashsize;
	rc = fdt_find_and_setprop(blob, "/plb/opb/ebc", "ranges",
				  val, sizeof(val), 1);
	if (rc)
		printf("Unable to update property NOR mapping, err=%s\n",
		       fdt_strerror(rc));
}
#endif /* defined(CONFIG_OF_LIBFDT) && defined(CONFIG_OF_BOARD_SETUP) */

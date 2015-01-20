/*
 * Copyright (c) 2010, CompuLab, Ltd.
 * Author: Mike Rapoport <mike@compulab.co.il>
 *
 * Based on NVIDIA PCIe driver
 * Copyright (c) 2008-2009, NVIDIA Corporation.
 *
 * Copyright (c) 2013-2014, NVIDIA Corporation.
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#define DEBUG
#define pr_fmt(fmt) "tegra-pcie: " fmt

#include <common.h>
#include <errno.h>
#include <fdtdec.h>
#include <malloc.h>
#include <pci.h>

#include <asm/io.h>
#include <asm/gpio.h>

#include <asm/arch/clock.h>
#include <asm/arch/powergate.h>
#include <asm/arch-tegra/xusb-padctl.h>

#include <linux/list.h>

#include <dt-bindings/pinctrl/pinctrl-tegra-xusb.h>

DECLARE_GLOBAL_DATA_PTR;

#define AFI_AXI_BAR0_SZ	0x00
#define AFI_AXI_BAR1_SZ	0x04
#define AFI_AXI_BAR2_SZ	0x08
#define AFI_AXI_BAR3_SZ	0x0c
#define AFI_AXI_BAR4_SZ	0x10
#define AFI_AXI_BAR5_SZ	0x14

#define AFI_AXI_BAR0_START	0x18
#define AFI_AXI_BAR1_START	0x1c
#define AFI_AXI_BAR2_START	0x20
#define AFI_AXI_BAR3_START	0x24
#define AFI_AXI_BAR4_START	0x28
#define AFI_AXI_BAR5_START	0x2c

#define AFI_FPCI_BAR0	0x30
#define AFI_FPCI_BAR1	0x34
#define AFI_FPCI_BAR2	0x38
#define AFI_FPCI_BAR3	0x3c
#define AFI_FPCI_BAR4	0x40
#define AFI_FPCI_BAR5	0x44

#define AFI_CACHE_BAR0_SZ	0x48
#define AFI_CACHE_BAR0_ST	0x4c
#define AFI_CACHE_BAR1_SZ	0x50
#define AFI_CACHE_BAR1_ST	0x54

#define AFI_MSI_BAR_SZ		0x60
#define AFI_MSI_FPCI_BAR_ST	0x64
#define AFI_MSI_AXI_BAR_ST	0x68

#define AFI_CONFIGURATION		0xac
#define  AFI_CONFIGURATION_EN_FPCI	(1 << 0)

#define AFI_FPCI_ERROR_MASKS	0xb0

#define AFI_INTR_MASK		0xb4
#define  AFI_INTR_MASK_INT_MASK	(1 << 0)
#define  AFI_INTR_MASK_MSI_MASK	(1 << 8)

#define AFI_SM_INTR_ENABLE	0xc4
#define  AFI_SM_INTR_INTA_ASSERT	(1 << 0)
#define  AFI_SM_INTR_INTB_ASSERT	(1 << 1)
#define  AFI_SM_INTR_INTC_ASSERT	(1 << 2)
#define  AFI_SM_INTR_INTD_ASSERT	(1 << 3)
#define  AFI_SM_INTR_INTA_DEASSERT	(1 << 4)
#define  AFI_SM_INTR_INTB_DEASSERT	(1 << 5)
#define  AFI_SM_INTR_INTC_DEASSERT	(1 << 6)
#define  AFI_SM_INTR_INTD_DEASSERT	(1 << 7)

#define AFI_AFI_INTR_ENABLE		0xc8
#define  AFI_INTR_EN_INI_SLVERR		(1 << 0)
#define  AFI_INTR_EN_INI_DECERR		(1 << 1)
#define  AFI_INTR_EN_TGT_SLVERR		(1 << 2)
#define  AFI_INTR_EN_TGT_DECERR		(1 << 3)
#define  AFI_INTR_EN_TGT_WRERR		(1 << 4)
#define  AFI_INTR_EN_DFPCI_DECERR	(1 << 5)
#define  AFI_INTR_EN_AXI_DECERR		(1 << 6)
#define  AFI_INTR_EN_FPCI_TIMEOUT	(1 << 7)
#define  AFI_INTR_EN_PRSNT_SENSE	(1 << 8)

#define AFI_PCIE_CONFIG					0x0f8
#define  AFI_PCIE_CONFIG_PCIE_DISABLE(x)		(1 << ((x) + 1))
#define  AFI_PCIE_CONFIG_PCIE_DISABLE_ALL		0xe
#define  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_MASK	(0xf << 20)
#define  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_SINGLE	(0x0 << 20)
#define  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_420	(0x0 << 20)
#define  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X2_X1	(0x0 << 20)
#define  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_DUAL	(0x1 << 20)
#define  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_222	(0x1 << 20)
#define  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X4_X1	(0x1 << 20)
#define  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_411	(0x2 << 20)

#define AFI_FUSE			0x104
#define  AFI_FUSE_PCIE_T0_GEN2_DIS	(1 << 2)

#define AFI_PEX0_CTRL			0x110
#define AFI_PEX1_CTRL			0x118
#define AFI_PEX2_CTRL			0x128
#define  AFI_PEX_CTRL_RST		(1 << 0)
#define  AFI_PEX_CTRL_CLKREQ_EN		(1 << 1)
#define  AFI_PEX_CTRL_REFCLK_EN		(1 << 3)
#define  AFI_PEX_CTRL_OVERRIDE_EN	(1 << 4)

#define AFI_PLLE_CONTROL		0x160
#define  AFI_PLLE_CONTROL_BYPASS_PADS2PLLE_CONTROL (1 << 9)
#define  AFI_PLLE_CONTROL_PADS2PLLE_CONTROL_EN (1 << 1)

#define AFI_PEXBIAS_CTRL_0		0x168

#define PADS_CTL_SEL		0x0000009C

#define PADS_CTL		0x000000A0
#define  PADS_CTL_IDDQ_1L	(1 <<  0)
#define  PADS_CTL_TX_DATA_EN_1L	(1 <<  6)
#define  PADS_CTL_RX_DATA_EN_1L	(1 << 10)

#define PADS_PLL_CTL_TEGRA20			0x000000B8
#define PADS_PLL_CTL_TEGRA30			0x000000B4
#define  PADS_PLL_CTL_RST_B4SM			(0x1 <<  1)
#define  PADS_PLL_CTL_LOCKDET			(0x1 <<  8)
#define  PADS_PLL_CTL_REFCLK_MASK		(0x3 << 16)
#define  PADS_PLL_CTL_REFCLK_INTERNAL_CML	(0x0 << 16)
#define  PADS_PLL_CTL_REFCLK_INTERNAL_CMOS	(0x1 << 16)
#define  PADS_PLL_CTL_REFCLK_EXTERNAL		(0x2 << 16)
#define  PADS_PLL_CTL_TXCLKREF_MASK		(0x1 << 20)
#define  PADS_PLL_CTL_TXCLKREF_DIV10		(0x0 << 20)
#define  PADS_PLL_CTL_TXCLKREF_DIV5		(0x1 << 20)
#define  PADS_PLL_CTL_TXCLKREF_BUF_EN		(0x1 << 22)

#define PADS_REFCLK_CFG0			0x000000C8
#define PADS_REFCLK_CFG1			0x000000CC

/*
 * Fields in PADS_REFCLK_CFG*. Those registers form an array of 16-bit
 * entries, one entry per PCIe port. These field definitions and desired
 * values aren't in the TRM, but do come from NVIDIA.
 */
#define PADS_REFCLK_CFG_TERM_SHIFT		2  /* 6:2 */
#define PADS_REFCLK_CFG_E_TERM_SHIFT		7
#define PADS_REFCLK_CFG_PREDI_SHIFT		8  /* 11:8 */
#define PADS_REFCLK_CFG_DRVI_SHIFT		12 /* 15:12 */

/* Default value provided by HW engineering is 0xfa5c */
#define PADS_REFCLK_CFG_VALUE \
	( \
		(0x17 << PADS_REFCLK_CFG_TERM_SHIFT)   | \
		(0    << PADS_REFCLK_CFG_E_TERM_SHIFT) | \
		(0xa  << PADS_REFCLK_CFG_PREDI_SHIFT)  | \
		(0xf  << PADS_REFCLK_CFG_DRVI_SHIFT)     \
	)

#define RP_VEND_XP	0x00000F00
#define  RP_VEND_XP_DL_UP	(1 << 30)

#define RP_PRIV_MISC	0x00000FE0
#define  RP_PRIV_MISC_PRSNT_MAP_EP_PRSNT (0xE << 0)
#define  RP_PRIV_MISC_PRSNT_MAP_EP_ABSNT (0xF << 0)

#define RP_LINK_CONTROL_STATUS			0x00000090
#define  RP_LINK_CONTROL_STATUS_DL_LINK_ACTIVE	0x20000000
#define  RP_LINK_CONTROL_STATUS_LINKSTAT_MASK	0x3fff0000

struct tegra_pcie;

struct tegra_pcie_port {
	struct tegra_pcie *pcie;

	struct fdt_resource regs;
	unsigned int num_lanes;
	unsigned int index;

	struct list_head list;
};

struct tegra_pcie_soc {
	unsigned int num_ports;
	unsigned long pads_pll_ctl;
	unsigned long tx_ref_sel;
	bool has_pex_clkreq_en;
	bool has_pex_bias_ctrl;
	bool has_cml_clk;
	bool has_gen2;
};

struct tegra_pcie {
	struct pci_controller hose;

	struct fdt_resource pads;
	struct fdt_resource afi;
	struct fdt_resource cs;

	struct fdt_resource prefetch;
	struct fdt_resource mem;
	struct fdt_resource io;

	struct list_head ports;
	unsigned long xbar;

	const struct tegra_pcie_soc *soc;
	struct tegra_xusb_phy *phy;
};

static inline struct tegra_pcie *to_tegra_pcie(struct pci_controller *hose)
{
	return container_of(hose, struct tegra_pcie, hose);
}

static void afi_writel(struct tegra_pcie *pcie, unsigned long value,
		       unsigned long offset)
{
	writel(value, pcie->afi.start + offset);
}

static unsigned long afi_readl(struct tegra_pcie *pcie, unsigned long offset)
{
	return readl(pcie->afi.start + offset);
}

static void pads_writel(struct tegra_pcie *pcie, unsigned long value,
			unsigned long offset)
{
	writel(value, pcie->pads.start + offset);
}

static unsigned long pads_readl(struct tegra_pcie *pcie, unsigned long offset)
{
	return readl(pcie->pads.start + offset);
}

static unsigned long rp_readl(struct tegra_pcie_port *port,
			      unsigned long offset)
{
	return readl(port->regs.start + offset);
}

static void rp_writel(struct tegra_pcie_port *port, unsigned long value,
		      unsigned long offset)
{
	writel(value, port->regs.start + offset);
}

static unsigned long tegra_pcie_conf_offset(pci_dev_t bdf, int where)
{
	return ((where & 0xf00) << 16) | (PCI_BUS(bdf) << 16) |
	       (PCI_DEV(bdf) << 11) | (PCI_FUNC(bdf) << 8) |
	       (where & 0xfc);
}

static int tegra_pcie_conf_address(struct tegra_pcie *pcie, pci_dev_t bdf,
				   int where, unsigned long *address)
{
	unsigned int bus = PCI_BUS(bdf);

	if (bus == 0) {
		unsigned int dev = PCI_DEV(bdf);
		struct tegra_pcie_port *port;

		list_for_each_entry(port, &pcie->ports, list) {
			if (port->index + 1 == dev) {
				*address = port->regs.start + (where & ~3);
				return 0;
			}
		}
	} else {
		*address = pcie->cs.start + tegra_pcie_conf_offset(bdf, where);
		return 0;
	}

	return -1;
}

static int tegra_pcie_read_conf(struct pci_controller *hose, pci_dev_t bdf,
				int where, u32 *value)
{
	struct tegra_pcie *pcie = to_tegra_pcie(hose);
	unsigned long address;
	int err;

	err = tegra_pcie_conf_address(pcie, bdf, where, &address);
	if (err < 0) {
		*value = 0xffffffff;
		return 1;
	}

	*value = readl(address);

	/* fixup root port class */
	if (PCI_BUS(bdf) == 0) {
		if (where == PCI_CLASS_REVISION) {
			*value &= ~0x00ff0000;
			*value |= PCI_CLASS_BRIDGE_PCI << 16;
		}
	}

	return 0;
}

static int tegra_pcie_write_conf(struct pci_controller *hose, pci_dev_t bdf,
				 int where, u32 value)
{
	struct tegra_pcie *pcie = to_tegra_pcie(hose);
	unsigned long address;
	int err;

	err = tegra_pcie_conf_address(pcie, bdf, where, &address);
	if (err < 0)
		return 1;

	writel(value, address);

	return 0;
}

static int tegra_pcie_port_parse_dt(const void *fdt, int node,
				    struct tegra_pcie_port *port)
{
	const u32 *addr;
	int len;

	addr = fdt_getprop(fdt, node, "assigned-addresses", &len);
	if (!addr) {
		error("property \"assigned-addresses\" not found");
		return -FDT_ERR_NOTFOUND;
	}

	port->regs.start = fdt32_to_cpu(addr[2]);
	port->regs.end = port->regs.start + fdt32_to_cpu(addr[4]);

	return 0;
}

static int tegra_pcie_get_xbar_config(const void *fdt, int node, u32 lanes,
				      unsigned long *xbar)
{
	enum fdt_compat_id id = fdtdec_lookup(fdt, node);

	switch (id) {
	case COMPAT_NVIDIA_TEGRA20_PCIE:
		switch (lanes) {
		case 0x00000004:
			debug("single-mode configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_SINGLE;
			return 0;

		case 0x00000202:
			debug("dual-mode configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_DUAL;
			return 0;
		}
		break;

	case COMPAT_NVIDIA_TEGRA30_PCIE:
		switch (lanes) {
		case 0x00000204:
			debug("4x1, 2x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_420;
			return 0;

		case 0x00020202:
			debug("2x3 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_222;
			return 0;

		case 0x00010104:
			debug("4x1, 1x2 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_411;
			return 0;
		}
		break;

	case COMPAT_NVIDIA_TEGRA124_PCIE:
		switch (lanes) {
		case 0x0000104:
			debug("4x1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X4_X1;
			return 0;

		case 0x0000102:
			debug("2x1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X2_X1;
			return 0;
		}
		break;

	default:
		break;
	}

	return -FDT_ERR_NOTFOUND;
}

static int tegra_pcie_parse_dt_ranges(const void *fdt, int node,
				      struct tegra_pcie *pcie)
{
	const u32 *ptr, *end;
	int len;

	ptr = fdt_getprop(fdt, node, "ranges", &len);
	if (!ptr) {
		error("missing \"ranges\" property");
		return -FDT_ERR_NOTFOUND;
	}

	end = ptr + len / 4;

	while (ptr < end) {
		struct fdt_resource *res = NULL;
		u32 space = fdt32_to_cpu(*ptr);

		switch ((space >> 24) & 0x3) {
		case 0x01:
			res = &pcie->io;
			break;

		case 0x02: /* 32 bit */
		case 0x03: /* 64 bit */
			if (space & (1 << 30))
				res = &pcie->prefetch;
			else
				res = &pcie->mem;

			break;
		}

		if (res) {
			res->start = fdt32_to_cpu(ptr[3]);
			res->end = res->start + fdt32_to_cpu(ptr[5]);
		}

		ptr += 3 + 1 + 2;
	}

	debug("PCI regions:\n");
	debug("  I/O: %#x-%#x\n", pcie->io.start, pcie->io.end);
	debug("  non-prefetchable memory: %#x-%#x\n", pcie->mem.start,
	      pcie->mem.end);
	debug("  prefetchable memory: %#x-%#x\n", pcie->prefetch.start,
	      pcie->prefetch.end);

	return 0;
}

static int tegra_pcie_parse_port_info(const void *fdt, int node,
				      unsigned int *index,
				      unsigned int *lanes)
{
	struct fdt_pci_addr addr;
	int err;

	err = fdtdec_get_int(fdt, node, "nvidia,num-lanes", 0);
	if (err < 0) {
		error("failed to parse \"nvidia,num-lanes\" property");
		return err;
	}

	*lanes = err;

	err = fdtdec_get_pci_addr(fdt, node, 0, "reg", &addr);
	if (err < 0) {
		error("failed to parse \"reg\" property");
		return err;
	}

	*index = PCI_DEV(addr.phys_hi) - 1;

	return 0;
}

static int tegra_pcie_parse_dt(const void *fdt, int node,
			       struct tegra_pcie *pcie)
{
	int err, subnode;
	u32 lanes = 0;

	err = fdt_get_named_resource(fdt, node, "reg", "reg-names", "pads",
				     &pcie->pads);
	if (err < 0) {
		error("resource \"pads\" not found");
		return err;
	}

	err = fdt_get_named_resource(fdt, node, "reg", "reg-names", "afi",
				     &pcie->afi);
	if (err < 0) {
		error("resource \"afi\" not found");
		return err;
	}

	err = fdt_get_named_resource(fdt, node, "reg", "reg-names", "cs",
				     &pcie->cs);
	if (err < 0) {
		error("resource \"cs\" not found");
		return err;
	}

	pcie->phy = tegra_xusb_phy_get(TEGRA_XUSB_PADCTL_PCIE);
	if (pcie->phy) {
		err = tegra_xusb_phy_prepare(pcie->phy);
		if (err < 0) {
			error("failed to prepare PHY: %d", err);
			return err;
		}
	}

	err = tegra_pcie_parse_dt_ranges(fdt, node, pcie);
	if (err < 0) {
		error("failed to parse \"ranges\" property");
		return err;
	}

	fdt_for_each_subnode(fdt, subnode, node) {
		unsigned int index = 0, num_lanes = 0;
		struct tegra_pcie_port *port;

		err = tegra_pcie_parse_port_info(fdt, subnode, &index,
						 &num_lanes);
		if (err < 0) {
			error("failed to obtain root port info");
			continue;
		}

		lanes |= num_lanes << (index << 3);

		if (!fdtdec_get_is_enabled(fdt, subnode))
			continue;

		port = malloc(sizeof(*port));
		if (!port)
			continue;

		memset(port, 0, sizeof(*port));
		port->num_lanes = num_lanes;
		port->index = index;

		err = tegra_pcie_port_parse_dt(fdt, subnode, port);
		if (err < 0) {
			free(port);
			continue;
		}

		list_add_tail(&port->list, &pcie->ports);
		port->pcie = pcie;
	}

	err = tegra_pcie_get_xbar_config(fdt, node, lanes, &pcie->xbar);
	if (err < 0) {
		error("invalid lane configuration");
		return err;
	}

	return 0;
}

int __weak tegra_pcie_board_init(void)
{
	return 0;
}

static int tegra_pcie_power_on(struct tegra_pcie *pcie)
{
	const struct tegra_pcie_soc *soc = pcie->soc;
	unsigned long value;
	int err;

	/* reset PCIEXCLK logic, AFI controller and PCIe controller */
	reset_set_enable(PERIPH_ID_PCIEXCLK, 1);
	reset_set_enable(PERIPH_ID_AFI, 1);
	reset_set_enable(PERIPH_ID_PCIE, 1);

	err = tegra_powergate_power_off(TEGRA_POWERGATE_PCIE);
	if (err < 0) {
		error("failed to power off PCIe partition: %d", err);
		return err;
	}

	tegra_pcie_board_init();

	err = tegra_powergate_sequence_power_up(TEGRA_POWERGATE_PCIE,
						PERIPH_ID_PCIE);
	if (err < 0) {
		error("failed to power up PCIe partition: %d", err);
		return err;
	}

	/* take AFI controller out of reset */
	reset_set_enable(PERIPH_ID_AFI, 0);

	/* enable AFI clock */
	clock_enable(PERIPH_ID_AFI);

	if (soc->has_cml_clk) {
		/* enable CML clock */
		value = readl(NV_PA_CLK_RST_BASE + 0x48c);
		value |= (1 << 0);
		value &= ~(1 << 1);
		writel(value, NV_PA_CLK_RST_BASE + 0x48c);
	}

	err = tegra_plle_enable();
	if (err < 0) {
		error("failed to enable PLLE: %d\n", err);
		return err;
	}

	return 0;
}

static int tegra_pcie_pll_wait(struct tegra_pcie *pcie, unsigned long timeout)
{
	const struct tegra_pcie_soc *soc = pcie->soc;
	unsigned long start = get_timer(0);
	u32 value;

	while (get_timer(start) < timeout) {
		value = pads_readl(pcie, soc->pads_pll_ctl);
		if (value & PADS_PLL_CTL_LOCKDET)
			return 0;
	}

	return -ETIMEDOUT;
}

static int tegra_pcie_phy_enable(struct tegra_pcie *pcie)
{
	const struct tegra_pcie_soc *soc = pcie->soc;
	u32 value;
	int err;

	/* initialize internal PHY, enable up to 16 PCIe lanes */
	pads_writel(pcie, 0, PADS_CTL_SEL);

	/* override IDDQ to 1 on all 4 lanes */
	value = pads_readl(pcie, PADS_CTL);
	value |= PADS_CTL_IDDQ_1L;
	pads_writel(pcie, value, PADS_CTL);

	/*
	 * Set up PHY PLL inputs select PLLE output as refclock, set TX
	 * ref sel to div10 (not div5).
	 */
	value = pads_readl(pcie, soc->pads_pll_ctl);
	value &= ~(PADS_PLL_CTL_REFCLK_MASK | PADS_PLL_CTL_TXCLKREF_MASK);
	value |= PADS_PLL_CTL_REFCLK_INTERNAL_CML | soc->tx_ref_sel;
	pads_writel(pcie, value, soc->pads_pll_ctl);

	/* reset PLL */
	value = pads_readl(pcie, soc->pads_pll_ctl);
	value &= ~PADS_PLL_CTL_RST_B4SM;
	pads_writel(pcie, value, soc->pads_pll_ctl);

	udelay(20);

	/* take PLL out of reset */
	value = pads_readl(pcie, soc->pads_pll_ctl);
	value |= PADS_PLL_CTL_RST_B4SM;
	pads_writel(pcie, value, soc->pads_pll_ctl);

	/* configure the reference clock driver */
	value = PADS_REFCLK_CFG_VALUE | (PADS_REFCLK_CFG_VALUE << 16);
	pads_writel(pcie, value, PADS_REFCLK_CFG0);

	if (soc->num_ports > 2)
		pads_writel(pcie, PADS_REFCLK_CFG_VALUE, PADS_REFCLK_CFG1);

	/* wait for the PLL to lock */
	err = tegra_pcie_pll_wait(pcie, 500);
	if (err < 0) {
		error("PLL failed to lock: %d", err);
		return err;
	}

	/* turn off IDDQ override */
	value = pads_readl(pcie, PADS_CTL);
	value &= ~PADS_CTL_IDDQ_1L;
	pads_writel(pcie, value, PADS_CTL);

	/* enable TX/RX data */
	value = pads_readl(pcie, PADS_CTL);
	value |= PADS_CTL_TX_DATA_EN_1L | PADS_CTL_RX_DATA_EN_1L;
	pads_writel(pcie, value, PADS_CTL);

	return 0;
}

static int tegra_pcie_enable_controller(struct tegra_pcie *pcie)
{
	const struct tegra_pcie_soc *soc = pcie->soc;
	struct tegra_pcie_port *port;
	u32 value;
	int err;

	if (pcie->phy) {
		value = afi_readl(pcie, AFI_PLLE_CONTROL);
		value &= ~AFI_PLLE_CONTROL_BYPASS_PADS2PLLE_CONTROL;
		value |= AFI_PLLE_CONTROL_PADS2PLLE_CONTROL_EN;
		afi_writel(pcie, value, AFI_PLLE_CONTROL);
	}

	if (soc->has_pex_bias_ctrl)
		afi_writel(pcie, 0, AFI_PEXBIAS_CTRL_0);

	value = afi_readl(pcie, AFI_PCIE_CONFIG);
	value &= ~AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_MASK;
	value |= AFI_PCIE_CONFIG_PCIE_DISABLE_ALL | pcie->xbar;

	list_for_each_entry(port, &pcie->ports, list)
		value &= ~AFI_PCIE_CONFIG_PCIE_DISABLE(port->index);

	afi_writel(pcie, value, AFI_PCIE_CONFIG);

	value = afi_readl(pcie, AFI_FUSE);

	if (soc->has_gen2)
		value &= ~AFI_FUSE_PCIE_T0_GEN2_DIS;
	else
		value |= AFI_FUSE_PCIE_T0_GEN2_DIS;

	afi_writel(pcie, value, AFI_FUSE);

	if (pcie->phy)
		err = tegra_xusb_phy_enable(pcie->phy);
	else
		err = tegra_pcie_phy_enable(pcie);

	if (err < 0) {
		error("failed to power on PHY: %d\n", err);
		return err;
	}

	/* take the PCIEXCLK logic out of reset */
	reset_set_enable(PERIPH_ID_PCIEXCLK, 0);

	/* finally enable PCIe */
	value = afi_readl(pcie, AFI_CONFIGURATION);
	value |= AFI_CONFIGURATION_EN_FPCI;
	afi_writel(pcie, value, AFI_CONFIGURATION);

	/* disable all interrupts */
	afi_writel(pcie, 0, AFI_AFI_INTR_ENABLE);
	afi_writel(pcie, 0, AFI_SM_INTR_ENABLE);
	afi_writel(pcie, 0, AFI_INTR_MASK);
	afi_writel(pcie, 0, AFI_FPCI_ERROR_MASKS);

	return 0;
}

static void tegra_pcie_setup_translations(struct tegra_pcie *pcie)
{
	unsigned long fpci, axi, size;

	/* BAR 0: type 1 extended configuration space */
	fpci = 0xfe100000;
	size = fdt_resource_size(&pcie->cs);
	axi = pcie->cs.start;

	afi_writel(pcie, axi, AFI_AXI_BAR0_START);
	afi_writel(pcie, size >> 12, AFI_AXI_BAR0_SZ);
	afi_writel(pcie, fpci, AFI_FPCI_BAR0);

	/* BAR 1: downstream I/O */
	fpci = 0xfdfc0000;
	size = fdt_resource_size(&pcie->io);
	axi = pcie->io.start;

	afi_writel(pcie, axi, AFI_AXI_BAR1_START);
	afi_writel(pcie, size >> 12, AFI_AXI_BAR1_SZ);
	afi_writel(pcie, fpci, AFI_FPCI_BAR1);

	/* BAR 2: prefetchable memory */
	fpci = (((pcie->prefetch.start >> 12) & 0x0fffffff) << 4) | 0x1;
	size = fdt_resource_size(&pcie->prefetch);
	axi = pcie->prefetch.start;

	afi_writel(pcie, axi, AFI_AXI_BAR2_START);
	afi_writel(pcie, size >> 12, AFI_AXI_BAR2_SZ);
	afi_writel(pcie, fpci, AFI_FPCI_BAR2);

	/* BAR 3: non-prefetchable memory */
	fpci = (((pcie->mem.start >> 12) & 0x0fffffff) << 4) | 0x1;
	size = fdt_resource_size(&pcie->mem);
	axi = pcie->mem.start;

	afi_writel(pcie, axi, AFI_AXI_BAR3_START);
	afi_writel(pcie, size >> 12, AFI_AXI_BAR3_SZ);
	afi_writel(pcie, fpci, AFI_FPCI_BAR3);

	/* NULL out the remaining BARs as they are not used */
	afi_writel(pcie, 0, AFI_AXI_BAR4_START);
	afi_writel(pcie, 0, AFI_AXI_BAR4_SZ);
	afi_writel(pcie, 0, AFI_FPCI_BAR4);

	afi_writel(pcie, 0, AFI_AXI_BAR5_START);
	afi_writel(pcie, 0, AFI_AXI_BAR5_SZ);
	afi_writel(pcie, 0, AFI_FPCI_BAR5);

	/* map all upstream transactions as uncached */
	afi_writel(pcie, NV_PA_SDRAM_BASE, AFI_CACHE_BAR0_ST);
	afi_writel(pcie, 0, AFI_CACHE_BAR0_SZ);
	afi_writel(pcie, 0, AFI_CACHE_BAR1_ST);
	afi_writel(pcie, 0, AFI_CACHE_BAR1_SZ);

	/* MSI translations are setup only when needed */
	afi_writel(pcie, 0, AFI_MSI_FPCI_BAR_ST);
	afi_writel(pcie, 0, AFI_MSI_BAR_SZ);
	afi_writel(pcie, 0, AFI_MSI_AXI_BAR_ST);
	afi_writel(pcie, 0, AFI_MSI_BAR_SZ);
}

static unsigned long tegra_pcie_port_get_pex_ctrl(struct tegra_pcie_port *port)
{
	unsigned long ret = 0;

	switch (port->index) {
	case 0:
		ret = AFI_PEX0_CTRL;
		break;

	case 1:
		ret = AFI_PEX1_CTRL;
		break;

	case 2:
		ret = AFI_PEX2_CTRL;
		break;
	}

	return ret;
}

static void tegra_pcie_port_reset(struct tegra_pcie_port *port)
{
	unsigned long ctrl = tegra_pcie_port_get_pex_ctrl(port);
	unsigned long value;

	/* pulse reset signel */
	value = afi_readl(port->pcie, ctrl);
	value &= ~AFI_PEX_CTRL_RST;
	afi_writel(port->pcie, value, ctrl);

	udelay(2000);

	value = afi_readl(port->pcie, ctrl);
	value |= AFI_PEX_CTRL_RST;
	afi_writel(port->pcie, value, ctrl);
}

static void tegra_pcie_port_enable(struct tegra_pcie_port *port)
{
	unsigned long ctrl = tegra_pcie_port_get_pex_ctrl(port);
	unsigned long value;

	/* enable reference clock */
	value = afi_readl(port->pcie, ctrl);
	value |= AFI_PEX_CTRL_REFCLK_EN;

	if (port->pcie->soc->has_pex_clkreq_en)
		value |= AFI_PEX_CTRL_CLKREQ_EN;

	value |= AFI_PEX_CTRL_OVERRIDE_EN;

	afi_writel(port->pcie, value, ctrl);

	tegra_pcie_port_reset(port);
}

static bool tegra_pcie_port_check_link(struct tegra_pcie_port *port)
{
	unsigned int retries = 3;
	unsigned long value;

	value = rp_readl(port, RP_PRIV_MISC);
	value &= ~RP_PRIV_MISC_PRSNT_MAP_EP_ABSNT;
	value |= RP_PRIV_MISC_PRSNT_MAP_EP_PRSNT;
	rp_writel(port, value, RP_PRIV_MISC);

	do {
		unsigned int timeout = 200;

		do {
			value = rp_readl(port, RP_VEND_XP);
			if (value & RP_VEND_XP_DL_UP)
				break;

			udelay(2000);
		} while (--timeout);

		if (!timeout) {
			debug("link %u down, retrying\n", port->index);
			goto retry;
		}

		timeout = 200;

		do {
			value = rp_readl(port, RP_LINK_CONTROL_STATUS);
			if (value & RP_LINK_CONTROL_STATUS_DL_LINK_ACTIVE)
				return true;

			udelay(2000);
		} while (--timeout);

retry:
		tegra_pcie_port_reset(port);
	} while (--retries);

	return false;
}

static void tegra_pcie_port_disable(struct tegra_pcie_port *port)
{
	unsigned long ctrl = tegra_pcie_port_get_pex_ctrl(port);
	unsigned long value;

	/* assert port reset */
	value = afi_readl(port->pcie, ctrl);
	value &= ~AFI_PEX_CTRL_RST;
	afi_writel(port->pcie, value, ctrl);

	/* disable reference clock */
	value = afi_readl(port->pcie, ctrl);
	value &= ~AFI_PEX_CTRL_REFCLK_EN;
	afi_writel(port->pcie, value, ctrl);
}

static void tegra_pcie_port_free(struct tegra_pcie_port *port)
{
	list_del(&port->list);
	free(port);
}

static int tegra_pcie_enable(struct tegra_pcie *pcie)
{
	struct tegra_pcie_port *port, *tmp;

	list_for_each_entry_safe(port, tmp, &pcie->ports, list) {
		debug("probing port %u, using %u lanes\n", port->index,
		      port->num_lanes);

		tegra_pcie_port_enable(port);

		if (tegra_pcie_port_check_link(port))
			continue;

		debug("link %u down, ignoring\n", port->index);

		tegra_pcie_port_disable(port);
		tegra_pcie_port_free(port);
	}

	return 0;
}

static const struct tegra_pcie_soc tegra20_pcie_soc = {
	.num_ports = 2,
	.pads_pll_ctl = PADS_PLL_CTL_TEGRA20,
	.tx_ref_sel = PADS_PLL_CTL_TXCLKREF_DIV10,
	.has_pex_clkreq_en = false,
	.has_pex_bias_ctrl = false,
	.has_cml_clk = false,
	.has_gen2 = false,
};

static const struct tegra_pcie_soc tegra30_pcie_soc = {
	.num_ports = 3,
	.pads_pll_ctl = PADS_PLL_CTL_TEGRA30,
	.tx_ref_sel = PADS_PLL_CTL_TXCLKREF_BUF_EN,
	.has_pex_clkreq_en = true,
	.has_pex_bias_ctrl = true,
	.has_cml_clk = true,
	.has_gen2 = false,
};

static const struct tegra_pcie_soc tegra124_pcie_soc = {
	.num_ports = 2,
	.pads_pll_ctl = PADS_PLL_CTL_TEGRA30,
	.tx_ref_sel = PADS_PLL_CTL_TXCLKREF_BUF_EN,
	.has_pex_clkreq_en = true,
	.has_pex_bias_ctrl = true,
	.has_cml_clk = true,
	.has_gen2 = true,
};

static int process_nodes(const void *fdt, int nodes[], unsigned int count)
{
	unsigned int i;

	for (i = 0; i < count; i++) {
		const struct tegra_pcie_soc *soc;
		struct tegra_pcie *pcie;
		enum fdt_compat_id id;
		int err;

		if (!fdtdec_get_is_enabled(fdt, nodes[i]))
			continue;

		id = fdtdec_lookup(fdt, nodes[i]);
		switch (id) {
		case COMPAT_NVIDIA_TEGRA20_PCIE:
			soc = &tegra20_pcie_soc;
			break;

		case COMPAT_NVIDIA_TEGRA30_PCIE:
			soc = &tegra30_pcie_soc;
			break;

		case COMPAT_NVIDIA_TEGRA124_PCIE:
			soc = &tegra124_pcie_soc;
			break;

		default:
			error("unsupported compatible: %s",
			      fdtdec_get_compatible(id));
			continue;
		}

		pcie = malloc(sizeof(*pcie));
		if (!pcie) {
			error("failed to allocate controller");
			continue;
		}

		memset(pcie, 0, sizeof(*pcie));
		pcie->soc = soc;

		INIT_LIST_HEAD(&pcie->ports);

		err = tegra_pcie_parse_dt(fdt, nodes[i], pcie);
		if (err < 0) {
			free(pcie);
			continue;
		}

		err = tegra_pcie_power_on(pcie);
		if (err < 0) {
			error("failed to power on");
			continue;
		}

		err = tegra_pcie_enable_controller(pcie);
		if (err < 0) {
			error("failed to enable controller");
			continue;
		}

		tegra_pcie_setup_translations(pcie);

		err = tegra_pcie_enable(pcie);
		if (err < 0) {
			error("failed to enable PCIe");
			continue;
		}

		pcie->hose.first_busno = 0;
		pcie->hose.current_busno = 0;
		pcie->hose.last_busno = 0;

		pci_set_region(&pcie->hose.regions[0], NV_PA_SDRAM_BASE,
			       NV_PA_SDRAM_BASE, gd->ram_size,
			       PCI_REGION_MEM | PCI_REGION_SYS_MEMORY);

		pci_set_region(&pcie->hose.regions[1], pcie->io.start,
			       pcie->io.start, fdt_resource_size(&pcie->io),
			       PCI_REGION_IO);

		pci_set_region(&pcie->hose.regions[2], pcie->mem.start,
			       pcie->mem.start, fdt_resource_size(&pcie->mem),
			       PCI_REGION_MEM);

		pci_set_region(&pcie->hose.regions[3], pcie->prefetch.start,
			       pcie->prefetch.start,
			       fdt_resource_size(&pcie->prefetch),
			       PCI_REGION_MEM | PCI_REGION_PREFETCH);

		pcie->hose.region_count = 4;

		pci_set_ops(&pcie->hose,
			    pci_hose_read_config_byte_via_dword,
			    pci_hose_read_config_word_via_dword,
			    tegra_pcie_read_conf,
			    pci_hose_write_config_byte_via_dword,
			    pci_hose_write_config_word_via_dword,
			    tegra_pcie_write_conf);

		pci_register_hose(&pcie->hose);

#ifdef CONFIG_PCI_SCAN_SHOW
		printf("PCI: Enumerating devices...\n");
		printf("---------------------------------------\n");
		printf("  Device        ID          Description\n");
		printf("  ------        --          -----------\n");
#endif

		pcie->hose.last_busno = pci_hose_scan(&pcie->hose);
	}

	return 0;
}

void pci_init_board(void)
{
	const void *fdt = gd->fdt_blob;
	int count, nodes[1];

	count = fdtdec_find_aliases_for_id(fdt, "pcie-controller",
					   COMPAT_NVIDIA_TEGRA124_PCIE,
					   nodes, ARRAY_SIZE(nodes));
	if (process_nodes(fdt, nodes, count))
		return;

	count = fdtdec_find_aliases_for_id(fdt, "pcie-controller",
					   COMPAT_NVIDIA_TEGRA30_PCIE,
					   nodes, ARRAY_SIZE(nodes));
	if (process_nodes(fdt, nodes, count))
		return;

	count = fdtdec_find_aliases_for_id(fdt, "pcie-controller",
					   COMPAT_NVIDIA_TEGRA20_PCIE,
					   nodes, ARRAY_SIZE(nodes));
	if (process_nodes(fdt, nodes, count))
		return;
}

int pci_skip_dev(struct pci_controller *hose, pci_dev_t dev)
{
	if (PCI_BUS(dev) != 0 && PCI_DEV(dev) > 0)
		return 1;

	return 0;
}

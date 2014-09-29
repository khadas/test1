/*
 * emac definitions for keystone2 devices
 *
 * (C) Copyright 2012-2014
 *     Texas Instruments Incorporated, <www.ti.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _EMAC_DEFS_H_
#define _EMAC_DEFS_H_

#include <asm/arch/hardware.h>
#include <asm/io.h>

/* EMAC */
#ifdef KS2_NETCP_V1_0

#define EMAC_EMACSL_BASE_ADDR           (KS2_PASS_BASE + 0x00090900)
#define EMAC_MDIO_BASE_ADDR             (KS2_PASS_BASE + 0x00090300)
#define EMAC_SGMII_BASE_ADDR            (KS2_PASS_BASE + 0x00090100)
#define DEVICE_EMACSL_BASE(x)		(EMAC_EMACSL_BASE_ADDR + (x)*0x040)

/* Register offsets */
#define CPGMACSL_REG_CTL		0x04
#define CPGMACSL_REG_STATUS		0x08
#define CPGMACSL_REG_RESET		0x0c
#define CPGMACSL_REG_MAXLEN		0x10

#elif defined KS2_NETCP_V1_5

#define CPGMACSL_REG_RX_PRI_MAP		0x020
#define EMAC_EMACSL_BASE_ADDR           (KS2_PASS_BASE + 0x00222000)
#define EMAC_MDIO_BASE_ADDR             (KS2_PASS_BASE + 0x00200f00)
#define EMAC_SGMII_BASE_ADDR            (KS2_PASS_BASE + 0x00200100)
#define DEVICE_EMACSL_BASE(x)		(EMAC_EMACSL_BASE_ADDR + (x) * 0x1000)

/* Register offsets */
#define CPGMACSL_REG_CTL		0x330
#define CPGMACSL_REG_STATUS		0x334
#define CPGMACSL_REG_RESET		0x338
#define CPGMACSL_REG_MAXLEN		0x024

#endif

#define KEYSTONE2_EMAC_GIG_ENABLE

#define MAC_ID_BASE_ADDR                (KS2_DEVICE_STATE_CTRL_BASE + 0x110)

/* MDIO module input frequency */
#define EMAC_MDIO_BUS_FREQ              (clk_get_rate(pass_pll_clk))
/* MDIO clock output frequency */
#define EMAC_MDIO_CLOCK_FREQ            1000000		/* 1.0 MHz */

/* MII Status Register */
#define MII_STATUS_REG                  1
#define MII_STATUS_LINK_MASK            (0x4)

/* Marvell 88E1111 PHY ID */
#define PHY_MARVELL_88E1111             (0x01410cc0)

#define MDIO_CONTROL_IDLE               (0x80000000)
#define MDIO_CONTROL_ENABLE             (0x40000000)
#define MDIO_CONTROL_FAULT_ENABLE       (0x40000)
#define MDIO_CONTROL_FAULT              (0x80000)
#define MDIO_USERACCESS0_GO             (0x80000000)
#define MDIO_USERACCESS0_WRITE_READ     (0x0)
#define MDIO_USERACCESS0_WRITE_WRITE    (0x40000000)
#define MDIO_USERACCESS0_ACK            (0x20000000)

#define EMAC_MACCONTROL_MIIEN_ENABLE       (0x20)
#define EMAC_MACCONTROL_FULLDUPLEX_ENABLE  (0x1)
#define EMAC_MACCONTROL_GIGABIT_ENABLE     (1 << 7)
#define EMAC_MACCONTROL_GIGFORCE           (1 << 17)
#define EMAC_MACCONTROL_RMIISPEED_100      (1 << 15)

#define EMAC_MIN_ETHERNET_PKT_SIZE         60

struct mac_sl_cfg {
	u_int32_t max_rx_len;	/* Maximum receive packet length. */
	u_int32_t ctl;		/* Control bitfield */
};

/*
 * Definition: Control bitfields used in the ctl field of hwGmacSlCfg_t
 */
#define GMACSL_RX_ENABLE_RCV_CONTROL_FRAMES       (1 << 24)
#define GMACSL_RX_ENABLE_RCV_SHORT_FRAMES         (1 << 23)
#define GMACSL_RX_ENABLE_RCV_ERROR_FRAMES         (1 << 22)
#define GMACSL_RX_ENABLE_EXT_CTL                  (1 << 18)
#define GMACSL_RX_ENABLE_GIG_FORCE                (1 << 17)
#define GMACSL_RX_ENABLE_IFCTL_B                  (1 << 16)
#define GMACSL_RX_ENABLE_IFCTL_A                  (1 << 15)
#define GMACSL_RX_ENABLE_CMD_IDLE                 (1 << 11)
#define GMACSL_TX_ENABLE_SHORT_GAP                (1 << 10)
#define GMACSL_ENABLE_GIG_MODE                    (1 <<  7)
#define GMACSL_TX_ENABLE_PACE                     (1 <<  6)
#define GMACSL_ENABLE                             (1 <<  5)
#define GMACSL_TX_ENABLE_FLOW_CTL                 (1 <<  4)
#define GMACSL_RX_ENABLE_FLOW_CTL                 (1 <<  3)
#define GMACSL_ENABLE_LOOPBACK                    (1 <<  1)
#define GMACSL_ENABLE_FULL_DUPLEX                 (1 <<  0)

/*
 * DEFINTITION: function return values
 */
#define GMACSL_RET_OK                        0
#define GMACSL_RET_INVALID_PORT             -1
#define GMACSL_RET_WARN_RESET_INCOMPLETE    -2
#define GMACSL_RET_WARN_MAXLEN_TOO_BIG      -3
#define GMACSL_RET_CONFIG_FAIL_RESET_ACTIVE -4

/* EMAC SL register definitions */
#define DEVICE_EMACSL_RESET_POLL_COUNT		  100

/* Soft reset register values */
#define CPGMAC_REG_RESET_VAL_RESET_MASK      (1 << 0)
#define CPGMAC_REG_RESET_VAL_RESET           (1 << 0)

/* Maxlen register values */
#define CPGMAC_REG_MAXLEN_LEN                0x3fff

/* CPSW */
/* Control bitfields */
#define CPSW_CTL_P2_PASS_PRI_TAGGED     (1 << 5)
#define CPSW_CTL_P1_PASS_PRI_TAGGED     (1 << 4)
#define CPSW_CTL_P0_PASS_PRI_TAGGED     (1 << 3)
#define CPSW_CTL_P0_ENABLE              (1 << 2)
#define CPSW_CTL_VLAN_AWARE             (1 << 1)
#define CPSW_CTL_FIFO_LOOPBACK          (1 << 0)

#define DEVICE_CPSW_NUM_PORTS		CONFIG_KSNET_CPSW_NUM_PORTS
#define DEVICE_N_GMACSL_PORTS		(DEVICE_CPSW_NUM_PORTS - 1)

#ifdef KS2_NETCP_V1_0

#define DEVICE_CPSW_BASE		(KS2_PASS_BASE + 0x00090800)
#define CPSW_REG_CTL			0x004
#define CPSW_REG_STAT_PORT_EN		0x00c
#define CPSW_REG_MAXLEN			0x040
#define CPSW_REG_ALE_CONTROL		0x608
#define CPSW_REG_ALE_PORTCTL(x)		(0x640 + (x)*4)
#define CPSW_REG_VAL_STAT_ENABLE_ALL     0xf

#elif defined KS2_NETCP_V1_5

#define DEVICE_CPSW_BASE		 (KS2_PASS_BASE + 0x00220000)
#define CPSW_REG_CTL		         0x00004
#define CPSW_REG_STAT_PORT_EN	         0x00014
#define CPSW_REG_MAXLEN		         0x01024
#define CPSW_REG_ALE_CONTROL	         0x1e008
#define CPSW_REG_ALE_PORTCTL(x)		 (0x1e040 + (x) * 4)
#define CPSW_REG_VAL_STAT_ENABLE_ALL     0x1ff

#endif

#define CPSW_REG_VAL_ALE_CTL_RESET_AND_ENABLE    ((u_int32_t)0xc0000000)
#define CPSW_REG_VAL_ALE_CTL_BYPASS              ((u_int32_t)0x00000010)
#define CPSW_REG_VAL_PORTCTL_FORWARD_MODE        0x3

#define target_get_switch_ctl()     CPSW_CTL_P0_ENABLE   /* Enable port 0 */
#define SWITCH_MAX_PKT_SIZE         9000

/* SGMII */
#define SGMII_REG_STATUS_LOCK           BIT(4)
#define SGMII_REG_STATUS_LINK           BIT(0)
#define SGMII_REG_STATUS_AUTONEG        BIT(2)
#define SGMII_REG_CONTROL_AUTONEG       BIT(0)
#define SGMII_REG_CONTROL_MASTER        BIT(5)
#define	SGMII_REG_MR_ADV_ENABLE         BIT(0)
#define	SGMII_REG_MR_ADV_LINK           BIT(15)
#define	SGMII_REG_MR_ADV_FULL_DUPLEX    BIT(12)
#define SGMII_REG_MR_ADV_GIG_MODE       BIT(11)

#define SGMII_LINK_MAC_MAC_AUTONEG      0
#define SGMII_LINK_MAC_PHY              1
#define SGMII_LINK_MAC_MAC_FORCED       2
#define SGMII_LINK_MAC_FIBER            3
#define SGMII_LINK_MAC_PHY_FORCED       4

#ifdef KS2_NETCP_V1_0
#define SGMII_OFFSET(x)	((x <= 1) ? (x * 0x100) : ((x * 0x100) + 0x100))
#elif defined KS2_NETCP_V1_5
#define SGMII_OFFSET(x)			((x) * 0x100)
#endif

#define SGMII_IDVER_REG(x)    (EMAC_SGMII_BASE_ADDR + SGMII_OFFSET(x) + 0x000)
#define SGMII_SRESET_REG(x)   (EMAC_SGMII_BASE_ADDR + SGMII_OFFSET(x) + 0x004)
#define SGMII_CTL_REG(x)      (EMAC_SGMII_BASE_ADDR + SGMII_OFFSET(x) + 0x010)
#define SGMII_STATUS_REG(x)   (EMAC_SGMII_BASE_ADDR + SGMII_OFFSET(x) + 0x014)
#define SGMII_MRADV_REG(x)    (EMAC_SGMII_BASE_ADDR + SGMII_OFFSET(x) + 0x018)
#define SGMII_LPADV_REG(x)    (EMAC_SGMII_BASE_ADDR + SGMII_OFFSET(x) + 0x020)
#define SGMII_TXCFG_REG(x)    (EMAC_SGMII_BASE_ADDR + SGMII_OFFSET(x) + 0x030)
#define SGMII_RXCFG_REG(x)    (EMAC_SGMII_BASE_ADDR + SGMII_OFFSET(x) + 0x034)
#define SGMII_AUXCFG_REG(x)   (EMAC_SGMII_BASE_ADDR + SGMII_OFFSET(x) + 0x038)

/* PSS */
#ifdef KS2_NETCP_V1_0

#define DEVICE_PSTREAM_CFG_REG_ADDR		(KS2_PASS_BASE + 0x604)
#define DEVICE_PSTREAM_CFG_VAL_ROUTE_CPPI	0x06060606
#define hw_config_streaming_switch()\
	writel(DEVICE_PSTREAM_CFG_VAL_ROUTE_CPPI, DEVICE_PSTREAM_CFG_REG_ADDR);

#elif defined KS2_NETCP_V1_5

#define DEVICE_PSTREAM_CFG_REG_ADDR		(KS2_PASS_BASE + 0x500)
#define DEVICE_PSTREAM_CFG_VAL_ROUTE_CPPI	0x0

#define hw_config_streaming_switch()\
	writel(DEVICE_PSTREAM_CFG_VAL_ROUTE_CPPI,\
	       DEVICE_PSTREAM_CFG_REG_ADDR);\
	writel(DEVICE_PSTREAM_CFG_VAL_ROUTE_CPPI,\
	       DEVICE_PSTREAM_CFG_REG_ADDR+4);\
	writel(DEVICE_PSTREAM_CFG_VAL_ROUTE_CPPI,\
	       DEVICE_PSTREAM_CFG_REG_ADDR+8);\
	writel(DEVICE_PSTREAM_CFG_VAL_ROUTE_CPPI,\
	       DEVICE_PSTREAM_CFG_REG_ADDR+12);

#endif

/* EMAC MDIO Registers Structure */
struct mdio_regs {
	dv_reg		version;
	dv_reg		control;
	dv_reg		alive;
	dv_reg		link;
	dv_reg		linkintraw;
	dv_reg		linkintmasked;
	u_int8_t	rsvd0[8];
	dv_reg		userintraw;
	dv_reg		userintmasked;
	dv_reg		userintmaskset;
	dv_reg		userintmaskclear;
	u_int8_t	rsvd1[80];
	dv_reg		useraccess0;
	dv_reg		userphysel0;
	dv_reg		useraccess1;
	dv_reg		userphysel1;
};

struct eth_priv_t {
	char	int_name[32];
	int	rx_flow;
	int	phy_addr;
	int	slave_port;
	int	sgmii_link_type;
};

int keystone2_emac_initialize(struct eth_priv_t *eth_priv);
void sgmii_serdes_setup_156p25mhz(void);
void sgmii_serdes_shutdown(void);

#endif  /* _EMAC_DEFS_H_ */

/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <commproc.h>
#include <malloc.h>
#include <net.h>

#include <phy.h>

DECLARE_GLOBAL_DATA_PTR;

#if defined(CONFIG_CMD_NET) && \
	(defined(FEC_ENET) || defined(CONFIG_ETHER_ON_FEC1) || defined(CONFIG_ETHER_ON_FEC2))

/* compatibility test, if only FEC_ENET defined assume ETHER on FEC1 */
#if defined(FEC_ENET) && !defined(CONFIG_ETHER_ON_FEC1) && !defined(CONFIG_ETHER_ON_FEC2)
#define CONFIG_ETHER_ON_FEC1 1
#endif

/* define WANT_MII when MII support is required */
#if defined(CONFIG_SYS_DISCOVER_PHY) || defined(CONFIG_FEC1_PHY) || defined(CONFIG_FEC2_PHY)
#define WANT_MII
#else
#undef WANT_MII
#endif

#if defined(WANT_MII)
#include <miiphy.h>

#if !(defined(CONFIG_MII) || defined(CONFIG_CMD_MII))
#error "CONFIG_MII has to be defined!"
#endif

#endif

#if defined(CONFIG_RMII) && !defined(WANT_MII)
#error RMII support is unusable without a working PHY.
#endif

#ifdef CONFIG_SYS_DISCOVER_PHY
static int mii_discover_phy(struct eth_device *dev);
#endif

int fec8xx_miiphy_read(struct mii_dev *bus, int addr, int devad, int reg);
int fec8xx_miiphy_write(struct mii_dev *bus, int addr, int devad, int reg,
			u16 value);

static struct ether_fcc_info_s
{
	int ether_index;
	int fecp_offset;
	int phy_addr;
	int actual_phy_addr;
	int initialized;
}
	ether_fcc_info[] = {
#if defined(CONFIG_ETHER_ON_FEC1)
	{
		0,
		offsetof(immap_t, im_cpm.cp_fec1),
#if defined(CONFIG_FEC1_PHY)
		CONFIG_FEC1_PHY,
#else
		-1,	/* discover */
#endif
		-1,
		0,

	},
#endif
#if defined(CONFIG_ETHER_ON_FEC2)
	{
		1,
		offsetof(immap_t, im_cpm.cp_fec2),
#if defined(CONFIG_FEC2_PHY)
		CONFIG_FEC2_PHY,
#else
		-1,
#endif
		-1,
		0,
	},
#endif
};

/* Ethernet Transmit and Receive Buffers */
#define DBUF_LENGTH  1520

#define TX_BUF_CNT 2

#define TOUT_LOOP 100

#define PKT_MAXBUF_SIZE		1518
#define PKT_MINBUF_SIZE		64
#define PKT_MAXBLR_SIZE		1520

#ifdef __GNUC__
static char txbuf[DBUF_LENGTH] __attribute__ ((aligned(8)));
#else
#error txbuf must be aligned.
#endif

static uint rxIdx;	/* index of the current RX buffer */
static uint txIdx;	/* index of the current TX buffer */

/*
  * FEC Ethernet Tx and Rx buffer descriptors allocated at the
  *  immr->udata_bd address on Dual-Port RAM
  * Provide for Double Buffering
  */

typedef volatile struct CommonBufferDescriptor {
    cbd_t rxbd[PKTBUFSRX];		/* Rx BD */
    cbd_t txbd[TX_BUF_CNT];		/* Tx BD */
} RTXBD;

static RTXBD *rtx = NULL;

static int fec_send(struct eth_device *dev, void *packet, int length);
static int fec_recv(struct eth_device* dev);
static int fec_init(struct eth_device* dev, bd_t * bd);
static void fec_halt(struct eth_device* dev);
#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
static void __mii_init(void);
#endif

int fec_initialize(bd_t *bis)
{
	struct eth_device* dev;
	struct ether_fcc_info_s *efis;
	int             i;

	for (i = 0; i < ARRAY_SIZE(ether_fcc_info); i++) {

		dev = malloc(sizeof(*dev));
		if (dev == NULL)
			hang();

		memset(dev, 0, sizeof(*dev));

		/* for FEC1 make sure that the name of the interface is the same
		   as the old one for compatibility reasons */
		if (i == 0) {
			strcpy(dev->name, "FEC");
		} else {
			sprintf (dev->name, "FEC%d",
				ether_fcc_info[i].ether_index + 1);
		}

		efis = &ether_fcc_info[i];

		/*
		 * reset actual phy addr
		 */
		efis->actual_phy_addr = -1;

		dev->priv = efis;
		dev->init = fec_init;
		dev->halt = fec_halt;
		dev->send = fec_send;
		dev->recv = fec_recv;

		eth_register(dev);

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
		int retval;
		struct mii_dev *mdiodev = mdio_alloc();
		if (!mdiodev)
			return -ENOMEM;
		strncpy(mdiodev->name, dev->name, MDIO_NAME_LEN);
		mdiodev->read = fec8xx_miiphy_read;
		mdiodev->write = fec8xx_miiphy_write;

		retval = mdio_register(mdiodev);
		if (retval < 0)
			return retval;
#endif
	}
	return 1;
}

static int fec_send(struct eth_device *dev, void *packet, int length)
{
	int j, rc;
	struct ether_fcc_info_s *efis = dev->priv;
	volatile fec_t *fecp = (volatile fec_t *)(CONFIG_SYS_IMMR + efis->fecp_offset);

	/* section 16.9.23.3
	 * Wait for ready
	 */
	j = 0;
	while ((rtx->txbd[txIdx].cbd_sc & BD_ENET_TX_READY) && (j<TOUT_LOOP)) {
		udelay(1);
		j++;
	}
	if (j>=TOUT_LOOP) {
		printf("TX not ready\n");
	}

	rtx->txbd[txIdx].cbd_bufaddr = (uint)packet;
	rtx->txbd[txIdx].cbd_datlen  = length;
	rtx->txbd[txIdx].cbd_sc |= BD_ENET_TX_READY | BD_ENET_TX_LAST;
	__asm__ ("eieio");

	/* Activate transmit Buffer Descriptor polling */
	fecp->fec_x_des_active = 0x01000000;	/* Descriptor polling active	*/

	j = 0;
	while ((rtx->txbd[txIdx].cbd_sc & BD_ENET_TX_READY) && (j<TOUT_LOOP)) {
		udelay(1);
		j++;
	}
	if (j>=TOUT_LOOP) {
		printf("TX timeout\n");
	}
	/* return only status bits */;
	rc = (rtx->txbd[txIdx].cbd_sc & BD_ENET_TX_STATS);

	txIdx = (txIdx + 1) % TX_BUF_CNT;

	return rc;
}

static int fec_recv (struct eth_device *dev)
{
	struct ether_fcc_info_s *efis = dev->priv;
	volatile fec_t *fecp =
		(volatile fec_t *) (CONFIG_SYS_IMMR + efis->fecp_offset);
	int length;

	for (;;) {
		/* section 16.9.23.2 */
		if (rtx->rxbd[rxIdx].cbd_sc & BD_ENET_RX_EMPTY) {
			length = -1;
			break;	/* nothing received - leave for() loop */
		}

		length = rtx->rxbd[rxIdx].cbd_datlen;

		if (rtx->rxbd[rxIdx].cbd_sc & 0x003f) {
		} else {
			uchar *rx = net_rx_packets[rxIdx];

			length -= 4;

#if defined(CONFIG_CMD_CDP)
			if ((rx[0] & 1) != 0 &&
			    memcmp((uchar *)rx, net_bcast_ethaddr, 6) != 0 &&
			    !is_cdp_packet((uchar *)rx))
				rx = NULL;
#endif
			/*
			 * Pass the packet up to the protocol layers.
			 */
			if (rx != NULL)
				net_process_received_packet(rx, length);
		}

		/* Give the buffer back to the FEC. */
		rtx->rxbd[rxIdx].cbd_datlen = 0;

		/* wrap around buffer index when necessary */
		if ((rxIdx + 1) >= PKTBUFSRX) {
			rtx->rxbd[PKTBUFSRX - 1].cbd_sc =
				(BD_ENET_RX_WRAP | BD_ENET_RX_EMPTY);
			rxIdx = 0;
		} else {
			rtx->rxbd[rxIdx].cbd_sc = BD_ENET_RX_EMPTY;
			rxIdx++;
		}

		__asm__ ("eieio");

		/* Try to fill Buffer Descriptors */
		fecp->fec_r_des_active = 0x01000000;	/* Descriptor polling active    */
	}

	return length;
}

/**************************************************************
 *
 * FEC Ethernet Initialization Routine
 *
 *************************************************************/

#define	FEC_ECNTRL_PINMUX	0x00000004
#define FEC_ECNTRL_ETHER_EN	0x00000002
#define FEC_ECNTRL_RESET	0x00000001

#define FEC_RCNTRL_BC_REJ	0x00000010
#define FEC_RCNTRL_PROM		0x00000008
#define FEC_RCNTRL_MII_MODE	0x00000004
#define FEC_RCNTRL_DRT		0x00000002
#define FEC_RCNTRL_LOOP		0x00000001

#define FEC_TCNTRL_FDEN		0x00000004
#define FEC_TCNTRL_HBC		0x00000002
#define FEC_TCNTRL_GTS		0x00000001

#define	FEC_RESET_DELAY		50

#if defined(CONFIG_RMII)

static inline void fec_10Mbps(struct eth_device *dev)
{
	struct ether_fcc_info_s *efis = dev->priv;
	int fecidx = efis->ether_index;
	uint mask = (fecidx == 0) ? 0x0000010 : 0x0000008;

	if ((unsigned int)fecidx >= 2)
		hang();

	((volatile immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_cptr |=  mask;
}

static inline void fec_100Mbps(struct eth_device *dev)
{
	struct ether_fcc_info_s *efis = dev->priv;
	int fecidx = efis->ether_index;
	uint mask = (fecidx == 0) ? 0x0000010 : 0x0000008;

	if ((unsigned int)fecidx >= 2)
		hang();

	((volatile immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_cptr &= ~mask;
}

#endif

static inline void fec_full_duplex(struct eth_device *dev)
{
	struct ether_fcc_info_s *efis = dev->priv;
	volatile fec_t *fecp = (volatile fec_t *)(CONFIG_SYS_IMMR + efis->fecp_offset);

	fecp->fec_r_cntrl &= ~FEC_RCNTRL_DRT;
	fecp->fec_x_cntrl |=  FEC_TCNTRL_FDEN;	/* FD enable */
}

static inline void fec_half_duplex(struct eth_device *dev)
{
	struct ether_fcc_info_s *efis = dev->priv;
	volatile fec_t *fecp = (volatile fec_t *)(CONFIG_SYS_IMMR + efis->fecp_offset);

	fecp->fec_r_cntrl |=  FEC_RCNTRL_DRT;
	fecp->fec_x_cntrl &= ~FEC_TCNTRL_FDEN;	/* FD disable */
}

static void fec_pin_init(int fecidx)
{
	bd_t           *bd = gd->bd;
	volatile immap_t *immr = (immap_t *) CONFIG_SYS_IMMR;

	/*
	 * Set MII speed to 2.5 MHz or slightly below.
	 *
	 * According to the MPC860T (Rev. D) Fast ethernet controller user
	 * manual (6.2.14),
	 * the MII management interface clock must be less than or equal
	 * to 2.5 MHz.
	 * This MDC frequency is equal to system clock / (2 * MII_SPEED).
	 * Then MII_SPEED = system_clock / 2 * 2,5 MHz.
	 *
	 * All MII configuration is done via FEC1 registers:
	 */
	immr->im_cpm.cp_fec1.fec_mii_speed = ((bd->bi_intfreq + 4999999) / 5000000) << 1;

#if defined(CONFIG_MPC885_FAMILY) && defined(WANT_MII)
	/* use MDC for MII */
	immr->im_ioport.iop_pdpar |=  0x0080;
	immr->im_ioport.iop_pddir &= ~0x0080;
#endif

	if (fecidx == 0) {
#if defined(CONFIG_ETHER_ON_FEC1)

#if defined(CONFIG_MPC885_FAMILY) /* MPC87x/88x have got 2 FECs and different pinout */

#if !defined(CONFIG_RMII)

		immr->im_ioport.iop_papar |=  0xf830;
		immr->im_ioport.iop_padir |=  0x0830;
		immr->im_ioport.iop_padir &= ~0xf000;

		immr->im_cpm.cp_pbpar     |=  0x00001001;
		immr->im_cpm.cp_pbdir     &= ~0x00001001;

		immr->im_ioport.iop_pcpar |=  0x000c;
		immr->im_ioport.iop_pcdir &= ~0x000c;

		immr->im_cpm.cp_pepar     |=  0x00000003;
		immr->im_cpm.cp_pedir     |=  0x00000003;
		immr->im_cpm.cp_peso      &= ~0x00000003;

		immr->im_cpm.cp_cptr      &= ~0x00000100;

#else

#if !defined(CONFIG_FEC1_PHY_NORXERR)
		immr->im_ioport.iop_papar |=  0x1000;
		immr->im_ioport.iop_padir &= ~0x1000;
#endif
		immr->im_ioport.iop_papar |=  0xe810;
		immr->im_ioport.iop_padir |=  0x0810;
		immr->im_ioport.iop_padir &= ~0xe000;

		immr->im_cpm.cp_pbpar     |=  0x00000001;
		immr->im_cpm.cp_pbdir     &= ~0x00000001;

		immr->im_cpm.cp_cptr      |=  0x00000100;
		immr->im_cpm.cp_cptr      &= ~0x00000050;

#endif /* !CONFIG_RMII */

#else
		/*
		 * Configure all of port D for MII.
		 */
		immr->im_ioport.iop_pdpar = 0x1fff;

			immr->im_ioport.iop_pddir = 0x1fff;	/* Rev. D and later */
#endif

#endif	/* CONFIG_ETHER_ON_FEC1 */
	} else if (fecidx == 1) {

#if defined(CONFIG_ETHER_ON_FEC2)

#if defined(CONFIG_MPC885_FAMILY) /* MPC87x/88x have got 2 FECs and different pinout */

#if !defined(CONFIG_RMII)
		immr->im_cpm.cp_pepar     |=  0x0003fffc;
		immr->im_cpm.cp_pedir     |=  0x0003fffc;
		immr->im_cpm.cp_peso      &= ~0x000087fc;
		immr->im_cpm.cp_peso      |=  0x00037800;

		immr->im_cpm.cp_cptr      &= ~0x00000080;
#else

#if !defined(CONFIG_FEC2_PHY_NORXERR)
		immr->im_cpm.cp_pepar     |=  0x00000010;
		immr->im_cpm.cp_pedir     |=  0x00000010;
		immr->im_cpm.cp_peso      &= ~0x00000010;
#endif
		immr->im_cpm.cp_pepar     |=  0x00039620;
		immr->im_cpm.cp_pedir     |=  0x00039620;
		immr->im_cpm.cp_peso      |=  0x00031000;
		immr->im_cpm.cp_peso      &= ~0x00008620;

		immr->im_cpm.cp_cptr      |=  0x00000080;
		immr->im_cpm.cp_cptr      &= ~0x00000028;
#endif /* CONFIG_RMII */

#endif /* CONFIG_MPC885_FAMILY */

#endif /* CONFIG_ETHER_ON_FEC2 */

	}
}

static int fec_reset(volatile fec_t *fecp)
{
	int i;

	/* Whack a reset.
	 * A delay is required between a reset of the FEC block and
	 * initialization of other FEC registers because the reset takes
	 * some time to complete. If you don't delay, subsequent writes
	 * to FEC registers might get killed by the reset routine which is
	 * still in progress.
	 */

	fecp->fec_ecntrl = FEC_ECNTRL_PINMUX | FEC_ECNTRL_RESET;
	for (i = 0;
	     (fecp->fec_ecntrl & FEC_ECNTRL_RESET) && (i < FEC_RESET_DELAY);
	     ++i) {
		udelay (1);
	}
	if (i == FEC_RESET_DELAY)
		return -1;

	return 0;
}

static int fec_init (struct eth_device *dev, bd_t * bd)
{
	struct ether_fcc_info_s *efis = dev->priv;
	volatile immap_t *immr = (immap_t *) CONFIG_SYS_IMMR;
	volatile fec_t *fecp =
		(volatile fec_t *) (CONFIG_SYS_IMMR + efis->fecp_offset);
	int i;

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
	/* the MII interface is connected to FEC1
	 * so for the miiphy_xxx function to work we must
	 * call mii_init since fec_halt messes the thing up
	 */
	if (efis->ether_index != 0)
		__mii_init();
#endif

	if (fec_reset(fecp) < 0)
		printf ("FEC_RESET_DELAY timeout\n");

	/* We use strictly polling mode only
	 */
	fecp->fec_imask = 0;

	/* Clear any pending interrupt
	 */
	fecp->fec_ievent = 0xffc0;

	/* No need to set the IVEC register */

	/* Set station address
	 */
#define ea dev->enetaddr
	fecp->fec_addr_low = (ea[0] << 24) | (ea[1] << 16) | (ea[2] << 8) | (ea[3]);
	fecp->fec_addr_high = (ea[4] << 8) | (ea[5]);
#undef ea

#if defined(CONFIG_CMD_CDP)
	/*
	 * Turn on multicast address hash table
	 */
	fecp->fec_hash_table_high = 0xffffffff;
	fecp->fec_hash_table_low = 0xffffffff;
#else
	/* Clear multicast address hash table
	 */
	fecp->fec_hash_table_high = 0;
	fecp->fec_hash_table_low = 0;
#endif

	/* Set maximum receive buffer size.
	 */
	fecp->fec_r_buff_size = PKT_MAXBLR_SIZE;

	/* Set maximum frame length
	 */
	fecp->fec_r_hash = PKT_MAXBUF_SIZE;

	/*
	 * Setup Buffers and Buffer Desriptors
	 */
	rxIdx = 0;
	txIdx = 0;

	if (!rtx)
		rtx = (RTXBD *)(immr->im_cpm.cp_dpmem + CPM_FEC_BASE);
	/*
	 * Setup Receiver Buffer Descriptors (13.14.24.18)
	 * Settings:
	 *     Empty, Wrap
	 */
	for (i = 0; i < PKTBUFSRX; i++) {
		rtx->rxbd[i].cbd_sc = BD_ENET_RX_EMPTY;
		rtx->rxbd[i].cbd_datlen = 0;	/* Reset */
		rtx->rxbd[i].cbd_bufaddr = (uint) net_rx_packets[i];
	}
	rtx->rxbd[PKTBUFSRX - 1].cbd_sc |= BD_ENET_RX_WRAP;

	/*
	 * Setup Ethernet Transmitter Buffer Descriptors (13.14.24.19)
	 * Settings:
	 *    Last, Tx CRC
	 */
	for (i = 0; i < TX_BUF_CNT; i++) {
		rtx->txbd[i].cbd_sc = BD_ENET_TX_LAST | BD_ENET_TX_TC;
		rtx->txbd[i].cbd_datlen = 0;	/* Reset */
		rtx->txbd[i].cbd_bufaddr = (uint) (&txbuf[0]);
	}
	rtx->txbd[TX_BUF_CNT - 1].cbd_sc |= BD_ENET_TX_WRAP;

	/* Set receive and transmit descriptor base
	 */
	fecp->fec_r_des_start = (unsigned int) (&rtx->rxbd[0]);
	fecp->fec_x_des_start = (unsigned int) (&rtx->txbd[0]);

	/* Enable MII mode
	 */
	/* Half duplex mode */
	fecp->fec_r_cntrl = FEC_RCNTRL_MII_MODE | FEC_RCNTRL_DRT;
	fecp->fec_x_cntrl = 0;

	/* Enable big endian and don't care about SDMA FC.
	 */
	fecp->fec_fun_code = 0x78000000;

	/*
	 * Setup the pin configuration of the FEC
	 */
	fec_pin_init (efis->ether_index);

	rxIdx = 0;
	txIdx = 0;

	/*
	 * Now enable the transmit and receive processing
	 */
	fecp->fec_ecntrl = FEC_ECNTRL_PINMUX | FEC_ECNTRL_ETHER_EN;

	if (efis->phy_addr == -1) {
#ifdef CONFIG_SYS_DISCOVER_PHY
		/*
		 * wait for the PHY to wake up after reset
		 */
		efis->actual_phy_addr = mii_discover_phy (dev);

		if (efis->actual_phy_addr == -1) {
			printf ("Unable to discover phy!\n");
			return -1;
		}
#else
		efis->actual_phy_addr = -1;
#endif
	} else {
		efis->actual_phy_addr = efis->phy_addr;
	}

#if defined(CONFIG_MII) && defined(CONFIG_RMII)
	/*
	 * adapt the RMII speed to the speed of the phy
	 */
	if (miiphy_speed (dev->name, efis->actual_phy_addr) == _100BASET) {
		fec_100Mbps (dev);
	} else {
		fec_10Mbps (dev);
	}
#endif

#if defined(CONFIG_MII)
	/*
	 * adapt to the half/full speed settings
	 */
	if (miiphy_duplex (dev->name, efis->actual_phy_addr) == FULL) {
		fec_full_duplex (dev);
	} else {
		fec_half_duplex (dev);
	}
#endif

	/* And last, try to fill Rx Buffer Descriptors */
	fecp->fec_r_des_active = 0x01000000;	/* Descriptor polling active    */

	efis->initialized = 1;

	return 0;
}


static void fec_halt(struct eth_device* dev)
{
	struct ether_fcc_info_s *efis = dev->priv;
	volatile fec_t *fecp = (volatile fec_t *)(CONFIG_SYS_IMMR + efis->fecp_offset);
	int i;

	/* avoid halt if initialized; mii gets stuck otherwise */
	if (!efis->initialized)
		return;

	/* Whack a reset.
	 * A delay is required between a reset of the FEC block and
	 * initialization of other FEC registers because the reset takes
	 * some time to complete. If you don't delay, subsequent writes
	 * to FEC registers might get killed by the reset routine which is
	 * still in progress.
	 */

	fecp->fec_ecntrl = FEC_ECNTRL_PINMUX | FEC_ECNTRL_RESET;
	for (i = 0;
	     (fecp->fec_ecntrl & FEC_ECNTRL_RESET) && (i < FEC_RESET_DELAY);
	     ++i) {
		udelay (1);
	}
	if (i == FEC_RESET_DELAY) {
		printf ("FEC_RESET_DELAY timeout\n");
		return;
	}

	efis->initialized = 0;
}

#if defined(CONFIG_SYS_DISCOVER_PHY) || defined(CONFIG_MII) || defined(CONFIG_CMD_MII)

/* Make MII read/write commands for the FEC.
*/

#define mk_mii_read(ADDR, REG)	(0x60020000 | ((ADDR << 23) | \
						(REG & 0x1f) << 18))

#define mk_mii_write(ADDR, REG, VAL)	(0x50020000 | ((ADDR << 23) | \
						(REG & 0x1f) << 18) | \
						(VAL & 0xffff))

/* Interrupt events/masks.
*/
#define FEC_ENET_HBERR	((uint)0x80000000)	/* Heartbeat error */
#define FEC_ENET_BABR	((uint)0x40000000)	/* Babbling receiver */
#define FEC_ENET_BABT	((uint)0x20000000)	/* Babbling transmitter */
#define FEC_ENET_GRA	((uint)0x10000000)	/* Graceful stop complete */
#define FEC_ENET_TXF	((uint)0x08000000)	/* Full frame transmitted */
#define FEC_ENET_TXB	((uint)0x04000000)	/* A buffer was transmitted */
#define FEC_ENET_RXF	((uint)0x02000000)	/* Full frame received */
#define FEC_ENET_RXB	((uint)0x01000000)	/* A buffer was received */
#define FEC_ENET_MII	((uint)0x00800000)	/* MII interrupt */
#define FEC_ENET_EBERR	((uint)0x00400000)	/* SDMA bus error */

/* send command to phy using mii, wait for result */
static uint
mii_send(uint mii_cmd)
{
	uint mii_reply;
	volatile fec_t	*ep;
	int cnt;

	ep = &(((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_fec);

	ep->fec_mii_data = mii_cmd;	/* command to phy */

	/* wait for mii complete */
	cnt = 0;
	while (!(ep->fec_ievent & FEC_ENET_MII)) {
		if (++cnt > 1000) {
			printf("mii_send STUCK!\n");
			break;
		}
	}
	mii_reply = ep->fec_mii_data;		/* result from phy */
	ep->fec_ievent = FEC_ENET_MII;		/* clear MII complete */
	return (mii_reply & 0xffff);		/* data read from phy */
}
#endif

#if defined(CONFIG_SYS_DISCOVER_PHY)
static int mii_discover_phy(struct eth_device *dev)
{
#define MAX_PHY_PASSES 11
	uint phyno;
	int  pass;
	uint phytype;
	int phyaddr;

	phyaddr = -1;	/* didn't find a PHY yet */
	for (pass = 1; pass <= MAX_PHY_PASSES && phyaddr < 0; ++pass) {
		if (pass > 1) {
			/* PHY may need more time to recover from reset.
			 * The LXT970 needs 50ms typical, no maximum is
			 * specified, so wait 10ms before try again.
			 * With 11 passes this gives it 100ms to wake up.
			 */
			udelay(10000);	/* wait 10ms */
		}
		for (phyno = 0; phyno < 32 && phyaddr < 0; ++phyno) {
			phytype = mii_send(mk_mii_read(phyno, MII_PHYSID2));
			if (phytype != 0xffff) {
				phyaddr = phyno;
				phytype |= mii_send(mk_mii_read(phyno,
								MII_PHYSID1)) << 16;
			}
		}
	}
	if (phyaddr < 0) {
		printf("No PHY device found.\n");
	}
	return phyaddr;
}
#endif	/* CONFIG_SYS_DISCOVER_PHY */

#if (defined(CONFIG_MII) || defined(CONFIG_CMD_MII)) && !defined(CONFIG_BITBANGMII)

/****************************************************************************
 * mii_init -- Initialize the MII via FEC 1 for MII command without ethernet
 * This function is a subset of eth_init
 ****************************************************************************
 */
static void __mii_init(void)
{
	volatile immap_t *immr = (immap_t *) CONFIG_SYS_IMMR;
	volatile fec_t *fecp = &(immr->im_cpm.cp_fec);

	if (fec_reset(fecp) < 0)
		printf ("FEC_RESET_DELAY timeout\n");

	/* We use strictly polling mode only
	 */
	fecp->fec_imask = 0;

	/* Clear any pending interrupt
	 */
	fecp->fec_ievent = 0xffc0;

	/* Now enable the transmit and receive processing
	 */
	fecp->fec_ecntrl = FEC_ECNTRL_PINMUX | FEC_ECNTRL_ETHER_EN;
}

void mii_init (void)
{
	int i;

	__mii_init();

	/* Setup the pin configuration of the FEC(s)
	*/
	for (i = 0; i < ARRAY_SIZE(ether_fcc_info); i++)
		fec_pin_init(ether_fcc_info[i].ether_index);
}

/*****************************************************************************
 * Read and write a MII PHY register, routines used by MII Utilities
 *
 * FIXME: These routines are expected to return 0 on success, but mii_send
 *	  does _not_ return an error code. Maybe 0xFFFF means error, i.e.
 *	  no PHY connected...
 *	  For now always return 0.
 * FIXME: These routines only work after calling eth_init() at least once!
 *	  Otherwise they hang in mii_send() !!! Sorry!
 *****************************************************************************/

int fec8xx_miiphy_read(struct mii_dev *bus, int addr, int devad, int reg)
{
	unsigned short value = 0;
	short rdreg;    /* register working value */

	rdreg = mii_send(mk_mii_read(addr, reg));

	value = rdreg;
	return value;
}

int fec8xx_miiphy_write(struct mii_dev *bus, int addr, int devad, int reg,
			u16 value)
{
	(void)mii_send(mk_mii_write(addr, reg, value));

	return 0;
}
#endif

#endif

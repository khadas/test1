
/*******  dummy register *********/
#ifndef MIPI_DSI_REGISTER
#define REG_BASE_DSI_HOST                          (0xFFD00000L)

/* ********  mipi_dsi_host = 0xffD06000(0xffD06000 - 0xffD06fff) *********/
#define MIPI_DSI_DWC_VERSION_OS                (0x1800)
#define MIPI_DSI_DWC_PWR_UP_OS                 (0x1801)
#define MIPI_DSI_DWC_CLKMGR_CFG_OS             (0x1802)
#define MIPI_DSI_DWC_DPI_VCID_OS               (0x1803)
#define MIPI_DSI_DWC_DPI_COLOR_CODING_OS       (0x1804)
#define MIPI_DSI_DWC_DPI_CFG_POL_OS            (0x1805)
#define MIPI_DSI_DWC_DPI_LP_CMD_TIM_OS         (0x1806)
#define MIPI_DSI_DWC_PCKHDL_CFG_OS             (0x180b)
#define MIPI_DSI_DWC_GEN_VCID_OS               (0x180c)
#define MIPI_DSI_DWC_MODE_CFG_OS               (0x180d)
#define MIPI_DSI_DWC_VID_MODE_CFG_OS           (0x180e)
#define MIPI_DSI_DWC_VID_PKT_SIZE_OS           (0x180f)
#define MIPI_DSI_DWC_VID_NUM_CHUNKS_OS         (0x1810)
#define MIPI_DSI_DWC_VID_NULL_SIZE_OS          (0x1811)
#define MIPI_DSI_DWC_VID_HSA_TIME_OS           (0x1812)
#define MIPI_DSI_DWC_VID_HBP_TIME_OS           (0x1813)
#define MIPI_DSI_DWC_VID_HLINE_TIME_OS         (0x1814)
#define MIPI_DSI_DWC_VID_VSA_LINES_OS          (0x1815)
#define MIPI_DSI_DWC_VID_VBP_LINES_OS          (0x1816)
#define MIPI_DSI_DWC_VID_VFP_LINES_OS          (0x1817)
#define MIPI_DSI_DWC_VID_VACTIVE_LINES_OS      (0x1818)
#define MIPI_DSI_DWC_EDPI_CMD_SIZE_OS          (0x1819)
#define MIPI_DSI_DWC_CMD_MODE_CFG_OS           (0x181a)
#define MIPI_DSI_DWC_GEN_HDR_OS                (0x181b)
#define MIPI_DSI_DWC_GEN_PLD_DATA_OS           (0x181c)
#define MIPI_DSI_DWC_CMD_PKT_STATUS_OS         (0x181d)
#define MIPI_DSI_DWC_TO_CNT_CFG_OS             (0x181e)
#define MIPI_DSI_DWC_HS_RD_TO_CNT_OS           (0x181f)
#define MIPI_DSI_DWC_LP_RD_TO_CNT_OS           (0x1820)
#define MIPI_DSI_DWC_HS_WR_TO_CNT_OS           (0x1821)
#define MIPI_DSI_DWC_LP_WR_TO_CNT_OS           (0x1822)
#define MIPI_DSI_DWC_BTA_TO_CNT_OS             (0x1823)
#define MIPI_DSI_DWC_SDF_3D_OS                 (0x1824)
#define MIPI_DSI_DWC_LPCLK_CTRL_OS             (0x1825)
#define MIPI_DSI_DWC_PHY_TMR_LPCLK_CFG_OS      (0x1826)
#define MIPI_DSI_DWC_PHY_TMR_CFG_OS            (0x1827)
#define MIPI_DSI_DWC_PHY_RSTZ_OS               (0x1828)
#define MIPI_DSI_DWC_PHY_IF_CFG_OS             (0x1829)
#define MIPI_DSI_DWC_PHY_ULPS_CTRL_OS          (0x182a)
#define MIPI_DSI_DWC_PHY_TX_TRIGGERS_OS        (0x182b)
#define MIPI_DSI_DWC_PHY_STATUS_OS             (0x182c)
#define MIPI_DSI_DWC_PHY_TST_CTRL0_OS          (0x182d)
#define MIPI_DSI_DWC_PHY_TST_CTRL1_OS          (0x182e)
#define MIPI_DSI_DWC_INT_ST0_OS                (0x182f)
#define MIPI_DSI_DWC_INT_ST1_OS                (0x1830)
#define MIPI_DSI_DWC_INT_MSK0_OS               (0x1831)
#define MIPI_DSI_DWC_INT_MSK1_OS               (0x1832)

#define MIPI_DSI_TOP_SW_RESET                  (0x18f0)
#define MIPI_DSI_TOP_CLK_CNTL                  (0x18f1)
#define MIPI_DSI_TOP_CNTL                      (0x18f2)
#define MIPI_DSI_TOP_SUSPEND_CNTL              (0x18f3)
#define MIPI_DSI_TOP_SUSPEND_LINE              (0x18f4)
#define MIPI_DSI_TOP_SUSPEND_PIX               (0x18f5)
#define MIPI_DSI_TOP_MEAS_CNTL                 (0x18f6)
#define MIPI_DSI_TOP_STAT                      (0x18f7)
#define MIPI_DSI_TOP_MEAS_STAT_TE0             (0x18f8)
#define MIPI_DSI_TOP_MEAS_STAT_TE1             (0x18f9)
#define MIPI_DSI_TOP_MEAS_STAT_VS0             (0x18fa)
#define MIPI_DSI_TOP_MEAS_STAT_VS1             (0x18fb)
#define MIPI_DSI_TOP_INTR_CNTL_STAT            (0x18fc)
#define MIPI_DSI_TOP_MEM_PD                    (0x18fd)

/*=============    MIPI_DSI_PHY   ********* */
#define MIPI_DSI_PHY_CTRL                                  (0xff640000 + (0x000 << 2))
#define MIPI_DSI_CHAN_CTRL                                 (0xff640000 + (0x001 << 2))
#define MIPI_DSI_CHAN_STS                                  (0xff640000 + (0x002 << 2))
#define MIPI_DSI_CLK_TIM                                   (0xff640000 + (0x003 << 2))
#define MIPI_DSI_HS_TIM                                    (0xff640000 + (0x004 << 2))
#define MIPI_DSI_LP_TIM                                    (0xff640000 + (0x005 << 2))
#define MIPI_DSI_ANA_UP_TIM                                (0xff640000 + (0x006 << 2))
#define MIPI_DSI_INIT_TIM                                  (0xff640000 + (0x007 << 2))
#define MIPI_DSI_WAKEUP_TIM                                (0xff640000 + (0x008 << 2))
#define MIPI_DSI_LPOK_TIM                                  (0xff640000 + (0x009 << 2))
#define MIPI_DSI_LP_WCHDOG                                 (0xff640000 + (0x00a << 2))
#define MIPI_DSI_ANA_CTRL                                  (0xff640000 + (0x00b << 2))
#define MIPI_DSI_CLK_TIM1                                  (0xff640000 + (0x00c << 2))
#define MIPI_DSI_TURN_WCHDOG                               (0xff640000 + (0x00d << 2))
#define MIPI_DSI_ULPS_CHECK                                (0xff640000 + (0x00e << 2))
#define MIPI_DSI_TEST_CTRL0                                (0xff640000 + (0x00f << 2))
#define MIPI_DSI_TEST_CTRL1                                (0xff640000 + (0x010 << 2))

#define HHI_MIPI_CNTL0                                     (0xff63c000 + (0x00 << 2))
#define HHI_MIPI_CNTL1                                     (0xff63c000 + (0x01 << 2))
#define HHI_MIPI_CNTL2                                     (0xff63c000 + (0x02 << 2))

#endif /* #ifndef MIPI_DSI_REGISTER */

#ifndef HHI_GP0_PLL_CNTL
#define HHI_GP0_PLL_CNTL                                   (0xff63c000 + (0x010 << 2))
#endif
#ifndef HHI_GP0_PLL_CNTL0
#define HHI_GP0_PLL_CNTL0                                  (0xff63c000 + (0x010 << 2))
#endif
#ifndef HHI_GP0_PLL_CNTL1
#define HHI_GP0_PLL_CNTL1                                  (0xff63c000 + (0x11 << 2))
#endif
#ifndef HHI_GP0_PLL_CNTL6
#define HHI_GP0_PLL_CNTL6                                  (0xff63c000 + (0x016 << 2))
#endif

#ifndef HHI_HDMI_PLL_CNTL
#define HHI_HDMI_PLL_CNTL                                  (0xff63c000 + (0xc8 << 2))
#endif
#ifndef HHI_HDMI_PLL_CNTL0
#define HHI_HDMI_PLL_CNTL0                                 (0xff63c000 + (0xc8 << 2))
#endif
#ifndef HHI_HDMI_PLL_CNTL1
#define HHI_HDMI_PLL_CNTL1                                 (0xff63c000 + (0xc9 << 2))
#endif
#ifndef HHI_HDMI_PLL_CNTL2
#define HHI_HDMI_PLL_CNTL2                                 (0xff63c000 + (0xca << 2))
#endif
#ifndef HHI_HDMI_PLL_CNTL3
#define HHI_HDMI_PLL_CNTL3                                 (0xff63c000 + (0xcb << 2))
#endif
#ifndef HHI_HDMI_PLL_CNTL4
#define HHI_HDMI_PLL_CNTL4                                 (0xff63c000 + (0xcd << 2))
#endif
#ifndef HHI_HDMI_PLL_CNTL5
#define HHI_HDMI_PLL_CNTL5                                 (0xff63c000 + (0xcd << 2))
#endif
#ifndef HHI_HDMI_PLL_CNTL6
#define HHI_HDMI_PLL_CNTL6                                 (0xff63c000 + (0xce << 2))
#endif

#ifndef HHI_MIPIDSI_PHY_CLK_CNTL
#define HHI_MIPIDSI_PHY_CLK_CNTL                           (0xff63c000 + (0x95 << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL0
#define HHI_DIF_CSI_PHY_CNTL0                              (0xff63c000 + (0xd8 << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL1
#define HHI_DIF_CSI_PHY_CNTL1                              (0xff63c000 + (0xd9 << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL2
#define HHI_DIF_CSI_PHY_CNTL2                              (0xff63c000 + (0xda << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL3
#define HHI_DIF_CSI_PHY_CNTL3                              (0xff63c000 + (0xdb << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL4
#define HHI_DIF_CSI_PHY_CNTL4                              (0xff63c000 + (0xdc << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL5
#define HHI_DIF_CSI_PHY_CNTL5                              (0xff63c000 + (0xdd << 2))
#endif
#ifndef HHI_DSI_LVDS_EDP_CNTL0
#define HHI_DSI_LVDS_EDP_CNTL0                             (0xff63c000 + (0xd1 << 2))
#endif
#ifndef HHI_DSI_LVDS_EDP_CNTL1
#define HHI_DSI_LVDS_EDP_CNTL1                             (0xff63c000 + (0xd2 << 2))
#endif
#ifndef HHI_CSI_PHY_CNTL1
#define HHI_CSI_PHY_CNTL1                                  (0xff63c000 + (0xd4 << 2))
#endif
#ifndef HHI_CSI_PHY_CNTL2
#define HHI_CSI_PHY_CNTL2                                  (0xff63c000 + (0xd5 << 2))
#endif
#ifndef HHI_CSI_PHY_CNTL3
#define HHI_CSI_PHY_CNTL3                                  (0xff63c000 + (0xd6 << 2))
#endif
#ifndef HHI_LVDS_TX_PHY_CNTL0
#define HHI_LVDS_TX_PHY_CNTL0                              (0xff63c000 + (0xde << 2))
#endif
#ifndef HHI_LVDS_TX_PHY_CNTL1
#define HHI_LVDS_TX_PHY_CNTL1                              (0xff63c000 + (0xdf << 2))
#endif

#ifndef HHI_DIF_CSI_PHY_CNTL10
#define HHI_DIF_CSI_PHY_CNTL10			(0xff63c000 + (0x8e << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL11
#define HHI_DIF_CSI_PHY_CNTL11			(0xff63c000 + (0x8f << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL12
#define HHI_DIF_CSI_PHY_CNTL12			(0xff63c000 + (0x90 << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL13
#define HHI_DIF_CSI_PHY_CNTL13			(0xff63c000 + (0x91 << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL14
#define HHI_DIF_CSI_PHY_CNTL14			(0xff63c000 + (0x92 << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL15
#define HHI_DIF_CSI_PHY_CNTL15			(0xff63c000 + (0x93 << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL16
#define HHI_DIF_CSI_PHY_CNTL16			(0xff63c000 + (0xde << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL6
#define HHI_DIF_CSI_PHY_CNTL6			(0xff63c000 + (0xea << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL7
#define HHI_DIF_CSI_PHY_CNTL7			(0xff63c000 + (0xeb << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL8
#define HHI_DIF_CSI_PHY_CNTL8			(0xff63c000 + (0xec << 2))
#endif
#ifndef HHI_DIF_CSI_PHY_CNTL9
#define HHI_DIF_CSI_PHY_CNTL9			(0xff63c000 + (0xed << 2))
#endif

#ifndef HHI_TCON_PLL_CNTL0
#define HHI_TCON_PLL_CNTL0			(0xff63c000 + (0x020 << 2))
#endif
#ifndef HHI_TCON_PLL_CNTL1
#define HHI_TCON_PLL_CNTL1			(0xff63c000 + (0x021 << 2))
#endif
#ifndef HHI_TCON_PLL_CNTL2
#define HHI_TCON_PLL_CNTL2			(0xff63c000 + (0x022 << 2))
#endif
#ifndef HHI_TCON_PLL_CNTL3
#define HHI_TCON_PLL_CNTL3			(0xff63c000 + (0x023 << 2))
#endif
#ifndef HHI_TCON_PLL_CNTL4
#define HHI_TCON_PLL_CNTL4			(0xff63c000 + (0x0df << 2))
#endif

#ifndef ANACTRL_TCON_PLL0_CNTL0
#define ANACTRL_TCON_PLL0_CNTL0			((0x00e0  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_TCON_PLL0_CNTL1
#define ANACTRL_TCON_PLL0_CNTL1			((0x00e1  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_TCON_PLL0_CNTL2
#define ANACTRL_TCON_PLL0_CNTL2			((0x00e2  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_TCON_PLL0_CNTL3
#define ANACTRL_TCON_PLL0_CNTL3			((0x00e3  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_TCON_PLL0_CNTL4
#define ANACTRL_TCON_PLL0_CNTL4			((0x00e4  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_TCON_PLL0_STS
#define ANACTRL_TCON_PLL0_STS			((0x00ef  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_TCON_PLL1_STS
#define ANACTRL_TCON_PLL1_STS			((0x00f0  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_TCON_PLL2_STS
#define ANACTRL_TCON_PLL2_STS			((0x00f1  << 2) + 0xfe008000)
#endif

#ifndef COMBO_DPHY_CNTL0
#define COMBO_DPHY_CNTL0			((0x0000  << 2) + 0xfe018000)
#endif
#ifndef COMBO_DPHY_CNTL1
#define COMBO_DPHY_CNTL1			((0x0001  << 2) + 0xfe018000)
#endif
#ifndef COMBO_DPHY_VID_PLL0_DIV
#define COMBO_DPHY_VID_PLL0_DIV			((0x0002  << 2) + 0xfe018000)
#endif
#ifndef COMBO_DPHY_VID_PLL1_DIV
#define COMBO_DPHY_VID_PLL1_DIV			((0x0003  << 2) + 0xfe018000)
#endif
#ifndef COMBO_DPHY_VID_PLL2_DIV
#define COMBO_DPHY_VID_PLL2_DIV			((0x0004  << 2) + 0xfe018000)
#endif
#ifndef COMBO_DPHY_EDP_PIXEL_CLK_DIV
#define COMBO_DPHY_EDP_PIXEL_CLK_DIV		((0x0005  << 2) + 0xfe018000)
#endif
#ifndef COMBO_DPHY_EDP_LVDS_TX_PHY0_CNTL0
#define COMBO_DPHY_EDP_LVDS_TX_PHY0_CNTL0	((0x0006  << 2) + 0xfe018000)
#endif
#ifndef COMBO_DPHY_EDP_LVDS_TX_PHY0_CNTL1
#define COMBO_DPHY_EDP_LVDS_TX_PHY0_CNTL1	((0x0009  << 2) + 0xfe018000)
#endif

#ifndef ANACTRL_DIF_PHY_CNTL1
#define ANACTRL_DIF_PHY_CNTL1			((0x00c8  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL2
#define ANACTRL_DIF_PHY_CNTL2			((0x00c9  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL3
#define ANACTRL_DIF_PHY_CNTL3			((0x00ca  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL4
#define ANACTRL_DIF_PHY_CNTL4			((0x00cb  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL5
#define ANACTRL_DIF_PHY_CNTL5			((0x00cc  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL6
#define ANACTRL_DIF_PHY_CNTL6			((0x00cd  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL7
#define ANACTRL_DIF_PHY_CNTL7			((0x00ce  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL8
#define ANACTRL_DIF_PHY_CNTL8			((0x00cf  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL9
#define ANACTRL_DIF_PHY_CNTL9			((0x00d0  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL10
#define ANACTRL_DIF_PHY_CNTL10			((0x00d1  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL11
#define ANACTRL_DIF_PHY_CNTL11			((0x00d2  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL12
#define ANACTRL_DIF_PHY_CNTL12			((0x00d3  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL13
#define ANACTRL_DIF_PHY_CNTL13			((0x00d4  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL14
#define ANACTRL_DIF_PHY_CNTL14			((0x00d5  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL15
#define ANACTRL_DIF_PHY_CNTL15			((0x00d6  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL16
#define ANACTRL_DIF_PHY_CNTL16			((0x00d7  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL17
#define ANACTRL_DIF_PHY_CNTL17			((0x00d8  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL18
#define ANACTRL_DIF_PHY_CNTL18			((0x00d9  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL19
#define ANACTRL_DIF_PHY_CNTL19			((0x00da  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL20
#define ANACTRL_DIF_PHY_CNTL20			((0x00db  << 2) + 0xfe008000)
#endif
#ifndef ANACTRL_DIF_PHY_CNTL21
#define ANACTRL_DIF_PHY_CNTL21			((0x00dc  << 2) + 0xfe008000)
#endif

#ifndef CLKCTRL_VIID_CLK0_DIV
#define CLKCTRL_VIID_CLK0_DIV			((0x0033  << 2) + 0xfe000000)
#endif
#ifndef CLKCTRL_VIID_CLK0_CTRL
#define CLKCTRL_VIID_CLK0_CTRL			((0x0034  << 2) + 0xfe000000)
#endif
#ifndef CLKCTRL_VID_CLK0_CTRL2
#define CLKCTRL_VID_CLK0_CTRL2			((0x0031  << 2) + 0xfe000000)
#endif
#ifndef CLKCTRL_VIID_CLK1_DIV
#define CLKCTRL_VIID_CLK1_DIV			((0x0076  << 2) + 0xfe000000)
#endif
#ifndef CLKCTRL_VIID_CLK1_CTRL
#define CLKCTRL_VIID_CLK1_CTRL			((0x0077  << 2) + 0xfe000000)
#endif
#ifndef CLKCTRL_VID_CLK1_CTRL2
#define CLKCTRL_VID_CLK1_CTRL2			((0x0074  << 2) + 0xfe000000)
#endif
#ifndef CLKCTRL_VIID_CLK2_DIV
#define CLKCTRL_VIID_CLK2_DIV			((0x007b  << 2) + 0xfe000000)
#endif
#ifndef CLKCTRL_VIID_CLK2_CTRL
#define CLKCTRL_VIID_CLK2_CTRL			((0x007c  << 2) + 0xfe000000)
#endif
#ifndef CLKCTRL_VID_CLK2_CTRL2
#define CLKCTRL_VID_CLK2_CTRL2			((0x0079  << 2) + 0xfe000000)
#endif
#ifndef CLKCTRL_VID_PLL_CLK0_DIV
#define CLKCTRL_VID_PLL_CLK0_DIV		((0x0039  << 2) + 0xfe000000)
#endif

#ifndef CLKCTRL_MIPIDSI_PHY_CLK_CTRL
#define CLKCTRL_MIPIDSI_PHY_CLK_CTRL		((0x0041  << 2) + 0xfe000000)
#endif
#ifndef CLKCTRL_MIPI_DSI_MEAS_CLK_CTRL
#define CLKCTRL_MIPI_DSI_MEAS_CLK_CTRL		((0x0080  << 2) + 0xfe000000)
#endif

#ifndef ENCL_VIDEO_H_PRE_DE_END
#define ENCL_VIDEO_H_PRE_DE_END                    0x1ccf
#endif
#ifndef ENCL_VIDEO_H_PRE_DE_BEGIN
#define ENCL_VIDEO_H_PRE_DE_BEGIN                  0x1cd0
#endif
#ifndef ENCL_VIDEO_V_PRE_DE_ELINE
#define ENCL_VIDEO_V_PRE_DE_ELINE                  0x1cd1
#endif
#ifndef ENCL_VIDEO_V_PRE_DE_BLINE
#define ENCL_VIDEO_V_PRE_DE_BLINE                  0x1cd2
#endif
#ifndef ENCL_INBUF_CNTL0
#define ENCL_INBUF_CNTL0                           0x1cd3
#endif
#ifndef ENCL_INBUF_CNTL1
#define ENCL_INBUF_CNTL1                           0x1cd4
#endif
#ifndef ENCL_INBUF_CNT
#define ENCL_INBUF_CNT                             0x1cd5
#endif

#ifndef VPU_VENC_CTRL
#define VPU_VENC_CTRL                              ((0x1cef  << 2) + 0xff000000)
#endif
#ifndef VPU_DISP_VIU0_CTRL
#define VPU_DISP_VIU0_CTRL                         ((0x2786  << 2) + 0xff000000)
#endif
#ifndef VPU_DISP_VIU1_CTRL
#define VPU_DISP_VIU1_CTRL                         ((0x2787  << 2) + 0xff000000)
#endif
#ifndef VPU_DISP_VIU2_CTRL
#define VPU_DISP_VIU2_CTRL                         ((0x2788  << 2) + 0xff000000)
#endif

#ifndef VBO_INFILTER_CTRL
#define VBO_INFILTER_CTRL                          0x14f9
#endif
#ifndef VBO_INFILTER_TICK_PERIOD_L
#define VBO_INFILTER_TICK_PERIOD_L                 0x14f9
#endif
#ifndef VBO_INFILTER_TICK_PERIOD_H
#define VBO_INFILTER_TICK_PERIOD_H                 0x1477
#endif

#define TCON_CORE_FLAG_LIC2			(0xff630000L + (0x00e << 2))

#ifndef REG_TCON_APB_BASE
#define REG_TCON_APB_BASE                          (0xFF600000L)
#define TCON_CORE_REG_START                        0x0000
#define TCON_CTRL_TIMING_BASE                      0x01b0
#define TCON_TOP_CTRL                              0x1000
#define TCON_RGB_IN_MUX                            0x1001
#define TCON_OUT_CH_SEL0                           0x1002
#define TCON_OUT_CH_SEL1                           0x1003
#define TCON_I2C_DEGLITCH_CNTL                     0x1004
#define TCON_STATUS0                               0x1008 /* read only */
#define TCON_PLLLOCK_CNTL                          0x1009
#define TCON_PLLLCK_RST_CNT                        0x100a
#define TCON_RST_CTRL                              0x100b
#define TCON_AXI_OFST                              0x100c
#define TCON_DDRIF_CTRL0                           0x100d
#define TCON_CLK_CTRL                              0x100e
#define TCON_DDRIF_CTRL1                           0x100f
#define TCON_STATUS1                               0x1010 /* read only */
#define TCON_DDRIF_CTRL2                           0x1011
#define TCON_INTR_MASKN                            0x1022
#define TCON_INTR                                  0x1023 /* read only */
#endif

#ifndef TCON_AXI_OFST
#define TCON_AXI_OFST                              0x100c
#endif
#ifndef TCON_AXI_OFST0
#define TCON_AXI_OFST0                             0x200c
#endif
#ifndef TCON_STATUS2
#define TCON_STATUS2                               0x2012
#endif
#ifndef TCON_AXI_OFST1
#define TCON_AXI_OFST1                             0x2013
#endif
#ifndef TCON_AXI_OFST2
#define TCON_AXI_OFST2                             0x2014
#endif
#ifndef TCON_GPO_CTRL0
#define TCON_GPO_CTRL0                             0x2015
#endif
#ifndef TCON_GPO_CTRL1
#define TCON_GPO_CTRL1                             0x2016
#endif
#ifndef TCON_GPO_CTRL2
#define TCON_GPO_CTRL2                             0x2017
#endif
#ifndef TCON_INTR_WR
#define TCON_INTR_WR                               0x2020
#endif
#ifndef TCON_INTR_CLR
#define TCON_INTR_CLR                              0x2021
#endif
#ifndef TCON_INTR_MASKN
#define TCON_INTR_MASKN                            0x2022
#endif
#ifndef TCON_INTR_RO
#define TCON_INTR_RO                               0x2023
#endif

#ifndef P2P_CH_SWAP0
#define P2P_CH_SWAP0                               0x4200
#endif
#ifndef P2P_CH_SWAP1
#define P2P_CH_SWAP1                               0x4201
#endif
#ifndef P2P_BIT_REV
#define P2P_BIT_REV                               ((0x1950  << 2) + 0xff000000)
#endif

#ifndef LVDS_CH_SWAP0
#define LVDS_CH_SWAP0                              0x14e1
#endif
#ifndef LVDS_CH_SWAP1
#define LVDS_CH_SWAP1                              0x14e2
#endif
#ifndef LVDS_CH_SWAP2
#define LVDS_CH_SWAP2                              0x14e3
#endif

#ifndef HHI_DIF_TCON_CNTL0
#define HHI_DIF_TCON_CNTL0                         (0xff63c000 + (0x3c << 2))
#endif
#ifndef HHI_DIF_TCON_CNTL1
#define HHI_DIF_TCON_CNTL1                         (0xff63c000 + (0x3d << 2))
#endif
#ifndef HHI_DIF_TCON_CNTL2
#define HHI_DIF_TCON_CNTL2                         (0xff63c000 + (0x3e << 2))
#endif
#ifndef HHI_TCON_CLK_CNTL
#define HHI_TCON_CLK_CNTL                          (0xff63c000 + (0xf0 << 2))
#endif

#ifndef PWM_PWM_E
#define PWM_PWM_E                                  ((0x6400 << 2) + 0xffd00000)
#endif
#ifndef PWM_PWM_F
#define PWM_PWM_F                                  ((0x6401 << 2) + 0xffd00000)
#endif
#ifndef PWM_MISC_REG_EF
#define PWM_MISC_REG_EF                            ((0x6402 << 2) + 0xffd00000)
#endif

#ifndef REG_BASE_CBUS
#define REG_BASE_CBUS 0x1
#endif

#ifndef REG_BASE_VCBUS
#define REG_BASE_VCBUS 0x2
#endif

#ifndef REG_BASE_DSI_HOST
#define REG_BASE_DSI_HOST 0x3
#endif

#ifndef HHI_GP0_PLL_CNTL2
#define HHI_GP0_PLL_CNTL2 0x4
#endif

#ifndef HHI_GP0_PLL_CNTL3
#define HHI_GP0_PLL_CNTL3 0x4
#endif

#ifndef HHI_GP0_PLL_CNTL4
#define HHI_GP0_PLL_CNTL4 0x4
#endif

#ifndef HHI_GP0_PLL_CNTL5
#define HHI_GP0_PLL_CNTL5 0x4
#endif

#ifndef HHI_VIID_CLK_CNTL
#define HHI_VIID_CLK_CNTL 0x4
#endif

#ifndef HHI_VIID_CLK_DIV
#define HHI_VIID_CLK_DIV 0x4
#endif

#ifndef HHI_VID_PLL_CLK_DIV
#define HHI_VID_PLL_CLK_DIV 0x4
#endif

#ifndef HHI_VID_CLK_CNTL2
#define HHI_VID_CLK_CNTL2 0x4
#endif

#ifndef HHI_MIPI_CNTL0
#define HHI_MIPI_CNTL0 0x4
#endif

#ifndef HHI_MIPI_CNTL1
#define HHI_MIPI_CNTL1 0x4
#endif

#ifndef HHI_MIPI_CNTL2
#define HHI_MIPI_CNTL2 0x4
#endif

#ifndef HHI_VDIN_MEAS_CLK_CNTL
#define HHI_VDIN_MEAS_CLK_CNTL 0x4
#endif

#ifndef PWM_MISC_REG_AB
#define PWM_MISC_REG_AB PWMAB_MISC_REG_AB
#endif

#ifndef PWM_MISC_REG_CD
#define PWM_MISC_REG_CD PWMCD_MISC_REG_AB
#endif

#ifndef PWM_MISC_REG_EF
#define PWM_MISC_REG_EF PWMEF_MISC_REG_AB
#endif

#ifndef PWM_PWM_A
#define PWM_PWM_A PWMCD_PWM_A
#endif

#ifndef PWM_PWM_B
#define PWM_PWM_B PWMCD_PWM_B
#endif

#ifndef PWM_PWM_C
#define PWM_PWM_C PWMCD_PWM_A
#endif

#ifndef PWM_PWM_D
#define PWM_PWM_D PWMCD_PWM_B
#endif

#ifndef PWM_PWM_E
#define PWM_PWM_E PWMEF_PWM_A
#endif

#ifndef PWM_PWM_F
#define PWM_PWM_F PWMEF_PWM_B
#endif

#ifndef PERIPHS_PIN_MUX_0
#define PERIPHS_PIN_MUX_0 PADCTRL_PIN_MUX_REG0
#endif

#ifndef PERIPHS_PIN_MUX_7
#define PERIPHS_PIN_MUX_7 0x5
#endif

#ifndef PERIPHS_PIN_MUX_8
#define PERIPHS_PIN_MUX_8 0x5
#endif

#ifndef PERIPHS_PIN_MUX_9
#define PERIPHS_PIN_MUX_9 0x5
#endif

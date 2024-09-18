/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef REGISTER_H
#define REGISTER_H

//
// Reading file:  ./REG_LIST_RTL.h
//
// synopsys translate_off
// synopsys translate_on
//
//
// Reading file:  ./dmc_clk_freq.vh
//
//`ifdef DMC_FREQ_REG_DEFINE
//`else
//`define DMC_FREQ_REG_DEFINE
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe040000
// -----------------------------------------------
//`define DMC_FREQ_REG_BASE      32'hfe040000
#define AM_DDR_PLL_CNTL0 ((0x0000 << 2) + 0xfe040000)
// bit 29    : dpll_reset.
// bit 28    : dpll_en.
// bit 27:26 : dpll_clk_en
// bit 25    : dpll_inv_sel
// bit 21:19 : od1  OD1[0] : 0 /2,  1: /4.   OD1[2:1].  2'b00: /1, 2'b01: /2. 2'b10 /4. 2'b11: /8.
// bit 18:16 : od
// bit 14:10 : dpll_ref_div_n
// bit 8:0   : dpll_int_num
#define AM_DDR_PLL_CNTL1 ((0x0001 << 2) + 0xfe040000)
// bit 18:0    : ddr_dpll_frac
#define AM_DDR_PLL_CNTL2 ((0x0002 << 2) + 0xfe040000)
// bit 22:20  : fref_sel
// bit 17:16  : os_ssc
// bit 15:12  : ssc_str_m
// bit 8      : ssc_en
// bit 7:4    : ssc_dep_sel
// bit 1:0    : dpll ss_mode.
#define AM_DDR_PLL_CNTL3 ((0x0003 << 2) + 0xfe040000)
// bit 31     : afc bypass
// bit 30     : afc clk sel
// bit 29     : code new
// bit 28     : dco_m_en
// bit 27     : dco_sdm_en
// bit 26     : div2
// bit 25     : div mode
// bit 24     : fast_lock mode
// bit 23     : fb_pre_div
// bit 22     : filter_mode
// bit 21     : fix_en
// bit 20     : freq_shift_en
// bit 19     : load
// bit 18     : load_en
// bit 17     : lock_f
// bit 16     : pulse_width_en
// bit 15     : sdmnc_en
// bit 14     : sdmnc_mode
// bit 13     : sdmnc_range
// bit 12     : tdc_en
// bit 11     : tdc_mode_sel
// bit 10     :  wait_en
#define AM_DDR_PLL_CNTL4 ((0x0004 << 2) + 0xfe040000)
// bit 1:0    : pfd_gain
// bit 7:4    : filter_pvt1
// bit 11:8   : filter pvt2
// bit 13:12  : acq_gain
// bit 18:16  : lambda0
// bit 22:20  : lambda1
// bit 26:24  : rou
// bit 30:28  : alpha
#define AM_DDR_PLL_CNTL5 ((0x0005 << 2) + 0xfe040000)
// bit 15:0   : reve
// bit 21:16  : lm_s
// bit 27:24  : lm_w
// bit 30:28  : adj_vco_ldo
#define AM_DDR_PLL_CNTL6 ((0x0006 << 2) + 0xfe040000)
// bit 15:0   : reve
// bit 21:16  : lm_s
// bit 27:24  : lm_w
// bit 30:28  : adj_vco_ldo
#define AM_DDR_PLL_STS ((0x0007 << 2) + 0xfe040000)
// bit 31     : DDR_PLL_LOCK
// bit 30:19  : not used.
// bit 18     : DDR_AFC_DONE
// bit 17     : DDR_PLL_LOCK
// bit 16:7   : DDR_DPLL_OUT_RSV
// bit 6:0    : DDR_SDMNC_MONITOR
#define DDR_CLK_CNTL ((0x0008 << 2) + 0xfe040000)
// bit 31     ddr_pll_clk enable. enable the clock from DDR_PLL to clock generateion.
// whenever change the DDR_PLL frequency, disable the clock, after the DDR_PLL locked, then enable
// it again.
// bit 30.    ddr_pll_prod_test_en.  enable the clock to clock/32 which to clock frequency
// measurement and production test pin. bit 29.    not used. bit 28.    clock generation logic soft
// reset. 0 = reset. bit 27.    phy_4xclk phase inverter.. bit 25.    DDRPHY DfiClk/DMC clock
// selection.  1:  AM_PLL clk output /2.  0: directly output from AM_PLL . bit 24.    enable AM_PLL
// CLK output /2 function.   1: enable.  0: disable.   if try to use this clkoutput/2 function.
// bit 16.   enable DMC at speed mbist mode.
// bit 9     enable DFICLK use LPCLK/4 at FREQ1..
// bit 8.    reset lpclk logic.
// bit 7     enalbe DFICLK use LPCLK/4 at current freq.
// bit 6.    enable 4Xclock use LPCLK
// bit 5.    not used.
// bit 4.   enable DFICLK use APB clock.
// bit 2. enable dmc_clk.
// bit 1. not used.
// bit 0. enable LPDDR4-PHY clock
#define DDR_PHY_CTRL ((0x0009 << 2) + 0xfe040000)
// LPDDR4 power on reset need to special combination of PwrOkIn and phy_reset_n.
// bit 31:  DDr PHY power on status.  read only.
// bit 5.   DDR PHY dfi_init_start_or.   1: for dfi_init_start = 1 if dmc need to power down.  0:
// normal working mode. bit 4.   DDR PHY PwrOkIn pin. bit 1.   DDR PHY APB soft reset_n. bit 0.
// phy_reset_n.
#define AM_DDR_PLL_FREQ1_OD ((0x000c << 2) + 0xfe040000)
// freqency set 1 PLL OD and OD1 setting. when change to freqency 1 will use this setting.
// frequency set 0 use original DDR_PLL_CNTL0 setting.
// bit 8     currunt FREQ selection.  it can forced to change to select which freqency to select,
// or it can auto changed by FREQ change hardware. bit 5:3   OD1. bit 2:0.  OD. `endif
//
// Closing file:  ./dmc_clk_freq.vh
//
//
// Reading file:  ../mmc_lp4/dmc/rtl/dmc_reg.vh
//
//`define DMC_REG_BASE      32'hfe036000
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe036000
// -----------------------------------------------
#define DMC_REQ_CTRL ((0x0000 << 2) + 0xfe036000)
// bit 31~8.  Not used.
// bit 7.   enable dmc request of axibus chan 7.  DEV0.( Audio eth_top, SPICCx2).
// bit 6.   enable dmc request of axibus chan 6.  DEV1 ( EMMC, SDIO, SEC_TOP USB2).
// bit 5.   enable dmc request of axibus chan 5.  reserved for dmc_test.
// bit 4.   enable dmc request of axibus chan 4.  DSP
// bit 3.   enable dmc request of axibus chan 3.  NNA
// bit 2.   enable dmc request of axibus chan 2.  not used.
// bit 1.   enable dmc request of axibus chan 1.  Not used.
// bit 0.   enable dmc request of axibus chan 0.  CPU/A53   async interface.
// DMC CLK and RESET domain register. please check DMC_SEC_APB_CTRLx register for access details.
#define DMC_SOFT_RST ((0x0001 << 2) + 0xfe036000)
// bit 31~8. reserved for future.
// bit 7:0. 8 AXI BUS input intefaces n_clk domain reset_n signal. 0: reset. 1: normal working
// mode. each bit for one interface.
#define DMC_SOFT_RST1 ((0x0002 << 2) + 0xfe036000)
// To reset the Async interface, you need to disable the interface both clock domain, then reset
// both n_clk and m_clk domain bit 31~8 not used. bit 7:0.  8 AXI bus interfaces master clock
// domain reset_n signal. 0 : reset : 1 normal working mode.
#define DMC_SOFT_RST2 ((0x0003 << 2) + 0xfe036000)
// bit 31~11.  reserved for future.
// bit 10  DMC DFI cmd soft reset_n
// bit 9   DMC DFI MISC soft reset_n
// bit 8   DMC DFI data soft reset_n
// bit 7   DMC DFI dcu soft reset_n
// bit 6   DMC siu soft reset_n
// bit 5.  DMC test soft reset_n.  0 : reset. 1 : normal working mode.
// bit 4.  DMC low power control moudle soft reset_n.    0 : reset. 1 : normal working mode.
// bit 3.  DMC QOS monitor module soft reset_n.   0 : reset. 1 : normal working mode.
// bit 2.  DMC register modle soft reset_n.       0 : reset. 1 : normal working mode.
// bit 1.  DMC canvas transfer module soft reset_n.  0 : reset. 1 : normal working mode.
// bit 0.  DMC command buffers and command generation modules soft reset.  0 = reset. 1:
#define DMC_RST_STS1 ((0x0004 << 2) + 0xfe036000)
// 31~24.  not used.
// 23~0.   Read only.  the DMC_SOFT_RST1 signal in n_clk domain. the purpose of this register is
// when one of the 2 clocks is too slow or too fast,  we can read this register to make sure
// another clock domain reset is done.
#define DMC_CLKG_CTRL0 ((0x0006 << 2) + 0xfe036000)
// bit 23:16. enable the 8 ambus interfaces both main and n_clk auto clock gating function. each 1
// bit for one interface. bit 15:0.  enable the 16 axi interfaces both main and n_clk auto clock
// gating function. each 1 bit for one interface.
#define DMC_CLKG_CTRL1 ((0x0007 << 2) + 0xfe036000)
// bit 23:16. force to disable the 8 ambus interfaces both main and n_clk. each 1 bit for one
// interface. bit 15:0.  force to disable the 16 axi interfaces both main and n_clk. each 1 bit for
// one interface.
#define DMC_CLKG_CTRL2 ((0x0008 << 2) + 0xfe036000)
// bit 12  enalbe auto clock gating for awcmdfifo.
// bit 11  enalbe auto clock gating for arcmdfifo.
// bit 10  enable auto clock gating for dfi command generation
// bit 9   enable auto clock gating for dram cntroller
// bit 8   enable auto clock gating for dfi data path.
// bit 7.  enalbe auto clock gating for write rsp generation.
// bit 6.  enalbe auto clock gating for read rsp generation.
// bit 5.  enalbe auto clock gating for ddr0 command filter.
// bit 4.  enalbe auto clock gating for ddr0 write reorder buffer.
// bit 3.  enalbe auto clock gating for ddr0 write data buffer.
// bit 2.  enalbe auto clock gating for ddr0 read reorder buffer.
// bit 1.  enalbe auto clock gating for read canvas.
// bit 0.  enalbe auto clock gating for write canvas.
#define DMC_CLKG_CTRL3 ((0x0009 << 2) + 0xfe036000)
// bit 12  force to disable the clock of awcmdfifo.
// bit 11  force to disable the clock of arcmdfifo.
// bit 10  force to disable the clock of dfi command generation
// bit 9   force to disable the clock of dram cntroller
// bit 8   force to disable the clock of dfi data path.
// bit 7. force to disalbe the clock of write rsp generation.
// bit 6. force to disalbe the clock of read rsp generation.
// bit 5.  force to disalbe the clock of  command filter.
// bit 4.  force to disalbe the clock of  write reorder buffer.
// bit 3.  force to disalbe the clock of write data buffer.
// bit 2.  force to disalbe the clock of read reorder buffer.
// bit 1.  force to disalbe the clock of read canvas.
// bit 0.  force to disalbe the clock of write canvas.
#define DMC_MON_CTRL0 ((0x0020 << 2) + 0xfe036000)
// bit 31.   qos_mon_en.    write 1 to trigger the enable. polling this bit 0, means finished.  or
// use interrupt to check finish. bit 30.   qos_mon interrupt clear.  clear the qos monitor result.
// read 1 = qos mon finish interrupt. bit 7.    BW monitor 3 enable. bit 6.    BW monitor 3 enable.
// bit 5.    BW monitor 3 enable.
// bit 4.    BW monitor 3 enable.
// bit 3.    BW monitor 3 enable.
// bit 2.    BW monitor 2 enable.
// bit 1.    BW monitor 1 enable.
// bit 0.    BW monitor 0 enable.
#define DMC_MON_TIMER ((0x0021 << 2) + 0xfe036000)
// timer for the monitor period.
#define DMC_MON_ALL_IDLE_CNT ((0x0022 << 2) + 0xfe036000)
// at the test period,  the whole MMC all channel IDLE time. unit, dmc clock.
#define DMC_MON_ALL_BW ((0x0023 << 2) + 0xfe036000)
// at the test period,  the whole MMC granted data cycles. 64bits unit.
#define DMC_MON_ALL16_BW ((0x0024 << 2) + 0xfe036000)
// at the test period,  the whole MMC granted data cycles which goes to 16bits ddr. unit:64bits
#define DMC_MON0_CTRL ((0x0025 << 2) + 0xfe036000)
// BW MONTIOR 0 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define DMC_MON0_CTRL1 ((0x0026 << 2) + 0xfe036000)
// bit 23:0.  BW monitor 0 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define DMC_MON0_CTRL2 ((0x0027 << 2) + 0xfe036000)
// bit 15:0.  BW monitor 0 port select for the selected channel.
#define DMC_MON0_BW ((0x0028 << 2) + 0xfe036000)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define DMC_MON1_CTRL ((0x0029 << 2) + 0xfe036000)
// BW monitor 1 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define DMC_MON1_CTRL1 ((0x002a << 2) + 0xfe036000)
// bit 23:0.  BW monitor 1 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define DMC_MON1_CTRL2 ((0x002b << 2) + 0xfe036000)
// bit 15:0.  BW monitor 1 port select for the selected channel.
#define DMC_MON1_BW ((0x002c << 2) + 0xfe036000)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define DMC_MON2_CTRL ((0x002d << 2) + 0xfe036000)
// BW monitor 2 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define DMC_MON2_CTRL1 ((0x002e << 2) + 0xfe036000)
// bit 23:0.  BW monitor 2 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define DMC_MON2_CTRL2 ((0x002f << 2) + 0xfe036000)
// bit 15:0.  BW monitor 2 port select for the selected channel.
#define DMC_MON2_BW ((0x0030 << 2) + 0xfe036000)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define DMC_MON3_CTRL ((0x0031 << 2) + 0xfe036000)
// BW monitor 3 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define DMC_MON3_CTRL1 ((0x0032 << 2) + 0xfe036000)
// bit 23:0.  BW monitor 3 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define DMC_MON3_CTRL2 ((0x0033 << 2) + 0xfe036000)
// bit 15:0.  BW monitor 3 port select for the selected channel.
#define DMC_MON3_BW ((0x0034 << 2) + 0xfe036000)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define DMC_MON4_CTRL ((0x0035 << 2) + 0xfe036000)
// BW monitor 4 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define DMC_MON4_CTRL1 ((0x0036 << 2) + 0xfe036000)
// bit 23:0.  BW monitor 4 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define DMC_MON4_CTRL2 ((0x0037 << 2) + 0xfe036000)
// bit 15:0.  BW monitor 4 port select for the selected channel.
#define DMC_MON4_BW ((0x0038 << 2) + 0xfe036000)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define DMC_MON5_CTRL ((0x0039 << 2) + 0xfe036000)
// BW monitor 5 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define DMC_MON5_CTRL1 ((0x003a << 2) + 0xfe036000)
// bit 23:0.  BW monitor 5 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define DMC_MON5_CTRL2 ((0x003b << 2) + 0xfe036000)
// bit 15:0.  BW monitor 5 port select for the selected channel.
#define DMC_MON5_BW ((0x003c << 2) + 0xfe036000)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define DMC_MON6_CTRL ((0x003d << 2) + 0xfe036000)
// BW monitor 6 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define DMC_MON6_CTRL1 ((0x003e << 2) + 0xfe036000)
// bit 23:0.  BW monitor 6 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define DMC_MON6_CTRL2 ((0x003f << 2) + 0xfe036000)
// bit 15:0.  BW monitor 6 port select for the selected channel.
#define DMC_MON6_BW ((0x0040 << 2) + 0xfe036000)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define DMC_MON7_CTRL ((0x0041 << 2) + 0xfe036000)
// BW monitor 7 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define DMC_MON7_CTRL1 ((0x0042 << 2) + 0xfe036000)
// bit 23:0.  BW monitor 7 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define DMC_MON7_CTRL2 ((0x0043 << 2) + 0xfe036000)
// bit 15:0.  BW monitor 7 port select for the selected channel.
#define DMC_MON7_BW ((0x0044 << 2) + 0xfe036000)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define DMC_CMD_FILTER_CTRL1 ((0x0050 << 2) + 0xfe036000)
// not used.
#define DMC_CMD_FILTER_CTRL2 ((0x0051 << 2) + 0xfe036000)
// 31:24. keep the bank active if there's urgent level 3 read bank hit request.
// 23:16. keep the bank active if there's urgent level 2 read bank hit request.
// 15:8.  keep the bank active if there's urgent level 1 read bank hit request.
// 7:0.   keep the bank active if there's urgent level 0 read bank hit request.
#define DMC_CMD_FILTER_CTRL3 ((0x0052 << 2) + 0xfe036000)
// bit 31.    force wbuf empty.
// bit 30:26  wbuf high level number
// bit 25:21  wbuf mid  level number
// bit 20:16  wbuf low level number
// bit 14:10  rbuf high level number
// bit 9:5    rbuf middle level number
// bit 4:0    rbuf low level number
#define DMC_CMD_FILTER_CTRL4 ((0x0053 << 2) + 0xfe036000)
// bit 29:25.  tITW.long
// bit 24:20.  tITW. short
// bit 19:12   tAP auto precharge the bank not used if idle that long time.
// bit 11:6    write to read accesses if there write hit request.
// bit 5:0     read to write accesses if there write hit request.
#define DMC_CMD_FILTER_CTRL5 ((0x0054 << 2) + 0xfe036000)
// bit 31:24   Once ddr data bus switch to read, the maxmum read command number to give up the bus
// when there's write request pending for write buffer. bit 23:16   Once ddr data bus switch to
// write, the maxmum write command number to give up the bus when there's read request pending too
// long. bit 15:8.   Once ddr data bus switch to read, the minimum read command number to transfer
// back to write stage if there's still pending read request. bit 7:0.    Once ddr data bus switch
// to write, the minimum write command number to transfer back to read stage if there's still
// pending write request.
#define DMC_CMD_FILTER_CTRL6 ((0x0055 << 2) + 0xfe036000)
// bit 31:24   write urgent 3 request pending hold num.
// bit 23:16   write urgent 2 request pending hold num.
// bit 15:8.   write urgent 1 request pending hold num.
// bit 7:0.    write urgent 0 request pending hold num.
#define DMC_CMD_FILTER_CTRL7 ((0x0056 << 2) + 0xfe036000)
// bit 31:24.  aw_req_pedning signal assertion after wbuf full.
// bit 23:16   aw_req_pending signal hold how long if wbuf not full.
// bit 15:8    write to read waiting cycles if there write hit request.
// bit 7:0     read to write waiting cycles if there write hit request.
#define DMC_CMD_FILTER_CTRL8 ((0x0057 << 2) + 0xfe036000)
// bit 31:8    reserved.
// bit 7:0     rank limit to change to another rank.
#define DMC_CMD_BUFFER_CTRL ((0x0058 << 2) + 0xfe036000)
// bit 31:26  total write buffer number. default 32.
// bit 25:20  total read buffer number. default 32.
// bit 19:8    reserved.
// bit 7:0    aw_pending_inc_num.  incease write ugent level 1 when write command waiting to in
// write buffer that long.
#define DMC_CMD_BUFFER_CTRL1 ((0x0059 << 2) + 0xfe036000)
// bit 29:24  read buffer number in non-urgent request.
// bit 23:16  read buffer bank miss watch dog threshold.
// bit 15:12  read buffer urgent level 3 counter inc weight.
// bit 11:8   read buffer urgent level 2 counter inc weight.
// bit 7:4    read buffer urgent level 1 counter inc weight.
// bit 3:0    read buffer urgent level 0 counter inc weight.
#define DMC_2ARB_CTRL ((0x005c << 2) + 0xfe036000)
// 32:24. Waiting limit to use the highest urgent level in the pipelines.
// 22.    1: allow to increase 2 urgent levels if waiting time is doubled than inc_ugt_limit.
// 21:12  inc_ugt_limit.  if waiting time > inc_ugt_limit, increase the urgent level by one
// 11:6.  the final arbitration control from AXI bus(port channel 0~7).
// 5:0.   the final arbitration weight control for Ambus ( port channel 8~15).
#define DMC_VERSION ((0x005f << 2) + 0xfe036000)
// read only 32'h000a0008  for sc2
#define DMC_AXI0_CHAN_CTRL ((0x0080 << 2) + 0xfe036000)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi0 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 arbiter
// weight
#define DMC_AXI0_HOLD_CTRL ((0x0081 << 2) + 0xfe036000)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define DMC_AXI0_CHAN_CTRL1 ((0x0082 << 2) + 0xfe036000)
// bit 31:28.  FIQ status
// bit 27:24.  IRQ status.
// bit 22      use ACTIVE input as clock gating control.
// bit 21:20.  chan0 QOS mode.
// bit 19:16.   AXI0 QOS high limit.
// bit 15:12    AXI0 QOS mit limit.
// bit 11  ARM  FIQ controlled super urgent enable.
// bit 10  ARM  FIQ controlled urgent enable.
// bit  9. ARM IRQ controlled super urgent enable.
// bit  8. ARM IRQ controlled urgent enable.
// bit  7.  IRQ/FIQ control enable.
// bit  6:5.  not used.
// bit 4. enable AXI0 auto urgent enable. When there's no other request, treat the AXI0 as super
// urgent request. other wise, use the bit3:0 to set the urgent. bit 3:2 A9 urgent if there's VIU
// request. bit 1:0 A9 urgent if there's request other than VIU
#define DMC_AXI1_CHAN_CTRL ((0x0084 << 2) + 0xfe036000)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define DMC_AXI1_HOLD_CTRL ((0x0085 << 2) + 0xfe036000)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define DMC_AXI1_CHAN_CTRL1 ((0x0086 << 2) + 0xfe036000)
// bit 31:28.  FIQ status
// bit 27:24.  IRQ status.
// bit 21:20.  Mali QOS mode.
// bit 19:16.   mail QOS high limit.
// bit 15:12    mail QOS mit limit.
// bit 11  ARM  FIQ controlled super urgent enable.
// bit 10  ARM  FIQ controlled urgent enable.
// bit  9. ARM IRQ controlled super urgent enable.
// bit  8. ARM IRQ controlled urgent enable.
// bit  7.  IRQ/FIQ control enable.
// bit  6:0.  not used.
#define DMC_AXI2_CHAN_CTRL ((0x0088 << 2) + 0xfe036000)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define DMC_AXI2_HOLD_CTRL ((0x0089 << 2) + 0xfe036000)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define DMC_AXI3_CHAN_CTRL ((0x008c << 2) + 0xfe036000)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define DMC_AXI3_HOLD_CTRL ((0x008d << 2) + 0xfe036000)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define DMC_AXI4_CHAN_CTRL ((0x0090 << 2) + 0xfe036000)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define DMC_AXI4_HOLD_CTRL ((0x0091 << 2) + 0xfe036000)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define DMC_AXI5_CHAN_CTRL ((0x0094 << 2) + 0xfe036000)
// not used.
#define DMC_AXI5_HOLD_CTRL ((0x0095 << 2) + 0xfe036000)
// not used.
#define DMC_AXI6_CHAN_CTRL ((0x0098 << 2) + 0xfe036000)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define DMC_AXI6_HOLD_CTRL ((0x0099 << 2) + 0xfe036000)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define DMC_AXI7_CHAN_CTRL ((0x009c << 2) + 0xfe036000)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define DMC_AXI7_HOLD_CTRL ((0x009d << 2) + 0xfe036000)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define DMC_AXI7_CHAN_CTRL1 ((0x009e << 2) + 0xfe036000)
// bit 0.  wrdata hold mode.  1, after receive enough wrdata, send AWVALID. 0: send AWVALID dont
// wait WRDATA.
#define DMC_AXI0_CHAN_STS ((0x00c0 << 2) + 0xfe036000)
#define DMC_AXI1_CHAN_STS ((0x00c1 << 2) + 0xfe036000)
#define DMC_AXI2_CHAN_STS ((0x00c2 << 2) + 0xfe036000)
#define DMC_AXI3_CHAN_STS ((0x00c3 << 2) + 0xfe036000)
#define DMC_AXI4_CHAN_STS ((0x00c4 << 2) + 0xfe036000)
#define DMC_AXI5_CHAN_STS ((0x00c5 << 2) + 0xfe036000)
#define DMC_AXI6_CHAN_STS ((0x00c6 << 2) + 0xfe036000)
#define DMC_AXI7_CHAN_STS ((0x00c7 << 2) + 0xfe036000)
#define DMC_CHAN_STS ((0x00ce << 2) + 0xfe036000)
// AXI0  is first CPU and Mali conbined channel from CCI-400 directly.  The first 2Gbyte address
// will go through this channel. AXI10  is the second CPU, Mali channel combined with NNA  from
// NIC-400.  The upper 2Gbyte address will go through this channel.
// read only register.
// the second mali and NNA channel IDLE.
// the second CPU channel IDLE.
// the first mali channel IDLE.
// the first CPU channel IDLE.
// bit 27      always 1
// bit 26      ddr0 write data buffer idle. 1 : idle 0: busy.
// bit 25      always 1.
// bit 24      ddr0 wbuf idle.              1 : idle 0: busy.
// bit 23:16   ambus channel idle.          1 : idle 0: busy.
// bit 15:0.   axibus channel idle.         1 : idle 0: busy.
#define DMC_IRQ_STS ((0x00cf << 2) + 0xfe036000)
// bit 31:3   Not used.
// bit 2 :    QOS Monitor interrupt flag.  1: means there's QOS monitor interrupt.  write 1 to
// clean this interrupt. bit 1 :    WRITE protection interrupt.  1: means there's write protection
// violation.  need to write DMC_PROT_IRQ_CTRL  bit 1to clean this bit. bit 0 :    read protection
// interrupt.   1: means there's read  protection violation.  need to write DMC_PROT_IRQ_CTRL bit 0
// to clean this bit.
#define DMC_PROT0_RANGE ((0x00d0 << 2) + 0xfe036000)
// protection 0 address range. the range define is 64Kbyte boundary.  current address [31:16] >=
// start address && current address [31:16] <= end address. bit 31:16 :   range end address. bit
// 15:0  :   range start address
#define DMC_PROT0_CTRL ((0x00d1 << 2) + 0xfe036000)
// bit 23:16. each bit to enable one of the 8 ambus channal for the protection function.
// bit 15:0   each bit to enable one of the 15 channel input for the protection function.
#define DMC_PROT0_CTRL1 ((0x00d2 << 2) + 0xfe036000)
// bit 26.  protection 0  read access protection enable.
// bit 25.  protection 0  write access block function. if enabled, the access wouldn't write to
// the DDR SDRAM.  if not enabled only generate a interrupt, but the access still wrote to DDR.
// bit 24.  protection range 0  write access protection enable.
// bit 15:0 for some AXI port subID bits
#define DMC_PROT1_RANGE ((0x00d3 << 2) + 0xfe036000)
// protection 1 address range. the range define is 64Kbyte boundary.  current address [31:16] >=
// start address && current address [31:16] <= end address. bit 31:16 :   range end address. bit
// 15:0  :   range start address
#define DMC_PROT1_CTRL ((0x00d4 << 2) + 0xfe036000)
// bit 23:16. each bit to enable one of the 8 ambus channal for the protection function.
// bit 15:0   each bit to enable one of the 15 channel input for the protection function.
#define DMC_PROT1_CTRL1 ((0x00d5 << 2) + 0xfe036000)
// bit 26.  protection range 1 read access protection enable bit.
// bit 25.  protection 1  write access block function. if enabled, the access wouldn't write to
// the DDR SDRAM.  if not enabled only generate a interrupt, but the access still wrote to DDR.
// bit 24.  protection range 1 write access protection enable bit.
// bit 15:0 for some AXI port subID bits
#define DMC_PROT_VIO_0 ((0x00d6 << 2) + 0xfe036000)
// ddr0 write proection violation address.
#define DMC_PROT_VIO_1 ((0x00d7 << 2) + 0xfe036000)
// bit 31:22 . not used. always 0.
// 21.    ddr0 protection 1 vilation.
// 20     ddr0 protection 0 vilation.
// 19:14. ddr0 write violation AWPROT bits. ( 6 bits for write security)
// 13:12.  Not used.
// 11:0    ddr0_write violation ID. bit 11~9 for Master ID. bit 7:4 for subid.
#define DMC_PROT_VIO_2 ((0x00d8 << 2) + 0xfe036000)
// ddr0 read prot violation address
#define DMC_PROT_VIO_3 ((0x00d9 << 2) + 0xfe036000)
// bit 31:21 . not used. always 0.
// 21     ddr0 read protection 1 violation.
// 20     ddr0 read protection 0 violation.
// 19.    not used.
// 18:16. ddr0 read violation ARPROT bits. (3 bits for read secutiry).
// 15:12. not used.
// 11:0   ddr0 read violation ID.   bit 11~9 for master ID. bit 7:4 for subid.
#define DMC_PROT_IRQ_CTRL ((0x00da << 2) + 0xfe036000)
// bit 2 :  protect function IRQ enable.
// bit 1 :  write protection violation.  write 1 to clean write protection vio registers.
// bit 0 :  read  protection violation.  write 1 to clean read protection vio registers.
//`define DMC_TEST_REG_BASE                32'hfe037800
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe037800
// -----------------------------------------------
#define DMC_TEST_STA ((0x0000 << 2) + 0xfe037800)
// test start address.  for non-sha mode,  the last 5 bits would be ignored. the test address at
// 32bytes boundary.
//                     for sha mode,      address must be in 64 bytes boundary. that mean the last
//                     6 bits must be 0.
#define DMC_TEST_EDA ((0x0001 << 2) + 0xfe037800)
// test end address.  for non-sha mode,  the last 5 bits would be ignored. the test address at
// 32bytes boundary.
//                   for sha mode,       address must be in 64 bytes boundary. that mean the last
//                   6bits must be 1.
#define DMC_TEST_CTRL ((0x0002 << 2) + 0xfe037800)
// bit 31.  enable test.
// bit 30.  when enable test, enable the write to DDR function.
// bit 29.  when enable test, enable the read from DDR function.
// bit 28.  when enable test,  enable the sha calculation function  must be same as read enable
// but without write function. bit 27.  enabe to compare data.  when do the read enable to enable
// the error comparaion. suppose the read data should be same as the data in the write buffer.
// bit 26.  0: save sha result to test_sha_message registers.  1 : don't save.
// bit 25.  address generation type.  0: continuous increase the address in the range of test
// start address and test end address.
//                                   1: test module would pick the random address from test start
//                                   address  and test end address.
// bit 24.  done type.      0 : use the DMC_TEST_NUM register as the counter of test numbers.
//                             for write if the write command number == the DMC_TEST_NUM, the
//                             write is done. for read if the read command number == the DMC
//                             TEST_num, the read id done. for one read command can be repeated
//                             repeat number times.
//                         1 : finshed at end address.
// bit 23.  wdata type.     1 : the first write is {WD3, WD2,WD1,WD0}, then the latter is the
// previous data plus a pattern.( { + WD7,  + WD6, + WD5, + WD4}).
//                         0 : the WDATA is the data in write register.
// bit 23.  1  compare the sha result with the test sha message registers. 0 : dont compare the
// result. bit 22:20.   read repeat times.  for non-sha function, we can define multi times of the
// read. the test module would repeat the same address repeat times. bit 19.     limit write.  0:
// no outstanding write request limitation.
//                          1: limit the outstanding write commands to the number of bits [15:8]
// bit 18.     limit read.   0. no outstanding read request limitation.
//                          1. limit the read outstanding request to the number of bits[7:0].
// bit 17:16.  sha mode for sha function enabled.  00 : not used.  01 : sha1. 2: sha2-256. 3:
// sha2_224. not used in GXL fixed to be  Sha 2. bit 15:8.   write outstanding commands limit. bit
// 7:0.    read  outstanding commands limit.
#define DMC_TEST_NUM ((0x0003 << 2) + 0xfe037800)
// how many test command for the test if the DMC_TEST_CTRL bit 24 is 0.
#define DMC_TEST_WDG ((0x0004 << 2) + 0xfe037800)
// 31:16.  write response watch dog.
// 15:0.   read response  watch dog.
#define DMC_TEST_COMP_MASK ((0x0005 << 2) + 0xfe037800)
// 32bits for DMC TEST COMPARE bit enable.
// 1 : to MASK this bit.  0: compare this bit.
#define DMC_TEST_WSTRB0 ((0x0006 << 2) + 0xfe037800)
// MPC WR FIFO command DM bit write data
// bit 31:16  the second cycle.
// bit 15:0   the first cycle.
#define DMC_TEST_WSTRB1 ((0x0007 << 2) + 0xfe037800)
// MPC WR FIFO command DM bit write data
// bit 31:16. the Forth cycle.
// bit 15:0.  the third cycle.
#define DMC_TEST_WD0 ((0x0010 << 2) + 0xfe037800)
// write data 0 for write command. also for read back data comparision.
#define DMC_TEST_WD1 ((0x0011 << 2) + 0xfe037800)
// write data 1 for write command. also for read back data comparision.
#define DMC_TEST_WD2 ((0x0012 << 2) + 0xfe037800)
// write data 2 for write command. also for read back data comparision.
#define DMC_TEST_WD3 ((0x0013 << 2) + 0xfe037800)
// write data 3 for write command. also for read back data comparision.
#define DMC_TEST_WD4 ((0x0014 << 2) + 0xfe037800)
// write data 4 for write command. also for read back data comparision.
#define DMC_TEST_WD5 ((0x0015 << 2) + 0xfe037800)
// write data 5 for write command. also for read back data comparision.
#define DMC_TEST_WD6 ((0x0016 << 2) + 0xfe037800)
// write data 6 for write command. also for read back data comparision.
#define DMC_TEST_WD7 ((0x0017 << 2) + 0xfe037800)
// write data 7 for write command. also for read back data comparision.
#define DMC_TEST_WD8 ((0x0018 << 2) + 0xfe037800)
// write data 8 for write command. also for read back data comparision.
#define DMC_TEST_WD9 ((0x0019 << 2) + 0xfe037800)
// write data 9 for write command. also for read back data comparision.
#define DMC_TEST_WD10 ((0x001a << 2) + 0xfe037800)
// write data 10 for write command. also for read back data comparision.
#define DMC_TEST_WD11 ((0x001b << 2) + 0xfe037800)
// write data 11 for write command. also for read back data comparision.
#define DMC_TEST_WD12 ((0x001c << 2) + 0xfe037800)
// write data 12 for write command. also for read back data comparision.
#define DMC_TEST_WD13 ((0x001d << 2) + 0xfe037800)
// write data 13 for write command. also for read back data comparision.
#define DMC_TEST_WD14 ((0x001e << 2) + 0xfe037800)
// write data 14 for write command. also for read back data comparision.
#define DMC_TEST_WD15 ((0x001f << 2) + 0xfe037800)
// write data 15 for write command. also for read back data comparision.
#define DMC_TEST_RD0 ((0x0020 << 2) + 0xfe037800)
// the read back data 0.  if error happens, it would capture the first error data.
#define DMC_TEST_RD1 ((0x0021 << 2) + 0xfe037800)
// the read back data 1.  if error happens, it would capture the first error data.
#define DMC_TEST_RD2 ((0x0022 << 2) + 0xfe037800)
// the read back data 2.  if error happens, it would capture the first error data.
#define DMC_TEST_RD3 ((0x0023 << 2) + 0xfe037800)
// the read back data 3.  if error happens, it would capture the first error data.
#define DMC_TEST_RD4 ((0x0024 << 2) + 0xfe037800)
// the read back data 4.  if error happens, it would capture the first error data.
#define DMC_TEST_RD5 ((0x0025 << 2) + 0xfe037800)
// the read back data 5.  if error happens, it would capture the first error data.
#define DMC_TEST_RD6 ((0x0026 << 2) + 0xfe037800)
// the read back data 6.  if error happens, it would capture the first error data.
#define DMC_TEST_RD7 ((0x0027 << 2) + 0xfe037800)
// the read back data 7.  if error happens, it would capture the first error data.
#define DMC_TEST_RD8 ((0x0028 << 2) + 0xfe037800)
// the read back data 7.  if error happens, it would capture the first error data.
#define DMC_TEST_RD9 ((0x0029 << 2) + 0xfe037800)
// the read back data 7.  if error happens, it would capture the first error data.
#define DMC_TEST_RD10 ((0x002a << 2) + 0xfe037800)
// the read back data 7.  if error happens, it would capture the first error data.
#define DMC_TEST_RD11 ((0x002b << 2) + 0xfe037800)
// the read back data 7.  if error happens, it would capture the first error data.
#define DMC_TEST_RD12 ((0x002c << 2) + 0xfe037800)
// the read back data 7.  if error happens, it would capture the first error data.
#define DMC_TEST_RD13 ((0x002d << 2) + 0xfe037800)
// the read back data 7.  if error happens, it would capture the first error data.
#define DMC_TEST_RD14 ((0x002e << 2) + 0xfe037800)
// the read back data 7.  if error happens, it would capture the first error data.
#define DMC_TEST_RD15 ((0x002f << 2) + 0xfe037800)
// the read back data 7.  if error happens, it would capture the first error data.
#define DMC_TEST_ERR_ADDR ((0x0040 << 2) + 0xfe037800)
// read only. it capature the first error address.
#define DMC_TEST_ERR_CNT ((0x0041 << 2) + 0xfe037800)
// read only. how many data error happens in the whole test period.
#define DMC_TEST_STS ((0x0042 << 2) + 0xfe037800)
// read only.
// bit 31,   test done bit. write 1 to clean.
// bit 30,   indicate address err
// bit 29~7.  not used.
// bit 6.    read data resp error(caused by security or rd latency).
// bit 5.    test MRR/MPR rd latency error. write 1 clear
// bit 4,    sha done.     write 1 to clean.
// bit 3,    write done.   write 1 to clean.
// bit 2,    read done.    write 1 to clean
// bit 1,    write watchdog triggered.   write 1 to clean
// bit 0,    read watchdog triggered.    write 1 to clean.
#define DMC_TEST_WRCMD_ADDR ((0x0043 << 2) + 0xfe037800)
// read only. the current write cmd address.
#define DMC_TEST_RDCMD_ADDR ((0x0044 << 2) + 0xfe037800)
// read only. the current read command address.
#define DMC_TEST_RDRSP_ADDR ((0x0045 << 2) + 0xfe037800)
// read only. the failed read response address(for error data )
//`define DMC_DRAM_REG_BASE      32'hfe036400
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe036400
// -----------------------------------------------
// there's 2 set of timing DDR timing parameter for 2 set of DDR freqency parameter.
// when change frequency, the hardware would automatically select one of these two set of timing
// parameter DMC_DRAM_* is for Frequency set 0. DMC_NFQ_* is for Freqency set 1.
#define DMC_DRAM_TMRD ((0x0000 << 2) + 0xfe036400)
// bit 4:0.  tMRD. //MR command cycles, in DDR3/4.  in LPDDR4, it should be value of tMRW
#define DMC_DRAM_TRFC ((0x0001 << 2) + 0xfe036400)
// bit 9:0 tRFC
#define DMC_DRAM_TRP ((0x0002 << 2) + 0xfe036400)
// bit 21:16.  tRP for precharge all banks.
// bit 5:0.    tRP for precharge one bank.
#define DMC_DRAM_TRTW ((0x0003 << 2) + 0xfe036400)
// bit 31:6:   Not used.
// bit 5:0     DDR3/4 mode : tRTW.
// For LPDDR4 .  The total read command -> write command = (RL + BL/2 - tWODTON) + TDQSCK_MAX +
// tWPRE +RD(tRPST).
//                 tRTW = TDQSCK_max + tWPRE + tRD(tRPST)  + (delay margin)
#define DMC_DRAM_TCL ((0x0004 << 2) + 0xfe036400)
// bit 5:0  tCL/tRL. read latency.
#define DMC_DRAM_TCWL ((0x0005 << 2) + 0xfe036400)
// bit 5:0.  CWL:  write latency.
#define DMC_DRAM_TRAS ((0x0006 << 2) + 0xfe036400)
// bit 7:0.  tRAS.  minimum active to precharge time for same bank.
#define DMC_DRAM_TRC ((0x0007 << 2) + 0xfe036400)
// bit 7:0.  tRC.  minimum active to active time for same bank.
#define DMC_DRAM_TRCD ((0x0008 << 2) + 0xfe036400)
// bit 7:0  tRCD  active to read/write timing for same bank.
#define DMC_DRAM_TRRD ((0x0009 << 2) + 0xfe036400)
// bit 21:16.  tRRD_l  active bank A to active B in same band group for DDR4.
// bit 5:0.    tRRD/tRRD_s   active bank A to active bank b time.
// tRRD_s:   active bank A to active bank b in different bank grousp for DDR4.
#define DMC_DRAM_TFAW ((0x000a << 2) + 0xfe036400)
// bit 8:0   tFAW.  four active command windows
#define DMC_DRAM_TRTP ((0x000b << 2) + 0xfe036400)
// bit 5:0  tRTP.
#define DMC_DRAM_TWR ((0x000c << 2) + 0xfe036400)
// bit 5:0 tWR.
#define DMC_DRAM_TWTR ((0x000d << 2) + 0xfe036400)
// bit 21:16 tWTR_l   For DDR4 WTR_l.  FOR DDR3/LPDDR4 same as tWTR_s.
// bit 5:0 tWTR_s.
#define DMC_DRAM_TCCD ((0x000e << 2) + 0xfe036400)
// bit 19:16. tCCD/tCCD_l.
// bit 3:0 tCCD/tCCD_s    read to read command time or write to write command time.
#define DMC_DRAM_TEXSR ((0x000f << 2) + 0xfe036400)
// bit 12:0. tEXSR.  EXIT SELF-REFRESH to read/write command.
#define DMC_DRAM_TXS ((0x0010 << 2) + 0xfe036400)
// bit 9:0  tXS.  EXIT SELF_REFRESH to other command time
#define DMC_DRAM_TXP ((0x0011 << 2) + 0xfe036400)
// bit 3:0. tXP.  EXIT power down to other command time
#define DMC_DRAM_TXPDLL ((0x0012 << 2) + 0xfe036400)
// bit 12:0.  tXPDLL,  EXIT power down to read/write command time(need to relock PLL).
#define DMC_DRAM_TZQCS ((0x0013 << 2) + 0xfe036400)
// bit 11:0.  ZQCS command to other command time.
#define DMC_DRAM_TCKSRE ((0x0014 << 2) + 0xfe036400)
// bit 4:0. enter self refresh to disable clock time.
#define DMC_DRAM_TCKSRX ((0x0015 << 2) + 0xfe036400)
// bit 4:0. enable clock to exit self refresh time.
#define DMC_DRAM_TCKE ((0x0016 << 2) + 0xfe036400)
// bit 4:0.  CKE high or low minimum time.
#define DMC_DRAM_TMOD ((0x0017 << 2) + 0xfe036400)
// bit 4:0  tMOD.  MRR/MRW to other command time. in LPDDR4, still use this register but it called
// tMRD.
#define DMC_DRAM_TDQS ((0x0018 << 2) + 0xfe036400)
// bit 31:28 reserved
// bit 27:24 tDQS. the delay for write after read in different rank.
// bit 23:20 reserved
// bit 19:16 tDQS. the delay for read after write in different rank.
// bit 15:12 reserved
// bit 11:8  tDQS. the delay for write after write in different rank.
// bit 7:4 reserved
// bit 3:0 tDQS. the delay for read after read in different rank.
#define DMC_DRAM_TRSTL ((0x0019 << 2) + 0xfe036400)
// not used.
#define DMC_DRAM_TZQLAT ((0x001a << 2) + 0xfe036400)
// bit 5:0 ZQ LATCH command to other command timing in LPDDR4 mode.
#define DMC_DRAM_TMRR ((0x001b << 2) + 0xfe036400)
// bit 7:0 tMRR  not used in DMC.
#define DMC_DRAM_TCKESR ((0x001c << 2) + 0xfe036400)
// bit 9:0 tCKESR.   CKE low minimum pulse in self refresh mode.
#define DMC_DRAM_TDPD ((0x001d << 2) + 0xfe036400)
// not support.
#define DMC_DRAM_DFITCTRLDELAY ((0x001e << 2) + 0xfe036400)
// bit 3:0. DFI_t_ctrldealy
#define DMC_DRAM_DFITPHYWRDATA ((0x001f << 2) + 0xfe036400)
// bit 5:0.  dfi_t_phy_wrdata.
#define DMC_DRAM_DFITPHYWRLAT ((0x0020 << 2) + 0xfe036400)
// bit 5:0.  dfi_t_phy_wrlat.  in DDR3/4/LPDDR3 mode:   WL -5.   in LPDDR4 mode: WL -5 + 2.
#define DMC_DRAM_DFITRDDATAEN ((0x0021 << 2) + 0xfe036400)
// bit 5:0.  dfi_t_rddata_en.  in DDR3/4/LPDDR3 mode: RL -5. in LPDDR4 mode : RL -5 + 1.
#define DMC_DRAM_DFITPHYRDLAT ((0x0022 << 2) + 0xfe036400)
// bit 5:0.  dfi_t_rdlat.
#define DMC_DRAM_DFITCTRLUPDMIN ((0x0023 << 2) + 0xfe036400)
// bit 7:0.  CTRLUPD_MIN  minimux clock cycle to maintain CTRLUPD_REQ.
#define DMC_DRAM_DFITCTRLUPDMAX ((0x0024 << 2) + 0xfe036400)
// bit 7:0   CTRLUPD_MAX.  maxmum clock cycle to maintain CTRLUPD_REQ if no CTRLUPD_ACK response.
#define DMC_DRAM_DFITREFMSKI ((0x0026 << 2) + 0xfe036400)
// not used.
#define DMC_DRAM_DFITCTRLUPDI ((0x0027 << 2) + 0xfe036400)
// not used.
#define DMC_DRAM_DFITDRAMCLK ((0x0028 << 2) + 0xfe036400)
// bit 17    dram clk1 enable.
// bit 16    dram clk0 enable.
// bit 15:8  DRAM CLK disable waiting time
// bit 7:0   DRAM CLK enable  enable timer
#define DMC_DRAM_DFITLPRESP ((0x002a << 2) + 0xfe036400)
// bit 3:0.  dfi_lp_ctrl_req response time. after dfi_lp_ctrl_req asserted, and after response
// time if there's still no dfi_lp_ack respone, then drop the dfi_lp_ctrl_req.
#define DMC_DRAM_TCKECK ((0x002c << 2) + 0xfe036400)
// bit 4:0. tCKECK  from CKE low to assert dfi_dram_clk_disable time. this time + dfi_t_ctrl_delay
#define DMC_DRAM_TREFI ((0x002d << 2) + 0xfe036400)
// write this register will update the auto refresh related register to the auto refresh control
// logic. bit 31:24:  tZQCI dmc send zqci period.  unit is how much auto refresh period. bit 23:16
// pvti  dmc send dfi_ctrlupd_req period.  unit is one auto refresh period. bit 15:8.   tREFI.dmc
// send auto refresh command period. unit is 100ns. bit 7:0.    t100ns period. unit is dmc clock
// cycles
#define DMC_DRAM_TSR ((0x002e << 2) + 0xfe036400)
// bit 5:0 tSR.  self resfresh enter to exit time.
#define DMC_DRAM_TCCDMW ((0x002f << 2) + 0xfe036400)
// bit 5:0.  4*tCCD in LPDDR4 mask write.
#define DMC_DRAM_TESCKE ((0x0030 << 2) + 0xfe036400)
// bit 5:0  tESCKE.  enter self refresh to power time for LPDDR4.
#define DMC_DRAM_TREFI_DDR3 ((0x0031 << 2) + 0xfe036400)
// 7:0. DDR3 SDRAM tREFI single auto refresh time . the unit is t100ns.
// use this to check in 8*tREFI time, the DMC should not sent more than 16 auto REFRESH command.
#define DMC_DRAM_TZQCAL ((0x0032 << 2) + 0xfe036400)
// 11:0. ZQCAL for LPDDR4. ZQINIT/ZQoper for DDR3/4 ZQCL command.
#define DMC_DRAM_T10US ((0x0033 << 2) + 0xfe036400)
// 10us clock cycle number used for LP2 mode.
#define DMC_DRAM_TMRRI ((0x0034 << 2) + 0xfe036400)
// bit 7:0   tMRRI for MRR
#define DMC_DRAM_TXS_FAST ((0x0035 << 2) + 0xfe036400)
// bit 9:0 DDR4 mode XS_FAST exit self_refrest to zqcl/zqcs/mrs command.
#define DMC_DRAM_DFIODTCFG ((0x0036 << 2) + 0xfe036400)
// bit 12.  rank1 ODT default. default vulue for ODT[1] pins if theres no read/write activity.
// bit 11.  rank1 ODT write sel.  enable ODT[1] if there's write occur in rank1.
// bit 10.  rank1 ODT write nsel. enable ODT[1] if theres's write occur in rank0.
// bit 9.   rank1 odt read sel.   enable ODT[1] if there's read occur in rank1.
// bit 8.   rank1 odt read nsel.  enable ODT[1] if there's read occurred in rank0.
// bit 4.   rank0 ODT default.    default vulue for ODT[0] pins if theres no read/write activity.
// bit 3.   rank0 ODT write sel.  enable ODT[0] if there's write occur in rank0.
// bit 2.   rank0 ODT write nsel. enable ODT[0] if theres's write occur in rank1.
// bit 1.   rank0 odt read sel.   enable ODT[0] if there's read occur in rank0.
// bit 0.   rank0 odt read nsel.  enable ODT[0] if there's read occurred in rank1.
#define DMC_DRAM_DFIODTCFG1 ((0x0037 << 2) + 0xfe036400)
// bit 27:24  ODT length for BL8 read transfer.
// bit 19:16. ODT length for BL8 write transfer.
// bit 12:8.  ODT latency for reads.  suppose to be 0.
// bit 4:0.   ODT latency for writes.  suppose to be 0.
#define DMC_DRAM_TWODTON ((0x0038 << 2) + 0xfe036400)
// bit 5:0   DRAM write access ODT on time.
//   in DDR3/4 should be same as WL.
//   in LPDDR4 ODT enable  mode:  tODTLon + tODTon.min
//   In LPDDR4 ODT disable mode:  tWL.
#define DMC_DRAM_TRETRAIN ((0x0039 << 2) + 0xfe036400)
// bit 15:0 LPDDR4 OSCRING retraining timer(units = auto_refresh timer). sync with autorefresh
#define DMC_DRAM_PHYADDRON ((0x003a << 2) + 0xfe036400)
// bit 5:0 PHY_CTRL_ADDR_ON for new PHY. default : 12 unit: DfiClk
#define DMC_DRAM_PHYWRON ((0x003b << 2) + 0xfe036400)
// bit 6:0 PHY_CTRL_ADDR_ON for new PHY. unit: ddr clk
// PHY_CTRL_WR_ON.  = 20 + WL + (tDQSS+ tDQS2DQ + tWPST)/ddr_clk + BL/2
#define DMC_DRAM_PHYRDON ((0x003c << 2) + 0xfe036400)
// PHY_CTRL_RD_ON.  = 20 + RL + (tDQSCK+ tRPST + tDQSQ)/ddr_clk + BL/2
#define DMC_DRAM_ZQCTRL ((0x003d << 2) + 0xfe036400)
// tZQCI bits in DMC_DRAM_TREFI  defined how many refresh period send ZQCS/ZQUPD/command.
// this register defines in 0~tZQCI period, which refresh period count to send partical
// ZQCS/ZACAL/ZQUPD command 31:24.  in LPDDR4 case when to send ZQLAT comman to both RANKs of
// LPDDR4 SDRAM 23:16.  when to send PHY ZQ UPDATE command. 15:8.   when to send ZQCS/ZQCAL to
// rank1 DDR SDRAM. 7:0.    when to senc ZQCS/ZQCAL to rank0 DDR SDRAM. timing parameter for
// frequency set 1.
#define DMC_NFQ_TMRD ((0x0040 << 2) + 0xfe036400)
#define DMC_NFQ_TRFC ((0x0041 << 2) + 0xfe036400)
#define DMC_NFQ_TRP ((0x0042 << 2) + 0xfe036400)
#define DMC_NFQ_TRTW ((0x0043 << 2) + 0xfe036400)
#define DMC_NFQ_TCL ((0x0044 << 2) + 0xfe036400)
#define DMC_NFQ_TCWL ((0x0045 << 2) + 0xfe036400)
#define DMC_NFQ_TRAS ((0x0046 << 2) + 0xfe036400)
#define DMC_NFQ_TRC ((0x0047 << 2) + 0xfe036400)
#define DMC_NFQ_TRCD ((0x0048 << 2) + 0xfe036400)
#define DMC_NFQ_TRRD ((0x0049 << 2) + 0xfe036400)
#define DMC_NFQ_TFAW ((0x004a << 2) + 0xfe036400)
#define DMC_NFQ_TRTP ((0x004b << 2) + 0xfe036400)
#define DMC_NFQ_TWR ((0x004c << 2) + 0xfe036400)
#define DMC_NFQ_TWTR ((0x004d << 2) + 0xfe036400)
#define DMC_NFQ_TCCD ((0x004e << 2) + 0xfe036400)
#define DMC_NFQ_TEXSR ((0x004f << 2) + 0xfe036400)
#define DMC_NFQ_TXS ((0x0050 << 2) + 0xfe036400)
#define DMC_NFQ_TXP ((0x0051 << 2) + 0xfe036400)
#define DMC_NFQ_TXPDLL ((0x0052 << 2) + 0xfe036400)
#define DMC_NFQ_TZQCS ((0x0053 << 2) + 0xfe036400)
#define DMC_NFQ_TCKSRE ((0x0054 << 2) + 0xfe036400)
#define DMC_NFQ_TCKSRX ((0x0055 << 2) + 0xfe036400)
#define DMC_NFQ_TCKE ((0x0056 << 2) + 0xfe036400)
#define DMC_NFQ_TMOD ((0x0057 << 2) + 0xfe036400)
#define DMC_NFQ_TDQS ((0x0058 << 2) + 0xfe036400)
#define DMC_NFQ_TRSTL ((0x0059 << 2) + 0xfe036400)
#define DMC_NFQ_TZQLAT ((0x005a << 2) + 0xfe036400)
#define DMC_NFQ_TMRR ((0x005b << 2) + 0xfe036400)
#define DMC_NFQ_TCKESR ((0x005c << 2) + 0xfe036400)
#define DMC_NFQ_TDPD ((0x005d << 2) + 0xfe036400)
#define DMC_NFQ_DFITCTRLDELAY ((0x005e << 2) + 0xfe036400)
#define DMC_NFQ_DFITPHYWRDATA ((0x005f << 2) + 0xfe036400)
#define DMC_NFQ_DFITPHYWRLAT ((0x0060 << 2) + 0xfe036400)
#define DMC_NFQ_DFITRDDATAEN ((0x0061 << 2) + 0xfe036400)
#define DMC_NFQ_DFITPHYRDLAT ((0x0062 << 2) + 0xfe036400)
#define DMC_NFQ_DFITCTRLUPDMIN ((0x0063 << 2) + 0xfe036400)
#define DMC_NFQ_DFITCTRLUPDMAX ((0x0064 << 2) + 0xfe036400)
#define DMC_NFQ_DFITREFMSKI ((0x0066 << 2) + 0xfe036400)
#define DMC_NFQ_DFITCTRLUPDI ((0x0067 << 2) + 0xfe036400)
#define DMC_NFQ_DFITDRAMCLK ((0x0068 << 2) + 0xfe036400)
#define DMC_NFQ_DFITLPRESP ((0x006a << 2) + 0xfe036400)
#define DMC_NFQ_TCKECK ((0x006c << 2) + 0xfe036400)
#define DMC_NFQ_TREFI ((0x006d << 2) + 0xfe036400)
#define DMC_NFQ_TSR ((0x006e << 2) + 0xfe036400)
#define DMC_NFQ_TCCDMW ((0x006f << 2) + 0xfe036400)
#define DMC_NFQ_TESCKE ((0x0070 << 2) + 0xfe036400)
#define DMC_NFQ_TREFI_DDR3 ((0x0071 << 2) + 0xfe036400)
#define DMC_NFQ_TZQCAL ((0x0072 << 2) + 0xfe036400)
#define DMC_NFQ_T10US ((0x0073 << 2) + 0xfe036400)
#define DMC_NFQ_TMRRI ((0x0074 << 2) + 0xfe036400)
#define DMC_NFQ_TXS_FAST ((0x0075 << 2) + 0xfe036400)
#define DMC_NFQ_DFIODTCFG ((0x0076 << 2) + 0xfe036400)
#define DMC_NFQ_DFIODTCFG1 ((0x0077 << 2) + 0xfe036400)
#define DMC_NFQ_TWODTON ((0x0078 << 2) + 0xfe036400)
#define DMC_NFQ_TRETRAIN ((0x0079 << 2) + 0xfe036400)
#define DMC_NFQ_PHYADDRON ((0x007a << 2) + 0xfe036400)
#define DMC_NFQ_PHYWRON ((0x007b << 2) + 0xfe036400)
#define DMC_NFQ_PHYRDON ((0x007c << 2) + 0xfe036400)
#define DMC_NFQ_ZQCTRL ((0x007d << 2) + 0xfe036400)
// end of second frequency timing parameter
#define DMC_DRAM_DFITPHYUPDTYPE0 ((0x0080 << 2) + 0xfe036400)
// dfi_phyupd_ack hold time for dfi_phyupd_req type = 0.
#define DMC_DRAM_DFITPHYUPDTYPE1 ((0x0081 << 2) + 0xfe036400)
// dfi_phyupd_ack hold time for dfi_phyupd_req type = 1.
#define DMC_DRAM_DFITPHYUPDTYPE2 ((0x0082 << 2) + 0xfe036400)
// dfi_phyupd_ack hold time for dfi_phyupd_req type = 2.
#define DMC_DRAM_DFITPHYUPDTYPE3 ((0x0083 << 2) + 0xfe036400)
// dfi_phyupd_ack hold time for dfi_phyupd_req type = 3.
#define DMC_DRAM_MCFG ((0x0086 << 2) + 0xfe036400)
// bit 31:27  not used.
// bit 26:24  rank1_d16_sel.  16bit mode, rank 1 byte selection.
// bit 23     not used.
// bit 22:20. rank0_d16_sel. 16bit mode, rank 0 byte selection.
// bit 19.   send PHY ZQ command  after siu self refresh exit. 1 : enable.  0 : disable.
// bit 18.   send retrain command after siu self refresh exit. 1 : enable. 0 : disable.
// bit 17.   in DDR3/4 mode, send ZQCL command after exit register triggered self refresh.
// bit 16.   send refresh command after finish frequency change. 1 : enable. 0 : disable.
// bit 15.   send refresh command after finish LPDDR4 retraining. 1 : enable. 0 : disable.
// bit 14.   1: cke init low.  0 : cke init high.
// bit 13    1: dbi write enable only for LPDDR4.
// bit 12.   1: dbi read inversion.   0:  dbi read high inversion.
// bit 11.   1: dbi read enable. 0:  dbi not enabled.
// bit 10    1: enable staggered chip select for 2 ranks DRAM.
// bit 9     1: enable send auto refresh command to DDR SDRAM when PCTL is in CFG/STOP state.
// bit 8     send auto refr cmd before enter register triggered  self refresh
// bit 7     send auto refr cmd after exit register triggered self refresh mode.
// bit 6     disable dram clock after enter register triggered self refresh.
// bit 5     send DFI_LP_REQ to PHY after enter register triggered elf refresh mode.
// bit 4     send DRAM to power down mode after enter self refresh. ONLY for LPDDR4.
// bit 3     send DFI_CTRLUPD_REQ after exit register triggered self refresh.
// bit 2     send ZQCS command after exit register triggered self refresh.
// bit 1     enable PHY triggered DFI_PHYUPD_REQ.
// bit 0     2T mode. always 1 in DDR3/4 mode.
#define DMC_DRAM_ZQ_CTRL ((0x0087 << 2) + 0xfe036400)
// bit 2  ZQ command must be send in different time.
// bit 1  ZQ command can be send at same time.
// bit 0  rank0 ZQ only
#define DMC_DRAM_MCFG1 ((0x0088 << 2) + 0xfe036400)
// bit7:0 LPDDR4 WDBI mode maskwrite dbi pattern
#define DMC_DRAM_DFI_CTRL ((0x0089 << 2) + 0xfe036400)
// bit 31 siu_dfi_lat err generation enable.  1: if dfi read latency violation, generate data
// error. 0 : disable. bit 20 phy_ctrl_rd_on phy_ctrl_wr_on ignore 16bit mode.  1: sending 0xf in
// 16bit mode.  0: sending valid byte enable in 16bit mode bit 19: dfi_init_complete wait enable.
// 1: after dfi_init_complete, wait additional EXSR time for new command. 0: phy will handle all
// the timing    after dfi_init_complete DMC can do everything they want. bit 18:  dfi_rddata_cs_n
// polariy.  0:  rank0 select = 2'b10. rank1 select = 2'b10. 1: rank0 select = 2'b01, rank1_select
// = 2'b10. bit 17:  dfi_wrdata_cs_n polariy.  0:  rank0 select = 2'b10. rank1 select = 2'b10. 1:
// rank0 select = 2'b01, rank1_select = 2'b10. bit 16:  force PHY ctrl_on  if = 1, phy_ctrl_on
// signal will keep on. bit 15 siu_dfi1_lp_en bit 14 siu_dfi_lp_ack_and bit 13 siu_dfi_lp_ack_or
// bit 12 siu_dfi1_init_start_en
// bit 11 siu_dfi_init_com_and
// bit 10 siu_dfi_init_com_or
// bit  9 siu_dfi1_freq_en
// bit  8 siu_dfi1_dram_clk_dis_en
// bit  7 siu_dfi_phyupd_type_sel
// bit  6 siu_dfi1_phyupd_ack_en
// bit  5 siu_dfi_phyupd_req_and
// bit  4 siu_dfi_phyupd_req_or
// bit  3 siu_dfi_ctrlupd_ack_and
// bit  2 siu_dfi_ctrlupd_ack_or
// bit  1 siu_dfi1_ctrlupd_req_en
// bit  0 siu_dfi1_cmd_en
#define DMC_DRAM_DFIINITCFG ((0x008a << 2) + 0xfe036400)
// bit 31.   dfi_init_complete status. read only.
// bit 15:14.  Frequency set 1 dfi_freq_ratio value.
// bit 12:8    Frequency set 1 dfi_freq value.
// bit 7:6     Frequency set 0 dfi_freq_ratio value.
// bit 5:1     Frequency set 0 dfi_freq value.
// bit 0.      dfi_init_start value  can be use manually config dfi_init_start signal.
#define DMC_DRAM_APD_CTRL ((0x008c << 2) + 0xfe036400)
// bit 19:16  DFI_LP_WAKEUP value in APD DFI_LP_REQ mode
// bit 12    1: exit power down slow mode(waiting PLL LOCK).  0 : fast mode.
// bit 11    enable DFI_LP_REQ when enter Auto power down mode.
// bit 10    disable DFI_clk_disable when enter auto power down mode.
// bit 9:0    0  disable auto power down mode.
// non zero value to enable auto power down when DMC is in idle state for this number of clock
// cycles.
#define DMC_DRAM_ASR_CTRL ((0x008d << 2) + 0xfe036400)
// bit 31. enable RETRAIN PHY after auto selfrefresh exit. for AM_PHY only.
// bit 30. in DDR3/4 mode, send ZQCL command after exit from auto self refresh mode.
// bit 29. enable PHY clock in LP2 mode.  1: enable. 0 : disable.
// bit 28. enable dmc wait 10us after LP2 mode exit if it's long time the PHY in LP2 mode..
// bit [27:24] DFI_LP_WAKEUP value in self refresh DFI_LP_REQ mode.
// bit 23 : send REFRESH command after exit from auto self refersh mode(ASR).
// bit 22 : send REFERSH command before enter to Auto self refresh mode(ASR).
// bit 21 : send ZQCS command after exit from Auto self refresh mode(ASR).
// bit 20 : send dfi_ctrl_upd after exit from ASR mode
// bit 19 : send power down command when enter ASR mode. //for LPDDR4 only.
// bit 18 : set the PHY enter LP2 mode after enter ASR mode.
// bit 17 : send DFI_LP_REQ  after enter ASR mode.
// bit 16 : set DFI_CLK_DISABLE after enter ASR mode.
// bit 15:0.   0 disable auto ASR mode.
// Non-zero valule enable ASR mode. when DMC is in idle state for this number of clock cycles, the
// DMC will enter ASR mode.
#define DMC_DRAM_REFR_CTRL ((0x0092 << 2) + 0xfe036400)
// bit 22  dmc to control DFI_CTRLUPD_REQ  with zq generation together.
// bit 21  dmc to control PHY ZQ generation enable.
// bit 20  dmc to control zqlat(in LPDDR4 mode) generation enable.
// bit 19  dmc to control zqcs1 generation enable.
// bit 18  dmc to control zqcs0 generation enable.
// bit 17:8 auto refresh request pending cnt if there's page hit request.
// bit 7  retrain enable for auto refresh requent. 1: enable. 0: disable.
// bit 6  Disabled auto refresh command if over 16 auto refresh command sent in 2 TREFI_DDR3
// period bit 5  enable dmc send ZQCS command . bit 4. enable dmc send DFI_CTRUPD_REQ. bit 3:1. how
// many refresh command send for one period. = this number + 1 bit 0.  enable dmc send auto refresh
// command.
#define DMC_DRAM_FREQ_CTRL ((0x0093 << 2) + 0xfe036400)
// bit 31 .  write 1 to change freqency   read 0: finished.
// bit 30.   waiting for software to send some manual command.  1 : waiting. 0 : not ready yet.
// bit 29:23.  not used.
// bit 22.   after freqchenge send refresh command.
// bit 21     after Freqchange send PHY ZQ update.
// bit 20    send CTRLUPD_REQ to PHY after freq_change finished.
// bit 19:16. how many cycles to send PLL change req after init_complete signal to low.
// bit 15.   freq pre  config_en. Before freq enter stop state let DMC configure DDR SDRAM.
// bit 14.   freq post config_en. After  freq enter stop state let DMC configure DDR SDRAM.
// bit 13.   send zqcl after freq change in DDR3/4 mode.
// bit 12.   send zqcs after freq change. 1: enable. 0 not send.
// bit 11.   in AUTO MRW funcntion: the data format.  1: use USR_CMD format.  0: MRW format.
// bit 10.   AUTO MRW function:  1 use hardware auto MRW function.  0: don't do auto MRW.
// bit 9.  1 : FREQ MRW done. let FREQ change machine continue.
// bit 8   FREQ WAIT. 1 when freq change finishes, state machine stop at self refresh state in
// case there's something need to handle.
//     0 after freq change finishes  the state machine go back to access state.
// bit 7   when change PLL setting, disable dmc clock
// bit 6   when change PLL setting, disable PHY DfiClk and DfiCtlClk.
// bit 5   check vpu_sleep_en ==1 when do FREQ change.  if vpu_sleep_en == 0, just wait.
// bit 4   nxt frequency selection.  1 = freq1. 0 = freq0.
// bit 3:1.  not used.
// bit 0.   current frequency selection.
#define DMC_DRAM_SCFG ((0x0094 << 2) + 0xfe036400)
// bit 2:0 only one bit can be high at same time.
// bit 2  1 : to ask PCTL enter ACCESS STATE.  0 : deassert the request.
// bit 1  1 : to ask PCTL enter SELF REFRESH STATE.  0 : deassert the request.
// bit 0  1 : to ask PCTL enter STOP/CONFIG STATE .  0 : deassert the request.
#define DMC_DRAM_STAT ((0x0095 << 2) + 0xfe036400)
// bit 31     rd latency error. 1: means after dfiphytrdlat cycles, the read data still not back.
// bit 28:24   dram_sr_state
// bit 23:20   stop_st
// bit 19:15   sleep_st
// bit 14:12  ACCESS STATUS 0 :  ACCESS is in normal working mode.
// 1 :   ACCESS sending precharege command.
// 2 :   ACCESS sending AUTO REFESH command.
// 3 :   ACCESS sending DIF_CTRLUPD_REQ command.
// 4 :   ACCESS sending ZQCS command to DDR DRAM(ZQCAL for LPDDR4).
// 5 :   ACCESS sending ZQLATCH command to  LPDDR4 only.
// bit 11:8   APD STATUS:   0 :   APD_IDLE
// 1 :    APD sending PRECHARGE command
// 2 :    APD sending CKE low command
// 3 :    APD sending DISABLE DRAM CLOCK command
// 4 :    APD sending DFI_LP_CTRL_REQ
// 5 :    APD in Auto Power down mode.
// 6 :    APD deassert DFI_LP_CTRL_REQ
// 7 :    APD sending enable DRAM CLOCK command
// 8 :    APD sending out CKE high command.
// bit 7:4: DRAM_STATUS:  0  :    DRAM IDLE
// 1  :    DRAM_STOP/DRAM_CFG
// 2  :    DRAM_ACCESS
// 3  :    DRAM_SLEEP
// 4  :    DRAM APD(AUTO POWER DOWN).
// 5  :    IDLE -> STOP/CONFIG
// 6  :    STOP -> SLEEP
// 7  :    STOP -> ACCESS
// 8  :    ACCESS -> SLEEP.
// 9  :    ACCESS -> STOP
// A  :    ACCESS -> APD
// B  :    SLEEP -> STOP
// C  :    SLEEP -> ACCESS
// D  :    APD -> ACCESS
// bit 3        reserved.
// bit 2        1 : DRAM enter normal working state.
// bit 1        1 : DRAM enter sleep state. self refresh state.
// bit 0        1 : dram enter cfg state.
#define DMC_DRAM_STAT1 ((0x0096 << 2) + 0xfe036400)
// bit 11:8  freq_st.
// 4'h0 : IDLE
// 4'h1 : FREQ_CHECK_VPU
// 4'h2 : FREQ_WAITING_STOP
// 4'h3 : FREQ_DRAM_CFG.  waiting DMC/software to send special MRW/MPC command to configure DDR
// SDRAM either before Freq change or after freq change. 4'h4 : FREQ_SELF_REFR_ST. 4'h5 :
// FREQ_SET_DFI_FREQ. 4'h6 : FREQ_DFI_INIT_START_HIGH. 4'h7 : FREQ_CHANGE PLL_ST. 4'h8 :
// FREQ_UPDATA REG. 4'h9 : FREQ_DFI_INIT_START_LOW. 4'ha : FREQ_WAITING_FINISH 4'hb : FREQ_ZQCS
// 4'hc : FREQ_ZQ_LATCH
// 4'hd : FREQ_PVT
// bit 7:5   train_st
// bit 4:0   dram_phy_st
#define DMC_PHY_RETRAINING_CTRL ((0x0097 << 2) + 0xfe036400)
// bit 31 :  phy_retraining enable.
// bit 30 :  check  vpu sleep_en.
// bit 25:24 : retraining dfi_freq[4:3], the [2:0] bit still use the dfi_freq bits to keep the
// frequency. bit 23:0: retraining period unit : 100ns.
#define DMC_DFI_ERR_STAT ((0x0098 << 2) + 0xfe036400)
// LPDDR4 PHY DFI error information.
// bit 31:20. not used.
// bit 9.    ddr0_dfi_error
// bit 8:5   ddr0_dfi_error_info.
// bit 4.    ddr1_dfi_error.
// bit 3:0.  ddr1_dfi_error_info.
#define DMC_LP2_TIMER ((0x009a << 2) + 0xfe036400)
// bit 15:0.   timer setting to measure how long the chip is entered LP2 mode.
// this timer is 40bits counter with DMC PCLK.
// we use the high 16bits to compare this register. if the counter is large than this number, that
// means  the PHY need addition 10us after wakeup the PHY and before exit self_refresh mode.
#define DMC_DRAM_COMPLETE_WAIT ((0x009b << 2) + 0xfe036400)
// read only how long to waiting for DFI_INIT_COMPLETE become high after DFI_INIT_START triggered.
#define DMC_DRAM_DFI_SWAP_0 ((0x00a0 << 2) + 0xfe036400)
// bit 5:0. dfi_act_n function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define DMC_DRAM_DFI_SWAP_1 ((0x00a1 << 2) + 0xfe036400)
// bit 5:0. dfi_ras_n function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define DMC_DRAM_DFI_SWAP_2 ((0x00a2 << 2) + 0xfe036400)
// bit 5:0. dfi_cas_n function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define DMC_DRAM_DFI_SWAP_3 ((0x00a3 << 2) + 0xfe036400)
// bit 5:0. dfi_we_n function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define DMC_DRAM_DFI_SWAP_4 ((0x00a4 << 2) + 0xfe036400)
// bit 5:0. dfi_bg0 function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define DMC_DRAM_DFI_SWAP_5 ((0x00a5 << 2) + 0xfe036400)
// bit 5:0. dfi_bg[1] function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define DMC_DRAM_DFI_SWAP_6 ((0x00a6 << 2) + 0xfe036400)
// bit 5:0. dfi_ba[0] function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define DMC_DRAM_DFI_SWAP_7 ((0x00a7 << 2) + 0xfe036400)
// bit 5:0. dfi_ba[1] function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define DMC_DRAM_DFI_SWAP_8 ((0x00a8 << 2) + 0xfe036400)
// bit 5:0. dfi_ba[2] function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define DMC_DRAM_DFI_SWAP_9 ((0x00a9 << 2) + 0xfe036400)
// bit 5:0. dfi_a[0] function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define DMC_DRAM_DFI_SWAP_10 ((0x00aa << 2) + 0xfe036400)
// bit 5:0. dfi_a[1] function select
#define DMC_DRAM_DFI_SWAP_11 ((0x00ab << 2) + 0xfe036400)
// bit 5:0. dfi_a[2] function select
#define DMC_DRAM_DFI_SWAP_12 ((0x00ac << 2) + 0xfe036400)
// bit 5:0. dfi_a[3] function select
#define DMC_DRAM_DFI_SWAP_13 ((0x00ad << 2) + 0xfe036400)
// bit 5:0. dfi_a[4] function select
#define DMC_DRAM_DFI_SWAP_14 ((0x00ae << 2) + 0xfe036400)
// bit 5:0. dfi_a[5] function select
#define DMC_DRAM_DFI_SWAP_15 ((0x00af << 2) + 0xfe036400)
// bit 5:0. dfi_a[6] function select
#define DMC_DRAM_DFI_SWAP_16 ((0x00b0 << 2) + 0xfe036400)
// bit 5:0. dfi_a[7] function select
#define DMC_DRAM_DFI_SWAP_17 ((0x00b1 << 2) + 0xfe036400)
// bit 5:0. dfi_a[8] function select
#define DMC_DRAM_DFI_SWAP_18 ((0x00b2 << 2) + 0xfe036400)
// bit 5:0. dfi_a[9] function select
#define DMC_DRAM_DFI_SWAP_19 ((0x00b3 << 2) + 0xfe036400)
// bit 5:0. dfi_a[10] function select
#define DMC_DRAM_DFI_SWAP_20 ((0x00b4 << 2) + 0xfe036400)
// bit 5:0. dfi_a[11] function select
#define DMC_DRAM_DFI_SWAP_21 ((0x00b5 << 2) + 0xfe036400)
// bit 5:0. dfi_a[12] function select
#define DMC_DRAM_DFI_SWAP_22 ((0x00b6 << 2) + 0xfe036400)
// bit 5:0. dfi_a[13] function select
#define DMC_DRAM_DFI_SWAP_23 ((0x00b7 << 2) + 0xfe036400)
// bit 5:0. dfi_a[14] function select
#define DMC_DRAM_DFI_SWAP_24 ((0x00b8 << 2) + 0xfe036400)
// bit 5:0. dfi_a[15] function select
#define DMC_DRAM_DFI_SWAP_25 ((0x00b9 << 2) + 0xfe036400)
// bit 5:0. dfi_a[16] function select
#define DMC_DRAM_DFI_SWAP_26 ((0x00ba << 2) + 0xfe036400)
// bit 5:0. dfi_a[17] function select
#define DMC_DRAM_CMD ((0x00d0 << 2) + 0xfe036400)
// bit 31. cmd done.  write 0 to clean.
// bit 30. data done. write 0 to clean.
// bit 8.  1: MPC/MRR command is in a 16bits width SDRAM. 0 : normal operation.
// bit 5.  user defined command.
// bit 4.  LPDDR4 MPC write data command( MPC WR FIFO).
// bit 3.  LPDDR4 MPC read data command (MPC RD Calibration and RD FIFO).
// bit 2.  LPDDR4 MPC-1 command ( NOP,  Start DQS interval ....)
// bit 1.  mrr command.
// bit 0.  mrw command.
#define DMC_DRAM_CMD_CODE ((0x00d1 << 2) + 0xfe036400)
// bit 31:28  user command case: = {act_n, ras_n, cas_n, we_n}
// bit 27:26. 128bits data cycles . 0: 1 clock cycles;  1: 2  clock cycles; 2: 3 clock cycles; 3:4
// clock cycles.
//           LPDDR4 : 4 clock cycles;
//           DDR3/4/LPDDR3  : 2 clock cycles.
// bit 25     MRW/MRR/MPC command rank 1 select.  1: select.  0: not select.
// bit 24.    MRW/MRR/MPC command rank 0 select.  1: select.  0: not select.
// bit 23:16  MR addr.  DDR4 case :  18:16 ba[2:0].    20:19 BG[1:0].
// bit 15:0   opcode.
#define DMC_DRAM_CMD_TIME ((0x00d2 << 2) + 0xfe036400)
// bit 31:16  PRE  CMD timer. //delay how many cycle to start the command.
// bit 15:0   POST CMD timer  //delay how many cycle after the command execute.
#define DMC_DRAM_WSTRB0 ((0x00d3 << 2) + 0xfe036400)
#define DMC_DRAM_WSTRB1 ((0x00d4 << 2) + 0xfe036400)
#define DMC_DRAM_RDBI0 ((0x00d5 << 2) + 0xfe036400)
// MPC RD FIFO command DBI read back data
// bit 31:16  the second cycle.
// bit 15:0   the first cycle.
#define DMC_DRAM_RDBI1 ((0x00d6 << 2) + 0xfe036400)
// MPC RD FIFO command DBI read back data
// bit 31:16. the Forth cycle.
// bit 15:0.  the third cycle.
// WD0~16 and RD0~16 can be used as MRW command as Frequency change .
// WD0~16 is for Freq1 DRAM MR setting, it would send to DRAM right before FREQ0-> FREQ1
// RD0_16 is for Freq0 DRAM MR setting. it would send to DRAM right before FREQ1-> FREQ0.
// each register can be one MRW command. So total 16 MRW command can be sent to DRAM.
// The register formats:
// bit 31.   MRW/USER command enable.  1: enabled command. 0 not enabled.
// bit 30.   last MRW/USER command.   if this bit =1, After send this command, the DRAM controller
// will contine frequency next stage. bit 29:26. USER COMMAND parameter: in DDR3/DDR4.  {act_n,
// ras_n, cas_n, we_n} value for user command in LPDDR4.  bit 16: 1 4 cycles command.  0 2 cycles
// command. bit 25     MRW/USER command rank 1 select.  1: select.  0: not select. bit 24. MRW/USER
// command rank 0 select.  1: select.  0: not select. bit 23:0.  USER command. DDR3:    18:16 bank
// address. 15:0:  address. DDR4:    20:19 bank group address.   18:16: bank address. 15:0 address.
// LPDDR3:   9:0. rising edge address.  19:10.  falling edge address.
// LPDDR4.   5:0, first edge address,  11:6 second edge address, 17:12: third edge address. 23:18,
// forth edge address. MRW command format: bit 23:16  MR addr.  DDR4 case :  18:16 ba[2:0]. 20:19
// BG[1:0]. bit 15:0   opcode.
#define DMC_DRAM_WD0 ((0x00e0 << 2) + 0xfe036400)
#define DMC_DRAM_WD1 ((0x00e1 << 2) + 0xfe036400)
#define DMC_DRAM_WD2 ((0x00e2 << 2) + 0xfe036400)
#define DMC_DRAM_WD3 ((0x00e3 << 2) + 0xfe036400)
#define DMC_DRAM_WD4 ((0x00e4 << 2) + 0xfe036400)
#define DMC_DRAM_WD5 ((0x00e5 << 2) + 0xfe036400)
#define DMC_DRAM_WD6 ((0x00e6 << 2) + 0xfe036400)
#define DMC_DRAM_WD7 ((0x00e7 << 2) + 0xfe036400)
#define DMC_DRAM_WD8 ((0x00e8 << 2) + 0xfe036400)
#define DMC_DRAM_WD9 ((0x00e9 << 2) + 0xfe036400)
#define DMC_DRAM_WD10 ((0x00ea << 2) + 0xfe036400)
#define DMC_DRAM_WD11 ((0x00eb << 2) + 0xfe036400)
#define DMC_DRAM_WD12 ((0x00ec << 2) + 0xfe036400)
#define DMC_DRAM_WD13 ((0x00ed << 2) + 0xfe036400)
#define DMC_DRAM_WD14 ((0x00ee << 2) + 0xfe036400)
#define DMC_DRAM_WD15 ((0x00ef << 2) + 0xfe036400)
#define DMC_DRAM_RD0 ((0x00f0 << 2) + 0xfe036400)
#define DMC_DRAM_RD1 ((0x00f1 << 2) + 0xfe036400)
#define DMC_DRAM_RD2 ((0x00f2 << 2) + 0xfe036400)
#define DMC_DRAM_RD3 ((0x00f3 << 2) + 0xfe036400)
#define DMC_DRAM_RD4 ((0x00f4 << 2) + 0xfe036400)
#define DMC_DRAM_RD5 ((0x00f5 << 2) + 0xfe036400)
#define DMC_DRAM_RD6 ((0x00f6 << 2) + 0xfe036400)
#define DMC_DRAM_RD7 ((0x00f7 << 2) + 0xfe036400)
#define DMC_DRAM_RD8 ((0x00f8 << 2) + 0xfe036400)
#define DMC_DRAM_RD9 ((0x00f9 << 2) + 0xfe036400)
#define DMC_DRAM_RD10 ((0x00fa << 2) + 0xfe036400)
#define DMC_DRAM_RD11 ((0x00fb << 2) + 0xfe036400)
#define DMC_DRAM_RD12 ((0x00fc << 2) + 0xfe036400)
#define DMC_DRAM_RD13 ((0x00fd << 2) + 0xfe036400)
#define DMC_DRAM_RD14 ((0x00fe << 2) + 0xfe036400)
#define DMC_DRAM_RD15 ((0x00ff << 2) + 0xfe036400)
//`define DMC_STICKY_REG_BASE   32'hfe036800
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe036800
// -----------------------------------------------
// those register is for software save some tempary value. and because it's in RAM. it won't lose
// if DMC get reseted.
#define DMC_STICKY_0 ((0x0000 << 2) + 0xfe036800)
#define DMC_STICKY_1 ((0x0001 << 2) + 0xfe036800)
#define DMC_STICKY_2 ((0x0002 << 2) + 0xfe036800)
#define DMC_STICKY_3 ((0x0003 << 2) + 0xfe036800)
#define DMC_STICKY_4 ((0x0004 << 2) + 0xfe036800)
#define DMC_STICKY_5 ((0x0005 << 2) + 0xfe036800)
#define DMC_STICKY_6 ((0x0006 << 2) + 0xfe036800)
#define DMC_STICKY_7 ((0x0007 << 2) + 0xfe036800)
#define DMC_STICKY_8 ((0x0008 << 2) + 0xfe036800)
#define DMC_STICKY_9 ((0x0009 << 2) + 0xfe036800)
#define DMC_STICKY_10 ((0x000a << 2) + 0xfe036800)
#define DMC_STICKY_11 ((0x000b << 2) + 0xfe036800)
#define DMC_STICKY_12 ((0x000c << 2) + 0xfe036800)
#define DMC_STICKY_13 ((0x000d << 2) + 0xfe036800)
#define DMC_STICKY_14 ((0x000e << 2) + 0xfe036800)
#define DMC_STICKY_15 ((0x000f << 2) + 0xfe036800)
#define DMC_STICKY_16 ((0x0010 << 2) + 0xfe036800)
#define DMC_STICKY_17 ((0x0011 << 2) + 0xfe036800)
#define DMC_STICKY_18 ((0x0012 << 2) + 0xfe036800)
#define DMC_STICKY_19 ((0x0013 << 2) + 0xfe036800)
#define DMC_STICKY_20 ((0x0014 << 2) + 0xfe036800)
#define DMC_STICKY_21 ((0x0015 << 2) + 0xfe036800)
#define DMC_STICKY_22 ((0x0016 << 2) + 0xfe036800)
#define DMC_STICKY_23 ((0x0017 << 2) + 0xfe036800)
#define DMC_STICKY_24 ((0x0018 << 2) + 0xfe036800)
#define DMC_STICKY_25 ((0x0019 << 2) + 0xfe036800)
#define DMC_STICKY_26 ((0x001a << 2) + 0xfe036800)
#define DMC_STICKY_27 ((0x001b << 2) + 0xfe036800)
#define DMC_STICKY_28 ((0x001c << 2) + 0xfe036800)
#define DMC_STICKY_29 ((0x001d << 2) + 0xfe036800)
#define DMC_STICKY_30 ((0x001e << 2) + 0xfe036800)
#define DMC_STICKY_31 ((0x001f << 2) + 0xfe036800)
#define DMC_STICKY_32 ((0x0020 << 2) + 0xfe036800)
#define DMC_STICKY_33 ((0x0021 << 2) + 0xfe036800)
#define DMC_STICKY_34 ((0x0022 << 2) + 0xfe036800)
#define DMC_STICKY_35 ((0x0023 << 2) + 0xfe036800)
#define DMC_STICKY_36 ((0x0024 << 2) + 0xfe036800)
#define DMC_STICKY_37 ((0x0025 << 2) + 0xfe036800)
#define DMC_STICKY_38 ((0x0026 << 2) + 0xfe036800)
#define DMC_STICKY_39 ((0x0027 << 2) + 0xfe036800)
#define DMC_STICKY_40 ((0x0028 << 2) + 0xfe036800)
#define DMC_STICKY_41 ((0x0029 << 2) + 0xfe036800)
#define DMC_STICKY_42 ((0x002a << 2) + 0xfe036800)
#define DMC_STICKY_43 ((0x002b << 2) + 0xfe036800)
#define DMC_STICKY_44 ((0x002c << 2) + 0xfe036800)
#define DMC_STICKY_45 ((0x002d << 2) + 0xfe036800)
#define DMC_STICKY_46 ((0x002e << 2) + 0xfe036800)
#define DMC_STICKY_47 ((0x002f << 2) + 0xfe036800)
#define DMC_STICKY_48 ((0x0030 << 2) + 0xfe036800)
#define DMC_STICKY_49 ((0x0031 << 2) + 0xfe036800)
#define DMC_STICKY_50 ((0x0032 << 2) + 0xfe036800)
#define DMC_STICKY_51 ((0x0033 << 2) + 0xfe036800)
#define DMC_STICKY_52 ((0x0034 << 2) + 0xfe036800)
#define DMC_STICKY_53 ((0x0035 << 2) + 0xfe036800)
#define DMC_STICKY_54 ((0x0036 << 2) + 0xfe036800)
#define DMC_STICKY_55 ((0x0037 << 2) + 0xfe036800)
#define DMC_STICKY_56 ((0x0038 << 2) + 0xfe036800)
#define DMC_STICKY_57 ((0x0039 << 2) + 0xfe036800)
#define DMC_STICKY_58 ((0x003a << 2) + 0xfe036800)
#define DMC_STICKY_59 ((0x003b << 2) + 0xfe036800)
#define DMC_STICKY_60 ((0x003c << 2) + 0xfe036800)
#define DMC_STICKY_61 ((0x003d << 2) + 0xfe036800)
#define DMC_STICKY_62 ((0x003e << 2) + 0xfe036800)
#define DMC_STICKY_63 ((0x003f << 2) + 0xfe036800)
//`define DMC_SEC_REG_BASE                32'hfe037000
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe037000
// -----------------------------------------------
// DMC use 15bits ID to identify the input ports and ID.
// bit 14:10.
// AXI bus ID number from 0 ~15.  2, 8~10, 12~15 Not used the others defined as bellow.
// 0 : CPU and MALI.   Mali and cpu will be separated to 2 channel. CPU traffic will be assigned
// to ID = 0. Mali traffic will assigned to ID =1. 1 : Mali 3 : HDMI. 4 : HEVC.   //HEVC_F/B
// combined to one 5 : TEST. 6 : USB 7 : Device.
// 11 : DEMUX
// 16: VPU read 0.
// 17: VPU read 1.
// 18: VPU read 2.
// 19: VPU write 0.
// 20: VPU write 1.
// 21: VDEC.
// 22: HCODEC.
// 23: ge2d.
// control bit for  SubID functions for all the input.
// ARM   2 bit.    HPROT[1] == 0 : SECURE CPU;   HPROT[1] == 1 : NONSEC CPU.
// GPU   2 bit.    HPROT[2] == 1 : SECURE GPU;   HPROT[2] == 0 : NONSEC GPU access;
// HDCP  4 bits.   ID AR/AWID[1:0].
// HEVC  9 bits.   HEVC use ARUSER/AWUSER[3:0] 16 levels of security control.
// TEST  1 type.
// USB   1 type.
// DEVICE  DMA    : AR/AWID[7:3] == 4'h2.  8bits control   use AR/WID[3:1].
//         AUDIO  : AR/AWID[7:3] == 4'h6.  8bits control.  use AR/AWID[2:0].
//         the others total 16 bits use AR/AWID[7:3].  bit 2 and bit 6 not used.
// VPU the 5 VPU ports use ARSEC/AWSEC as the secruity control.
// VDEC  total 16bits.  use AR/WID[5:2]
// GE2D. total 3bits.  2 read bits, check ARID[0].  1 write bit.   AWID dont care.
// there's total 16 ranges in the whole memory range.
// 15 ranges can be defined in 64kbyte boundary start address and end address.
// the 16th range is all other space not defined by 15 ranges.
// Each range can be enabled or disabled and  each range use security level bit to select key to
// do data scramble. The ranges can be overlapped or crossover.  But from 0 to 15 ranges, the
// earlier has higher priority.
#define DMC_SEC_RANGE0_CTRL ((0x0000 << 2) + 0xfe037000)
// bit 31:16   | 0 | range0_eda | range 0 end address  higher 16bits.
// bit 15:0    | 0 | range0_sta | range 0 start address higher 16bits.
#define DMC_SEC_RANGE0_CTRL1 ((0x0001 << 2) + 0xfe037000)
// bit 7:5 | 0 | range0_secrity_level | range0 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range0_prot_en       | range0 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range0_local_des_en  | range0 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES_EN to decide this region data describle enable
// or not. bit 2  | 0 | range0_lock  |  lock range 0 registers. write 1 to lock range 0 register.
// can't change anymore. bit 1  | 0 | range0_key_sel | range 0 data describle key selection.  1 :
// key1. 0 : key0. bit 0  | 0 | range0_en    | range 0 enable bit. 1 : enable, 0 : disable.
#define DMC_SEC_RANGE1_CTRL ((0x0002 << 2) + 0xfe037000)
// bit 31:16   | 0 | range1_eda | range 1 end address  higher 16bits.
// bit 15:0    | 0 | range1_sta | range 1 start address higher 16bits.
#define DMC_SEC_RANGE1_CTRL1 ((0x0003 << 2) + 0xfe037000)
// bit 7:5 | 0 | range1_secrity_level | range1 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range1_prot_en       | range1 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range1_local_des_en  | range1 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES_EN to decide this region data describle enable
// or not. bit 2  | 0 | range1_lock  |  lock range 1 registers. write 1 to lock range 1 register.
// can't change anymore. bit 1  | 0 | range1_key_sel | range 1 data describle key selection.  1 :
// key1. 1 : key0. bit 0  | 0 | range1_en    | range 0 enable bit. 1 : enable, 0 : disable.
#define DMC_SEC_RANGE2_CTRL ((0x0004 << 2) + 0xfe037000)
// bit 31:16   | 0 | range2_eda | range 2 end address  higher 16bits.
// bit 15:0    | 0 | range2_sta | range 2 start address higher 16bits.
#define DMC_SEC_RANGE2_CTRL1 ((0x0005 << 2) + 0xfe037000)
// bit 7:5 | 0 | range2_secrity_level | range2 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range2_prot_en       | range2 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range2_local_des_en  | range2 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES to decide this region data describle enable or
// not. bit 2  | 0 | range2_lock  |  lock range 2 registers. write 1 to lock range 2 register.
// can't change anymore. bit 1  | 0 | range2_key_sel | range 2 data describle key selection.  1 :
// key1. 1 : key0. bit 0  | 0 | range2_en    | range 2 enable bit. 1 : enable, 0 : disable.
#define DMC_SEC_RANGE3_CTRL ((0x0006 << 2) + 0xfe037000)
// bit 31:16   | 0 | range3_eda | range 3 end address  higher 16bits.
// bit 15:0    | 0 | range3_sta | range 3 start address higher 16bits.
#define DMC_SEC_RANGE3_CTRL1 ((0x0007 << 2) + 0xfe037000)
// bit 7:5 | 0 | range3_secrity_level | range3 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range3_prot_en       | range3 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range3_local_des_en  | range3 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES to decide this region data describle enable or
// not. bit 2  | 0 | range3_lock    | lock range 3 registers. write 1 to lock range 3 related
// registers. can't change anymore. bit 1  | 0 | range3_key_sel | range 3 data describle key
// selection.  1 : key1. 1 : key0. bit 0  | 0 | range3_en      | range 3 enable bit. 1 : enable, 0
// : disable.
#define DMC_SEC_RANGE4_CTRL ((0x0008 << 2) + 0xfe037000)
// bit 31:16   | 0 | range4_eda | range 4 end address  higher 16bits.
// bit 15:0    | 0 | range4_sta | range 4 start address higher 16bits.
#define DMC_SEC_RANGE4_CTRL1 ((0x0009 << 2) + 0xfe037000)
// bit 7:5 | 0 | range4_secrity_level | range4 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range4_prot_en       | range4 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range4_local_des_en  | range4 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES to decide this region data describle enable or
// not. bit 2  | 0 | range4_lock    | lock range 4 registers. write 1 to lock range 4 related
// registers. can't change anymore. bit 1  | 0 | range4_key_sel | range 4 data describle key
// selection.  1 : key1. 1 : key0. bit 0  | 0 | range4_en      | range 4 enable bit. 1 : enable, 0
// : disable.
#define DMC_SEC_RANGE5_CTRL ((0x000a << 2) + 0xfe037000)
#define DMC_SEC_RANGE5_CTRL1 ((0x000b << 2) + 0xfe037000)
#define DMC_SEC_RANGE6_CTRL ((0x000c << 2) + 0xfe037000)
#define DMC_SEC_RANGE6_CTRL1 ((0x000d << 2) + 0xfe037000)
#define DMC_SEC_RANGE7_CTRL ((0x000e << 2) + 0xfe037000)
#define DMC_SEC_RANGE7_CTRL1 ((0x000f << 2) + 0xfe037000)
#define DMC_SEC_RANGE8_CTRL ((0x0010 << 2) + 0xfe037000)
#define DMC_SEC_RANGE8_CTRL1 ((0x0011 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_CTRL ((0x0012 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_CTRL1 ((0x0013 << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_CTRL ((0x0014 << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_CTRL1 ((0x0015 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_CTRL ((0x0016 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_CTRL1 ((0x0017 << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_CTRL ((0x0018 << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_CTRL1 ((0x0019 << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_CTRL ((0x001a << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_CTRL1 ((0x001b << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_CTRL ((0x001c << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_CTRL1 ((0x001d << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_CTRL1 ((0x001f << 2) + 0xfe037000)
// default : 0
// bit 7:5 | 0 | range1_secrity_level | range1 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range1_prot_en       | range1 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range1_local_des_en  | range1 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES_EN to decide this region data describle enable
// or not. bit 2  | 0 | range1_lock  |  lock range 1 registers. write 1 to lock range 1 register.
// can't change anymore. bit 1  | 0 | range1_key_sel | range 1 data describle key selection.  1 :
// key1. 1 : key0. bit 0  | 0 | not used. range 15 is always enabled. for each range there's 96bits
// read/write subid control to control all master DDR access. the 96bits assignments
// rangex_rd_sid_en[95:0] and rangx_wr_sid_en[95:0] is as below: bit 3:0. for CPU
// ARPROT[2:1]/AWPROT[2:1] selection. CPU ARPROT[2:1] /AWPROT[2:1] define: bit0 PROT[2:1]==00: data
// secure access. bit1 PROT[2:1]==01:   data non-secure access. bit2 PROT[2:1] 10:    instruction
// secure access. bit3 PROT[2:1] 11:    instruction non-secure access. per range per sub ID access
// enable.
#define DMC_SEC_RANGE0_RID_CTRL0 ((0x0020 << 2) + 0xfe037000)
// default : 0
// range0_rd_sid_en[31:0];
#define DMC_SEC_RANGE0_RID_CTRL1 ((0x0021 << 2) + 0xfe037000)
// default : 0
// range0_rd_sid_en[63:32];
#define DMC_SEC_RANGE0_RID_CTRL2 ((0x0022 << 2) + 0xfe037000)
// default : 0
// range0_rd_sid_en[95:64];
#define DMC_SEC_RANGE0_RID_CTRL3 ((0x0023 << 2) + 0xfe037000)
// default : 0
// not used.
#define DMC_SEC_RANGE0_RID_CTRL4 ((0x0024 << 2) + 0xfe037000)
// default : 0 not used in
#define DMC_SEC_RANGE1_RID_CTRL0 ((0x0026 << 2) + 0xfe037000)
// default : 0
// range1_rd_sid_en[31:0];
#define DMC_SEC_RANGE1_RID_CTRL1 ((0x0027 << 2) + 0xfe037000)
// default : 0
// range1_rd_sid_en[63:32];
#define DMC_SEC_RANGE1_RID_CTRL2 ((0x0028 << 2) + 0xfe037000)
// default : 0
// range1_rd_sid_en[95:64];
#define DMC_SEC_RANGE1_RID_CTRL3 ((0x0029 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE1_RID_CTRL4 ((0x002a << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE2_RID_CTRL0 ((0x002c << 2) + 0xfe037000)
#define DMC_SEC_RANGE2_RID_CTRL1 ((0x002d << 2) + 0xfe037000)
#define DMC_SEC_RANGE2_RID_CTRL2 ((0x002e << 2) + 0xfe037000)
#define DMC_SEC_RANGE2_RID_CTRL3 ((0x002f << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE2_RID_CTRL4 ((0x0030 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE3_RID_CTRL0 ((0x0032 << 2) + 0xfe037000)
#define DMC_SEC_RANGE3_RID_CTRL1 ((0x0033 << 2) + 0xfe037000)
#define DMC_SEC_RANGE3_RID_CTRL2 ((0x0034 << 2) + 0xfe037000)
#define DMC_SEC_RANGE3_RID_CTRL3 ((0x0035 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE3_RID_CTRL4 ((0x0036 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE4_RID_CTRL0 ((0x0038 << 2) + 0xfe037000)
#define DMC_SEC_RANGE4_RID_CTRL1 ((0x0039 << 2) + 0xfe037000)
#define DMC_SEC_RANGE4_RID_CTRL2 ((0x003a << 2) + 0xfe037000)
#define DMC_SEC_RANGE4_RID_CTRL3 ((0x003b << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE4_RID_CTRL4 ((0x003c << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE5_RID_CTRL0 ((0x003e << 2) + 0xfe037000)
#define DMC_SEC_RANGE5_RID_CTRL1 ((0x003f << 2) + 0xfe037000)
#define DMC_SEC_RANGE5_RID_CTRL2 ((0x0040 << 2) + 0xfe037000)
#define DMC_SEC_RANGE5_RID_CTRL3 ((0x0041 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE5_RID_CTRL4 ((0x0042 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE6_RID_CTRL0 ((0x0044 << 2) + 0xfe037000)
#define DMC_SEC_RANGE6_RID_CTRL1 ((0x0045 << 2) + 0xfe037000)
#define DMC_SEC_RANGE6_RID_CTRL2 ((0x0046 << 2) + 0xfe037000)
#define DMC_SEC_RANGE6_RID_CTRL3 ((0x0047 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE6_RID_CTRL4 ((0x0048 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE7_RID_CTRL0 ((0x004a << 2) + 0xfe037000)
#define DMC_SEC_RANGE7_RID_CTRL1 ((0x004b << 2) + 0xfe037000)
#define DMC_SEC_RANGE7_RID_CTRL2 ((0x004c << 2) + 0xfe037000)
#define DMC_SEC_RANGE7_RID_CTRL3 ((0x004d << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE7_RID_CTRL4 ((0x004e << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE8_RID_CTRL0 ((0x0050 << 2) + 0xfe037000)
#define DMC_SEC_RANGE8_RID_CTRL1 ((0x0051 << 2) + 0xfe037000)
#define DMC_SEC_RANGE8_RID_CTRL2 ((0x0052 << 2) + 0xfe037000)
#define DMC_SEC_RANGE8_RID_CTRL3 ((0x0053 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE8_RID_CTRL4 ((0x0054 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE9_RID_CTRL0 ((0x0056 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_RID_CTRL1 ((0x0057 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_RID_CTRL2 ((0x0058 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_RID_CTRL3 ((0x0059 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_RID_CTRL4 ((0x005a << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_RID_CTRL0 ((0x005c << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_RID_CTRL1 ((0x005d << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_RID_CTRL2 ((0x005e << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_RID_CTRL3 ((0x005f << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_RID_CTRL4 ((0x0060 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_RID_CTRL0 ((0x0062 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_RID_CTRL1 ((0x0063 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_RID_CTRL2 ((0x0064 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_RID_CTRL3 ((0x0065 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_RID_CTRL4 ((0x0066 << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_RID_CTRL0 ((0x0068 << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_RID_CTRL1 ((0x0069 << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_RID_CTRL2 ((0x006a << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_RID_CTRL3 ((0x006b << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_RID_CTRL4 ((0x006c << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_RID_CTRL0 ((0x006e << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_RID_CTRL1 ((0x006f << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_RID_CTRL2 ((0x0070 << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_RID_CTRL3 ((0x0071 << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_RID_CTRL4 ((0x0072 << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_RID_CTRL0 ((0x0074 << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_RID_CTRL1 ((0x0075 << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_RID_CTRL2 ((0x0076 << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_RID_CTRL3 ((0x0077 << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_RID_CTRL4 ((0x0078 << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_RID_CTRL0 ((0x007a << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_RID_CTRL1 ((0x007b << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_RID_CTRL2 ((0x007c << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_RID_CTRL3 ((0x007d << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_RID_CTRL4 ((0x007e << 2) + 0xfe037000)
// per range per sub ID access enable.
#define DMC_SEC_RANGE0_WID_CTRL0 ((0x0080 << 2) + 0xfe037000)
// default : 0
// range0_wr_sid_en[31:0];
#define DMC_SEC_RANGE0_WID_CTRL1 ((0x0081 << 2) + 0xfe037000)
// default : 0
// range0_wr_sid_en[63:32];
#define DMC_SEC_RANGE0_WID_CTRL2 ((0x0082 << 2) + 0xfe037000)
// default : 0
// range0_wr_sid_en[95:64];
#define DMC_SEC_RANGE0_WID_CTRL3 ((0x0083 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE0_WID_CTRL4 ((0x0084 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE1_WID_CTRL0 ((0x0086 << 2) + 0xfe037000)
// default : 0
// range1_wr_sid_en[31:0];
#define DMC_SEC_RANGE1_WID_CTRL1 ((0x0087 << 2) + 0xfe037000)
// default : 0
// range1_wr_sid_en[63:32];
#define DMC_SEC_RANGE1_WID_CTRL2 ((0x0088 << 2) + 0xfe037000)
// default : 0
// range1_wr_sid_en[95:64];
#define DMC_SEC_RANGE1_WID_CTRL3 ((0x0089 << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE1_WID_CTRL4 ((0x008a << 2) + 0xfe037000)
// not used.
#define DMC_SEC_RANGE2_WID_CTRL0 ((0x008c << 2) + 0xfe037000)
#define DMC_SEC_RANGE2_WID_CTRL1 ((0x008d << 2) + 0xfe037000)
#define DMC_SEC_RANGE2_WID_CTRL2 ((0x008e << 2) + 0xfe037000)
#define DMC_SEC_RANGE2_WID_CTRL3 ((0x008f << 2) + 0xfe037000)
#define DMC_SEC_RANGE2_WID_CTRL4 ((0x0090 << 2) + 0xfe037000)
#define DMC_SEC_RANGE3_WID_CTRL0 ((0x0092 << 2) + 0xfe037000)
#define DMC_SEC_RANGE3_WID_CTRL1 ((0x0093 << 2) + 0xfe037000)
#define DMC_SEC_RANGE3_WID_CTRL2 ((0x0094 << 2) + 0xfe037000)
#define DMC_SEC_RANGE3_WID_CTRL3 ((0x0095 << 2) + 0xfe037000)
#define DMC_SEC_RANGE3_WID_CTRL4 ((0x0096 << 2) + 0xfe037000)
#define DMC_SEC_RANGE4_WID_CTRL0 ((0x0098 << 2) + 0xfe037000)
#define DMC_SEC_RANGE4_WID_CTRL1 ((0x0099 << 2) + 0xfe037000)
#define DMC_SEC_RANGE4_WID_CTRL2 ((0x009a << 2) + 0xfe037000)
#define DMC_SEC_RANGE4_WID_CTRL3 ((0x009b << 2) + 0xfe037000)
#define DMC_SEC_RANGE4_WID_CTRL4 ((0x009c << 2) + 0xfe037000)
#define DMC_SEC_RANGE5_WID_CTRL0 ((0x009e << 2) + 0xfe037000)
#define DMC_SEC_RANGE5_WID_CTRL1 ((0x009f << 2) + 0xfe037000)
#define DMC_SEC_RANGE5_WID_CTRL2 ((0x00a0 << 2) + 0xfe037000)
#define DMC_SEC_RANGE5_WID_CTRL3 ((0x00a1 << 2) + 0xfe037000)
#define DMC_SEC_RANGE5_WID_CTRL4 ((0x00a2 << 2) + 0xfe037000)
#define DMC_SEC_RANGE6_WID_CTRL0 ((0x00a4 << 2) + 0xfe037000)
#define DMC_SEC_RANGE6_WID_CTRL1 ((0x00a5 << 2) + 0xfe037000)
#define DMC_SEC_RANGE6_WID_CTRL2 ((0x00a6 << 2) + 0xfe037000)
#define DMC_SEC_RANGE6_WID_CTRL3 ((0x00a7 << 2) + 0xfe037000)
#define DMC_SEC_RANGE6_WID_CTRL4 ((0x00a8 << 2) + 0xfe037000)
#define DMC_SEC_RANGE7_WID_CTRL0 ((0x00aa << 2) + 0xfe037000)
#define DMC_SEC_RANGE7_WID_CTRL1 ((0x00ab << 2) + 0xfe037000)
#define DMC_SEC_RANGE7_WID_CTRL2 ((0x00ac << 2) + 0xfe037000)
#define DMC_SEC_RANGE7_WID_CTRL3 ((0x00ad << 2) + 0xfe037000)
#define DMC_SEC_RANGE7_WID_CTRL4 ((0x00ae << 2) + 0xfe037000)
#define DMC_SEC_RANGE8_WID_CTRL0 ((0x00b0 << 2) + 0xfe037000)
#define DMC_SEC_RANGE8_WID_CTRL1 ((0x00b1 << 2) + 0xfe037000)
#define DMC_SEC_RANGE8_WID_CTRL2 ((0x00b2 << 2) + 0xfe037000)
#define DMC_SEC_RANGE8_WID_CTRL3 ((0x00b3 << 2) + 0xfe037000)
#define DMC_SEC_RANGE8_WID_CTRL4 ((0x00b4 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_WID_CTRL0 ((0x00b6 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_WID_CTRL1 ((0x00b7 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_WID_CTRL2 ((0x00b8 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_WID_CTRL3 ((0x00b9 << 2) + 0xfe037000)
#define DMC_SEC_RANGE9_WID_CTRL4 ((0x00ba << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_WID_CTRL0 ((0x00bc << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_WID_CTRL1 ((0x00bd << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_WID_CTRL2 ((0x00be << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_WID_CTRL3 ((0x00bf << 2) + 0xfe037000)
#define DMC_SEC_RANGE10_WID_CTRL4 ((0x00c0 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_WID_CTRL0 ((0x00c2 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_WID_CTRL1 ((0x00c3 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_WID_CTRL2 ((0x00c4 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_WID_CTRL3 ((0x00c5 << 2) + 0xfe037000)
#define DMC_SEC_RANGE11_WID_CTRL4 ((0x00c6 << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_WID_CTRL0 ((0x00c8 << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_WID_CTRL1 ((0x00c9 << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_WID_CTRL2 ((0x00ca << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_WID_CTRL3 ((0x00cb << 2) + 0xfe037000)
#define DMC_SEC_RANGE12_WID_CTRL4 ((0x00cc << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_WID_CTRL0 ((0x00ce << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_WID_CTRL1 ((0x00cf << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_WID_CTRL2 ((0x00d0 << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_WID_CTRL3 ((0x00d1 << 2) + 0xfe037000)
#define DMC_SEC_RANGE13_WID_CTRL4 ((0x00d2 << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_WID_CTRL0 ((0x00d4 << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_WID_CTRL1 ((0x00d5 << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_WID_CTRL2 ((0x00d6 << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_WID_CTRL3 ((0x00d7 << 2) + 0xfe037000)
#define DMC_SEC_RANGE14_WID_CTRL4 ((0x00d8 << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_WID_CTRL0 ((0x00da << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_WID_CTRL1 ((0x00db << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_WID_CTRL2 ((0x00dc << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_WID_CTRL3 ((0x00dd << 2) + 0xfe037000)
#define DMC_SEC_RANGE15_WID_CTRL4 ((0x00de << 2) + 0xfe037000)
#define DMC_DES_CTRL ((0x00e1 << 2) + 0xfe037000)
// bit 31 : range15_des_en policy : 1 range15_des_en = range15_local_des_en && GLOBAL_DES_EN. 0 :
// range15_des_en = range15_local_des_en ||  GLOBAL_DES_EN. bit 30 : range14_des_en policy : 1
// range14_des_en = range14_local_des_en && GLOBAL_DES_EN. 0 : range14_des_en =
// range14_local_des_en ||  GLOBAL_DES_EN. bit 29 : range13_des_en policy : 1 range13_des_en =
// range13_local_des_en && GLOBAL_DES_EN. 0 : range13_des_en = range13_local_des_en ||
// GLOBAL_DES_EN. bit 28 : range12_des_en policy : 1 range12_des_en = range12_local_des_en &&
// GLOBAL_DES_EN. 0 : range12_des_en = range12_local_des_en ||  GLOBAL_DES_EN. bit 27 :
// range11_des_en policy : 1 range11_des_en = range11_local_des_en && GLOBAL_DES_EN. 0 :
// range11_des_en = range11_local_des_en ||  GLOBAL_DES_EN. bit 26 : range10_des_en policy : 1
// range11_des_en = range10_local_des_en && GLOBAL_DES_EN. 0 : range10_des_en =
// range10_local_des_en ||  GLOBAL_DES_EN. bit 25 : range9_des_en policy  : 1  range9_des_en =
// range9_local_des_en && GLOBAL_DES_EN. 0 :  range9_des_en =  range9_local_des_en ||
// GLOBAL_DES_EN. bit 24 : range8_des_en policy  : 1  range8_des_en =  range8_local_des_en &&
// GLOBAL_DES_EN. 0 :  range8_des_en =  range8_local_des_en ||  GLOBAL_DES_EN. bit 23 :
// range7_des_en policy  : 1  range7_des_en =  range7_local_des_en && GLOBAL_DES_EN. 0 :
// range7_des_en =  range7_local_des_en ||  GLOBAL_DES_EN. bit 22 : range6_des_en policy  : 1
// range6_des_en =  range6_local_des_en && GLOBAL_DES_EN. 0 :  range6_des_en =  range6_local_des_en
// ||  GLOBAL_DES_EN. bit 21 : range5_des_en policy  : 1  range5_des_en =  range5_local_des_en &&
// GLOBAL_DES_EN. 0 :  range5_des_en =  range5_local_des_en ||  GLOBAL_DES_EN. bit 20 :
// range4_des_en policy  : 1  range4_des_en =  range4_local_des_en && GLOBAL_DES_EN. 0 :
// range4_des_en =  range4_local_des_en ||  GLOBAL_DES_EN. bit 19 : range3_des_en policy  : 1
// range3_des_en =  range3_local_des_en && GLOBAL_DES_EN. 0 :  range3_des_en =  range3_local_des_en
// ||  GLOBAL_DES_EN. bit 18 : range2_des_en policy  : 1  range2_des_en =  range2_local_des_en &&
// GLOBAL_DES_EN. 0 :  range2_des_en =  range2_local_des_en ||  GLOBAL_DES_EN. bit 17 :
// range1_des_en policy  : 1  range1_des_en =  range1_local_des_en && GLOBAL_DES_EN. 0 :
// range1_des_en =  range1_local_des_en ||  GLOBAL_DES_EN. bit 16 : range0_des_en policy  : 1
// range0_des_en =  range0_local_des_en && GLOBAL_DES_EN. 0 :  range0_des_en =  range0_local_des_en
// ||  GLOBAL_DES_EN. bit 1 | 0 | GLOBAL_DES_EN |  1: Global DES enable. 0 : global DES disable.
// default is 0. bit 0 | 0 | DES_lock  |  one time lock bit. after write 1 to this bit,
// DMC_DES_CTRL,DMC_DES_PADDING  can't be write and read. DES KEY registers and DES_PADDING can
// only be reset by pad reset.  But it can be changed by software after watch dog reset.
#define DMC_DES_KEY0_REG0 ((0x00e2 << 2) + 0xfe037000)
// default : 0
#define DMC_DES_KEY0_REG1 ((0x00e3 << 2) + 0xfe037000)
// default : 0
#define DMC_DES_KEY0_REG2 ((0x00e4 << 2) + 0xfe037000)
// default : 0
#define DMC_DES_KEY0_REG3 ((0x00e5 << 2) + 0xfe037000)
// default : 0
#define DMC_DES_KEY1_REG0 ((0x00e6 << 2) + 0xfe037000)
// default : 0
#define DMC_DES_KEY1_REG1 ((0x00e7 << 2) + 0xfe037000)
// default : 0
#define DMC_DES_KEY1_REG2 ((0x00e8 << 2) + 0xfe037000)
// default : 0
#define DMC_DES_KEY1_REG3 ((0x00e9 << 2) + 0xfe037000)
// default : 0
#define DMC_DES_PADDING ((0x00e0 << 2) + 0xfe037000)
// default : 0
// bit 31:0 | 0 | des_pading | 32bits address padding used for DES dkey generation.
// FROM SC2, the APB bus provided Master ID through PUSER signals.
// there's total 8 master IDs could access DMC non-secure registers.
// we assign 1 control bit for each APB Master and each DMC non-secure register domains
// and we added one lock bits to lock this setting can't be modified any more.
#define DDR_APB_SEC_CTRL0 ((0x00f0 << 2) + 0xfe037000)
// APB access  control for dmc REQUEST control register access control register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define DDR_APB_SEC_CTRL1 ((0x00f1 << 2) + 0xfe037000)
// APB access control for DMC DRAM timing parameter and DFI interface registers.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define DDR_APB_SEC_CTRL2 ((0x00f2 << 2) + 0xfe037000)
// APB access control for DMC PLL clock frequency control register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define DDR_APB_SEC_CTRL3 ((0x00f3 << 2) + 0xfe037000)
// APB access control for DMC sticky control register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define DDR_APB_SEC_CTRL4 ((0x00f4 << 2) + 0xfe037000)
// APB access control for DMC test control register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define DDR_APB_SEC_CTRL5 ((0x00f5 << 2) + 0xfe037000)
// APB access control for DMC clk reset control register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define DDR_APB_SEC_CTRL6 ((0x00f6 << 2) + 0xfe037000)
// APB access control for DMC protection register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define DDR_APB_SEC_CTRL7 ((0x00f7 << 2) + 0xfe037000)
// APB access control for DMC normal register.
// default : 0x0ff
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define DDR_APB_SEC_CTRL8 ((0x00f8 << 2) + 0xfe037000)
// APB access control for DDR PHY group registers.
// default : 0x50005
// bit 23:16.  APB access enable for DDR PHY group 1 register.
// bit 10  PHY IMEM control 1: force PHY IMEM output 0. 0: normal working mode.
// bit 9   PHY DMEM control 1: force PHY DMEM output 0. 0: normal working mode.
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define DDR_APB_SEC_CTRL9 ((0x00f9 << 2) + 0xfe037000)
// APB access control for DMC canvas register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
// registers to check the security protection and watch point error information.
#define DMC_SEC_STATUS ((0x00fa << 2) + 0xfe037000)
// bit 31~2. not used.
// bit 6
// bit 5
// bit 4
// bit 3   1 : normal security register write violation.( APB bus WDATA not equre the register
// value when APB write).  write 1 to clean this bit to 0. bit 2   sec_alert.   1 DMC secruity
// register alert function triggered. can't clean. only reset DMC can clear this bit. bit 1   write
// security violation. bit 0.  read security violation.
#define DMC_VIO_ADDR0 ((0x00fb << 2) + 0xfe037000)
// ddr0 write secure violation address.
#define DMC_VIO_ADDR1 ((0x00fc << 2) + 0xfe037000)
// bit 31:26 . not used. always 0.
// 24      ddr0 secure check violation.
// 23:21.  not used.
// 20     ddr0 write address overflow. write out of DDR size.
// 19:14. ddr0 write violation AWPROT bits.  (6bits write secruity)
// 13:12  Not used.
// 11:0   ddr0_write violation ID. bit 11~9. Master ID bit 7:4 for subid.
#define DMC_VIO_ADDR2 ((0x00fd << 2) + 0xfe037000)
// ddr0 read seure violation address
#define DMC_VIO_ADDR3 ((0x00fe << 2) + 0xfe037000)
// bit 31:26. not used. always 0.
// 24     ddr0 read secure check violation.
// 23:21. Not used.
// 20     ddr 0 read address overflow. write out of DDR size.
// 19.    Not used.
// 18:16. ddr 0 read violation ARPROT bits. (3 bits for read security).
// 15:12. Not used.
// 11:0   ddr 0 read violation ID. bit 11~9 Marster ID. bit 7:4 subid.
#define DMC_DDR_CTRL ((0x0100 << 2) + 0xfe037000)
// bit 27.   0 : cavnas use 64bytes boundary
// 1 : canvas use 32bytes boundary.
// bit 24:22     3'b000 : ddr3 mode.
// 3'b001 : ddr4 mode.
// 3'b010 : lpddr3 mode.
// 3'b011 : lpddr4 mode.
// bit 21.   rank1 enable bit. if 1,  rank1 used the address map is as bit 5:3 defined.
// bit 20    DDR4 BG1 enable bit.
// bit 18:   ddrphy_16b, DDR PHY DDR SDRAM data bits width.  1: 16bits. 0 : 32 bits.
// bit 16.   ddr_16b,   1: only use 16bits data in a 32bits DDR PHY data interface. 0 : normal
// data interface. bit 7:4 :  ddr1_size.  DDR rank1 size control. 4'b0000 : DDR rank 1 is 128Mbyte.
// 4'b0001 : DDR rank 1 is 256Mbyte.
// 4'b0010 : DDR rank 1 is 512Mbyte.
// 4'b0011 : DDR rank 1 is 1Gbyte.
// 4'b0100 : DDR rank 1 is 2Gbyte.
// 4'b0101 : DDR rank 1 is 4Gbyte.
// 4'b1000 : DDR rank 1 is 192Mbyte.
// 4'b1001 : DDR rank 1 is 374Mbyte.
// 4'b1010 : DDR rank 1 is 768Mbyte.
// 4'b1011 : DDR rank 1 is 1.5Gbyte.
// 4'b1100 : DDR rank 1 is 3Gbyte.
// others :  reserved.
// bit 3:0  :  ddr0_size. DDR rank0 size control.
// 4'b0000 : DDR rank 0 is 128Mbyte.
// 4'b0001 : DDR rank 0 is 256Mbyte.
// 4'b0010 : DDR rank 0 is 512Mbyte.
// 4'b0011 : DDR rank 0 is 1Gbyte.
// 4'b0100 : DDR rank 0 is 2Gbyte.
// 4'b0101 : DDR rank 0 is 4Gbyte.
// 4'b1000 : DDR rank 1 is 192Mbyte.
// 4'b1001 : DDR rank 1 is 374Mbyte.
// 4'b1010 : DDR rank 1 is 768Mbyte.
// 4'b1011 : DDR rank 1 is 1.5Gbyte.
// 4'b1100 : DDR rank 1 is 3Gbyte.
// others :  reserved.
// DDR3/4 LPDDR3/4 SDRAM address  to 32bits linear address map:
// DDR0_ADDRMAP is used to select RANK0 bank, row, col address selection.
// DDR1_ADDRMAP is used to select RANK1 bank, row, col address selection.
#define DDR0_ADDRMAP_0 ((0x0101 << 2) + 0xfe037000)
// 29:25 ca8.
// 24:20 ca7.
// 19:15 ca6.
// 14:10 ca5.
// 9:5   ca4.
// 4:0   ca3.
#define DDR0_ADDRMAP_1 ((0x0102 << 2) + 0xfe037000)
// 29:25 ra2.
// 24:20 ra1.
// 19:15 ra0.
// 14:10 ca11.
// 9:5   ca10.
// 4:0   ca9.
#define DDR0_ADDRMAP_2 ((0x0103 << 2) + 0xfe037000)
// 29:25 ra8.
// 24:20 ra7.
// 19:15 ra6.
// 14:10 ra5.
// 9:5   ra4.
// 4:0   ra3.
#define DDR0_ADDRMAP_3 ((0x0104 << 2) + 0xfe037000)
// 29:25 ra14.
// 24:20 ra13.
// 19:15 ra12.
// 14:10 ra11.
// 9:5   ra10.
// 4:0   ra9.
#define DDR0_ADDRMAP_4 ((0x0105 << 2) + 0xfe037000)
// 29:25 ra16 for DDR4 SDRAM
// 24:20 bg1  for DDR4 SDRAM.
// 19:15 ba2.    or bg0 for DDR4.
// 14:10 ba1.
// 9:5   ba0.
// 4:0   ra15.
#define DDR1_ADDRMAP_0 ((0x0106 << 2) + 0xfe037000)
// 29:25 ca8.
// 24:20 ca7.
// 19:15 ca6.
// 14:10 ca5.
// 9:5   ca4.
// 4:0   ca3.
#define DDR1_ADDRMAP_1 ((0x0107 << 2) + 0xfe037000)
// 29:25 ra2.
// 24:20 ra1.
// 19:15 ra0.
// 14:10 ca11.
// 9:5   ca10.
// 4:0   ca9.
#define DDR1_ADDRMAP_2 ((0x0108 << 2) + 0xfe037000)
// 29:25 ra8.
// 24:20 ra7.
// 19:15 ra6.
// 14:10 ra5.
// 9:5   ra4.
// 4:0   ra3.
#define DDR1_ADDRMAP_3 ((0x0109 << 2) + 0xfe037000)
// 29:25 ra14.
// 24:20 ra13.
// 19:15 ra12.
// 14:10 ra11.
// 9:5   ra10.
// 4:0   ra9.
#define DDR1_ADDRMAP_4 ((0x010a << 2) + 0xfe037000)
// 29:25 ra16 for DDR4 SDRAM
// 24:20 bg1  for DDR4 SDRAM.
// 19:15 ba2  or bg0 for DDR4 SDRAM..
// 14:10 ba1.
// 9:5   ba0.
// 4:0   ra15.
#define DMC_AXI2DDR0 ((0x0120 << 2) + 0xfe037000)
// for AXI address first 256MB  AXI ADDRESS[31:28] == 4'b0000.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr data 16bits mode   0 : 32bits.  1: 16 bits valid data in a 32bits data bus.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDR1 ((0x0121 << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b0001.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDR2 ((0x0122 << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b0010.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDR3 ((0x0123 << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b0011.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDR4 ((0x0124 << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b0100.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDR5 ((0x0125 << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b0101.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDR6 ((0x0126 << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b0110.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDR7 ((0x0127 << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b0111.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDR8 ((0x0128 << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b1000.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDR9 ((0x0129 << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b1001.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDRA ((0x012a << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b1010.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDRB ((0x012b << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b1011.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDRC ((0x012c << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b1100.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDRD ((0x012d << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b1101.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDRE ((0x012e << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b1110.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_AXI2DDRF ((0x012f << 2) + 0xfe037000)
// for AXI_ADDRESS[31:28] == 4'b1111.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define DMC_DDR_CTRL1 ((0x0130 << 2) + 0xfe037000)
// bit 1.  1: only allow DMA/DEMUX write data level == region security level.   0:  DMA/DEMUX
// write data level <= region sec level. bit 0. DMC_DDR_LOCK.    1: LOCK DMC_DDR_CTRL,
// DMC_DDR_CTRL1, DMC_AXI2DDRx, DDR0/1_ADDRMAP_x registers. those register can't modified any more.
//  0: all these registers can be read/write by secure APB access.
//
// Closing file:  ../mmc_lp4/dmc/rtl/dmc_reg.vh
//
//========================================================================
// STARTUP
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe02e000
// -----------------------------------------------
#define STARTUP_LOCK ((0x0000 << 2) + 0xfe02e000)
#define STARTUP_DFU_STS ((0x0004 << 2) + 0xfe02e000)
#define STARTUP_BOOT_SRC ((0x0008 << 2) + 0xfe02e000)
#define STARTUP_TEE_REQ_DFU ((0x0009 << 2) + 0xfe02e000)
#define STARTUP_BOOT_OVERRIDE ((0x000a << 2) + 0xfe02e000)
#define STARTUP_COLD_BOOT_CNT ((0x000b << 2) + 0xfe02e000)
#define STARTUP_KEY_PRESERVE ((0x000c << 2) + 0xfe02e000)
//========================================================================
// MIPI_DSI_PHY
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe01c000
// -----------------------------------------------
//`define MIPI_DSI_PHY_START      8'h00
//`define MIPI_DSI_PHY_END        16'hffff
#define MIPI_DSI_PHY_CTRL ((0x0000 << 2) + 0xfe01c000)
// bit 31.  soft reset for the phy. 1 = reset. 0 = dessert the reset.
// bit 30.  clock lane soft reset.
// bit 29.  data byte lane 3 soft reset.
// bit 28.  data byte lane 2 soft reset.
// bit 27.  data byte lane 1 soft reset.
// bit 26.  data byte lane 0 soft reset.
// bit 5.   LPDT data endian.  1 = transfer the high bit first. 0 : transfer the low bit first.
// bit 4.   HS data endian.
// bit 3.  force data byte lane in stop mode.
// bit 2.  force data byte lane 0 in receiver mode.
// bit 1. write 1 to sync the txclkesc input. the internal logic have to use txclkesc to decide
// Txvalid and Txready. bit 0.  enalbe the MIPI DSI PHY TxDDRClk.
#define MIPI_DSI_CHAN_CTRL ((0x0001 << 2) + 0xfe01c000)
// bit 31.   clk lane tx_hs_en control selection.  1 = from register. 0 use clk lane state
// machine. bit 30.   register bit for clock lane tx_hs_en. bit 29.  clk lane tx_lp_en contrl
// selection.  1 = from register. 0 from clk lane state machine. bit 28.  register bit for clock
// lane tx_lp_en. bit 27.  chan0 tx_hs_en control selection. 1 = from register. 0 from chan0 state
// machine. bit 26.  register bit for chan0 tx_hs_en. bit 25.  chan0 tx_lp_en control selection. 1
// = from register. 0 from chan0 state machine. bit 24. register bit from chan0 tx_lp_en. bit 23.
// chan0 rx_lp_en control selection. 1 = from register. 0 from chan0 state machine. bit 22.
// register bit from chan0 rx_lp_en. bit 21.  chan0 contention detection enable control selection.
// 1 = from register. 0 from chan0 state machine. bit 20. register bit from chan0 contention
// dectection enable. bit 19.  chan1 tx_hs_en control selection. 1 = from register. 0 from chan0
// state machine. bit 18.  register bit for chan1 tx_hs_en. bit 17.  chan1 tx_lp_en control
// selection. 1 = from register. 0 from chan0 state machine. bit 16. register bit from chan1
// tx_lp_en. bit 15.  chan2 tx_hs_en control selection. 1 = from register. 0 from chan0 state
// machine. bit 14.  register bit for chan2 tx_hs_en. bit 13.  chan2 tx_lp_en control selection. 1
// = from register. 0 from chan0 state machine. bit 12. register bit from chan2 tx_lp_en. bit 11.
// chan3 tx_hs_en control selection. 1 = from register. 0 from chan0 state machine. bit 10.
// register bit for chan3 tx_hs_en. bit 9.  chan3 tx_lp_en control selection. 1 = from register. 0
// from chan0 state machine. bit 8. register bit from chan3 tx_lp_en. bit 4.  clk chan power down.
// this bit is also used as the power down of the whole MIPI_DSI_PHY. bit 3.  chan3 power down.
// bit 2.  chan2 power down.
// bit 1.  chan1 power down.
// bit 0.  chan0 power down.
#define MIPI_DSI_CHAN_STS ((0x0002 << 2) + 0xfe01c000)
// bit 24.  chan0 TX->RX turn can't accept the ACK command from slave watch dog triggered.  write
// 1 to clear the status bit. bit 23.  chan0 RX ESC command watch dog triggered. write 1 to clean
// this bit. bit
#define MIPI_DSI_CLK_TIM ((0x0003 << 2) + 0xfe01c000)
// bit 31:24. TCLK_PREPARE.
// bit 23:16. TCLK_ZERO.
// bit 15:8.  TCLK_POST.
// bit 7:0.   TCLK_TRAIL.
#define MIPI_DSI_HS_TIM ((0x0004 << 2) + 0xfe01c000)
// bit 31:24. THS_PREPARE.
// bit 23:16. THS_ZERO.
// bit 15:8.  THS_TRAIL.
// bit 7:0.   THS_EXIT.
#define MIPI_DSI_LP_TIM ((0x0005 << 2) + 0xfe01c000)
// bit 31:24. tTA_GET.
// bit 23:16. tTA_GO.
// bit 15:8.  tTA_SURE.
// bit 7:0.   tLPX.
#define MIPI_DSI_ANA_UP_TIM ((0x0006 << 2) + 0xfe01c000)
// wait time to  MIPI DIS analog ready.
#define MIPI_DSI_INIT_TIM ((0x0007 << 2) + 0xfe01c000)
// TINIT.
#define MIPI_DSI_WAKEUP_TIM ((0x0008 << 2) + 0xfe01c000)
// TWAKEUP.
#define MIPI_DSI_LPOK_TIM ((0x0009 << 2) + 0xfe01c000)
// bit 31:0 when in RxULPS state, RX receiver is in sleep mode.
// every MIPI_DSI_ULPS_CHECK period, the receiver would be enabled once, and waiting this timer
// period to get the stable input.
#define MIPI_DSI_LP_WCHDOG ((0x000a << 2) + 0xfe01c000)
// bit 31:0 watch dog timer for MIPI DSI LP receive state.
#define MIPI_DSI_ANA_CTRL ((0x000b << 2) + 0xfe01c000)
// bit 31:0 tMBIAS.  timer to wait for analog mBIAS voltage stable.
#define MIPI_DSI_CLK_TIM1 ((0x000c << 2) + 0xfe01c000)
// bit 31:8  not used.
// bit 7:0    tCLK_PRE
#define MIPI_DSI_TURN_WCHDOG ((0x000d << 2) + 0xfe01c000)
// bit 31:0 watch dog timer for lane 0 LP turn around waiting time.
#define MIPI_DSI_ULPS_CHECK ((0x000e << 2) + 0xfe01c000)
// bit 31:0 when Lane0 in LP receive state,  if the another side sent Low power command,  using
// this timer to enable Tcheck the another size wakeup nor not.
#define MIPI_DSI_TEST_CTRL0 ((0x000f << 2) + 0xfe01c000)
#define MIPI_DSI_TEST_CTRL1 ((0x0010 << 2) + 0xfe01c000)
//========================================================================
//  rtc dig
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe09a000
// -----------------------------------------------
//
//
//
#define RTC_CTRL ((0x0000 << 2) + 0xfe09a000)
#define RTC_COUNTER_REG ((0x0001 << 2) + 0xfe09a000)
#define RTC_ALARM0_REG ((0x0002 << 2) + 0xfe09a000)
#define RTC_ALARM1_REG ((0x0003 << 2) + 0xfe09a000)
#define RTC_ALARM2_REG ((0x0004 << 2) + 0xfe09a000)
#define RTC_ALARM3_REG ((0x0005 << 2) + 0xfe09a000)
#define RTC_SEC_ADJUST_REG ((0x0006 << 2) + 0xfe09a000)
#define RTC_WIDEN_VAL ((0x0007 << 2) + 0xfe09a000)
#define RTC_INT_MASK ((0x0008 << 2) + 0xfe09a000)
#define RTC_INT_CLR ((0x0009 << 2) + 0xfe09a000)
#define RTC_OSCIN_CTRL0 ((0x000a << 2) + 0xfe09a000)
#define RTC_OSCIN_CTRL1 ((0x000b << 2) + 0xfe09a000)
#define RTC_INT_STATUS ((0x000c << 2) + 0xfe09a000)
#define RTC_REAL_TIME ((0x000d << 2) + 0xfe09a000)
//========================================================================
//  Temp sensor PLL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe020000
// -----------------------------------------------
#define TS_PLL_CFG_REG1 ((0x0001 << 2) + 0xfe020000)
#define TS_PLL_CFG_REG2 ((0x0002 << 2) + 0xfe020000)
#define TS_PLL_CFG_REG3 ((0x0003 << 2) + 0xfe020000)
#define TS_PLL_CFG_REG4 ((0x0004 << 2) + 0xfe020000)
#define TS_PLL_CFG_REG5 ((0x0005 << 2) + 0xfe020000)
#define TS_PLL_CFG_REG6 ((0x0006 << 2) + 0xfe020000)
#define TS_PLL_CFG_REG7 ((0x0007 << 2) + 0xfe020000)
#define TS_PLL_STAT0 ((0x0010 << 2) + 0xfe020000)
#define TS_PLL_STAT1 ((0x0011 << 2) + 0xfe020000)
#define TS_PLL_STAT2 ((0x0012 << 2) + 0xfe020000)
#define TS_PLL_STAT3 ((0x0013 << 2) + 0xfe020000)
#define TS_PLL_STAT4 ((0x0014 << 2) + 0xfe020000)
#define TS_PLL_STAT5 ((0x0015 << 2) + 0xfe020000)
#define TS_PLL_STAT6 ((0x0016 << 2) + 0xfe020000)
#define TS_PLL_STAT7 ((0x0017 << 2) + 0xfe020000)
#define TS_PLL_STAT8 ((0x0018 << 2) + 0xfe020000)
#define TS_PLL_STAT9 ((0x0019 << 2) + 0xfe020000)
//========================================================================
//  Temp sensor DDR
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe022000
// -----------------------------------------------
#define TS_DDR_CFG_REG1 ((0x0001 << 2) + 0xfe022000)
#define TS_DDR_CFG_REG2 ((0x0002 << 2) + 0xfe022000)
#define TS_DDR_CFG_REG3 ((0x0003 << 2) + 0xfe022000)
#define TS_DDR_CFG_REG4 ((0x0004 << 2) + 0xfe022000)
#define TS_DDR_CFG_REG5 ((0x0005 << 2) + 0xfe022000)
#define TS_DDR_CFG_REG6 ((0x0006 << 2) + 0xfe022000)
#define TS_DDR_CFG_REG7 ((0x0007 << 2) + 0xfe022000)
#define TS_DDR_STAT0 ((0x0010 << 2) + 0xfe022000)
#define TS_DDR_STAT1 ((0x0011 << 2) + 0xfe022000)
#define TS_DDR_STAT2 ((0x0012 << 2) + 0xfe022000)
#define TS_DDR_STAT3 ((0x0013 << 2) + 0xfe022000)
#define TS_DDR_STAT4 ((0x0014 << 2) + 0xfe022000)
#define TS_DDR_STAT5 ((0x0015 << 2) + 0xfe022000)
#define TS_DDR_STAT6 ((0x0016 << 2) + 0xfe022000)
#define TS_DDR_STAT7 ((0x0017 << 2) + 0xfe022000)
#define TS_DDR_STAT8 ((0x0018 << 2) + 0xfe022000)
#define TS_DDR_STAT9 ((0x0019 << 2) + 0xfe022000)
//========================================================================
//  Temp sensor GPU
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe035000
// -----------------------------------------------
//`define TS_GPU_CFG_REG1                         8'h01
//`define TS_GPU_CFG_REG2                         8'h02
//`define TS_GPU_CFG_REG3                         8'h03
//`define TS_GPU_CFG_REG4                         8'h04
//`define TS_GPU_CFG_REG5                         8'h05
//`define TS_GPU_CFG_REG6                         8'h06
//`define TS_GPU_CFG_REG7                         8'h07
//`define TS_GPU_STAT0                            8'h10
//`define TS_GPU_STAT1                            8'h11
//`define TS_GPU_STAT2                            8'h12
//`define TS_GPU_STAT3                            8'h13
//`define TS_GPU_STAT4                            8'h14
//`define TS_GPU_STAT5                            8'h15
//`define TS_GPU_STAT6                            8'h16
//`define TS_GPU_STAT7                            8'h17
//`define TS_GPU_STAT8                            8'h18
//`define TS_GPU_STAT9                            8'h19
//========================================================================
//  RNG
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe034000
// -----------------------------------------------
//========================================================================
//  ACODEC
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe01a000
// -----------------------------------------------
#define ACODEC_0 ((0x0000 << 2) + 0xfe01a000)
#define ACODEC_1 ((0x0001 << 2) + 0xfe01a000)
#define ACODEC_2 ((0x0002 << 2) + 0xfe01a000)
#define ACODEC_3 ((0x0003 << 2) + 0xfe01a000)
#define ACODEC_4 ((0x0004 << 2) + 0xfe01a000)
#define ACODEC_5 ((0x0005 << 2) + 0xfe01a000)
#define ACODEC_6 ((0x0006 << 2) + 0xfe01a000)
#define ACODEC_7 ((0x0007 << 2) + 0xfe01a000)
//========================================================================
//  AML USB PHY A
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe03c000
// -----------------------------------------------
#define AMLUSB_A0 ((0x0000 << 2) + 0xfe03c000)
#define AMLUSB_A1 ((0x0001 << 2) + 0xfe03c000)
#define AMLUSB_A2 ((0x0002 << 2) + 0xfe03c000)
#define AMLUSB_A3 ((0x0003 << 2) + 0xfe03c000)
#define AMLUSB_A4 ((0x0004 << 2) + 0xfe03c000)
#define AMLUSB_A5 ((0x0005 << 2) + 0xfe03c000)
#define AMLUSB_A6 ((0x0006 << 2) + 0xfe03c000)
#define AMLUSB_A7 ((0x0007 << 2) + 0xfe03c000)
#define AMLUSB_A8 ((0x0008 << 2) + 0xfe03c000)
#define AMLUSB_A9 ((0x0009 << 2) + 0xfe03c000)
#define AMLUSB_A10 ((0x000a << 2) + 0xfe03c000)
#define AMLUSB_A11 ((0x000b << 2) + 0xfe03c000)
#define AMLUSB_A12 ((0x000c << 2) + 0xfe03c000)
#define AMLUSB_A13 ((0x000d << 2) + 0xfe03c000)
#define AMLUSB_A14 ((0x000e << 2) + 0xfe03c000)
#define AMLUSB_A15 ((0x000f << 2) + 0xfe03c000)
#define AMLUSB_A16 ((0x0010 << 2) + 0xfe03c000)
#define AMLUSB_A17 ((0x0011 << 2) + 0xfe03c000)
#define AMLUSB_A18 ((0x0012 << 2) + 0xfe03c000)
#define AMLUSB_A19 ((0x0013 << 2) + 0xfe03c000)
#define AMLUSB_A20 ((0x0014 << 2) + 0xfe03c000)
#define AMLUSB_A21 ((0x0015 << 2) + 0xfe03c000)
#define AMLUSB_A22 ((0x0016 << 2) + 0xfe03c000)
#define AMLUSB_A23 ((0x0017 << 2) + 0xfe03c000)
#define AMLUSB_A24 ((0x0018 << 2) + 0xfe03c000)
#define AMLUSB_A25 ((0x0019 << 2) + 0xfe03c000)
#define AMLUSB_A26 ((0x001a << 2) + 0xfe03c000)
#define AMLUSB_A27 ((0x001b << 2) + 0xfe03c000)
#define AMLUSB_A28 ((0x001c << 2) + 0xfe03c000)
#define AMLUSB_A29 ((0x001d << 2) + 0xfe03c000)
#define AMLUSB_A30 ((0x001e << 2) + 0xfe03c000)
#define AMLUSB_A31 ((0x001f << 2) + 0xfe03c000)
//========================================================================
//  AML USB PHY B
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe03e000
// -----------------------------------------------
#define AMLUSB_B0 ((0x0000 << 2) + 0xfe03e000)
#define AMLUSB_B1 ((0x0001 << 2) + 0xfe03e000)
#define AMLUSB_B2 ((0x0002 << 2) + 0xfe03e000)
#define AMLUSB_B3 ((0x0003 << 2) + 0xfe03e000)
#define AMLUSB_B4 ((0x0004 << 2) + 0xfe03e000)
#define AMLUSB_B5 ((0x0005 << 2) + 0xfe03e000)
#define AMLUSB_B6 ((0x0006 << 2) + 0xfe03e000)
#define AMLUSB_B7 ((0x0007 << 2) + 0xfe03e000)
#define AMLUSB_B8 ((0x0008 << 2) + 0xfe03e000)
#define AMLUSB_B9 ((0x0009 << 2) + 0xfe03e000)
#define AMLUSB_B10 ((0x000a << 2) + 0xfe03e000)
#define AMLUSB_B11 ((0x000b << 2) + 0xfe03e000)
#define AMLUSB_B12 ((0x000c << 2) + 0xfe03e000)
#define AMLUSB_B13 ((0x000d << 2) + 0xfe03e000)
#define AMLUSB_B14 ((0x000e << 2) + 0xfe03e000)
#define AMLUSB_B15 ((0x000f << 2) + 0xfe03e000)
#define AMLUSB_B16 ((0x0010 << 2) + 0xfe03e000)
#define AMLUSB_B17 ((0x0011 << 2) + 0xfe03e000)
#define AMLUSB_B18 ((0x0012 << 2) + 0xfe03e000)
#define AMLUSB_B19 ((0x0013 << 2) + 0xfe03e000)
#define AMLUSB_B20 ((0x0014 << 2) + 0xfe03e000)
#define AMLUSB_B21 ((0x0015 << 2) + 0xfe03e000)
#define AMLUSB_B22 ((0x0016 << 2) + 0xfe03e000)
#define AMLUSB_B23 ((0x0017 << 2) + 0xfe03e000)
#define AMLUSB_B24 ((0x0018 << 2) + 0xfe03e000)
#define AMLUSB_B25 ((0x0019 << 2) + 0xfe03e000)
#define AMLUSB_B26 ((0x001a << 2) + 0xfe03e000)
#define AMLUSB_B27 ((0x001b << 2) + 0xfe03e000)
#define AMLUSB_B28 ((0x001c << 2) + 0xfe03e000)
#define AMLUSB_B29 ((0x001d << 2) + 0xfe03e000)
#define AMLUSB_B30 ((0x001e << 2) + 0xfe03e000)
#define AMLUSB_B31 ((0x001f << 2) + 0xfe03e000)
//========================================================================
//  PAD_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe004000
// -----------------------------------------------
#define PADCTRL_PIN_MUX_REG0 ((0x0000 << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REG1 ((0x0001 << 2) + 0xfe004000)
//`define PADCTRL_PIN_MUX_REG2          8'h02
#define PADCTRL_PIN_MUX_REG3 ((0x0003 << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REG4 ((0x0004 << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REG5 ((0x0005 << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REG6 ((0x0006 << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REG7 ((0x0007 << 2) + 0xfe004000)
//`define PADCTRL_PIN_MUX_REG8          8'h08
#define PADCTRL_PIN_MUX_REG9 ((0x0009 << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REGA ((0x000a << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REGB ((0x000b << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REGC ((0x000c << 2) + 0xfe004000)
//`define PADCTRL_PIN_MUX_REGD          8'h0d
//`define PADCTRL_PIN_MUX_REGE          8'h0e
//`define PADCTRL_PIN_MUX_REGF          8'h0f
#define PADCTRL_PIN_MUX_REGG ((0x0010 << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REGH ((0x0011 << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REGI ((0x0012 << 2) + 0xfe004000)
#define PADCTRL_PIN_MUX_REGJ ((0x0013 << 2) + 0xfe004000)
#define PADCTRL_GPIO_IRQ_CTRL0 ((0x0020 << 2) + 0xfe004000)
#define PADCTRL_GPIO_IRQ_CTRL1 ((0x0021 << 2) + 0xfe004000)
#define PADCTRL_GPIO_IRQ_CTRL2 ((0x0022 << 2) + 0xfe004000)
#define PADCTRL_GPIO_IRQ_CTRL3 ((0x0023 << 2) + 0xfe004000)
#define PADCTRL_GPIO_IRQ_CTRL4 ((0x0024 << 2) + 0xfe004000)
#define PADCTRL_GPIO_IRQ_CTRL5 ((0x0025 << 2) + 0xfe004000)
#define PADCTRL_GPIO_IRQ_CTRL6 ((0x0026 << 2) + 0xfe004000)
#define PADCTRL_GPIO_IRQ_CTRL7 ((0x0027 << 2) + 0xfe004000)
#define PADCTRL_WORLD_SYNC_CTRL0 ((0x0028 << 2) + 0xfe004000)
#define PADCTRL_GPIO_MSR_CTRL0 ((0x0029 << 2) + 0xfe004000)
#define PADCTRL_MISC_CTRL0 ((0x002a << 2) + 0xfe004000)
#define PADCTRL_GPIOZ_I ((0x0030 << 2) + 0xfe004000)
#define PADCTRL_GPIOZ_O ((0x0031 << 2) + 0xfe004000)
#define PADCTRL_GPIOZ_OEN ((0x0032 << 2) + 0xfe004000)
#define PADCTRL_GPIOZ_PULL_EN ((0x0033 << 2) + 0xfe004000)
#define PADCTRL_GPIOZ_PULL_UP ((0x0034 << 2) + 0xfe004000)
#define PADCTRL_GPIOZ_LOCK ((0x0035 << 2) + 0xfe004000)
#define PADCTRL_GPIOZ_PROT ((0x0036 << 2) + 0xfe004000)
#define PADCTRL_GPIOZ_DS ((0x0037 << 2) + 0xfe004000)
#define PADCTRL_GPIOX_I ((0x0040 << 2) + 0xfe004000)
#define PADCTRL_GPIOX_O ((0x0041 << 2) + 0xfe004000)
#define PADCTRL_GPIOX_OEN ((0x0042 << 2) + 0xfe004000)
#define PADCTRL_GPIOX_PULL_EN ((0x0043 << 2) + 0xfe004000)
#define PADCTRL_GPIOX_PULL_UP ((0x0044 << 2) + 0xfe004000)
#define PADCTRL_GPIOX_LOCK ((0x0045 << 2) + 0xfe004000)
#define PADCTRL_GPIOX_PROT ((0x0046 << 2) + 0xfe004000)
#define PADCTRL_GPIOX_DS ((0x0047 << 2) + 0xfe004000)
#define PADCTRL_GPIOX_DS_EXT ((0x0048 << 2) + 0xfe004000)
#define PADCTRL_GPIOT_I ((0x0050 << 2) + 0xfe004000)
#define PADCTRL_GPIOT_O ((0x0051 << 2) + 0xfe004000)
#define PADCTRL_GPIOT_OEN ((0x0052 << 2) + 0xfe004000)
#define PADCTRL_GPIOT_PULL_EN ((0x0053 << 2) + 0xfe004000)
#define PADCTRL_GPIOT_PULL_UP ((0x0054 << 2) + 0xfe004000)
#define PADCTRL_GPIOT_LOCK ((0x0055 << 2) + 0xfe004000)
#define PADCTRL_GPIOT_PROT ((0x0056 << 2) + 0xfe004000)
#define PADCTRL_GPIOT_DS ((0x0057 << 2) + 0xfe004000)
//`define PADCTRL_GPIOH_I               8'h50
//`define PADCTRL_GPIOH_O               8'h51
//`define PADCTRL_GPIOH_OEN             8'h52
//`define PADCTRL_GPIOH_PULL_EN         8'h53
//`define PADCTRL_GPIOH_PULL_UP         8'h54
//`define PADCTRL_GPIOH_LOCK            8'h55
//`define PADCTRL_GPIOH_PROT            8'h56
//`define PADCTRL_GPIOH_DS              8'h57
#define PADCTRL_GPIOD_I ((0x0060 << 2) + 0xfe004000)
#define PADCTRL_GPIOD_O ((0x0061 << 2) + 0xfe004000)
#define PADCTRL_GPIOD_OEN ((0x0062 << 2) + 0xfe004000)
#define PADCTRL_GPIOD_PULL_EN ((0x0063 << 2) + 0xfe004000)
#define PADCTRL_GPIOD_PULL_UP ((0x0064 << 2) + 0xfe004000)
#define PADCTRL_GPIOD_LOCK ((0x0065 << 2) + 0xfe004000)
#define PADCTRL_GPIOD_PROT ((0x0066 << 2) + 0xfe004000)
#define PADCTRL_GPIOD_DS ((0x0067 << 2) + 0xfe004000)
#define PADCTRL_GPIOE_I ((0x0070 << 2) + 0xfe004000)
#define PADCTRL_GPIOE_O ((0x0071 << 2) + 0xfe004000)
#define PADCTRL_GPIOE_OEN ((0x0072 << 2) + 0xfe004000)
#define PADCTRL_GPIOE_PULL_EN ((0x0073 << 2) + 0xfe004000)
#define PADCTRL_GPIOE_PULL_UP ((0x0074 << 2) + 0xfe004000)
#define PADCTRL_GPIOE_LOCK ((0x0075 << 2) + 0xfe004000)
#define PADCTRL_GPIOE_PROT ((0x0076 << 2) + 0xfe004000)
#define PADCTRL_GPIOE_DS ((0x0077 << 2) + 0xfe004000)
#define PADCTRL_GPIOC_I ((0x0080 << 2) + 0xfe004000)
#define PADCTRL_GPIOC_O ((0x0081 << 2) + 0xfe004000)
#define PADCTRL_GPIOC_OEN ((0x0082 << 2) + 0xfe004000)
#define PADCTRL_GPIOC_PULL_EN ((0x0083 << 2) + 0xfe004000)
#define PADCTRL_GPIOC_PULL_UP ((0x0084 << 2) + 0xfe004000)
#define PADCTRL_GPIOC_LOCK ((0x0085 << 2) + 0xfe004000)
#define PADCTRL_GPIOC_PROT ((0x0086 << 2) + 0xfe004000)
#define PADCTRL_GPIOC_DS ((0x0087 << 2) + 0xfe004000)
#define PADCTRL_GPIOB_I ((0x0090 << 2) + 0xfe004000)
#define PADCTRL_GPIOB_O ((0x0091 << 2) + 0xfe004000)
#define PADCTRL_GPIOB_OEN ((0x0092 << 2) + 0xfe004000)
#define PADCTRL_GPIOB_PULL_EN ((0x0093 << 2) + 0xfe004000)
#define PADCTRL_GPIOB_PULL_UP ((0x0094 << 2) + 0xfe004000)
#define PADCTRL_GPIOB_LOCK ((0x0095 << 2) + 0xfe004000)
#define PADCTRL_GPIOB_PROT ((0x0096 << 2) + 0xfe004000)
#define PADCTRL_GPIOB_DS ((0x0097 << 2) + 0xfe004000)
#define PADCTRL_GPIOH_I ((0x00a0 << 2) + 0xfe004000)
#define PADCTRL_GPIOH_O ((0x00a1 << 2) + 0xfe004000)
#define PADCTRL_GPIOH_OEN ((0x00a2 << 2) + 0xfe004000)
#define PADCTRL_GPIOH_PULL_EN ((0x00a3 << 2) + 0xfe004000)
#define PADCTRL_GPIOH_PULL_UP ((0x00a4 << 2) + 0xfe004000)
#define PADCTRL_GPIOH_LOCK ((0x00a5 << 2) + 0xfe004000)
#define PADCTRL_GPIOH_PROT ((0x00a6 << 2) + 0xfe004000)
#define PADCTRL_GPIOH_DS ((0x00a7 << 2) + 0xfe004000)
//`define PADCTRL_GPIOA_I               8'hA0
//`define PADCTRL_GPIOA_O               8'hA1
//`define PADCTRL_GPIOA_OEN             8'hA2
//`define PADCTRL_GPIOA_PULL_EN         8'hA3
//`define PADCTRL_GPIOA_PULL_UP         8'hA4
//`define PADCTRL_GPIOA_LOCK            8'hA5
//`define PADCTRL_GPIOA_PROT            8'hA6
//`define PADCTRL_GPIOA_DS              8'hA7
#define PADCTRL_TESTN_I ((0x00b0 << 2) + 0xfe004000)
#define PADCTRL_TESTN_O ((0x00b1 << 2) + 0xfe004000)
#define PADCTRL_TESTN_OEN ((0x00b2 << 2) + 0xfe004000)
#define PADCTRL_TESTN_PULL_EN ((0x00b3 << 2) + 0xfe004000)
#define PADCTRL_TESTN_PULL_UP ((0x00b4 << 2) + 0xfe004000)
#define PADCTRL_TESTN_LOCK ((0x00b5 << 2) + 0xfe004000)
#define PADCTRL_TESTN_PROT ((0x00b6 << 2) + 0xfe004000)
#define PADCTRL_TESTN_DS ((0x00b7 << 2) + 0xfe004000)
//`define PADCTRL_ANALOG_I              8'hC0
//`define PADCTRL_ANALOG_EN             8'hC1
#define PADCTRL_LOCK_PIN_MUX0 ((0x00d0 << 2) + 0xfe004000)
#define PADCTRL_LOCK_PIN_MUX1 ((0x00d1 << 2) + 0xfe004000)
#define PADCTRL_LOCK_PIN_MUX2 ((0x00d2 << 2) + 0xfe004000)
#define PADCTRL_LOCK_PIN_MUX3 ((0x00d3 << 2) + 0xfe004000)
#define PADCTRL_LOCK_PIN_MUX4 ((0x00d4 << 2) + 0xfe004000)
#define PADCTRL_PROT_PIN_MUX0 ((0x00d8 << 2) + 0xfe004000)
#define PADCTRL_PROT_PIN_MUX1 ((0x00d9 << 2) + 0xfe004000)
#define PADCTRL_PROT_PIN_MUX2 ((0x00da << 2) + 0xfe004000)
#define PADCTRL_PROT_PIN_MUX3 ((0x00db << 2) + 0xfe004000)
#define PADCTRL_PROT_PIN_MUX4 ((0x00dc << 2) + 0xfe004000)
#define PADCTRL_MUTE_CTRL ((0x00e0 << 2) + 0xfe004000)
#define PADCTRL_MUTE_TDM_DISA ((0x00e1 << 2) + 0xfe004000)
#define PADCTRL_DEBUG_SEL ((0x00e2 << 2) + 0xfe004000)
#define PADCTRL_AUDIO_PAD_SEL0 ((0x00e3 << 2) + 0xfe004000)
#define PADCTRL_AUDIO_PAD_SEL1 ((0x00e4 << 2) + 0xfe004000)
//========================================================================
//  SYS_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe010000
// -----------------------------------------------
#define SYSCTRL_METAL_REV0 ((0x0000 << 2) + 0xfe010000)
#define SYSCTRL_METAL_REV1 ((0x0001 << 2) + 0xfe010000)
#define SYSCTRL_METAL_REV2 ((0x0002 << 2) + 0xfe010000)
#define SYSCTRL_CHIP_ID ((0x000b << 2) + 0xfe010000)
#define SYSCTRL_WRITEONCE1_REG0 ((0x0010 << 2) + 0xfe010000)
#define SYSCTRL_WRITEONCE1_STICKY_REG0 ((0x0011 << 2) + 0xfe010000)
#define SYSCTRL_WRITEONCE1_SEC_REG0 ((0x0012 << 2) + 0xfe010000)
#define SYSCTRL_WRITEONCE1_STICKY_SEC_REG0 ((0x0013 << 2) + 0xfe010000)
#define SYSCTRL_WRITEONCE_REG0 ((0x0014 << 2) + 0xfe010000)
#define SYSCTRL_WRITEONCE_REG1 ((0x0015 << 2) + 0xfe010000)
#define SYSCTRL_WRITEONCE_SEC_REG0 ((0x0016 << 2) + 0xfe010000)
#define SYSCTRL_WRITEONCE_STICKY_REG0 ((0x0017 << 2) + 0xfe010000)
#define SYSCTRL_WRITEONCE_STICKY_REG1 ((0x0018 << 2) + 0xfe010000)
#define SYSCTRL_WRITEONCE_STICKY_SEC_REG0 ((0x0019 << 2) + 0xfe010000)
#define SYSCTRL_TIMERA_CTRL ((0x0030 << 2) + 0xfe010000)
#define SYSCTRL_TIMERA ((0x0031 << 2) + 0xfe010000)
#define SYSCTRL_TIMERB_CTRL ((0x0032 << 2) + 0xfe010000)
#define SYSCTRL_TIMERB ((0x0033 << 2) + 0xfe010000)
#define SYSCTRL_TIMERC_CTRL ((0x0034 << 2) + 0xfe010000)
#define SYSCTRL_TIMERC ((0x0035 << 2) + 0xfe010000)
#define SYSCTRL_TIMERD_CTRL ((0x0036 << 2) + 0xfe010000)
#define SYSCTRL_TIMERD ((0x0037 << 2) + 0xfe010000)
#define SYSCTRL_SEC_TIMERA_CTRL ((0x0038 << 2) + 0xfe010000)
#define SYSCTRL_SEC_TIMERA ((0x0039 << 2) + 0xfe010000)
#define SYSCTRL_TIMERE_CTRL ((0x003a << 2) + 0xfe010000)
#define SYSCTRL_TIMERE ((0x003b << 2) + 0xfe010000)
#define SYSCTRL_TIMERE_HI ((0x003c << 2) + 0xfe010000)
#define SYSCTRL_TIMERF_CTRL ((0x003d << 2) + 0xfe010000)
#define SYSCTRL_TIMERF ((0x003e << 2) + 0xfe010000)
#define SYSCTRL_TIMERF_HI ((0x003f << 2) + 0xfe010000)
#define SYSCTRL_TIMERG_CTRL ((0x0040 << 2) + 0xfe010000)
#define SYSCTRL_TIMERG ((0x0041 << 2) + 0xfe010000)
#define SYSCTRL_TIMERH_CTRL ((0x0042 << 2) + 0xfe010000)
#define SYSCTRL_TIMERH ((0x0043 << 2) + 0xfe010000)
#define SYSCTRL_TIMERI_CTRL ((0x0044 << 2) + 0xfe010000)
#define SYSCTRL_TIMERI ((0x0045 << 2) + 0xfe010000)
#define SYSCTRL_TIMERJ_CTRL ((0x0046 << 2) + 0xfe010000)
#define SYSCTRL_TIMERJ ((0x0047 << 2) + 0xfe010000)
#define SYSCTRL_SEC_TIMERE_CTRL ((0x0048 << 2) + 0xfe010000)
#define SYSCTRL_SEC_TIMERE ((0x0049 << 2) + 0xfe010000)
#define SYSCTRL_SEC_TIMERE_HI ((0x004a << 2) + 0xfe010000)
#define SYSCTRL_OSC_RING_CTRL0 ((0x0050 << 2) + 0xfe010000)
#define SYSCTRL_OSC_RING_CTRL1 ((0x0051 << 2) + 0xfe010000)
#define SYSCTRL_AM2AXI_CTRL0 ((0x0052 << 2) + 0xfe010000)
#define SYSCTRL_AM2AXI_STS ((0x0053 << 2) + 0xfe010000)
#define SYSCTRL_AXI_PIPE_CTRL0 ((0x0055 << 2) + 0xfe010000)
#define SYSCTRL_AXI_PIPE_CTRL1 ((0x0056 << 2) + 0xfe010000)
#define SYSCTRL_TIMER90K ((0x0057 << 2) + 0xfe010000)
#define SYSCTRL_SCR ((0x0058 << 2) + 0xfe010000)
#define SYSCTRL_HPG_TIMER ((0x0059 << 2) + 0xfe010000)
#define SYSCTRL_AXI_PIPE_CTRL2 ((0x005a << 2) + 0xfe010000)
//`define SYSCTRL_VIPNANOQ_CTRL0                  10'h5A
#define SYSCTRL_AHB2DDR_CTRL0 ((0x005b << 2) + 0xfe010000)
#define SYSCTRL_AHB2DDR_CTRL1 ((0x005c << 2) + 0xfe010000)
#define SYSCTRL_POC ((0x0060 << 2) + 0xfe010000)
#define SYSCTRL_VPU_SECURE_REG0 ((0x0061 << 2) + 0xfe010000)
#define SYSCTRL_VPU_SECURE_REG1 ((0x0062 << 2) + 0xfe010000)
//`define SYSCTRL_NIC_CFG0                        10'h63
#define SYSCTRL_ALERT_STS_STICKY ((0x0064 << 2) + 0xfe010000)
#define SYSCTRL_ALERT_ENABLE ((0x0066 << 2) + 0xfe010000)
#define SYSCTRL_ENABLE_SPIFC ((0x0068 << 2) + 0xfe010000)
#define SYSCTRL_DEBUG_REG0 ((0x0090 << 2) + 0xfe010000)
#define SYSCTRL_DEBUG_REG1 ((0x0091 << 2) + 0xfe010000)
#define SYSCTRL_DEBUG_REG2 ((0x0092 << 2) + 0xfe010000)
#define SYSCTRL_DEBUG_REG3 ((0x0093 << 2) + 0xfe010000)
#define SYSCTRL_DEBUG_REG4 ((0x0094 << 2) + 0xfe010000)
#define SYSCTRL_DEBUG_REG5 ((0x0095 << 2) + 0xfe010000)
#define SYSCTRL_DEBUG_REG6 ((0x0096 << 2) + 0xfe010000)
#define SYSCTRL_DEBUG_REG7 ((0x0097 << 2) + 0xfe010000)
#define SYSCTRL_STATUS_REG0 ((0x00a0 << 2) + 0xfe010000)
#define SYSCTRL_STATUS_REG1 ((0x00a1 << 2) + 0xfe010000)
#define SYSCTRL_STATUS_REG2 ((0x00a2 << 2) + 0xfe010000)
#define SYSCTRL_STATUS_REG3 ((0x00a3 << 2) + 0xfe010000)
#define SYSCTRL_STATUS_REG4 ((0x00a4 << 2) + 0xfe010000)
#define SYSCTRL_STATUS_REG5 ((0x00a5 << 2) + 0xfe010000)
#define SYSCTRL_STATUS_REG6 ((0x00a6 << 2) + 0xfe010000)
#define SYSCTRL_STATUS_REG7 ((0x00a7 << 2) + 0xfe010000)
#define SYSCTRL_STICKY_REG0 ((0x00b0 << 2) + 0xfe010000)
#define SYSCTRL_STICKY_REG1 ((0x00b1 << 2) + 0xfe010000)
#define SYSCTRL_STICKY_REG2 ((0x00b2 << 2) + 0xfe010000)
#define SYSCTRL_STICKY_REG3 ((0x00b3 << 2) + 0xfe010000)
#define SYSCTRL_STICKY_REG4 ((0x00b4 << 2) + 0xfe010000)
#define SYSCTRL_STICKY_REG5 ((0x00b5 << 2) + 0xfe010000)
#define SYSCTRL_STICKY_REG6 ((0x00b6 << 2) + 0xfe010000)
#define SYSCTRL_STICKY_REG7 ((0x00b7 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG0 ((0x00c0 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG1 ((0x00c1 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG2 ((0x00c2 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG3 ((0x00c3 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG4 ((0x00c4 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG5 ((0x00c5 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG6 ((0x00c6 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG7 ((0x00c7 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG8 ((0x00c8 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG9 ((0x00c9 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG10 ((0x00ca << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG11 ((0x00cb << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG12 ((0x00cc << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG13 ((0x00cd << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG14 ((0x00ce << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG15 ((0x00cf << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG16 ((0x00d0 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG17 ((0x00d1 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG18 ((0x00d2 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG19 ((0x00d3 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG20 ((0x00d4 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG21 ((0x00d5 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG22 ((0x00d6 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG23 ((0x00d7 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG24 ((0x00d8 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG25 ((0x00d9 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG26 ((0x00da << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG27 ((0x00db << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG28 ((0x00dc << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG29 ((0x00dd << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG30 ((0x00de << 2) + 0xfe010000)
#define SYSCTRL_SEC_STATUS_REG31 ((0x00df << 2) + 0xfe010000)
#define SYSCTRL_SEC_STICKY_REG0 ((0x00e0 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STICKY_REG1 ((0x00e1 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STICKY_REG2 ((0x00e2 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STICKY_REG3 ((0x00e3 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STICKY_REG4 ((0x00e4 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STICKY_REG5 ((0x00e5 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STICKY_REG6 ((0x00e6 << 2) + 0xfe010000)
#define SYSCTRL_SEC_STICKY_REG7 ((0x00e7 << 2) + 0xfe010000)
#define SYSCTRL_MSG_INDEX0_STICKY ((0x00f0 << 2) + 0xfe010000)
#define SYSCTRL_MSG_INDEX1_STICKY ((0x00f1 << 2) + 0xfe010000)
#define SYSCTRL_MSG_INDEX2_STICKY ((0x00f2 << 2) + 0xfe010000)
#define SYSCTRL_MSG_INDEX3_STICKY ((0x00f3 << 2) + 0xfe010000)
//========================================================================
//  CLK_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe000000
// -----------------------------------------------
#define CLKCTRL_OSCIN_CTRL ((0x0001 << 2) + 0xfe000000)
#define CLKCTRL_RTC_BY_OSCIN_CTRL0 ((0x0002 << 2) + 0xfe000000)
#define CLKCTRL_RTC_BY_OSCIN_CTRL1 ((0x0003 << 2) + 0xfe000000)
#define CLKCTRL_RTC_CTRL ((0x0004 << 2) + 0xfe000000)
#define CLKCTRL_CHECK_CLK_RESULT ((0x0005 << 2) + 0xfe000000)
#define CLKCTRL_MBIST_ATSPEED_CTRL ((0x0006 << 2) + 0xfe000000)
#define CLKCTRL_LOCK_BIT_REG0 ((0x0008 << 2) + 0xfe000000)
#define CLKCTRL_LOCK_BIT_REG1 ((0x0009 << 2) + 0xfe000000)
#define CLKCTRL_LOCK_BIT_REG2 ((0x000a << 2) + 0xfe000000)
#define CLKCTRL_LOCK_BIT_REG3 ((0x000b << 2) + 0xfe000000)
#define CLKCTRL_PROT_BIT_REG0 ((0x000c << 2) + 0xfe000000)
#define CLKCTRL_PROT_BIT_REG1 ((0x000d << 2) + 0xfe000000)
#define CLKCTRL_PROT_BIT_REG2 ((0x000e << 2) + 0xfe000000)
#define CLKCTRL_PROT_BIT_REG3 ((0x000f << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_CTRL0 ((0x0010 << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_EN0_REG0 ((0x0011 << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_EN0_REG1 ((0x0012 << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_EN0_REG2 ((0x0013 << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_EN0_REG3 ((0x0014 << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_EN1_REG0 ((0x0015 << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_EN1_REG1 ((0x0016 << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_EN1_REG2 ((0x0017 << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_EN1_REG3 ((0x0018 << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_VPU_EN0 ((0x0019 << 2) + 0xfe000000)
#define CLKCTRL_SYS_CLK_VPU_EN1 ((0x001a << 2) + 0xfe000000)
#define CLKCTRL_AXI_CLK_CTRL0 ((0x001b << 2) + 0xfe000000)
#define CLKCTRL_SYSOSCIN_CTRL ((0x001c << 2) + 0xfe000000)
#define CLKCTRL_TST_CTRL0 ((0x0020 << 2) + 0xfe000000)
#define CLKCTRL_TST_CTRL1 ((0x0021 << 2) + 0xfe000000)
#define CLKCTRL_CECA_CTRL0 ((0x0022 << 2) + 0xfe000000)
#define CLKCTRL_CECA_CTRL1 ((0x0023 << 2) + 0xfe000000)
#define CLKCTRL_CECB_CTRL0 ((0x0024 << 2) + 0xfe000000)
#define CLKCTRL_CECB_CTRL1 ((0x0025 << 2) + 0xfe000000)
#define CLKCTRL_SC_CLK_CTRL ((0x0026 << 2) + 0xfe000000)
#define CLKCTRL_DSPA_CLK_CTRL0 ((0x0027 << 2) + 0xfe000000)
//`define CLKCTRL_DSPB_CLK_CTRL0          10'h28
#define CLKCTRL_RAMA_CLK_CTRL0 ((0x0029 << 2) + 0xfe000000)
#define CLKCTRL_CLK12_24_CTRL ((0x002a << 2) + 0xfe000000)
#define CLKCTRL_AXI_CLK_EN0 ((0x002b << 2) + 0xfe000000)
#define CLKCTRL_AXI_CLK_EN1 ((0x002c << 2) + 0xfe000000)
//`define CLKCTRL_RTCPLL_CTRL0            10'h2b
//`define CLKCTRL_RTCPLL_CTRL1            10'h2c
//`define CLKCTRL_RTCPLL_CTRL2            10'h2d
//`define CLKCTRL_RTCPLL_CTRL3            10'h2e
//`define CLKCTRL_RTCPLL_CTRL4            10'h2f
//`define CLKCTRL_RTCPLL_STS              10'h28
#define CLKCTRL_VID_CLK_CTRL ((0x0030 << 2) + 0xfe000000)
#define CLKCTRL_VID_CLK_CTRL2 ((0x0031 << 2) + 0xfe000000)
#define CLKCTRL_VID_CLK_DIV ((0x0032 << 2) + 0xfe000000)
#define CLKCTRL_VIID_CLK_DIV ((0x0033 << 2) + 0xfe000000)
#define CLKCTRL_VIID_CLK_CTRL ((0x0034 << 2) + 0xfe000000)
#define CLKCTRL_HDMI_CLK_CTRL ((0x0038 << 2) + 0xfe000000)
#define CLKCTRL_VID_PLL_CLK_DIV ((0x0039 << 2) + 0xfe000000)
#define CLKCTRL_VPU_CLK_CTRL ((0x003a << 2) + 0xfe000000)
#define CLKCTRL_VPU_CLKB_CTRL ((0x003b << 2) + 0xfe000000)
#define CLKCTRL_VPU_CLKC_CTRL ((0x003c << 2) + 0xfe000000)
#define CLKCTRL_VID_LOCK_CLK_CTRL ((0x003d << 2) + 0xfe000000)
#define CLKCTRL_VDIN_MEAS_CLK_CTRL ((0x003e << 2) + 0xfe000000)
#define CLKCTRL_VAPBCLK_CTRL ((0x003f << 2) + 0xfe000000)
#define CLKCTRL_HDCP22_CLK_CTRL ((0x0040 << 2) + 0xfe000000)
//`define CLKCTRL_MIPIDSI_PHY_CLK_CTRL    10'h41
#define CLKCTRL_CDAC_CLK_CTRL ((0x0042 << 2) + 0xfe000000)
//`define CLKCTRL_MIPI_CSI_PHY_CLK_CTRL   10'h43
//`define CLKCTRL_CSI2_ADAPT_CLK_CTRL     10'h44
#define CLKCTRL_VDEC_CLK_CTRL ((0x0050 << 2) + 0xfe000000)
#define CLKCTRL_VDEC2_CLK_CTRL ((0x0051 << 2) + 0xfe000000)
#define CLKCTRL_VDEC3_CLK_CTRL ((0x0052 << 2) + 0xfe000000)
#define CLKCTRL_VDEC4_CLK_CTRL ((0x0053 << 2) + 0xfe000000)
//`define CLKCTRL_WAVE420L_CLK_CTRL       10'h54
//`define CLKCTRL_WAVE420L_CLK_CTRL2      10'h55
#define CLKCTRL_TS_CLK_CTRL ((0x0056 << 2) + 0xfe000000)
#define CLKCTRL_MALI_CLK_CTRL ((0x0057 << 2) + 0xfe000000)
//`define CLKCTRL_VIPNANOQ_CLK_CTRL       10'h58
#define CLKCTRL_ETH_CLK_CTRL ((0x0059 << 2) + 0xfe000000)
#define CLKCTRL_NAND_CLK_CTRL ((0x005a << 2) + 0xfe000000)
#define CLKCTRL_SD_EMMC_CLK_CTRL ((0x005b << 2) + 0xfe000000)
//`define CLKCTRL_BT656_CLK_CTRL          10'h5C
#define CLKCTRL_SPICC_CLK_CTRL ((0x005d << 2) + 0xfe000000)
#define CLKCTRL_GEN_CLK_CTRL ((0x005e << 2) + 0xfe000000)
#define CLKCTRL_SAR_CLK_CTRL0 ((0x005f << 2) + 0xfe000000)
#define CLKCTRL_PWM_CLK_AB_CTRL ((0x0060 << 2) + 0xfe000000)
#define CLKCTRL_PWM_CLK_CD_CTRL ((0x0061 << 2) + 0xfe000000)
#define CLKCTRL_PWM_CLK_EF_CTRL ((0x0062 << 2) + 0xfe000000)
#define CLKCTRL_PWM_CLK_GH_CTRL ((0x0063 << 2) + 0xfe000000)
#define CLKCTRL_PWM_CLK_IJ_CTRL ((0x0064 << 2) + 0xfe000000)
#define CLKCTRL_DEMOD_CLK_CTRL ((0x0080 << 2) + 0xfe000000)
#define CLKCTRL_NNA_CLK_CNTL ((0x0088 << 2) + 0xfe000000)
#define CLKCTRL_TIMESTAMP_CTRL ((0x0100 << 2) + 0xfe000000)
#define CLKCTRL_TIMESTAMP_CTRL1 ((0x0101 << 2) + 0xfe000000)
#define CLKCTRL_TIMESTAMP_CTRL2 ((0x0103 << 2) + 0xfe000000)
#define CLKCTRL_TIMESTAMP_RD0 ((0x0104 << 2) + 0xfe000000)
#define CLKCTRL_TIMESTAMP_RD1 ((0x0105 << 2) + 0xfe000000)
#define CLKCTRL_TIMEBASE_CTRL0 ((0x0106 << 2) + 0xfe000000)
#define CLKCTRL_TIMEBASE_CTRL1 ((0x0107 << 2) + 0xfe000000)
#define CLKCTRL_EFUSE_CPU_CFG01 ((0x0120 << 2) + 0xfe000000)
#define CLKCTRL_EFUSE_CPU_CFG2 ((0x0121 << 2) + 0xfe000000)
#define CLKCTRL_EFUSE_ENCP_CFG0 ((0x0122 << 2) + 0xfe000000)
#define CLKCTRL_EFUSE_MALI_CFG01 ((0x0123 << 2) + 0xfe000000)
//`define CLKCTRL_EFUSE_HEVCB_CFG01       10'h124
//`define CLKCTRL_EFUSE_HEVCB_CFG2        10'h125
#define CLKCTRL_EFUSE_LOCK ((0x0126 << 2) + 0xfe000000)
//========================================================================
//  PWR_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe00c000
// -----------------------------------------------
#define PWRCTRL_PWR_ACK0 ((0x0000 << 2) + 0xfe00c000)
#define PWRCTRL_PWR_ACK1 ((0x0001 << 2) + 0xfe00c000)
#define PWRCTRL_PWR_OFF0 ((0x0004 << 2) + 0xfe00c000)
#define PWRCTRL_PWR_OFF1 ((0x0005 << 2) + 0xfe00c000)
#define PWRCTRL_ISO_EN0 ((0x0008 << 2) + 0xfe00c000)
#define PWRCTRL_ISO_EN1 ((0x0009 << 2) + 0xfe00c000)
#define PWRCTRL_FOCRST0 ((0x000c << 2) + 0xfe00c000)
#define PWRCTRL_FOCRST1 ((0x000d << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD0 ((0x0010 << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD1 ((0x0011 << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD2 ((0x0012 << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD3 ((0x0013 << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD4 ((0x0014 << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD5 ((0x0015 << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD6 ((0x0016 << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD7 ((0x0017 << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD8 ((0x0018 << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD9 ((0x0019 << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD10 ((0x001a << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD11 ((0x001b << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD12 ((0x001c << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD13 ((0x001d << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD14 ((0x001e << 2) + 0xfe00c000)
#define PWRCTRL_MEM_PD15 ((0x001f << 2) + 0xfe00c000)
#define PWRCTRL_NNA_AXI_PWR_CTRL ((0x0020 << 2) + 0xfe00c000)
#define PWRCTRL_ACCESS_CTRL ((0x0021 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_AUTO_OFF_CTRL0 ((0x0040 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_AUTO_OFF_CTRL1 ((0x0041 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_AUTO_OFF_CTRL2 ((0x0042 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_AUTO_OFF_CTRL3 ((0x0043 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_AUTO_OFF_CTRL4 ((0x0044 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_TIMER_TH_01 ((0x0048 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_TIMER_TH_23 ((0x0049 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_TIMER_TH_45 ((0x004a << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_TIMER_TH_67 ((0x004b << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_TIMER_TH_89 ((0x004c << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_IRQ_MASK0 ((0x0050 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_IRQ_MASK1 ((0x0051 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_IRQ_MASK2 ((0x0052 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_IRQ_MASK3 ((0x0053 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_IRQ_MASK4 ((0x0054 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_IRQ_MASK5 ((0x0055 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_IRQ_MASK6 ((0x0056 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_IRQ_MASK7 ((0x0057 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_MEMPD_INIT_SET ((0x0060 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_MEMPD_OFF_SET ((0x0061 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_MEMPD_ON_A_SET ((0x0062 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_MEMPD_ON_B_SET ((0x0063 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_MEMPD_ON_C_SET ((0x0064 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_MEMPD_ON_D_SET ((0x0065 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_MEMPD_STS ((0x0066 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_FSM_STS0 ((0x0067 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_FSM_STS1 ((0x0068 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_FSM_STS2 ((0x0069 << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_FSM_START_OFF ((0x006d << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_FSM_START_ON ((0x006e << 2) + 0xfe00c000)
#define PWRCTRL_CPU0_FSM_JUMP ((0x006f << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_AUTO_OFF_CTRL0 ((0x0070 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_AUTO_OFF_CTRL1 ((0x0071 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_AUTO_OFF_CTRL2 ((0x0072 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_AUTO_OFF_CTRL3 ((0x0073 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_AUTO_OFF_CTRL4 ((0x0074 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_TIMER_TH_01 ((0x0078 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_TIMER_TH_23 ((0x0079 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_TIMER_TH_45 ((0x007a << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_TIMER_TH_67 ((0x007b << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_TIMER_TH_89 ((0x007c << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_IRQ_MASK0 ((0x0080 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_IRQ_MASK1 ((0x0081 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_IRQ_MASK2 ((0x0082 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_IRQ_MASK3 ((0x0083 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_IRQ_MASK4 ((0x0084 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_IRQ_MASK5 ((0x0085 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_IRQ_MASK6 ((0x0086 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_IRQ_MASK7 ((0x0087 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_MEMPD_INIT_SET ((0x0090 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_MEMPD_OFF_SET ((0x0091 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_MEMPD_ON_A_SET ((0x0092 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_MEMPD_ON_B_SET ((0x0093 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_MEMPD_ON_C_SET ((0x0094 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_MEMPD_ON_D_SET ((0x0095 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_MEMPD_STS ((0x0096 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_FSM_STS0 ((0x0097 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_FSM_STS1 ((0x0098 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_FSM_STS2 ((0x0099 << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_FSM_START_OFF ((0x009d << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_FSM_START_ON ((0x009e << 2) + 0xfe00c000)
#define PWRCTRL_CPU1_FSM_JUMP ((0x009f << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_AUTO_OFF_CTRL0 ((0x00a0 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_AUTO_OFF_CTRL1 ((0x00a1 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_AUTO_OFF_CTRL2 ((0x00a2 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_AUTO_OFF_CTRL3 ((0x00a3 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_AUTO_OFF_CTRL4 ((0x00a4 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_TIMER_TH_01 ((0x00a8 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_TIMER_TH_23 ((0x00a9 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_TIMER_TH_45 ((0x00aa << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_TIMER_TH_67 ((0x00ab << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_TIMER_TH_89 ((0x00ac << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_IRQ_MASK0 ((0x00b0 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_IRQ_MASK1 ((0x00b1 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_IRQ_MASK2 ((0x00b2 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_IRQ_MASK3 ((0x00b3 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_IRQ_MASK4 ((0x00b4 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_IRQ_MASK5 ((0x00b5 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_IRQ_MASK6 ((0x00b6 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_IRQ_MASK7 ((0x00b7 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_MEMPD_INIT_SET ((0x00c0 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_MEMPD_OFF_SET ((0x00c1 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_MEMPD_ON_A_SET ((0x00c2 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_MEMPD_ON_B_SET ((0x00c3 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_MEMPD_ON_C_SET ((0x00c4 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_MEMPD_ON_D_SET ((0x00c5 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_MEMPD_STS ((0x00c6 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_FSM_STS0 ((0x00c7 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_FSM_STS1 ((0x00c8 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_FSM_STS2 ((0x00c9 << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_FSM_START_OFF ((0x00cd << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_FSM_START_ON ((0x00ce << 2) + 0xfe00c000)
#define PWRCTRL_CPU2_FSM_JUMP ((0x00cf << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_AUTO_OFF_CTRL0 ((0x00d0 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_AUTO_OFF_CTRL1 ((0x00d1 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_AUTO_OFF_CTRL2 ((0x00d2 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_AUTO_OFF_CTRL3 ((0x00d3 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_AUTO_OFF_CTRL4 ((0x00d4 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_TIMER_TH_01 ((0x00d8 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_TIMER_TH_23 ((0x00d9 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_TIMER_TH_45 ((0x00da << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_TIMER_TH_67 ((0x00db << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_TIMER_TH_89 ((0x00dc << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_IRQ_MASK0 ((0x00e0 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_IRQ_MASK1 ((0x00e1 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_IRQ_MASK2 ((0x00e2 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_IRQ_MASK3 ((0x00e3 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_IRQ_MASK4 ((0x00e4 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_IRQ_MASK5 ((0x00e5 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_IRQ_MASK6 ((0x00e6 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_IRQ_MASK7 ((0x00e7 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_MEMPD_INIT_SET ((0x00f0 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_MEMPD_OFF_SET ((0x00f1 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_MEMPD_ON_A_SET ((0x00f2 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_MEMPD_ON_B_SET ((0x00f3 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_MEMPD_ON_C_SET ((0x00f4 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_MEMPD_ON_D_SET ((0x00f5 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_MEMPD_STS ((0x00f6 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_FSM_STS0 ((0x00f7 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_FSM_STS1 ((0x00f8 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_FSM_STS2 ((0x00f9 << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_FSM_START_OFF ((0x00fd << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_FSM_START_ON ((0x00fe << 2) + 0xfe00c000)
#define PWRCTRL_CPU3_FSM_JUMP ((0x00ff << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_AUTO_OFF_CTRL0 ((0x0100 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_AUTO_OFF_CTRL1 ((0x0101 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_AUTO_OFF_CTRL2 ((0x0102 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_AUTO_OFF_CTRL3 ((0x0103 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_AUTO_OFF_CTRL4 ((0x0104 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_TIMER_TH_01 ((0x0108 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_TIMER_TH_23 ((0x0109 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_TIMER_TH_45 ((0x010a << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_TIMER_TH_67 ((0x010b << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_TIMER_TH_89 ((0x010c << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_IRQ_MASK0 ((0x0110 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_IRQ_MASK1 ((0x0111 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_IRQ_MASK2 ((0x0112 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_IRQ_MASK3 ((0x0113 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_IRQ_MASK4 ((0x0114 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_IRQ_MASK5 ((0x0115 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_IRQ_MASK6 ((0x0116 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_IRQ_MASK7 ((0x0117 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_MEMPD_INIT_SET ((0x0120 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_MEMPD_OFF_SET ((0x0121 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_MEMPD_ON_A_SET ((0x0122 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_MEMPD_ON_B_SET ((0x0123 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_MEMPD_ON_C_SET ((0x0124 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_MEMPD_ON_D_SET ((0x0125 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_MEMPD_STS ((0x0126 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_FSM_STS0 ((0x0127 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_FSM_STS1 ((0x0128 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_FSM_STS2 ((0x0129 << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_FSM_START_OFF ((0x012d << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_FSM_START_ON ((0x012e << 2) + 0xfe00c000)
#define PWRCTRL_CPUTOP_FSM_JUMP ((0x012f << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_AUTO_OFF_CTRL0 ((0x0130 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_AUTO_OFF_CTRL1 ((0x0131 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_AUTO_OFF_CTRL2 ((0x0132 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_AUTO_OFF_CTRL3 ((0x0133 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_AUTO_OFF_CTRL4 ((0x0134 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_TIMER_TH_01 ((0x0138 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_TIMER_TH_23 ((0x0139 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_TIMER_TH_45 ((0x013a << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_TIMER_TH_67 ((0x013b << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_TIMER_TH_89 ((0x013c << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_IRQ_MASK0 ((0x0140 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_IRQ_MASK1 ((0x0141 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_IRQ_MASK2 ((0x0142 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_IRQ_MASK3 ((0x0143 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_IRQ_MASK4 ((0x0144 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_IRQ_MASK5 ((0x0145 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_IRQ_MASK6 ((0x0146 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_IRQ_MASK7 ((0x0147 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_MEMPD_INIT_SET ((0x0150 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_MEMPD_OFF_SET ((0x0151 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_MEMPD_ON_A_SET ((0x0152 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_MEMPD_ON_B_SET ((0x0153 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_MEMPD_ON_C_SET ((0x0154 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_MEMPD_ON_D_SET ((0x0155 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_MEMPD_STS ((0x0156 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_FSM_STS0 ((0x0157 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_FSM_STS1 ((0x0158 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_FSM_STS2 ((0x0159 << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_FSM_START_OFF ((0x015d << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_FSM_START_ON ((0x015e << 2) + 0xfe00c000)
#define PWRCTRL_DSPA_FSM_JUMP ((0x015f << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_AUTO_OFF_CTRL0 ((0x0160 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_AUTO_OFF_CTRL1 ((0x0161 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_AUTO_OFF_CTRL2 ((0x0162 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_AUTO_OFF_CTRL3 ((0x0163 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_AUTO_OFF_CTRL4 ((0x0164 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_TIMER_TH_01 ((0x0168 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_TIMER_TH_23 ((0x0169 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_TIMER_TH_45 ((0x016a << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_TIMER_TH_67 ((0x016b << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_TIMER_TH_89 ((0x016c << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_IRQ_MASK0 ((0x0170 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_IRQ_MASK1 ((0x0171 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_IRQ_MASK2 ((0x0172 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_IRQ_MASK3 ((0x0173 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_IRQ_MASK4 ((0x0174 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_IRQ_MASK5 ((0x0175 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_IRQ_MASK6 ((0x0176 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_IRQ_MASK7 ((0x0177 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_MEMPD_INIT_SET ((0x0180 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_MEMPD_OFF_SET ((0x0181 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_MEMPD_ON_A_SET ((0x0182 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_MEMPD_ON_B_SET ((0x0183 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_MEMPD_ON_C_SET ((0x0184 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_MEMPD_ON_D_SET ((0x0185 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_MEMPD_STS ((0x0186 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_FSM_STS0 ((0x0187 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_FSM_STS1 ((0x0188 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_FSM_STS2 ((0x0189 << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_FSM_START_OFF ((0x018d << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_FSM_START_ON ((0x018e << 2) + 0xfe00c000)
#define PWRCTRL_AOCPU_FSM_JUMP ((0x018f << 2) + 0xfe00c000)
//========================================================================
// RSA
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe042000
// -----------------------------------------------
#define RSA_BASE ((0x0000 << 2) + 0xfe042000)
//========================================================================
//  AOCPU
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe09c000
// -----------------------------------------------
#define AOCPU_CPU_CTRL0 ((0x0000 << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_CPU_CTRL1 ((0x0001 << 2) + 0xfe09c000)
// Bit 31:11-       0   - n205 address shift, 1: 0x8000_0000~0x4000_0000
// Bit 30:11-       0   - reserved
// Bit 10   -       0   - gate by sleep, 1: gate, 0: free run
// Bit  9   -       0   - RXEV for riscv input refer riscv doc
// Bit  8   -       0   - reserved
// Bit   7:6-       0   - n205_debug_sel,aocpu_core_status0 info select
// Bit   5:2-       0   - reserved
// Bit 1    -       0   - n205_i_dbg_stop
// Bit 0    -       0   - n205_pc_enable
#define AOCPU_CPU_CTRL2 ((0x0002 << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_CPU_CTRL3 ((0x0003 << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_CPU_CTRL4 ((0x0004 << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_CPU_CTRL5 ((0x0005 << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_CPU_STS0 ((0x000a << 2) + 0xfe09c000)
// Bit 31:0 -       0   - n205_debug_sel==0 : n205_trace_casuse, 1:n205_trace_tval,
// 2:n205_trace_iaddr, 3:n205_trace_instr
#define AOCPU_CPU_STS1 ((0x000b << 2) + 0xfe09c000)
// Bit 31   -       0   - n205_core_sleep_value
// Bit 30:29-       0   - n205_trace_priv
// Bit 28:20-       0   - reserved
// Bit 19   -       0   - n205_core_wfi_mode
// Bit 18   -       0   - n205_trace_ivalid
// Bit 17   -       0   - n205_trace_iexception
// Bit 16   -       0   - n205_trace_interrupt
// Bit 15:0 -       0   - reserved
#define AOCPU_CPU_STS2 ((0x000c << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_CPU_STS3 ((0x000d << 2) + 0xfe09c000)
// Bit 31   -       0   - n205_hart_halted
// Bit 30   -       0   - n205_ndmreset
// Bit 29   -       0   - n205_dmactive
// Bit 28:0 -       0   - reserved
#define AOCPU_CPU_VECTOR ((0x000f << 2) + 0xfe09c000)
// Bit 31:0-   0x1000_0000   - reserved
#define AOCPU_IRQ_SEL0 ((0x0010 << 2) + 0xfe09c000)
// Bit 31:24-       0   - INTISR03 interrupt source select in int_map
// Bit 23:16-       0   - INTISR02 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR01 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR00 interrupt source select in int_map
#define AOCPU_IRQ_SEL1 ((0x0011 << 2) + 0xfe09c000)
// Bit 31:24-       0   - INTISR07 interrupt source select in int_map
// Bit 23:16-       0   - INTISR06 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR05 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR04 interrupt source select in int_map
#define AOCPU_IRQ_SEL2 ((0x0012 << 2) + 0xfe09c000)
// Bit 31:24-       0   - INTISR11 interrupt source select in int_map
// Bit 23:16-       0   - INTISR10 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR09 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR08 interrupt source select in int_map
#define AOCPU_IRQ_SEL3 ((0x0013 << 2) + 0xfe09c000)
// Bit 31:24-       0   - INTISR15 interrupt source select in int_map
// Bit 23:16-       0   - INTISR14 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR13 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR12 interrupt source select in int_map
#define AOCPU_IRQ_SEL4 ((0x0014 << 2) + 0xfe09c000)
// Bit 31:24-       0   - INTISR19 interrupt source select in int_map
// Bit 23:16-       0   - INTISR18 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR17 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR16 interrupt source select in int_map
#define AOCPU_IRQ_SEL5 ((0x0015 << 2) + 0xfe09c000)
// Bit 31:24-       0   - INTISR23 interrupt source select in int_map
// Bit 23:16-       0   - INTISR22 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR21 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR20 interrupt source select in int_map
#define AOCPU_IRQ_SEL6 ((0x0016 << 2) + 0xfe09c000)
// Bit 31:24-       0   - INTISR27 interrupt source select in int_map
// Bit 23:16-       0   - INTISR26 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR25 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR24 interrupt source select in int_map
#define AOCPU_IRQ_SEL7 ((0x0017 << 2) + 0xfe09c000)
// Bit 31:24-       0   - INTISR31 interrupt source select in int_map
// Bit 23:16-       0   - INTISR30 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR29 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR28 interrupt source select in int_map
#define AOCPU_STS00_BYCPU ((0x0018 << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_STS01_BYCPU ((0x0019 << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_STS02_BYCPU ((0x001a << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_STS03_BYCPU ((0x001b << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_STS04_BYCPU ((0x001c << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_STS05_BYCPU ((0x001d << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_STS06_BYCPU ((0x001e << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
#define AOCPU_STS07_BYCPU ((0x001f << 2) + 0xfe09c000)
// Bit 31:0-       0   - reserved
//========================================================================
//  AUCPU
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe09e000
// -----------------------------------------------
#define AUCPU_CPU_CTRL0 ((0x0000 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_CPU_CTRL1 ((0x0001 << 2) + 0xfe09e000)
// Bit 31:11-       0   - reserved
// Bit 10   -       0   - gate by sleep
// Bit 9    -       0   - RXEV
// Bit 8    -       0   - reserved
// Bit 7:6  -       0   - n205_debug_sel,aucpu_core_status0 info select
// Bit 5:2  -       0   - reserved
// Bit 1    -       0   - n205_i_dbg_stop
// Bit 0    -       0   - n205_pc_enable
#define AUCPU_CPU_CTRL2 ((0x0002 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_CPU_CTRL3 ((0x0003 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_CPU_CTRL4 ((0x0004 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_CPU_CTRL5 ((0x0005 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_CPU_STS0 ((0x000a << 2) + 0xfe09e000)
// Bit 31:0 -       0   - n205_debug_sel==0 : n205_trace_casuse, 1:n205_trace_tval,
// 2:n205_trace_iaddr, 3:n205_trace_instr
#define AUCPU_CPU_STS1 ((0x000b << 2) + 0xfe09e000)
// Bit 31   -       0   - n205_core_sleep_value
// Bit 30:29-       0   - n205_trace_priv
// Bit 28:20-       0   - reserved
// Bit 19   -       0   - n205_core_wfi_mode
// Bit 18   -       0   - n205_trace_ivalid
// Bit 17   -       0   - n205_trace_iexception
// Bit 16   -       0   - n205_trace_interrupt
// Bit 15:0 -       0   - reserved
#define AUCPU_CPU_STS2 ((0x000c << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_CPU_STS3 ((0x000d << 2) + 0xfe09e000)
// Bit 31   -       0   - n205_hart_halted
// Bit 30   -       0   - n205_ndmreset
// Bit 29   -       0   - n205_dmactive
// Bit 28:0 -       0   - reserved
#define AUCPU_DMA_APB_SEL ((0x0010 << 2) + 0xfe09e000)
// Bit 31:30-       0   - reserved
// Bit 0    -       0   - 1: riscv control dma, 0: ap control dma
#define AUCPU_IRQ_AP2RISCV ((0x0011 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - AP cpu send irq to riscv
#define AUCPU_IRQ_RISCV2AP ((0x0012 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - riscv send irq to AP
#define AUCPU_STS00_BY_AP ((0x0020 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS01_BY_AP ((0x0021 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS02_BY_AP ((0x0022 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS03_BY_AP ((0x0023 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS04_BY_AP ((0x0024 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS05_BY_AP ((0x0025 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS06_BY_AP ((0x0026 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS07_BY_AP ((0x0027 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS08_BY_AP ((0x0028 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS09_BY_AP ((0x0029 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS10_BY_AP ((0x002a << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS11_BY_AP ((0x002b << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS12_BY_AP ((0x002c << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS13_BY_AP ((0x002d << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS14_BY_AP ((0x002e << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS15_BY_AP ((0x002f << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS16_BY_AP ((0x0030 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS17_BY_AP ((0x0031 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS18_BY_AP ((0x0032 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS19_BY_AP ((0x0033 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS20_BY_AP ((0x0034 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS21_BY_AP ((0x0035 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS22_BY_AP ((0x0036 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS23_BY_AP ((0x0037 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS24_BY_AP ((0x0038 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS25_BY_AP ((0x0039 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS26_BY_AP ((0x003a << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS27_BY_AP ((0x003b << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS28_BY_AP ((0x003c << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS29_BY_AP ((0x003d << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS30_BY_AP ((0x003e << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS31_BY_AP ((0x003f << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS00_BY_RISCV ((0x0040 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS01_BY_RISCV ((0x0041 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS02_BY_RISCV ((0x0042 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS03_BY_RISCV ((0x0043 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS04_BY_RISCV ((0x0044 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS05_BY_RISCV ((0x0045 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS06_BY_RISCV ((0x0046 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS07_BY_RISCV ((0x0047 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS08_BY_RISCV ((0x0048 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS09_BY_RISCV ((0x0049 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS10_BY_RISCV ((0x004a << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS11_BY_RISCV ((0x004b << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS12_BY_RISCV ((0x004c << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS13_BY_RISCV ((0x004d << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS14_BY_RISCV ((0x004e << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS15_BY_RISCV ((0x004f << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS16_BY_RISCV ((0x0050 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS17_BY_RISCV ((0x0051 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS18_BY_RISCV ((0x0052 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS19_BY_RISCV ((0x0053 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS20_BY_RISCV ((0x0054 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS21_BY_RISCV ((0x0055 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS22_BY_RISCV ((0x0056 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS23_BY_RISCV ((0x0057 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS24_BY_RISCV ((0x0058 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS25_BY_RISCV ((0x0059 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS26_BY_RISCV ((0x005a << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS27_BY_RISCV ((0x005b << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS28_BY_RISCV ((0x005c << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS29_BY_RISCV ((0x005d << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS30_BY_RISCV ((0x005e << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_STS31_BY_RISCV ((0x005f << 2) + 0xfe09e000)
// Bit 31:0 -       0   - reserved
#define AUCPU_DEMUX_STS_BY_RISCV ((0x0060 << 2) + 0xfe09e000)
// Bit 31   -       0   - read only, demux status updated
// Bit 31:8 -       0   - reserved
// Bit  7:0 -       0   - read demux chn select
#define AUCPU_DEMUX_STS0 ((0x0061 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - demux status 0
#define AUCPU_DEMUX_STS1 ((0x0062 << 2) + 0xfe09e000)
// Bit 31:0 -       0   - demux status 1
//========================================================================
//  AXI_SRAM
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe090000
// -----------------------------------------------
#define SRAM_RANGE0_STA ((0x0000 << 2) + 0xfe090000)
#define SRAM_RANGE1_STA ((0x0001 << 2) + 0xfe090000)
#define SRAM_RANGE2_STA ((0x0002 << 2) + 0xfe090000)
#define SRAM_RANGE3_STA ((0x0003 << 2) + 0xfe090000)
#define SRAM_RANGE4_STA ((0x0004 << 2) + 0xfe090000)
#define SRAM_RANGE5_STA ((0x0005 << 2) + 0xfe090000)
#define SRAM_RANGE6_STA ((0x0006 << 2) + 0xfe090000)
#define SRAM_RANGE7_STA ((0x0007 << 2) + 0xfe090000)
#define SRAM_RANGE8_STA ((0x0008 << 2) + 0xfe090000)
#define SRAM_RANGE9_STA ((0x0009 << 2) + 0xfe090000)
#define SRAM_RANGE10_STA ((0x000a << 2) + 0xfe090000)
#define SRAM_RANGE11_STA ((0x000b << 2) + 0xfe090000)
#define SRAM_RANGE12_STA ((0x000c << 2) + 0xfe090000)
#define SRAM_RANGE13_STA ((0x000d << 2) + 0xfe090000)
#define SRAM_RANGE14_STA ((0x000e << 2) + 0xfe090000)
#define SRAM_RANGE0_EDA ((0x000f << 2) + 0xfe090000)
#define SRAM_RANGE1_EDA ((0x0010 << 2) + 0xfe090000)
#define SRAM_RANGE2_EDA ((0x0011 << 2) + 0xfe090000)
#define SRAM_RANGE3_EDA ((0x0012 << 2) + 0xfe090000)
#define SRAM_RANGE4_EDA ((0x0013 << 2) + 0xfe090000)
#define SRAM_RANGE5_EDA ((0x0014 << 2) + 0xfe090000)
#define SRAM_RANGE6_EDA ((0x0015 << 2) + 0xfe090000)
#define SRAM_RANGE7_EDA ((0x0016 << 2) + 0xfe090000)
#define SRAM_RANGE8_EDA ((0x0017 << 2) + 0xfe090000)
#define SRAM_RANGE9_EDA ((0x0018 << 2) + 0xfe090000)
#define SRAM_RANGE10_EDA ((0x0019 << 2) + 0xfe090000)
#define SRAM_RANGE11_EDA ((0x001a << 2) + 0xfe090000)
#define SRAM_RANGE12_EDA ((0x001b << 2) + 0xfe090000)
#define SRAM_RANGE13_EDA ((0x001c << 2) + 0xfe090000)
#define SRAM_RANGE14_EDA ((0x001d << 2) + 0xfe090000)
#define SRAM_RANGE0_READ_CTRL0 ((0x001e << 2) + 0xfe090000)
#define SRAM_RANGE1_READ_CTRL0 ((0x001f << 2) + 0xfe090000)
#define SRAM_RANGE2_READ_CTRL0 ((0x0020 << 2) + 0xfe090000)
#define SRAM_RANGE3_READ_CTRL0 ((0x0021 << 2) + 0xfe090000)
#define SRAM_RANGE4_READ_CTRL0 ((0x0022 << 2) + 0xfe090000)
#define SRAM_RANGE5_READ_CTRL0 ((0x0023 << 2) + 0xfe090000)
#define SRAM_RANGE6_READ_CTRL0 ((0x0024 << 2) + 0xfe090000)
#define SRAM_RANGE7_READ_CTRL0 ((0x0025 << 2) + 0xfe090000)
#define SRAM_RANGE8_READ_CTRL0 ((0x0026 << 2) + 0xfe090000)
#define SRAM_RANGE9_READ_CTRL0 ((0x0027 << 2) + 0xfe090000)
#define SRAM_RANGE10_READ_CTRL0 ((0x0028 << 2) + 0xfe090000)
#define SRAM_RANGE11_READ_CTRL0 ((0x0029 << 2) + 0xfe090000)
#define SRAM_RANGE12_READ_CTRL0 ((0x002a << 2) + 0xfe090000)
#define SRAM_RANGE13_READ_CTRL0 ((0x002b << 2) + 0xfe090000)
#define SRAM_RANGE14_READ_CTRL0 ((0x002c << 2) + 0xfe090000)
#define SRAM_RANGE15_READ_CTRL0 ((0x002d << 2) + 0xfe090000)
#define SRAM_RANGE0_WRITE_CTRL0 ((0x002e << 2) + 0xfe090000)
#define SRAM_RANGE1_WRITE_CTRL0 ((0x002f << 2) + 0xfe090000)
#define SRAM_RANGE2_WRITE_CTRL0 ((0x0030 << 2) + 0xfe090000)
#define SRAM_RANGE3_WRITE_CTRL0 ((0x0031 << 2) + 0xfe090000)
#define SRAM_RANGE4_WRITE_CTRL0 ((0x0032 << 2) + 0xfe090000)
#define SRAM_RANGE5_WRITE_CTRL0 ((0x0033 << 2) + 0xfe090000)
#define SRAM_RANGE6_WRITE_CTRL0 ((0x0034 << 2) + 0xfe090000)
#define SRAM_RANGE7_WRITE_CTRL0 ((0x0035 << 2) + 0xfe090000)
#define SRAM_RANGE8_WRITE_CTRL0 ((0x0036 << 2) + 0xfe090000)
#define SRAM_RANGE9_WRITE_CTRL0 ((0x0037 << 2) + 0xfe090000)
#define SRAM_RANGE10_WRITE_CTRL0 ((0x0038 << 2) + 0xfe090000)
#define SRAM_RANGE11_WRITE_CTRL0 ((0x0039 << 2) + 0xfe090000)
#define SRAM_RANGE12_WRITE_CTRL0 ((0x003a << 2) + 0xfe090000)
#define SRAM_RANGE13_WRITE_CTRL0 ((0x003b << 2) + 0xfe090000)
#define SRAM_RANGE14_WRITE_CTRL0 ((0x003c << 2) + 0xfe090000)
#define SRAM_RANGE15_WRITE_CTRL0 ((0x003d << 2) + 0xfe090000)
#define SRAM_RANGE0_READ_CTRL1 ((0x003e << 2) + 0xfe090000)
#define SRAM_RANGE1_READ_CTRL1 ((0x003f << 2) + 0xfe090000)
#define SRAM_RANGE2_READ_CTRL1 ((0x0040 << 2) + 0xfe090000)
#define SRAM_RANGE3_READ_CTRL1 ((0x0041 << 2) + 0xfe090000)
#define SRAM_RANGE4_READ_CTRL1 ((0x0042 << 2) + 0xfe090000)
#define SRAM_RANGE5_READ_CTRL1 ((0x0043 << 2) + 0xfe090000)
#define SRAM_RANGE6_READ_CTRL1 ((0x0044 << 2) + 0xfe090000)
#define SRAM_RANGE7_READ_CTRL1 ((0x0045 << 2) + 0xfe090000)
#define SRAM_RANGE8_READ_CTRL1 ((0x0046 << 2) + 0xfe090000)
#define SRAM_RANGE9_READ_CTRL1 ((0x0047 << 2) + 0xfe090000)
#define SRAM_RANGE10_READ_CTRL1 ((0x0048 << 2) + 0xfe090000)
#define SRAM_RANGE11_READ_CTRL1 ((0x0049 << 2) + 0xfe090000)
#define SRAM_RANGE12_READ_CTRL1 ((0x004a << 2) + 0xfe090000)
#define SRAM_RANGE13_READ_CTRL1 ((0x004b << 2) + 0xfe090000)
#define SRAM_RANGE14_READ_CTRL1 ((0x004c << 2) + 0xfe090000)
#define SRAM_RANGE15_READ_CTRL1 ((0x004d << 2) + 0xfe090000)
#define SRAM_RANGE0_WRITE_CTRL1 ((0x004e << 2) + 0xfe090000)
#define SRAM_RANGE1_WRITE_CTRL1 ((0x004f << 2) + 0xfe090000)
#define SRAM_RANGE2_WRITE_CTRL1 ((0x0050 << 2) + 0xfe090000)
#define SRAM_RANGE3_WRITE_CTRL1 ((0x0051 << 2) + 0xfe090000)
#define SRAM_RANGE4_WRITE_CTRL1 ((0x0052 << 2) + 0xfe090000)
#define SRAM_RANGE5_WRITE_CTRL1 ((0x0053 << 2) + 0xfe090000)
#define SRAM_RANGE6_WRITE_CTRL1 ((0x0054 << 2) + 0xfe090000)
#define SRAM_RANGE7_WRITE_CTRL1 ((0x0055 << 2) + 0xfe090000)
#define SRAM_RANGE8_WRITE_CTRL1 ((0x0056 << 2) + 0xfe090000)
#define SRAM_RANGE9_WRITE_CTRL1 ((0x0057 << 2) + 0xfe090000)
#define SRAM_RANGE10_WRITE_CTRL1 ((0x0058 << 2) + 0xfe090000)
#define SRAM_RANGE11_WRITE_CTRL1 ((0x0059 << 2) + 0xfe090000)
#define SRAM_RANGE12_WRITE_CTRL1 ((0x005a << 2) + 0xfe090000)
#define SRAM_RANGE13_WRITE_CTRL1 ((0x005b << 2) + 0xfe090000)
#define SRAM_RANGE14_WRITE_CTRL1 ((0x005c << 2) + 0xfe090000)
#define SRAM_RANGE15_WRITE_CTRL1 ((0x005d << 2) + 0xfe090000)
#define SRAM_GLOBAL_READ_CTRL0 ((0x005e << 2) + 0xfe090000)
#define SRAM_GLOBAL_READ_CTRL1 ((0x005f << 2) + 0xfe090000)
#define SRAM_GLOBAL_WRITE_CTRL0 ((0x0060 << 2) + 0xfe090000)
#define SRAM_GLOBAL_WRITE_CTRL1 ((0x0061 << 2) + 0xfe090000)
#define SRAM_SEC_CTRL0 ((0x0062 << 2) + 0xfe090000)
#define SRAM_REG_LOCK0 ((0x0063 << 2) + 0xfe090000)
#define SRAM_REG_LOCK1 ((0x0064 << 2) + 0xfe090000)
#define SRAM_REG_LOCK2 ((0x0065 << 2) + 0xfe090000)
#define SRAM_GLOBAL_READ_CTRL0_LOCK ((0x0066 << 2) + 0xfe090000)
#define SRAM_GLOBAL_READ_CTRL1_LOCK ((0x0067 << 2) + 0xfe090000)
#define SRAM_GLOBAL_WRITE_CTRL0_LOCK ((0x0068 << 2) + 0xfe090000)
#define SRAM_GLOBAL_WRITE_CTRL1_LOCK ((0x0069 << 2) + 0xfe090000)
#define SRAM_SEC_CTRL0_LOCK ((0x006a << 2) + 0xfe090000)
#define SRAM_STATUS_REG ((0x006b << 2) + 0xfe090000)
#define SRAM_INIT_DLY_TCNT ((0x006c << 2) + 0xfe090000)
//========================================================================
//  AXI_SRAM B
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe092000
// -----------------------------------------------
#define SRAM_B_RANGE0_STA ((0x0000 << 2) + 0xfe092000)
#define SRAM_B_RANGE1_STA ((0x0001 << 2) + 0xfe092000)
#define SRAM_B_RANGE2_STA ((0x0002 << 2) + 0xfe092000)
#define SRAM_B_RANGE3_STA ((0x0003 << 2) + 0xfe092000)
#define SRAM_B_RANGE4_STA ((0x0004 << 2) + 0xfe092000)
#define SRAM_B_RANGE5_STA ((0x0005 << 2) + 0xfe092000)
#define SRAM_B_RANGE6_STA ((0x0006 << 2) + 0xfe092000)
#define SRAM_B_RANGE7_STA ((0x0007 << 2) + 0xfe092000)
#define SRAM_B_RANGE8_STA ((0x0008 << 2) + 0xfe092000)
#define SRAM_B_RANGE9_STA ((0x0009 << 2) + 0xfe092000)
#define SRAM_B_RANGE10_STA ((0x000a << 2) + 0xfe092000)
#define SRAM_B_RANGE11_STA ((0x000b << 2) + 0xfe092000)
#define SRAM_B_RANGE12_STA ((0x000c << 2) + 0xfe092000)
#define SRAM_B_RANGE13_STA ((0x000d << 2) + 0xfe092000)
#define SRAM_B_RANGE14_STA ((0x000e << 2) + 0xfe092000)
#define SRAM_B_RANGE0_EDA ((0x000f << 2) + 0xfe092000)
#define SRAM_B_RANGE1_EDA ((0x0010 << 2) + 0xfe092000)
#define SRAM_B_RANGE2_EDA ((0x0011 << 2) + 0xfe092000)
#define SRAM_B_RANGE3_EDA ((0x0012 << 2) + 0xfe092000)
#define SRAM_B_RANGE4_EDA ((0x0013 << 2) + 0xfe092000)
#define SRAM_B_RANGE5_EDA ((0x0014 << 2) + 0xfe092000)
#define SRAM_B_RANGE6_EDA ((0x0015 << 2) + 0xfe092000)
#define SRAM_B_RANGE7_EDA ((0x0016 << 2) + 0xfe092000)
#define SRAM_B_RANGE8_EDA ((0x0017 << 2) + 0xfe092000)
#define SRAM_B_RANGE9_EDA ((0x0018 << 2) + 0xfe092000)
#define SRAM_B_RANGE10_EDA ((0x0019 << 2) + 0xfe092000)
#define SRAM_B_RANGE11_EDA ((0x001a << 2) + 0xfe092000)
#define SRAM_B_RANGE12_EDA ((0x001b << 2) + 0xfe092000)
#define SRAM_B_RANGE13_EDA ((0x001c << 2) + 0xfe092000)
#define SRAM_B_RANGE14_EDA ((0x001d << 2) + 0xfe092000)
#define SRAM_B_RANGE0_READ_CTRL0 ((0x001e << 2) + 0xfe092000)
#define SRAM_B_RANGE1_READ_CTRL0 ((0x001f << 2) + 0xfe092000)
#define SRAM_B_RANGE2_READ_CTRL0 ((0x0020 << 2) + 0xfe092000)
#define SRAM_B_RANGE3_READ_CTRL0 ((0x0021 << 2) + 0xfe092000)
#define SRAM_B_RANGE4_READ_CTRL0 ((0x0022 << 2) + 0xfe092000)
#define SRAM_B_RANGE5_READ_CTRL0 ((0x0023 << 2) + 0xfe092000)
#define SRAM_B_RANGE6_READ_CTRL0 ((0x0024 << 2) + 0xfe092000)
#define SRAM_B_RANGE7_READ_CTRL0 ((0x0025 << 2) + 0xfe092000)
#define SRAM_B_RANGE8_READ_CTRL0 ((0x0026 << 2) + 0xfe092000)
#define SRAM_B_RANGE9_READ_CTRL0 ((0x0027 << 2) + 0xfe092000)
#define SRAM_B_RANGE10_READ_CTRL0 ((0x0028 << 2) + 0xfe092000)
#define SRAM_B_RANGE11_READ_CTRL0 ((0x0029 << 2) + 0xfe092000)
#define SRAM_B_RANGE12_READ_CTRL0 ((0x002a << 2) + 0xfe092000)
#define SRAM_B_RANGE13_READ_CTRL0 ((0x002b << 2) + 0xfe092000)
#define SRAM_B_RANGE14_READ_CTRL0 ((0x002c << 2) + 0xfe092000)
#define SRAM_B_RANGE15_READ_CTRL0 ((0x002d << 2) + 0xfe092000)
#define SRAM_B_RANGE0_WRITE_CTRL0 ((0x002e << 2) + 0xfe092000)
#define SRAM_B_RANGE1_WRITE_CTRL0 ((0x002f << 2) + 0xfe092000)
#define SRAM_B_RANGE2_WRITE_CTRL0 ((0x0030 << 2) + 0xfe092000)
#define SRAM_B_RANGE3_WRITE_CTRL0 ((0x0031 << 2) + 0xfe092000)
#define SRAM_B_RANGE4_WRITE_CTRL0 ((0x0032 << 2) + 0xfe092000)
#define SRAM_B_RANGE5_WRITE_CTRL0 ((0x0033 << 2) + 0xfe092000)
#define SRAM_B_RANGE6_WRITE_CTRL0 ((0x0034 << 2) + 0xfe092000)
#define SRAM_B_RANGE7_WRITE_CTRL0 ((0x0035 << 2) + 0xfe092000)
#define SRAM_B_RANGE8_WRITE_CTRL0 ((0x0036 << 2) + 0xfe092000)
#define SRAM_B_RANGE9_WRITE_CTRL0 ((0x0037 << 2) + 0xfe092000)
#define SRAM_B_RANGE10_WRITE_CTRL0 ((0x0038 << 2) + 0xfe092000)
#define SRAM_B_RANGE11_WRITE_CTRL0 ((0x0039 << 2) + 0xfe092000)
#define SRAM_B_RANGE12_WRITE_CTRL0 ((0x003a << 2) + 0xfe092000)
#define SRAM_B_RANGE13_WRITE_CTRL0 ((0x003b << 2) + 0xfe092000)
#define SRAM_B_RANGE14_WRITE_CTRL0 ((0x003c << 2) + 0xfe092000)
#define SRAM_B_RANGE15_WRITE_CTRL0 ((0x003d << 2) + 0xfe092000)
#define SRAM_B_RANGE0_READ_CTRL1 ((0x003e << 2) + 0xfe092000)
#define SRAM_B_RANGE1_READ_CTRL1 ((0x003f << 2) + 0xfe092000)
#define SRAM_B_RANGE2_READ_CTRL1 ((0x0040 << 2) + 0xfe092000)
#define SRAM_B_RANGE3_READ_CTRL1 ((0x0041 << 2) + 0xfe092000)
#define SRAM_B_RANGE4_READ_CTRL1 ((0x0042 << 2) + 0xfe092000)
#define SRAM_B_RANGE5_READ_CTRL1 ((0x0043 << 2) + 0xfe092000)
#define SRAM_B_RANGE6_READ_CTRL1 ((0x0044 << 2) + 0xfe092000)
#define SRAM_B_RANGE7_READ_CTRL1 ((0x0045 << 2) + 0xfe092000)
#define SRAM_B_RANGE8_READ_CTRL1 ((0x0046 << 2) + 0xfe092000)
#define SRAM_B_RANGE9_READ_CTRL1 ((0x0047 << 2) + 0xfe092000)
#define SRAM_B_RANGE10_READ_CTRL1 ((0x0048 << 2) + 0xfe092000)
#define SRAM_B_RANGE11_READ_CTRL1 ((0x0049 << 2) + 0xfe092000)
#define SRAM_B_RANGE12_READ_CTRL1 ((0x004a << 2) + 0xfe092000)
#define SRAM_B_RANGE13_READ_CTRL1 ((0x004b << 2) + 0xfe092000)
#define SRAM_B_RANGE14_READ_CTRL1 ((0x004c << 2) + 0xfe092000)
#define SRAM_B_RANGE15_READ_CTRL1 ((0x004d << 2) + 0xfe092000)
#define SRAM_B_RANGE0_WRITE_CTRL1 ((0x004e << 2) + 0xfe092000)
#define SRAM_B_RANGE1_WRITE_CTRL1 ((0x004f << 2) + 0xfe092000)
#define SRAM_B_RANGE2_WRITE_CTRL1 ((0x0050 << 2) + 0xfe092000)
#define SRAM_B_RANGE3_WRITE_CTRL1 ((0x0051 << 2) + 0xfe092000)
#define SRAM_B_RANGE4_WRITE_CTRL1 ((0x0052 << 2) + 0xfe092000)
#define SRAM_B_RANGE5_WRITE_CTRL1 ((0x0053 << 2) + 0xfe092000)
#define SRAM_B_RANGE6_WRITE_CTRL1 ((0x0054 << 2) + 0xfe092000)
#define SRAM_B_RANGE7_WRITE_CTRL1 ((0x0055 << 2) + 0xfe092000)
#define SRAM_B_RANGE8_WRITE_CTRL1 ((0x0056 << 2) + 0xfe092000)
#define SRAM_B_RANGE9_WRITE_CTRL1 ((0x0057 << 2) + 0xfe092000)
#define SRAM_B_RANGE10_WRITE_CTRL1 ((0x0058 << 2) + 0xfe092000)
#define SRAM_B_RANGE11_WRITE_CTRL1 ((0x0059 << 2) + 0xfe092000)
#define SRAM_B_RANGE12_WRITE_CTRL1 ((0x005a << 2) + 0xfe092000)
#define SRAM_B_RANGE13_WRITE_CTRL1 ((0x005b << 2) + 0xfe092000)
#define SRAM_B_RANGE14_WRITE_CTRL1 ((0x005c << 2) + 0xfe092000)
#define SRAM_B_RANGE15_WRITE_CTRL1 ((0x005d << 2) + 0xfe092000)
#define SRAM_B_GLOBAL_READ_CTRL0 ((0x005e << 2) + 0xfe092000)
#define SRAM_B_GLOBAL_READ_CTRL1 ((0x005f << 2) + 0xfe092000)
#define SRAM_B_GLOBAL_WRITE_CTRL0 ((0x0060 << 2) + 0xfe092000)
#define SRAM_B_GLOBAL_WRITE_CTRL1 ((0x0061 << 2) + 0xfe092000)
#define SRAM_B_SEC_CTRL0 ((0x0062 << 2) + 0xfe092000)
#define SRAM_B_REG_LOCK0 ((0x0063 << 2) + 0xfe092000)
#define SRAM_B_REG_LOCK1 ((0x0064 << 2) + 0xfe092000)
#define SRAM_B_REG_LOCK2 ((0x0065 << 2) + 0xfe092000)
#define SRAM_B_GLOBAL_READ_CTRL0_LOCK ((0x0066 << 2) + 0xfe092000)
#define SRAM_B_GLOBAL_READ_CTRL1_LOCK ((0x0067 << 2) + 0xfe092000)
#define SRAM_B_GLOBAL_WRITE_CTRL0_LOCK ((0x0068 << 2) + 0xfe092000)
#define SRAM_B_GLOBAL_WRITE_CTRL1_LOCK ((0x0069 << 2) + 0xfe092000)
#define SRAM_B_SEC_CTRL0_LOCK ((0x006a << 2) + 0xfe092000)
#define SRAM_B_STATUS_REG ((0x006b << 2) + 0xfe092000)
#define SRAM_B_INIT_DLY_TCNT ((0x006c << 2) + 0xfe092000)
//========================================================================
//  MAILBOX
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe006000
// -----------------------------------------------
#define MAILBOX_WR_MBOX00 ((0x0000 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX01 ((0x0020 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX02 ((0x0040 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX03 ((0x0060 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX04 ((0x0080 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX05 ((0x00a0 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX06 ((0x00c0 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX07 ((0x00e0 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX08 ((0x0100 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX09 ((0x0120 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX10 ((0x0140 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX11 ((0x0160 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX12 ((0x0180 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX13 ((0x01a0 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX14 ((0x01c0 << 2) + 0xfe006000)
#define MAILBOX_WR_MBOX15 ((0x01e0 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX00 ((0x0200 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX01 ((0x0220 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX02 ((0x0240 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX03 ((0x0260 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX04 ((0x0280 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX05 ((0x02a0 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX06 ((0x02c0 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX07 ((0x02e0 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX08 ((0x0300 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX09 ((0x0320 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX10 ((0x0340 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX11 ((0x0360 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX12 ((0x0380 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX13 ((0x03a0 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX14 ((0x03c0 << 2) + 0xfe006000)
#define MAILBOX_RD_MBOX15 ((0x03e0 << 2) + 0xfe006000)
#define MAILBOX_LOCK_BIT0 ((0x0400 << 2) + 0xfe006000)
#define MAILBOX_LOCK_BIT1 ((0x0401 << 2) + 0xfe006000)
#define MAILBOX_PROT_BIT0 ((0x0402 << 2) + 0xfe006000)
#define MAILBOX_PROT_BIT1 ((0x0403 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_IRQA_CLR ((0x0404 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_IRQB_CLR ((0x0405 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_IRQC_CLR ((0x0406 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_IRQD_CLR ((0x0407 << 2) + 0xfe006000)
#define MAILBOX_IRQA_MASK ((0x0408 << 2) + 0xfe006000)
#define MAILBOX_IRQB_MASK ((0x0409 << 2) + 0xfe006000)
#define MAILBOX_IRQC_MASK ((0x040a << 2) + 0xfe006000)
#define MAILBOX_IRQD_MASK ((0x040b << 2) + 0xfe006000)
#define MAILBOX_IRQ_TYPE ((0x040c << 2) + 0xfe006000)
#define MAILBOX_IRQA_CLR ((0x0410 << 2) + 0xfe006000)
#define MAILBOX_IRQB_CLR ((0x0411 << 2) + 0xfe006000)
#define MAILBOX_IRQC_CLR ((0x0412 << 2) + 0xfe006000)
#define MAILBOX_IRQD_CLR ((0x0413 << 2) + 0xfe006000)
#define MAILBOX_IRQA_STS ((0x0414 << 2) + 0xfe006000)
#define MAILBOX_IRQB_STS ((0x0415 << 2) + 0xfe006000)
#define MAILBOX_IRQC_STS ((0x0416 << 2) + 0xfe006000)
#define MAILBOX_IRQD_STS ((0x0417 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX00 ((0x0420 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX01 ((0x0421 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX02 ((0x0422 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX03 ((0x0423 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX04 ((0x0424 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX05 ((0x0425 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX06 ((0x0426 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX07 ((0x0427 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX08 ((0x0428 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX09 ((0x0429 << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX10 ((0x042a << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX11 ((0x042b << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX12 ((0x042c << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX13 ((0x042d << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX14 ((0x042e << 2) + 0xfe006000)
#define MAILBOX_ACCESS_EN_MBOX15 ((0x042f << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX00 ((0x0430 << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX01 ((0x0431 << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX02 ((0x0432 << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX03 ((0x0433 << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX04 ((0x0434 << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX05 ((0x0435 << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX06 ((0x0436 << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX07 ((0x0437 << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX08 ((0x0438 << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX09 ((0x0439 << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX10 ((0x043a << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX11 ((0x043b << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX12 ((0x043c << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX13 ((0x043d << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX14 ((0x043e << 2) + 0xfe006000)
#define MAILBOX_SET_MBOX15 ((0x043f << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX00 ((0x0440 << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX01 ((0x0441 << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX02 ((0x0442 << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX03 ((0x0443 << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX04 ((0x0444 << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX05 ((0x0445 << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX06 ((0x0446 << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX07 ((0x0447 << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX08 ((0x0448 << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX09 ((0x0449 << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX10 ((0x044a << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX11 ((0x044b << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX12 ((0x044c << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX13 ((0x044d << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX14 ((0x044e << 2) + 0xfe006000)
#define MAILBOX_CLR_MBOX15 ((0x044f << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX00 ((0x0450 << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX01 ((0x0451 << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX02 ((0x0452 << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX03 ((0x0453 << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX04 ((0x0454 << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX05 ((0x0455 << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX06 ((0x0456 << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX07 ((0x0457 << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX08 ((0x0458 << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX09 ((0x0459 << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX10 ((0x045a << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX11 ((0x045b << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX12 ((0x045c << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX13 ((0x045d << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX14 ((0x045e << 2) + 0xfe006000)
#define MAILBOX_STS_MBOX15 ((0x045f << 2) + 0xfe006000)
//========================================================================
//  IRQ_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe00a000
// -----------------------------------------------
#define IRQCTRL_IRQ_INV0 ((0x0000 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_INV1 ((0x0001 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_INV2 ((0x0002 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_INV3 ((0x0003 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_INV4 ((0x0004 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_INV5 ((0x0005 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_INV6 ((0x0006 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_INV7 ((0x0007 << 2) + 0xfe00a000)
#define IRQCTRL_MASK0_GIC ((0x0010 << 2) + 0xfe00a000)
#define IRQCTRL_MASK1_GIC ((0x0011 << 2) + 0xfe00a000)
#define IRQCTRL_MASK2_GIC ((0x0012 << 2) + 0xfe00a000)
#define IRQCTRL_MASK3_GIC ((0x0013 << 2) + 0xfe00a000)
#define IRQCTRL_MASK4_GIC ((0x0014 << 2) + 0xfe00a000)
#define IRQCTRL_MASK5_GIC ((0x0015 << 2) + 0xfe00a000)
#define IRQCTRL_MASK6_GIC ((0x0016 << 2) + 0xfe00a000)
#define IRQCTRL_MASK7_GIC ((0x0017 << 2) + 0xfe00a000)
#define IRQCTRL_MASK0_DSP ((0x0020 << 2) + 0xfe00a000)
#define IRQCTRL_MASK1_DSP ((0x0021 << 2) + 0xfe00a000)
#define IRQCTRL_MASK2_DSP ((0x0022 << 2) + 0xfe00a000)
#define IRQCTRL_MASK3_DSP ((0x0023 << 2) + 0xfe00a000)
#define IRQCTRL_MASK4_DSP ((0x0024 << 2) + 0xfe00a000)
#define IRQCTRL_MASK5_DSP ((0x0025 << 2) + 0xfe00a000)
#define IRQCTRL_MASK6_DSP ((0x0026 << 2) + 0xfe00a000)
#define IRQCTRL_MASK7_DSP ((0x0027 << 2) + 0xfe00a000)
#define IRQCTRL_MASK0_PWRCTRL ((0x0030 << 2) + 0xfe00a000)
#define IRQCTRL_MASK1_PWRCTRL ((0x0031 << 2) + 0xfe00a000)
#define IRQCTRL_MASK2_PWRCTRL ((0x0032 << 2) + 0xfe00a000)
#define IRQCTRL_MASK3_PWRCTRL ((0x0033 << 2) + 0xfe00a000)
#define IRQCTRL_MASK4_PWRCTRL ((0x0034 << 2) + 0xfe00a000)
#define IRQCTRL_MASK5_PWRCTRL ((0x0035 << 2) + 0xfe00a000)
#define IRQCTRL_MASK6_PWRCTRL ((0x0036 << 2) + 0xfe00a000)
#define IRQCTRL_MASK7_PWRCTRL ((0x0037 << 2) + 0xfe00a000)
#define IRQCTRL_MASK0_AOCPU ((0x0040 << 2) + 0xfe00a000)
#define IRQCTRL_MASK1_AOCPU ((0x0041 << 2) + 0xfe00a000)
#define IRQCTRL_MASK2_AOCPU ((0x0042 << 2) + 0xfe00a000)
#define IRQCTRL_MASK3_AOCPU ((0x0043 << 2) + 0xfe00a000)
#define IRQCTRL_MASK4_AOCPU ((0x0044 << 2) + 0xfe00a000)
#define IRQCTRL_MASK5_AOCPU ((0x0045 << 2) + 0xfe00a000)
#define IRQCTRL_MASK6_AOCPU ((0x0046 << 2) + 0xfe00a000)
#define IRQCTRL_MASK7_AOCPU ((0x0047 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_MODE0 ((0x0050 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_MODE1 ((0x0051 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_MODE2 ((0x0052 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_MODE3 ((0x0053 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_MODE4 ((0x0054 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_MODE5 ((0x0055 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_MODE6 ((0x0056 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_MODE7 ((0x0057 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH0 ((0x0060 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH1 ((0x0061 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH2 ((0x0062 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH3 ((0x0063 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH4 ((0x0064 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH5 ((0x0065 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH6 ((0x0066 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH7 ((0x0067 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH_CLR0 ((0x0070 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH_CLR1 ((0x0071 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH_CLR2 ((0x0072 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH_CLR3 ((0x0073 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH_CLR4 ((0x0074 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH_CLR5 ((0x0075 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH_CLR6 ((0x0076 << 2) + 0xfe00a000)
#define IRQCTRL_IRQ_LATCH_CLR7 ((0x0077 << 2) + 0xfe00a000)
#define IRQCTRL_LOCK_BIT ((0x0080 << 2) + 0xfe00a000)
#define IRQCTRL_PROT_BIT ((0x0081 << 2) + 0xfe00a000)
//========================================================================
//  RESET_CTRL - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe002000
// -----------------------------------------------
#define RESETCTRL_RESET0 ((0x0000 << 2) + 0xfe002000)
#define RESETCTRL_RESET1 ((0x0001 << 2) + 0xfe002000)
#define RESETCTRL_RESET2 ((0x0002 << 2) + 0xfe002000)
#define RESETCTRL_RESET3 ((0x0003 << 2) + 0xfe002000)
#define RESETCTRL_RESET4 ((0x0004 << 2) + 0xfe002000)
#define RESETCTRL_RESET5 ((0x0005 << 2) + 0xfe002000)
#define RESETCTRL_RESET0_LEVEL ((0x0010 << 2) + 0xfe002000)
#define RESETCTRL_RESET1_LEVEL ((0x0011 << 2) + 0xfe002000)
#define RESETCTRL_RESET2_LEVEL ((0x0012 << 2) + 0xfe002000)
#define RESETCTRL_RESET3_LEVEL ((0x0013 << 2) + 0xfe002000)
#define RESETCTRL_RESET4_LEVEL ((0x0014 << 2) + 0xfe002000)
#define RESETCTRL_RESET5_LEVEL ((0x0015 << 2) + 0xfe002000)
#define RESETCTRL_RESET0_MASK ((0x0020 << 2) + 0xfe002000)
#define RESETCTRL_RESET1_MASK ((0x0021 << 2) + 0xfe002000)
#define RESETCTRL_RESET2_MASK ((0x0022 << 2) + 0xfe002000)
#define RESETCTRL_RESET3_MASK ((0x0023 << 2) + 0xfe002000)
#define RESETCTRL_RESET4_MASK ((0x0024 << 2) + 0xfe002000)
#define RESETCTRL_RESET5_MASK ((0x0025 << 2) + 0xfe002000)
#define RESETCTRL_RESET_HOLD_CYC ((0x0030 << 2) + 0xfe002000)
#define RESETCTRL_WATCHDOG_CTRL0 ((0x0040 << 2) + 0xfe002000)
#define RESETCTRL_WATCHDOG_CTRL1 ((0x0041 << 2) + 0xfe002000)
#define RESETCTRL_WATCHDOG_CNT ((0x0042 << 2) + 0xfe002000)
#define RESETCTRL_WATCHDOG_CLR ((0x0043 << 2) + 0xfe002000)
#define RESETCTRL_SEC_WATCHDOG_CTRL0 ((0x0044 << 2) + 0xfe002000)
#define RESETCTRL_SEC_WATCHDOG_CTRL1 ((0x0045 << 2) + 0xfe002000)
#define RESETCTRL_SEC_WATCHDOG_CNT ((0x0046 << 2) + 0xfe002000)
#define RESETCTRL_SEC_WATCHDOG_CLR ((0x0047 << 2) + 0xfe002000)
#define RESETCTRL_WATCHDOG_DLY_CNT ((0x0048 << 2) + 0xfe002000)
#define RESETCTRL_SEC_RESET0 ((0x0050 << 2) + 0xfe002000)
#define RESETCTRL_SEC_RESET1 ((0x0051 << 2) + 0xfe002000)
#define RESETCTRL_SEC_RESET0_LEVEL ((0x0060 << 2) + 0xfe002000)
#define RESETCTRL_SEC_RESET1_LEVEL ((0x0061 << 2) + 0xfe002000)
#define RESETCTRL_SEC_RESET0_MASK ((0x0070 << 2) + 0xfe002000)
#define RESETCTRL_SEC_RESET1_MASK ((0x0071 << 2) + 0xfe002000)
#define RESETCTRL_RESET0_LOCK ((0x0080 << 2) + 0xfe002000)
#define RESETCTRL_RESET1_LOCK ((0x0081 << 2) + 0xfe002000)
#define RESETCTRL_RESET2_LOCK ((0x0082 << 2) + 0xfe002000)
#define RESETCTRL_RESET3_LOCK ((0x0083 << 2) + 0xfe002000)
#define RESETCTRL_RESET4_LOCK ((0x0084 << 2) + 0xfe002000)
#define RESETCTRL_RESET5_LOCK ((0x0085 << 2) + 0xfe002000)
#define RESETCTRL_SEC_RESET0_LOCK ((0x0088 << 2) + 0xfe002000)
#define RESETCTRL_SEC_RESET1_LOCK ((0x0089 << 2) + 0xfe002000)
#define RESETCTRL_RESET0_PROT ((0x0090 << 2) + 0xfe002000)
#define RESETCTRL_RESET1_PROT ((0x0091 << 2) + 0xfe002000)
#define RESETCTRL_RESET2_PROT ((0x0092 << 2) + 0xfe002000)
#define RESETCTRL_RESET3_PROT ((0x0093 << 2) + 0xfe002000)
#define RESETCTRL_RESET4_PROT ((0x0094 << 2) + 0xfe002000)
#define RESETCTRL_RESET5_PROT ((0x0095 << 2) + 0xfe002000)
#define RESETCTRL_SEC_RESET0_PROT ((0x0098 << 2) + 0xfe002000)
#define RESETCTRL_SEC_RESET1_PROT ((0x0099 << 2) + 0xfe002000)
//========================================================================
//  CPU_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe00e000
// -----------------------------------------------
#define CPUCTRL_SYS_CPU_RESET_CNTL ((0x0050 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CLK_CTRL ((0x0051 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CLK_CTRL1 ((0x0052 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CLK_CTRL2 ((0x0053 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CLK_CTRL3 ((0x0054 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CLK_CTRL4 ((0x0055 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CLK_CTRL5 ((0x0056 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CLK_CTRL6 ((0x0057 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CLK_RESULT ((0x0058 << 2) + 0xfe00e000)
#define CPUCTRL_ROM_DISABLE ((0x0060 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_POR_CFG0 ((0x0090 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_POR_CFG1 ((0x0091 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG0 ((0x0092 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG1 ((0x0093 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG2 ((0x0094 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG3 ((0x0095 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG4 ((0x0096 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG5 ((0x0097 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG6 ((0x0098 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG7 ((0x0099 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG8 ((0x009a << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG9 ((0x009b << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG10 ((0x009c << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG11 ((0x009d << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG12 ((0x009e << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_CFG13 ((0x009f << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_STATUS0 ((0x00a0 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_STATUS1 ((0x00a1 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_STATUS2 ((0x00a2 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_STATUS3 ((0x00a3 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_STATUS4 ((0x00a4 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_STATUS5 ((0x00a5 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_STATUS6 ((0x00a6 << 2) + 0xfe00e000)
#define CPUCTRL_SYS_CPU_STATUS7 ((0x00a7 << 2) + 0xfe00e000)
#define SYS_CPU_MISC ((0x00a8 << 2) + 0xfe00e000)
//========================================================================
//  SAR_ADC
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe026000
// -----------------------------------------------
#define SAR_ADC_REG0 ((0x0000 << 2) + 0xfe026000)
#define SAR_ADC_CHAN_LIST ((0x0001 << 2) + 0xfe026000)
#define SAR_ADC_AVG_CNTL ((0x0002 << 2) + 0xfe026000)
#define SAR_ADC_REG3 ((0x0003 << 2) + 0xfe026000)
#define SAR_ADC_DELAY ((0x0004 << 2) + 0xfe026000)
#define SAR_ADC_LAST_RD ((0x0005 << 2) + 0xfe026000)
#define SAR_ADC_FIFO_RD ((0x0006 << 2) + 0xfe026000)
#define SAR_ADC_AUX_SW ((0x0007 << 2) + 0xfe026000)
#define SAR_ADC_CHAN_10_SW ((0x0008 << 2) + 0xfe026000)
#define SAR_ADC_DETECT_IDLE_SW ((0x0009 << 2) + 0xfe026000)
#define SAR_ADC_DELTA_10 ((0x000a << 2) + 0xfe026000)
#define SAR_ADC_REG11 ((0x000b << 2) + 0xfe026000)
#define SAR_ADC_REG12 ((0x000c << 2) + 0xfe026000)
#define SAR_ADC_REG13 ((0x000d << 2) + 0xfe026000)
#define SAR_ADC_REG14 ((0x000e << 2) + 0xfe026000)
#define SAR_ADC_CH0_CTRL1 ((0x0013 << 2) + 0xfe026000)
#define SAR_ADC_CH0_CTRL2 ((0x0014 << 2) + 0xfe026000)
#define SAR_ADC_CH0_CTRL3 ((0x0015 << 2) + 0xfe026000)
#define SAR_ADC_CH1_CTRL1 ((0x0016 << 2) + 0xfe026000)
#define SAR_ADC_CH1_CTRL2 ((0x0017 << 2) + 0xfe026000)
#define SAR_ADC_CH1_CTRL3 ((0x0018 << 2) + 0xfe026000)
#define SAR_ADC_CH2_CTRL1 ((0x0019 << 2) + 0xfe026000)
#define SAR_ADC_CH2_CTRL2 ((0x001a << 2) + 0xfe026000)
#define SAR_ADC_CH2_CTRL3 ((0x001b << 2) + 0xfe026000)
#define SAR_ADC_CH3_CTRL1 ((0x001c << 2) + 0xfe026000)
#define SAR_ADC_CH3_CTRL2 ((0x001d << 2) + 0xfe026000)
#define SAR_ADC_CH3_CTRL3 ((0x001e << 2) + 0xfe026000)
#define SAR_ADC_CH4_CTRL1 ((0x001f << 2) + 0xfe026000)
#define SAR_ADC_CH4_CTRL2 ((0x0020 << 2) + 0xfe026000)
#define SAR_ADC_CH4_CTRL3 ((0x0021 << 2) + 0xfe026000)
#define SAR_ADC_CH5_CTRL1 ((0x0022 << 2) + 0xfe026000)
#define SAR_ADC_CH5_CTRL2 ((0x0023 << 2) + 0xfe026000)
#define SAR_ADC_CH5_CTRL3 ((0x0024 << 2) + 0xfe026000)
#define SAR_ADC_CH6_CTRL1 ((0x0025 << 2) + 0xfe026000)
#define SAR_ADC_CH6_CTRL2 ((0x0026 << 2) + 0xfe026000)
#define SAR_ADC_CH6_CTRL3 ((0x0027 << 2) + 0xfe026000)
#define SAR_ADC_CH7_CTRL1 ((0x0028 << 2) + 0xfe026000)
#define SAR_ADC_CH7_CTRL2 ((0x0029 << 2) + 0xfe026000)
#define SAR_ADC_CH7_CTRL3 ((0x002a << 2) + 0xfe026000)
#define SAR_ADC_HCIC_CTRL1 ((0x002b << 2) + 0xfe026000)
#define SAR_ADC_F1_CTRL ((0x002c << 2) + 0xfe026000)
#define SAR_ADC_F2_CTRL ((0x002d << 2) + 0xfe026000)
#define SAR_ADC_F3_CTRL ((0x002e << 2) + 0xfe026000)
#define SAR_ADC_DECI_FILTER_CTRL ((0x002f << 2) + 0xfe026000)
#define SAR_ADC_COEF_RAM_CNTL ((0x0030 << 2) + 0xfe026000)
#define SAR_ADC_COEF_RAM_DATA ((0x0031 << 2) + 0xfe026000)
#define SAR_ADC_FIFO_RD_NEW ((0x0032 << 2) + 0xfe026000)
#define SAR_ADC_RAW ((0x0033 << 2) + 0xfe026000)
#define SAR_ADC_CHNL0 ((0x0034 << 2) + 0xfe026000)
#define SAR_ADC_CHNL1 ((0x0035 << 2) + 0xfe026000)
#define SAR_ADC_CHNL2 ((0x0036 << 2) + 0xfe026000)
#define SAR_ADC_CHNL3 ((0x0037 << 2) + 0xfe026000)
#define SAR_ADC_CHNL4 ((0x0038 << 2) + 0xfe026000)
#define SAR_ADC_CHNL5 ((0x0039 << 2) + 0xfe026000)
#define SAR_ADC_CHNL6 ((0x003a << 2) + 0xfe026000)
#define SAR_ADC_CHNL7 ((0x003b << 2) + 0xfe026000)
//========================================================================
//  ANA_CTRL - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe008000
// -----------------------------------------------
#define ANACTRL_SYSPLL_CTRL0 ((0x0000 << 2) + 0xfe008000)
#define ANACTRL_SYSPLL_CTRL1 ((0x0001 << 2) + 0xfe008000)
#define ANACTRL_SYSPLL_CTRL2 ((0x0002 << 2) + 0xfe008000)
#define ANACTRL_SYSPLL_CTRL3 ((0x0003 << 2) + 0xfe008000)
#define ANACTRL_SYSPLL_CTRL4 ((0x0004 << 2) + 0xfe008000)
#define ANACTRL_SYSPLL_CTRL5 ((0x0005 << 2) + 0xfe008000)
#define ANACTRL_SYSPLL_CTRL6 ((0x0006 << 2) + 0xfe008000)
#define ANACTRL_SYSPLL_STS ((0x0007 << 2) + 0xfe008000)
#define ANACTRL_FIXPLL_CTRL0 ((0x0010 << 2) + 0xfe008000)
#define ANACTRL_FIXPLL_CTRL1 ((0x0011 << 2) + 0xfe008000)
#define ANACTRL_FIXPLL_CTRL2 ((0x0012 << 2) + 0xfe008000)
#define ANACTRL_FIXPLL_CTRL3 ((0x0013 << 2) + 0xfe008000)
#define ANACTRL_FIXPLL_CTRL4 ((0x0014 << 2) + 0xfe008000)
#define ANACTRL_FIXPLL_CTRL5 ((0x0015 << 2) + 0xfe008000)
#define ANACTRL_FIXPLL_CTRL6 ((0x0016 << 2) + 0xfe008000)
#define ANACTRL_FIXPLL_STS ((0x0017 << 2) + 0xfe008000)
#define ANACTRL_GP0PLL_CTRL0 ((0x0020 << 2) + 0xfe008000)
#define ANACTRL_GP0PLL_CTRL1 ((0x0021 << 2) + 0xfe008000)
#define ANACTRL_GP0PLL_CTRL2 ((0x0022 << 2) + 0xfe008000)
#define ANACTRL_GP0PLL_CTRL3 ((0x0023 << 2) + 0xfe008000)
#define ANACTRL_GP0PLL_CTRL4 ((0x0024 << 2) + 0xfe008000)
#define ANACTRL_GP0PLL_CTRL5 ((0x0025 << 2) + 0xfe008000)
#define ANACTRL_GP0PLL_CTRL6 ((0x0026 << 2) + 0xfe008000)
#define ANACTRL_GP0PLL_STS ((0x0027 << 2) + 0xfe008000)
#define ANACTRL_GP1PLL_CTRL0 ((0x0030 << 2) + 0xfe008000)
#define ANACTRL_GP1PLL_CTRL1 ((0x0031 << 2) + 0xfe008000)
#define ANACTRL_GP1PLL_CTRL2 ((0x0032 << 2) + 0xfe008000)
#define ANACTRL_GP1PLL_CTRL3 ((0x0033 << 2) + 0xfe008000)
#define ANACTRL_GP1PLL_CTRL4 ((0x0034 << 2) + 0xfe008000)
#define ANACTRL_GP1PLL_CTRL5 ((0x0035 << 2) + 0xfe008000)
#define ANACTRL_GP1PLL_CTRL6 ((0x0036 << 2) + 0xfe008000)
#define ANACTRL_GP1PLL_STS ((0x0037 << 2) + 0xfe008000)
#define ANACTRL_HIFIPLL_CTRL0 ((0x0040 << 2) + 0xfe008000)
#define ANACTRL_HIFIPLL_CTRL1 ((0x0041 << 2) + 0xfe008000)
#define ANACTRL_HIFIPLL_CTRL2 ((0x0042 << 2) + 0xfe008000)
#define ANACTRL_HIFIPLL_CTRL3 ((0x0043 << 2) + 0xfe008000)
#define ANACTRL_HIFIPLL_CTRL4 ((0x0044 << 2) + 0xfe008000)
#define ANACTRL_HIFIPLL_CTRL5 ((0x0045 << 2) + 0xfe008000)
#define ANACTRL_HIFIPLL_CTRL6 ((0x0046 << 2) + 0xfe008000)
#define ANACTRL_HIFIPLL_STS ((0x0047 << 2) + 0xfe008000)
//`define ANACTRL_PCIEPLL_CTRL0    8'h50
//`define ANACTRL_PCIEPLL_CTRL1    8'h51
//`define ANACTRL_PCIEPLL_CTRL2    8'h52
//`define ANACTRL_PCIEPLL_CTRL3    8'h53
//`define ANACTRL_PCIEPLL_CTRL4    8'h54
//`define ANACTRL_PCIEPLL_CTRL5    8'h55
//`define ANACTRL_PCIEPLL_STS      8'h56
#define ANACTRL_MPLL_CTRL0 ((0x0060 << 2) + 0xfe008000)
#define ANACTRL_MPLL_CTRL1 ((0x0061 << 2) + 0xfe008000)
#define ANACTRL_MPLL_CTRL2 ((0x0062 << 2) + 0xfe008000)
#define ANACTRL_MPLL_CTRL3 ((0x0063 << 2) + 0xfe008000)
#define ANACTRL_MPLL_CTRL4 ((0x0064 << 2) + 0xfe008000)
#define ANACTRL_MPLL_CTRL5 ((0x0065 << 2) + 0xfe008000)
#define ANACTRL_MPLL_CTRL6 ((0x0066 << 2) + 0xfe008000)
#define ANACTRL_MPLL_CTRL7 ((0x0067 << 2) + 0xfe008000)
#define ANACTRL_MPLL_CTRL8 ((0x0068 << 2) + 0xfe008000)
#define ANACTRL_MPLL_STS ((0x0069 << 2) + 0xfe008000)
#define ANACTRL_HDMIPLL_CTRL0 ((0x0070 << 2) + 0xfe008000)
#define ANACTRL_HDMIPLL_CTRL1 ((0x0071 << 2) + 0xfe008000)
#define ANACTRL_HDMIPLL_CTRL2 ((0x0072 << 2) + 0xfe008000)
#define ANACTRL_HDMIPLL_CTRL3 ((0x0073 << 2) + 0xfe008000)
#define ANACTRL_HDMIPLL_CTRL4 ((0x0074 << 2) + 0xfe008000)
#define ANACTRL_HDMIPLL_CTRL5 ((0x0075 << 2) + 0xfe008000)
#define ANACTRL_HDMIPLL_CTRL6 ((0x0076 << 2) + 0xfe008000)
//`define ANACTRL_HDMIPLL_STS      8'h77
//`define ANACTRL_HDMIPLL_VLOCK    8'h79
#define ANACTRL_HDMIPHY_CTRL0 ((0x0080 << 2) + 0xfe008000)
#define ANACTRL_HDMIPHY_CTRL1 ((0x0081 << 2) + 0xfe008000)
#define ANACTRL_HDMIPHY_CTRL2 ((0x0082 << 2) + 0xfe008000)
#define ANACTRL_HDMIPHY_CTRL3 ((0x0083 << 2) + 0xfe008000)
#define ANACTRL_HDMIPHY_CTRL4 ((0x0084 << 2) + 0xfe008000)
#define ANACTRL_HDMIPHY_CTRL5 ((0x0085 << 2) + 0xfe008000)
#define ANACTRL_HDMIPHY_STS ((0x0086 << 2) + 0xfe008000)
//`define ANACTRL_MIPICSI_CTRL0    8'h90
//`define ANACTRL_MIPICSI_CTRL1    8'h91
//`define ANACTRL_MIPICSI_CTRL2    8'h92
//`define ANACTRL_MIPICSI_CTRL3    8'h93
//`define ANACTRL_MIPICSI_CTRL4    8'h94
//`define ANACTRL_MIPICSI_CTRL5    8'h95
//`define ANACTRL_MIPIDSI_CTRL0    8'hA0
//`define ANACTRL_MIPIDSI_CTRL1    8'hA1
//`define ANACTRL_MIPIDSI_CTRL2    8'hA2
//`define ANACTRL_MIPIDSI_STS      8'hA3
//`define ANACTRL_VDAC_CTRL0       8'hB0
//`define ANACTRL_VDAC_CTRL1       8'hB1
#define ANACTRL_POR_CTRL ((0x00b6 << 2) + 0xfe008000)
#define ANACTRL_LOCK_BIT ((0x00b8 << 2) + 0xfe008000)
#define ANACTRL_PROT_BIT ((0x00b9 << 2) + 0xfe008000)
#define ANACTRL_ADC_PLL_CTRL ((0x00c0 << 2) + 0xfe008000)
#define ANACTRL_ADC_PLL_CTRL1 ((0x00c1 << 2) + 0xfe008000)
#define ANACTRL_ADC_PLL_CTRL2 ((0x00c2 << 2) + 0xfe008000)
#define ANACTRL_ADC_PLL_CTRL3 ((0x00c3 << 2) + 0xfe008000)
#define ANACTRL_ADC_PLL_CTRL4 ((0x00c4 << 2) + 0xfe008000)
#define ANACTRL_ADC_PLL_CTRL5 ((0x00c5 << 2) + 0xfe008000)
#define ANACTRL_ADC_PLL_CTRL6 ((0x00c6 << 2) + 0xfe008000)
//`define ANACTRL_ADC_PLL_STS      8'hC7
#define ANACTRL_RTCPLL_CTRL0 ((0x00d0 << 2) + 0xfe008000)
#define ANACTRL_RTCPLL_CTRL1 ((0x00d1 << 2) + 0xfe008000)
#define ANACTRL_RTCPLL_CTRL2 ((0x00d2 << 2) + 0xfe008000)
#define ANACTRL_RTCPLL_CTRL3 ((0x00d3 << 2) + 0xfe008000)
#define ANACTRL_RTCPLL_CTRL4 ((0x00d4 << 2) + 0xfe008000)
#define ANACTRL_RTCPLL_STS ((0x00d5 << 2) + 0xfe008000)
//`define ANACTRL_S2_DADC_CTRL     8'hD0
//`define ANACTRL_S2_DADC_CTRL2    8'hD1
#define ANACTRL_CHIP_TEST_STS ((0x00e0 << 2) + 0xfe008000)
//========================================================================
//  Ethernet Phy
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe028000
// -----------------------------------------------
#define ETH_PHY_DBG_CTL0 ((0x0000 << 2) + 0xfe028000)
#define ETH_PHY_DBG_CTL1 ((0x0001 << 2) + 0xfe028000)
#define ETH_PHY_DBG_CFG0 ((0x0002 << 2) + 0xfe028000)
#define ETH_PHY_DBG_CFG1 ((0x0003 << 2) + 0xfe028000)
#define ETH_PHY_DBG_CFG2 ((0x0004 << 2) + 0xfe028000)
#define ETH_PHY_DBG_CFG3 ((0x0005 << 2) + 0xfe028000)
#define ETH_PHY_DBG_CFG4 ((0x0006 << 2) + 0xfe028000)
#define ETH_PLL_STS ((0x0010 << 2) + 0xfe028000)
#define ETH_PLL_CTL0 ((0x0011 << 2) + 0xfe028000)
#define ETH_PLL_CTL1 ((0x0012 << 2) + 0xfe028000)
#define ETH_PLL_CTL2 ((0x0013 << 2) + 0xfe028000)
#define ETH_PLL_CTL3 ((0x0014 << 2) + 0xfe028000)
#define ETH_PLL_CTL4 ((0x0015 << 2) + 0xfe028000)
#define ETH_PLL_CTL5 ((0x0016 << 2) + 0xfe028000)
#define ETH_PLL_CTL6 ((0x0017 << 2) + 0xfe028000)
#define ETH_PLL_CTL7 ((0x0018 << 2) + 0xfe028000)
#define ETH_PHY_CNTL0 ((0x0020 << 2) + 0xfe028000)
#define ETH_PHY_CNTL1 ((0x0021 << 2) + 0xfe028000)
#define ETH_PHY_CNTL2 ((0x0022 << 2) + 0xfe028000)
#define ETH_PHY_CNTL3 ((0x0023 << 2) + 0xfe028000)
#define ETH_PHY_STS0 ((0x0025 << 2) + 0xfe028000)
#define ETH_PHY_STS1 ((0x0026 << 2) + 0xfe028000)
#define ETH_PHY_STS2 ((0x0027 << 2) + 0xfe028000)
#define ETH_PHY_DBG_REG ((0x0028 << 2) + 0xfe028000)
//========================================================================
//  Ethernet TOP
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe024000
// -----------------------------------------------
#define ETHTOP_CNTL0 ((0x0000 << 2) + 0xfe024000)
#define ETHTOP_CNTL1 ((0x0001 << 2) + 0xfe024000)
//========================================================================
//  I2C Slave A
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe064000
// -----------------------------------------------
#define I2C_S_A_CONTROL_REG ((0x0000 << 2) + 0xfe064000)
#define I2C_S_A_SEND_REG ((0x0001 << 2) + 0xfe064000)
#define I2C_S_A_RECV_REG ((0x0002 << 2) + 0xfe064000)
#define I2C_S_A_CNTL1_REG ((0x0003 << 2) + 0xfe064000)
//========================================================================
//  IR RX/TX
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe084000
// -----------------------------------------------
#define IRCTRL_IR_DEC_LDR_ACTIVE ((0x0000 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_LDR_IDLE ((0x0001 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_LDR_REPEAT ((0x0002 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_BIT_0 ((0x0003 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_REG0 ((0x0004 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_FRAME ((0x0005 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_STATUS ((0x0006 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_REG1 ((0x0007 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_LDR_ACTIVE ((0x0010 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_LDR_IDLE ((0x0011 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_LDR_REPEAT ((0x0012 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_BIT_0 ((0x0013 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_REG0 ((0x0014 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_FRAME ((0x0015 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_STATUS ((0x0016 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_REG1 ((0x0017 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_REG2 ((0x0018 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_DURATN2 ((0x0019 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_DURATN3 ((0x001a << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_FRAME1 ((0x001b << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_STATUS1 ((0x001c << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_STATUS2 ((0x001d << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_REG3 ((0x001e << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_FRAME_RSV0 ((0x001f << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_FRAME_RSV1 ((0x0020 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_FILTE ((0x0021 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_IRQ_CTL ((0x0022 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_FIFO_CTL ((0x0023 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_WIDTH_NEW ((0x0024 << 2) + 0xfe084000)
#define IRCTRL_MF_IR_DEC_REPEAT_DET ((0x0025 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_DEMOD_CNTL0 ((0x0030 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_DEMOD_CNTL1 ((0x0031 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_DEMOD_IIR_THD ((0x0032 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_DEMOD_THD0 ((0x0033 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_DEMOD_THD1 ((0x0034 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_DEMOD_SUM_CNT0 ((0x0035 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_DEMOD_SUM_CNT1 ((0x0036 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_DEMOD_CNT0 ((0x0037 << 2) + 0xfe084000)
#define IRCTRL_IR_DEC_DEMOD_CNT1 ((0x0038 << 2) + 0xfe084000)
#define IRCTRL_IR_BLASTER_ADDR0 ((0x0043 << 2) + 0xfe084000)
#define IRCTRL_IR_BLASTER_ADDR1 ((0x0044 << 2) + 0xfe084000)
#define IRCTRL_IR_BLASTER_ADDR2 ((0x0045 << 2) + 0xfe084000)
#define IRCTRL_IR_BLASTER_ADDR3 ((0x0046 << 2) + 0xfe084000)
//========================================================================
//  I2C Master A
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe066000
// -----------------------------------------------
#define I2C_M_A_CONTROL_REG ((0x0000 << 2) + 0xfe066000)
#define I2C_M_A_SLAVE_ADDR ((0x0001 << 2) + 0xfe066000)
#define I2C_M_A_TOKEN_LIST0 ((0x0002 << 2) + 0xfe066000)
#define I2C_M_A_TOKEN_LIST1 ((0x0003 << 2) + 0xfe066000)
#define I2C_M_A_WDATA_REG0 ((0x0004 << 2) + 0xfe066000)
#define I2C_M_A_WDATA_REG1 ((0x0005 << 2) + 0xfe066000)
#define I2C_M_A_RDATA_REG0 ((0x0006 << 2) + 0xfe066000)
#define I2C_M_A_RDATA_REG1 ((0x0007 << 2) + 0xfe066000)
#define I2C_M_A_TIMEOUT_TH ((0x0008 << 2) + 0xfe066000)
#define I2C_M_A_CNTL_DELY1 ((0x0009 << 2) + 0xfe066000)
#define I2C_M_A_CNTL_DELY2 ((0x000a << 2) + 0xfe066000)
#define I2C_M_A_LOW_DELY ((0x000b << 2) + 0xfe066000)
#define I2C_M_A_HIGH_DELY ((0x000c << 2) + 0xfe066000)
#define I2C_M_A_FIFO_CTRL0 ((0x000d << 2) + 0xfe066000)
#define I2C_M_A_FIFO_CTRL1 ((0x000e << 2) + 0xfe066000)
#define I2C_M_A_FIFO_PENDING ((0x000f << 2) + 0xfe066000)
#define I2C_M_A_FIFO_PENDING_MASK ((0x0010 << 2) + 0xfe066000)
#define I2C_M_A_FIFO_ST0 ((0x0011 << 2) + 0xfe066000)
//========================================================================
//  I2C Master B
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe068000
// -----------------------------------------------
#define I2C_M_B_CONTROL_REG ((0x0000 << 2) + 0xfe068000)
#define I2C_M_B_SLAVE_ADDR ((0x0001 << 2) + 0xfe068000)
#define I2C_M_B_TOKEN_LIST0 ((0x0002 << 2) + 0xfe068000)
#define I2C_M_B_TOKEN_LIST1 ((0x0003 << 2) + 0xfe068000)
#define I2C_M_B_WDATA_REG0 ((0x0004 << 2) + 0xfe068000)
#define I2C_M_B_WDATA_REG1 ((0x0005 << 2) + 0xfe068000)
#define I2C_M_B_RDATA_REG0 ((0x0006 << 2) + 0xfe068000)
#define I2C_M_B_RDATA_REG1 ((0x0007 << 2) + 0xfe068000)
#define I2C_M_B_TIMEOUT_TH ((0x0008 << 2) + 0xfe068000)
#define I2C_M_B_CNTL_DELY1 ((0x0009 << 2) + 0xfe068000)
#define I2C_M_B_CNTL_DELY2 ((0x000a << 2) + 0xfe068000)
#define I2C_M_B_LOW_DELY ((0x000b << 2) + 0xfe068000)
#define I2C_M_B_HIGH_DELY ((0x000c << 2) + 0xfe068000)
#define I2C_M_B_FIFO_CTRL0 ((0x000d << 2) + 0xfe068000)
#define I2C_M_B_FIFO_CTRL1 ((0x000e << 2) + 0xfe068000)
#define I2C_M_B_FIFO_PENDING ((0x000f << 2) + 0xfe068000)
#define I2C_M_B_FIFO_PENDING_MASK ((0x0010 << 2) + 0xfe068000)
#define I2C_M_B_FIFO_ST0 ((0x0011 << 2) + 0xfe068000)
//========================================================================
//  I2C Master C
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe06a000
// -----------------------------------------------
#define I2C_M_C_CONTROL_REG ((0x0000 << 2) + 0xfe06a000)
#define I2C_M_C_SLAVE_ADDR ((0x0001 << 2) + 0xfe06a000)
#define I2C_M_C_TOKEN_LIST0 ((0x0002 << 2) + 0xfe06a000)
#define I2C_M_C_TOKEN_LIST1 ((0x0003 << 2) + 0xfe06a000)
#define I2C_M_C_WDATA_REG0 ((0x0004 << 2) + 0xfe06a000)
#define I2C_M_C_WDATA_REG1 ((0x0005 << 2) + 0xfe06a000)
#define I2C_M_C_RDATA_REG0 ((0x0006 << 2) + 0xfe06a000)
#define I2C_M_C_RDATA_REG1 ((0x0007 << 2) + 0xfe06a000)
#define I2C_M_C_TIMEOUT_TH ((0x0008 << 2) + 0xfe06a000)
#define I2C_M_C_CNTL_DELY1 ((0x0009 << 2) + 0xfe06a000)
#define I2C_M_C_CNTL_DELY2 ((0x000a << 2) + 0xfe06a000)
#define I2C_M_C_LOW_DELY ((0x000b << 2) + 0xfe06a000)
#define I2C_M_C_HIGH_DELY ((0x000c << 2) + 0xfe06a000)
#define I2C_M_C_FIFO_CTRL0 ((0x000d << 2) + 0xfe06a000)
#define I2C_M_C_FIFO_CTRL1 ((0x000e << 2) + 0xfe06a000)
#define I2C_M_C_FIFO_PENDING ((0x000f << 2) + 0xfe06a000)
#define I2C_M_C_FIFO_PENDING_MASK ((0x0010 << 2) + 0xfe06a000)
#define I2C_M_C_FIFO_ST0 ((0x0011 << 2) + 0xfe06a000)
//========================================================================
//  I2C Master D
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe06c000
// -----------------------------------------------
#define I2C_M_D_CONTROL_REG ((0x0000 << 2) + 0xfe06c000)
#define I2C_M_D_SLAVE_ADDR ((0x0001 << 2) + 0xfe06c000)
#define I2C_M_D_TOKEN_LIST0 ((0x0002 << 2) + 0xfe06c000)
#define I2C_M_D_TOKEN_LIST1 ((0x0003 << 2) + 0xfe06c000)
#define I2C_M_D_WDATA_REG0 ((0x0004 << 2) + 0xfe06c000)
#define I2C_M_D_WDATA_REG1 ((0x0005 << 2) + 0xfe06c000)
#define I2C_M_D_RDATA_REG0 ((0x0006 << 2) + 0xfe06c000)
#define I2C_M_D_RDATA_REG1 ((0x0007 << 2) + 0xfe06c000)
#define I2C_M_D_TIMEOUT_TH ((0x0008 << 2) + 0xfe06c000)
#define I2C_M_D_CNTL_DELY1 ((0x0009 << 2) + 0xfe06c000)
#define I2C_M_D_CNTL_DELY2 ((0x000a << 2) + 0xfe06c000)
#define I2C_M_D_LOW_DELY ((0x000b << 2) + 0xfe06c000)
#define I2C_M_D_HIGH_DELY ((0x000c << 2) + 0xfe06c000)
#define I2C_M_D_FIFO_CTRL0 ((0x000d << 2) + 0xfe06c000)
#define I2C_M_D_FIFO_CTRL1 ((0x000e << 2) + 0xfe06c000)
#define I2C_M_D_FIFO_PENDING ((0x000f << 2) + 0xfe06c000)
#define I2C_M_D_FIFO_PENDING_MASK ((0x0010 << 2) + 0xfe06c000)
#define I2C_M_D_FIFO_ST0 ((0x0011 << 2) + 0xfe06c000)
//========================================================================
//  I2C Master E
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe06e000
// -----------------------------------------------
#define I2C_M_E_CONTROL_REG ((0x0000 << 2) + 0xfe06e000)
#define I2C_M_E_SLAVE_ADDR ((0x0001 << 2) + 0xfe06e000)
#define I2C_M_E_TOKEN_LIST0 ((0x0002 << 2) + 0xfe06e000)
#define I2C_M_E_TOKEN_LIST1 ((0x0003 << 2) + 0xfe06e000)
#define I2C_M_E_WDATA_REG0 ((0x0004 << 2) + 0xfe06e000)
#define I2C_M_E_WDATA_REG1 ((0x0005 << 2) + 0xfe06e000)
#define I2C_M_E_RDATA_REG0 ((0x0006 << 2) + 0xfe06e000)
#define I2C_M_E_RDATA_REG1 ((0x0007 << 2) + 0xfe06e000)
#define I2C_M_E_TIMEOUT_TH ((0x0008 << 2) + 0xfe06e000)
#define I2C_M_E_CNTL_DELY1 ((0x0009 << 2) + 0xfe06e000)
#define I2C_M_E_CNTL_DELY2 ((0x000a << 2) + 0xfe06e000)
#define I2C_M_E_LOW_DELY ((0x000b << 2) + 0xfe06e000)
#define I2C_M_E_HIGH_DELY ((0x000c << 2) + 0xfe06e000)
#define I2C_M_E_FIFO_CTRL0 ((0x000d << 2) + 0xfe06e000)
#define I2C_M_E_FIFO_CTRL1 ((0x000e << 2) + 0xfe06e000)
#define I2C_M_E_FIFO_PENDING ((0x000f << 2) + 0xfe06e000)
#define I2C_M_E_FIFO_PENDING_MASK ((0x0010 << 2) + 0xfe06e000)
#define I2C_M_E_FIFO_ST0 ((0x0011 << 2) + 0xfe06e000)
//========================================================================
//  I2C Master F
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe070000
// -----------------------------------------------
#define I2C_M_F_CONTROL_REG ((0x0000 << 2) + 0xfe070000)
#define I2C_M_F_SLAVE_ADDR ((0x0001 << 2) + 0xfe070000)
#define I2C_M_F_TOKEN_LIST0 ((0x0002 << 2) + 0xfe070000)
#define I2C_M_F_TOKEN_LIST1 ((0x0003 << 2) + 0xfe070000)
#define I2C_M_F_WDATA_REG0 ((0x0004 << 2) + 0xfe070000)
#define I2C_M_F_WDATA_REG1 ((0x0005 << 2) + 0xfe070000)
#define I2C_M_F_RDATA_REG0 ((0x0006 << 2) + 0xfe070000)
#define I2C_M_F_RDATA_REG1 ((0x0007 << 2) + 0xfe070000)
#define I2C_M_F_TIMEOUT_TH ((0x0008 << 2) + 0xfe070000)
#define I2C_M_F_CNTL_DELY1 ((0x0009 << 2) + 0xfe070000)
#define I2C_M_F_CNTL_DELY2 ((0x000a << 2) + 0xfe070000)
#define I2C_M_F_LOW_DELY ((0x000b << 2) + 0xfe070000)
#define I2C_M_F_HIGH_DELY ((0x000c << 2) + 0xfe070000)
#define I2C_M_F_FIFO_CTRL_REG ((0x000d << 2) + 0xfe070000)
#define I2C_M_F_STATE_REG ((0x000e << 2) + 0xfe070000)
//========================================================================
//  APB0_UART_A - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe078000
// -----------------------------------------------
#define UART_A_WFIFO ((0x0000 << 2) + 0xfe078000)
#define UART_A_RFIFO ((0x0001 << 2) + 0xfe078000)
#define UART_A_CONTROL ((0x0002 << 2) + 0xfe078000)
#define UART_A_STATUS ((0x0003 << 2) + 0xfe078000)
#define UART_A_MISC ((0x0004 << 2) + 0xfe078000)
#define UART_A_REG5 ((0x0005 << 2) + 0xfe078000)
//========================================================================
//  APB0_UART_B - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe07a000
// -----------------------------------------------
#define UART_B_WFIFO ((0x0000 << 2) + 0xfe07a000)
#define UART_B_RFIFO ((0x0001 << 2) + 0xfe07a000)
#define UART_B_CONTROL ((0x0002 << 2) + 0xfe07a000)
#define UART_B_STATUS ((0x0003 << 2) + 0xfe07a000)
#define UART_B_MISC ((0x0004 << 2) + 0xfe07a000)
#define UART_B_REG5 ((0x0005 << 2) + 0xfe07a000)
//========================================================================
//  APB0_UART_C - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe07c000
// -----------------------------------------------
#define UART_C_WFIFO ((0x0000 << 2) + 0xfe07c000)
#define UART_C_RFIFO ((0x0001 << 2) + 0xfe07c000)
#define UART_C_CONTROL ((0x0002 << 2) + 0xfe07c000)
#define UART_C_STATUS ((0x0003 << 2) + 0xfe07c000)
#define UART_C_MISC ((0x0004 << 2) + 0xfe07c000)
#define UART_C_REG5 ((0x0005 << 2) + 0xfe07c000)
//========================================================================
//  APB0_UART_D - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe07e000
// -----------------------------------------------
#define UART_D_WFIFO ((0x0000 << 2) + 0xfe07e000)
#define UART_D_RFIFO ((0x0001 << 2) + 0xfe07e000)
#define UART_D_CONTROL ((0x0002 << 2) + 0xfe07e000)
#define UART_D_STATUS ((0x0003 << 2) + 0xfe07e000)
#define UART_D_MISC ((0x0004 << 2) + 0xfe07e000)
#define UART_D_REG5 ((0x0005 << 2) + 0xfe07e000)
//========================================================================
//  APB0_UART_E - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe080000
// -----------------------------------------------
#define UART_E_WFIFO ((0x0000 << 2) + 0xfe080000)
#define UART_E_RFIFO ((0x0001 << 2) + 0xfe080000)
#define UART_E_CONTROL ((0x0002 << 2) + 0xfe080000)
#define UART_E_STATUS ((0x0003 << 2) + 0xfe080000)
#define UART_E_MISC ((0x0004 << 2) + 0xfe080000)
#define UART_E_REG5 ((0x0005 << 2) + 0xfe080000)
//========================================================================
//  PWM_AB - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe058000
// -----------------------------------------------
#define PWMAB_PWM_A ((0x0000 << 2) + 0xfe058000)
#define PWMAB_PWM_B ((0x0001 << 2) + 0xfe058000)
#define PWMAB_MISC_REG_AB ((0x0002 << 2) + 0xfe058000)
#define PWMAB_DELTA_SIGMA_AB ((0x0003 << 2) + 0xfe058000)
#define PWMAB_TIME_AB ((0x0004 << 2) + 0xfe058000)
#define PWMAB_A2 ((0x0005 << 2) + 0xfe058000)
#define PWMAB_B2 ((0x0006 << 2) + 0xfe058000)
#define PWMAB_BLINK_AB ((0x0007 << 2) + 0xfe058000)
#define PWMAB_LOCK_AB ((0x0008 << 2) + 0xfe058000)
//========================================================================
//  PWM_CD - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe05a000
// -----------------------------------------------
#define PWMCD_PWM_A ((0x0000 << 2) + 0xfe05a000)
#define PWMCD_PWM_B ((0x0001 << 2) + 0xfe05a000)
#define PWMCD_MISC_REG_AB ((0x0002 << 2) + 0xfe05a000)
#define PWMCD_DELTA_SIGMA_AB ((0x0003 << 2) + 0xfe05a000)
#define PWMCD_TIME_AB ((0x0004 << 2) + 0xfe05a000)
#define PWMCD_A2 ((0x0005 << 2) + 0xfe05a000)
#define PWMCD_B2 ((0x0006 << 2) + 0xfe05a000)
#define PWMCD_BLINK_AB ((0x0007 << 2) + 0xfe05a000)
#define PWMCD_LOCK_AB ((0x0008 << 2) + 0xfe05a000)
//========================================================================
//  PWM_EF - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe05c000
// -----------------------------------------------
#define PWMEF_PWM_A ((0x0000 << 2) + 0xfe05c000)
#define PWMEF_PWM_B ((0x0001 << 2) + 0xfe05c000)
#define PWMEF_MISC_REG_AB ((0x0002 << 2) + 0xfe05c000)
#define PWMEF_DELTA_SIGMA_AB ((0x0003 << 2) + 0xfe05c000)
#define PWMEF_TIME_AB ((0x0004 << 2) + 0xfe05c000)
#define PWMEF_A2 ((0x0005 << 2) + 0xfe05c000)
#define PWMEF_B2 ((0x0006 << 2) + 0xfe05c000)
#define PWMEF_BLINK_AB ((0x0007 << 2) + 0xfe05c000)
#define PWMEF_LOCK_AB ((0x0008 << 2) + 0xfe05c000)
//========================================================================
//  PWM_GH - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe05e000
// -----------------------------------------------
#define PWMGH_PWM_A ((0x0000 << 2) + 0xfe05e000)
#define PWMGH_PWM_B ((0x0001 << 2) + 0xfe05e000)
#define PWMGH_MISC_REG_AB ((0x0002 << 2) + 0xfe05e000)
#define PWMGH_DELTA_SIGMA_AB ((0x0003 << 2) + 0xfe05e000)
#define PWMGH_TIME_AB ((0x0004 << 2) + 0xfe05e000)
#define PWMGH_A2 ((0x0005 << 2) + 0xfe05e000)
#define PWMGH_B2 ((0x0006 << 2) + 0xfe05e000)
#define PWMGH_BLINK_AB ((0x0007 << 2) + 0xfe05e000)
#define PWMGH_LOCK_AB ((0x0008 << 2) + 0xfe05e000)
//========================================================================
//  PWM_IJ - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe060000
// -----------------------------------------------
#define PWMIJ_PWM_A ((0x0000 << 2) + 0xfe060000)
#define PWMIJ_PWM_B ((0x0001 << 2) + 0xfe060000)
#define PWMIJ_MISC_REG_AB ((0x0002 << 2) + 0xfe060000)
#define PWMIJ_DELTA_SIGMA_AB ((0x0003 << 2) + 0xfe060000)
#define PWMIJ_TIME_AB ((0x0004 << 2) + 0xfe060000)
#define PWMIJ_A2 ((0x0005 << 2) + 0xfe060000)
#define PWMIJ_B2 ((0x0006 << 2) + 0xfe060000)
#define PWMIJ_BLINK_AB ((0x0007 << 2) + 0xfe060000)
#define PWMIJ_LOCK_AB ((0x0008 << 2) + 0xfe060000)
//========================================================================
//  SPICC_0
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe050000
// -----------------------------------------------
#define SPICC0_RXDATA ((0x0000 << 2) + 0xfe050000)
#define SPICC0_TXDATA ((0x0001 << 2) + 0xfe050000)
#define SPICC0_CONREG ((0x0002 << 2) + 0xfe050000)
#define SPICC0_INTREG ((0x0003 << 2) + 0xfe050000)
#define SPICC0_DMAREG ((0x0004 << 2) + 0xfe050000)
#define SPICC0_STATREG ((0x0005 << 2) + 0xfe050000)
#define SPICC0_PERIODREG ((0x0006 << 2) + 0xfe050000)
#define SPICC0_TESTREG ((0x0007 << 2) + 0xfe050000)
#define SPICC0_DRADDR ((0x0008 << 2) + 0xfe050000)
#define SPICC0_DWADDR ((0x0009 << 2) + 0xfe050000)
#define SPICC0_LD_CNTL0 ((0x000a << 2) + 0xfe050000)
#define SPICC0_LD_CNTL1 ((0x000b << 2) + 0xfe050000)
#define SPICC0_LD_RADDR ((0x000c << 2) + 0xfe050000)
#define SPICC0_LD_WADDR ((0x000d << 2) + 0xfe050000)
#define SPICC0_ENHANCE_CNTL ((0x000e << 2) + 0xfe050000)
#define SPICC0_ENHANCE_CNTL1 ((0x000f << 2) + 0xfe050000)
#define SPICC0_ENHANCE_CNTL2 ((0x0010 << 2) + 0xfe050000)
//========================================================================
//  SPICC_1
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe052000
// -----------------------------------------------
#define SPICC1_RXDATA ((0x0000 << 2) + 0xfe052000)
#define SPICC1_TXDATA ((0x0001 << 2) + 0xfe052000)
#define SPICC1_CONREG ((0x0002 << 2) + 0xfe052000)
#define SPICC1_INTREG ((0x0003 << 2) + 0xfe052000)
#define SPICC1_DMAREG ((0x0004 << 2) + 0xfe052000)
#define SPICC1_STATREG ((0x0005 << 2) + 0xfe052000)
#define SPICC1_PERIODREG ((0x0006 << 2) + 0xfe052000)
#define SPICC1_TESTREG ((0x0007 << 2) + 0xfe052000)
#define SPICC1_DRADDR ((0x0008 << 2) + 0xfe052000)
#define SPICC1_DWADDR ((0x0009 << 2) + 0xfe052000)
#define SPICC1_LD_CNTL0 ((0x000a << 2) + 0xfe052000)
#define SPICC1_LD_CNTL1 ((0x000b << 2) + 0xfe052000)
#define SPICC1_LD_RADDR ((0x000c << 2) + 0xfe052000)
#define SPICC1_LD_WADDR ((0x000d << 2) + 0xfe052000)
#define SPICC1_ENHANCE_CNTL ((0x000e << 2) + 0xfe052000)
#define SPICC1_ENHANCE_CNTL1 ((0x000f << 2) + 0xfe052000)
#define SPICC1_ENHANCE_CNTL2 ((0x0010 << 2) + 0xfe052000)
//========================================================================
//  AIFIFO - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe046000
// -----------------------------------------------
#define AIU_AIFIFO_CTRL ((0x0000 << 2) + 0xfe046000)
#define AIU_AIFIFO_STATUS ((0x0001 << 2) + 0xfe046000)
#define AIU_AIFIFO_GBIT ((0x0002 << 2) + 0xfe046000)
#define AIU_AIFIFO_CLB ((0x0003 << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_START_PTR ((0x0004 << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_CURR_PTR ((0x0005 << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_END_PTR ((0x0006 << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_BYTES_AVAIL ((0x0007 << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_CONTROL ((0x0008 << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_MAN_WP ((0x0009 << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_MAN_RP ((0x000a << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_LEVEL ((0x000b << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_BUF_CNTL ((0x000c << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_BUF_WRAP_COUNT ((0x000d << 2) + 0xfe046000)
#define AIU_MEM_AIFIFO_MEM_CTL ((0x000f << 2) + 0xfe046000)
#define AIFIFO_TIME_STAMP_CNTL ((0x0010 << 2) + 0xfe046000)
#define AIFIFO_TIME_STAMP_SYNC_0 ((0x0011 << 2) + 0xfe046000)
#define AIFIFO_TIME_STAMP_SYNC_1 ((0x0012 << 2) + 0xfe046000)
#define AIFIFO_TIME_STAMP_0 ((0x0013 << 2) + 0xfe046000)
#define AIFIFO_TIME_STAMP_1 ((0x0014 << 2) + 0xfe046000)
#define AIFIFO_TIME_STAMP_2 ((0x0015 << 2) + 0xfe046000)
#define AIFIFO_TIME_STAMP_3 ((0x0016 << 2) + 0xfe046000)
#define AIFIFO_TIME_STAMP_LENGTH ((0x0017 << 2) + 0xfe046000)
//========================================================================
//  MSR_CLK - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe048000
// -----------------------------------------------
#define MSR_CLK_REG0 ((0x0000 << 2) + 0xfe048000)
#define MSR_CLK_REG1 ((0x0001 << 2) + 0xfe048000)
#define MSR_CLK_REG2 ((0x0002 << 2) + 0xfe048000)
#define MSR_CLK_REG3 ((0x0003 << 2) + 0xfe048000)
#define MSR_CLK_REG4 ((0x0004 << 2) + 0xfe048000)
#define MSR_CLK_REG5 ((0x0005 << 2) + 0xfe048000)
#define MSR_CLK_DUTY ((0x0006 << 2) + 0xfe048000)
//========================================================================
//  SPIFC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe056000
// -----------------------------------------------
#define SPI_FLASH_CMD ((0x0000 << 2) + 0xfe056000)
// SPI_FLASH_READ    31
// SPI_FLASH_WREN    30
// SPI_FLASH_WRDI    29
// SPI_FLASH_RDID    28
// SPI_FLASH_RDSR    27
// SPI_FLASH_WRSR    26
// SPI_FLASH_PP      25
// SPI_FLASH_SE      24
// SPI_FLASH_BE      23
// SPI_FLASH_CE      22
// SPI_FLASH_DP      21
// SPI_FLASH_RES     20
// SPI_HPM           19
// SPI_FLASH_USR     18
// SPI_FLASH_USR_ADDR 15
// SPI_FLASH_USR_DUMMY 14
// SPI_FLASH_USR_DIN   13
// SPI_FLASH_USR_DOUT   12
// SPI_FLASH_USR_DUMMY_BLEN   10
// SPI_FLASH_USR_CMD     0
#define SPI_FLASH_ADDR ((0x0001 << 2) + 0xfe056000)
// SPI_FLASH_BYTES_LEN 24
// SPI_FLASH_ADDR_START 0
#define SPI_FLASH_CTRL ((0x0002 << 2) + 0xfe056000)
// SPI_ENABLE_AHB    17
// SPI_SST_AAI       16
// SPI_RES_RID       15
// SPI_FREAD_DUAL    14
// SPI_READ_READ_EN  13
// SPI_CLK_DIV0      12
// SPI_CLKCNT_N      8
// SPI_CLKCNT_H      4
// SPI_CLKCNT_L      0
#define SPI_FLASH_CTRL1 ((0x0003 << 2) + 0xfe056000)
#define SPI_FLASH_STATUS ((0x0004 << 2) + 0xfe056000)
#define SPI_FLASH_CTRL2 ((0x0005 << 2) + 0xfe056000)
#define SPI_FLASH_CLOCK ((0x0006 << 2) + 0xfe056000)
#define SPI_FLASH_USER ((0x0007 << 2) + 0xfe056000)
#define SPI_FLASH_USER1 ((0x0008 << 2) + 0xfe056000)
#define SPI_FLASH_USER2 ((0x0009 << 2) + 0xfe056000)
#define SPI_FLASH_USER3 ((0x000a << 2) + 0xfe056000)
#define SPI_FLASH_USER4 ((0x000b << 2) + 0xfe056000)
#define SPI_FLASH_SLAVE ((0x000c << 2) + 0xfe056000)
#define SPI_FLASH_SLAVE1 ((0x000d << 2) + 0xfe056000)
#define SPI_FLASH_SLAVE2 ((0x000e << 2) + 0xfe056000)
#define SPI_FLASH_SLAVE3 ((0x000f << 2) + 0xfe056000)
#define SPI_FLASH_C0 ((0x0010 << 2) + 0xfe056000)
#define SPI_FLASH_C1 ((0x0011 << 2) + 0xfe056000)
#define SPI_FLASH_C2 ((0x0012 << 2) + 0xfe056000)
#define SPI_FLASH_C3 ((0x0013 << 2) + 0xfe056000)
#define SPI_FLASH_C4 ((0x0014 << 2) + 0xfe056000)
#define SPI_FLASH_C5 ((0x0015 << 2) + 0xfe056000)
#define SPI_FLASH_C6 ((0x0016 << 2) + 0xfe056000)
#define SPI_FLASH_C7 ((0x0017 << 2) + 0xfe056000)
#define SPI_FLASH_B8 ((0x0018 << 2) + 0xfe056000)
#define SPI_FLASH_B9 ((0x0019 << 2) + 0xfe056000)
#define SPI_FLASH_B10 ((0x001a << 2) + 0xfe056000)
#define SPI_FLASH_B11 ((0x001b << 2) + 0xfe056000)
#define SPI_FLASH_B12 ((0x001c << 2) + 0xfe056000)
#define SPI_FLASH_B13 ((0x001d << 2) + 0xfe056000)
#define SPI_FLASH_B14 ((0x001e << 2) + 0xfe056000)
#define SPI_FLASH_B15 ((0x001f << 2) + 0xfe056000)
//========================================================================
//  CEC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe044000
// -----------------------------------------------
#define CECA_GEN_CNTL ((0x0000 << 2) + 0xfe044000)
#define CECA_RW_REG ((0x0001 << 2) + 0xfe044000)
#define CECA_INTR_MASKN ((0x0002 << 2) + 0xfe044000)
#define CECA_INTR_CLR ((0x0003 << 2) + 0xfe044000)
#define CECA_INTR_STAT ((0x0004 << 2) + 0xfe044000)
#define CECB_GEN_CNTL ((0x0010 << 2) + 0xfe044000)
#define CECB_RW_REG ((0x0011 << 2) + 0xfe044000)
#define CECB_INTR_MASKN ((0x0012 << 2) + 0xfe044000)
#define CECB_INTR_CLR ((0x0013 << 2) + 0xfe044000)
#define CECB_INTR_STAT ((0x0014 << 2) + 0xfe044000)
//========================================================================
//  SMART CARD - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe038000
// -----------------------------------------------
#define SMARTCARD_REG0 ((0x0000 << 2) + 0xfe038000)
#define SMARTCARD_REG1 ((0x0001 << 2) + 0xfe038000)
#define SMARTCARD_REG2 ((0x0002 << 2) + 0xfe038000)
#define SMARTCARD_STATUS ((0x0003 << 2) + 0xfe038000)
#define SMARTCARD_INTR ((0x0004 << 2) + 0xfe038000)
#define SMARTCARD_REG5 ((0x0005 << 2) + 0xfe038000)
#define SMARTCARD_REG6 ((0x0006 << 2) + 0xfe038000)
#define SMARTCARD_FIFO ((0x0007 << 2) + 0xfe038000)
#define SMARTCARD_REG8 ((0x0008 << 2) + 0xfe038000)
//========================================================================
//  CAPU
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe012000
// -----------------------------------------------
#define CAPU_ACCESS_EN_AHB_NNA ((0x00c3 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_AHB_ETH ((0x00c2 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_AHB_USB0 ((0x00c1 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_AHB_USB1 ((0x00c0 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_16M_SLOT0 ((0x00b0 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_256K_SLOT1 ((0x00a1 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_256K_SLOT0 ((0x00a0 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_64K_SLOT5 ((0x0085 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_64K_SLOT4 ((0x0084 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_64K_SLOT3 ((0x0083 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_64K_SLOT2 ((0x0082 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_64K_SLOT1 ((0x0081 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_64K_SLOT0 ((0x0080 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT4F ((0x004f << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT4E ((0x004e << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT4D ((0x004d << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT4C ((0x004c << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT4B ((0x004b << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT4A ((0x004a << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT49 ((0x0049 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT48 ((0x0048 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT47 ((0x0047 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT46 ((0x0046 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT45 ((0x0045 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT44 ((0x0044 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT43 ((0x0043 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT42 ((0x0042 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT41 ((0x0041 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT40 ((0x0040 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT3F ((0x003f << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT3E ((0x003e << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT3D ((0x003d << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT3C ((0x003c << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT3B ((0x003b << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT3A ((0x003a << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT39 ((0x0039 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT38 ((0x0038 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT37 ((0x0037 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT36 ((0x0036 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT35 ((0x0035 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT34 ((0x0034 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT33 ((0x0033 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT32 ((0x0032 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT31 ((0x0031 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT30 ((0x0030 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT2F ((0x002f << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT2E ((0x002e << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT2D ((0x002d << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT2C ((0x002c << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT2B ((0x002b << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT2A ((0x002a << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT29 ((0x0029 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT28 ((0x0028 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT27 ((0x0027 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT26 ((0x0026 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT25 ((0x0025 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT24 ((0x0024 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT23 ((0x0023 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT22 ((0x0022 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT21 ((0x0021 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT20 ((0x0020 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT1F ((0x001f << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT1E ((0x001e << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT1D ((0x001d << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT1C ((0x001c << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT1B ((0x001b << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT1A ((0x001a << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT19 ((0x0019 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT18 ((0x0018 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT17 ((0x0017 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT16 ((0x0016 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT15 ((0x0015 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT14 ((0x0014 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT13 ((0x0013 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT12 ((0x0012 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT11 ((0x0011 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT10 ((0x0010 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT0F ((0x000f << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT0E ((0x000e << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT0D ((0x000d << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT0C ((0x000c << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT0B ((0x000b << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT0A ((0x000a << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT09 ((0x0009 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT08 ((0x0008 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT07 ((0x0007 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT06 ((0x0006 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT05 ((0x0005 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT04 ((0x0004 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT03 ((0x0003 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT02 ((0x0002 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT01 ((0x0001 << 2) + 0xfe012000)
#define CAPU_ACCESS_EN_8K_SLOT00 ((0x0000 << 2) + 0xfe012000)
//========================================================================
//  BT656
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe030000
// -----------------------------------------------
#define BT_CTRL ((0x0000 << 2) + 0xfe030000)
#define BT_SOFT_RESET 31 // Soft reset
#define BT_JPEG_START 30
#define BT_JPEG_IGNORE_BYTES 18 // 20:18
#define BT_JPEG_IGNORE_LAST 17
#define BT_UPDATE_ST_SEL 16
#define BT_COLOR_REPEAT 15
#define BT_VIDEO_MODE 13 // 14:13
#define BT_AUTO_FMT 12
#define BT_PROG_MODE 11
#define BT_JPEG_MODE 10
#define BT_XCLK27_EN_BIT 9 // 1 : xclk27 is input.     0 : xclk27 is output.
#define BT_FID_EN_BIT 8 // 1 : enable use FID port.
#define BT_CLK27_SEL_BIT 7 // 1 : external xclk27      0 : internal clk27.
#define BT_CLK27_PHASE_BIT 6 // 1 : no inverted          0 : inverted.
#define BT_ACE_MODE_BIT 5 // 1 : auto cover error by hardware.
#define BT_SLICE_MODE_BIT 4 // 1 : no ancillay flag     0 : with ancillay flag.
#define BT_FMT_MODE_BIT 3 // 1 : ntsc                 0 : pal.
#define BT_REF_MODE_BIT 2 // 1 : from bit stream.     0 : from ports.
#define BT_MODE_BIT 1 // 1 : BT656 model          0 : SAA7118 mode.
#define BT_EN_BIT 0 // 1 : enable.
#define BT_VBISTART ((0x0001 << 2) + 0xfe030000)
#define BT_VBIEND ((0x0002 << 2) + 0xfe030000)
#define BT_FIELDSADR ((0x0003 << 2) + 0xfe030000)
#define BT_LINECTRL ((0x0004 << 2) + 0xfe030000)
#define BT_VIDEOSTART ((0x0005 << 2) + 0xfe030000)
#define BT_VIDEOEND ((0x0006 << 2) + 0xfe030000)
#define BT_SLICELINE0 ((0x0007 << 2) + 0xfe030000)
#define BT_SLICELINE1 ((0x0008 << 2) + 0xfe030000)
#define BT_PORT_CTRL ((0x0009 << 2) + 0xfe030000)
#define BT_HSYNC_PHASE 0
#define BT_VSYNC_PHASE 1
#define BT_HSYNC_PULSE 2
#define BT_VSYNC_PULSE 3
#define BT_FID_PHASE 4
#define BT_FID_HSVS 5
#define BT_IDQ_EN 6
#define BT_IDQ_PHASE 7
#define BT_D8B 8
#define BT_10BTO8B 9
#define BT_FID_DELAY 10 // 12:10
#define BT_VSYNC_DELAY 13 //
#define BT_HSYNC_DELAY 16
#define BT_FID_HSVS_PCNT 19
#define BT_FID_HSVS_VS_RISING 20
#define BT_FID_HSVS_VS_FALLING 21
#define BT_VREF_FROM_VS_ONLY 22
#define BT_PORT_ACTIVE_HMODE 23
#define BT_DUAL_EDGE_CLK_EN 24
#define BT_CLK_INV_SEL 25
#define BT_DATA_ENDIAN 26
#define BT_SWAP_CTRL ((0x000a << 2) + 0xfe030000)
#define BT_601_CTRL0 ((0x000e << 2) + 0xfe030000)
#define BT_601_CTRL1 ((0x000f << 2) + 0xfe030000)
#define BT_601_CTRL2 ((0x0010 << 2) + 0xfe030000)
#define BT_601_CTRL3 ((0x0011 << 2) + 0xfe030000)
#define BT_FIELD_LUMA ((0x0012 << 2) + 0xfe030000)
#define BT_RAW_CTRL ((0x0013 << 2) + 0xfe030000)
#define BT_STATUS ((0x0014 << 2) + 0xfe030000)
#define BT_INT_CTRL ((0x0015 << 2) + 0xfe030000)
#define BT_VLINE_STATUS ((0x0017 << 2) + 0xfe030000)
#define BT_ERR_CNT ((0x0019 << 2) + 0xfe030000)
#define BT_LCNT_STATUS ((0x001a << 2) + 0xfe030000)
#define BT_PCNT_STATUS ((0x001c << 2) + 0xfe030000)
#define BT_DELAY_CTRL ((0x001d << 2) + 0xfe030000)
#define BT_REF_000 ((0x0020 << 2) + 0xfe030000)
#define BT_REF_001 ((0x0021 << 2) + 0xfe030000)
#define BT_REF_010 ((0x0022 << 2) + 0xfe030000)
#define BT_REF_011 ((0x0023 << 2) + 0xfe030000)
#define BT_REF_100 ((0x0024 << 2) + 0xfe030000)
#define BT_REF_101 ((0x0025 << 2) + 0xfe030000)
#define BT_REF_110 ((0x0026 << 2) + 0xfe030000)
#define BT_REF_111 ((0x0027 << 2) + 0xfe030000)
//========================================================================
//  PDM
//========================================================================
//`include "../audio/rtl/pdm_reg.vh"
//
// Reading file:  REG_LIST_AUDIO_RTL.h
//
//========================================================================
//  AUDIO - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe330000
// -----------------------------------------------
#define EE_AUDIO_CLK_GATE_EN0 ((0x0000 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_GATE_EN1 ((0x0001 << 2) + 0xfe330000)
#define EE_AUDIO_MCLK_A_CTRL ((0x0002 << 2) + 0xfe330000)
#define EE_AUDIO_MCLK_B_CTRL ((0x0003 << 2) + 0xfe330000)
#define EE_AUDIO_MCLK_C_CTRL ((0x0004 << 2) + 0xfe330000)
#define EE_AUDIO_MCLK_D_CTRL ((0x0005 << 2) + 0xfe330000)
#define EE_AUDIO_MCLK_E_CTRL ((0x0006 << 2) + 0xfe330000)
#define EE_AUDIO_MCLK_F_CTRL ((0x0007 << 2) + 0xfe330000)
#define EE_AUDIO_SW_RESET0 ((0x000a << 2) + 0xfe330000)
#define EE_AUDIO_SW_RESET1 ((0x000b << 2) + 0xfe330000)
#define EE_AUDIO_CLK81_CTRL ((0x000c << 2) + 0xfe330000)
#define EE_AUDIO_CLK81_EN ((0x000d << 2) + 0xfe330000)
#define EE_AUDIO_MCLK_CTRL ((0x000e << 2) + 0xfe330000)
#define EE_AUDIO_MST_A_SCLK_CTRL0 ((0x0010 << 2) + 0xfe330000)
#define EE_AUDIO_MST_A_SCLK_CTRL1 ((0x0011 << 2) + 0xfe330000)
#define EE_AUDIO_MST_B_SCLK_CTRL0 ((0x0012 << 2) + 0xfe330000)
#define EE_AUDIO_MST_B_SCLK_CTRL1 ((0x0013 << 2) + 0xfe330000)
#define EE_AUDIO_MST_C_SCLK_CTRL0 ((0x0014 << 2) + 0xfe330000)
#define EE_AUDIO_MST_C_SCLK_CTRL1 ((0x0015 << 2) + 0xfe330000)
#define EE_AUDIO_MST_D_SCLK_CTRL0 ((0x0016 << 2) + 0xfe330000)
#define EE_AUDIO_MST_D_SCLK_CTRL1 ((0x0017 << 2) + 0xfe330000)
#define EE_AUDIO_MST_E_SCLK_CTRL0 ((0x0018 << 2) + 0xfe330000)
#define EE_AUDIO_MST_E_SCLK_CTRL1 ((0x0019 << 2) + 0xfe330000)
#define EE_AUDIO_MST_F_SCLK_CTRL0 ((0x001a << 2) + 0xfe330000)
#define EE_AUDIO_MST_F_SCLK_CTRL1 ((0x001b << 2) + 0xfe330000)
#define EE_AUDIO_MST_DLY_CTRL0 ((0x001c << 2) + 0xfe330000)
#define EE_AUDIO_MST_DLY_CTRL1 ((0x001d << 2) + 0xfe330000)
#define EE_AUDIO_CLK_TDMIN_A_CTRL ((0x0020 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_TDMIN_B_CTRL ((0x0021 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_TDMIN_C_CTRL ((0x0022 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_TDMIN_LB_CTRL ((0x0023 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_TDMOUT_A_CTRL ((0x0024 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_TDMOUT_B_CTRL ((0x0025 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_TDMOUT_C_CTRL ((0x0026 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_SPDIFIN_CTRL ((0x0027 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_SPDIFOUT_CTRL ((0x0028 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_RESAMPLEA_CTRL ((0x0029 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_LOCKER_CTRL ((0x002a << 2) + 0xfe330000)
#define EE_AUDIO_CLK_PDMIN_CTRL0 ((0x002b << 2) + 0xfe330000)
#define EE_AUDIO_CLK_PDMIN_CTRL1 ((0x002c << 2) + 0xfe330000)
#define EE_AUDIO_CLK_SPDIFOUT_B_CTRL ((0x002d << 2) + 0xfe330000)
#define EE_AUDIO_CLK_RESAMPLEB_CTRL ((0x002e << 2) + 0xfe330000)
#define EE_AUDIO_CLK_SPDIFIN_LB_CTRL ((0x002f << 2) + 0xfe330000)
#define EE_AUDIO_CLK_EQDRC_CTRL0 ((0x0030 << 2) + 0xfe330000)
#define EE_AUDIO_VAD_CLK_CTRL ((0x0031 << 2) + 0xfe330000)
#define EE_AUDIO_EARCTX_CMDC_CLK_CTRL ((0x0032 << 2) + 0xfe330000)
#define EE_AUDIO_EARCTX_DMAC_CLK_CTRL ((0x0033 << 2) + 0xfe330000)
#define EE_AUDIO_EARCRX_CMDC_CLK_CTRL ((0x0034 << 2) + 0xfe330000)
#define EE_AUDIO_EARCRX_DMAC_CLK_CTRL ((0x0035 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_LOCKERB_CTRL ((0x0036 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_TDMINB_LB_CTRL ((0x0037 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_PDMIN_CTRL2 ((0x0038 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_PDMIN_CTRL3 ((0x0039 << 2) + 0xfe330000)
#define EE_AUDIO_CLK_TDMIN_D_CTRL ((0x003a << 2) + 0xfe330000)
#define EE_AUDIO_CLK_TDMOUT_D_CTRL ((0x003b << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CTRL0 ((0x0040 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CTRL1 ((0x0041 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_START_ADDR ((0x0042 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_FINISH_ADDR ((0x0043 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_INT_ADDR ((0x0044 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_STATUS1 ((0x0045 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_STATUS2 ((0x0046 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_START_ADDRB ((0x0047 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_FINISH_ADDRB ((0x0048 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_INIT_ADDR ((0x0049 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CTRL2 ((0x004a << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CTRL0 ((0x0050 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CTRL1 ((0x0051 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_START_ADDR ((0x0052 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_FINISH_ADDR ((0x0053 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_INT_ADDR ((0x0054 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_STATUS1 ((0x0055 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_STATUS2 ((0x0056 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_START_ADDRB ((0x0057 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_FINISH_ADDRB ((0x0058 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_INIT_ADDR ((0x0059 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CTRL2 ((0x005a << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CTRL0 ((0x0060 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CTRL1 ((0x0061 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_START_ADDR ((0x0062 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_FINISH_ADDR ((0x0063 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_INT_ADDR ((0x0064 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_STATUS1 ((0x0065 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_STATUS2 ((0x0066 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_START_ADDRB ((0x0067 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_FINISH_ADDRB ((0x0068 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_INIT_ADDR ((0x0069 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CTRL2 ((0x006a << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_CTRL0 ((0x0070 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_CTRL1 ((0x0071 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_START_ADDR ((0x0072 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_FINISH_ADDR ((0x0073 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_INT_ADDR ((0x0074 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_STATUS1 ((0x0075 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_STATUS2 ((0x0076 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_START_ADDRB ((0x0077 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_FINISH_ADDRB ((0x0078 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_INIT_ADDR ((0x0079 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_A_CTRL2 ((0x007a << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_CTRL0 ((0x0080 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_CTRL1 ((0x0081 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_START_ADDR ((0x0082 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_FINISH_ADDR ((0x0083 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_INT_ADDR ((0x0084 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_STATUS1 ((0x0085 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_STATUS2 ((0x0086 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_START_ADDRB ((0x0087 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_FINISH_ADDRB ((0x0088 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_INIT_ADDR ((0x0089 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_B_CTRL2 ((0x008a << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_CTRL0 ((0x0090 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_CTRL1 ((0x0091 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_START_ADDR ((0x0092 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_FINISH_ADDR ((0x0093 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_INT_ADDR ((0x0094 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_STATUS1 ((0x0095 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_STATUS2 ((0x0096 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_START_ADDRB ((0x0097 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_FINISH_ADDRB ((0x0098 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_INIT_ADDR ((0x0099 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_C_CTRL2 ((0x009a << 2) + 0xfe330000)
//`define EE_AUDIO_ARB_CTRL0              10'ha0
//`define EE_AUDIO_ARB_CTRL1              10'ha1
//`define EE_AUDIO_ARB_STS                10'ha8
#define EE_AUDIO_AM2AXI_CTRL0 ((0x00a2 << 2) + 0xfe330000)
#define EE_AUDIO_AM2AXI_CTRL1 ((0x00a3 << 2) + 0xfe330000)
#define EE_AUDIO_AXI_ASYNC_CTRL0 ((0x00a4 << 2) + 0xfe330000)
#define EE_AUDIO_AM2AXI_STS ((0x00a9 << 2) + 0xfe330000)
#define EE_AUDIO_AXI_ASYNC_STS ((0x00aa << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_CTRL0 ((0x00b0 << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_CTRL1 ((0x00b1 << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_CTRL2 ((0x00b2 << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_CTRL3 ((0x00b3 << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_DAT_CH_ID0 ((0x00b4 << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_DAT_CH_ID1 ((0x00b5 << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_DAT_CH_ID2 ((0x00b6 << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_DAT_CH_ID3 ((0x00b7 << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_LB_CH_ID0 ((0x00b8 << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_LB_CH_ID1 ((0x00b9 << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_LB_CH_ID2 ((0x00ba << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_LB_CH_ID3 ((0x00bb << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_STS ((0x00bc << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_CHSYNC_CTRL_INSERT ((0x00bd << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_CHSYNC_CTRL_ORIG ((0x00be << 2) + 0xfe330000)
#define EE_AUDIO_LB_A_CTRL4 ((0x00bf << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_CTRL ((0x00c0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_SWAP0 ((0x00c1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MASK0 ((0x00c2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MASK1 ((0x00c3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MASK2 ((0x00c4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MASK3 ((0x00c5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_STAT ((0x00c6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MUTE_VAL ((0x00c7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MUTE0 ((0x00c8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MUTE1 ((0x00c9 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MUTE2 ((0x00ca << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MUTE3 ((0x00cb << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_CTRL ((0x00d0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_SWAP0 ((0x00d1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MASK0 ((0x00d2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MASK1 ((0x00d3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MASK2 ((0x00d4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MASK3 ((0x00d5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_STAT ((0x00d6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MUTE_VAL ((0x00d7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MUTE0 ((0x00d8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MUTE1 ((0x00d9 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MUTE2 ((0x00da << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MUTE3 ((0x00db << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_CTRL ((0x00e0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_SWAP0 ((0x00e1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MASK0 ((0x00e2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MASK1 ((0x00e3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MASK2 ((0x00e4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MASK3 ((0x00e5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_STAT ((0x00e6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MUTE_VAL ((0x00e7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MUTE0 ((0x00e8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MUTE1 ((0x00e9 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MUTE2 ((0x00ea << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MUTE3 ((0x00eb << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_CTRL ((0x00f0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_SWAP0 ((0x00f1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MASK0 ((0x00f2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MASK1 ((0x00f3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MASK2 ((0x00f4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MASK3 ((0x00f5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_STAT ((0x00f6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MUTE_VAL ((0x00f7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MUTE0 ((0x00f8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MUTE1 ((0x00f9 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MUTE2 ((0x00fa << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MUTE3 ((0x00fb << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_CTRL0 ((0x0100 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_CTRL1 ((0x0101 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_CTRL2 ((0x0102 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_CTRL3 ((0x0103 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_CTRL4 ((0x0104 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_CTRL5 ((0x0105 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_CTRL6 ((0x0106 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_STAT0 ((0x0107 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_STAT1 ((0x0108 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_STAT2 ((0x0109 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_MUTE_VAL ((0x010a << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_CTRL7 ((0x010b << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEA_CTRL0 ((0x0110 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEA_CTRL1 ((0x0111 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEA_CTRL2 ((0x0112 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEA_CTRL3 ((0x0113 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEA_COEF0 ((0x0114 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEA_COEF1 ((0x0115 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEA_COEF2 ((0x0116 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEA_COEF3 ((0x0117 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEA_COEF4 ((0x0118 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEA_STATUS1 ((0x0119 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_STAT ((0x0120 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_GAIN0 ((0x0121 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_GAIN1 ((0x0122 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CTRL0 ((0x0123 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CTRL1 ((0x0124 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_PREAMB ((0x0125 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_SWAP ((0x0126 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTS0 ((0x0127 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTS1 ((0x0128 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTS2 ((0x0129 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTS3 ((0x012a << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTS4 ((0x012b << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTS5 ((0x012c << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTS6 ((0x012d << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTS7 ((0x012e << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTS8 ((0x012f << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTS9 ((0x0130 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTSA ((0x0131 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_CHSTSB ((0x0132 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_MUTE_VAL ((0x0133 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_GAIN2 ((0x0134 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_GAIN3 ((0x0135 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_GAIN_EN ((0x0136 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_GAIN_CTRL ((0x0137 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_CTRL0 ((0x0140 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_CTRL1 ((0x0141 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_SWAP0 ((0x0142 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MASK0 ((0x0143 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MASK1 ((0x0144 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MASK2 ((0x0145 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MASK3 ((0x0146 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_STAT ((0x0147 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_GAIN0 ((0x0148 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_GAIN1 ((0x0149 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MUTE_VAL ((0x014a << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MUTE0 ((0x014b << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MUTE1 ((0x014c << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MUTE2 ((0x014d << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MUTE3 ((0x014e << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MASK_VAL ((0x014f << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_CTRL0 ((0x0150 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_CTRL1 ((0x0151 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_SWAP0 ((0x0152 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MASK0 ((0x0153 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MASK1 ((0x0154 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MASK2 ((0x0155 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MASK3 ((0x0156 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_STAT ((0x0157 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_GAIN0 ((0x0158 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_GAIN1 ((0x0159 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MUTE_VAL ((0x015a << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MUTE0 ((0x015b << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MUTE1 ((0x015c << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MUTE2 ((0x015d << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MUTE3 ((0x015e << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MASK_VAL ((0x015f << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_CTRL0 ((0x0160 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_CTRL1 ((0x0161 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_SWAP0 ((0x0162 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MASK0 ((0x0163 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MASK1 ((0x0164 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MASK2 ((0x0165 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MASK3 ((0x0166 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_STAT ((0x0167 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_GAIN0 ((0x0168 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_GAIN1 ((0x0169 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MUTE_VAL ((0x016a << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MUTE0 ((0x016b << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MUTE1 ((0x016c << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MUTE2 ((0x016d << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MUTE3 ((0x016e << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MASK_VAL ((0x016f << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_CTRL ((0x0170 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_SWAP0 ((0x0171 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MASK0 ((0x0172 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MASK1 ((0x0173 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MASK2 ((0x0174 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MASK3 ((0x0175 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_STAT ((0x0176 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MUTE_VAL ((0x0177 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MUTE0 ((0x0178 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MUTE1 ((0x0179 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MUTE2 ((0x017a << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MUTE3 ((0x017b << 2) + 0xfe330000)
//`define EE_AUDIO_POW_DET_CTRL0          10'h180
//`define EE_AUDIO_POW_DET_CTRL1          10'h181
//`define EE_AUDIO_POW_DET_TH_HI          10'h182
//`define EE_AUDIO_POW_DET_TH_LO          10'h183
//`define EE_AUDIO_POW_DET_VALUE          10'h184
#define EE_AUDIO_SECURITY_CTRL0 ((0x0190 << 2) + 0xfe330000)
#define EE_AUDIO_SECURITY_CTRL1 ((0x0191 << 2) + 0xfe330000)
#define EE_AUDIO_SECURITY_CTRL2 ((0x0192 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_STAT ((0x01a0 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_GAIN0 ((0x01a1 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_GAIN1 ((0x01a2 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CTRL0 ((0x01a3 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CTRL1 ((0x01a4 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_PREAMB ((0x01a5 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_SWAP ((0x01a6 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTS0 ((0x01a7 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTS1 ((0x01a8 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTS2 ((0x01a9 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTS3 ((0x01aa << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTS4 ((0x01ab << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTS5 ((0x01ac << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTS6 ((0x01ad << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTS7 ((0x01ae << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTS8 ((0x01af << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTS9 ((0x01b0 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTSA ((0x01b1 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_CHSTSB ((0x01b2 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_MUTE_VAL ((0x01b3 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_GAIN2 ((0x01b4 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_GAIN3 ((0x01b5 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_GAIN_EN ((0x01b6 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFOUT_B_GAIN_CTRL ((0x01b7 << 2) + 0xfe330000)
#define EE_AUDIO_TORAM_CTRL0 ((0x01c0 << 2) + 0xfe330000)
#define EE_AUDIO_TORAM_CTRL1 ((0x01c1 << 2) + 0xfe330000)
#define EE_AUDIO_TORAM_START_ADDR ((0x01c2 << 2) + 0xfe330000)
#define EE_AUDIO_TORAM_FINISH_ADDR ((0x01c3 << 2) + 0xfe330000)
#define EE_AUDIO_TORAM_INT_ADDR ((0x01c4 << 2) + 0xfe330000)
#define EE_AUDIO_TORAM_STATUS1 ((0x01c5 << 2) + 0xfe330000)
#define EE_AUDIO_TORAM_STATUS2 ((0x01c6 << 2) + 0xfe330000)
#define EE_AUDIO_TORAM_INIT_ADDR ((0x01c7 << 2) + 0xfe330000)
#define EE_AUDIO_TOACODEC_CTRL0 ((0x01d0 << 2) + 0xfe330000)
#define EE_AUDIO_TOHDMITX_CTRL0 ((0x01d1 << 2) + 0xfe330000)
#define EE_AUDIO_TOVAD_CTRL0 ((0x01d2 << 2) + 0xfe330000)
#define EE_AUDIO_FRATV_CTRL0 ((0x01d3 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEB_CTRL0 ((0x01e0 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEB_CTRL1 ((0x01e1 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEB_CTRL2 ((0x01e2 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEB_CTRL3 ((0x01e3 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEB_COEF0 ((0x01e4 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEB_COEF1 ((0x01e5 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEB_COEF2 ((0x01e6 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEB_COEF3 ((0x01e7 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEB_COEF4 ((0x01e8 << 2) + 0xfe330000)
#define EE_AUDIO_RESAMPLEB_STATUS1 ((0x01e9 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_LB_CTRL0 ((0x01f0 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_LB_CTRL1 ((0x01f1 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_LB_CTRL6 ((0x01f6 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_LB_STAT0 ((0x01f7 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_LB_STAT1 ((0x01f8 << 2) + 0xfe330000)
#define EE_AUDIO_SPDIFIN_LB_MUTE_VAL ((0x01fa << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_CTRL0 ((0x0200 << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_CTRL1 ((0x0201 << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_CTRL2 ((0x0202 << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_CTRL3 ((0x0203 << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_CTRL4 ((0x0204 << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_CTRL5 ((0x0205 << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_CTRL6 ((0x0206 << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_CTRL7 ((0x0207 << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_STAT0 ((0x020a << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_STAT1 ((0x020b << 2) + 0xfe330000)
#define EE_AUDIO_FRHDMIRX_STAT2 ((0x020c << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CTRL0 ((0x0210 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CTRL1 ((0x0211 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_START_ADDR ((0x0212 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_FINISH_ADDR ((0x0213 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_INT_ADDR ((0x0214 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_STATUS1 ((0x0215 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_STATUS2 ((0x0216 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_START_ADDRB ((0x0217 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_FINISH_ADDRB ((0x0218 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_INIT_ADDR ((0x0219 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CTRL2 ((0x021a << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_CTRL0 ((0x0220 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_CTRL1 ((0x0221 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_START_ADDR ((0x0222 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_FINISH_ADDR ((0x0223 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_INT_ADDR ((0x0224 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_STATUS1 ((0x0225 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_STATUS2 ((0x0226 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_START_ADDRB ((0x0227 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_FINISH_ADDRB ((0x0228 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_INIT_ADDR ((0x0229 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_D_CTRL2 ((0x022a << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_CTRL0 ((0x0230 << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_CTRL1 ((0x0231 << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_CTRL2 ((0x0232 << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_CTRL3 ((0x0233 << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_DAT_CH_ID0 ((0x0234 << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_DAT_CH_ID1 ((0x0235 << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_DAT_CH_ID2 ((0x0236 << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_DAT_CH_ID3 ((0x0237 << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_LB_CH_ID0 ((0x0238 << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_LB_CH_ID1 ((0x0239 << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_LB_CH_ID2 ((0x023a << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_LB_CH_ID3 ((0x023b << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_STS ((0x023c << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_CHSYNC_CTRL_INSERT ((0x023d << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_CHSYNC_CTRL_ORIG ((0x023e << 2) + 0xfe330000)
#define EE_AUDIO_LB_B_CTRL4 ((0x023f << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CTRL0 ((0x0240 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CTRL1 ((0x0241 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_START_ADDR ((0x0242 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_FINISH_ADDR ((0x0243 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_INT_ADDR ((0x0244 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_STATUS1 ((0x0245 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_STATUS2 ((0x0246 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_START_ADDRB ((0x0247 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_FINISH_ADDRB ((0x0248 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_INIT_ADDR ((0x0249 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CTRL2 ((0x024a << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_CTRL0 ((0x0250 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_CTRL1 ((0x0251 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_START_ADDR ((0x0252 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_FINISH_ADDR ((0x0253 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_INT_ADDR ((0x0254 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_STATUS1 ((0x0255 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_STATUS2 ((0x0256 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_START_ADDRB ((0x0257 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_FINISH_ADDRB ((0x0258 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_INIT_ADDR ((0x0259 << 2) + 0xfe330000)
#define EE_AUDIO_FRDDR_E_CTRL2 ((0x025a << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_SWAP1 ((0x0260 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MASK4 ((0x0261 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MASK5 ((0x0262 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MASK6 ((0x0263 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MASK7 ((0x0264 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MUTE4 ((0x0265 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MUTE5 ((0x0266 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MUTE6 ((0x0267 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_A_MUTE7 ((0x0268 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_SWAP1 ((0x0270 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MASK4 ((0x0271 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MASK5 ((0x0272 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MASK6 ((0x0273 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MASK7 ((0x0274 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MUTE4 ((0x0275 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MUTE5 ((0x0276 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MUTE6 ((0x0277 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_B_MUTE7 ((0x0278 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_SWAP1 ((0x0280 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MASK4 ((0x0281 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MASK5 ((0x0282 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MASK6 ((0x0283 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MASK7 ((0x0284 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MUTE4 ((0x0285 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MUTE5 ((0x0286 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MUTE6 ((0x0287 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_C_MUTE7 ((0x0288 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_SWAP1 ((0x0290 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MASK4 ((0x0291 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MASK5 ((0x0292 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MASK6 ((0x0293 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MASK7 ((0x0294 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MUTE4 ((0x0295 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MUTE5 ((0x0296 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MUTE6 ((0x0297 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_LB_MUTE7 ((0x0298 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_CTRL2 ((0x02a0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_SWAP1 ((0x02a1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_GAIN2 ((0x02a2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_GAIN3 ((0x02a3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MASK4 ((0x02a4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MASK5 ((0x02a5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MASK6 ((0x02a6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MASK7 ((0x02a7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MUTE4 ((0x02a8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MUTE5 ((0x02a9 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MUTE6 ((0x02aa << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_MUTE7 ((0x02ab << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_GAIN_EN ((0x02ac << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_A_GAIN_CTRL ((0x02ad << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_CTRL2 ((0x02b0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_SWAP1 ((0x02b1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_GAIN2 ((0x02b2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_GAIN3 ((0x02b3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MASK4 ((0x02b4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MASK5 ((0x02b5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MASK6 ((0x02b6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MASK7 ((0x02b7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MUTE4 ((0x02b8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MUTE5 ((0x02b9 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MUTE6 ((0x02ba << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_MUTE7 ((0x02bb << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_GAIN_EN ((0x02bc << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_B_GAIN_CTRL ((0x02bd << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_CTRL2 ((0x02c0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_SWAP1 ((0x02c1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_GAIN2 ((0x02c2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_GAIN3 ((0x02c3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MASK4 ((0x02c4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MASK5 ((0x02c5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MASK6 ((0x02c6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MASK7 ((0x02c7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MUTE4 ((0x02c8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MUTE5 ((0x02c9 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MUTE6 ((0x02ca << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_MUTE7 ((0x02cb << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_GAIN_EN ((0x02cc << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_C_GAIN_CTRL ((0x02cd << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_SWAP1 ((0x02d0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MASK4 ((0x02d1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MASK5 ((0x02d2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MASK6 ((0x02d3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MASK7 ((0x02d4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MUTE4 ((0x02d5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MUTE5 ((0x02d6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MUTE6 ((0x02d7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMINB_LB_MUTE7 ((0x02d8 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CHNUM_ID0 ((0x0300 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CHNUM_ID1 ((0x0301 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CHNUM_ID2 ((0x0302 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CHNUM_ID3 ((0x0303 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CHNUM_ID4 ((0x0304 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CHNUM_ID5 ((0x0305 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CHNUM_ID6 ((0x0306 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CHNUM_ID7 ((0x0307 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_A_CHSYNC_CTRL ((0x030f << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CHNUM_ID0 ((0x0310 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CHNUM_ID1 ((0x0311 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CHNUM_ID2 ((0x0312 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CHNUM_ID3 ((0x0313 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CHNUM_ID4 ((0x0314 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CHNUM_ID5 ((0x0315 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CHNUM_ID6 ((0x0316 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CHNUM_ID7 ((0x0317 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_B_CHSYNC_CTRL ((0x031f << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CHNUM_ID0 ((0x0320 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CHNUM_ID1 ((0x0321 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CHNUM_ID2 ((0x0322 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CHNUM_ID3 ((0x0323 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CHNUM_ID4 ((0x0324 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CHNUM_ID5 ((0x0325 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CHNUM_ID6 ((0x0326 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CHNUM_ID7 ((0x0327 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_C_CHSYNC_CTRL ((0x032f << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CHNUM_ID0 ((0x0330 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CHNUM_ID1 ((0x0331 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CHNUM_ID2 ((0x0332 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CHNUM_ID3 ((0x0333 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CHNUM_ID4 ((0x0334 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CHNUM_ID5 ((0x0335 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CHNUM_ID6 ((0x0336 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CHNUM_ID7 ((0x0337 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_D_CHSYNC_CTRL ((0x033f << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CHNUM_ID0 ((0x0340 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CHNUM_ID1 ((0x0341 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CHNUM_ID2 ((0x0342 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CHNUM_ID3 ((0x0343 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CHNUM_ID4 ((0x0344 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CHNUM_ID5 ((0x0345 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CHNUM_ID6 ((0x0346 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CHNUM_ID7 ((0x0347 << 2) + 0xfe330000)
#define EE_AUDIO_TODDR_E_CHSYNC_CTRL ((0x034f << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_A_CHNUM_ID0 ((0x0350 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_A_CHNUM_ID1 ((0x0351 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_A_CHNUM_ID2 ((0x0352 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_A_CHNUM_ID3 ((0x0353 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_A_CHNUM_ID4 ((0x0354 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_A_CHNUM_ID5 ((0x0355 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_A_CHNUM_ID6 ((0x0356 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_A_CHNUM_ID7 ((0x0357 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_CHSYNC_MASK ((0x035e << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_A_CHSYNC_CTRL ((0x035f << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_B_CHNUM_ID0 ((0x0360 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_B_CHNUM_ID1 ((0x0361 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_B_CHNUM_ID2 ((0x0362 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_B_CHNUM_ID3 ((0x0363 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_B_CHNUM_ID4 ((0x0364 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_B_CHNUM_ID5 ((0x0365 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_B_CHNUM_ID6 ((0x0366 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_B_CHNUM_ID7 ((0x0367 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_B_CHSYNC_CTRL ((0x036f << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_C_CHNUM_ID0 ((0x0370 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_C_CHNUM_ID1 ((0x0371 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_C_CHNUM_ID2 ((0x0372 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_C_CHNUM_ID3 ((0x0373 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_C_CHNUM_ID4 ((0x0374 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_C_CHNUM_ID5 ((0x0375 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_C_CHNUM_ID6 ((0x0376 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_C_CHNUM_ID7 ((0x0377 << 2) + 0xfe330000)
#define EE_AUDIO_RSAMP_C_CHSYNC_CTRL ((0x037f << 2) + 0xfe330000)
#define EE_AUDIO_EXCEPTION_IRQ_STS0 ((0x0380 << 2) + 0xfe330000)
#define EE_AUDIO_EXCEPTION_IRQ_STS1 ((0x0381 << 2) + 0xfe330000)
#define EE_AUDIO_EXCEPTION_IRQ_MASK0 ((0x0382 << 2) + 0xfe330000)
#define EE_AUDIO_EXCEPTION_IRQ_MASK1 ((0x0383 << 2) + 0xfe330000)
#define EE_AUDIO_EXCEPTION_IRQ_MODE0 ((0x0384 << 2) + 0xfe330000)
#define EE_AUDIO_EXCEPTION_IRQ_MODE1 ((0x0385 << 2) + 0xfe330000)
#define EE_AUDIO_EXCEPTION_IRQ_CLR0 ((0x0386 << 2) + 0xfe330000)
#define EE_AUDIO_EXCEPTION_IRQ_CLR1 ((0x0387 << 2) + 0xfe330000)
#define EE_AUDIO_EXCEPTION_IRQ_INV0 ((0x0388 << 2) + 0xfe330000)
#define EE_AUDIO_EXCEPTION_IRQ_INV1 ((0x0389 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRL0 ((0x0390 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRL1 ((0x0391 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRL2 ((0x0392 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRL3 ((0x0393 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRL4 ((0x0394 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRL5 ((0x0395 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRL6 ((0x0396 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRL7 ((0x0397 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRL8 ((0x0398 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRL9 ((0x0399 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRLA ((0x039a << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRLB ((0x039b << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRLC ((0x039c << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRLD ((0x039d << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRLE ((0x039e << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRLF ((0x039f << 2) + 0xfe330000)
#define EE_AUDIO_MCLK_PAD_CTRL0 ((0x03a0 << 2) + 0xfe330000)
#define EE_AUDIO_MCLK_PAD_CTRL1 ((0x03a1 << 2) + 0xfe330000)
#define EE_AUDIO_SCLK_PAD_CTRL0 ((0x03a2 << 2) + 0xfe330000)
#define EE_AUDIO_LRCLK_PAD_CTRL0 ((0x03a3 << 2) + 0xfe330000)
#define EE_AUDIO_MCLK_PAD_CTRL2 ((0x03a4 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRLG ((0x03a5 << 2) + 0xfe330000)
#define EE_AUDIO_DAT_PAD_CTRLH ((0x03a6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_CTRL ((0x03b0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_SWAP0 ((0x03b1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MASK0 ((0x03b2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MASK1 ((0x03b3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MASK2 ((0x03b4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MASK3 ((0x03b5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_STAT ((0x03b6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MUTE_VAL ((0x03b7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MUTE0 ((0x03b8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MUTE1 ((0x03b9 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MUTE2 ((0x03ba << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MUTE3 ((0x03bb << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_SWAP1 ((0x03c0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MASK4 ((0x03c1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MASK5 ((0x03c2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MASK6 ((0x03c3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MASK7 ((0x03c4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MUTE4 ((0x03c5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MUTE5 ((0x03c6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MUTE6 ((0x03c7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMIN_D_MUTE7 ((0x03c8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_CTRL0 ((0x03d0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_CTRL1 ((0x03d1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_SWAP0 ((0x03d2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MASK0 ((0x03d3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MASK1 ((0x03d4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MASK2 ((0x03d5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MASK3 ((0x03d6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_STAT ((0x03d7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_GAIN0 ((0x03d8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_GAIN1 ((0x03d9 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MUTE_VAL ((0x03da << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MUTE0 ((0x03db << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MUTE1 ((0x03dc << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MUTE2 ((0x03dd << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MUTE3 ((0x03de << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MASK_VAL ((0x03df << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_CTRL2 ((0x03e0 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_SWAP1 ((0x03e1 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_GAIN2 ((0x03e2 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_GAIN3 ((0x03e3 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MASK4 ((0x03e4 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MASK5 ((0x03e5 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MASK6 ((0x03e6 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MASK7 ((0x03e7 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MUTE4 ((0x03e8 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MUTE5 ((0x03e9 << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MUTE6 ((0x03ea << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_MUTE7 ((0x03eb << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_GAIN_EN ((0x03ec << 2) + 0xfe330000)
#define EE_AUDIO_TDMOUT_D_GAIN_CTRL ((0x03ed << 2) + 0xfe330000)
//========================================================================
//  PDM - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe331000
// -----------------------------------------------
#define PDM_CTRL ((0x0000 << 2) + 0xfe331000)
// bit 31:   PDM enable.
// bit 30:   invert the PDM_DCLK.
// bit 29:   output mode:  1: 24bits. 0: 32 bits.
// bit 28:   bypass mode. 1: bypass all filter. directly output the PDM input to DDR. 0: normal
// mode. bit 27~9: not used. bit 16:.   PDM Asynchronous FIFO soft reset.  write 1 to soft reset
// AFIFO. bit 15:8   PDM channel reset.  0: to reset each PDM channel.  1: normal mode. bit 7:0.
// PDM channel enable. each bit for one channel.
#define PDM_HCIC_CTRL1 ((0x0001 << 2) + 0xfe331000)
// bit 31      hcic filter enable.  1 use sinc filter. 0 bypass input to output.
// bit 29:24.  hcic final gain shift parameter.
// bit 23:16   hcic final gain multiplier.
// bit 8:4     hcic  down sample rate.
// bit 3:0     hcic  stage number. must be between 3 to 9.
#define PDM_HCIC_CTRL2 ((0x0002 << 2) + 0xfe331000)
// Not used.
#define PDM_F1_CTRL ((0x0003 << 2) + 0xfe331000)
// bit 31 .   filter 1 enable.
// bit 16:15. f1 round mode.  2'b00 : sign bit at bit 49.  28bits output [49:22] round at bit 21.
// 32bits output [49:18]. 24bits output [49:26]
//                    2'b01 : sign bit at bit 50.  28bits output [50:23] round at bit 22. 32bits
//                    output [49:18]. 24bits output [49:26] 2'b10 : sign bit at bit 51.  28bits
//                    output [51:24] round at bit 23 32bits output [49:18]. 24bits output [49:26].
// bit 15:12. filter 1 down sample rate.
// bit 8:0.   filter 1 stage number.
#define PDM_F2_CTRL ((0x0004 << 2) + 0xfe331000)
// bit 31 .   filter 2 enable.
// bit 16:15. f2 round mode.  2'b00 : round at bit 21. 2'b01 : round at bit 22.  2'b10 : round at
// bit 23. bit 15:12. filter 2 down sample rate. bit 8:0.   filter 2 stage number.
#define PDM_F3_CTRL ((0x0005 << 2) + 0xfe331000)
// bit 31 .   filter 3 enable.
// bit 16:15. f3 round mode.  2'b00 : round at bit 21. 2'b01 : round at bit 22.  2'b10 : round at
// bit 23. bit 15:12. filter 3 down sample rate. bit 8:0.   filter 3 stage number.
#define PDM_HPF_CTRL ((0x0006 << 2) + 0xfe331000)
// bit 31  High pass filter enable.
// bit 20:16 high pass filter shift steps. 6~19 steps.
// bit 15:0 high pass filter output factor.
#define PDM_CHAN_CTRL ((0x0007 << 2) + 0xfe331000)
// bit 31:24.  chan3 data sample pointer vs edge of the PDM_DCLK.
// bit 23:16   chan2 data sample pointer vs edge of the PDM_DCLK.
// bit 15:8.   chan1 data sample pointer vs edge of the PDM_DCLK.
// bit 7:0     chan0 data sample pointer vs edge of the PDM_DCLK.
#define PDM_CHAN_CTRL1 ((0x0008 << 2) + 0xfe331000)
// bit 31:24.  chan7 data sample pointer vs edge of the PDM_DCLK.
// bit 23:16   chan6 data sample pointer vs edge of the PDM_DCLK.
// bit 15:8.   chan5 data sample pointer vs edge of the PDM_DCLK.
// bit 7:0     chan4 data sample pointer vs edge of the PDM_DCLK.
#define PDM_COEFF_ADDR ((0x0009 << 2) + 0xfe331000)
// address of the write/read of coeff data.
#define PDM_COEFF_DATA ((0x000a << 2) + 0xfe331000)
// write/read data to coeff memory.
#define PDM_CLKG_CTRL ((0x000b << 2) + 0xfe331000)
// auto clock gating control.  1: disable the clock gating function. the clock will awlays
// enabled. 0 : use RTL auto clock gating.
// 31:7 not used.
// bit 6  filt_ctrl module auto clock gating control.
// bit 5  sinc fifo module auto clock gating control.
// bit 4  filter module auto clock gating control.
// bit 3  apb module auto clock gating control.
// bit 2  coeff memory module auto clock gating control.
// bit 1  each channel module auto clock gating control.
// bit 0 cts_pdm_clk   auto clock gating control.
#define PDM_STS ((0x000c << 2) + 0xfe331000)
// bit 1  HPF filter output overflow.  means the PCLK is too slow.
// bit 0  HCIC filter output overflow. means the CTS_PDM_CLK is too slow. can't finished the
// filter function.
#define PDM_MUTE_VALUE ((0x000d << 2) + 0xfe331000)
#define PDM_MASK_NUM ((0x000e << 2) + 0xfe331000)
#define PDM_CHAN_CTRL2 ((0x000f << 2) + 0xfe331000)
// bit 7:0    second sample and start FSM point vs rise edge of PDM_DCLK
//========================================================================
//  PDMB - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe334800
// -----------------------------------------------
#define PDMB_CTRL ((0x0000 << 2) + 0xfe334800)
// bit 31:   PDM enable.
// bit 30:   invert the PDM_DCLK.
// bit 29:   output mode:  1: 24bits. 0: 32 bits.
// bit 28:   bypass mode. 1: bypass all filter. directly output the PDM input to DDR. 0: normal
// mode. bit 27~9: not used. bit 16:.   PDM Asynchronous FIFO soft reset.  write 1 to soft reset
// AFIFO. bit 15:8   PDM channel reset.  0: to reset each PDM channel.  1: normal mode. bit 7:0.
// PDM channel enable. each bit for one channel.
#define PDMB_HCIC_CTRL1 ((0x0001 << 2) + 0xfe334800)
// bit 31      hcic filter enable.  1 use sinc filter. 0 bypass input to output.
// bit 29:24.  hcic final gain shift parameter.
// bit 23:16   hcic final gain multiplier.
// bit 8:4     hcic  down sample rate.
// bit 3:0     hcic  stage number. must be between 3 to 9.
#define PDMB_HCIC_CTRL2 ((0x0002 << 2) + 0xfe334800)
// Not used.
#define PDMB_F1_CTRL ((0x0003 << 2) + 0xfe334800)
// bit 31 .   filter 1 enable.
// bit 16:15. f1 round mode.  2'b00 : sign bit at bit 49.  28bits output [49:22] round at bit 21.
// 32bits output [49:18]. 24bits output [49:26]
//                    2'b01 : sign bit at bit 50.  28bits output [50:23] round at bit 22. 32bits
//                    output [49:18]. 24bits output [49:26] 2'b10 : sign bit at bit 51.  28bits
//                    output [51:24] round at bit 23 32bits output [49:18]. 24bits output [49:26].
// bit 15:12. filter 1 down sample rate.
// bit 8:0.   filter 1 stage number.
#define PDMB_F2_CTRL ((0x0004 << 2) + 0xfe334800)
// bit 31 .   filter 2 enable.
// bit 16:15. f2 round mode.  2'b00 : round at bit 21. 2'b01 : round at bit 22.  2'b10 : round at
// bit 23. bit 15:12. filter 2 down sample rate. bit 8:0.   filter 2 stage number.
#define PDMB_F3_CTRL ((0x0005 << 2) + 0xfe334800)
// bit 31 .   filter 3 enable.
// bit 16:15. f3 round mode.  2'b00 : round at bit 21. 2'b01 : round at bit 22.  2'b10 : round at
// bit 23. bit 15:12. filter 3 down sample rate. bit 8:0.   filter 3 stage number.
#define PDMB_HPF_CTRL ((0x0006 << 2) + 0xfe334800)
// bit 31  High pass filter enable.
// bit 20:16 high pass filter shift steps. 6~19 steps.
// bit 15:0 high pass filter output factor.
#define PDMB_CHAN_CTRL ((0x0007 << 2) + 0xfe334800)
// bit 31:24.  chan3 data sample pointer vs edge of the PDM_DCLK.
// bit 23:16   chan2 data sample pointer vs edge of the PDM_DCLK.
// bit 15:8.   chan1 data sample pointer vs edge of the PDM_DCLK.
// bit 7:0     chan0 data sample pointer vs edge of the PDM_DCLK.
#define PDMB_CHAN_CTRL1 ((0x0008 << 2) + 0xfe334800)
// bit 31:24.  chan7 data sample pointer vs edge of the PDM_DCLK.
// bit 23:16   chan6 data sample pointer vs edge of the PDM_DCLK.
// bit 15:8.   chan5 data sample pointer vs edge of the PDM_DCLK.
// bit 7:0     chan4 data sample pointer vs edge of the PDM_DCLK.
#define PDMB_COEFF_ADDR ((0x0009 << 2) + 0xfe334800)
// address of the write/read of coeff data.
#define PDMB_COEFF_DATA ((0x000a << 2) + 0xfe334800)
// write/read data to coeff memory.
#define PDMB_CLKG_CTRL ((0x000b << 2) + 0xfe334800)
// auto clock gating control.  1: disable the clock gating function. the clock will awlays
// enabled. 0 : use RTL auto clock gating.
// 31:7 not used.
// bit 6  filt_ctrl module auto clock gating control.
// bit 5  sinc fifo module auto clock gating control.
// bit 4  filter module auto clock gating control.
// bit 3  apb module auto clock gating control.
// bit 2  coeff memory module auto clock gating control.
// bit 1  each channel module auto clock gating control.
// bit 0 cts_pdm_clk   auto clock gating control.
#define PDMB_STS ((0x000c << 2) + 0xfe334800)
// bit 1  HPF filter output overflow.  means the PCLK is too slow.
// bit 0  HCIC filter output overflow. means the CTS_PDM_CLK is too slow. can't finished the
// filter function.
#define PDMB_MUTE_VALUE ((0x000d << 2) + 0xfe334800)
#define PDMB_MASK_NUM ((0x000e << 2) + 0xfe334800)
#define PDMB_CHAN_CTRL2 ((0x000f << 2) + 0xfe334800)
// bit 7:0    second sample and start FSM point vs rise edge of PDM_DCLK
//========================================================================
//  EQ DRC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe332000
// -----------------------------------------------
#define AED_COEF_RAM_CNTL ((0x0000 << 2) + 0xfe332000)
#define AED_COEF_RAM_DATA ((0x0001 << 2) + 0xfe332000)
#define AED_EQ_EN ((0x0002 << 2) + 0xfe332000)
#define AED_EQ_TAP_CNTL ((0x0003 << 2) + 0xfe332000)
#define AED_EQ_VOLUME ((0x0004 << 2) + 0xfe332000)
#define AED_EQ_VOLUME_SLEW_CNT ((0x0005 << 2) + 0xfe332000)
#define AED_MUTE ((0x0006 << 2) + 0xfe332000)
#define AED_DRC_CNTL ((0x0007 << 2) + 0xfe332000)
#define AED_DRC_RMS_COEF0 ((0x0008 << 2) + 0xfe332000)
#define AED_DRC_RMS_COEF1 ((0x0009 << 2) + 0xfe332000)
#define AED_DRC_THD0 ((0x000a << 2) + 0xfe332000)
#define AED_DRC_THD1 ((0x000b << 2) + 0xfe332000)
#define AED_DRC_THD2 ((0x000c << 2) + 0xfe332000)
#define AED_DRC_THD3 ((0x000d << 2) + 0xfe332000)
#define AED_DRC_THD4 ((0x000e << 2) + 0xfe332000)
#define AED_DRC_K0 ((0x000f << 2) + 0xfe332000)
#define AED_DRC_K1 ((0x0010 << 2) + 0xfe332000)
#define AED_DRC_K2 ((0x0011 << 2) + 0xfe332000)
#define AED_DRC_K3 ((0x0012 << 2) + 0xfe332000)
#define AED_DRC_K4 ((0x0013 << 2) + 0xfe332000)
#define AED_DRC_K5 ((0x0014 << 2) + 0xfe332000)
#define AED_DRC_THD_OUT0 ((0x0015 << 2) + 0xfe332000)
#define AED_DRC_THD_OUT1 ((0x0016 << 2) + 0xfe332000)
#define AED_DRC_THD_OUT2 ((0x0017 << 2) + 0xfe332000)
#define AED_DRC_THD_OUT3 ((0x0018 << 2) + 0xfe332000)
#define AED_DRC_OFFSET ((0x0019 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF00 ((0x001a << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF01 ((0x001b << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF10 ((0x001c << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF11 ((0x001d << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF20 ((0x001e << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF21 ((0x001f << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF30 ((0x0020 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF31 ((0x0021 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF40 ((0x0022 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF41 ((0x0023 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF50 ((0x0024 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF51 ((0x0025 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF00 ((0x0026 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF01 ((0x0027 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF10 ((0x0028 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF11 ((0x0029 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF20 ((0x002a << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF21 ((0x002b << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF30 ((0x002c << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF31 ((0x002d << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF40 ((0x002e << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF41 ((0x002f << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF50 ((0x0030 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF51 ((0x0031 << 2) + 0xfe332000)
#define AED_DRC_LOOPBACK_CNTL ((0x0032 << 2) + 0xfe332000)
#define AED_MDRC_CNTL ((0x0033 << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF00 ((0x0034 << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF01 ((0x0035 << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF00 ((0x0036 << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF01 ((0x0037 << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF00 ((0x0038 << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF01 ((0x0039 << 2) + 0xfe332000)
#define AED_MDRC_THD0 ((0x003a << 2) + 0xfe332000)
#define AED_MDRC_K0 ((0x003b << 2) + 0xfe332000)
#define AED_MDRC_LOW_GAIN ((0x003c << 2) + 0xfe332000)
#define AED_MDRC_OFFSET0 ((0x003d << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF10 ((0x003e << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF11 ((0x003f << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF10 ((0x0040 << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF11 ((0x0041 << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF10 ((0x0042 << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF11 ((0x0043 << 2) + 0xfe332000)
#define AED_MDRC_THD1 ((0x0044 << 2) + 0xfe332000)
#define AED_MDRC_K1 ((0x0045 << 2) + 0xfe332000)
#define AED_MDRC_OFFSET1 ((0x0046 << 2) + 0xfe332000)
#define AED_MDRC_MID_GAIN ((0x0047 << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF20 ((0x0048 << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF21 ((0x0049 << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF20 ((0x004a << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF21 ((0x004b << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF20 ((0x004c << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF21 ((0x004d << 2) + 0xfe332000)
#define AED_MDRC_THD2 ((0x004e << 2) + 0xfe332000)
#define AED_MDRC_K2 ((0x004f << 2) + 0xfe332000)
#define AED_MDRC_OFFSET2 ((0x0050 << 2) + 0xfe332000)
#define AED_MDRC_HIGH_GAIN ((0x0051 << 2) + 0xfe332000)
#define AED_ED_CNTL ((0x0052 << 2) + 0xfe332000)
#define AED_DC_EN ((0x0053 << 2) + 0xfe332000)
#define AED_ND_LOW_THD ((0x0054 << 2) + 0xfe332000)
#define AED_ND_HIGH_THD ((0x0055 << 2) + 0xfe332000)
#define AED_ND_CNT_THD ((0x0056 << 2) + 0xfe332000)
#define AED_ND_SUM_NUM ((0x0057 << 2) + 0xfe332000)
#define AED_ND_CZ_NUM ((0x0058 << 2) + 0xfe332000)
#define AED_ND_SUM_THD0 ((0x0059 << 2) + 0xfe332000)
#define AED_ND_SUM_THD1 ((0x005a << 2) + 0xfe332000)
#define AED_ND_CZ_THD0 ((0x005b << 2) + 0xfe332000)
#define AED_ND_CZ_THD1 ((0x005c << 2) + 0xfe332000)
#define AED_ND_COND_CNTL ((0x005d << 2) + 0xfe332000)
#define AED_ND_RELEASE_COEF0 ((0x005e << 2) + 0xfe332000)
#define AED_ND_RELEASE_COEF1 ((0x005f << 2) + 0xfe332000)
#define AED_ND_ATTACK_COEF0 ((0x0060 << 2) + 0xfe332000)
#define AED_ND_ATTACK_COEF1 ((0x0061 << 2) + 0xfe332000)
#define AED_ND_CNTL ((0x0062 << 2) + 0xfe332000)
#define AED_MIX0_LL ((0x0063 << 2) + 0xfe332000)
#define AED_MIX0_RL ((0x0064 << 2) + 0xfe332000)
#define AED_MIX0_LR ((0x0065 << 2) + 0xfe332000)
#define AED_MIX0_RR ((0x0066 << 2) + 0xfe332000)
#define AED_CLIP_THD ((0x0067 << 2) + 0xfe332000)
#define AED_CH1_ND_SUM_OUT ((0x0068 << 2) + 0xfe332000)
#define AED_CH2_ND_SUM_OUT ((0x0069 << 2) + 0xfe332000)
#define AED_CH1_ND_CZ_OUT ((0x006a << 2) + 0xfe332000)
#define AED_CH2_ND_CZ_OUT ((0x006b << 2) + 0xfe332000)
#define AED_NOISE_STATUS ((0x006c << 2) + 0xfe332000)
#define AED_POW_CURRENT_S0 ((0x006d << 2) + 0xfe332000)
#define AED_POW_CURRENT_S1 ((0x006e << 2) + 0xfe332000)
#define AED_POW_CURRENT_S2 ((0x006f << 2) + 0xfe332000)
#define AED_POW_OUT0 ((0x0070 << 2) + 0xfe332000)
#define AED_POW_OUT1 ((0x0071 << 2) + 0xfe332000)
#define AED_POW_OUT2 ((0x0072 << 2) + 0xfe332000)
#define AED_POW_ADJ_INDEX0 ((0x0073 << 2) + 0xfe332000)
#define AED_POW_ADJ_INDEX1 ((0x0074 << 2) + 0xfe332000)
#define AED_POW_ADJ_INDEX2 ((0x0075 << 2) + 0xfe332000)
#define AED_DRC_GAIN_INDEX0 ((0x0076 << 2) + 0xfe332000)
#define AED_DRC_GAIN_INDEX1 ((0x0077 << 2) + 0xfe332000)
#define AED_DRC_GAIN_INDEX2 ((0x0078 << 2) + 0xfe332000)
#define AED_CH1_VOLUME_STATE ((0x0079 << 2) + 0xfe332000)
#define AED_CH2_VOLUME_STATE ((0x007a << 2) + 0xfe332000)
#define AED_CH1_VOLUME_GAIN ((0x007b << 2) + 0xfe332000)
#define AED_CH2_VOLUME_GAIN ((0x007c << 2) + 0xfe332000)
#define AED_FULL_POW_CURRENT ((0x007d << 2) + 0xfe332000)
#define AED_FULL_POW_OUT ((0x007e << 2) + 0xfe332000)
#define AED_FULL_POW_ADJ ((0x007f << 2) + 0xfe332000)
#define AED_FULL_DRC_GAIN ((0x0080 << 2) + 0xfe332000)
#define AED_MASTER_VOLUME_STATE ((0x0081 << 2) + 0xfe332000)
#define AED_MASTER_VOLUME_GAIN ((0x0082 << 2) + 0xfe332000)
#define AED_TOP_CTL0 ((0x0083 << 2) + 0xfe332000)
#define AED_TOP_CTL1 ((0x0084 << 2) + 0xfe332000)
#define AED_TOP_CTL2 ((0x0085 << 2) + 0xfe332000)
#define AED_TOP_ST0 ((0x0086 << 2) + 0xfe332000)
#define AED_TOP_ST1 ((0x0087 << 2) + 0xfe332000)
#define AED_EQDRC_DYNAMIC_CNTL ((0x0090 << 2) + 0xfe332000)
#define AED_COEF_RAM_CNTL_B ((0x0091 << 2) + 0xfe332000)
#define AED_COEF_RAM_DATA_B ((0x0092 << 2) + 0xfe332000)
#define AED_DRC_RMS_COEF0_B ((0x0093 << 2) + 0xfe332000)
#define AED_DRC_RMS_COEF1_B ((0x0094 << 2) + 0xfe332000)
#define AED_DRC_THD0_B ((0x0095 << 2) + 0xfe332000)
#define AED_DRC_THD1_B ((0x0096 << 2) + 0xfe332000)
#define AED_DRC_THD2_B ((0x0097 << 2) + 0xfe332000)
#define AED_DRC_THD3_B ((0x0098 << 2) + 0xfe332000)
#define AED_DRC_THD4_B ((0x0099 << 2) + 0xfe332000)
#define AED_DRC_K0_B ((0x009a << 2) + 0xfe332000)
#define AED_DRC_K1_B ((0x009b << 2) + 0xfe332000)
#define AED_DRC_K2_B ((0x009c << 2) + 0xfe332000)
#define AED_DRC_K3_B ((0x009d << 2) + 0xfe332000)
#define AED_DRC_K4_B ((0x009e << 2) + 0xfe332000)
#define AED_DRC_K5_B ((0x009f << 2) + 0xfe332000)
#define AED_DRC_THD_OUT0_B ((0x00a0 << 2) + 0xfe332000)
#define AED_DRC_THD_OUT1_B ((0x00a1 << 2) + 0xfe332000)
#define AED_DRC_THD_OUT2_B ((0x00a2 << 2) + 0xfe332000)
#define AED_DRC_THD_OUT3_B ((0x00a3 << 2) + 0xfe332000)
#define AED_DRC_OFFSET_B ((0x00a4 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF00_B ((0x00a5 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF01_B ((0x00a6 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF10_B ((0x00a7 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF11_B ((0x00a8 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF20_B ((0x00a9 << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF21_B ((0x00aa << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF30_B ((0x00ab << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF31_B ((0x00ac << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF40_B ((0x00ad << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF41_B ((0x00ae << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF50_B ((0x00af << 2) + 0xfe332000)
#define AED_DRC_RELEASE_COEF51_B ((0x00b0 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF00_B ((0x00b1 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF01_B ((0x00b2 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF10_B ((0x00b3 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF11_B ((0x00b4 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF20_B ((0x00b5 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF21_B ((0x00b6 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF30_B ((0x00b7 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF31_B ((0x00b8 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF40_B ((0x00b9 << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF41_B ((0x00ba << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF50_B ((0x00bb << 2) + 0xfe332000)
#define AED_DRC_ATTACK_COEF51_B ((0x00bc << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF00_B ((0x00bd << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF01_B ((0x00be << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF10_B ((0x00bf << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF11_B ((0x00c0 << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF20_B ((0x00c1 << 2) + 0xfe332000)
#define AED_MDRC_RMS_COEF21_B ((0x00c2 << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF00_B ((0x00c3 << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF01_B ((0x00c4 << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF10_B ((0x00c5 << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF11_B ((0x00c6 << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF20_B ((0x00c7 << 2) + 0xfe332000)
#define AED_MDRC_RELEASE_COEF21_B ((0x00c8 << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF00_B ((0x00c9 << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF01_B ((0x00ca << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF10_B ((0x00cb << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF11_B ((0x00cc << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF20_B ((0x00cd << 2) + 0xfe332000)
#define AED_MDRC_ATTACK_COEF21_B ((0x00ce << 2) + 0xfe332000)
#define AED_MDRC_THD0_B ((0x00cf << 2) + 0xfe332000)
#define AED_MDRC_THD1_B ((0x00d0 << 2) + 0xfe332000)
#define AED_MDRC_THD2_B ((0x00d1 << 2) + 0xfe332000)
#define AED_MDRC_K0_B ((0x00d2 << 2) + 0xfe332000)
#define AED_MDRC_K1_B ((0x00d3 << 2) + 0xfe332000)
#define AED_MDRC_K2_B ((0x00d4 << 2) + 0xfe332000)
#define AED_MDRC_OFFSET0_B ((0x00d5 << 2) + 0xfe332000)
#define AED_MDRC_OFFSET1_B ((0x00d6 << 2) + 0xfe332000)
#define AED_MDRC_OFFSET2_B ((0x00d7 << 2) + 0xfe332000)
#define AED_MDRC_LOW_GAIN_B ((0x00d8 << 2) + 0xfe332000)
#define AED_MDRC_MID_GAIN_B ((0x00d9 << 2) + 0xfe332000)
#define AED_MDRC_HIGH_GAIN_B ((0x00da << 2) + 0xfe332000)
#define AED_DRC_CNTL_B ((0x00db << 2) + 0xfe332000)
#define AED_DRC_LOOPBACK_CNTL_B ((0x00dc << 2) + 0xfe332000)
#define AED_MDRC_CNTL_B ((0x00dd << 2) + 0xfe332000)
#define AED_STATUS_REG ((0x00de << 2) + 0xfe332000)
//========================================================================
//  AUDIO locker - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe331400
// -----------------------------------------------
#define AUD_LOCK_EN ((0x0000 << 2) + 0xfe331400)
#define AUD_LOCK_SW_RESET ((0x0001 << 2) + 0xfe331400)
#define AUD_LOCK_SW_LATCH ((0x0002 << 2) + 0xfe331400)
#define AUD_LOCK_HW_LATCH ((0x0003 << 2) + 0xfe331400)
#define AUD_LOCK_REFCLK_SRC ((0x0004 << 2) + 0xfe331400)
#define AUD_LOCK_REFCLK_LAT_INT ((0x0005 << 2) + 0xfe331400)
#define AUD_LOCK_IMCLK_LAT_INT ((0x0006 << 2) + 0xfe331400)
#define AUD_LOCK_OMCLK_LAT_INT ((0x0007 << 2) + 0xfe331400)
#define AUD_LOCK_REFCLK_DS_INT ((0x0008 << 2) + 0xfe331400)
#define AUD_LOCK_IMCLK_DS_INT ((0x0009 << 2) + 0xfe331400)
#define AUD_LOCK_OMCLK_DS_INT ((0x000a << 2) + 0xfe331400)
#define AUD_LOCK_INT_CLR ((0x000b << 2) + 0xfe331400)
#define AUD_LOCK_GCLK_CTRL ((0x000c << 2) + 0xfe331400)
#define AUD_LOCK_INT_CTRL ((0x000d << 2) + 0xfe331400)
#define RO_REF2IMCLK_CNT_L ((0x0010 << 2) + 0xfe331400)
#define RO_REF2IMCLK_CNT_H ((0x0011 << 2) + 0xfe331400)
#define RO_REF2OMCLK_CNT_L ((0x0012 << 2) + 0xfe331400)
#define RO_REF2OMCLK_CNT_H ((0x0013 << 2) + 0xfe331400)
#define RO_IMCLK2REF_CNT_L ((0x0014 << 2) + 0xfe331400)
#define RO_IMCLK2REF_CNT_H ((0x0015 << 2) + 0xfe331400)
#define RO_OMCLK2REF_CNT_L ((0x0016 << 2) + 0xfe331400)
#define RO_OMCLK2REF_CNT_H ((0x0017 << 2) + 0xfe331400)
#define RO_REFCLK_PKG_CNT ((0x0018 << 2) + 0xfe331400)
#define RO_IMCLK_PKG_CNT ((0x0019 << 2) + 0xfe331400)
#define RO_OMCLK_PKG_CNT ((0x001a << 2) + 0xfe331400)
#define RO_AUD_LOCK_INT_STATUS ((0x001b << 2) + 0xfe331400)
//========================================================================
//  AUDIO lockerB - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe334400
// -----------------------------------------------
#define AUD_LOCKB_EN ((0x0000 << 2) + 0xfe334400)
#define AUD_LOCKB_SW_RESET ((0x0001 << 2) + 0xfe334400)
#define AUD_LOCKB_SW_LATCH ((0x0002 << 2) + 0xfe334400)
#define AUD_LOCKB_HW_LATCH ((0x0003 << 2) + 0xfe334400)
#define AUD_LOCKB_REFCLK_SRC ((0x0004 << 2) + 0xfe334400)
#define AUD_LOCKB_REFCLK_LAT_INT ((0x0005 << 2) + 0xfe334400)
#define AUD_LOCKB_IMCLK_LAT_INT ((0x0006 << 2) + 0xfe334400)
#define AUD_LOCKB_OMCLK_LAT_INT ((0x0007 << 2) + 0xfe334400)
#define AUD_LOCKB_REFCLK_DS_INT ((0x0008 << 2) + 0xfe334400)
#define AUD_LOCKB_IMCLK_DS_INT ((0x0009 << 2) + 0xfe334400)
#define AUD_LOCKB_OMCLK_DS_INT ((0x000a << 2) + 0xfe334400)
#define AUD_LOCKB_INT_CLR ((0x000b << 2) + 0xfe334400)
#define AUD_LOCKB_GCLK_CTRL ((0x000c << 2) + 0xfe334400)
#define AUD_LOCKB_INT_CTRL ((0x000d << 2) + 0xfe334400)
#define ROB_REF2IMCLK_CNT_L ((0x0010 << 2) + 0xfe334400)
#define ROB_REF2IMCLK_CNT_H ((0x0011 << 2) + 0xfe334400)
#define ROB_REF2OMCLK_CNT_L ((0x0012 << 2) + 0xfe334400)
#define ROB_REF2OMCLK_CNT_H ((0x0013 << 2) + 0xfe334400)
#define ROB_IMCLK2REF_CNT_L ((0x0014 << 2) + 0xfe334400)
#define ROB_IMCLK2REF_CNT_H ((0x0015 << 2) + 0xfe334400)
#define ROB_OMCLK2REF_CNT_L ((0x0016 << 2) + 0xfe334400)
#define ROB_OMCLK2REF_CNT_H ((0x0017 << 2) + 0xfe334400)
#define ROB_REFCLK_PKG_CNT ((0x0018 << 2) + 0xfe334400)
#define ROB_IMCLK_PKG_CNT ((0x0019 << 2) + 0xfe334400)
#define ROB_OMCLK_PKG_CNT ((0x001a << 2) + 0xfe334400)
#define ROB_AUD_LOCK_INT_STATUS ((0x001b << 2) + 0xfe334400)
//========================================================================
//  AUDIO VAD - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe331800
// -----------------------------------------------
//
// Reading file:  VAD_REG.h
//
#define VAD_TOP_CTRL0 ((0x0000 << 2) + 0xfe331800)
#define VAD_TOP_CTRL1 ((0x0001 << 2) + 0xfe331800)
#define VAD_TOP_CTRL2 ((0x0002 << 2) + 0xfe331800)
#define VAD_FIR_CTRL ((0x0003 << 2) + 0xfe331800)
#define VAD_FIR_EMP ((0x0004 << 2) + 0xfe331800)
#define VAD_FIR_COEF0 ((0x0005 << 2) + 0xfe331800)
#define VAD_FIR_COEF1 ((0x0006 << 2) + 0xfe331800)
#define VAD_FIR_COEF2 ((0x0007 << 2) + 0xfe331800)
#define VAD_FIR_COEF3 ((0x0008 << 2) + 0xfe331800)
#define VAD_FIR_COEF4 ((0x0009 << 2) + 0xfe331800)
#define VAD_FIR_COEF5 ((0x000a << 2) + 0xfe331800)
#define VAD_FIR_COEF6 ((0x000b << 2) + 0xfe331800)
#define VAD_FIR_COEF7 ((0x000c << 2) + 0xfe331800)
#define VAD_FIR_COEF8 ((0x000d << 2) + 0xfe331800)
#define VAD_FIR_COEF9 ((0x000e << 2) + 0xfe331800)
#define VAD_FIR_COEF10 ((0x000f << 2) + 0xfe331800)
#define VAD_FIR_COEF11 ((0x0010 << 2) + 0xfe331800)
#define VAD_FIR_COEF12 ((0x0011 << 2) + 0xfe331800)
#define VAD_FRAME_CTRL0 ((0x0012 << 2) + 0xfe331800)
#define VAD_FRAME_CTRL1 ((0x0013 << 2) + 0xfe331800)
#define VAD_FRAME_CTRL2 ((0x0014 << 2) + 0xfe331800)
#define VAD_CEP_CTRL0 ((0x0015 << 2) + 0xfe331800)
#define VAD_CEP_CTRL1 ((0x0016 << 2) + 0xfe331800)
#define VAD_CEP_CTRL2 ((0x0017 << 2) + 0xfe331800)
#define VAD_CEP_CTRL3 ((0x0018 << 2) + 0xfe331800)
#define VAD_CEP_CTRL4 ((0x0019 << 2) + 0xfe331800)
#define VAD_CEP_CTRL5 ((0x001a << 2) + 0xfe331800)
#define VAD_DEC_CTRL ((0x001b << 2) + 0xfe331800)
#define VAD_TOP_STS0 ((0x001c << 2) + 0xfe331800)
#define VAD_TOP_STS1 ((0x001d << 2) + 0xfe331800)
#define VAD_TOP_STS2 ((0x001e << 2) + 0xfe331800)
#define VAD_FIR_STS0 ((0x001f << 2) + 0xfe331800)
#define VAD_FIR_STS1 ((0x0020 << 2) + 0xfe331800)
#define VAD_POW_STS0 ((0x0021 << 2) + 0xfe331800)
#define VAD_POW_STS1 ((0x0022 << 2) + 0xfe331800)
#define VAD_POW_STS2 ((0x0023 << 2) + 0xfe331800)
#define VAD_FFT_STS0 ((0x0024 << 2) + 0xfe331800)
#define VAD_FFT_STS1 ((0x0025 << 2) + 0xfe331800)
#define VAD_SPE_STS0 ((0x0026 << 2) + 0xfe331800)
#define VAD_SPE_STS1 ((0x0027 << 2) + 0xfe331800)
#define VAD_SPE_STS2 ((0x0028 << 2) + 0xfe331800)
#define VAD_SPE_STS3 ((0x0029 << 2) + 0xfe331800)
#define VAD_DEC_STS0 ((0x002a << 2) + 0xfe331800)
#define VAD_DEC_STS1 ((0x002b << 2) + 0xfe331800)
#define VAD_LUT_CTRL ((0x002c << 2) + 0xfe331800)
#define VAD_LUT_WR ((0x002d << 2) + 0xfe331800)
#define VAD_LUT_RD ((0x002e << 2) + 0xfe331800)
#define VAD_IN_SEL0 ((0x002f << 2) + 0xfe331800)
#define VAD_IN_SEL1 ((0x0030 << 2) + 0xfe331800)
#define VAD_TO_DDR ((0x0031 << 2) + 0xfe331800)
#define VAD_SYNC_CTRL0 ((0x0032 << 2) + 0xfe331800)
#define VAD_SYNC_CHNUM_ID0 ((0x0033 << 2) + 0xfe331800)
#define VAD_SYNC_CHNUM_ID1 ((0x0034 << 2) + 0xfe331800)
#define VAD_SYNC_CHNUM_ID2 ((0x0035 << 2) + 0xfe331800)
#define VAD_SYNC_CHNUM_ID3 ((0x0036 << 2) + 0xfe331800)
#define VAD_SYNC_CHNUM_ID4 ((0x0037 << 2) + 0xfe331800)
#define VAD_SYNC_CHNUM_ID5 ((0x0038 << 2) + 0xfe331800)
#define VAD_SYNC_CHNUM_ID6 ((0x0039 << 2) + 0xfe331800)
#define VAD_SYNC_CHNUM_ID7 ((0x003a << 2) + 0xfe331800)
//
// Closing file:  VAD_REG.h
//
//========================================================================
//  AUDIO RESAMPLEA - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe331c00
// -----------------------------------------------
//
// Reading file:  RESAMPLE.h
//
#define AUDIO_RSAMP_CTRL0 ((0x0000 << 2) + 0xfe331c00)
// Bit   31:3      reserved
// Bit   2         reg_lock_rst      //unsigned  , default =0;
// Bit   1         reg_rsamp_rst     //unsigned  , default =0;
// Bit   0         reg_sw_rst        //unsigned  , default =0;
#define AUDIO_RSAMP_CTRL1 ((0x0001 << 2) + 0xfe331c00)
// Bit   31:27      reg_in_lsb        //unsigned  , default =0;
// Bit   26         reg_watchdog_en   //unsigned  , default =0;
// Bit   25         reg_rsamp_rst_sel //unsigned  , default =0;
// Bit   24         reg_module_bypas  //unsigned  , default =0;
// Bit   23:18      reg_gclk_ctrl     //unsigned  , default =0;
// Bit   17:13      reg_in_msb        //unsigned  , default =23;
// Bit   12         reg_output_en     //unsigned  , default =0;
// Bit   11         reg_rsamp_en      //unsigned  , default =0;
// Bit   10         reg_filt_en       //unsigned  , default =0;
// Bit   9          reg_post_en       //unsigned  , default =0;
// Bit   8          reg_inp_mux_mode  //unsigned  , default =0;
// Bit   7:5        reserved          //unsigned  , default =2;
// Bit   4:0        reg_inp_mux       //unsigned  , default =0;
#define AUDIO_RSAMP_CTRL2 ((0x0002 << 2) + 0xfe331c00)
// Bit 31:30    reserved              //unsigned  , default =0;
// Bit 29:24    reg_chx_size          //unsigned  , default =2;
// Bit 23:18    reserved              //unsigned  , default =0;
// Bit 17:16    reg_scl_step          //unsigned  , default =0; 0: 1/1  1: 1/2  2: 1/4
// Bit 15:8     reg_filt_tap          //unsigned  , default =63;
// Bit 7:0      reg_intp_tap          //unsigned  , default =63;
#define AUDIO_RSAMP_PHSINIT ((0x0003 << 2) + 0xfe331c00)
// Bit   31:28      reserved          //unsigned  , default = 0;
// Bit   27:0       reg_init_phs      //unsigned  , default = 0;
#define AUDIO_RSAMP_PHSSTEP ((0x0004 << 2) + 0xfe331c00)
// Bit   31         reserved          //unsigned  , default = 0;
// Bit   30:0       reg_rsamp_step    //unsigned  , default = 134217728;//'h800_0000
#define AUDIO_RSAMP_SHIFT ((0x0005 << 2) + 0xfe331c00)
// Bit   31:24       reg_rsft_iir    //unsigned  , default = 23;
// Bit   23:16       reg_rsft_blnd   //unsigned  , default = 21;
// Bit   15:8        reg_rsft_sinc   //unsigned  , default = 31;
// Bit   7:0         reg_rsft_aa     //unsigned  , default = 31;
#define AUDIO_RSAMP_ADJ_CTRL0 ((0x0006 << 2) + 0xfe331c00)
// Bit   31:7        reserved                //unsigned
// Bit   6           reg_lock_vld_sel        //unsigned , default = 0;
// Bit   5           reg_loop_dif_clr_en     //unsigned , default = 0;
// Bit   4           reg_aout_force_en       //unsigned , default = 0;
// Bit   3           reserved                //unsigned
// Bit   2           reg_rsamp_adj_out_inv   //unsigned , default = 0;
// Bit   1           reg_rsamp_adj_force_en  //unsigned , default = 0;
// Bit   0           reg_rsamp_adj_en        //unsigned , default = 0;
#define AUDIO_RSAMP_ADJ_CTRL1 ((0x0007 << 2) + 0xfe331c00)
// Bit   31:16       reg_rsamp_adj_odet_step     //unsigned , default = 8;
// Bit   15:0        reg_rsamp_adj_kmax          //unsigned , default = 32768;
#define AUDIO_RSAMP_ADJ_SFT ((0x0008 << 2) + 0xfe331c00)
// Bit   31:30       reserved                //unsigned , default = 0;
// Bit   29          reg_rsamp_adj_dif_sel   //unsigned , default = 0;
// Bit   28:24       reg_rsamp_adj_ki        //unsigned , default = 9;
// Bit   23:21       reserved                //unsigned , default = 0;
// Bit   20:16       reg_rsamp_adj_kp        //unsigned , default = 1;
// Bit   15:13       reserved                //unsigned , default = 0;
// Bit   12:8        reg_rsamp_adj_ki_sft    //unsigned , default = 6;
// Bit   7:6         reserved                //unsigned , default = 0;
// Bit   5:0         reg_rsamp_adj_out_sft   //unsigned , default = 12;
#define AUDIO_RSAMP_ADJ_IDET_LEN ((0x0009 << 2) + 0xfe331c00)
// Bit   31:0       reg_rsamp_adj_idet_len       //unsigned , default = 10000;
#define AUDIO_RSAMP_ADJ_FORCE ((0x000a << 2) + 0xfe331c00)
// Bit   31:0       reg_rsamp_adj_force_err      //signed , default = 8;
#define AUDIO_RSAMP_ADJ_KI_FORCE ((0x000b << 2) + 0xfe331c00)
// Bit   31:0       reg_rsamp_adj_ki_force //signed , default = 0;
#define AUDIO_RSAMP_WATCHDOG_THRD ((0x000c << 2) + 0xfe331c00)
// Bit   31:0       reg_watchdog_thrd      //signed , default = 32'h1000;
#define AUDIO_RSAMP_DBG_INFO ((0x000d << 2) + 0xfe331c00)
// Bit   31:16      reg_aout_force_hi        //unsigned , default = 0;
// Bit   15:7       reserved                 //unsigned , default = 0;
// Bit   6          reg_rsamp_dbgcnt_clr     //unsigned , default = 0;
// Bit   5          reg_rsamp_dbgcnt_vldsel  //unsigned , default = 0;
// Bit   4          reg_rsamp_dbgcnt_en      //unsigned , default = 0;
// Bit   3          reserved                 //unsigned , default = 0;
// Bit   2:0        reg_watchdog_rstsel      //unsigned , default = 4;
#define AUDIO_RSAMP_AOUT_FORCE ((0x000e << 2) + 0xfe331c00)
// Bit   31:0       reg_aout_force_lo        //unsigned , default = 0;
#define AUDIO_RSAMP_IRQ_CTRL ((0x000f << 2) + 0xfe331c00)
// Bit   31:16      reg_irq_thrd             //unsigned , default = 0;
// Bit   15:12      reserved                 //unsigned , default = 0;
// Bit   11:8       reg_irq_sel              //unsigned , default = 0;
// Bit   7:4        reg_irq_clr              //unsigned , default = 0;
// Bit   3:0        reg_irq_en               //unsigned , default = 0;
#define AUDIO_RSAMP_RO_STATUS ((0x0010 << 2) + 0xfe331c00)
// Bit   31:0       ro_rsamp_stat  //{din_chx_chk_err,is_idle_st,rsamp_fifo_over_cnt[7:0]}
#define AUDIO_RSAMP_RO_ADJ_FREQ ((0x0011 << 2) + 0xfe331c00)
// Bit   31:0       ro_rsamp_adj_freq
#define AUDIO_RSAMP_RO_ADJ_DIFF_BAK ((0x0012 << 2) + 0xfe331c00)
// Bit   31:0       ro_det_diff_bak
#define AUDIO_RSAMP_RO_ADJ_DIFF_DLT ((0x0013 << 2) + 0xfe331c00)
// Bit   31:0       ro_det_diff_dlt
#define AUDIO_RSAMP_RO_ADJ_PHS_ERR ((0x0014 << 2) + 0xfe331c00)
// Bit   31:0       ro_det_phase_err
#define AUDIO_RSAMP_RO_ADJ_KI_OUT ((0x0015 << 2) + 0xfe331c00)
// Bit   31:0       ro_rsamp_ki_out
#define AUDIO_RSAMP_RO_IN_CNT ((0x0016 << 2) + 0xfe331c00)
// Bit   31:0       ro_rsamp_in_cnt
#define AUDIO_RSAMP_RO_OUT_CNT ((0x0017 << 2) + 0xfe331c00)
// Bit   31:0       ro_rsamp_out_cnt
#define AUDIO_RSAMP_RO_ADJ_PHS_ERR_VAR ((0x0018 << 2) + 0xfe331c00)
// Bit   31:0       ro_det_phase_err_var
#define AUDIO_RSAMP_POST_COEF0 ((0x0020 << 2) + 0xfe331c00)
// Bit   31:0       reg_post_coef0 //signed  , default = 0;
#define AUDIO_RSAMP_POST_COEF1 ((0x0021 << 2) + 0xfe331c00)
// Bit   31:0       reg_post_coef1 //signed  , default = 0;
#define AUDIO_RSAMP_POST_COEF2 ((0x0022 << 2) + 0xfe331c00)
// Bit   31:0       reg_post_coef2 //signed  , default = 0;
#define AUDIO_RSAMP_POST_COEF3 ((0x0023 << 2) + 0xfe331c00)
// Bit   31:0       reg_post_coef3 //signed  , default = 0;
#define AUDIO_RSAMP_POST_COEF4 ((0x0024 << 2) + 0xfe331c00)
// Bit   31:0       reg_post_coef4 //signed  , default = 0;
#define AUDIO_RSAMP_AA_COEF_ADDR ((0x0030 << 2) + 0xfe331c00)
// Bit   31:0       reg_aa_coef_addr     //unsigned, default = 0;
#define AUDIO_RSAMP_AA_COEF_DATA ((0x0031 << 2) + 0xfe331c00)
// Bit   31:0       reg_aa_coef_data     //signed  , default = 0;
#define AUDIO_RSAMP_SINC_COEF_ADDR ((0x0040 << 2) + 0xfe331c00)
// Bit   31:0       reg_sinc_coef_addr   //unsigned, default = 0;
#define AUDIO_RSAMP_SINC_COEF_DATA ((0x0041 << 2) + 0xfe331c00)
// Bit   31:0       reg_sinc_coef_data   //signed  , default = 0;
//
// Closing file:  RESAMPLE.h
//
//========================================================================
//  AUDIO EARCTX_CMDC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333000
// -----------------------------------------------
//
// Reading file:  earc_tx_cmdc.h
//
#define EARC_TX_CMDC_TOP_CTRL0 ((0x0030 << 2) + 0xfe333000)
// Bit   31   ,      idle2_int          unsigned, default = 0, 1: enable
// Bit   30   ,      idle1_int            unsigned, default = 0, 1: enable
// Bit   29   ,      disc2_int            unsigned, default = 0, 1: enable
// Bit   28   ,      disc1_int            unsigned, default = 0, 1: enable
// Bit   27   ,      earc_int             unsigned, default = 0, 1: enable
// Bit   26   ,      hb_status_int        unsigned, default = 0, 1: enable
// Bit   25   ,      losthb_int           unsigned, default = 0, 1: enable
// Bit   24   ,      timeout_int          unsigned, default = 0, 1: enable
// Bit   23   ,      status_ch_int        unsigned, default = 0, 1: enable
// Bit   22   ,      int_recv_finished  unsigned, default = 0, 1: enable
// Bit   21   ,      int_rdata          unsigned, default = 0, 1: enable
// Bit   20   ,      int_recv_nack       unsigned, default = 0, 1: enable
// Bit   19   ,      int_recv_norsp     unsigned, default = 0, 1: enable
// Bit   18   ,      int_recv_unexp     unsigned, default = 0, 1: enable
// Bit   17   ,      int_recv_data       unsigned, default = 0, 1: enable
// Bit   16   ,      int_recv_ack       unsigned, default = 0, 1: enable
// Bit   15   ,      int_recv_ecc_err   unsigned, default = 0, 1: enable
// Bit   14   ,      int_recv_packet    unsigned, default = 0, 1: enable
// Bit   13:0 ,      reserved
#define EARC_TX_CMDC_TOP_CTRL1 ((0x0031 << 2) + 0xfe333000)
// Bit      31:0,     cmdc_top_ctrl1     //unsigned, RW, default = 0,
#define EARC_TX_CMDC_TOP_CTRL2 ((0x0032 << 2) + 0xfe333000)
// Bit   31   ,     reset_idle2_int              unsigned, default = 0, 1: enable
// Bit   30   ,     reset_idle1_int            unsigned, default = 0, 1: enable
// Bit   29   ,     reset_disc2_int            unsigned, default = 0, 1: enable
// Bit   28   ,     reset_disc1_int            unsigned, default = 0, 1: enable
// Bit   27   ,     reset_earc_int             unsigned, default = 0, 1: enable
// Bit   26   ,     reset_hb_status_int        unsigned, default = 0, 1: enable
// Bit   25   ,     reset_losthb_int           unsigned, default = 0, 1: enable
// Bit   24   ,     reset_timeout_int          unsigned, default = 0, 1: enable
// Bit   23   ,     reset_status_ch_int        unsigned, default = 0, 1: enable
// Bit   22   ,     reset_int_recv_finished        unsigned, default = 0, 1: enable
// Bit   21   ,     reset_int_rdata              unsigned, default = 0, 1: enable
// Bit   20   ,     reset_int_recv_nack       unsigned, default = 0, 1: enable
// Bit   19   ,     reset_int_recv_norsp         unsigned, default = 0, 1: enable
// Bit   18   ,     reset_int_recv_unexp         unsigned, default = 0, 1: enable
// Bit   17   ,     reset_int_recv_data       unsigned, default = 0, 1: enable
// Bit   16   ,     reset_int_recv_ack       unsigned, default = 0, 1: enable
// Bit   15   ,     reset_int_recv_ecc_err       unsigned, default = 0, 1: enable
// Bit   14   ,     reset_int_recv_packet        unsigned, default = 0, 1: enable
// Bit 13:0   ,     reserved
#define EARC_TX_CMDC_TIMER_CTRL0 ((0x0033 << 2) + 0xfe333000)
// Bit      31:0,     cmdc_timer_ctrl0   //unsigned, RW, default = 0,
#define EARC_TX_CMDC_TIMER_CTRL1 ((0x0034 << 2) + 0xfe333000)
// Bit      31:0,     cmdc_timer_ctrl1  //unsigned, RW, default = 0,
#define EARC_TX_CMDC_TIMER_CTRL2 ((0x0035 << 2) + 0xfe333000)
// Bit      31:0,     cmdc_timer_ctrl2  //unsigned, RW, default = 0,
#define EARC_TX_CMDC_TIMER_CTRL3 ((0x0036 << 2) + 0xfe333000)
// Bit      31:0,     cmdc_timer_ctrl3  //unsigned, RW, default = 0,
#define EARC_TX_CMDC_VSM_CTRL0 ((0x0037 << 2) + 0xfe333000)
// Bit      31,      sw_state_update         unsigned, default = 0,  XX
// Bit      30:28,   sw_state                 unsigned, default = 0,  XX
// Bit      27,      arc_initiated             unsigned, default = 0,  XX
// Bit      26,      arc_terminated             unsigned, default = 0,  XX
// Bit      25,      arc_enable                 unsigned, default = 1,  XX
// Bit      24,      man_hpd                 unsigned, default = 0,  XX
// Bit      23:22,   hpd_sel                 unsigned, default = 0,  XX
// Bit      21:20,   hpd_sel_earc            unsigned, default = 0,  XX
// Bit      19,      comma_cnt_rst           unsigned, default = 0,  XX
// Bit      18,      timeout_status_rst      unsigned, default = 0,  XX
// Bit      17,      losthb_status_rst       unsigned, default = 0,  XX
// Bit      16,      force_rst               unsigned, default = 0,  XX
// Bit      15,      auto_state_en           unsigned, default = 0,  XX
// Bit      14,      cmdc_state_en             unsigned, default = 0,  XX
// Bit      13,      noack_repeat_en            unsigned, default = 0,  XX
// Bit    12:0,      reserved
#define EARC_TX_CMDC_VSM_CTRL1 ((0x0038 << 2) + 0xfe333000)
// Bit    31:9,      reserved
// Bit       8,      cntl_hpd_sel            unsigned, default = 0, 0:sel hd_hpd,1:sel hdmirx_hpd
// Bit     7:0,      comma_cnt_th            unsigned, default = 0, should bigger than 3 and small
// than 10
#define EARC_TX_CMDC_VSM_CTRL2 ((0x0039 << 2) + 0xfe333000)
// Bit    31:12,      max_count_th          unsigned, default = 0,  disc1 hpd_val timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  disc1 hpd_val timing
// Bit      6:4,      time_sel              unsigned, default = 0,  disc1 hpd_val timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  disc1 hpd_val timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  disc1 hpd_val timing
#define EARC_TX_CMDC_VSM_CTRL3 ((0x003a << 2) + 0xfe333000)
// Bit    31:12,      max_count_th          unsigned, default = 0,  disc2 heartbeat act timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  disc2 heartbeat act timing
// Bit      6:4,      time_sel              unsigned, default = 0,  disc2 heartbeat act timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  disc2 heartbeat act timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  disc2 heartbeat act timing
#define EARC_TX_CMDC_VSM_CTRL4 ((0x003b << 2) + 0xfe333000)
// Bit    31:12,      max_count_th          unsigned, default = 0,  in disc2, no heartbeat ack
// timing Bit     11:8,      reserved Bit        7,      reg_soft_rst          unsigned, default =
// 0,  in disc2, no heartbeat ack timing Bit      6:4,      time_sel              unsigned, default
// = 0,  in disc2, no heartbeat ack timing Bit      3:2,      soft_rst_sel          unsigned,
// default = 0,  in disc2, no heartbeat ack timing Bit      1:0,      enable_ctrl unsigned, default
// = 0,  in disc2, no heartbeat ack timing
#define EARC_TX_CMDC_VSM_CTRL5 ((0x003c << 2) + 0xfe333000)
// Bit    31:12,      max_count_th          unsigned, default = 0,  in disc1 and disc2 timing out
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  in disc1 and disc2 timing out
// Bit      6:4,      time_sel              unsigned, default = 0,  in disc1 and disc2 timing out
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  in disc1 and disc2 timing out
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  in disc1 and disc2 timing out
#define EARC_TX_CMDC_VSM_CTRL6 ((0x003d << 2) + 0xfe333000)
// Bit    31:12,      max_count_th          unsigned, default = 0,  in earc heartbeat act timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  in earc heartbeat act timing
// Bit      6:4,      time_sel              unsigned, default = 0,  in earc heartbeat act timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  in earc heartbeat act timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  in earc heartbeat act timing
#define EARC_TX_CMDC_VSM_CTRL7 ((0x003e << 2) + 0xfe333000)
// Bit    31:16,      reserved
// Bit     15:8,      status_soft_val       unsigned, default = 0,  in earc heartbeat det timing
// Bit        7,      reg_soft_rst          unsigned, default = 0,  in earc heartbeat det timing
// Bit        6,      status_rst            unsigned, default = 0,  in earc heartbeat det timing
// Bit      5:4,      reserved
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  in earc heartbeat det timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  in earc heartbeat det timing
#define EARC_TX_CMDC_VSM_CTRL8 ((0x003f << 2) + 0xfe333000)
// Bit      31:0,     cmdc_vsm_ctrl8        //unsigned, RW, default = 0,
#define EARC_TX_CMDC_VSM_CTRL9 ((0x0041 << 2) + 0xfe333000)
// Bit      31:0,     cmdc_vsm_ctrl9        //unsigned, RW, default = 0
#define EARC_TX_CMDC_SENDER_CTRL0 ((0x0042 << 2) + 0xfe333000)
// Bit      31:2,     sender_ctrl0                 unsigned,  default = 0,
// Bit      1,        hb_chg_conf_auto             unsigned,  default = 1,
// Bit      0,        hb_chg_auto                  unsigned,  default = 0,
#define EARC_TX_CMDC_PACKET_CTRL0 ((0x0043 << 2) + 0xfe333000)
// Bit        31,      packet_mode_enable          unsigned, default = 0,  packet control
// Bit        30,      free_enable                 unsigned, default = 0,  packet control
// Bit        29,      soft_rst                    unsigned, default = 0,  packet control
// Bit     28:24,      tx_ready_threshold          unsigned, default = 0,  packet control
// Bit     23:20,      reserved
// Bit      19:8,      send_pre_threshold          unsigned, default = 0,  packet control
// Bit       7:6,      reserved
// Bit         5,      state_auto_en               unsigned, default = 0, packet control
// Bit         4,      sw_state_update_en          unsigned, default = 0,  packet control
// Bit       3:0,      sw_state_value              unsigned, default = 0,  packet control
#define EARC_TX_CMDC_PACKET_CTRL1 ((0x0044 << 2) + 0xfe333000)
// Bit        31,      ecc_endian                  unsigned, default = 0,  send
// Bit        30,      pre_start_value             unsigned, default = 0,  send
// Bit     29:21,      reserved
// Bit     20:16,      post_threshold              unsigned, default = 0,  send
// Bit     15:14,      reserved
// Bit      13:8,      pre_threshold               unsigned, default = 0,  XX
// Bit       7:0,      post_flag                   unsigned, default = 0,  XX
#define EARC_TX_CMDC_PACKET_CTRL2 ((0x0045 << 2) + 0xfe333000)
// Bit      31:0,      pre_flag                    unsigned, default = 0,  XX
#define EARC_TX_CMDC_PACKET_CTRL3 ((0x0046 << 2) + 0xfe333000)
// Bit      31,       recv_en                      unsigned, default = 0,  XX
// Bit      30,       recv_parity_mask             unsigned, default = 0,  XX
// Bit      29,       recv_timeout_en              unsigned, default = 0,  XX
// Bit      28,       bch_ecc_en                   unsigned, default = 0, xx
// Bit     27:16,     reserved
// Bit      15:0,     recv_timeout_threshold       unsigned, default = 0,  XX
#define EARC_TX_CMDC_PACKET_CTRL4 ((0x0047 << 2) + 0xfe333000)
// Bit     31:20,     reserved
// Bit      19:0,     recv_packet_head             unsigned, default = 0,  XX
#define EARC_TX_CMDC_PACKET_CTRL5 ((0x0048 << 2) + 0xfe333000)
// Bit     31:20,     reserved
// Bit      19:0,     recv_packet_head_mask        unsigned, default = 0,  XX
#define EARC_TX_CMDC_PACKET_CTRL6 ((0x0049 << 2) + 0xfe333000)
// Bit     31:20,     recv_pre_threshold          unsigned, default = 0,  packet control
// Bit      19:7,     reserved
// Bit         6,     recv_finished_int            unsigned, default = 0,  XX
// Bit         5,     recv_ecc_err_int             unsigned, default = 0,  XX
// Bit         4,     recv_ack_int                 unsigned, default = 0,  XX
// Bit         3,     recv_data_int                unsigned, default = 0,  XX
// Bit         2,     recv_unexp_int               unsigned, default = 0,  XX
// Bit         1,     recv_norsp_int               unsigned, default = 0,  XX
// Bit         0,     recv_nack_int                unsigned, default = 0,  XX
#define EARC_TX_CMDC_BIPHASE_CTRL0 ((0x004a << 2) + 0xfe333000)
// Bit     31:24,     reserved
// Bit     23:16,     ack delay threshold           unsigned, default = 0, xx
// Bit     15:10,     reserved
// Bit         9,     send_ack_en                   unsigned, default = 0,  xx
// Bit         8,     sq_val_en                     unsigned, default = 0,  XX
// Bit         7,     biphase_send_soft_rst         unsigned, default = 0,  XX
// Bit         6,     comma_soft_rst                unsigned, default = 0,  XX
// Bit         5,     fifo_rst                      unsigned, default = 0,  XX
// Bit         4,     receiver_no_sender            unsigned, default = 0,  XX
// Bit         3,     sender_free                   unsigned, default = 0,  XX
// Bit         2,     receiver_send                 unsigned, default = 0,  XX
// Bit         1,     receiver_earc                 unsigned, default = 0,  XX
// Bit         0,     receiver_free                 unsigned, default = 0,  XX
#define EARC_TX_CMDC_BIPHASE_CTRL1 ((0x004b << 2) + 0xfe333000)
// Bit     31:16,     reserved
// Bit        15,     ack_enable                    unsigned, default = 0,  send
// Bit      14:8,     reserved
// Bit       7:0,     wait_threshold before ack     unsigned, default = 0,  send
#define EARC_TX_CMDC_BIPHASE_CTRL2 ((0x004c << 2) + 0xfe333000)
// Bit        31,     comma_detection_enable        unsigned, default = 0, comma detection
// Bit        30,     manual_reset_enable           unsigned, default = 0, manual reset select, 1:
// manual Bit        29,     manual_reset_value            unsigned, default = 0, manual reset
// control Bit     28:16,     reserved Bit      15:0,     comma_detection_threshold     unsigned,
// default = 0,
#define EARC_TX_CMDC_BIPHASE_CTRL3 ((0x004d << 2) + 0xfe333000)
// Bit      31:0,     cmdc_biphase_ctrl3            unsigned, default = 0,
#define EARC_TX_CMDC_DEVICE_ID_CTRL ((0x004e << 2) + 0xfe333000)
// Bit        31,     apb_write                     unsigned, default = 0, apb bus wr/read
// Bit        30,     apb_read                      unsigned, default = 0, apb bus wr/read
// Bit        29,     apb_rw_done                  unsigned, default = 0, apb bus wr/read
// Bit        28,     apb_rw_reset                 unsigned, default = 0, apb bus wr/read
// Bit     27:17,     reserved
// Bit        16,     hpb_rst_enable               unsigned, default = 1, hpd rst enable
// Bit      15:8,     apb_rwid                    unsigned, default = 0, apb bus wr/read
// Bit       7:0,     apbrw_start_addr            unsigned, default = 0, apb bus wr/read
#define EARC_TX_CMDC_DEVICE_WDATA ((0x004f << 2) + 0xfe333000)
// Bit      31:8,     reserved
// Bit       7:0,     apb_write_data                unsigned, default = 0, apb bus wr/read
#define EARC_TX_CMDC_DEVICE_RDATA ((0x0050 << 2) + 0xfe333000)
// Bit      31:8,     reserved
// Bit       7:0,     apb_read_data                 unsigned, default = 0, apb bus wr/read
#define EARC_TX_CMDC_MASTER_CTRL ((0x0051 << 2) + 0xfe333000)
// Bit        31,     master_cmd_rw                 unsigned, default = 0, 1 write 0 read
// Bit        30,     master_hb_ignore              unsigned, default =0, 0:wait hb issued before
// pkt cmd, 1: pkt cmd issued immediately Bit        29,     master_idle unsigned, default = 0,
// master status Bit        28,     master_cmd_soft_rst           unsigned, default= 0, Bit 27:24,
// hb_cmd_cal_th                 unsigned, default= 0, Bit     23:16,     master_cmd_count
// unsigned, default = 0, cmd count -1 Bit      15:8,     master_cmd_id                 unsigned,
// default = 0, Bit       7:0,     master_cmd_address            unsigned, default = 0,
#define EARC_TX_ANA_CTRL0 ((0x0052 << 2) + 0xfe333000)
// Bit      31:0,      reg_earctx_ana_ctrl0       //unsigned, RW, default = 0,
#define EARC_TX_ANA_CTRL1 ((0x0053 << 2) + 0xfe333000)
// Bit      31:0,      reg_earctx_ana_ctrl1       //unsigned, RW, default = 0,
#define EARC_TX_ANA_CTRL2 ((0x0054 << 2) + 0xfe333000)
// Bit      31:0,      reg_earctx_ana_ctrl2       //unsigned, RW, default = 0,
#define EARC_TX_ANA_CTRL3 ((0x0055 << 2) + 0xfe333000)
// Bit      31:0,      reg_earctx_ana_ctrl3       //unsigned, RW, default = 0,
#define EARC_TX_ANA_CTRL4 ((0x0056 << 2) + 0xfe333000)
// Bit      31:0,      reg_earctx_ana_ctrl4       //unsigned, RW, default = 0,
#define EARC_TX_ANA_CTRL5 ((0x0057 << 2) + 0xfe333000)
// Bit      31:0,      reg_earctx_ana_ctrl5       //unsigned, RW, default = 0,
#define EARC_TX_ANA_STAT0 ((0x0058 << 2) + 0xfe333000)
// Bit      31:0,     ro_ANA_status0              //unsigned, RO, default = 0,
#define EARC_TX_CMDC_STATUS0 ((0x0059 << 2) + 0xfe333000)
// Bit      31:0,     ro_cmdc_status0              //unsigned, RO, default = 0,
#define EARC_TX_CMDC_STATUS1 ((0x005a << 2) + 0xfe333000)
// Bit      31:0,     ro_cmdc_status1              ///unsigned, RO, default = 0,
#define EARC_TX_CMDC_STATUS2 ((0x005b << 2) + 0xfe333000)
// Bit      31:0,     ro_cmdc_status2              ///unsigned, RO, default = 0,
#define EARC_TX_CMDC_STATUS3 ((0x005c << 2) + 0xfe333000)
// Bit      31:0,     ro_cmdc_status3              ///unsigned, RO, default = 0,
#define EARC_TX_CMDC_STATUS4 ((0x005d << 2) + 0xfe333000)
// Bit      31:0,     ro_cmdc_status4              ///unsigned, RO, default = 0,
#define EARC_TX_CMDC_STATUS5 ((0x005e << 2) + 0xfe333000)
// Bit      31:0,     ro_cmdc_status5              ///unsigned, RO, default = 0,
#define EARC_TX_CMDC_STATUS6 ((0x005f << 2) + 0xfe333000)
// Bit   31   ,     ro_idle2_int            unsigned, RO, default = 0
// Bit   30   ,     ro_idle1_int            unsigned, RO, default = 0
// Bit   29   ,     ro_disc2_int            unsigned, RO, default = 0
// Bit   28   ,     ro_disc1_int            unsigned, RO, default = 0
// Bit   27   ,     ro_earc_int             unsigned, RO, default = 0
// Bit   26   ,     ro_hb_status_int        unsigned, RO, default = 0
// Bit   25   ,     ro_losthb_int           unsigned, RO, default = 0
// Bit   24   ,     ro_timeout_int          unsigned, RO, default = 0
// Bit   23   ,     ro_status_ch_int        unsigned, RO, default = 0
// Bit   22   ,     ro_int_recv_finished    unsigned, RO, default = 0
// Bit   21   ,     ro_int_rdata            unsigned, RO, default = 0
// Bit   20   ,     ro_int_recv_nack        unsigned, RO, default = 0
// Bit   19   ,     ro_int_recv_norsp       unsigned, RO, default = 0
// Bit   18   ,     ro_int_recv_unexp       unsigned, RO, default = 0
// Bit   17   ,     ro_int_recv_data        unsigned, RO, default = 0
// Bit   16   ,     ro_int_recv_ack         unsigned, RO, default = 0
// Bit   15   ,     ro_int_recv_ecc_err     unsigned, RO, default = 0
// Bit   14   ,     ro_int_recv_packet      unsigned, RO, default = 0
// Bit 13:0   ,     reserved
//
// Closing file:  earc_tx_cmdc.h
//
//========================================================================
//  AUDIO EARCTX_DMAC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333400
// -----------------------------------------------
//
// Reading file:  earctx_dmac.h
//
#define EARCTX_DMAC_TOP_CTRL0 ((0x0000 << 2) + 0xfe333400)
// Bit 31,       reg_top_reg_sync             ,default = 0,Bit 3:0 sync to clk10m,pluse auto clear
// Bit 30,       reg_top_soft_rst             ,default = 0
// Bit 29:26,    reserved
// Bit 25:24,    reg_debug_mux                ,default = 0
// Bit 23:21,    reserved
// Bit 20,       reg_slow_sync_scan_reg       ,default = 0
// Bit 19,       reg_fe_sf_scan_reg           ,default = 0
// Bit 18,       reg_fe_slow_sync_scan_reg    ,default = 0
// Bit 17,       reg_top_sf_scan_reg          ,default = 0
// Bit 16,       reg_top_slow_sync_scan_reg   ,default = 0
// Bit 15:4,     reserved
// Bit 3,        reg_spdif_tx_en_force        ,default = 0,spdif_tx_en force enable
// Bit 2,        reg_spdif_tx_en_force_value  ,default = 0,spdif_tx_en force value
// Bit 1,        reg_dmac_tx_en_force         ,default = 0,dmac_tx_en force enable
// Bit 0,        reg_dmac_tx_en_force_value   ,default = 0,dmac_tx_en force value
#define EARCTX_MUTE_VAL ((0x0001 << 2) + 0xfe333400)
// Bit 31:0,     reg_spdif_mute_val     ,default = 0,when biahpase encode mute,the channel
// value,with reg_mute_l/reg_mute_r
#define EARCTX_SPDIFOUT_GAIN0 ((0x0002 << 2) + 0xfe333400)
// Bit 31:24,    reg_gain_ch3     ,default = 0,channel 3 gain
// Bit 23:16,    reg_gain_ch2     ,default = 0,channel 2 gain
// Bit 15:8,     reg_gain_ch1     ,default = 0,channel 1 gain
// Bit 7:0,      reg_gain_ch0     ,default = 0,channel 0 gain
#define EARCTX_SPDIFOUT_GAIN1 ((0x0003 << 2) + 0xfe333400)
// Bit 31:24,    reg_gain_ch7     ,default = 0,channel 7 gain
// Bit 23:16,    reg_gain_ch6     ,default = 0,channel 6 gain
// Bit 15:8,     reg_gain_ch5     ,default = 0,channel 5 gain
// Bit 7:0,      reg_gain_ch4     ,default = 0,channel 4 gain
#define EARCTX_SPDIFOUT_CTRL0 ((0x0004 << 2) + 0xfe333400)
// Bit 31,     reg_work_start      ,default = 0,biphase work start,pluse
// Bit 30,     reg_work_clr        ,default = 0,biphase work clear,pluse
// Bit 29,     reg_rst_afifo_out_n ,default = 0,afifo out reset
// Bit 28,     reg_rst_afifo_in_n  ,default = 0,afifo in reset
// Bit 27,     reg_hold_for_tdm    ,default = 0,add delay to mathc TDM out when share buff
// Bit 26,     reg_userdata_sel    ,default = 0,user Bit select : 0 from reg_userdata_set 1 from
// data[29] Bit 25,     reg_userdata_set    ,default = 0 Bit 24,     reg_chdata_sel      ,default =
// 0,0 :from reg_chstst 1 from data[30] Bit 23,     reserved Bit 22,     reg_mute_l ,default = 0,r
// channel mute ,with reg_mute_val Bit 21,     reg_mute_r          ,default = 0,l channel mute
// ,with reg_mute_val Bit 20,     reg_data_sel        ,default = 0,0 data from 31Bit 1 data from
// 27bit Bit 19,     reg_out_msb_first   ,default = 0,0 lsb first 1 msb first Bit 18, reg_valid_sel
// ,default = 0,biphase encode valid Bit value sel : 0 from data 1 from reg_valid_set Bit 17,
// reg_valid_set       ,default = 0,biphase encode valid Bit value Bit 16, reg_mute_hold_init_en
// ,default = 0,when c_mute_hold_last_err_corrt valid,clear work enable, initial biphase encode Bit
// 15:12,  reserved Bit 0,      reg_parity_mask     ,default = 0,Bit 0 is initial parity value
#define EARCTX_SPDIFOUT_CTRL1 ((0x0005 << 2) + 0xfe333400)
// Bit 31,     reg_eq_drc_sel      ,default = 0,set 1 select eq_drc data
// Bit 30,     reg_keep_req_ddr_init ,default = 0,reg_keep_req_ddr_init
// Bit 29:28,  reserved
// Bit 27,     reg_gain_en         ,default = 0,gain enable
// Bit 26:24,  reg_frddr_sel       ,default = 0,from ddr selet
// Bit 23:16,  reg_wait_cnt        ,default = 0,wait some time when enalble set to 1
// Bit 15:13,  reserved
// Bit 12:8,   reg_frddr_msb       ,default = 0,msb position of data
// Bit 7,      reg_force_start     ,default = 0,set 1 no need ack from frddr to transmit channel
// status Bit 6:4,    reg_frddr_type      ,default = 0 Bit 3:0,    reserved
#define EARCTX_SPDIFOUT_PREAMB ((0x0006 << 2) + 0xfe333400)
// Bit 31,     reg_premable_Z_set      ,default = 0,user 8'b11101000 1 user 7:0
// Bit 30,     reg_premable_Y_set      ,default = 0,user 8'b11100100 1 user 15:8
// Bit 29,     reg_premable_X_set      ,default = 0,user 8'b11100010 1 user 23:16
// Bit 28:24,  reserved
// Bit 23:16,  reg_premable_X_value    ,default = 0
// Bit 15:8,   reg_premable_Y_value    ,default = 0
// Bit 7:0,    reg_premable_Z_value    ,default = 0
#define EARCTX_SPDIFOUT_SWAP ((0x0007 << 2) + 0xfe333400)
// Bit 31:16,  reg_hold_cnt        ,default = 0,hold start cnt ,valid when reg_hold_for_tdm set 1
// Bit 15,     reg_init_send_en    ,default = 0,send 01 squence some times after initial done from
// frddr set Bit 14:0,   reg_init_send_cnt   ,default = 0,send 01 squence time ,valid when
// reg_init_send_en set 1
#define EARCTX_ERR_CORRT_CTRL0 ((0x0008 << 2) + 0xfe333400)
// Bit 31:24,  reserved
// Bit 23,     reg_bch_in_reverse       ,default = 0,bch input data generate in 24it data reverse
// Bit 22,     reg_bch_out_ecc_reverse  ,default = 0,bch output ecc  reverse
// Bit 21,     reg_bch_out_data_reverse ,default = 0,bch output data reverse
// Bit 20,     reg_bch_out_ecc_msb      ,default = 0,bch output ecc position
// Bit 19:17,  reserved
// Bit 16,     reg_ubit_fifo_init_n,default = 0,fifo in  initial
// Bit 15:14,  reserved
// Bit 13:12,  reg_gain_shift      ,default = 0,gain x 1/2/4/8
// Bit 11,     reg_mix_lr          ,default = 0,l/r mix
// Bit 10:8,   reg_spdifout_r_sel  ,default = 0,r channel select
// Bit 7,      reserved
// Bit 6:4,    reg_spdifout_l_sel  ,default = 0,l channel select
// Bit 3:0,    reg_iu_interval     ,default = 0,iu transmit interval
#define EARCTX_ERR_CORRT_CTRL1 ((0x0009 << 2) + 0xfe333400)
// Bit 31,     reg_ubit_fifo_wr    ,default = 0,iu data write enable,pluse,auto clr in reg.v
// Bit 30:8,   reserved
// Bit 7:0,    reg_ubit_fifo_wdata ,default = 0,iu data
#define EARCTX_ERR_CORRT_CTRL2 ((0x000a << 2) + 0xfe333400)
// Bit 31,     reg_mute_clear       ,default = 0,mute clear,pluse,auto clr in reg.v
// Bit 30,     reg_mute_start       ,default = 0,mute start,pluse,auto clr in reg.v
// Bit 29:28,  reserved
// Bit 27:16,  reg_mute_block_num   ,default = 0,mute block number
// Bit 15:8,   reg_mute_ch_Bit      ,default = 0,mute Bit at channel statue which bit
// Bit 7:3,    reserved
// Bit 2,      reg_mute_data_sel    ,default = 0,mute data sel: 0 data 1 reg_mute_data_value
// Bit 1:0,    reg_mute_mode        ,default = 0,0:always mute 1:mute block number and dis mute
// 2:mute bolck number and hold bus
#define EARCTX_ERR_CORRT_CTRL3 ((0x000b << 2) + 0xfe333400)
// Bit 31:30,  reserved
// Bit 29,     reg_bch_en           ,default = 0,bch generate enable
// Bit 28:24,  reg_bch_msb          ,default = 0,bch data msb position in audio data
// Bit 23:0,   reg_mute_data_value  ,default = 0,mute value,only for audio data part
#define EARCTX_ERR_CORRT_CTRL4 ((0x000c << 2) + 0xfe333400)
// Bit 31,    reg_ubit_fifo_lr_swap        ,default = 0,//user Bit lr swap
// Bit 30,    reg_ubit_fifo_lr_same        ,default = 0,//l/r channel use same Bit user bit
// Bit 29:25, reg_data_msb                 ,default = 0,audio data msb postion in input data
// Bit 24,    reg_data_rsv                 ,default = 0,audio data msb/lsb
// Bit 23,    reg_ubit_value               ,default = 0,user Bit value
// Bit 22,    reg_vbit_value               ,default = 0,valid Bit value
// Bit 21,    reg_data_sel                 ,default = 0,//data sel: 0 data 1 reg_mute_data_value
// Bit 20:19, reg_ubit_sel                 ,default = 0,//userBit sel: 0 data 1 reg_value 2 fifo
// data Bit 18,    reg_vbit_sel                 ,default = 0,//validBit sel: 0 data 1 reg_value Bit
// 17,    reg_chst_sel                 ,default = 0,//chanel status sel: 0 data 1 reg_value Bit 16,
// reg_ubit_fifo_less_irq_en    ,default = 0,fifo_less_thd irq enable Bit 15:8,
// reg_ubit_fifo_start_thd      ,default = 0,start transmit iu after fifo level greater than this
// value Bit 7:0,   reg_ubit_fifo_less_thd       ,default = 0,generate irq,when fifo level less
// than this value
#define EARCTX_ERR_CORRT_STAT0 ((0x000d << 2) + 0xfe333400)
// Bit 31:0,  ro_err_corrt_stat0          ,default = 0,
#define EARCTX_SPDIFOUT_CHSTS0 ((0x000e << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[31:0]
#define EARCTX_SPDIFOUT_CHSTS1 ((0x000f << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[63:32]
#define EARCTX_SPDIFOUT_CHSTS2 ((0x0010 << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[95:64]
#define EARCTX_SPDIFOUT_CHSTS3 ((0x0011 << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[127:96]
#define EARCTX_SPDIFOUT_CHSTS4 ((0x0012 << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[159:128]
#define EARCTX_SPDIFOUT_CHSTS5 ((0x0013 << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[191:160]
#define EARCTX_SPDIFOUT_CHSTS6 ((0x0014 << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[31:0]
#define EARCTX_SPDIFOUT_CHSTS7 ((0x0015 << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[63:32]
#define EARCTX_SPDIFOUT_CHSTS8 ((0x0016 << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[95:64]
#define EARCTX_SPDIFOUT_CHSTS9 ((0x0017 << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[127:96]
#define EARCTX_SPDIFOUT_CHSTSA ((0x0018 << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[159:128]
#define EARCTX_SPDIFOUT_CHSTSB ((0x0019 << 2) + 0xfe333400)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[191:160]
#define EARCTX_FE_CTRL0 ((0x001a << 2) + 0xfe333400)
// Bit 31,    reg_mute_hold_clr      ,default = 0,clear mute hold statues,pluse, auto clr
// Bit 30,    reg_work_enable        ,default = 0,wore enable
// Bit 29,    reg_dmac_invt          ,default = 0,fe out invent
// Bit 28,    reg_hold_time_en       ,default = 0,hold min time enable
// Bit 27,    reg_hold_soft_clr_en   ,default = 0,0 auto clear hold at next valid 1 clear hold
// with reg_mute_hold_clr Bit 26:24, reg_hold_time_tick_sel ,default = 0,hold min time tick select
// Bit 23:0,  reg_hold_min_time      ,default = 0,hold min time
#define EARCTX_FE_STAT0 ((0x001b << 2) + 0xfe333400)
// Bit 31:0,  ro_fe_stat0          ,default = 0,
#define EARCTX_SPDIFOUT_STAT ((0x001c << 2) + 0xfe333400)
// Bit 31:0,  ro_spdifout_stat     ,default = 0,
#define EARCTX_SPDIFOUT_CTRL2 ((0x001d << 2) + 0xfe333400)
// Bit 31:28,  reserved
// Bit 27:16,  reg_clr_by_init      ,default = 0,reg_clr_by_init
// Bit 15:0 ,  reg_mask             ,default = 0,reg_mask
#define EARCTX_SPDIFOUT_GAIN2 ((0x001e << 2) + 0xfe333400)
// Bit 31:0,  spdifout_gain2        ,default = 0,spdifout gain2
#define EARCTX_SPDIFOUT_GAIN3 ((0x001f << 2) + 0xfe333400)
// Bit 31:0,  spdifout_gain3        ,default = 0,spdifout gain3
#define EARCTX_SPDIFOUT_GAIN4 ((0x0020 << 2) + 0xfe333400)
// Bit 31:0,  spdifout_gain4        ,default = 0,spdifout gain4
#define EARCTX_SPDIFOUT_GAIN5 ((0x0021 << 2) + 0xfe333400)
// Bit 31:0,  spdifout_gain5        ,default = 0,spdifout gain5
//
//
// Closing file:  earctx_dmac.h
//
//========================================================================
//  AUDIO EARCTX_TOP  - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333600
// -----------------------------------------------
//
// Reading file:  earctx_top.h
//
#define EARCTX_TOP_CTRL0 ((0x0000 << 2) + 0xfe333600)
// Bit   31:18,   reserved
// Bit   17:16,   reg_earctx_debug_mux     unsigned, default = 0, debug mux
// Bit   15,      reg_slow_sync_scan_reg   unsigned, default = 0, reg_slow_sync_scan_reg
// Bit   14:12,   reserved
// Bit   11,      reg_hdmi_hpd_invt        unsigned, default = 0, hdmi_hpd invent
// Bit   10,      reg_hdmi_hpd_value       unsigned, default = 0, hdmi_hpd mux = 3,register value
// Bit   9:8,     reg_hdmi_hpd_mux         unsigned, default = 0, hdmi_hpd mux
// Bit   7,       reg_earctx_hd_hpd_invt   unsigned, default = 0, earctx_hd_hdp invent
// Bit   6,       reg_earctx_hd_hpd_value  unsigned, default = 0, earctx_hd_hdp mux = 3,register
// value Bit   5:4,     reg_earctx_hd_hdp_mux    unsigned, default = 0, earctx_hd_hdp mux Bit 3:2,
// reserved Bit   1,       reg_earctx_force_mode_en unsigned, default = 0, force mode enale Bit 0,
// reg_earctx_force_mode    unsigned, default = 0, force mode value
#define EARCTX_DMAC_INT_MASK ((0x0001 << 2) + 0xfe333600)
// Bit   31:6,  reserved
// Bit   5:0,   reg_dmac_int_mask             unsigned, default = 0, dmac int mask
#define EARCTX_DMAC_INT_PENDING ((0x0002 << 2) + 0xfe333600)
// Bit   31:6,  reserved
// Bit   5:0,   reg_dmac_int_mask             unsigned, default = 0, dmac int pending,read only
#define EARCTX_CMDC_INT_MASK ((0x0003 << 2) + 0xfe333600)
// Bit   31:18,  reserved
// Bit   17:0,   reg_cmdc_int_mask             unsigned, default = 0, cmdc int mask
#define EARCTX_CMDC_INT_PENDING ((0x0004 << 2) + 0xfe333600)
// Bit   31:18,  reserved
// Bit   17:0,   reg_cmdc_int_mask             unsigned, default = 0, cmdc int pending,read only
#define EARCTX_ANA_CTRL0 ((0x0005 << 2) + 0xfe333600)
// Bit   31:0,   reg_earctx_ana_ctrl0          unsigned, default = 0
#define EARCTX_ANA_CTRL1 ((0x0006 << 2) + 0xfe333600)
// Bit   31:0,   reg_earctx_ana_ctrl0          unsigned, default = 0
#define EARCTX_ANA_CTRL2 ((0x0007 << 2) + 0xfe333600)
// Bit   31:0,   reg_earctx_ana_ctrl0          unsigned, default = 0
#define EARCTX_ANA_STAT0 ((0x0008 << 2) + 0xfe333600)
// Bit   31:0,   reg_earctx_ana_ctrl0          unsigned, default = 0
//
// Closing file:  earctx_top.h
//
//========================================================================
//  AUDIO EARCRX_CMDC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333800
// -----------------------------------------------
//
// Reading file:  earc_rx_cmdc.h
//
#define EARC_RX_CMDC_TOP_CTRL0 ((0x0000 << 2) + 0xfe333800)
// Bit   31   ,     idle2_int                 unsigned, default = 0, 1: enable
// Bit   30   ,     idle1_int                 unsigned, default = 0, 1: enable
// Bit   29   ,     disc2_int                 unsigned, default = 0, 1: enable
// Bit   28   ,     disc1_int                 unsigned, default = 0, 1: enable
// Bit   27   ,     earc_int                  unsigned, default = 0, 1: enable
// Bit   26   ,     hb_status_int             unsigned, default = 0, 1: enable
// Bit   25   ,     losthb_int                unsigned, default = 0, 1: enable
// Bit   24   ,     timeout_int               unsigned, default = 0, 1: enable
// Bit   23   ,     status_ch_int             unsigned, default = 0, 1: enable
// Bit   22   ,     int_rec_invalid_id        unsigned, default = 0, 1: enable
// Bit   21   ,     int_rec_invalid_offset    unsigned, default = 0, 1: enable
// Bit   20   ,     int_rec_unexp             unsigned, default = 0, 1: enable
// Bit   19   ,     int_rec_ecc_err           unsigned, default = 0, 1: enable
// Bit   18   ,     int_rec_parity_err        unsigned, default = 0, 1: enable
// Bit   17   ,     int_recv_packet           unsigned, default = 0, 1: enable
// Bit   16   ,     int_rec_time_out          unsigned, default = 0, 1: enable
// Bit   15   ,     cmdc_debug0               unsigned, default = 0, 1: enable
// Bit   14   ,     cmdc_debug1               unsigned, default = 0, 1: enable
// Bit   13   ,     cmdc_debug2               unsigned, default = 0, 1: enable
// Bit   12:7 ,     reserved
// Bit    6   ,     mute_select               unsigned, default = 0, 1: use bit5, 0: earc off
// Bit    5   ,     mute_contrl               unsigned, default = 0, value of mannul mute control
// Bit    4:0 ,     reserved
#define EARC_RX_CMDC_TOP_CTRL1 ((0x0001 << 2) + 0xfe333800)
// Bit      31:13,  reserved
// Bit      12:8,   reg_scan_reg             unsigned, RW, default = 0,
// Bit      7:5,    reserved
// Bit      4:0,    reg_top_soft_rst         unsigned, RW, default = 0,
#define EARC_RX_CMDC_TOP_CTRL2 ((0x0002 << 2) + 0xfe333800)
// Bit      31,         reset_idle2_int                unsigned, default =0
// Bit      30,         reset_idle1_int                unsigned, default =0
// Bit      29,         reset_disc2_int                unsigned, default =0
// Bit      28,         reset_disc1_int                unsigned, default =0
// Bit      27,         reset_earc_int                 unsigned, default =0
// Bit      26,         reset_hb_status_int            unsigned, default =0
// Bit      25,         reset_losthb_int               unsigned, default =0
// Bit      24,         reset_timeout_int              unsigned, default =0
// Bit      23,         reset_status_ch_int            unsigned, default =0
// Bit      22,         reset_int_rec_invalid_id       unsigned, default =0
// Bit      21,         reset_int_rec_invalid_offset   unsigned, default =0
// Bit      20,         reset_int_rec_unexp            unsigned, default =0
// Bit      19,         reset_int_rec_ecc_err          unsigned, default =0
// Bit      18,         reset_int_rec_parity_err       unsigned, default =0
// Bit      17,         reset_int_recv_packet          unsigned, default =0
// Bit      16,         reset_int_rec_time_out         unsigned, default =0
// Bit      15:0,       reserved
#define EARC_RX_CMDC_TIMER_CTRL0 ((0x0003 << 2) + 0xfe333800)
// Bit      31:0,   ro_cmdc_status0         unsigned, RO, default = 0,
#define EARC_RX_CMDC_TIMER_CTRL1 ((0x0004 << 2) + 0xfe333800)
// Bit      31:0,   ro_cmdc_status0         unsigned, RO, default = 0,
#define EARC_RX_CMDC_TIMER_CTRL2 ((0x0005 << 2) + 0xfe333800)
// Bit      31:0,    ro_cmdc_status0         unsigned, RO, default = 0,
#define EARC_RX_CMDC_TIMER_CTRL3 ((0x0006 << 2) + 0xfe333800)
// Bit      31:0,    ro_cmdc_status0         unsigned, RO, default = 0,
#define EARC_RX_CMDC_VSM_CTRL0 ((0x0007 << 2) + 0xfe333800)
// Bit      31,      sw_state_update         unsigned, default = 0,  XX
// Bit      30:28,   sw_state                unsigned, default = 0,  XX
// Bit      27,      arc_initiated           unsigned, default = 0,  XX
// Bit      26,      arc_terminated          unsigned, default = 0,  XX
// Bit      25,      arc_enable              unsigned, default = 0,  XX
// Bit      24,      man_hpd                 unsigned, default = 0,  XX
// Bit      23:22,   hpd_sel                 unsigned, default = 0,  XX
// Bit      21:20,   hpd_sel_earc            unsigned, default = 0,  XX
// Bit      19,      comma_cnt_rst           unsigned, default = 0,  XX
// Bit      18,      timeout_status_rst      unsigned, default = 0,  XX
// Bit      17,      losthb_status_rst       unsigned, default = 0,  XX
// Bit      16,      force_rst               unsigned, default = 0,  XX
// Bit      15,      auto_state              unsigned, default = 0,  XX
// Bit      14,      cmdc_state_en           unsigned, default = 0,  XX
// Bit    13:0,      reserved
#define EARC_RX_CMDC_VSM_CTRL1 ((0x0008 << 2) + 0xfe333800)
// Bit    31:12,      max_count_th          unsigned, default = 0,  idle done timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  idle done timing
// Bit      6:4,      time_sel              unsigned, default = 0,  idle done timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  idle done timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  idle done timing
#define EARC_RX_CMDC_VSM_CTRL2 ((0x0009 << 2) + 0xfe333800)
// Bit    31:12,      max_count_th          unsigned, default = 0,  comma off done timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  comma off done timing
// Bit      6:4,      time_sel              unsigned, default = 0,  comma off done timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  comma off done timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  comma off done timing
#define EARC_RX_CMDC_VSM_CTRL3 ((0x000a << 2) + 0xfe333800)
// Bit    31:12,      max_count_th          unsigned, default = 0,  earc_time out timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  earc_time out timing
// Bit      6:4,      time_sel              unsigned, default = 0,  earc_time out timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  earc_time out timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  earc_time out timing
#define EARC_RX_CMDC_VSM_CTRL4 ((0x000b << 2) + 0xfe333800)
// Bit    31:12,      max_count_th          unsigned, default = 0,  heartbeat lost timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  heartbeat lost timing
// Bit      6:4,      time_sel              unsigned, default = 0,  heartbeat lost timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  heartbeat lost timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  heartbeat lost timing
#define EARC_RX_CMDC_VSM_CTRL5 ((0x000c << 2) + 0xfe333800)
// Bit    31:16,      reserved
// Bit     15:8,      status_soft           unsigned, default = 0,  in earc heartbeat det timing
// Bit        7,      reg_soft_rst          unsigned, default = 0,  in earc heartbeat det timing
// Bit        6,      status_rst            unsigned, default = 0,  in earc heartbeat det timing
// Bit      5:4,      reserved
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  in earc heartbeat det timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  in earc heartbeat det timing
#define EARC_RX_CMDC_VSM_CTRL6 ((0x000d << 2) + 0xfe333800)
// Bit    31:17,      reserved
// Bit        16,     cntl_hpd_sel          unsigned, default = 0,  in earc heartbeat det timing
// Bit      15:4,     cntl_hpd_valid_width  unsigned, default = 0,  in earc heartbeat det timing
// Bit      3:0,      cntl_hpd_glitch_width unsigned, default = 0,  in earc heartbeat det timing
#define EARC_RX_CMDC_VSM_CTRL7 ((0x000e << 2) + 0xfe333800)
// Bit      31:0,     vsm_ctrl7             unsigned,  default = 0,
#define EARC_RX_CMDC_VSM_CTRL8 ((0x000f << 2) + 0xfe333800)
// Bit      31:0,     vsm_ctrl8             unsigned,  default = 0,
#define EARC_RX_CMDC_VSM_CTRL9 ((0x0010 << 2) + 0xfe333800)
// Bit      31:0,     vsm_ctrl9             unsigned,  default = 0,
#define EARC_RX_CMDC_SENDER_CTRL0 ((0x0011 << 2) + 0xfe333800)
// Bit      31:2,     reserved
// Bit      1,        hb_chg_conf_auto          unsigned,  default = 0,
// Bit      0,        hb_chg_auto               unsigned,  default = 1,
#define EARC_RX_CMDC_PACKET_CTRL0 ((0x0012 << 2) + 0xfe333800)
// Bit        31,      packet_mode_enable          unsigned, default = 0,  packet control
// Bit        30,      free_enable                 unsigned, default = 0,  packet control
// Bit        29,      soft_rst_man                unsigned, default = 0,  packet control
// Bit     28:24,      ready_th                    unsigned, default = 0,  packet control
// Bit     23:20,      reserved
// Bit      19:8,      send_pre_th                 unsigned, default = 0,  packet control
// Bit       7:5,      reserved
// Bit         4,      sw_state_update             unsigned, default = 0,  packet control
// Bit       3:0,      sw_state                    unsigned, default = 0,  packet control
#define EARC_RX_CMDC_PACKET_CTRL1 ((0x0013 << 2) + 0xfe333800)
// Bit        31,      ecc_endian                  unsigned, default = 0,  send
// Bit        30,      pre_reg_st                  unsigned, default = 0,  send
// Bit     29:21,      reserved
// Bit     20:16,      post_th                     unsigned, default = 0,  send
// Bit     15:14,      reserved
// Bit      13:8,      pre_th                      unsigned, default = 0,
// Bit       7:0,      post_flag                   unsigned, default = 0,
#define EARC_RX_CMDC_PACKET_CTRL2 ((0x0014 << 2) + 0xfe333800)
// Bit      31:0,      pre_flag                    unsigned, default = 0,  X
#define EARC_RX_CMDC_PACKET_CTRL3 ((0x0015 << 2) + 0xfe333800)
// Bit      31,       cmdc_en                      unsigned, default = 0,  XX
// Bit      30,       cmdc_parity_mask             unsigned, default = 0,  XX
// Bit      29,       imeout_en                    unsigned, default = 0,  XX
// Bit      28,       ecc_check_en                 unsigned, default = 0,  XX
// Bit      27,       rev_debug_en                 unsigned, default = 0,  XX
// Bit     26:16,     reserved
// Bit      15:0,     timeout_th                   unsigned, default = 0,  X
#define EARC_RX_CMDC_PACKET_CTRL4 ((0x0016 << 2) + 0xfe333800)
// Bit      31,       ack_ignore                   unsigned, default = 0,  XX
// Bit      30,       cmdc_tail_check_mask         unsigned, default = 0,  XX
// Bit     29:20,     reserved
// Bit      19:0,     cmdc_packet_head             unsigned, default = 0,  XX
#define EARC_RX_CMDC_PACKET_CTRL5 ((0x0017 << 2) + 0xfe333800)
// Bit     31:24,     rev_debug_mask               unsigned, default = 0,  XX
// Bit     23:20,     reserved
// Bit      19:0,     cmdc_packet_head_mask        unsigned, default = 0,  XX
#define EARC_RX_CMDC_PACKET_CTRL6 ((0x0018 << 2) + 0xfe333800)
// Bit     31:20,     recv_pre_threshold          unsigned, default = 0,  packet control
// Bit      19:9,     reserved
// Bit         8,     rec_packet_d                 unsigned, default = 0,  XX
// Bit         7,     rec_parity_err_cnt		      unsigned, default = 0,  XX
// Bit         6,     rec_ecc_err_cnt		      unsigned, default = 0,  XX
// Bit         5,     rec_unexp_cnt			      unsigned, default = 0,  XX
// Bit         4,     rec_invalid_offset_cnt	      unsigned, default = 0,  XX
// Bit         3,     rec_invalid_id_cnt		      unsigned, default = 0,  XX
// Bit         2,     rec_timeout_cnt		      unsigned, default = 0,  XX
// Bit         1,     rec_w_cnt				      unsigned, default = 0,  XX
// Bit         0,     rec_r_cnt				      unsigned, default = 0,  X
#define EARC_RX_CMDC_BIPHASE_CTRL0 ((0x0019 << 2) + 0xfe333800)
// Bit     31:24,     reg_tns                       unsigned, default = 7, xx
// Bit     23:16,     delay_th                      unsigned, default = 0, xx
// Bit     15:10,     reserved
// Bit         9,     send_ack_en                   unsigned, default = 0,  xx
// Bit         8,     sq_val_en                     unsigned, default = 0,  XX
// Bit         7,     biphase_send_soft_rst         unsigned, default = 0,  XX
// Bit         6,     comma_soft_rst                unsigned, default = 0,  XX
// Bit         5,     fifo_rst                      unsigned, default = 0,  XX
// Bit         4,     receiver_no_sender            unsigned, default = 0,  XX
// Bit         3,     sender_free                   unsigned, default = 0,  XX
// Bit         2,     receiver_send                 unsigned, default = 0,  XX
// Bit         1,     receiver_earc                 unsigned, default = 0,  XX
// Bit         0,     receiver_free                 unsigned, default = 0,  XX
#define EARC_RX_CMDC_BIPHASE_CTRL1 ((0x001a << 2) + 0xfe333800)
// Bit     31:16,     reserved
// Bit        15,     ack_val_en                      unsigned, default = 0,  send
// Bit      14:8,     reserved
// Bit       7:0,     width                        unsigned, default = 0,  send
#define EARC_RX_CMDC_BIPHASE_CTRL2 ((0x001b << 2) + 0xfe333800)
// Bit      31,        ack_val_en                  unsigned, default = 0,  send
// Bit      30:20,     reserved
// Bit       19:16,    ack_rate                   unsigned, default = 0,  comma send
// Bit       15:0,     width                         unsigned, default = 0,  comma sen
#define EARC_RX_CMDC_BIPHASE_CTRL3 ((0x001c << 2) + 0xfe333800)
// Bit      31:0,     biphase_ctrl3                 unsigned, default = 0,
#define EARC_RX_CMDC_DEVICE_ID_CTRL ((0x001d << 2) + 0xfe333800)
// Bit        31,     apb_write                     unsigned, default = 0, apb bus wr/read
// Bit        30,     apb_read                      unsigned, default = 0, apb bus wr/read
// Bit        29,     apb_w_r_done                  unsigned, default = 0, apb bus wr/read
// Bit        28,     apb_w_r_reset                 unsigned, default = 0, apb bus wr/read
// Bit     27:16,     reserved
// Bit      15:8,     apb_w_r_id                    unsigned, default = 0, apb bus wr/read
// Bit       7:0,     apb_w_r_start_addr            unsigned, default = 0, apb bus wr/read
#define EARC_RX_CMDC_DEVICE_WDATA ((0x001e << 2) + 0xfe333800)
// Bit      31:8,     reserved
// Bit       7:0,     apb_write_data                unsigned, default = 0, apb bus wr/rea
#define EARC_RX_CMDC_DEVICE_RDATA ((0x001f << 2) + 0xfe333800)
// Bit      31:8,     reserved
// Bit       7:0,     apb_read_data                 unsigned, default = 0, apb bus wr/rea
#define EARC_RX_ANA_CTRL0 ((0x0020 << 2) + 0xfe333800)
// Bit      31:0,     ana_ctrl0                     unsigned, default = 0,
#define EARC_RX_ANA_CTRL1 ((0x0021 << 2) + 0xfe333800)
// Bit      31:0,     ana_ctrl1                     unsigned, default = 0,
#define EARC_RX_ANA_CTRL2 ((0x0022 << 2) + 0xfe333800)
// Bit      31:0,     ana_ctrl2                     unsigned, default = 0,
#define EARC_RX_ANA_CTRL3 ((0x0023 << 2) + 0xfe333800)
// Bit      31:0,     ana_ctrl3                     unsigned, default = 0,
#define EARC_RX_ANA_CTRL4 ((0x0024 << 2) + 0xfe333800)
// Bit      31:0,     ana_ctrl4                     unsigned, default = 0,
#define EARC_RX_ANA_CTRL5 ((0x0025 << 2) + 0xfe333800)
// Bit      31:0,     ana_ctrl5                     unsigned, default = 0,
#define EARC_RX_ANA_STAT0 ((0x0026 << 2) + 0xfe333800)
// Bit      31:0,     ro_ANA_status0              unsigned, RO, default = 0,
#define EARC_RX_CMDC_STATUS0 ((0x0027 << 2) + 0xfe333800)
// Bit      31:0,     ro_cmdc_status0              unsigned, RO, default = 0,
#define EARC_RX_CMDC_STATUS1 ((0x0028 << 2) + 0xfe333800)
// Bit      31:0,     ro_cmdc_status1              unsigned, RO, default = 0,
#define EARC_RX_CMDC_STATUS2 ((0x0029 << 2) + 0xfe333800)
// Bit      31:0,     ro_cmdc_status2              unsigned, RO, default = 0,
#define EARC_RX_CMDC_STATUS3 ((0x002a << 2) + 0xfe333800)
// Bit      31:0,     ro_cmdc_status3              unsigned, RO, default = 0,
#define EARC_RX_CMDC_STATUS4 ((0x002b << 2) + 0xfe333800)
// Bit      31:0,     ro_cmdc_status4              unsigned, RO, default = 0,
#define EARC_RX_CMDC_STATUS5 ((0x002c << 2) + 0xfe333800)
// Bit      31:0,     ro_cmdc_status5              unsigned, RO, default = 0,
#define EARC_RX_CMDC_STATUS6 ((0x002d << 2) + 0xfe333800)
// Bit      31,         ro_idle2_int                unsigned, RO, dfault =0
// Bit      30,         ro_idle1_int                unsigned, RO, dfault =0
// Bit      29,         ro_disc2_int                unsigned, RO, dfault =0
// Bit      28,         ro_disc1_int                unsigned, RO, dfault =0
// Bit      27,         ro_earc_int                 unsigned, RO, dfault =0
// Bit      26,         ro_hb_status_int            unsigned, RO, dfault =0
// Bit      25,         ro_losthb_int               unsigned, RO, dfault =0
// Bit      24,         ro_timeout_int              unsigned, RO, dfault =0
// Bit      23,         ro_status_ch_int            unsigned, RO, dfault =0
// Bit      22,         ro_int_rec_invalid_id       unsigned, RO, dfault =0
// Bit      21,         ro_int_rec_invalid_offset   unsigned, RO, dfault =0
// Bit      20,         ro_int_rec_unexp            unsigned, RO, dfault =0
// Bit      19,         ro_int_rec_ecc_err          unsigned, RO, dfault =0
// Bit      18,         ro_int_rec_parity_err       unsigned, RO, dfault =0
// Bit      17,         ro_int_recv_packet          unsigned, RO, dfault =0
// Bit      16,         ro_int_rec_time_out         unsigned, RO, dfault =0
// Bit      15:0,       reserved
//
// Closing file:  earc_rx_cmdc.h
//
//========================================================================
//  AUDIO EARCRX_DMAC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333c00
// -----------------------------------------------
//
// Reading file:  earcrx_dmac.h
//
#define EARCRX_DMAC_TOP_CTRL0 ((0x0000 << 2) + 0xfe333c00)
// Bit   31,     reg_top_work_en               unsigned, default = 0, top work enable
// Bit   30,     reg_top_soft_rst              unsigned, default = 0, top soft reset
// Bit   29:23,  reserved
// Bit   22:20,  reg_dmac_debug_sel            unsigned, default = 0, dmac debug select
// Bit   19:18,  reserved
// Bit   17,     reg_dmac_valid_sel            unsigned, default = 0, dmac sync without clk
// Bit   16,     reg_dmac_without_clk          unsigned, default = 0, dmac sync without clk
// Bit   15,     reg_sf_sync_scan_reg          unsigned, default = 0, rst_n soft reset scan reg
// Bit   14,     reserved
// Bit   13,     reg_slow_sync_scan_reg        unsigned, default = 0, rst_n sync clk_slow scan reg
// Bit   12,     reg_a_sync_scan_reg           unsigned, default = 0, rst_n sync clk_analog scan
// reg Bit   11,     reg_slow_auto_gate            unsigned, default = 0, clk_slow auto gate Bit
// 10,     reg_a_auto_gate               unsigned, default = 0, clk_analog auto gate Bit   9:0,
// reserved
#define EARCRX_DMAC_SYNC_CTRL0 ((0x0001 << 2) + 0xfe333c00)
// Bit   31,     reg_work_enable               unsigned, default = 0, dmac sync module work enable
// Bit   30,     reg_rst_afifo_out_n           unsigned, default = 0, afifo out reset
// Bit   29,     reg_rst_afifo_in_n            unsigned, default = 0, afifo in reset
// Bit   28:17,  reserved
// Bit   16,     reg_ana_buf_data_sel_en       unsigned, default = 0, data from analog delay
// enable Bit   15,     reserved Bit   14:12,  reg_ana_buf_data_sel          unsigned, default = 0,
// delay cycles Bit   11,     reserved Bit   10:8,   reg_ana_clr_cnt               unsigned,
// default = 0, valid last how many 0 will clear Bit   7,      reserved Bit   6:4, reg_ana_set_cnt
// unsigned, default = 0, valid last how may 1 will set Bit   3:1,    reserved Bit   0,
// reg_dmacin_phase              unsigned, default = 0, dmac data invert
#define EARCRX_DMAC_SYNC_STAT0 ((0x0002 << 2) + 0xfe333c00)
// Bit   31:0,   reg_dmac_sync_stat0           unsigned, default = 0
#define EARCRX_SPDIFIN_SAMPLE_CTRL0 ((0x0003 << 2) + 0xfe333c00)
// Bit   31,     reg_work_enable               unsigned, default = 0, spdif in sample enable
// Bit   30,     reg_spdifin_phase             unsigned, default = 0, spdif in invert
// Bit   29,     reg_debug_en                  unsigned, default = 0, debug single enable
// Bit   28,     reg_width_sel                 unsigned, default = 0, 0 detect by max_width 1
// detect by min_width Bit   27:23,  reserved Bit   22:20,  reg_sample_mode               unsigned,
// default = 0, value Bit   19:0,   reg_base_timer                unsigned, default = 0, base timer
// to detect sample mode change
#define EARCRX_SPDIFIN_SAMPLE_CTRL1 ((0x0004 << 2) + 0xfe333c00)
// Bit   31,     reg_force_sample_mode         unsigned, default = 0, 0 auto detect sample mode 1
// force a fixed sample mode with reg_sample_mode Bit   30,     reserved Bit   29:20,
// reg_sample_mode0_timer_th     unsigned, default = 0, mode0 threathold time Bit   19:10,
// reg_sample_mode1_timer_th     unsigned, default = 0, mode1 threathold time Bit   9:0,
// reg_sample_mode2_timer_th     unsigned, default = 0, mode2 threathold time
#define EARCRX_SPDIFIN_SAMPLE_CTRL2 ((0x0005 << 2) + 0xfe333c00)
// Bit   31:30,  reserved
// Bit   29:20,  reg_sample_mode3_timer_th     unsigned, default = 0, mode3 threathold time
// Bit   19:10,  reg_sample_mode4_timer_th     unsigned, default = 0, mode4 threathold time
// Bit   9:0,    reg_sample_mode5_timer_th     unsigned, default = 0, mode5 threathold time
#define EARCRX_SPDIFIN_SAMPLE_CTRL3 ((0x0006 << 2) + 0xfe333c00)
// Bit   31:24,  reg_sample_mode0_timer        unsigned, default = 0, mode0 sample time
// Bit   23:16,  reg_sample_mode1_timer        unsigned, default = 0, mode1 sample time
// Bit   15:8,   reg_sample_mode2_timer        unsigned, default = 0, mode2 sample time
// Bit   7:0,    reg_sample_mode3_timer        unsigned, default = 0, mode3 sample time
#define EARCRX_SPDIFIN_SAMPLE_CTRL4 ((0x0007 << 2) + 0xfe333c00)
// Bit   31:24,  reg_sample_mode4_timer        unsigned, default = 0, mode4 sample time
// Bit   23:16,  reg_sample_mode5_timer        unsigned, default = 0, mode5 sample time
// Bit   15:8,   reg_sample_mode6_timer        unsigned, default = 0, mode6 sample time
// Bit   7:0,    reserved
#define EARCRX_SPDIFIN_SAMPLE_CTRL5 ((0x0008 << 2) + 0xfe333c00)
// Bit   31,     reg_sq_filt_en                unsigned, default = 0, dmac_sqout filter enable
// Bit   30,     reg_spdif_sqout_phase         unsigned, default = 0, dmac_sqout invert
// Bit   29:27,  reg_filter_tick_sel           unsigned, default = 0, dmac_sqout filter tick
// select Bit   26:24,  reg_filter_sel                unsigned, default = 0, dmac_sqout filter
// select Bit   23:20,  reserved Bit   19:0,   reg_sq_filt_timer             unsigned, default = 0,
// dmac_sqout filter tick
#define EARCRX_SPDIFIN_SAMPLE_STAT0 ((0x0009 << 2) + 0xfe333c00)
// Bit   31:0,   reg_spdifin_sample_stat0      unsigned, default = 0
#define EARCRX_SPDIFIN_SAMPLE_STAT1 ((0x000a << 2) + 0xfe333c00)
// Bit   31:0,   reg_spdifin_sample_stat1      unsigned, default = 0
#define EARCRX_SPDIFIN_MUTE_VAL ((0x000b << 2) + 0xfe333c00)
// Bit   31:0,   reg_spdifin_mute_val          unsigned, default = 0, spdif in mute value
#define EARCRX_SPDIFIN_CTRL0 ((0x000c << 2) + 0xfe333c00)
// Bit   31,     reg_work_enable               unsigned, default = 0, spdifin wore enable
// Bit   30,     reg_chnum_sel                 unsigned, default = 0, 0 ch_num = 0~383  1 ch_num =
// 0~1 Bit   29:28,  reserved Bit   27,     reg_debug_en                  unsigned, default = 0,
// debug enable Bit   26,     reg_chnum_en                  unsigned, default = 0, star add ch_cnt
// to ch_num Bit   25,     reg_findpapb_en               unsigned, default = 0, papb check enalbe
// Bit   24,     reg_nonpcm2pcm_en             unsigned, default = 0, nonpcm2pcm_th enable
// Bit   23:12,  reg_nonpcm2pcm_th             unsigned, default = 0, if long time didn't detect
// PaPb again,will generate irq Bit   11:8,   reg_ch_status_sel             unsigned, default = 0,
// for stat1/stat2 Bit   7,      reg_mute_l                    unsigned, default = 0, mute channel
// l Bit   6,      reg_mute_r                    unsigned, default = 0, mute channel r Bit   5:4,
// reserved Bit   3,      reg_check_valid               unsigned, default = 0, valid check enable
// Bit   2,      reg_check_parity              unsigned, default = 0, parity check enable
// Bit   1,      reg_invert_data               unsigned, default = 0, spdif data invert
// Bit   0,      reserved
#define EARCRX_SPDIFIN_CTRL1 ((0x000d << 2) + 0xfe333c00)
// Bit   31:24,  reserved
// Bit   31:24,  reg_clr_internal_sts          unsigned, default = 0, internal irq status clear
// Bit   23:12,  reg_mute_block_check_thd      unsigned, default = 0, mute block check time thd
// Bit   11:9,   reg_mute_block_check_tick_sel unsigned, default = 0, mute block check tick sel
// Bit   8,      reg_papb_ext_sync             unsigned, default = 0, ext 0 sync check for papb
// Bit   7:0,    reg_papb_ext_mask             unsigned, default = 0, sync 0 mask
#define EARCRX_SPDIFIN_CTRL2 ((0x000e << 2) + 0xfe333c00)
// Bit   31:24,  reg_mute_bit                   unsigned, default = 0, mute bit in channel st
// Bit   23:19,  reg_mute_block_num             unsigned, default = 0, mute min block number to
// declare Bit   18,     reg_mute_lr_ch_sel             unsigned, default = 0, mute bit in channel
// st L or R Bit   17,     reg_mute_block_check_en        unsigned, default = 0, mute block number
// check enable Bit   16,     reg_earc_cps_chst_clr_en       unsigned, default = 0, auto clear
// compress mode when channel status not compress Bit   15,     reg_earc_cps_nonpcm2pcm_clr_en
// unsigned, default = 0, auto clear compress mode when nonpcm2pcm Bit   14,     reg_earc_auto
// unsigned, default = 0, auto change earc/arc Bit   13,     reg_earcin_papb_lr unsigned, default =
// 0, user l or r channel status to check papb Bit   12,     reg_earcin_check_papb unsigned,
// default = 0, 0:data valid after 1 block;1: in 1st block if exit papb ,data valid after papb Bit
// 11,     reg_earcin_start_papb          unsigned, default = 0, start write toddr 1:from papb
// check,0 from preamble Z,valid when reg_earcin_check_papb set Bit   10, reg_formatchange_auto_rst
// unsigned, default = 0, auto reset will detect format change Bit   9, reg_earcin_cpsb_pcpd_sel
// unsigned, default = 0, compress B pcpd select : 1:next 4th subframe data 0:next sub frame data
// Bit   8:4,    reg_earc_papb_msb             unsigned, default = 0, papb msb position in data
// Bit   3,      reg_earcin_spdif_force        unsigned, default = 0, when in arc mode,spdif on
// force enable Bit   2,      reg_earcin_spdif_force_set    unsigned, default = 0, force value Bit
// 1,      reg_earcin_mode_force         unsigned, default = 0, earc mode force enable Bit   0,
// reg_earcin_mode_force_set     unsigned, default = 0, force value
#define EARCRX_SPDIFIN_CTRL3 ((0x000f << 2) + 0xfe333c00)
// Bit   31:16,  reg_earc_pa_value             unsigned, default = 0, earc mode pa value
// Bit   15:0,   reg_earc_pb_value             unsigned, default = 0, earc mode pb value
#define EARCRX_SPDIFIN_STAT0 ((0x0010 << 2) + 0xfe333c00)
// Bit   31:0,   reg_spdifin_stat0             unsigned, default = 0
#define EARCRX_SPDIFIN_STAT1 ((0x0011 << 2) + 0xfe333c00)
// Bit   31:0,   reg_spdifin_stat1             unsigned, default = 0
#define EARCRX_SPDIFIN_STAT2 ((0x0012 << 2) + 0xfe333c00)
// Bit   31:0,   reg_spdifin_stat2             unsigned, default = 0
#define EARCRX_DMAC_UBIT_CTRL0 ((0x0013 << 2) + 0xfe333c00)
// Bit   31,     reg_work_enable               unsigned, default = 0, dmac user bit decode enable
// Bit   30:24,  reg_iu_sync                   unsigned, default = 0, iu sync value
// Bit   23:16,  reg_fifo_thd                  unsigned, default = 0, generate irq when fifo level
// pass some threthold Bit   15,     reg_max_dist_en               unsigned, default = 0, max
// distance bewteen IUs to set lost Bit   14,     reg_iu_sync_en                unsigned, default =
// 0, iu sync code enable 0 : all iu to fifo 1 only sync iu packet to fifo Bit   13:12, reg_user_lr
// unsigned, default = 0, 00 off 01 use l channel userbit 10 use r channel userbit 11 user lr
// channel userbit Bit   11:8,   reg_max_dist                  unsigned, default = 0, max distance
// bewteen IUs value Bit   7,      reg_fifo_thd_en               unsigned, default = 0, fifo_thd
// irq enable Bit   6,      reg_fifo_lost_init_en         unsigned, default = 0, when lost,initial
// fifo Bit   5,      reg_fifo_init                 unsigned, default = 0, fifo initial Bit   4:0,
// reg_data_bit                  unsigned, default = 0, user bit position in data
#define EARCRX_IU_RDATA ((0x0014 << 2) + 0xfe333c00)
// Bit   31:8,   reserved
// Bit   7:0,    i_iu_rdata                    unsigned, default = 0, iu data,read only
#define EARCRX_DMAC_UBIT_STAT0 ((0x0015 << 2) + 0xfe333c00)
// Bit   31:0,   reg_dmac_ubit_stat0           unsigned, default = 0
#define EARCRX_ERR_CORRECT_CTRL0 ((0x0016 << 2) + 0xfe333c00)
// Bit   31,     reg_work_enable               unsigned, default = 0, err correct work enable
// Bit   30,     reserved
// Bit   29,     reg_rst_afifo_out_n           unsigned, default = 0, reset afifo out side
// Bit   28,     reg_rst_afifo_in_n            unsigned, default = 0, reset afifo in side
// Bit   27,     reg_lr_check                  unsigned, default = 0, enable lr_check
// Bit   26:7,   reserved
// Bit   6,      reg_bchout_data_ml            unsigned, default = 0, bch output 16bit data msb is
// 27 or 19 Bit   5,      reg_bchout_data_rsv           unsigned, default = 0, bch output data
// revers Bit   4,      reg_bchin_ecc_ml              unsigned, default = 0, bch input ecc msb/lsb
// Bit   3,      reg_bchin_ecc_rsv             unsigned, default = 0, bch input ecc revers
// Bit   2,      reg_bchin_data_rsv            unsigned, default = 0, bch input data revers
// Bit   1,      reg_force_set                 unsigned, default = 0, 0 off 1 compress audio mode
// Bit   0,      reg_force_en                  unsigned, default = 0, force work mode enable
#define EARCRX_ERR_CORRECT_STAT0 ((0x0017 << 2) + 0xfe333c00)
// Bit   31:0,   reg_err_correct_stat0         unsigned, default = 0
#define EARCRX_ANA_RST_CTRL0 ((0x0018 << 2) + 0xfe333c00)
// Bit   31,     reg_work_enable               unsigned, default = 0, analog reset check work
// enable Bit   30,     reg_ana_rst_sf_en             unsigned, default = 0, analog reset from
// register enable Bit   29,     reg_ana_rst_sf                unsigned, default = 0, soft reset
// value Bit   28,     reserved Bit   27:23,  reg_new_format_pos_num        unsigned, default = 0,
// when new format data in, hold reset after N posedge Bit   22:20,  reg_dmacrx_div2_thd_tick_sel
// unsigned, default = 0, earcrx_div2 hold thresthold tick select Bit   19:0,   reg_earcrx_div2_thd
// unsigned, default = 0, earcrx_div2 hold thresthold
#define EARCRX_ANA_RST_CTRL1 ((0x0019 << 2) + 0xfe333c00)
// Bit   31,     reg_dmacrx_data_filt_en       unsigned, default = 0, filter enable
// Bit   30:28,  reg_dmacrx_data_filter_sel    unsigned, default = 0, filter select
// Bit   27:25,  reg_dmacrx_data_tick_sel      unsigned, default = 0, filter tick sel
// Bit   24:16,  reg_dmacrx_data_time          unsigned, default = 0, filter tick time
// Bit   15,     reg_dmacrx_sqout_filt_en      unsigned, default = 0, filter enable
// Bit   14:12,  reg_dmacrx_sqout_filter_sel   unsigned, default = 0, filter select
// Bit   11:9,   reg_dmacrx_sqout_tick_sel     unsigned, default = 0, filter tick sel
// Bit   8:0,    reg_dmacrx_sqout_time         unsigned, default = 0, filter tick time
#define EARCRX_SPDIFIN_CTRL4 ((0x0020 << 2) + 0xfe333c00)
// Bit   31,     reserved
// Bit   30,     reg_add_ch_r                        unsigned, default = 0, reg_add_ch_r
// Bit   29,     reg_bc_val0_en                      unsigned, default = 0, reg_bc_val0_en
// Bit   28:20,  reg_stable_mask                     unsigned, default = 0, reg_stable_mask
// Bit   19:16,  reg_stable_zcnt                     unsigned, default = 0, reg_stable_zcnt
// Bit   15:0 ,  reserved
#define EARCRX_SPDIFIN_CTRL5 ((0x0021 << 2) + 0xfe333c00)
// Bit   31,     reg_st_timeout_sts_clr              unsigned, default = 0, reg_st_timeout_sts_clr
// Bit   30:28,  reserved
// Bit   27:16,  reg_st_timeout_check_thd            unsigned, default = 0,
// reg_st_timeout_check_thd Bit   15,     reserved Bit   14:12,  reg_st_timeout_check_tick_sel
// unsigned, default = 0, reg_st_timeout_check_tick_sel Bit   11,     reg_st_timeout_check_en
// unsigned, default = 0, reg_st_timeout_check_en Bit   10:9,   reserved Bit   8:0,
// reg_stable_int_mask                 unsigned, default = 0, reg_stable_int_mask
#define EARCRX_SPDIFIN_CTRL6 ((0x0022 << 2) + 0xfe333c00)
// Bit   31:17,  reserved
// Bit   16,     reg_check_time_en                   unsigned, default = 0, reg_check_time_en
// Bit   15:0,   reg_check_time_thd                  unsigned, default = 0, reg_check_time_thd
#define EARCRX_DMAC_SYNC_CTRL1 ((0x0023 << 2) + 0xfe333c00)
// Bit   31:19,  reserved
// Bit   18,     reg_auto_neg_int_en                 unsigned, default = 0, reg_auto_neg_int_en
// Bit   17,     reg_auto_stable_clr                 unsigned, default = 0, reg_auto_stable_clr
// Bit   16,     reg_auto_stable_en                  unsigned, default = 0, reg_auto_stable_en
// Bit   15:0,   reg_auto_stable_thd                 unsigned, default = 0, reg_auto_stable_thd
#define EARCRX_SPDIFIN_SAMPLE_CTRL6 ((0x0024 << 2) + 0xfe333c00)
// Bit   31:18,  reserved
// Bit   17,     reg_hold_tri_sample                 unsigned, default = 0, reg_hold_tri_sample
// Bit   16,     reg_sample_mode_filter_en           unsigned, default = 0,
// reg_sample_mode_filter_en Bit   15:8,   reg_stable_cyc_min                  unsigned, default =
// 0, reg_stable_cyc_min Bit   7:0,    reg_stable_cyc_max                  unsigned, default = 0,
// reg_stable_cyc_max
#define EARCRX_DMAC_SYNC_CTRL2 ((0x0025 << 2) + 0xfe333c00)
// Bit   31,     reg_unstable_t0_err_clr             unsigned, default = 0,
// reg_unstable_t0_err_clr Bit   30:20,  reserved Bit   19,     reg_unstable_t0_check_en unsigned,
// default = 0, reg_unstable_t0_check_en Bit   18:16,  reg_unstable_t0_tick_sel unsigned, default =
// 0, reg_unstable_t0_tick_sel Bit   15:0,   reg_unstable_t0_thd                 unsigned, default
// = 0, reg_unstable_t0_thd
#define EARCRX_DMAC_SYNC_CTRL3 ((0x0026 << 2) + 0xfe333c00)
// Bit   31,     reg_unstable_t1_err_clr             unsigned, default = 0,
// reg_unstable_t1_err_clr Bit   30:20,  reserved Bit   19,     reg_unstable_t1_check_en unsigned,
// default = 0, reg_unstable_t1_check_en Bit   18:16,  reg_unstable_t1_tick_sel unsigned, default =
// 0, reg_unstable_t1_tick_sel Bit   15:0,   reg_unstable_t1_thd                 unsigned, default
// = 0, reg_unstable_t1_thd
#define EARCRX_DMAC_SYNC_CTRL4 ((0x0027 << 2) + 0xfe333c00)
// Bit   31,     reg_unstable_t2_err_clr             unsigned, default = 0,
// reg_unstable_t2_err_clr Bit   30:20,  reserved Bit   19,     reg_unstable_t2_check_en unsigned,
// default = 0, reg_unstable_t2_check_en Bit   18:16,  reg_unstable_t2_tick_sel unsigned, default =
// 0, reg_unstable_t2_tick_sel Bit   15:0,   reg_unstable_t2_thd                 unsigned, default
// = 0, reg_unstable_t2_thd
#define EARCRX_DMAC_SYNC_STAT1 ((0x0028 << 2) + 0xfe333c00)
// Bit   31:0,   reg_dmac_sync_stat1           unsigned, default = 0
#define EARCRX_DMAC_SYNC_STAT2 ((0x0029 << 2) + 0xfe333c00)
// Bit   31:0,   reg_dmac_sync_stat2           unsigned, default = 0
#define EARCRX_DMAC_SYNC_STAT3 ((0x002a << 2) + 0xfe333c00)
// Bit   31:0,   reg_dmac_sync_stat3           unsigned, default = 0
//
// Closing file:  earcrx_dmac.h
//
//========================================================================
//  AUDIO EARCRX_TOP  - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333e00
// -----------------------------------------------
//
// Reading file:  earcrx_top.h
//
#define EARCRX_TOP_CTRL0 ((0x0000 << 2) + 0xfe333e00)
// Bit   31:10,  reserved
// Bit   9:8,    reg_top_debug_sel             unsigned, default = 0, top debug select
// Bit   7,      reg_spdif_rx_en_force         unsigned, default = 0, force spdif_rx_en to
// reg_spdif_rx_en_force_value Bit   6,      reg_spdif_rx_en_force_value   unsigned, default = 0,
// value Bit   5,      reg_spdif_rx_sqen_force       unsigned, default = 0, force spdif_rx_sqen to
// reg_spdif_rx_sqe Bit   4,      reg_spdif_rx_sqen_force_value unsigned, default = 0, value Bit 3,
// reg_dmacrx_en_force           unsigned, default = 0, force dmacrx_en to
// reg_dmacrx_en_force_value Bit   2,      reg_dmacrx_en_force_value     unsigned, default = 0,
// value Bit   1,      reg_dmacrx_sqen_force         unsigned, default = 0, force dmacrx_sqen to
// reg_dmacrx_sqen_force_value Bit   0,      reg_dmacrx_sqen_force_value   unsigned, default = 0,
// value
#define EARCRX_DMAC_INT_MASK ((0x0001 << 2) + 0xfe333e00)
// Bit   31:30,  reserved
// Bit   29:0,   reg_dmac_int_mask             unsigned, default = 0, dmac int mask
#define EARCRX_DMAC_INT_PENDING ((0x0002 << 2) + 0xfe333e00)
// Bit   31:30,  reserved
// Bit   29:0,   reg_dmac_int_mask             unsigned, default = 0, dmac int pending,read only
#define EARCRX_CMDC_INT_MASK ((0x0003 << 2) + 0xfe333e00)
// Bit   31:16,  reserved
// Bit   15:0,   reg_cmdc_int_mask             unsigned, default = 0, cmdc int mask
#define EARCRX_CMDC_INT_PENDING ((0x0004 << 2) + 0xfe333e00)
// Bit   31:18,  reserved
// Bit   17:0,   reg_cmdc_int_mask             unsigned, default = 0, cmdc int pending,read only
#define EARCRX_ANA_CTRL0 ((0x0005 << 2) + 0xfe333e00)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define EARCRX_ANA_CTRL1 ((0x0006 << 2) + 0xfe333e00)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define EARCRX_ANA_STAT0 ((0x0007 << 2) + 0xfe333e00)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define EARCRX_PLL_CTRL0 ((0x0008 << 2) + 0xfe333e00)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define EARCRX_PLL_CTRL1 ((0x0009 << 2) + 0xfe333e00)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define EARCRX_PLL_CTRL2 ((0x000a << 2) + 0xfe333e00)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define EARCRX_PLL_CTRL3 ((0x000b << 2) + 0xfe333e00)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define EARCRX_PLL_STAT0 ((0x000c << 2) + 0xfe333e00)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
//
// Closing file:  earcrx_top.h
//
//========================================================================
//  AUDIO RESAMPLEB - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe334000
// -----------------------------------------------
//
// Reading file:  RESAMPLEB.h
//
#define AUDIO_RSAMPB_CTRL0 ((0x0000 << 2) + 0xfe334000)
// Bit   31:3      reserved
// Bit   2         reg_lock_rst      //unsigned  , default =0;
// Bit   1         reg_rsamp_rst     //unsigned  , default =0;
// Bit   0         reg_sw_rst        //unsigned  , default =0;
#define AUDIO_RSAMPB_CTRL1 ((0x0001 << 2) + 0xfe334000)
// Bit   31:27      reserved          //unsigned  , default =0;
// Bit   26         reg_watchdog_en   //unsigned  , default =0;
// Bit   25         reg_rsamp_rst_sel //unsigned  , default =0;
// Bit   24         reg_module_bypas  //unsigned  , default =0;
// Bit   23:18      reg_gclk_ctrl     //unsigned  , default =0;
// Bit   17:13      reg_in_msb        //unsigned  , default =23;
// Bit   12         reg_output_en     //unsigned  , default =0;
// Bit   11         reg_rsamp_en      //unsigned  , default =0;
// Bit   10         reg_filt_en       //unsigned  , default =0;
// Bit   9          reg_post_en       //unsigned  , default =0;
// Bit   8          reg_inp_mux_mode  //unsigned  , default =0;
// Bit   7:4        reserved          //unsigned  , default =2;
// Bit   3:0        reg_inp_mux       //unsigned  , default =0;
#define AUDIO_RSAMPB_CTRL2 ((0x0002 << 2) + 0xfe334000)
// Bit 31:30    reserved              //unsigned  , default =0;
// Bit 29:24    reg_chx_size          //unsigned  , default =2;
// Bit 23:18    reserved              //unsigned  , default =0;
// Bit 17:16    reg_scl_step          //unsigned  , default =0; 0: 1/1  1: 1/2  2: 1/4
// Bit 15:8     reg_filt_tap          //unsigned  , default =63;
// Bit 7:0      reg_intp_tap          //unsigned  , default =63;
#define AUDIO_RSAMPB_PHSINIT ((0x0003 << 2) + 0xfe334000)
// Bit   31:28      reserved          //unsigned  , default = 0;
// Bit   27:0       reg_init_phs      //unsigned  , default = 0;
#define AUDIO_RSAMPB_PHSSTEP ((0x0004 << 2) + 0xfe334000)
// Bit   31         reserved          //unsigned  , default = 0;
// Bit   30:0       reg_rsamp_step    //unsigned  , default = 134217728;//'h800_0000
#define AUDIO_RSAMPB_SHIFT ((0x0005 << 2) + 0xfe334000)
// Bit   31:24       reg_rsft_iir    //unsigned  , default = 23;
// Bit   23:16       reg_rsft_blnd   //unsigned  , default = 21;
// Bit   15:8        reg_rsft_sinc   //unsigned  , default = 31;
// Bit   7:0         reg_rsft_aa     //unsigned  , default = 31;
#define AUDIO_RSAMPB_ADJ_CTRL0 ((0x0006 << 2) + 0xfe334000)
// Bit   31:3        reserved                //unsigned
// Bit   2           reg_rsamp_adj_out_inv   //unsigned , default = 0;
// Bit   1           reg_rsamp_adj_force_en  //unsigned , default = 0;
// Bit   0           reg_rsamp_adj_en        //unsigned , default = 0;
#define AUDIO_RSAMPB_ADJ_CTRL1 ((0x0007 << 2) + 0xfe334000)
// Bit   31:16       reg_rsamp_adj_odet_step     //unsigned , default = 8;
// Bit   15:0        reg_rsamp_adj_kmax          //unsigned , default = 32768;
#define AUDIO_RSAMPB_ADJ_SFT ((0x0008 << 2) + 0xfe334000)
// Bit   31:30       reserved                //unsigned , default = 0;
// Bit   29          reg_rsamp_adj_dif_sel   //unsigned , default = 0;
// Bit   28:24       reg_rsamp_adj_ki        //unsigned , default = 9;
// Bit   23:21       reserved                //unsigned , default = 0;
// Bit   20:16       reg_rsamp_adj_kp        //unsigned , default = 1;
// Bit   15:13       reserved                //unsigned , default = 0;
// Bit   12:8        reg_rsamp_adj_ki_sft    //unsigned , default = 6;
// Bit   7:6         reserved                //unsigned , default = 0;
// Bit   5:0         reg_rsamp_adj_out_sft   //unsigned , default = 12;
#define AUDIO_RSAMPB_ADJ_IDET_LEN ((0x0009 << 2) + 0xfe334000)
// Bit   31:0       reg_rsamp_adj_idet_len       //unsigned , default = 10000;
#define AUDIO_RSAMPB_ADJ_FORCE ((0x000a << 2) + 0xfe334000)
// Bit   31:0       reg_rsamp_adj_force_err      //signed , default = 8;
#define AUDIO_RSAMPB_ADJ_KI_FORCE ((0x000b << 2) + 0xfe334000)
// Bit   31:0       reg_rsamp_adj_ki_force //signed , default = 0;
#define AUDIO_RSAMPB_WATCHDOG_THRD ((0x000c << 2) + 0xfe334000)
// Bit   31:0       reg_watchdog_thrd      //signed , default = 32'h1000;
#define AUDIO_RSAMPB_RO_STATUS ((0x0010 << 2) + 0xfe334000)
// Bit   31:0       ro_rsamp_stat  //{din_chx_chk_err,is_idle_st,rsamp_fifo_over_cnt[7:0]}
#define AUDIO_RSAMPB_RO_ADJ_FREQ ((0x0011 << 2) + 0xfe334000)
// Bit   31:0       ro_rsamp_adj_freq
#define AUDIO_RSAMPB_RO_ADJ_DIFF_BAK ((0x0012 << 2) + 0xfe334000)
// Bit   31:0       ro_det_diff_bak
#define AUDIO_RSAMPB_RO_ADJ_DIFF_DLT ((0x0013 << 2) + 0xfe334000)
// Bit   31:0       ro_det_diff_dlt
#define AUDIO_RSAMPB_RO_ADJ_PHS_ERR ((0x0014 << 2) + 0xfe334000)
// Bit   31:0       ro_det_phase_err
#define AUDIO_RSAMPB_RO_ADJ_KI_OUT ((0x0015 << 2) + 0xfe334000)
// Bit   31:0       ro_rsamp_ki_out
#define AUDIO_RSAMPB_RO_IN_CNT ((0x0016 << 2) + 0xfe334000)
// Bit   31:0       ro_rsamp_in_cnt
#define AUDIO_RSAMPB_RO_OUT_CNT ((0x0017 << 2) + 0xfe334000)
// Bit   31:0       ro_rsamp_out_cnt
#define AUDIO_RSAMPB_RO_ADJ_PHS_ERR_VAR ((0x0018 << 2) + 0xfe334000)
// Bit   31:0       ro_det_phase_err_var
#define AUDIO_RSAMPB_POST_COEF0 ((0x0020 << 2) + 0xfe334000)
// Bit   31:0       reg_post_coef0 //signed  , default = 0;
#define AUDIO_RSAMPB_POST_COEF1 ((0x0021 << 2) + 0xfe334000)
// Bit   31:0       reg_post_coef1 //signed  , default = 0;
#define AUDIO_RSAMPB_POST_COEF2 ((0x0022 << 2) + 0xfe334000)
// Bit   31:0       reg_post_coef2 //signed  , default = 0;
#define AUDIO_RSAMPB_POST_COEF3 ((0x0023 << 2) + 0xfe334000)
// Bit   31:0       reg_post_coef3 //signed  , default = 0;
#define AUDIO_RSAMPB_POST_COEF4 ((0x0024 << 2) + 0xfe334000)
// Bit   31:0       reg_post_coef4 //signed  , default = 0;
#define AUDIO_RSAMPB_AA_COEF_ADDR ((0x0030 << 2) + 0xfe334000)
// Bit   31:0       reg_aa_coef_addr     //unsigned, default = 0;
#define AUDIO_RSAMPB_AA_COEF_DATA ((0x0031 << 2) + 0xfe334000)
// Bit   31:0       reg_aa_coef_data     //signed  , default = 0;
#define AUDIO_RSAMPB_SINC_COEF_ADDR ((0x0040 << 2) + 0xfe334000)
// Bit   31:0       reg_sinc_coef_addr   //unsigned, default = 0;
#define AUDIO_RSAMPB_SINC_COEF_DATA ((0x0041 << 2) + 0xfe334000)
// Bit   31:0       reg_sinc_coef_data   //signed  , default = 0;
//
// Closing file:  RESAMPLEB.h
//
//========================================================================
//  AUDIO TOP_VAD - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  APB0_BASE_ADDR = 0xfe334c00
// -----------------------------------------------
#define EE_AUDIO2_CLK81_CTRL ((0x0000 << 2) + 0xfe334c00)
#define EE_AUDIO2_CLK81_EN ((0x0001 << 2) + 0xfe334c00)
#define EE_AUDIO2_SW_RESET0 ((0x0002 << 2) + 0xfe334c00)
#define EE_AUDIO2_CLK_GATE_EN0 ((0x0003 << 2) + 0xfe334c00)
#define EE_AUDIO2_SECURITY_CTRL0 ((0x0004 << 2) + 0xfe334c00)
#define EE_AUDIO2_SECURITY_CTRL1 ((0x0005 << 2) + 0xfe334c00)
#define EE_AUDIO2_MCLK_VAD_CTRL ((0x0010 << 2) + 0xfe334c00)
#define EE_AUDIO2_VAD_CLK_CTRL ((0x0011 << 2) + 0xfe334c00)
#define EE_AUDIO2_MST_DLY_CTRL0 ((0x0012 << 2) + 0xfe334c00)
#define EE_AUDIO2_MST_VAD_SCLK_CTRL0 ((0x0013 << 2) + 0xfe334c00)
#define EE_AUDIO2_MST_VAD_SCLK_CTRL1 ((0x0014 << 2) + 0xfe334c00)
#define EE_AUDIO2_CLK_TDMIN_VAD_CTRL ((0x0015 << 2) + 0xfe334c00)
#define EE_AUDIO2_CLK_PDMIN_CTRL0 ((0x0016 << 2) + 0xfe334c00)
#define EE_AUDIO2_CLK_PDMIN_CTRL1 ((0x0017 << 2) + 0xfe334c00)
#define EE_AUDIO2_AUD_VAD_PAD_CTRL0 ((0x0018 << 2) + 0xfe334c00)
#define EE_AUDIO2_TOVAD_CTRL0 ((0x0020 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CTRL0 ((0x0030 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CTRL1 ((0x0031 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CTRL2 ((0x0032 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_START_ADDR ((0x0033 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_INIT_ADDR ((0x0034 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_FINISH_ADDR ((0x0035 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_START_ADDRB ((0x0036 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_FINISH_ADDRB ((0x0037 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_INT_ADDR ((0x0038 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_STATUS1 ((0x0039 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_STATUS2 ((0x003a << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_CTRL ((0x0040 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_SWAP0 ((0x0041 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_SWAP1 ((0x0042 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MUTE_VAL ((0x0043 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_STAT ((0x0044 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MUTE0 ((0x0050 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MUTE1 ((0x0051 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MUTE2 ((0x0052 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MUTE3 ((0x0053 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MUTE4 ((0x0054 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MUTE5 ((0x0055 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MUTE6 ((0x0056 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MUTE7 ((0x0057 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MASK0 ((0x0058 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MASK1 ((0x0059 << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MASK2 ((0x005a << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MASK3 ((0x005b << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MASK4 ((0x005c << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MASK5 ((0x005d << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MASK6 ((0x005e << 2) + 0xfe334c00)
#define EE_AUDIO2_TDMIN_VAD_MASK7 ((0x005f << 2) + 0xfe334c00)
#define EE_AUDIO2_VAD_DAT_PAD_CTRL0 ((0x0060 << 2) + 0xfe334c00)
#define EE_AUDIO2_VAD_DAT_PAD_CTRL1 ((0x0061 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CHNUM_ID0 ((0x0070 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CHNUM_ID1 ((0x0071 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CHNUM_ID2 ((0x0072 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CHNUM_ID3 ((0x0073 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CHNUM_ID4 ((0x0074 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CHNUM_ID5 ((0x0075 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CHNUM_ID6 ((0x0076 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CHNUM_ID7 ((0x0077 << 2) + 0xfe334c00)
#define EE_AUDIO2_TODDR_VAD_CHSYNC_CTRL ((0x007f << 2) + 0xfe334c00)
#define EE_AUDIO2_VAD_AM2AXI_CTRL0 ((0x0080 << 2) + 0xfe334c00)
#define EE_AUDIO2_VAD_AXIWR_ASYNC_CTRL0 ((0x0081 << 2) + 0xfe334c00)
#define EE_AUDIO2_VAD_AM2AXI_STAT ((0x0088 << 2) + 0xfe334c00)
#define EE_AUDIO2_VAD_AXIWR_ASYNC_STAT ((0x0089 << 2) + 0xfe334c00)
#define EE_AUDIO2_EXCEPTION_IRQ_STS0 ((0x0090 << 2) + 0xfe334c00)
#define EE_AUDIO2_EXCEPTION_IRQ_MASK0 ((0x0091 << 2) + 0xfe334c00)
#define EE_AUDIO2_EXCEPTION_IRQ_MODE0 ((0x0092 << 2) + 0xfe334c00)
#define EE_AUDIO2_EXCEPTION_IRQ_CLR0 ((0x0093 << 2) + 0xfe334c00)
#define EE_AUDIO2_EXCEPTION_IRQ_INV0 ((0x0094 << 2) + 0xfe334c00)
//
// Closing file:  REG_LIST_AUDIO_RTL.h
//
//
// Reading file:  REG_LIST_DSP_RTL.h
//
// synopsys translate_off
// synopsys translate_on
//========================================================================
//  DSPA - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe340000
// -----------------------------------------------
#define DSP_CFG0 ((0x0000 << 2) + 0xfe340000)
#define DSP_CFG1 ((0x0001 << 2) + 0xfe340000)
#define DSP_CFG2 ((0x0002 << 2) + 0xfe340000)
#define DSP_IMPWIRE ((0x0003 << 2) + 0xfe340000)
#define DSP_RESET_VEC ((0x0004 << 2) + 0xfe340000)
#define DSP_SEC_CFG0 ((0x0006 << 2) + 0xfe340000)
#define DSP_SEC_CFG1 ((0x0007 << 2) + 0xfe340000)
#define DSP_IRQ_CTRL0 ((0x0010 << 2) + 0xfe340000)
#define DSP_IRQ_CTRL1 ((0x0011 << 2) + 0xfe340000)
#define DSP_IRQ_CTRL2 ((0x0012 << 2) + 0xfe340000)
#define DSP_IRQ_CTRL3 ((0x0013 << 2) + 0xfe340000)
#define DSP_IRQ_CTRL4 ((0x0014 << 2) + 0xfe340000)
#define DSP_IRQ_CTRL5 ((0x0015 << 2) + 0xfe340000)
#define DSP_IRQ_CTRL6 ((0x0016 << 2) + 0xfe340000)
#define DSP_IRQ_CTRL7 ((0x0017 << 2) + 0xfe340000)
#define DSP_IRQ_CTRL8 ((0x0018 << 2) + 0xfe340000)
#define DSP_IRQ_CTRL9 ((0x0019 << 2) + 0xfe340000)
#define DSP_IRQ_STS ((0x001f << 2) + 0xfe340000)
#define DSP_REMAP0 ((0x0020 << 2) + 0xfe340000)
#define DSP_REMAP1 ((0x0021 << 2) + 0xfe340000)
#define DSP_REMAP2 ((0x0022 << 2) + 0xfe340000)
#define DSP_STS0 ((0x0040 << 2) + 0xfe340000)
#define DSP_STS1 ((0x0041 << 2) + 0xfe340000)
#define DSP_STS2 ((0x0042 << 2) + 0xfe340000)
#define DSP_STS3 ((0x0043 << 2) + 0xfe340000)
#define DSP_STS4 ((0x0044 << 2) + 0xfe340000)
#define DSP_STS5 ((0x0045 << 2) + 0xfe340000)
#define DSP_QIF_CTRL ((0x0080 << 2) + 0xfe340000)
#define DSP_QIF_STS ((0x0081 << 2) + 0xfe340000)
#define DSP_WRFIFO_TOCPUA ((0x0082 << 2) + 0xfe340000)
#define DSP_WRFIFO_TOCPUB ((0x0083 << 2) + 0xfe340000)
#define DSP_WRFIFO_TODSP ((0x0084 << 2) + 0xfe340000)
#define DSP_RDFIFO_FRCPUA ((0x0088 << 2) + 0xfe340000)
#define DSP_RDFIFO_FRCPUB ((0x0089 << 2) + 0xfe340000)
#define DSP_RDFIFO_FRDSP ((0x008a << 2) + 0xfe340000)
#define DSP_PM_CTRL ((0x0090 << 2) + 0xfe340000)
#define DSP_PDEBUGDATA_STS ((0x0091 << 2) + 0xfe340000)
#define DSP_PDEBUGINST_STS ((0x0092 << 2) + 0xfe340000)
#define DSP_PDEBUGLS0STAT_STS ((0x0093 << 2) + 0xfe340000)
#define DSP_PDEBUGLS1STAT_STS ((0x0094 << 2) + 0xfe340000)
#define DSP_PDEBUGOUTPIF_STS ((0x0095 << 2) + 0xfe340000)
#define DSP_PDEBUGPC_STS ((0x0096 << 2) + 0xfe340000)
#define DSP_PDEBUGPREFETCHL1FILL_STS ((0x0097 << 2) + 0xfe340000)
#define DSP_PDEBUGPREFETCHLOOKUP_STS ((0x0098 << 2) + 0xfe340000)
#define DSP_PDEBUGSTATUS_STS ((0x0099 << 2) + 0xfe340000)
//========================================================================
//  DSPB - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe350000
// -----------------------------------------------
#define DSPB_CFG0 ((0x0000 << 2) + 0xfe350000)
#define DSPB_CFG1 ((0x0001 << 2) + 0xfe350000)
#define DSPB_CFG2 ((0x0002 << 2) + 0xfe350000)
#define DSPB_IMPWIRE ((0x0003 << 2) + 0xfe350000)
#define DSPB_RESET_VEC ((0x0004 << 2) + 0xfe350000)
#define DSPB_SEC_CFG0 ((0x0006 << 2) + 0xfe350000)
#define DSPB_SEC_CFG1 ((0x0007 << 2) + 0xfe350000)
#define DSPB_IRQ_CTRL0 ((0x0010 << 2) + 0xfe350000)
#define DSPB_IRQ_CTRL1 ((0x0011 << 2) + 0xfe350000)
#define DSPB_IRQ_CTRL2 ((0x0012 << 2) + 0xfe350000)
#define DSPB_IRQ_CTRL3 ((0x0013 << 2) + 0xfe350000)
#define DSPB_IRQ_CTRL4 ((0x0014 << 2) + 0xfe350000)
#define DSPB_IRQ_CTRL5 ((0x0015 << 2) + 0xfe350000)
#define DSPB_IRQ_CTRL6 ((0x0016 << 2) + 0xfe350000)
#define DSPB_IRQ_CTRL7 ((0x0017 << 2) + 0xfe350000)
#define DSPB_IRQ_CTRL8 ((0x0018 << 2) + 0xfe350000)
#define DSPB_IRQ_CTRL9 ((0x0019 << 2) + 0xfe350000)
#define DSPB_IRQ_STS ((0x001f << 2) + 0xfe350000)
#define DSPB_REMAP0 ((0x0020 << 2) + 0xfe350000)
#define DSPB_REMAP1 ((0x0021 << 2) + 0xfe350000)
#define DSPB_REMAP2 ((0x0022 << 2) + 0xfe350000)
#define DSPB_STS0 ((0x0040 << 2) + 0xfe350000)
#define DSPB_STS1 ((0x0041 << 2) + 0xfe350000)
#define DSPB_STS2 ((0x0042 << 2) + 0xfe350000)
#define DSPB_STS3 ((0x0043 << 2) + 0xfe350000)
#define DSPB_STS4 ((0x0044 << 2) + 0xfe350000)
#define DSPB_STS5 ((0x0045 << 2) + 0xfe350000)
#define DSPB_QIF_CTRL ((0x0080 << 2) + 0xfe350000)
#define DSPB_QIF_STS ((0x0081 << 2) + 0xfe350000)
#define DSPB_WRFIFO_TOCPUA ((0x0082 << 2) + 0xfe350000)
#define DSPB_WRFIFO_TOCPUB ((0x0083 << 2) + 0xfe350000)
#define DSPB_WRFIFO_TODSP ((0x0084 << 2) + 0xfe350000)
#define DSPB_RDFIFO_FRCPUA ((0x0088 << 2) + 0xfe350000)
#define DSPB_RDFIFO_FRCPUB ((0x0089 << 2) + 0xfe350000)
#define DSPB_RDFIFO_FRDSP ((0x008a << 2) + 0xfe350000)
#define DSPB_PM_CTRL ((0x0090 << 2) + 0xfe350000)
#define DSPB_PDEBUGDATA_STS ((0x0091 << 2) + 0xfe350000)
#define DSPB_PDEBUGINST_STS ((0x0092 << 2) + 0xfe350000)
#define DSPB_PDEBUGLS0STAT_STS ((0x0093 << 2) + 0xfe350000)
#define DSPB_PDEBUGLS1STAT_STS ((0x0094 << 2) + 0xfe350000)
#define DSPB_PDEBUGOUTPIF_STS ((0x0095 << 2) + 0xfe350000)
#define DSPB_PDEBUGPC_STS ((0x0096 << 2) + 0xfe350000)
#define DSPB_PDEBUGPREFETCHL1FILL_STS ((0x0097 << 2) + 0xfe350000)
#define DSPB_PDEBUGPREFETCHLOOKUP_STS ((0x0098 << 2) + 0xfe350000)
#define DSPB_PDEBUGSTATUS_STS ((0x0099 << 2) + 0xfe350000)
// synopsys translate_off
// synopsys translate_on
//
// Closing file:  REG_LIST_DSP_RTL.h
//
//
// Reading file:  REG_LIST_SECURITY_RTL.h
//
//
/****************************************************************************
 * Title:      REG_LIST_SECURITY_RTL.h
 *
 * Author:     shan.luan
 *
 * Created:    23:09:44 28/02/2020
 *
 * Description:
 *
 * Note:
 *
 * History:
 *
 ****************************************************************************
 * ========================================================================
 *   TS_DEMUX_REG - Registers
 * ========================================================================
 * -----------------------------------------------
 * REG_BASE:  REGISTER_BASE_ADDR = 0xfe444000
 * -----------------------------------------------
 ****************************************************************************/
#define RCH_READY_CHANNEL_0 ((0x0000 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_1 ((0x0008 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_2 ((0x0010 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_3 ((0x0018 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_4 ((0x0020 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_5 ((0x0028 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_6 ((0x0030 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_7 ((0x0038 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_8 ((0x0040 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_9 ((0x0048 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_10 ((0x0050 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_11 ((0x0058 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_12 ((0x0060 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_13 ((0x0068 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_14 ((0x0070 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_15 ((0x0078 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_16 ((0x0080 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_17 ((0x0088 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_18 ((0x0090 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_19 ((0x0098 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_20 ((0x00a0 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_21 ((0x00a8 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_22 ((0x00b0 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_23 ((0x00b8 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_24 ((0x00c0 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_25 ((0x00c8 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_26 ((0x00d0 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_27 ((0x00d8 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_28 ((0x00e0 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_29 ((0x00e8 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_30 ((0x00f0 << 2) + 0xfe444000)
#define RCH_READY_CHANNEL_31 ((0x00f8 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_0 ((0x0001 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_1 ((0x0009 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_2 ((0x0011 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_3 ((0x0019 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_4 ((0x0021 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_5 ((0x0029 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_6 ((0x0031 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_7 ((0x0039 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_8 ((0x0041 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_9 ((0x0049 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_10 ((0x0051 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_11 ((0x0059 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_12 ((0x0061 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_13 ((0x0069 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_14 ((0x0071 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_15 ((0x0079 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_16 ((0x0081 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_17 ((0x0089 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_18 ((0x0091 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_19 ((0x0099 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_20 ((0x00a1 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_21 ((0x00a9 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_22 ((0x00b1 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_23 ((0x00b9 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_24 ((0x00c1 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_25 ((0x00c9 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_26 ((0x00d1 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_27 ((0x00d9 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_28 ((0x00e1 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_29 ((0x00e9 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_30 ((0x00f1 << 2) + 0xfe444000)
#define RCH_STATUS_CHANNEL_31 ((0x00f9 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_0 ((0x0002 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_1 ((0x000a << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_2 ((0x0012 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_3 ((0x001a << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_4 ((0x0022 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_5 ((0x002a << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_6 ((0x0032 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_7 ((0x003a << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_8 ((0x0042 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_9 ((0x004a << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_10 ((0x0052 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_11 ((0x005a << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_12 ((0x0062 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_13 ((0x006a << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_14 ((0x0072 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_15 ((0x007a << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_16 ((0x0082 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_17 ((0x008a << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_18 ((0x0092 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_19 ((0x009a << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_20 ((0x00a2 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_21 ((0x00aa << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_22 ((0x00b2 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_23 ((0x00ba << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_24 ((0x00c2 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_25 ((0x00ca << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_26 ((0x00d2 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_27 ((0x00da << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_28 ((0x00e2 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_29 ((0x00ea << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_30 ((0x00f2 << 2) + 0xfe444000)
#define RCH_CFG_CHANNEL_31 ((0x00fa << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_0 ((0x0003 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_1 ((0x000b << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_2 ((0x0013 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_3 ((0x001b << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_4 ((0x0023 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_5 ((0x002b << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_6 ((0x0033 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_7 ((0x003b << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_8 ((0x0043 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_9 ((0x004b << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_10 ((0x0053 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_11 ((0x005b << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_12 ((0x0063 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_13 ((0x006b << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_14 ((0x0073 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_15 ((0x007b << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_16 ((0x0083 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_17 ((0x008b << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_18 ((0x0093 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_19 ((0x009b << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_20 ((0x00a3 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_21 ((0x00ab << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_22 ((0x00b3 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_23 ((0x00bb << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_24 ((0x00c3 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_25 ((0x00cb << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_26 ((0x00d3 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_27 ((0x00db << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_28 ((0x00e3 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_29 ((0x00eb << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_30 ((0x00f3 << 2) + 0xfe444000)
#define RCH_ADDR_CHANNEL_31 ((0x00fb << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_0 ((0x0004 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_1 ((0x000c << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_2 ((0x0014 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_3 ((0x001c << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_4 ((0x0024 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_5 ((0x002c << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_6 ((0x0034 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_7 ((0x003c << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_8 ((0x0044 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_9 ((0x004c << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_10 ((0x0054 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_11 ((0x005c << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_12 ((0x0064 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_13 ((0x006c << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_14 ((0x0074 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_15 ((0x007c << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_16 ((0x0084 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_17 ((0x008c << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_18 ((0x0094 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_19 ((0x009c << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_20 ((0x00a4 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_21 ((0x00ac << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_22 ((0x00b4 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_23 ((0x00bc << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_24 ((0x00c4 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_25 ((0x00cc << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_26 ((0x00d4 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_27 ((0x00dc << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_28 ((0x00e4 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_29 ((0x00ec << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_30 ((0x00f4 << 2) + 0xfe444000)
#define RCH_LEN_CHANNEL_31 ((0x00fc << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_0 ((0x0005 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_1 ((0x000d << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_2 ((0x0015 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_3 ((0x001d << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_4 ((0x0025 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_5 ((0x002d << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_6 ((0x0035 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_7 ((0x003d << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_8 ((0x0045 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_9 ((0x004d << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_10 ((0x0055 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_11 ((0x005d << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_12 ((0x0065 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_13 ((0x006d << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_14 ((0x0075 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_15 ((0x007d << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_16 ((0x0085 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_17 ((0x008d << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_18 ((0x0095 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_19 ((0x009d << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_20 ((0x00a5 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_21 ((0x00ad << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_22 ((0x00b5 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_23 ((0x00bd << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_24 ((0x00c5 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_25 ((0x00cd << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_26 ((0x00d5 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_27 ((0x00dd << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_28 ((0x00e5 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_29 ((0x00ed << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_30 ((0x00f5 << 2) + 0xfe444000)
#define RCH_RD_LEN_CHANNEL_31 ((0x00fd << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_0 ((0x0006 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_1 ((0x000e << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_2 ((0x0016 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_3 ((0x001e << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_4 ((0x0026 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_5 ((0x002e << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_6 ((0x0036 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_7 ((0x003e << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_8 ((0x0046 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_9 ((0x004e << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_10 ((0x0056 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_11 ((0x005e << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_12 ((0x0066 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_13 ((0x006e << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_14 ((0x0076 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_15 ((0x007e << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_16 ((0x0086 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_17 ((0x008e << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_18 ((0x0096 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_19 ((0x009e << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_20 ((0x00a6 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_21 ((0x00ae << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_22 ((0x00b6 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_23 ((0x00be << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_24 ((0x00c6 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_25 ((0x00ce << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_26 ((0x00d6 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_27 ((0x00de << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_28 ((0x00e6 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_29 ((0x00ee << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_30 ((0x00f6 << 2) + 0xfe444000)
#define RCH_PTR_CHANNEL_31 ((0x00fe << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_0 ((0x0007 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_1 ((0x000f << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_2 ((0x0017 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_3 ((0x001f << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_4 ((0x0027 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_5 ((0x002f << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_6 ((0x0037 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_7 ((0x003f << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_8 ((0x0047 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_9 ((0x004f << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_10 ((0x0057 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_11 ((0x005f << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_12 ((0x0067 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_13 ((0x006f << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_14 ((0x0077 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_15 ((0x007f << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_16 ((0x0087 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_17 ((0x008f << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_18 ((0x0097 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_19 ((0x009f << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_20 ((0x00a7 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_21 ((0x00af << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_22 ((0x00b7 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_23 ((0x00bf << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_24 ((0x00c7 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_25 ((0x00cf << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_26 ((0x00d7 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_27 ((0x00df << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_28 ((0x00e7 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_29 ((0x00ef << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_30 ((0x00f7 << 2) + 0xfe444000)
#define RCH_PKT_SYNC_STATUS_CHANNEL_31 ((0x00ff << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_0 ((0x0400 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_1 ((0x0408 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_2 ((0x0410 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_3 ((0x0418 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_4 ((0x0420 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_5 ((0x0428 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_6 ((0x0430 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_7 ((0x0438 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_8 ((0x0440 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_9 ((0x0448 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_10 ((0x0450 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_11 ((0x0458 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_12 ((0x0460 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_13 ((0x0468 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_14 ((0x0470 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_15 ((0x0478 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_16 ((0x0480 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_17 ((0x0488 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_18 ((0x0490 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_19 ((0x0498 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_20 ((0x04a0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_21 ((0x04a8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_22 ((0x04b0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_23 ((0x04b8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_24 ((0x04c0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_25 ((0x04c8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_26 ((0x04d0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_27 ((0x04d8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_28 ((0x04e0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_29 ((0x04e8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_30 ((0x04f0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_31 ((0x04f8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_32 ((0x0500 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_33 ((0x0508 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_34 ((0x0510 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_35 ((0x0518 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_36 ((0x0520 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_37 ((0x0528 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_38 ((0x0530 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_39 ((0x0538 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_40 ((0x0540 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_41 ((0x0548 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_42 ((0x0550 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_43 ((0x0558 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_44 ((0x0560 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_45 ((0x0568 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_46 ((0x0570 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_47 ((0x0578 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_48 ((0x0580 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_49 ((0x0588 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_50 ((0x0590 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_51 ((0x0598 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_52 ((0x05a0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_53 ((0x05a8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_54 ((0x05b0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_55 ((0x05b8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_56 ((0x05c0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_57 ((0x05c8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_58 ((0x05d0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_59 ((0x05d8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_60 ((0x05e0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_61 ((0x05e8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_62 ((0x05f0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_63 ((0x05f8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_64 ((0x0600 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_65 ((0x0608 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_66 ((0x0610 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_67 ((0x0618 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_68 ((0x0620 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_69 ((0x0628 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_70 ((0x0630 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_71 ((0x0638 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_72 ((0x0640 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_73 ((0x0648 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_74 ((0x0650 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_75 ((0x0658 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_76 ((0x0660 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_77 ((0x0668 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_78 ((0x0670 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_79 ((0x0678 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_80 ((0x0680 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_81 ((0x0688 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_82 ((0x0690 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_83 ((0x0698 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_84 ((0x06a0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_85 ((0x06a8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_86 ((0x06b0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_87 ((0x06b8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_88 ((0x06c0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_89 ((0x06c8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_90 ((0x06d0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_91 ((0x06d8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_92 ((0x06e0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_93 ((0x06e8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_94 ((0x06f0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_95 ((0x06f8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_96 ((0x0700 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_97 ((0x0708 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_98 ((0x0710 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_99 ((0x0718 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_100 ((0x0720 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_101 ((0x0728 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_102 ((0x0730 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_103 ((0x0738 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_104 ((0x0740 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_105 ((0x0748 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_106 ((0x0750 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_107 ((0x0758 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_108 ((0x0760 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_109 ((0x0768 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_110 ((0x0770 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_111 ((0x0778 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_112 ((0x0780 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_113 ((0x0788 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_114 ((0x0790 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_115 ((0x0798 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_116 ((0x07a0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_117 ((0x07a8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_118 ((0x07b0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_119 ((0x07b8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_120 ((0x07c0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_121 ((0x07c8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_122 ((0x07d0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_123 ((0x07d8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_124 ((0x07e0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_125 ((0x07e8 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_126 ((0x07f0 << 2) + 0xfe444000)
#define WCH_READY_CHANNEL_127 ((0x07f8 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_0 ((0x0401 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_1 ((0x0409 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_2 ((0x0411 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_3 ((0x0419 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_4 ((0x0421 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_5 ((0x0429 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_6 ((0x0431 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_7 ((0x0439 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_8 ((0x0441 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_9 ((0x0449 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_10 ((0x0451 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_11 ((0x0459 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_12 ((0x0461 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_13 ((0x0469 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_14 ((0x0471 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_15 ((0x0479 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_16 ((0x0481 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_17 ((0x0489 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_18 ((0x0491 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_19 ((0x0499 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_20 ((0x04a1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_21 ((0x04a9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_22 ((0x04b1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_23 ((0x04b9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_24 ((0x04c1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_25 ((0x04c9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_26 ((0x04d1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_27 ((0x04d9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_28 ((0x04e1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_29 ((0x04e9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_30 ((0x04f1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_31 ((0x04f9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_32 ((0x0501 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_33 ((0x0509 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_34 ((0x0511 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_35 ((0x0519 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_36 ((0x0521 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_37 ((0x0529 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_38 ((0x0531 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_39 ((0x0539 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_40 ((0x0541 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_41 ((0x0549 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_42 ((0x0551 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_43 ((0x0559 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_44 ((0x0561 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_45 ((0x0569 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_46 ((0x0571 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_47 ((0x0579 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_48 ((0x0581 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_49 ((0x0589 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_50 ((0x0591 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_51 ((0x0599 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_52 ((0x05a1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_53 ((0x05a9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_54 ((0x05b1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_55 ((0x05b9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_56 ((0x05c1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_57 ((0x05c9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_58 ((0x05d1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_59 ((0x05d9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_60 ((0x05e1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_61 ((0x05e9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_62 ((0x05f1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_63 ((0x05f9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_64 ((0x0601 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_65 ((0x0609 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_66 ((0x0611 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_67 ((0x0619 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_68 ((0x0621 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_69 ((0x0629 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_70 ((0x0631 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_71 ((0x0639 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_72 ((0x0641 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_73 ((0x0649 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_74 ((0x0651 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_75 ((0x0659 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_76 ((0x0661 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_77 ((0x0669 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_78 ((0x0671 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_79 ((0x0679 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_80 ((0x0681 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_81 ((0x0689 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_82 ((0x0691 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_83 ((0x0699 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_84 ((0x06a1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_85 ((0x06a9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_86 ((0x06b1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_87 ((0x06b9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_88 ((0x06c1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_89 ((0x06c9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_90 ((0x06d1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_91 ((0x06d9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_92 ((0x06e1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_93 ((0x06e9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_94 ((0x06f1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_95 ((0x06f9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_96 ((0x0701 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_97 ((0x0709 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_98 ((0x0711 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_99 ((0x0719 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_100 ((0x0721 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_101 ((0x0729 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_102 ((0x0731 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_103 ((0x0739 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_104 ((0x0741 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_105 ((0x0749 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_106 ((0x0751 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_107 ((0x0759 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_108 ((0x0761 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_109 ((0x0769 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_110 ((0x0771 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_111 ((0x0779 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_112 ((0x0781 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_113 ((0x0789 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_114 ((0x0791 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_115 ((0x0799 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_116 ((0x07a1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_117 ((0x07a9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_118 ((0x07b1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_119 ((0x07b9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_120 ((0x07c1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_121 ((0x07c9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_122 ((0x07d1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_123 ((0x07d9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_124 ((0x07e1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_125 ((0x07e9 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_126 ((0x07f1 << 2) + 0xfe444000)
#define WCH_DEBUG_CHANNEL_127 ((0x07f9 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_0 ((0x0402 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_1 ((0x040a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_2 ((0x0412 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_3 ((0x041a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_4 ((0x0422 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_5 ((0x042a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_6 ((0x0432 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_7 ((0x043a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_8 ((0x0442 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_9 ((0x044a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_10 ((0x0452 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_11 ((0x045a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_12 ((0x0462 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_13 ((0x046a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_14 ((0x0472 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_15 ((0x047a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_16 ((0x0482 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_17 ((0x048a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_18 ((0x0492 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_19 ((0x049a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_20 ((0x04a2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_21 ((0x04aa << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_22 ((0x04b2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_23 ((0x04ba << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_24 ((0x04c2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_25 ((0x04ca << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_26 ((0x04d2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_27 ((0x04da << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_28 ((0x04e2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_29 ((0x04ea << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_30 ((0x04f2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_31 ((0x04fa << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_32 ((0x0502 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_33 ((0x050a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_34 ((0x0512 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_35 ((0x051a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_36 ((0x0522 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_37 ((0x052a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_38 ((0x0532 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_39 ((0x053a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_40 ((0x0542 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_41 ((0x054a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_42 ((0x0552 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_43 ((0x055a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_44 ((0x0562 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_45 ((0x056a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_46 ((0x0572 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_47 ((0x057a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_48 ((0x0582 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_49 ((0x058a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_50 ((0x0592 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_51 ((0x059a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_52 ((0x05a2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_53 ((0x05aa << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_54 ((0x05b2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_55 ((0x05ba << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_56 ((0x05c2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_57 ((0x05ca << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_58 ((0x05d2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_59 ((0x05da << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_60 ((0x05e2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_61 ((0x05ea << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_62 ((0x05f2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_63 ((0x05fa << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_64 ((0x0602 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_65 ((0x060a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_66 ((0x0612 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_67 ((0x061a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_68 ((0x0622 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_69 ((0x062a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_70 ((0x0632 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_71 ((0x063a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_72 ((0x0642 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_73 ((0x064a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_74 ((0x0652 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_75 ((0x065a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_76 ((0x0662 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_77 ((0x066a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_78 ((0x0672 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_79 ((0x067a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_80 ((0x0682 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_81 ((0x068a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_82 ((0x0692 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_83 ((0x069a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_84 ((0x06a2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_85 ((0x06aa << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_86 ((0x06b2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_87 ((0x06ba << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_88 ((0x06c2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_89 ((0x06ca << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_90 ((0x06d2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_91 ((0x06da << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_92 ((0x06e2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_93 ((0x06ea << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_94 ((0x06f2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_95 ((0x06fa << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_96 ((0x0702 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_97 ((0x070a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_98 ((0x0712 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_99 ((0x071a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_100 ((0x0722 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_101 ((0x072a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_102 ((0x0732 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_103 ((0x073a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_104 ((0x0742 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_105 ((0x074a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_106 ((0x0752 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_107 ((0x075a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_108 ((0x0762 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_109 ((0x076a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_110 ((0x0772 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_111 ((0x077a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_112 ((0x0782 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_113 ((0x078a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_114 ((0x0792 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_115 ((0x079a << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_116 ((0x07a2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_117 ((0x07aa << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_118 ((0x07b2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_119 ((0x07ba << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_120 ((0x07c2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_121 ((0x07ca << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_122 ((0x07d2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_123 ((0x07da << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_124 ((0x07e2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_125 ((0x07ea << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_126 ((0x07f2 << 2) + 0xfe444000)
#define WCH_CFG_CHANNEL_127 ((0x07fa << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_0 ((0x0403 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_1 ((0x040b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_2 ((0x0413 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_3 ((0x041b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_4 ((0x0423 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_5 ((0x042b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_6 ((0x0433 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_7 ((0x043b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_8 ((0x0443 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_9 ((0x044b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_10 ((0x0453 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_11 ((0x045b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_12 ((0x0463 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_13 ((0x046b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_14 ((0x0473 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_15 ((0x047b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_16 ((0x0483 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_17 ((0x048b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_18 ((0x0493 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_19 ((0x049b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_20 ((0x04a3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_21 ((0x04ab << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_22 ((0x04b3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_23 ((0x04bb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_24 ((0x04c3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_25 ((0x04cb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_26 ((0x04d3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_27 ((0x04db << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_28 ((0x04e3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_29 ((0x04eb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_30 ((0x04f3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_31 ((0x04fb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_32 ((0x0503 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_33 ((0x050b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_34 ((0x0513 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_35 ((0x051b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_36 ((0x0523 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_37 ((0x052b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_38 ((0x0533 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_39 ((0x053b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_40 ((0x0543 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_41 ((0x054b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_42 ((0x0553 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_43 ((0x055b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_44 ((0x0563 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_45 ((0x056b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_46 ((0x0573 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_47 ((0x057b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_48 ((0x0583 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_49 ((0x058b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_50 ((0x0593 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_51 ((0x059b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_52 ((0x05a3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_53 ((0x05ab << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_54 ((0x05b3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_55 ((0x05bb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_56 ((0x05c3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_57 ((0x05cb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_58 ((0x05d3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_59 ((0x05db << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_60 ((0x05e3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_61 ((0x05eb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_62 ((0x05f3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_63 ((0x05fb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_64 ((0x0603 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_65 ((0x060b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_66 ((0x0613 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_67 ((0x061b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_68 ((0x0623 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_69 ((0x062b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_70 ((0x0633 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_71 ((0x063b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_72 ((0x0643 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_73 ((0x064b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_74 ((0x0653 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_75 ((0x065b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_76 ((0x0663 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_77 ((0x066b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_78 ((0x0673 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_79 ((0x067b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_80 ((0x0683 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_81 ((0x068b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_82 ((0x0693 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_83 ((0x069b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_84 ((0x06a3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_85 ((0x06ab << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_86 ((0x06b3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_87 ((0x06bb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_88 ((0x06c3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_89 ((0x06cb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_90 ((0x06d3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_91 ((0x06db << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_92 ((0x06e3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_93 ((0x06eb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_94 ((0x06f3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_95 ((0x06fb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_96 ((0x0703 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_97 ((0x070b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_98 ((0x0713 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_99 ((0x071b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_100 ((0x0723 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_101 ((0x072b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_102 ((0x0733 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_103 ((0x073b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_104 ((0x0743 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_105 ((0x074b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_106 ((0x0753 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_107 ((0x075b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_108 ((0x0763 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_109 ((0x076b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_110 ((0x0773 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_111 ((0x077b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_112 ((0x0783 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_113 ((0x078b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_114 ((0x0793 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_115 ((0x079b << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_116 ((0x07a3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_117 ((0x07ab << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_118 ((0x07b3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_119 ((0x07bb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_120 ((0x07c3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_121 ((0x07cb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_122 ((0x07d3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_123 ((0x07db << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_124 ((0x07e3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_125 ((0x07eb << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_126 ((0x07f3 << 2) + 0xfe444000)
#define WCH_ADDR_CHANNEL_127 ((0x07fb << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_0 ((0x0404 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_1 ((0x040c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_2 ((0x0414 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_3 ((0x041c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_4 ((0x0424 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_5 ((0x042c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_6 ((0x0434 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_7 ((0x043c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_8 ((0x0444 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_9 ((0x044c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_10 ((0x0454 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_11 ((0x045c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_12 ((0x0464 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_13 ((0x046c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_14 ((0x0474 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_15 ((0x047c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_16 ((0x0484 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_17 ((0x048c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_18 ((0x0494 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_19 ((0x049c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_20 ((0x04a4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_21 ((0x04ac << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_22 ((0x04b4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_23 ((0x04bc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_24 ((0x04c4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_25 ((0x04cc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_26 ((0x04d4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_27 ((0x04dc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_28 ((0x04e4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_29 ((0x04ec << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_30 ((0x04f4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_31 ((0x04fc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_32 ((0x0504 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_33 ((0x050c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_34 ((0x0514 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_35 ((0x051c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_36 ((0x0524 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_37 ((0x052c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_38 ((0x0534 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_39 ((0x053c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_40 ((0x0544 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_41 ((0x054c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_42 ((0x0554 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_43 ((0x055c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_44 ((0x0564 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_45 ((0x056c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_46 ((0x0574 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_47 ((0x057c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_48 ((0x0584 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_49 ((0x058c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_50 ((0x0594 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_51 ((0x059c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_52 ((0x05a4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_53 ((0x05ac << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_54 ((0x05b4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_55 ((0x05bc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_56 ((0x05c4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_57 ((0x05cc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_58 ((0x05d4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_59 ((0x05dc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_60 ((0x05e4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_61 ((0x05ec << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_62 ((0x05f4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_63 ((0x05fc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_64 ((0x0604 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_65 ((0x060c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_66 ((0x0614 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_67 ((0x061c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_68 ((0x0624 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_69 ((0x062c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_70 ((0x0634 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_71 ((0x063c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_72 ((0x0644 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_73 ((0x064c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_74 ((0x0654 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_75 ((0x065c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_76 ((0x0664 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_77 ((0x066c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_78 ((0x0674 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_79 ((0x067c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_80 ((0x0684 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_81 ((0x068c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_82 ((0x0694 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_83 ((0x069c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_84 ((0x06a4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_85 ((0x06ac << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_86 ((0x06b4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_87 ((0x06bc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_88 ((0x06c4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_89 ((0x06cc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_90 ((0x06d4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_91 ((0x06dc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_92 ((0x06e4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_93 ((0x06ec << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_94 ((0x06f4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_95 ((0x06fc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_96 ((0x0704 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_97 ((0x070c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_98 ((0x0714 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_99 ((0x071c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_100 ((0x0724 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_101 ((0x072c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_102 ((0x0734 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_103 ((0x073c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_104 ((0x0744 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_105 ((0x074c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_106 ((0x0754 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_107 ((0x075c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_108 ((0x0764 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_109 ((0x076c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_110 ((0x0774 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_111 ((0x077c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_112 ((0x0784 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_113 ((0x078c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_114 ((0x0794 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_115 ((0x079c << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_116 ((0x07a4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_117 ((0x07ac << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_118 ((0x07b4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_119 ((0x07bc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_120 ((0x07c4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_121 ((0x07cc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_122 ((0x07d4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_123 ((0x07dc << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_124 ((0x07e4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_125 ((0x07ec << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_126 ((0x07f4 << 2) + 0xfe444000)
#define WCH_LEN_CHANNEL_127 ((0x07fc << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_0 ((0x0405 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_1 ((0x040d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_2 ((0x0415 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_3 ((0x041d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_4 ((0x0425 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_5 ((0x042d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_6 ((0x0435 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_7 ((0x043d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_8 ((0x0445 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_9 ((0x044d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_10 ((0x0455 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_11 ((0x045d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_12 ((0x0465 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_13 ((0x046d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_14 ((0x0475 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_15 ((0x047d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_16 ((0x0485 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_17 ((0x048d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_18 ((0x0495 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_19 ((0x049d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_20 ((0x04a5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_21 ((0x04ad << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_22 ((0x04b5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_23 ((0x04bd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_24 ((0x04c5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_25 ((0x04cd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_26 ((0x04d5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_27 ((0x04dd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_28 ((0x04e5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_29 ((0x04ed << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_30 ((0x04f5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_31 ((0x04fd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_32 ((0x0505 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_33 ((0x050d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_34 ((0x0515 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_35 ((0x051d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_36 ((0x0525 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_37 ((0x052d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_38 ((0x0535 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_39 ((0x053d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_40 ((0x0545 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_41 ((0x054d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_42 ((0x0555 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_43 ((0x055d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_44 ((0x0565 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_45 ((0x056d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_46 ((0x0575 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_47 ((0x057d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_48 ((0x0585 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_49 ((0x058d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_50 ((0x0595 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_51 ((0x059d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_52 ((0x05a5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_53 ((0x05ad << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_54 ((0x05b5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_55 ((0x05bd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_56 ((0x05c5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_57 ((0x05cd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_58 ((0x05d5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_59 ((0x05dd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_60 ((0x05e5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_61 ((0x05ed << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_62 ((0x05f5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_63 ((0x05fd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_64 ((0x0605 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_65 ((0x060d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_66 ((0x0615 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_67 ((0x061d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_68 ((0x0625 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_69 ((0x062d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_70 ((0x0635 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_71 ((0x063d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_72 ((0x0645 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_73 ((0x064d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_74 ((0x0655 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_75 ((0x065d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_76 ((0x0665 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_77 ((0x066d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_78 ((0x0675 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_79 ((0x067d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_80 ((0x0685 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_81 ((0x068d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_82 ((0x0695 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_83 ((0x069d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_84 ((0x06a5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_85 ((0x06ad << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_86 ((0x06b5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_87 ((0x06bd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_88 ((0x06c5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_89 ((0x06cd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_90 ((0x06d5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_91 ((0x06dd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_92 ((0x06e5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_93 ((0x06ed << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_94 ((0x06f5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_95 ((0x06fd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_96 ((0x0705 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_97 ((0x070d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_98 ((0x0715 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_99 ((0x071d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_100 ((0x0725 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_101 ((0x072d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_102 ((0x0735 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_103 ((0x073d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_104 ((0x0745 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_105 ((0x074d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_106 ((0x0755 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_107 ((0x075d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_108 ((0x0765 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_109 ((0x076d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_110 ((0x0775 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_111 ((0x077d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_112 ((0x0785 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_113 ((0x078d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_114 ((0x0795 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_115 ((0x079d << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_116 ((0x07a5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_117 ((0x07ad << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_118 ((0x07b5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_119 ((0x07bd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_120 ((0x07c5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_121 ((0x07cd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_122 ((0x07d5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_123 ((0x07dd << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_124 ((0x07e5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_125 ((0x07ed << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_126 ((0x07f5 << 2) + 0xfe444000)
#define WCH_WR_LEN_CHANNEL_127 ((0x07fd << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_0 ((0x0406 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_1 ((0x040e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_2 ((0x0416 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_3 ((0x041e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_4 ((0x0426 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_5 ((0x042e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_6 ((0x0436 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_7 ((0x043e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_8 ((0x0446 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_9 ((0x044e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_10 ((0x0456 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_11 ((0x045e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_12 ((0x0466 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_13 ((0x046e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_14 ((0x0476 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_15 ((0x047e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_16 ((0x0486 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_17 ((0x048e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_18 ((0x0496 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_19 ((0x049e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_20 ((0x04a6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_21 ((0x04ae << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_22 ((0x04b6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_23 ((0x04be << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_24 ((0x04c6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_25 ((0x04ce << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_26 ((0x04d6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_27 ((0x04de << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_28 ((0x04e6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_29 ((0x04ee << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_30 ((0x04f6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_31 ((0x04fe << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_32 ((0x0506 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_33 ((0x050e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_34 ((0x0516 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_35 ((0x051e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_36 ((0x0526 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_37 ((0x052e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_38 ((0x0536 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_39 ((0x053e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_40 ((0x0546 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_41 ((0x054e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_42 ((0x0556 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_43 ((0x055e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_44 ((0x0566 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_45 ((0x056e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_46 ((0x0576 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_47 ((0x057e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_48 ((0x0586 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_49 ((0x058e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_50 ((0x0596 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_51 ((0x059e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_52 ((0x05a6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_53 ((0x05ae << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_54 ((0x05b6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_55 ((0x05be << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_56 ((0x05c6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_57 ((0x05ce << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_58 ((0x05d6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_59 ((0x05de << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_60 ((0x05e6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_61 ((0x05ee << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_62 ((0x05f6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_63 ((0x05fe << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_64 ((0x0606 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_65 ((0x060e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_66 ((0x0616 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_67 ((0x061e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_68 ((0x0626 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_69 ((0x062e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_70 ((0x0636 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_71 ((0x063e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_72 ((0x0646 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_73 ((0x064e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_74 ((0x0656 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_75 ((0x065e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_76 ((0x0666 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_77 ((0x066e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_78 ((0x0676 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_79 ((0x067e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_80 ((0x0686 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_81 ((0x068e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_82 ((0x0696 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_83 ((0x069e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_84 ((0x06a6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_85 ((0x06ae << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_86 ((0x06b6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_87 ((0x06be << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_88 ((0x06c6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_89 ((0x06ce << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_90 ((0x06d6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_91 ((0x06de << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_92 ((0x06e6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_93 ((0x06ee << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_94 ((0x06f6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_95 ((0x06fe << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_96 ((0x0706 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_97 ((0x070e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_98 ((0x0716 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_99 ((0x071e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_100 ((0x0726 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_101 ((0x072e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_102 ((0x0736 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_103 ((0x073e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_104 ((0x0746 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_105 ((0x074e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_106 ((0x0756 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_107 ((0x075e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_108 ((0x0766 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_109 ((0x076e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_110 ((0x0776 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_111 ((0x077e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_112 ((0x0786 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_113 ((0x078e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_114 ((0x0796 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_115 ((0x079e << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_116 ((0x07a6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_117 ((0x07ae << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_118 ((0x07b6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_119 ((0x07be << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_120 ((0x07c6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_121 ((0x07ce << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_122 ((0x07d6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_123 ((0x07de << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_124 ((0x07e6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_125 ((0x07ee << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_126 ((0x07f6 << 2) + 0xfe444000)
#define WCH_PTR_CHANNEL_127 ((0x07fe << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_0 ((0x0407 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_1 ((0x040f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_2 ((0x0417 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_3 ((0x041f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_4 ((0x0427 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_5 ((0x042f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_6 ((0x0437 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_7 ((0x043f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_8 ((0x0447 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_9 ((0x044f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_10 ((0x0457 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_11 ((0x045f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_12 ((0x0467 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_13 ((0x046f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_14 ((0x0477 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_15 ((0x047f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_16 ((0x0487 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_17 ((0x048f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_18 ((0x0497 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_19 ((0x049f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_20 ((0x04a7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_21 ((0x04af << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_22 ((0x04b7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_23 ((0x04bf << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_24 ((0x04c7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_25 ((0x04cf << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_26 ((0x04d7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_27 ((0x04df << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_28 ((0x04e7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_29 ((0x04ef << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_30 ((0x04f7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_31 ((0x04ff << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_32 ((0x0507 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_33 ((0x050f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_34 ((0x0517 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_35 ((0x051f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_36 ((0x0527 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_37 ((0x052f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_38 ((0x0537 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_39 ((0x053f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_40 ((0x0547 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_41 ((0x054f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_42 ((0x0557 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_43 ((0x055f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_44 ((0x0567 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_45 ((0x056f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_46 ((0x0577 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_47 ((0x057f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_48 ((0x0587 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_49 ((0x058f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_50 ((0x0597 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_51 ((0x059f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_52 ((0x05a7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_53 ((0x05af << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_54 ((0x05b7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_55 ((0x05bf << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_56 ((0x05c7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_57 ((0x05cf << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_58 ((0x05d7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_59 ((0x05df << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_60 ((0x05e7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_61 ((0x05ef << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_62 ((0x05f7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_63 ((0x05ff << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_64 ((0x0607 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_65 ((0x060f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_66 ((0x0617 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_67 ((0x061f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_68 ((0x0627 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_69 ((0x062f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_70 ((0x0637 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_71 ((0x063f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_72 ((0x0647 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_73 ((0x064f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_74 ((0x0657 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_75 ((0x065f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_76 ((0x0667 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_77 ((0x066f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_78 ((0x0677 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_79 ((0x067f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_80 ((0x0687 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_81 ((0x068f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_82 ((0x0697 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_83 ((0x069f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_84 ((0x06a7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_85 ((0x06af << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_86 ((0x06b7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_87 ((0x06bf << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_88 ((0x06c7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_89 ((0x06cf << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_90 ((0x06d7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_91 ((0x06df << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_92 ((0x06e7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_93 ((0x06ef << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_94 ((0x06f7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_95 ((0x06ff << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_96 ((0x0707 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_97 ((0x070f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_98 ((0x0717 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_99 ((0x071f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_100 ((0x0727 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_101 ((0x072f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_102 ((0x0737 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_103 ((0x073f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_104 ((0x0747 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_105 ((0x074f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_106 ((0x0757 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_107 ((0x075f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_108 ((0x0767 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_109 ((0x076f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_110 ((0x0777 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_111 ((0x077f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_112 ((0x0787 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_113 ((0x078f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_114 ((0x0797 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_115 ((0x079f << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_116 ((0x07a7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_117 ((0x07af << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_118 ((0x07b7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_119 ((0x07bf << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_120 ((0x07c7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_121 ((0x07cf << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_122 ((0x07d7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_123 ((0x07df << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_124 ((0x07e7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_125 ((0x07ef << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_126 ((0x07f7 << 2) + 0xfe444000)
#define WCMD_CNT_CHANNEL_127 ((0x07ff << 2) + 0xfe444000)
#define DMX_RDMA_INT_MASK ((0x0800 << 2) + 0xfe444000)
#define DMX_WDMA_INT_MASK_0 ((0x0801 << 2) + 0xfe444000)
#define DMX_WDMA_INT_MASK_1 ((0x0802 << 2) + 0xfe444000)
#define DMX_WDMA_INT_MASK_2 ((0x0803 << 2) + 0xfe444000)
#define DMX_WDMA_INT_MASK_3 ((0x0804 << 2) + 0xfe444000)
#define DMX_CLEAN_W_BATCH_0 ((0x0805 << 2) + 0xfe444000)
#define DMX_CLEAN_W_BATCH_1 ((0x0806 << 2) + 0xfe444000)
#define DMX_CLEAN_W_BATCH_2 ((0x0807 << 2) + 0xfe444000)
#define DMX_CLEAN_W_BATCH_3 ((0x0808 << 2) + 0xfe444000)
#define DMX_CLEAN_RDMA ((0x0809 << 2) + 0xfe444000)
#define DMX_CLEAN_WDMA_0 ((0x080a << 2) + 0xfe444000)
#define DMX_CLEAN_WDMA_1 ((0x080b << 2) + 0xfe444000)
#define DMX_CLEAN_WDMA_2 ((0x080c << 2) + 0xfe444000)
#define DMX_CLEAN_WDMA_3 ((0x080d << 2) + 0xfe444000)
#define DMX_RDMA_ACTIVE ((0x080e << 2) + 0xfe444000)
#define DMX_WDMA_ACTIVE_0 ((0x080f << 2) + 0xfe444000)
#define DMX_WDMA_ACTIVE_1 ((0x0810 << 2) + 0xfe444000)
#define DMX_WDMA_ACTIVE_2 ((0x0811 << 2) + 0xfe444000)
#define DMX_WDMA_ACTIVE_3 ((0x0812 << 2) + 0xfe444000)
#define DMX_DMA_RDONE ((0x0813 << 2) + 0xfe444000)
#define DMX_DMA_WDONE_0 ((0x0814 << 2) + 0xfe444000)
#define DMX_DMA_WDONE_1 ((0x0815 << 2) + 0xfe444000)
#define DMX_DMA_WDONE_2 ((0x0816 << 2) + 0xfe444000)
#define DMX_DMA_WDONE_3 ((0x0817 << 2) + 0xfe444000)
#define DMX_RDES_ERR ((0x0818 << 2) + 0xfe444000)
#define DMX_RDES_LEN_ERR ((0x0819 << 2) + 0xfe444000)
#define DMX_WDES_ERR_0 ((0x081a << 2) + 0xfe444000)
#define DMX_WDES_ERR_1 ((0x081b << 2) + 0xfe444000)
#define DMX_WDES_ERR_2 ((0x081c << 2) + 0xfe444000)
#define DMX_WDES_ERR_3 ((0x081d << 2) + 0xfe444000)
#define DMX_DMA_BATCH_END_0 ((0x081e << 2) + 0xfe444000)
#define DMX_DMA_BATCH_END_1 ((0x081f << 2) + 0xfe444000)
#define DMX_DMA_BATCH_END_2 ((0x0820 << 2) + 0xfe444000)
#define DMX_DMA_BATCH_END_3 ((0x0821 << 2) + 0xfe444000)
#define DMX_WDES_EOC_DONE_0 ((0x0822 << 2) + 0xfe444000)
#define DMX_WDES_EOC_DONE_1 ((0x0823 << 2) + 0xfe444000)
#define DMX_WDES_EOC_DONE_2 ((0x0824 << 2) + 0xfe444000)
#define DMX_WDES_EOC_DONE_3 ((0x0825 << 2) + 0xfe444000)
#define DMX_WCH_RESP_ERR0 ((0x0826 << 2) + 0xfe444000)
#define DMX_WCH_RESP_ERR1 ((0x0827 << 2) + 0xfe444000)
#define DMX_WCH_RESP_ERR2 ((0x0828 << 2) + 0xfe444000)
#define DMX_WCH_RESP_ERR3 ((0x0829 << 2) + 0xfe444000)
#define DMX_UPDT_PKT_SYNC ((0x0830 << 2) + 0xfe444000)
#define DMX_RCHN_CFG ((0x0831 << 2) + 0xfe444000)
#define DMX_WCHN_CFG ((0x0832 << 2) + 0xfe444000)
#define DMX_MEM_PD_CRTL ((0x0833 << 2) + 0xfe444000)
#define DMX_DMA_BUS_CFG ((0x0834 << 2) + 0xfe444000)
#define DMX_DMA_GMW_CFG ((0x0835 << 2) + 0xfe444000)
#define DMX_DMA_GMR_CFG ((0x0836 << 2) + 0xfe444000)
//========================================================================
//  TS OUTPUT REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe442c00
// -----------------------------------------------
#define TS_OUTPUT_PID_RDY ((0x0000 << 2) + 0xfe442c00)
#define TS_OUTPUT_TEE_LOCK ((0x0001 << 2) + 0xfe442c00)
#define TS_OUTPUT_PID_CFG ((0x0002 << 2) + 0xfe442c00)
#define TS_OUTPUT_PID_DAT ((0x0003 << 2) + 0xfe442c00)
#define TS_OUTPUT_OUT_CFG ((0x0004 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_0 ((0x0010 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_1 ((0x0011 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_2 ((0x0012 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_3 ((0x0013 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_4 ((0x0014 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_5 ((0x0015 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_6 ((0x0016 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_7 ((0x0017 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_8 ((0x0018 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_9 ((0x0019 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_10 ((0x001a << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_11 ((0x001b << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_12 ((0x001c << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_13 ((0x001d << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_14 ((0x001e << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_TAB_ENTRY_15 ((0x001f << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_0_1 ((0x0020 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_2_3 ((0x0021 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_4_5 ((0x0022 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_6_7 ((0x0023 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_8_9 ((0x0024 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_10_11 ((0x0025 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_12_13 ((0x0026 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_14_15 ((0x0027 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_16_17 ((0x0028 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_18_19 ((0x0029 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_20_21 ((0x002a << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_22_23 ((0x002b << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_24_25 ((0x002c << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_26_27 ((0x002d << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_28_29 ((0x002e << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_30_31 ((0x002f << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_32_33 ((0x0030 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_34_35 ((0x0031 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_36_37 ((0x0032 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_38_39 ((0x0033 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_40_41 ((0x0034 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_42_43 ((0x0035 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_44_45 ((0x0036 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_46_47 ((0x0037 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_48_49 ((0x0038 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_50_51 ((0x0039 << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_52_53 ((0x003a << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_54_55 ((0x003b << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_56_57 ((0x003c << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_58_59 ((0x003d << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_60_61 ((0x003e << 2) + 0xfe442c00)
#define TS_OUTPUT_SID_TAB_62_63 ((0x003f << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_0 ((0x0040 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_1 ((0x0041 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_2 ((0x0042 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_3 ((0x0043 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_4 ((0x0044 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_5 ((0x0045 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_6 ((0x0046 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_7 ((0x0047 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_8 ((0x0048 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_9 ((0x0049 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_10 ((0x004a << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_11 ((0x004b << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_12 ((0x004c << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_13 ((0x004d << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_14 ((0x004e << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_15 ((0x004f << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_16 ((0x0050 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_17 ((0x0051 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_18 ((0x0052 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_19 ((0x0053 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_20 ((0x0054 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_21 ((0x0055 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_22 ((0x0056 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_23 ((0x0057 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_24 ((0x0058 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_25 ((0x0059 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_26 ((0x005a << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_27 ((0x005b << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_28 ((0x005c << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_29 ((0x005d << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_30 ((0x005e << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_31 ((0x005f << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_32 ((0x0060 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_33 ((0x0061 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_34 ((0x0062 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_35 ((0x0063 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_36 ((0x0064 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_37 ((0x0065 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_38 ((0x0066 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_39 ((0x0067 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_40 ((0x0068 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_41 ((0x0069 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_42 ((0x006a << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_43 ((0x006b << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_44 ((0x006c << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_45 ((0x006d << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_46 ((0x006e << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_47 ((0x006f << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_48 ((0x0070 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_49 ((0x0071 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_50 ((0x0072 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_51 ((0x0073 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_52 ((0x0074 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_53 ((0x0075 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_54 ((0x0076 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_55 ((0x0077 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_56 ((0x0078 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_57 ((0x0079 << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_58 ((0x007a << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_59 ((0x007b << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_60 ((0x007c << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_61 ((0x007d << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_62 ((0x007e << 2) + 0xfe442c00)
#define TS_OUTPUT_ES_TAB_63 ((0x007f << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_0 ((0x0080 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_0 ((0x0081 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_1 ((0x0082 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_1 ((0x0083 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_2 ((0x0084 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_2 ((0x0085 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_3 ((0x0086 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_3 ((0x0087 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_4 ((0x0088 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_4 ((0x0089 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_5 ((0x008a << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_5 ((0x008b << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_6 ((0x008c << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_6 ((0x008d << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_7 ((0x008e << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_7 ((0x008f << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_8 ((0x0090 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_8 ((0x0091 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_9 ((0x0092 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_9 ((0x0093 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_10 ((0x0094 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_10 ((0x0095 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_11 ((0x0096 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_11 ((0x0097 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_12 ((0x0098 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_12 ((0x0099 << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_13 ((0x009a << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_13 ((0x009b << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_14 ((0x009c << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_14 ((0x009d << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_LSB_15 ((0x009e << 2) + 0xfe442c00)
#define TS_OUTPUT_PCR_REG_MSB_15 ((0x009f << 2) + 0xfe442c00)
//========================================================================
//  TSD DESC AES REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe442000
// -----------------------------------------------
#define TSD_PID_RDY ((0x0000 << 2) + 0xfe442000)
#define TSD_TEE_LOCK ((0x0001 << 2) + 0xfe442000)
#define TSD_PID_STS ((0x0003 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_0 ((0x0004 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_0 ((0x0005 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_1 ((0x0006 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_1 ((0x0007 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_2 ((0x0008 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_2 ((0x0009 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_3 ((0x000a << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_3 ((0x000b << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_4 ((0x000c << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_4 ((0x000d << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_5 ((0x000e << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_5 ((0x000f << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_6 ((0x0010 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_6 ((0x0011 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_7 ((0x0012 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_7 ((0x0013 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_8 ((0x0014 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_8 ((0x0015 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_9 ((0x0016 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_9 ((0x0017 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_10 ((0x0018 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_10 ((0x0019 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_11 ((0x001a << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_11 ((0x001b << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_12 ((0x001c << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_12 ((0x001d << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_13 ((0x001e << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_13 ((0x001f << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_14 ((0x0020 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_14 ((0x0021 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_15 ((0x0022 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_15 ((0x0023 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_16 ((0x0024 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_16 ((0x0025 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_17 ((0x0026 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_17 ((0x0027 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_18 ((0x0028 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_18 ((0x0029 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_19 ((0x002a << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_19 ((0x002b << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_20 ((0x002c << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_20 ((0x002d << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_21 ((0x002e << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_21 ((0x002f << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_22 ((0x0030 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_22 ((0x0031 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_23 ((0x0032 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_23 ((0x0033 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_24 ((0x0034 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_24 ((0x0035 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_25 ((0x0036 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_25 ((0x0037 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_26 ((0x0038 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_26 ((0x0039 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_27 ((0x003a << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_27 ((0x003b << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_28 ((0x003c << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_28 ((0x003d << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_29 ((0x003e << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_29 ((0x003f << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_30 ((0x0040 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_30 ((0x0041 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_31 ((0x0042 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_31 ((0x0043 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_32 ((0x0044 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_32 ((0x0045 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_33 ((0x0046 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_33 ((0x0047 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_34 ((0x0048 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_34 ((0x0049 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_35 ((0x004a << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_35 ((0x004b << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_36 ((0x004c << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_36 ((0x004d << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_37 ((0x004e << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_37 ((0x004f << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_38 ((0x0050 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_38 ((0x0051 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_39 ((0x0052 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_39 ((0x0053 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_40 ((0x0054 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_40 ((0x0055 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_41 ((0x0056 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_41 ((0x0057 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_42 ((0x0058 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_42 ((0x0059 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_43 ((0x005a << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_43 ((0x005b << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_44 ((0x005c << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_44 ((0x005d << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_45 ((0x005e << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_45 ((0x005f << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_46 ((0x0060 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_46 ((0x0061 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_47 ((0x0062 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_47 ((0x0063 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_48 ((0x0064 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_48 ((0x0065 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_49 ((0x0066 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_49 ((0x0067 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_50 ((0x0068 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_50 ((0x0069 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_51 ((0x006a << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_51 ((0x006b << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_52 ((0x006c << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_52 ((0x006d << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_53 ((0x006e << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_53 ((0x006f << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_54 ((0x0070 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_54 ((0x0071 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_55 ((0x0072 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_55 ((0x0073 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_56 ((0x0074 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_56 ((0x0075 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_57 ((0x0076 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_57 ((0x0077 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_58 ((0x0078 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_58 ((0x0079 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_59 ((0x007a << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_59 ((0x007b << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_60 ((0x007c << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_60 ((0x007d << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_61 ((0x007e << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_61 ((0x007f << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_62 ((0x0080 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_62 ((0x0081 << 2) + 0xfe442000)
#define TSD_PID_TABLE_LSB_63 ((0x0082 << 2) + 0xfe442000)
#define TSD_PID_TABLE_MSB_63 ((0x0083 << 2) + 0xfe442000)
//========================================================================
// SECURE TOP REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440300
// -----------------------------------------------
#define SEC_TOP_CFG_LOCKABLE ((0x0000 << 2) + 0xfe440300)
#define SEC_TOP_CFG_LOCK ((0x0001 << 2) + 0xfe440300)
#define SEC_TOP_CFG_WTO ((0x0002 << 2) + 0xfe440300)
#define SEC_TOP_N2_GENOUT ((0x0003 << 2) + 0xfe440300)
#define SEC_TOP_CFG_REG ((0x0004 << 2) + 0xfe440300)
#define SEC_TOP_NSK_CTRL ((0x0005 << 2) + 0xfe440300)
#define SEC_TOP_AKL_STS ((0x0006 << 2) + 0xfe440300)
#define SEC_TOP_ND_STATUS ((0x0007 << 2) + 0xfe440300)
#define SEC_TOP_CFG_DEMUX ((0x0008 << 2) + 0xfe440300)
#define SEC_TOP_CFG_DIF ((0x000c << 2) + 0xfe440300)
#define SEC_TOP_NSK_HASH0 ((0x0010 << 2) + 0xfe440300)
#define SEC_TOP_NSK_HASH1 ((0x0011 << 2) + 0xfe440300)
#define SEC_TOP_NSK_HASH2 ((0x0012 << 2) + 0xfe440300)
#define SEC_TOP_NSK_HASH3 ((0x0013 << 2) + 0xfe440300)
#define SEC_TOP_PATH0_CTRL ((0x0028 << 2) + 0xfe440300)
#define SEC_TOP_PATH1_CTRL ((0x0029 << 2) + 0xfe440300)
#define SEC_TOP_PATH2_CTRL ((0x002a << 2) + 0xfe440300)
#define SEC_TOP_PATH3_CTRL ((0x002b << 2) + 0xfe440300)
#define SEC_TOP_DEMOD_PKT_CFG0 ((0x002c << 2) + 0xfe440300)
#define SEC_TOP_DEMOD_PKT_CFG1 ((0x002d << 2) + 0xfe440300)
#define SEC_TOP_DEMOD_PKT_CFG2 ((0x002e << 2) + 0xfe440300)
#define SEC_TOP_DEMOD_PKT_CFG3 ((0x002f << 2) + 0xfe440300)
#define SEC_TOP_DEMOD_FIFO_CFG0 ((0x0030 << 2) + 0xfe440300)
#define SEC_TOP_DEMOD_FIFO_CFG1 ((0x0031 << 2) + 0xfe440300)
#define SEC_TOP_TS_O_PATH_CTRL ((0x0032 << 2) + 0xfe440300)
#define SEC_TOP_CLEAN_DEMOD_INT ((0x0033 << 2) + 0xfe440300)
#define SEC_TOP_DEMOD_INT_MASK ((0x0034 << 2) + 0xfe440300)
#define SEC_TOP_DEMOD_INT_STATUS ((0x0035 << 2) + 0xfe440300)
#define SEC_TOP_TS_CHN0_ERR_STATUS ((0x0036 << 2) + 0xfe440300)
#define SEC_TOP_TS_CHN1_ERR_STATUS ((0x0037 << 2) + 0xfe440300)
#define SEC_TOP_TS_CHN2_ERR_STATUS ((0x0038 << 2) + 0xfe440300)
#define SEC_TOP_TS_CHN3_ERR_STATUS ((0x0039 << 2) + 0xfe440300)
//========================================================================
// TSE DESC AES REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe442800
// -----------------------------------------------
#define TSE_PID_RDY ((0x0000 << 2) + 0xfe442800)
#define TSE_TEE_LOCK ((0x0001 << 2) + 0xfe442800)
#define TSE_PID_STS ((0x0003 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_0 ((0x0004 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_0 ((0x0005 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_1 ((0x0006 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_1 ((0x0007 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_2 ((0x0008 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_2 ((0x0009 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_3 ((0x000a << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_3 ((0x000b << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_4 ((0x000c << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_4 ((0x000d << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_5 ((0x000e << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_5 ((0x000f << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_6 ((0x0010 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_6 ((0x0011 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_7 ((0x0012 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_7 ((0x0013 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_8 ((0x0014 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_8 ((0x0015 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_9 ((0x0016 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_9 ((0x0017 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_10 ((0x0018 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_10 ((0x0019 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_11 ((0x001a << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_11 ((0x001b << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_12 ((0x001c << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_12 ((0x001d << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_13 ((0x001e << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_13 ((0x001f << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_14 ((0x0020 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_14 ((0x0021 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_15 ((0x0022 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_15 ((0x0023 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_16 ((0x0024 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_16 ((0x0025 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_17 ((0x0026 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_17 ((0x0027 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_18 ((0x0028 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_18 ((0x0029 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_19 ((0x002a << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_19 ((0x002b << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_20 ((0x002c << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_20 ((0x002d << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_21 ((0x002e << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_21 ((0x002f << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_22 ((0x0030 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_22 ((0x0031 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_23 ((0x0032 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_23 ((0x0033 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_24 ((0x0034 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_24 ((0x0035 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_25 ((0x0036 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_25 ((0x0037 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_26 ((0x0038 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_26 ((0x0039 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_27 ((0x003a << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_27 ((0x003b << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_28 ((0x003c << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_28 ((0x003d << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_29 ((0x003e << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_29 ((0x003f << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_30 ((0x0040 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_30 ((0x0041 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_31 ((0x0042 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_31 ((0x0043 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_32 ((0x0044 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_32 ((0x0045 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_33 ((0x0046 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_33 ((0x0047 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_34 ((0x0048 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_34 ((0x0049 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_35 ((0x004a << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_35 ((0x004b << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_36 ((0x004c << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_36 ((0x004d << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_37 ((0x004e << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_37 ((0x004f << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_38 ((0x0050 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_38 ((0x0051 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_39 ((0x0052 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_39 ((0x0053 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_40 ((0x0054 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_40 ((0x0055 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_41 ((0x0056 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_41 ((0x0057 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_42 ((0x0058 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_42 ((0x0059 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_43 ((0x005a << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_43 ((0x005b << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_44 ((0x005c << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_44 ((0x005d << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_45 ((0x005e << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_45 ((0x005f << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_46 ((0x0060 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_46 ((0x0061 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_47 ((0x0062 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_47 ((0x0063 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_48 ((0x0064 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_48 ((0x0065 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_49 ((0x0066 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_49 ((0x0067 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_50 ((0x0068 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_50 ((0x0069 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_51 ((0x006a << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_51 ((0x006b << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_52 ((0x006c << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_52 ((0x006d << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_53 ((0x006e << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_53 ((0x006f << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_54 ((0x0070 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_54 ((0x0071 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_55 ((0x0072 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_55 ((0x0073 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_56 ((0x0074 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_56 ((0x0075 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_57 ((0x0076 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_57 ((0x0077 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_58 ((0x0078 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_58 ((0x0079 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_59 ((0x007a << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_59 ((0x007b << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_60 ((0x007c << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_60 ((0x007d << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_61 ((0x007e << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_61 ((0x007f << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_62 ((0x0080 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_62 ((0x0081 << 2) + 0xfe442800)
#define TSE_PID_TABLE_LSB_63 ((0x0082 << 2) + 0xfe442800)
#define TSE_PID_TABLE_MSB_63 ((0x0083 << 2) + 0xfe442800)
//========================================================================
// TSN DESC REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe442400
// -----------------------------------------------
#define TSN_PID_RDY ((0x0000 << 2) + 0xfe442400)
#define TSN_TEE_LOCK ((0x0001 << 2) + 0xfe442400)
#define TSN_PID_STS ((0x0003 << 2) + 0xfe442400)
#define TSN_PID_TABLE_0 ((0x0004 << 2) + 0xfe442400)
#define TSN_PID_TABLE_1 ((0x0005 << 2) + 0xfe442400)
#define TSN_PID_TABLE_2 ((0x0006 << 2) + 0xfe442400)
#define TSN_PID_TABLE_3 ((0x0007 << 2) + 0xfe442400)
#define TSN_PID_TABLE_4 ((0x0008 << 2) + 0xfe442400)
#define TSN_PID_TABLE_5 ((0x0009 << 2) + 0xfe442400)
#define TSN_PID_TABLE_6 ((0x000a << 2) + 0xfe442400)
#define TSN_PID_TABLE_7 ((0x000b << 2) + 0xfe442400)
#define TSN_PID_TABLE_8 ((0x000c << 2) + 0xfe442400)
#define TSN_PID_TABLE_9 ((0x000d << 2) + 0xfe442400)
#define TSN_PID_TABLE_10 ((0x000e << 2) + 0xfe442400)
#define TSN_PID_TABLE_11 ((0x000f << 2) + 0xfe442400)
#define TSN_PID_TABLE_12 ((0x0010 << 2) + 0xfe442400)
#define TSN_PID_TABLE_13 ((0x0011 << 2) + 0xfe442400)
#define TSN_PID_TABLE_14 ((0x0012 << 2) + 0xfe442400)
#define TSN_PID_TABLE_15 ((0x0013 << 2) + 0xfe442400)
#define TSN_PID_TABLE_16 ((0x0014 << 2) + 0xfe442400)
#define TSN_PID_TABLE_17 ((0x0015 << 2) + 0xfe442400)
#define TSN_PID_TABLE_18 ((0x0016 << 2) + 0xfe442400)
#define TSN_PID_TABLE_19 ((0x0017 << 2) + 0xfe442400)
#define TSN_PID_TABLE_20 ((0x0018 << 2) + 0xfe442400)
#define TSN_PID_TABLE_21 ((0x0019 << 2) + 0xfe442400)
#define TSN_PID_TABLE_22 ((0x001a << 2) + 0xfe442400)
#define TSN_PID_TABLE_23 ((0x001b << 2) + 0xfe442400)
#define TSN_PID_TABLE_24 ((0x001c << 2) + 0xfe442400)
#define TSN_PID_TABLE_25 ((0x001d << 2) + 0xfe442400)
#define TSN_PID_TABLE_26 ((0x001e << 2) + 0xfe442400)
#define TSN_PID_TABLE_27 ((0x001f << 2) + 0xfe442400)
#define TSN_PID_TABLE_28 ((0x0020 << 2) + 0xfe442400)
#define TSN_PID_TABLE_29 ((0x0021 << 2) + 0xfe442400)
#define TSN_PID_TABLE_30 ((0x0022 << 2) + 0xfe442400)
#define TSN_PID_TABLE_31 ((0x0023 << 2) + 0xfe442400)
#define TSN_PID_TABLE_32 ((0x0024 << 2) + 0xfe442400)
#define TSN_PID_TABLE_33 ((0x0025 << 2) + 0xfe442400)
#define TSN_PID_TABLE_34 ((0x0026 << 2) + 0xfe442400)
#define TSN_PID_TABLE_35 ((0x0027 << 2) + 0xfe442400)
#define TSN_PID_TABLE_36 ((0x0028 << 2) + 0xfe442400)
#define TSN_PID_TABLE_37 ((0x0029 << 2) + 0xfe442400)
#define TSN_PID_TABLE_38 ((0x002a << 2) + 0xfe442400)
#define TSN_PID_TABLE_39 ((0x002b << 2) + 0xfe442400)
#define TSN_PID_TABLE_40 ((0x002c << 2) + 0xfe442400)
#define TSN_PID_TABLE_41 ((0x002d << 2) + 0xfe442400)
#define TSN_PID_TABLE_42 ((0x002e << 2) + 0xfe442400)
#define TSN_PID_TABLE_43 ((0x002f << 2) + 0xfe442400)
#define TSN_PID_TABLE_44 ((0x0030 << 2) + 0xfe442400)
#define TSN_PID_TABLE_45 ((0x0031 << 2) + 0xfe442400)
#define TSN_PID_TABLE_46 ((0x0032 << 2) + 0xfe442400)
#define TSN_PID_TABLE_47 ((0x0033 << 2) + 0xfe442400)
#define TSN_PID_TABLE_48 ((0x0034 << 2) + 0xfe442400)
#define TSN_PID_TABLE_49 ((0x0035 << 2) + 0xfe442400)
#define TSN_PID_TABLE_50 ((0x0036 << 2) + 0xfe442400)
#define TSN_PID_TABLE_51 ((0x0037 << 2) + 0xfe442400)
#define TSN_PID_TABLE_52 ((0x0038 << 2) + 0xfe442400)
#define TSN_PID_TABLE_53 ((0x0039 << 2) + 0xfe442400)
#define TSN_PID_TABLE_54 ((0x003a << 2) + 0xfe442400)
#define TSN_PID_TABLE_55 ((0x003b << 2) + 0xfe442400)
#define TSN_PID_TABLE_56 ((0x003c << 2) + 0xfe442400)
#define TSN_PID_TABLE_57 ((0x003d << 2) + 0xfe442400)
#define TSN_PID_TABLE_58 ((0x003e << 2) + 0xfe442400)
#define TSN_PID_TABLE_59 ((0x003f << 2) + 0xfe442400)
#define TSN_PID_TABLE_60 ((0x0040 << 2) + 0xfe442400)
#define TSN_PID_TABLE_61 ((0x0041 << 2) + 0xfe442400)
#define TSN_PID_TABLE_62 ((0x0042 << 2) + 0xfe442400)
#define TSN_PID_TABLE_63 ((0x0043 << 2) + 0xfe442400)
#define TSN_PID_TABLE_64 ((0x0044 << 2) + 0xfe442400)
#define TSN_PID_TABLE_65 ((0x0045 << 2) + 0xfe442400)
#define TSN_PID_TABLE_66 ((0x0046 << 2) + 0xfe442400)
#define TSN_PID_TABLE_67 ((0x0047 << 2) + 0xfe442400)
#define TSN_PID_TABLE_68 ((0x0048 << 2) + 0xfe442400)
#define TSN_PID_TABLE_69 ((0x0049 << 2) + 0xfe442400)
#define TSN_PID_TABLE_70 ((0x004a << 2) + 0xfe442400)
#define TSN_PID_TABLE_71 ((0x004b << 2) + 0xfe442400)
#define TSN_PID_TABLE_72 ((0x004c << 2) + 0xfe442400)
#define TSN_PID_TABLE_73 ((0x004d << 2) + 0xfe442400)
#define TSN_PID_TABLE_74 ((0x004e << 2) + 0xfe442400)
#define TSN_PID_TABLE_75 ((0x004f << 2) + 0xfe442400)
#define TSN_PID_TABLE_76 ((0x0050 << 2) + 0xfe442400)
#define TSN_PID_TABLE_77 ((0x0051 << 2) + 0xfe442400)
#define TSN_PID_TABLE_78 ((0x0052 << 2) + 0xfe442400)
#define TSN_PID_TABLE_79 ((0x0053 << 2) + 0xfe442400)
#define TSN_PID_TABLE_80 ((0x0054 << 2) + 0xfe442400)
#define TSN_PID_TABLE_81 ((0x0055 << 2) + 0xfe442400)
#define TSN_PID_TABLE_82 ((0x0056 << 2) + 0xfe442400)
#define TSN_PID_TABLE_83 ((0x0057 << 2) + 0xfe442400)
#define TSN_PID_TABLE_84 ((0x0058 << 2) + 0xfe442400)
#define TSN_PID_TABLE_85 ((0x0059 << 2) + 0xfe442400)
#define TSN_PID_TABLE_86 ((0x005a << 2) + 0xfe442400)
#define TSN_PID_TABLE_87 ((0x005b << 2) + 0xfe442400)
#define TSN_PID_TABLE_88 ((0x005c << 2) + 0xfe442400)
#define TSN_PID_TABLE_89 ((0x005d << 2) + 0xfe442400)
#define TSN_PID_TABLE_90 ((0x005e << 2) + 0xfe442400)
#define TSN_PID_TABLE_91 ((0x005f << 2) + 0xfe442400)
#define TSN_PID_TABLE_92 ((0x0060 << 2) + 0xfe442400)
#define TSN_PID_TABLE_93 ((0x0061 << 2) + 0xfe442400)
#define TSN_PID_TABLE_94 ((0x0062 << 2) + 0xfe442400)
#define TSN_PID_TABLE_95 ((0x0063 << 2) + 0xfe442400)
#define TSN_PID_TABLE_96 ((0x0064 << 2) + 0xfe442400)
#define TSN_PID_TABLE_97 ((0x0065 << 2) + 0xfe442400)
#define TSN_PID_TABLE_98 ((0x0066 << 2) + 0xfe442400)
#define TSN_PID_TABLE_99 ((0x0067 << 2) + 0xfe442400)
#define TSN_PID_TABLE_100 ((0x0068 << 2) + 0xfe442400)
#define TSN_PID_TABLE_101 ((0x0069 << 2) + 0xfe442400)
#define TSN_PID_TABLE_102 ((0x006a << 2) + 0xfe442400)
#define TSN_PID_TABLE_103 ((0x006b << 2) + 0xfe442400)
#define TSN_PID_TABLE_104 ((0x006c << 2) + 0xfe442400)
#define TSN_PID_TABLE_105 ((0x006d << 2) + 0xfe442400)
#define TSN_PID_TABLE_106 ((0x006e << 2) + 0xfe442400)
#define TSN_PID_TABLE_107 ((0x006f << 2) + 0xfe442400)
#define TSN_PID_TABLE_108 ((0x0070 << 2) + 0xfe442400)
#define TSN_PID_TABLE_109 ((0x0071 << 2) + 0xfe442400)
#define TSN_PID_TABLE_110 ((0x0072 << 2) + 0xfe442400)
#define TSN_PID_TABLE_111 ((0x0073 << 2) + 0xfe442400)
#define TSN_PID_TABLE_112 ((0x0074 << 2) + 0xfe442400)
#define TSN_PID_TABLE_113 ((0x0075 << 2) + 0xfe442400)
#define TSN_PID_TABLE_114 ((0x0076 << 2) + 0xfe442400)
#define TSN_PID_TABLE_115 ((0x0077 << 2) + 0xfe442400)
#define TSN_PID_TABLE_116 ((0x0078 << 2) + 0xfe442400)
#define TSN_PID_TABLE_117 ((0x0079 << 2) + 0xfe442400)
#define TSN_PID_TABLE_118 ((0x007a << 2) + 0xfe442400)
#define TSN_PID_TABLE_119 ((0x007b << 2) + 0xfe442400)
#define TSN_PID_TABLE_120 ((0x007c << 2) + 0xfe442400)
#define TSN_PID_TABLE_121 ((0x007d << 2) + 0xfe442400)
#define TSN_PID_TABLE_122 ((0x007e << 2) + 0xfe442400)
#define TSN_PID_TABLE_123 ((0x007f << 2) + 0xfe442400)
#define TSN_PID_TABLE_124 ((0x0080 << 2) + 0xfe442400)
#define TSN_PID_TABLE_125 ((0x0081 << 2) + 0xfe442400)
#define TSN_PID_TABLE_126 ((0x0082 << 2) + 0xfe442400)
#define TSN_PID_TABLE_127 ((0x0083 << 2) + 0xfe442400)
//========================================================================
// RNG REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440700
// -----------------------------------------------
#define RNG_TEE_READY ((0x0000 << 2) + 0xfe440700)
#define RNG_TEE_LOCK ((0x0001 << 2) + 0xfe440700)
#define RNG_TEE_CFG ((0x0002 << 2) + 0xfe440700)
#define RNG_TEE_NIST_OUT ((0x0003 << 2) + 0xfe440700)
#define RNG_TEE_OUT0 ((0x0004 << 2) + 0xfe440700)
#define RNG_TEE_OUT1 ((0x0005 << 2) + 0xfe440700)
#define RNG_TEE_OUT2 ((0x0006 << 2) + 0xfe440700)
#define RNG_TEE_OUT3 ((0x0007 << 2) + 0xfe440700)
#define RNG_CFG_RING ((0x0010 << 2) + 0xfe440700)
#define RNG_CFG_RESEED ((0x0011 << 2) + 0xfe440700)
#define RNG_CFG_HEALTH ((0x0012 << 2) + 0xfe440700)
#define RNG_CFG_MISC ((0x0013 << 2) + 0xfe440700)
#define RNG_REE_READY ((0x0020 << 2) + 0xfe440700)
#define RNG_REE_DEBUG ((0x0021 << 2) + 0xfe440700)
#define RNG_REE_CFG ((0x0022 << 2) + 0xfe440700)
#define RNG_REE_OUT0 ((0x0024 << 2) + 0xfe440700)
#define RNG_REE_OUT1 ((0x0025 << 2) + 0xfe440700)
#define RNG_REE_OUT2 ((0x0026 << 2) + 0xfe440700)
#define RNG_REE_OUT3 ((0x0027 << 2) + 0xfe440700)
//========================================================================
// OTP REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440000
// -----------------------------------------------
#define OTP_TEE_RDY ((0x0000 << 2) + 0xfe440000)
#define OTP_TEE_DEBUG ((0x0001 << 2) + 0xfe440000)
#define OTP_TEE_CFG ((0x0002 << 2) + 0xfe440000)
#define OTP_TEE_WR_DAT ((0x0004 << 2) + 0xfe440000)
#define OTP_TEE_RD_DAT ((0x0008 << 2) + 0xfe440000)
#define OTP_LIC_A ((0x0010 << 2) + 0xfe440000)
#define OTP_AML_ID_L ((0x0020 << 2) + 0xfe440000)
#define OTP_AML_ID_H ((0x0021 << 2) + 0xfe440000)
#define OTP_ACGK_ID_L ((0x0022 << 2) + 0xfe440000)
#define OTP_ACGK_ID_H ((0x0023 << 2) + 0xfe440000)
#define OTP_DVGK_ID_L ((0x0024 << 2) + 0xfe440000)
#define OTP_DVGK_ID_H ((0x0025 << 2) + 0xfe440000)
#define OTP_DVUK_ID_L ((0x0026 << 2) + 0xfe440000)
#define OTP_DVUK_ID_H ((0x0027 << 2) + 0xfe440000)
#define OTP_DGPK_ID_L ((0x0028 << 2) + 0xfe440000)
#define OTP_DGPK_ID_H ((0x0029 << 2) + 0xfe440000)
#define OTP_SECPU_ID_L ((0x002a << 2) + 0xfe440000)
#define OTP_SECPU_ID_H ((0x002b << 2) + 0xfe440000)
#define OTP_ETSI012_ID_L ((0x002c << 2) + 0xfe440000)
#define OTP_ETSI012_ID_H ((0x002d << 2) + 0xfe440000)
#define OTP_ETSI3_ID_L ((0x002e << 2) + 0xfe440000)
#define OTP_ETSI3_ID_H ((0x002f << 2) + 0xfe440000)
#define OTP_MSR_ID_L ((0x0030 << 2) + 0xfe440000)
#define OTP_MSR_ID_H ((0x0031 << 2) + 0xfe440000)
#define OTP_VO_ID_L ((0x0032 << 2) + 0xfe440000)
#define OTP_VO_ID_H ((0x0033 << 2) + 0xfe440000)
#define OTP_NUID_ID_L ((0x0034 << 2) + 0xfe440000)
#define OTP_NUID_ID_H ((0x0035 << 2) + 0xfe440000)
#define OTP_CONAX_ID_L ((0x0036 << 2) + 0xfe440000)
#define OTP_CONAX_ID_H ((0x0037 << 2) + 0xfe440000)
#define OTP_NSK_ID_L ((0x0038 << 2) + 0xfe440000)
#define OTP_NSK_ID_H ((0x0039 << 2) + 0xfe440000)
#define OTP_REE_RDY ((0x0040 << 2) + 0xfe440000)
#define OTP_REE_DEBUG ((0x0041 << 2) + 0xfe440000)
#define OTP_REE_CFG ((0x0042 << 2) + 0xfe440000)
#define OTP_MRK_CHKNUM ((0x0043 << 2) + 0xfe440000)
#define OTP_REE_RD_DAT ((0x0048 << 2) + 0xfe440000)
//========================================================================
// KL REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440200
// -----------------------------------------------
#define MKL_TEE_RDY ((0x0000 << 2) + 0xfe440200)
#define MKL_TEE_DEBUG ((0x0001 << 2) + 0xfe440200)
#define MKL_TEE_CFG ((0x0002 << 2) + 0xfe440200)
#define MKL_TEE_CMD ((0x0003 << 2) + 0xfe440200)
#define MKL_TEE_EK ((0x0004 << 2) + 0xfe440200)
#define MKL_TEE_CR_0 ((0x001c << 2) + 0xfe440200)
#define MKL_TEE_CR_1 ((0x001d << 2) + 0xfe440200)
#define MKL_TEE_CR_2 ((0x001e << 2) + 0xfe440200)
#define MKL_TEE_CR_3 ((0x001f << 2) + 0xfe440200)
#define MKL_REE_RDY ((0x0020 << 2) + 0xfe440200)
#define MKL_REE_DEBUG ((0x0021 << 2) + 0xfe440200)
#define MKL_REE_CFG ((0x0022 << 2) + 0xfe440200)
#define MKL_REE_CMD ((0x0023 << 2) + 0xfe440200)
#define MKL_REE_EK ((0x0024 << 2) + 0xfe440200)
//========================================================================
// DMA REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440400
// -----------------------------------------------
#define DMA_CORE_DSC_0 ((0x0000 << 2) + 0xfe440400)
#define DMA_CORE_DSC_1 ((0x0001 << 2) + 0xfe440400)
#define DMA_CORE_DSC_2 ((0x0002 << 2) + 0xfe440400)
#define DMA_CORE_DSC_3 ((0x0003 << 2) + 0xfe440400)
#define DMA_CORE_DSC_4 ((0x0004 << 2) + 0xfe440400)
#define DMA_CORE_DSC_5 ((0x0005 << 2) + 0xfe440400)
#define DMA_CORE_IRQ_STS_0 ((0x0008 << 2) + 0xfe440400)
#define DMA_CORE_IRQ_STS_1 ((0x0009 << 2) + 0xfe440400)
#define DMA_CORE_IRQ_STS_2 ((0x000a << 2) + 0xfe440400)
#define DMA_CORE_IRQ_STS_3 ((0x000b << 2) + 0xfe440400)
#define DMA_CORE_IRQ_STS_4 ((0x000c << 2) + 0xfe440400)
#define DMA_CORE_IRQ_STS_5 ((0x000d << 2) + 0xfe440400)
#define DMA_CORE_CFG_REG ((0x0010 << 2) + 0xfe440400)
#define DMA_CORE_CFG_SEC_LSB ((0x0011 << 2) + 0xfe440400)
#define DMA_CORE_CFG_SEC_MSB ((0x0012 << 2) + 0xfe440400)
//========================================================================
// KT REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440500
// -----------------------------------------------
#define KT_TEE_RDY ((0x0000 << 2) + 0xfe440500)
#define KT_TEE_RDY2 ((0x0001 << 2) + 0xfe440500)
#define KT_TEE_CFG ((0x0002 << 2) + 0xfe440500)
#define KT_TEE_STS ((0x0003 << 2) + 0xfe440500)
#define KT_TEE_KEY0 ((0x0004 << 2) + 0xfe440500)
#define KT_TEE_KEY1 ((0x0005 << 2) + 0xfe440500)
#define KT_TEE_KEY2 ((0x0006 << 2) + 0xfe440500)
#define KT_TEE_KEY3 ((0x0007 << 2) + 0xfe440500)
#define KT_REE_RDY ((0x0020 << 2) + 0xfe440500)
#define KT_REE_RDY2 ((0x0021 << 2) + 0xfe440500)
#define KT_REE_CFG ((0x0022 << 2) + 0xfe440500)
#define KT_REE_STS ((0x0023 << 2) + 0xfe440500)
#define KT_REE_KEY0 ((0x0024 << 2) + 0xfe440500)
#define KT_REE_KEY1 ((0x0025 << 2) + 0xfe440500)
#define KT_REE_KEY2 ((0x0026 << 2) + 0xfe440500)
#define KT_REE_KEY3 ((0x0027 << 2) + 0xfe440500)
//========================================================================
// CERT REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440600
// -----------------------------------------------
//========================================================================
// SP REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe441000
// -----------------------------------------------
// ree domian
#define REE_SCPU2REE_CSR_ADDR ((0x0300 << 2) + 0xfe441000)
#define REE_SCPU2REE_DATA_ST_ADDR ((0x0380 << 2) + 0xfe441000)
#define REE_SCPU2REE_DATA_ED_ADDR ((0x039f << 2) + 0xfe441000)
#define REE_REE2SCPU_CSR_ADDR ((0x0200 << 2) + 0xfe441000)
#define REE_REE2SCPU_DATA_ST_ADDR ((0x0280 << 2) + 0xfe441000)
#define REE_REE2SCPU_DATA_ED_ADDR ((0x029f << 2) + 0xfe441000)
// tee domian
#define TEE_SCPU2TEE_CSR_ADDR ((0x0100 << 2) + 0xfe441000)
#define TEE_SCPU2TEE_DATA_ST_ADDR ((0x0180 << 2) + 0xfe441000)
#define TEE_SCPU2TEE_DATA_ED_ADDR ((0x019f << 2) + 0xfe441000)
#define TEE_TEE2SCPU_CSR_ADDR ((0x0000 << 2) + 0xfe441000)
#define TEE_TEE2SCPU_DATA_ST_ADDR ((0x0080 << 2) + 0xfe441000)
#define TEE_TEE2SCPU_DATA_ED_ADDR ((0x009f << 2) + 0xfe441000)
//========================================================================
// NSK REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe450000
// -----------------------------------------------
//
// Closing file:  REG_LIST_SECURITY_RTL.h
//
//`include "REG_LIST_DEMUX_RTL.h"
// synopsys translate_off
// synopsys translate_on
//
// Closing file:  ./REG_LIST_RTL.h
//

#endif // REGISTER_H

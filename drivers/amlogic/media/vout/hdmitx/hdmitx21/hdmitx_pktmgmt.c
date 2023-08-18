// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <amlogic/media/vout/hdmitx21/hdmitx.h>
#include "hdmitx_drv.h"

static void tpi_info_send(u8 sel, u8 *data)
{
	u8 checksum = 0;
	int i;

	hdmitx21_wr_reg(TPI_INFO_FSEL_IVCTX, sel); // buf selection
	if (!data) {
		hdmitx21_wr_reg(TPI_INFO_EN_IVCTX, 0);
		return;
	}

	/* do checksum */
	data[3] = 0;
	for (i = 0; i < 31; i++)
		checksum += data[i];
	checksum = 0 - checksum;
	data[3] = checksum;

	for (i = 0; i < 31; i++)
		hdmitx21_wr_reg(TPI_INFO_B0_IVCTX + i, data[i]);
	hdmitx21_wr_reg(TPI_INFO_EN_IVCTX, 0xe0); //TPI Info enable
}

/* packet no need checksum */
static void tpi_packet_send(u8 sel, u8 *data)
{
	int i;

	hdmitx21_wr_reg(TPI_INFO_FSEL_IVCTX, sel); // buf selection
	if (!data) {
		hdmitx21_wr_reg(TPI_INFO_EN_IVCTX, 0);
		return;
	}

	for (i = 0; i < 31; i++)
		hdmitx21_wr_reg(TPI_INFO_B0_IVCTX + i, data[i]);
	hdmitx21_wr_reg(TPI_INFO_EN_IVCTX, 0xe0); //TPI Info enable
}

static int tpi_info_get(u8 sel, u8 *data)
{
	int i;

	hdmitx21_wr_reg(TPI_INFO_FSEL_IVCTX, sel); // buf selection
	if (!data)
		return -1;
	if (hdmitx21_rd_reg(TPI_INFO_EN_IVCTX) == 0)
		return 0;
	for (i = 0; i < 31; i++)
		data[i] = hdmitx21_rd_reg(TPI_INFO_B0_IVCTX + i);
	return 31; /* fixed value */
}

void dump_infoframe_packets(void)
{
	int i, j;
	u8 body[32] = {0};

	for (i = 0; i < 17; i++) {
		tpi_info_get(i, body);
		body[31] = hdmitx21_rd_reg(TPI_INFO_EN_IVCTX);
		printf("dump hdmi infoframe[%d]\n", i);
		for (j = 0; j < 32; j += 8)
			printf("%02x%02x%02x%02x%02x%02x%02x%02x\n",
				body[j + 0], body[j + 1],
				body[j + 2], body[j + 3],
				body[j + 4], body[j + 5],
				body[j + 6], body[j + 7]);
		memset(body, 0, sizeof(body));
	}
}

static int _tpi_infoframe_wrrd(u8 wr, u16 info_type, u8 *body)
{
	u8 sel;

	switch (info_type) {
	case HDMI_INFOFRAME_TYPE_AVI:
		sel = 0;
		break;
	case HDMI_INFOFRAME_TYPE_AUDIO:
		sel = 2;
		break;
	case HDMI_INFOFRAME_TYPE_SPD:
		sel = 3;
		break;
	case HDMI_INFOFRAME_TYPE_VENDOR:
		sel = 5;
		break;
	case HDMI_INFOFRAME_TYPE_DRM:
		sel = 6;
		break;
	case HDMI_PACKET_TYPE_GCP:
		sel = 7;
		tpi_packet_send(sel, body);
		return 0;
	case HDMI_INFOFRAME_TYPE_VENDOR2:
		sel = 8;
		break;
	default:
		pr_info("%s[%d] wrong info_type %d\n", __func__, __LINE__, info_type);
		return -1;
	}

	if (wr) {
		if (!body) {
			tpi_info_send(sel, NULL);
			return 0;
		}
		/* do checksum */
		tpi_info_send(sel, body);
		return 0;
	} else {
		return tpi_info_get(sel, body);
	}
}

void hdmitx21_infoframe_send(u16 info_type, u8 *body)
{
	_tpi_infoframe_wrrd(1, info_type, body);
}

int hdmitx21_infoframe_rawget(u8 info_type, u8 *body)
{
	return _tpi_infoframe_wrrd(0, info_type, body);
}

/* refer to VESA-DSC-1.2a.pdf Page 50 */
static void pps_data_map(u8 *body, struct dsc_pps_data_s *pps,
	struct hdmi_timing *timing)
{
	int i;
	int j;

	if (!body || !pps)
		return;

	body[0] = ((pps->dsc_version_major & 0xf) << 4) |
		((pps->dsc_version_minor & 0xf) << 0);
	body[1] = pps->pps_identifier & 0xff;
	body[2] = 0x00; /* RESERVED */
	body[3] = ((pps->bits_per_component & 0xf) << 4) |
		((pps->line_buf_depth & 0xf) << 0);
	body[4] = ((pps->block_pred_enable & 0x1) << 5) |
		((pps->convert_rgb & 0x1) << 4) |
		((pps->simple_422 & 0x1) << 3) |
		((pps->vbr_enable & 0x1) << 2) |
		(((pps->bits_per_pixel >> 8) & 0x3) << 0);
	body[5] = pps->bits_per_pixel & 0xff;
	body[6] = (pps->pic_height >> 8) & 0xff;
	body[7] = pps->pic_height & 0xff;
	body[8] = (pps->pic_width >> 8) & 0xff;
	body[9] = pps->pic_width & 0xff;
	body[10] = (pps->slice_height >> 8) & 0xff;
	body[11] = pps->slice_height & 0xff;
	body[12] = (pps->slice_width >> 8) & 0xff;
	body[13] = pps->slice_width & 0xff;
	body[14] = (pps->chunk_size >> 8) & 0xff;
	body[15] = pps->chunk_size & 0xff;
	body[16] = (pps->initial_xmit_delay >> 8) & 0x3;
	body[17] = pps->initial_xmit_delay & 0xff;
	body[18] = (pps->initial_dec_delay >> 8) & 0xff;
	body[19] = pps->initial_dec_delay & 0xff;
	body[20] = 0x00; /* RESERVED */
	body[21] = pps->initial_scale_value & 0x3f; /* RESERVED */
	body[22] = (pps->scale_increment_interval >> 8) & 0xff;
	body[23] = pps->scale_increment_interval & 0xff;
	body[24] = (pps->scale_decrement_interval >> 8) & 0xf;
	body[25] = pps->scale_decrement_interval & 0xff;
	body[26] = 0x00; /* RESERVED */
	body[27] = pps->first_line_bpg_offset & 0x1f;
	body[28] = (pps->nfl_bpg_offset >> 8) & 0xff;
	body[29] = pps->nfl_bpg_offset & 0xff;
	body[30] = (pps->slice_bpg_offset >> 8) & 0xff;
	body[31] = pps->slice_bpg_offset & 0xff;
	body[32] = (pps->initial_offset >> 8) & 0xff;
	body[33] = pps->initial_offset & 0xff;
	body[34] = (pps->final_offset >> 8) & 0xff;
	body[35] = pps->final_offset & 0xff;
	body[36] = pps->flatness_min_qp & 0x1f;
	body[37] = pps->flatness_max_qp & 0x1f;
	body[38] = (pps->rc_parameter_set.rc_model_size >> 8) & 0xff;
	body[39] = pps->rc_parameter_set.rc_model_size & 0xff;
	body[40] = pps->rc_parameter_set.rc_edge_factor & 0xf;
	body[41] = pps->rc_parameter_set.rc_quant_incr_limit0 & 0x1f;
	body[42] = pps->rc_parameter_set.rc_quant_incr_limit1 & 0x1f;
	body[43] = ((pps->rc_parameter_set.rc_tgt_offset_hi & 0xf) << 4) |
		((pps->rc_parameter_set.rc_tgt_offset_lo & 0xf) << 0);
	for (i = 44, j = 0; i < 58; i++, j++)
		body[i] = pps->rc_parameter_set.rc_buf_thresh[j];
	for (i = 58, j = 0; i < 88; i += 2, j++) {
		u8 min_qp = pps->rc_parameter_set.rc_range_parameters[j].range_min_qp & 0x1f;
		u8 max_qp = pps->rc_parameter_set.rc_range_parameters[j].range_max_qp & 0x1f;
		u8 bpg_offset =
			pps->rc_parameter_set.rc_range_parameters[j].range_bpg_offset & 0x3f;

		body[i] = (min_qp << 3) | ((max_qp >> 2) & 0x7);
		body[i + 1] = ((max_qp & 0x3) << 6) | bpg_offset;
	}
	body[88] = ((pps->native_420 & 0x1) << 1) |
		((pps->native_422 & 0x1) << 0);
	body[89] = pps->second_line_bpg_offset & 0x1f;
	body[90] = (pps->nsl_bpg_offset >> 8) & 0xff;
	body[91] = pps->nsl_bpg_offset & 0xff;
	body[92] = (pps->second_line_offset_adj >> 8) & 0xff;
	body[93] = pps->second_line_offset_adj & 0xff;
	for (i = 94; i < 128; i++)
		body[i] = 0x00; /* RESERVED */
	body[128] = timing->h_front & 0xff;
	body[129] = (timing->h_front >> 8) & 0xff;
	body[130] = timing->h_sync & 0xff;
	body[131] = (timing->h_sync >> 8) & 0xff;
	body[132] = timing->h_back & 0xff;
	body[133] = (timing->h_back >> 8) & 0xff;
	body[134] = pps->hc_active_bytes & 0xff;
	body[135] = (pps->hc_active_bytes >> 8) & 0xff;
}

static int emp_verbose;

/* send DSC packet */
void hdmitx_dsc_cvtem_pkt_send(struct dsc_pps_data_s *pps,
	struct hdmi_timing *timing)
{
	int i;
	u8 data8;
	//dsc total send 6 packet as one emp, the actual payload byte is 136
	const u16 dsc_byte_num = (5 - 1) * 28 + 24;
	//all 6 DSF, and the remain bytes in last DSF should be cleared
	const u16 dsc_pkt_insert = (6 - 1) * 28 + 21;
	u8 body[6 * 28];

	memset(body, 0, sizeof(body));
	pps_data_map(body, pps, timing);

	// step1: DSC timing
	// DSC Vertical Blanking Lines Register
	// total_lines_fapa = reg_vb_le[0] ? (reg_vb_le+1)/2 : reg_vb_le/2;  ????
	// ***FAPA invalid after total_lines_fapa vblank lines ***
	// or vsync negedge when reg_fapa_fsm_proper_move=1
	hdmitx21_wr_reg(DSC_PKT_VB_LE_IVCTX, timing->v_blank); //reg_vb_le
	hdmitx21_wr_reg(DSC_PKT_SPARE_3_IVCTX, 0x2); //[1] reg_fapa_fsm_proper_move

	// step2: prepare packet data
	// setting generate packet
	// setting payload
	//payload [15:8] ===> pb5 length msb
	hdmitx21_wr_reg(DSC_PKT_INSERT_PAYLOAD_1_IVCTX, dsc_byte_num >> 8);
	//payload [7:0]  ===> pb6 length lsb
	hdmitx21_wr_reg(DSC_PKT_INSERT_PAYLOAD_0_IVCTX, dsc_byte_num & 0xff);
	hdmitx21_wr_reg(DSC_PKT_GEN_CTL_IVCTX, 0xb1); //[0] reg_source_en [6:5] fapa ctrl
	//[3] reg_send_pkt_cont (send data set for each frame if it is 1)
	//[0] reg_send_end_data_set
	hdmitx21_wr_reg(DSC_PKT_INSERT_CTL_1_IVCTX, 0x8);
	data8  = 0;
	data8 |= (0 << 6); //[7 : 6] rsvd
	data8 |= (0 << 5); //[    5] reg_set_new_in_m1_ds_pkt
	data8 |= (0 << 4); //[    4] reg_set_new_in_middle
	data8 |= (0 << 3); //[    3] reg_set_new_always
	data8 |= (1 << 2); //[    2] reg_to_err_ctrl
	data8 |= (0 << 1); //[    1] feg_fapa1_supprot. =0:FAPA start only after second active line.
	data8 |= (1 << 0); //[    0] reg_set_end_for_ml_ds
	hdmitx21_wr_reg(DSC_PKT_INSERT_CTL_2_IVCTX, data8);

	//HDR DE: reg_act_de = {reg_act_de_msb,reg_act_de_lsb};
	// ***FAPA valid after reg_act_de active lines***
	hdmitx21_wr_reg(DSC_PKT_ACT_DE_LO_IVCTX, timing->v_active & 0xff); //reg_act_de_lsb
	hdmitx21_wr_reg(DSC_PKT_ACT_DE_HI_IVCTX, (timing->v_active >> 8) & 0xff); //reg_act_de_msb

	//  step3: packet header and content
	hdmitx21_wr_reg(DSC_PKT_EM_HB0_IVCTX, 0x7f); // HB0 header
	hdmitx21_wr_reg(DSC_PKT_EM_PB0_IVCTX, (1 << 2) | (1 << 1)); // pb0 [7] new; [6] end
	hdmitx21_wr_reg(DSC_PKT_EM_PB2_IVCTX, 0x01); // pb2 ID
	hdmitx21_wr_reg(DSC_PKT_EM_PB3_IVCTX, 0x00); // pb3
	hdmitx21_wr_reg(DSC_PKT_EM_PB4_IVCTX, 0x02); // pb4

	//============== update DSC data ================
	hdmitx21_wr_reg(DSC_PKT_INSERT_CTRL_IVCTX, 0x1); // [0] reg_pkt_gen; [1]reg_pkt_gen_en
	hdmitx21_wr_reg(DSC_PKT_MEM_WADDR_RST_IVCTX, 0);
	hdmitx21_wr_reg(DSC_PKT_MEM_WADDR_RST_IVCTX, 1);
	hdmitx21_wr_reg(DSC_PKT_MEM_WADDR_RST_IVCTX, 0);

	hdmitx21_set_reg_bits(DSC_PKT_GEN_CTL_IVCTX, 1, 3, 1);
	udelay(100);
	hdmitx21_set_reg_bits(DSC_PKT_GEN_CTL_IVCTX, 0, 3, 1);

	for (i = 0; i < dsc_pkt_insert; i++) {
		if (emp_verbose)
			pr_info("body[%d]=0x%02x\n", i, body[i]);
		hdmitx21_wr_reg(DSC_PKT_MEM_WDATA_IVCTX, body[i]);
	}
	emp_verbose = 0;
	hdmitx21_wr_reg(DSC_PKT_INSERT_CTRL_IVCTX, 0x3);

	/* only for pkt send in vsync */
	//hdmitx21_wr_reg(DSC_PKT_INSERT_CTRL_IVCTX, 0x0); // [0] reg_pkt_gen; [1]reg_pkt_gen_en
	//hdmitx21_set_reg_bits(PCLK2TMDS_MISC1_IVCTX, 1, 4, 1); //[4] reg_bypass_video_path
}

void hdmitx_dsc_cvtem_pkt_disable(void)
{
	hdmitx21_wr_reg(DSC_PKT_INSERT_CTRL_IVCTX, 0x0);
}


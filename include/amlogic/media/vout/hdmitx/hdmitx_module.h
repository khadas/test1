#ifndef __HDMITX_MODULE_H__
#define __HDMITX_MODULE_H__

#include "hdmi_common.h"
#include "hdmitx_ext.h"

struct hdmitx_dev {
	unsigned char rx_edid[512]; /* some RX may exceeds 256Bytes */
	struct {
		int (*get_hpd_state)(void);
		int (*read_edid)(unsigned char *buf, unsigned char addr,
				 unsigned char blk_no);
		void (*turn_off)(void);
		void (*list_support_modes)(void);
		void (*dump_regs)(void);
		void (*test_bist)(unsigned int mode);
		void (*test_prbs)(void);
		void (*set_div40)(bool div40);
		void (*output_blank)(unsigned int blank);
	} hwop;
	unsigned char rawedid[EDID_BLK_SIZE * EDID_BLK_NO];
	struct rx_cap RXCap;
	struct hdmi_format_para *para;
	enum hdmi_vic vic;
	unsigned int frac_rate_policy;
	unsigned int mode420;
	unsigned int dc30;
	enum eotf_type hdmi_current_eotf_type;
	enum mode_type hdmi_current_tunnel_mode;
	/* Add dongle_mode, clock, phy may be different from mbox */
	unsigned int dongle_mode;
};

struct hdmitx_dev *hdmitx_get_hdev(void);

struct hdmi_format_para *hdmi_get_fmt_paras(enum hdmi_vic vic);
enum hdmi_vic hdmi_get_fmt_vic(char const *name);
void hdmi_parse_attr(struct hdmi_format_para *para, char const *name);
void hdmi_tx_set(struct hdmitx_dev *hdev);
/* Parsing RAW EDID data from edid to pRXCap */
unsigned int hdmi_edid_parsing(unsigned char *edid, struct rx_cap *pRXCap);
struct hdmi_format_para *hdmi_match_dtd_paras(struct dtd *t);
bool hdmimode_is_interlaced(enum hdmi_vic vic);
void hdmitx_ddc_init(void);
void hdmitx_set_clk(struct hdmitx_dev *hdev);
void hdmitx_turnoff(void);
int hdmitx_get_hpd_state(void);
void hdmitx_prbs(void);
unsigned int hdmitx_rd_check_reg(unsigned int addr, unsigned int exp_data,
	unsigned int mask);
void hdmitx_hdcp_init(void);
void hdmitx_set_phypara(enum hdmi_phy_para mode);
void hdmitx_test_prbs(void);
void hdmitx_set_div40(bool div40);

extern void hdmitx_set_drm_pkt(struct master_display_info_s *data);
bool hdmitx_find_vendor(struct hdmitx_dev *hdev);
#ifndef CONFIG_AML_HDMITX20
void __attribute__((weak))hdmitx_set_drm_pkt(struct master_display_info_s *data)
{
}
#endif

void hdmitx_set_vsif_pkt(enum eotf_type type, enum mode_type tunnel_mode,
	struct dv_vsif_para *data);
void hdmitx_set_hdr10plus_pkt(unsigned int flag,
	struct hdr10plus_para *data);

#ifndef printk
#define printk printf
#endif
#ifndef pr_info
#define pr_info printf
#endif

#define hdmitx_debug() /* printf("hd: %s[%d]\n", __func__, __LINE__) */

extern struct hdr_info *hdmitx_get_rx_hdr_info(void);
#ifndef CONFIG_AML_HDMITX20
struct hdr_info * __attribute__((weak))hdmitx_get_rx_hdr_info(void)
{
	return NULL;
}
#endif

#endif

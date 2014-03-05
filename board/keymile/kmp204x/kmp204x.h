/*
 * (C) Copyright 2013 Keymile AG
 * Valentin Longchamp <valentin.longchamp@keymile.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* QRIO GPIO ports */
#define GPIO_A			0x40
#define GPIO_B			0x60

int qrio_get_gpio(u8 port_off, u8 gpio_nr);
void qrio_set_opendrain_gpio(u8 port_off, u8 gpio_nr, u8 val);
void qrio_set_gpio(u8 port_off, u8 gpio_nr, bool value);
void qrio_gpio_direction_output(u8 port_off, u8 gpio_nr, bool value);
void qrio_gpio_direction_input(u8 port_off, u8 gpio_nr);

#define PRSTCFG_POWUP_UNIT_CORE_RST	0x0
#define PRSTCFG_POWUP_UNIT_RST		0x1
#define PRSTCFG_POWUP_RST		0x3

void qrio_prst(u8 bit, bool en, bool wden);
void qrio_prstcfg(u8 bit, u8 mode);

void pci_of_setup(void *blob, bd_t *bd);

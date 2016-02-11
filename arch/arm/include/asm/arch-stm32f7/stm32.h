/*
 * (C) Copyright 2016
 * Vikas Manocha, STMicroelectronics, <vikas.manocha@st.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _ASM_ARCH_HARDWARE_H
#define _ASM_ARCH_HARDWARE_H

/* STM32F746 */
#define ITCM_FLASH_BASE		0x00200000UL
#define AXIM_FLASH_BASE		0x08000000UL

#define ITCM_SRAM_BASE		0x00000000UL
#define DTCM_SRAM_BASE		0x20000000UL
#define SRAM1_BASE		0x20010000UL
#define SRAM2_BASE		0x2004C000UL

#define PERIPH_BASE		0x40000000UL

#define APB1_PERIPH_BASE	(PERIPH_BASE + 0x00000000)
#define APB2_PERIPH_BASE	(PERIPH_BASE + 0x00010000)
#define AHB1_PERIPH_BASE	(PERIPH_BASE + 0x00020000)
#define AHB2_PERIPH_BASE	(PERIPH_BASE + 0x10000000)
#define AHB3_PERIPH_BASE	(PERIPH_BASE + 0x20000000)

#define TIM2_BASE		(APB1_PERIPH_BASE + 0x0000)
#define USART2_BASE		(APB1_PERIPH_BASE + 0x4400)
#define USART3_BASE		(APB1_PERIPH_BASE + 0x4800)
#define PWR_BASE		(APB1_PERIPH_BASE + 0x7000)

#define USART1_BASE		(APB2_PERIPH_BASE + 0x1000)
#define USART6_BASE		(APB2_PERIPH_BASE + 0x1400)

#define STM32_GPIOA_BASE	(AHB1_PERIPH_BASE + 0x0000)
#define STM32_GPIOB_BASE	(AHB1_PERIPH_BASE + 0x0400)
#define STM32_GPIOC_BASE	(AHB1_PERIPH_BASE + 0x0800)
#define STM32_GPIOD_BASE	(AHB1_PERIPH_BASE + 0x0C00)
#define STM32_GPIOE_BASE	(AHB1_PERIPH_BASE + 0x1000)
#define STM32_GPIOF_BASE	(AHB1_PERIPH_BASE + 0x1400)
#define STM32_GPIOG_BASE	(AHB1_PERIPH_BASE + 0x1800)
#define STM32_GPIOH_BASE	(AHB1_PERIPH_BASE + 0x1C00)
#define STM32_GPIOI_BASE	(AHB1_PERIPH_BASE + 0x2000)
#define STM32_GPIOJ_BASE	(AHB1_PERIPH_BASE + 0x2400)
#define STM32_GPIOK_BASE	(AHB1_PERIPH_BASE + 0x2800)
#define RCC_BASE		(AHB1_PERIPH_BASE + 0x3800)
#define FLASH_CNTL_BASE		(AHB1_PERIPH_BASE + 0x3C00)


#define SDRAM_FMC_BASE		(AHB3_PERIPH_BASE + 0x4A0000140)

enum clock {
	CLOCK_CORE,
	CLOCK_AHB,
	CLOCK_APB1,
	CLOCK_APB2
};
#define STM32_BUS_MASK          0xFFFF0000

int configure_clocks(void);

#endif /* _ASM_ARCH_HARDWARE_H */

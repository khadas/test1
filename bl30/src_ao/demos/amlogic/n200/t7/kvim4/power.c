/*
 * Copyright (C) 2014-2018 Amlogic, Inc. All rights reserved.
 *
 * All information contained herein is Amlogic confidential.
 *
 * This software is provided to you pursuant to Software License Agreement
 * (SLA) with Amlogic Inc ("Amlogic"). This software may be used
 * only in accordance with the terms of this agreement.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification is strictly prohibited without prior written permission from
 * Amlogic.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "FreeRTOS.h"
#include "common.h"
#include "gpio.h"
#include "ir.h"
#include "suspend.h"
#include "task.h"
#include "gpio.h"
#include "pwm.h"
#include "pwm_plat.h"
#include "keypad.h"
#include "wifi_bt_wake.h"
#include "hdmi_cec.h"
#include "hdmirx_wake.h"
#include "interrupt_control_eclic.h"
#include "eth.h"
#include "meson_i2c.h"

#define CONFIG_HDMIRX_PLUGIN_WAKEUP

static TaskHandle_t cecTask = NULL;
static int vdd_ee;

static IRPowerKey_t prvPowerKeyList[] = {
	{ 0xef10fe01, IR_NORMAL}, /* ref tv pwr */
	{ 0xba45bd02, IR_NORMAL}, /* small ir pwr */
	{ 0xef10fb04, IR_NORMAL}, /* old ref tv pwr */
	{ 0xf20dfe01, IR_NORMAL},
	{ 0xe51afb04, IR_NORMAL},
	{ 0x3ac5bd02, IR_CUSTOM},
	{}
        /* add more */
};

static void vIRHandler(IRPowerKey_t *pkey)
{
	uint32_t buf[4] = {0};
	if (pkey->type == IR_NORMAL)
		buf[0] = REMOTE_WAKEUP;
	else if (pkey->type == IR_CUSTOM)
		buf[0] = REMOTE_CUS_WAKEUP;

        /* do sth below  to wakeup*/
	STR_Wakeup_src_Queue_Send_FromISR(buf);
};


void str_hw_init(void);
void str_hw_disable(void);
void str_power_on(int shutdown_flag);
void str_power_off(int shutdown_flag);
void Tp_GpioIRQRegister(void);
void Tp_GpioIRQFree(void);

void str_hw_init(void)
{
	/*enable device & wakeup source interrupt*/
	vIRInit(MODE_HARD_NEC, GPIOD_5, PIN_FUNC1, prvPowerKeyList, ARRAY_SIZE(prvPowerKeyList), vIRHandler);
	vETHInit(IRQ_ETH_PMT_NUM,eth_handler);
	xTaskCreate(vCEC_task, "CECtask", configMINIMAL_STACK_SIZE,
		    NULL, CEC_TASK_PRI, &cecTask);

	vBackupAndClearGpioIrqReg();
	vKeyPadInit();
	vGpioIRQInit();

	wifi_bt_wakeup_init();
	Tp_GpioIRQRegister();

#ifdef CONFIG_HDMIRX_PLUGIN_WAKEUP
	hdmirx_GpioIRQRegister();
#endif
}


void str_hw_disable(void)
{
	/*disable wakeup source interrupt*/
	vIRDeint();
	vETHDeint();
	if (cecTask) {
		vTaskDelete(cecTask);
		cec_req_irq(0);
	}
	Tp_GpioIRQFree();
	wifi_bt_wakeup_deinit();
	vKeyPadDeinit();
	vRestoreGpioIrqReg();
#ifdef CONFIG_HDMIRX_PLUGIN_WAKEUP
	hdmirx_GpioIRQFree();
#endif
}

static void str_gpio_backup(void)
{
	// TODO:

	// Example:
	// if (xBankStateBackup("A"))
	// 	printf("xBankStateBackup fail\n");
}

static void str_gpio_restore(void)
{
	// TODO:

	// Example:
	// if (xBankStateRestore("A"))
	// 	printf("xBankStateRestore fail\n");
}

void str_power_on(int shutdown_flag)
{
	int ret;
	shutdown_flag = shutdown_flag;

	/***set vdd_ee val***/
	ret = vPwmMesonSetVoltage(VDDEE_VOLT,vdd_ee);
	if (ret < 0) {
		printf("vdd_EE pwm set fail\n");
		return;
	}

	/***power on vcc_5v***/
	ret = xGpioSetDir(GPIOH_4,GPIO_DIR_OUT);
	if (ret < 0) {
		printf("vcc_5v set gpio dir fail\n");
		return;
	}

	ret = xGpioSetValue(GPIOH_4,GPIO_LEVEL_HIGH);
	if (ret < 0) {
		printf("vcc_5v set gpio val fail\n");
		return;
	}
	/***power on vdd_cpu***/
	ret = xGpioSetDir(GPIOD_7,GPIO_DIR_OUT);
	if (ret < 0) {
		printf("vdd_cpu_a set gpio dir fail\n");
		return;
	}

	ret = xGpioSetValue(GPIOD_7,GPIO_LEVEL_HIGH);
	if (ret < 0) {
		printf("vdd_cpu_a set gpio val fail\n");
		return;
	}

	/***power on vdd_cpu***/
	ret = xGpioSetDir(GPIO_TEST_N,GPIO_DIR_OUT);
	if (ret < 0) {
		printf("vdd_cpu_b set gpio dir fail\n");
		return;
	}

	ret = xGpioSetValue(GPIO_TEST_N,GPIO_LEVEL_HIGH);
	if (ret < 0) {
		printf("vdd_cpu_b set gpio val fail\n");
		return;
	}

	/*Wait POWERON_VDDCPU_DELAY for VDDCPU stable*/
	vTaskDelay(POWERON_VDDCPU_DELAY);
	printf("vdd_cpu on\n");

	str_gpio_restore();
}

void mcu_i2c_init(void);
void mcu_i2c_init(void)
{
	// set pinmux
	xPinmuxSet(GPIOD_2, PIN_FUNC1);
	xPinmuxSet(GPIOD_3, PIN_FUNC1);
	//set ds and pull up
	xPinconfSet(GPIOD_2, PINF_CONFIG_BIAS_PULL_UP | PINF_CONFIG_DRV_STRENGTH_3);
	xPinconfSet(GPIOD_3, PINF_CONFIG_BIAS_PULL_UP | PINF_CONFIG_DRV_STRENGTH_3);

	xI2cMesonPortInit(I2C_AO_A);
}

void str_power_off(int shutdown_flag)
{
	int ret;

	str_gpio_backup();

	//shutdown_flag = shutdown_flag;

	/***save vdd_ee val***/
	vdd_ee = vPwmMesonGetVoltage(VDDEE_VOLT);
	if (vdd_ee < 0) {
		printf("vdd_EE pwm get fail\n");
		return;
	}

	/***power off vdd_cpu***/
	if (get_ETHWol_flag() == 0) {
		ret = xGpioSetDir(GPIO_TEST_N,GPIO_DIR_OUT);
		if (ret < 0) {
			printf("vdd_cpu_b set gpio dir fail\n");
			return;
		}

		ret= xGpioSetValue(GPIO_TEST_N,GPIO_LEVEL_LOW);
		if (ret < 0) {
			printf("vdd_cpu_b set gpio val fail\n");
			return;
		}
	}

	/***power off vdd_cpu***/
	ret = xGpioSetDir(GPIOD_7,GPIO_DIR_OUT);
	if (ret < 0) {
		printf("vdd_cpu_a set gpio dir fail\n");
		return;
	}

	ret= xGpioSetValue(GPIOD_7,GPIO_LEVEL_LOW);
	if (ret < 0) {
		printf("vdd_cpu_a set gpio val fail\n");
		return;
	}

	printf("vdd_cpu off\n");
	if (1 == shutdown_flag) {
		uint8_t val = 1;

		printf("mcu off\n");
		mcu_i2c_init();
		// Poweroff MCU
		ret = xI2cMesonWrite(0x18, 0x80, &val, 1);
		if (ret < 0) {
			printf("power off mcu fail\n");
			return;
		}
	}
	/***power off vcc_5v***/
	ret = xGpioSetDir(GPIOH_4,GPIO_DIR_OUT);
	if (ret < 0) {
		printf("vcc_5v set gpio dir fail\n");
		return;
	}

	ret= xGpioSetValue(GPIOH_4,GPIO_LEVEL_LOW);
	if (ret < 0) {
		printf("vcc_5v set gpio val fail\n");
		return;
	}

	printf("vcc_5v off\n");

	/***set vdd_ee val***/
	ret = vPwmMesonSetVoltage(VDDEE_VOLT,771);
	if (ret < 0) {
		printf("vdd_EE pwm set fail\n");
		return;
	}
}


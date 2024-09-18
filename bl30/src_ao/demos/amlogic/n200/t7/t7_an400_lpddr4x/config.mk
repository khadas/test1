#
#  Copyright (C) 2014-2018 Amlogic, Inc. All rights reserved.
#
#  All information contained herein is Amlogic confidential.
#
#  This software is provided to you pursuant to Software License Agreement
#  (SLA) with Amlogic Inc ("Amlogic"). This software may be used
#  only in accordance with the terms of this agreement.
#
#  Redistribution and use in source and binary forms, with or without
#  modification is strictly prohibited without prior written permission from
#  Amlogic.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
SOC=t7
ARCH_CPU=RISC_V_N205
BOARD=t7_an400_lpddr4x

#config bt wakeup interrupt sampling
#BT_WAKE_CFG: 1 power and netflix key low level sampling
CFLAGS += -DBT_WAKE_CFG=1 -DBT_WAKE_HOST=GPIOX_18 -DBT_EN=GPIOX_17

#config wifi wakeup interrupt sampling
#WIFI_WAKE_CFG: 1
#CFLAGS += -DWIFI_WAKE_CFG=1 -DWIFI_WAKE_HOST=GPIOX_7 -DWIFI_PWREN=GPIOX_6
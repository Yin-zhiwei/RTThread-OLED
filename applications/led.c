/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-25     Awei         the first version
 */
#include <rtthread.h>

#define DBG_TAG "led"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <rtdevice.h>
#include <drv_common.h>

#include "led.h"

#define LED0    GET_PIN(C, 4)   // 板载LED

void led_thread_entry(void *parameter)
{
    rt_pin_mode(LED0, PIN_MODE_OUTPUT);
    while(1)
    {
        rt_pin_write(LED0, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0, PIN_LOW);
        rt_thread_mdelay(500);
    }
}




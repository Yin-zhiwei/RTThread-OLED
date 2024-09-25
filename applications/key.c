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

#define DBG_TAG "key"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <rtdevice.h>
#include <drv_common.h>

#include "key.h"

#define LED1    GET_PIN(A, 1)
#define KEY0    GET_PIN(B, 0)

void key_thread_entry(void *parameter)
{
    rt_pin_mode(LED1, PIN_MODE_OUTPUT);
    rt_pin_mode(KEY0, PIN_MODE_INPUT_PULLUP);
    while(1)
    {
        if(rt_pin_read(KEY0) == PIN_LOW)
        {
            rt_thread_mdelay(1);
            if(rt_pin_read(KEY0) == PIN_LOW)
            {
                rt_pin_write(LED1, PIN_LOW);
            }
        }
        else
        {
            rt_pin_write(LED1, PIN_HIGH);
        }
    }
}


/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-22     Awei         first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <rtdevice.h>
#include <drv_common.h>
//#include <u8g2_port.h>

#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

#define LED0    GET_PIN(C, 4)   // 板载LED
#define LED1    GET_PIN(A, 1)

#define KEY0    GET_PIN(B, 0)

static void key_thread_entry(void *parameter)
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

static void led_thread_entry(void *parameter)
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

static void count_thread_entry(void *parameter)
{
    int count = 1;

    while (count++)
    {
        LOG_D("Hello RT-Thread!");
        rt_thread_mdelay(1000);
    }
}

int main(void)
{
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_LPUART1_UART_Init();

    rt_thread_t key_thread;
    rt_thread_t led_thread;
    rt_thread_t count_thread;

    key_thread = rt_thread_create("thread3",
                                  key_thread_entry,
                                  RT_NULL,
                                  512,
                                  3,
                                  20);
    if(key_thread != RT_NULL)
    {
        rt_thread_startup(key_thread);
    }
    else
    {
        return -3;
    }

    led_thread = rt_thread_create("thread2",
                                  led_thread_entry,
                                  RT_NULL,
                                  512,
                                  3,
                                  20);
    if(led_thread != RT_NULL)
    {
        rt_thread_startup(led_thread);
    }
    else
    {
        return -2;
    }

    count_thread = rt_thread_create("thread1",
                                     count_thread_entry,
                                     RT_NULL,
                                     512,
                                     3,
                                     20);
    if(count_thread != RT_NULL)
    {
        rt_thread_startup(count_thread);
    }
    else
    {
        return -1;
    }
}

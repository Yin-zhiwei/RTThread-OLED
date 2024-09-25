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

#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include "led.h"
#include "key.h"
#include "oled.h"

#define THREAD_STACK_SIZE   1024
#define THREAD_PRIORITY     20
#define THREAD_COUNT_PRI    20
#define THREAD_TIMESLICE    10

void count_thread_entry(void *parameter)
{
    int count = 1;
    while (count++)
    {
        LOG_D("Hello RT-Thread!");
        rt_thread_mdelay(1000);
    }
}

rt_thread_t key_thread;
rt_thread_t led_thread;
rt_thread_t count_thread;
rt_thread_t oled_thread;

int main(void)
{
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_LPUART1_UART_Init();
    //u8g2_ssd1306_12864_sw_i2c();

    oled_thread = rt_thread_create("thread4",
                                   u8g2_ssd1306_12864_sw_i2c,
                                   RT_NULL,
                                   THREAD_STACK_SIZE,
                                   THREAD_PRIORITY,
                                   THREAD_TIMESLICE);
    if(oled_thread != RT_NULL)
    {
        rt_thread_startup(oled_thread);
    }
    else
    {
        return -4;
    }

    key_thread = rt_thread_create("thread3",
                                  key_thread_entry,
                                  RT_NULL,
                                  THREAD_STACK_SIZE,
                                  THREAD_PRIORITY,
                                  THREAD_TIMESLICE);
    if(key_thread != RT_NULL)
    {
        rt_thread_startup(key_thread);
    }
    else
    {
        LOG_D("can not create key thread");
        return -3;
    }

    led_thread = rt_thread_create("thread2",
                                  led_thread_entry,
                                  RT_NULL,
                                  THREAD_STACK_SIZE,
                                  THREAD_PRIORITY,
                                  THREAD_TIMESLICE);
    if(led_thread != RT_NULL)
    {
        rt_thread_startup(led_thread);
    }
    else
    {
        LOG_D("can not create led thread");
        return -2;
    }

    count_thread = rt_thread_create("thread1",
                                     count_thread_entry,
                                     RT_NULL,
                                     THREAD_STACK_SIZE,
                                     THREAD_COUNT_PRI,
                                     THREAD_TIMESLICE);
    if(count_thread != RT_NULL)
    {
        rt_thread_startup(count_thread);
    }
    else
    {
        return -1;
    }
}

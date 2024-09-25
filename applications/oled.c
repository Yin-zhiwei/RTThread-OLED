/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-24     Awei         the first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <u8g2_port.h>

#define OLED_I2C_PIN_SCL                    22  // PB6
#define OLED_I2C_PIN_SDA                    23  // PB7

void u8g2_ssd1306_12864_sw_i2c(void *parameter)
{
    u8g2_t u8g2;
    uint8_t i=0;

    // Initialization
    u8g2_Setup_ssd1306_i2c_128x64_noname_f( &u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8x8_gpio_and_delay_rtthread);
    // 该函数是根据oled的分辨率来的，在u8g2.h中可以找到对应的函数。
    u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_I2C_CLOCK, OLED_I2C_PIN_SCL);
    u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_I2C_DATA, OLED_I2C_PIN_SDA);

    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    // Draw Graphics
    /* full buffer example, setup procedure ends in _f */
    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);
    u8g2_DrawStr(&u8g2, 1, 18, "U8g2 start at RT-Thread");
    u8g2_SendBuffer(&u8g2);

    u8g2_SetFont(&u8g2, u8g2_font_unifont_t_symbols);
    u8g2_DrawGlyph(&u8g2, 112, 56, 0x2603 );
    u8g2_SendBuffer(&u8g2);

    while(1)
    {
        u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);
        //u8g2_DrawStr(&u8g2, 1, 18, "U8g2 start at RT-Thread");
        u8g2_SendBuffer(&u8g2);
    }
}

//MSH_CMD_EXPORT(u8g2_ssd1306_12864_sw_i2c_example, i2c ssd1306 software i2c sample);

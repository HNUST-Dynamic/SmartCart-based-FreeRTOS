/**
 ****************************************************************************************************
 * @file        led.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       LED 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 CH32V307开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20230720
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef _LED_H
#define _LED_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/

/* 引脚 定义 */
#define LED0_GPIO_PORT                  GPIOD
#define LED0_GPIO_PIN                   GPIO_Pin_12
#define LED0_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); }while(0)     /* PD口时钟使能 */

#define LED1_GPIO_PORT                  GPIOD
#define LED1_GPIO_PIN                   GPIO_Pin_13
#define LED1_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); }while(0)     /* PD口时钟使能 */

/******************************************************************************************/

/* LED端口定义 */
#define LED0(x)   do{ x ? \
                      GPIO_SetBits(LED0_GPIO_PORT,LED0_GPIO_PIN): \
                      GPIO_ResetBits(LED0_GPIO_PORT,LED0_GPIO_PIN); \
                  }while(0)             /* LED0 = RED */

#define LED1(x)   do{ x ? \
                      GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN): \
                      GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN); \
                  }while(0)             /* LED1 = GREEN */

/* LED取反定义 */
#define LED0_TOGGLE()   do{ gpio_toggle_pin(LED0_GPIO_PORT, LED0_GPIO_PIN); }while(0)        /* 翻转LED0 */
#define LED1_TOGGLE()   do{ gpio_toggle_pin(LED1_GPIO_PORT, LED1_GPIO_PIN); }while(0)        /* 翻转LED1 */

/******************************************************************************************/

void led_init(void);    /* 初始化LED */

#endif

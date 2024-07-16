/**
 ****************************************************************************************************
 * @file        led.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       LED ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� CH32V307������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20230720
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef _LED_H
#define _LED_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/

/* ���� ���� */
#define LED0_GPIO_PORT                  GPIOD
#define LED0_GPIO_PIN                   GPIO_Pin_12
#define LED0_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); }while(0)     /* PD��ʱ��ʹ�� */

#define LED1_GPIO_PORT                  GPIOD
#define LED1_GPIO_PIN                   GPIO_Pin_13
#define LED1_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); }while(0)     /* PD��ʱ��ʹ�� */

/******************************************************************************************/

/* LED�˿ڶ��� */
#define LED0(x)   do{ x ? \
                      GPIO_SetBits(LED0_GPIO_PORT,LED0_GPIO_PIN): \
                      GPIO_ResetBits(LED0_GPIO_PORT,LED0_GPIO_PIN); \
                  }while(0)             /* LED0 = RED */

#define LED1(x)   do{ x ? \
                      GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN): \
                      GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN); \
                  }while(0)             /* LED1 = GREEN */

/* LEDȡ������ */
#define LED0_TOGGLE()   do{ gpio_toggle_pin(LED0_GPIO_PORT, LED0_GPIO_PIN); }while(0)        /* ��תLED0 */
#define LED1_TOGGLE()   do{ gpio_toggle_pin(LED1_GPIO_PORT, LED1_GPIO_PIN); }while(0)        /* ��תLED1 */

/******************************************************************************************/

void led_init(void);    /* ��ʼ��LED */

#endif

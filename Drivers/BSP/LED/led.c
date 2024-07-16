/**
 ****************************************************************************************************
 * @file        led.c
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

#include "./BSP/LED/led.h"


/**
 * @brief       ��ʼ��LED���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    LED0_GPIO_CLK_ENABLE();                                 /* LED0ʱ��ʹ�� */
    LED1_GPIO_CLK_ENABLE();                                 /* LED1ʱ��ʹ�� */

    gpio_init_struct.GPIO_Pin = LED0_GPIO_PIN;              /* LED0���� */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;          /* ������� */
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;         /* ���� */
    GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);           /* ��ʼ��LED0���� */

    gpio_init_struct.GPIO_Pin = LED1_GPIO_PIN;              /* LED1���� */
    GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);           /* ��ʼ��LED1���� */
    

    LED0(1);                                                /* �ر� LED0 */
    LED1(1);                                                /* �ر� LED1 */
}

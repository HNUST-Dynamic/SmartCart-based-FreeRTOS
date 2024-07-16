/*
 * HX77.h
 *
 *  Created on: 2024年5月20日
 *      Author: 宋元
 */
#ifndef USER_HX77_H_
#define USER_HX77_H_

#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "system_ch32v30x.h"
#include "./SYSTEM//sys/sys.h"

void HX711_GPIO_Init(void);
void HX711_W_PD_SCK(uint8_t BitValue);
void HX711_W_DOUT(uint8_t BitValue);
uint8_t HX711_R_DOUT(void);
void HX711_Reset(void);
uint32_t HX711_ReadData(void);
int weight_check_add();
int weight_check_delete();

extern uint32_t     pi;
extern uint32_t    weight;
extern uint32_t current_product_weight;//放入商品的重量
extern uint32_t former_weight;//之前的总重量

extern volatile u8           numx;
extern int sx;
extern int arr[10];
//extern  arr[si_ze];
/******************************************************************************************/

/* 引脚 和 中断编号 & 中断服务函数 定义 */
#define AFIO_CLK_ENABLE()               do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); }while(0)   /* AFIO时钟使能 */

#define KEY0_INT_GPIO_PORT              GPIOA
#define KEY0_INT_GPIO_PIN               GPIO_Pin_1
#define KEY0_INT_GPIO_CLK_ENABLE()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)  /* PA口时钟使能 */
#define KEY0_INT_IRQn                   EXTI1_IRQn
#define KEY0_INT_IRQHandler             EXTI1_IRQHandler
#define KEY0_INT_EXTI_Line              EXTI_Line1

#define KEY1_INT_GPIO_PORT              GPIOC
#define KEY1_INT_GPIO_PIN               GPIO_Pin_5
#define KEY1_INT_GPIO_CLK_ENABLE()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); }while(0)  /* PC口时钟使能 */
#define KEY1_INT_IRQn                   EXTI9_5_IRQn
#define KEY1_INT_IRQHandler             EXTI9_5_IRQHandler
#define KEY1_INT_EXTI_Line              EXTI_Line5

#define WKUP_INT_GPIO_PORT              GPIOB
#define WKUP_INT_GPIO_PIN               GPIO_Pin_0
#define WKUP_INT_GPIO_CLK_ENABLE()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); }while(0)  /* PA口时钟使能 */
#define WKUP_INT_IRQn                   EXTI0_IRQn
#define WKUP_INT_IRQHandler             EXTI0_IRQHandler
#define WKUP_INT_EXTI_Line              EXTI_Line0
#define si_ze
#endif /* USER_HX77_H_ */

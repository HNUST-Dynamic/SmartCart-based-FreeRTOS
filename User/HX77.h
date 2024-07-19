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

#define si_ze
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

extern volatile u8 numx;
extern int sx;
extern int arr[10];

#endif /* USER_HX77_H_ */

/**
 ****************************************************************************************************
 * @file        usart.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       串口初始化代码(一般是串口1)，支持printf
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

#ifndef __USART_H
#define __USART_H

#include "stdio.h"	
#include "./SYSTEM/sys/sys.h"
#include "ch32v30x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define QUEUE_LENGTH  1024
#define QUEUE_ITEM_SIZE sizeof(uint8_t)

#define buffer_len 256
extern volatile u8 recv_ok ;       //接收完成标志
extern u8 uart_buf[32];  //用于保存串口数据
extern volatile u8 uart_cnt ;        //用于定位串口数据的位置
extern volatile u8 L610_Flag;
extern QueueHandle_t xQueue2;
extern QueueHandle_t xQueue1;
extern QueueHandle_t xQueue3;//用于摄像头和按键任务之间传递product的队列
extern QueueHandle_t xQueue4;//用于发送上报后获取的product给weightcheck
extern SemaphoreHandle_t xBinarySemaphore;//创建摄像头与按键扫描直接所用的二值信号量句柄
extern SemaphoreHandle_t xBinarySemaphore2;//创建上报后和weightcheck联系的二值信号量句柄
extern SemaphoreHandle_t xBinarySemaphore3;//创建扫描后页面与重量错误的同步二值信号量句柄
extern SemaphoreHandle_t xBinarySemaphore4;//创建显示重量错误与切回主页面的同步二值信号量句柄
extern SemaphoreHandle_t xBinarySemaphore5;//创建上报后和weightcheck联系的二值信号量句柄 delete
void USARTx_Init(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);

#endif

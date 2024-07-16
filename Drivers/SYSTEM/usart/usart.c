#include "usart.h"
#include "../User/pages.h"
#include "./BSP/LCD/lcd.h"
#include <ctype.h>
#include "../User/HX77.h"
#include "../User/L610.h"
#include "FreeRTOS.h"

#define MAX_BUFFER_SIZE 100

volatile u8 recv_ok;       //接收完成标志
u8 uart_buf[32]={0};  //用于保存串口数据
volatile u8 uart_cnt =0;        //用于定位串口数据的位置
uint16_t received_data;
volatile u8 L610_Flag=0;

QueueHandle_t xQueue;
SemaphoreHandle_t xSemaphore;


void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void USARTx_Init(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure1;
    GPIO_InitTypeDef   GPIO_InitStructure2;

    USART_InitTypeDef  USART_InitStructure1;
    USART_InitTypeDef  USART_InitStructure2;

    NVIC_InitTypeDef   NVIC_InitStructure1;
    NVIC_InitTypeDef   NVIC_InitStructure2;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  //摄像头
    GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF_PP;              //设置PA9为复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure1);
    GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //设置PA10为浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure1);
//L610
    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF_PP;              //设置PA2为复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure2);
    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //设置PA3为浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure2);

    //L610
    USART_InitStructure2.USART_BaudRate = 115200;
    USART_InitStructure2.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure2.USART_StopBits = USART_StopBits_1;
    USART_InitStructure2.USART_Parity = USART_Parity_No;
    USART_InitStructure2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure2.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure2);

//摄像头
    USART_InitStructure1.USART_BaudRate = 115200;
    USART_InitStructure1.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure1.USART_StopBits = USART_StopBits_1;
    USART_InitStructure1.USART_Parity = USART_Parity_No;
    USART_InitStructure1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure1.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure1);

    NVIC_InitStructure1.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority=1;      //抢占优先级为
    NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 1;           //子优先级为
    NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure1);                              //中断优先级初始化

    NVIC_InitStructure2.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority=1;      //抢占优先级为
    NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 1;           //子优先级为
    NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure2);                              //中断优先级初始化

    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

    USART_Cmd(USART1,ENABLE);
    USART_Cmd(USART2,ENABLE);
}

/*********************************************************************
 * @fn      _write
 *
 * @brief   Support Printf Function
 *
 * @param   *buf - UART send Data.
 *          size - Data length
 *
 * @return  size: Data length
 */
__attribute__((used)) int _write(int fd, char *buf, int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
        while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
        USART_SendData(USART2, *buf++);
    }

    return size;
}

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // 检查接收中断
       {
           USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 清除中断标志
           received_data = USART_ReceiveData(USART1); // 接收数据

           if(isalpha(received_data))
           {
                if (uart_cnt < sizeof(uart_buf) / sizeof(uart_buf[0])) // 检查缓冲区溢出
                {
                    uart_buf[uart_cnt++] = received_data; // 将接收到的数据存储在缓冲区中
                }
           }
           if(received_data=='\n') // 检查是否接收到换行符
           {
               uart_cnt = 0; // 重置缓冲区计数器
               recv_ok=1;
               numx =1;
               USART_Cmd(USART1,DISABLE);
           }

       }
}

void USART2_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // 中断产生
    {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE); // 清除中断标志
        uint8_t receivedData = USART_ReceiveData(USART2); // 接收数据
        
        // 从 ISR 中发送数据到队列
        xQueueSendFromISR(xQueue, &receivedData, &xHigherPriorityTaskWoken);

        // 如果需要的话进行上下文切换
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

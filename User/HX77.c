/*
 * HX77.c
 *
 *  Created on: 2024年5月20日
 *      Author: 宋元
 */
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "HX77.h"
#include "structures.h"
#include "L610.h"
#include "./BSP/LCD/lcd.h"

u32 HX711_Buffer;
u32 Weight_Maopi;
s32 Weight_Shiwu;
u8 Flag_Error = 0;
#define MEDIAN_LEN  5                         //中值滤波的滤波长度,一般取奇数
#define MEDIAN      3                         //中值在滤波数组中的位置
uint32_t   buffer[MEDIAN_LEN];              //中值滤波的数据缓存
int   medleng = 0;
uint32_t   num;                                   //数据对比大小中间变量
uint8_t Pi_flag=0;

uint32_t    pi_weight;                        //皮重
uint32_t pi ;                                 //初始自重
uint32_t    weight;                           //实际重量值
uint32_t current_product_weight;//放入商品的重量
uint32_t former_weight;//之前的总重量
int arr[10];
int sx=0;
volatile u8 numx;
void HX711_GPIO_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //时钟线推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //数据线浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void HX711_W_PD_SCK(uint8_t BitValue)                  //写时钟线
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)BitValue);
}

void HX711_W_DOUT(uint8_t BitValue)                    //写数据线，开始时，需要拉高DOUT电平
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)BitValue);
}

uint8_t HX711_R_DOUT(void)                             //读数据
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
}


void HX711_Reset(void)                                 // 传感器复位，去皮
{
    HX711_W_PD_SCK(1);                                   //拉高，延时60us
    delay_us(60);
}


uint32_t HX711_ReadData(void)                          //读数据
{
    uint8_t i;
    uint32_t value = 0;                         //接收HX711采集的AD值

    HX711_R_DOUT();
    HX711_W_PD_SCK(0);
    while(HX711_R_DOUT());           //等待DOUT引脚变为高电平

    delay_us(1);
    for(i=0;i<24;i++)                 //按照HX711时序接收数据
    {
        HX711_W_PD_SCK(1);              // PD_SCK置高，发送脉冲
        value=value<<1;
        HX711_W_PD_SCK(0);               // PD_SCK置低
        if(HX711_R_DOUT())value++;

    }
    HX711_W_PD_SCK(1);               //最后一个脉冲，增益为128
    value = value^0x800000;          //第25个脉冲转换数据，24位AD转换，最高位为符号位，其余为有效位
    HX711_W_PD_SCK(0);
    return value;
}
u8 charArrayToU8(const char *str)
{
    char *endptr;
    long int value;

    // 使用 strtol 函数将字符串转换为 long 类型整数
    value = strtol(str, &endptr, 10);

    // 检查是否转换成功以及值是否在 u8 范围内
    if (*endptr != '\0' || value < 0 || value > UINT8_MAX) {
        fprintf(stderr, "Invalid input or out of range.\n");
        return 0; // 返回0表示错误
    }

    return (u8)value;
}
int weight_check_add(ProductInfo product)
{
        current_product_weight=weight-former_weight;
        product.productWeight=charArrayToU8((const char*)product.productWeightStr);
        if((current_product_weight<=product.productWeight+20)&&(current_product_weight>=product.productWeight-20))
        {
            return 1;
        }
        else
        {
            return 0;
        }
}
int weight_check_delete(ProductInfo product)
{
        current_product_weight=former_weight-weight;
        product.productWeight=charArrayToU8((const char*)product.productWeightStr);
        if((current_product_weight<=product.productWeight+20)&&(current_product_weight>=product.productWeight-20))
        {
            return 1;
        }
        else
        {
            return 0;
        }
}








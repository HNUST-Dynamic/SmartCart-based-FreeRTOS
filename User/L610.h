/*
 * L610.c
 *
 *      Created on      :2024年3月22日
 *      Author          :潘泊名
 *      Version         :V1.0
 *      Description     :FibocomL610接口库,本版本为第一版，稍显粗糙，主要缺陷以及可改进点如下：
 *                          1.猜测由于串口打印的局限性，无法显示打印出来的浮点数字，即便是打印固定浮点数。
 *                            因此需要在函数外部调试所转换的浮点数是否正确，如果不正确，建议另外编写字符串型转浮点型的函数。
 *                          2.由于工时较短，本版本尚不具有鲁棒性（即健壮性）计划未来在V2中增强。
 *                          3.本项目计划开源，因此从第一版开始应规划它的易读性，在未来版本中将进行大量注释，以及VSCode
 *                            可识别可导出的解释文档，并在项目目录中添加README.md文件
 *
 *      !WARNING!       :1.此文件中的所有Delay的时长不要修改，等待最后优化时期统一修改；
 *                       2.本接口只接收了Price和Weight的字符串格式，后期使用浮点格式请自行编写函数转换，但不要修改原文。
 *                       3.初始化时间很长大概1-2分钟，请耐心等待或用CH340串口收发工具监听L610和CH32之间的通话。
 *                       4.初始化之后不需要再调用  void L610_Init();
 *                                          void L610_Lookup();
 *                                          void L610_RequestIP();
 *                                          void L610_SetAndConnect();
 *                                          void L610_Sub();
 *                         仅调用void L610_Pub(const char* productID);
 *                              ProductInfo L610_Recive();
 *                         即可。
 *
 *
 */

#ifndef USER_L610_H_
#define USER_L610_H_

#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

// 假设最大接收长度为100
//#define MAX_STRING_LENGTH 100

extern char *strx;
extern char *strstr(const char *, const char *);
extern char USART_Rbuffer[2048];
extern uint16_t USART_Rbuffer_Num;
extern char *endptr;
extern int len;
extern int number;

//返回的商品信息结构体
#define MAX_PRODUCTS 100 //规定最多可以储存100个商品信息
//typedef struct {
//    char productID[MAX_STRING_LENGTH+1];
//    float productPrice;
//    char productName[MAX_STRING_LENGTH+1];
//    float productWeight;
//    char productPriceStr[MAX_STRING_LENGTH];
//    char productWeightStr[MAX_STRING_LENGTH];
//    struct ProductInfo *next;
//} ProductInfo;

//extern ProductInfo products[MAX_PRODUCTS];

void L610_Init();
void L610_Lookup();
void L610_RequestIP();
void L610_SetAndConnect();
void L610_Sub();
void L610_Pub(const char* productID,const char* AddorDelete);
ProductInfo L610_Recive();

#endif /* USER_L610_H_ */

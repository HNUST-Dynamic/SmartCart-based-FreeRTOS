/*
 * pages.c
 *
 *  Created on: 2024年4月7日
 *      Author: noneo
 */
#include "./BSP/LCD/lcd.h"
#include "pages.h"
#include "./SYSTEM/delay/delay.h"
#include "stdlib.h"
#include <stdio.h>
#include "L610.h"
#include "structures.h"
#include "allshow.h"
/*
 * @brief:渲染主页面
 * @param:NULL
 * @return:NULL
 */
#define MAX_STRING_LENGTH 100
#define productId productID
#define productPrices productPrice



//extern struct ProductInfo product;
//extern struct ProductInfoList List;


void renderMainPage()
{
    LCD_Clear(BLACK);
    POINT_COLOR=WHITE;
    LCD_Color_Fill(40,24,760,456,GRAY);
    LCD_DrawLine(20,24,20,456);
    LCD_DrawLine(40,476,760,476);
    LCD_DrawLine(40,4,760,4);
    LCD_DrawLine(780,24,780,456);
    LCD_DrawRectangle(40,24,760,456);
    LCD_Draw_Circle(40,24,20);
    LCD_Draw_Circle(40,456,20);
    LCD_Draw_Circle(760,456,20);
    LCD_Draw_Circle(760,24,20);
    //LCD_Color_Fill(40,24,760,456,GRAY);
    LCD_ShowString(250,40,18*BIGCHAR,32,32,"SMART SHOPPINGCART");

    LCD_Color_Fill(60,166,270,286,LGRAY );
    LCD_Color_Fill(295,166,505,286,LGRAY );
    LCD_Color_Fill(530,166,740,286,LGRAY );
    LCD_Color_Fill(60,311,270,431,LGRAY );
    LCD_Color_Fill(295,311,505,431,LGRAY );
    LCD_Color_Fill(530,311,740,431,LGRAY );


    LCD_ShowString(100,200,5*BIGCHAR,32,32,"A:Add");
    LCD_ShowString(320,200,8*BIGCHAR,32,32,"B:Delete");
    LCD_ShowString(570,200,5*BIGCHAR,32,32,"C:Add");
    LCD_ShowString(600,240,5*BIGCHAR,32,32,"Fruit");
    LCD_ShowString(100,345,9*BIGCHAR,32,32,"D:Delete");
    LCD_ShowString(130,385,5*BIGCHAR,32,32,"Fruit");
    LCD_ShowString(320,345,6*BIGCHAR,32,32,"E:Back");
    LCD_ShowString(570,345,6*BIGCHAR,32,32,"F:Pay");

}
void Pages_add()
{
        LCD_Clear(BLACK);
        POINT_COLOR=WHITE;
        LCD_Color_Fill(40,24,760,456,GRAY);
        LCD_DrawLine(20,24,20,456);
        LCD_DrawLine(40,476,760,476);
        LCD_DrawLine(40,4,760,4);
        LCD_DrawLine(780,24,780,456);
        LCD_DrawRectangle(40,24,760,456);
        LCD_Draw_Circle(40,24,20);
        LCD_Draw_Circle(40,456,20);
        LCD_Draw_Circle(760,456,20);
        LCD_Draw_Circle(760,24,20);
        //LCD_Color_Fill(40,24,760,456,GRAY);
        LCD_ShowString(250,100,11*BIGCHAR,32,32,"Please show");

}
void Pages_X_add(ProductInfo product)
{

    LCD_Clear(BROWN);
    LCD_Color_Fill(200,120,600,240,LGRAY );
    LCD_ShowString(200, 180, (strlen((const char *)product.productName))*BIGCHAR, 32, 32,(u8*) product.productName);
    char priceStr[MAX_STRING_LENGTH]; // 用于存储 productPrice 的字符串表示
    snprintf(priceStr, sizeof(priceStr), "%.2f", product.productPrices); // 将浮点数转换为字符串，保留两位小数
    LCD_ShowString(200, 200, 5*BIGCHAR, 32, 32,(u8*) priceStr);
    delay_ms(4000);
    renderMainPage();
}
void Pages_delete()
{
    LCD_Clear(BLACK);
    POINT_COLOR=WHITE;
    LCD_Color_Fill(40,24,760,456,GRAY);
    LCD_DrawLine(20,24,20,456);
    LCD_DrawLine(40,476,760,476);
    LCD_DrawLine(40,4,760,4);
    LCD_DrawLine(780,24,780,456);
    LCD_DrawRectangle(40,24,760,456);
    LCD_Draw_Circle(40,24,20);
    LCD_Draw_Circle(40,456,20);
    LCD_Draw_Circle(760,456,20);
    LCD_Draw_Circle(760,24,20);
    //LCD_Color_Fill(40,24,760,456,GRAY);
     LCD_ShowString(250,40,11*BIGCHAR,32,32,"Please show");

}
void Pages_X_delete(ProductInfo product)
{

    LCD_Clear(WHITE);
    LCD_Color_Fill(200,120,600,240,LGRAY );
    LCD_ShowString(200, 180, (strlen((const char *)product.productName))*BIGCHAR, 32, 32,(u8*) product.productName);
    char priceStr[MAX_STRING_LENGTH]; // 用于存储 productPrice 的字符串表示
    snprintf(priceStr, sizeof(priceStr), "%.2f", product.productPrices); // 将浮点数转换为字符串，保留两位小数
    LCD_ShowString(200, 200, 5*BIGCHAR, 32, 32,(u8*) priceStr);
}

//void Pages_Back()
//{
//    LCD_Clear(GRAY);
//    renderCurrentProductsPage();
//    delay_ms(2000);
//    renderMainPage();
//}
void Pages_Pay()
{
    LCD_Clear(WHITE);
    LCD_Color_Fill(200,120,600,240,GRAY );
    LCD_ShowString(250, 180,10*BIGCHAR , 32, 32, "PLEASE PAY");
    LCD_ShowString(300, 400,7*BIGCHAR,32,32, "QR CODE");
}
/*
 *@brief:预留的添加商品页面，还没开始写
 *@param:NULL
 *@return:NULL
 */
//void renderAddComPage()
//{

//}
/*
 *@brief:本页面为测试页面
 *@param:ID:        传入的商品对象的ID成员
 *       name:      传入的商品对象的name成员
 *       priceStr:  传入的商品对象的priceStr成员
 *       weightStr: 传入的商品对象的weightStr成员
 *@return:NULL
 */
//void renderTestPage(const char* ID,const char* name,const char* priceStr,const char* weightStr)
//{
//
//    LCD_ShowString(250,72,sizeof(ID)*BIGCHAR,32,32,ID);
//    LCD_ShowString(250,104,sizeof(name)*BIGCHAR,32,32,name);
//    LCD_ShowString(250,136,sizeof(priceStr)*BIGCHAR,32,32,priceStr);
//    LCD_ShowString(250,178,sizeof(weightStr)*BIGCHAR,32,32,weightStr);
//}
// 渲染链表中的商品信息
void renderCurrentProductsPage(ProductInfoList *list)
{
    uint8_t Size = list->size;
    int i;
    ProductInfo *current = list->head;
    char buffer[256];  // 临时字符串缓冲区，用于格式化信息
    LCD_Clear(BLACK);
    while (Size > 10) {
        for (i = 1; i <= 10 && current != NULL; i++) {
            snprintf(buffer, sizeof(buffer), "Name: %s", current->productName);
            LCD_ShowString(PRODUCTNAME_X_START, LIST_Y_START + i * 35, strlen(buffer) * BIGCHAR, 32, 32, buffer);
            snprintf(buffer, sizeof(buffer), "Num: %d", current->productNum);
            LCD_ShowString(PRODUCTNUM_X_START, LIST_Y_START + i * 35, strlen(buffer) * BIGCHAR, 32, 32, "1");
            snprintf(buffer, sizeof(buffer), "Price: %s", current->productPriceStr);
            LCD_ShowString(PRODUCTPRICE_X_START, LIST_Y_START + i * 35, strlen(buffer) * BIGCHAR, 32, 32, buffer);

            current = current->next;
        }
        Size -= 10;
    }

    if (Size > 0) {
        for (i = 1; i <= Size && current != NULL; i++) {
            snprintf(buffer, sizeof(buffer), "Name: %s", current->productName);
            LCD_ShowString(PRODUCTNAME_X_START, LIST_Y_START + i * 35, strlen(buffer) * BIGCHAR, 32, 32, buffer);
            snprintf(buffer, sizeof(buffer), "Num: %d", current->productNum);
            LCD_ShowString(PRODUCTNUM_X_START, LIST_Y_START + i * 35, strlen(buffer) * BIGCHAR, 32, 32, "1");
            snprintf(buffer, sizeof(buffer), "Price: %s", current->productPriceStr);
            LCD_ShowString(PRODUCTPRICE_X_START, LIST_Y_START + i * 35, strlen(buffer) * BIGCHAR, 32, 32, buffer);

            current = current->next;
        }
    }
}
void Pages_error()
{

    LCD_Clear(WHITE);
    LCD_Color_Fill(200,120,600,240,LGRAY );
    LCD_ShowString(200, 180, 13*BIGCHAR, 32, 32,"weight error!");
    delay_ms(4000);
    renderMainPage();
}

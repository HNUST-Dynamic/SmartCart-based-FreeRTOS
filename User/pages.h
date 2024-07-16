/*
 * pages.h
 *
 *  Created on: 2024年4月7日
 *      Author: noneo
 */

#ifndef USER_PAGES_H_
#define USER_PAGES_H_

#include "./SYSTEM/delay/delay.h"
#include"stdlib.h"
#include"L610.h"
#include"structures.h"
//home page
/*
 * |BUTTON1|BUTTON3|
 * |BUTTON2|BUTTON4|
 *
 * */
//BUTTONs
#define BUTTON12_S_X     150
#define BUTTON12_E_X     390
#define BUTTON34_S_X     410
#define BUTTON34_E_X     650

#define BUTTON13_S_Y     110
#define BUTTON13_E_Y     260

#define BUTTON24_S_Y     290
#define BUTTON24_E_Y     440
//TEXTs
#define TEXT12_X     170
#define TEXT34_X     430
#define TEXT13_Y     170
#define TEXT24_Y     350

#define TITLE_X        390
#define TITLE_Y        50

//current products areas
#define PRODUCTNAME_X_START     50
#define PRODUCTNUM_X_START      250
#define PRODUCTPRICE_X_START    500
#define LIST_Y_START            110
#define LIST_Y_END              440

extern uint8_t Size;

void renderMainPage();
void renderAddComPage();
void renderTestPage(const char* ID,const char* name,const char* priceStr,const char* weightStr);
void Pages_add();
void Pages_X_add(ProductInfo product);
void Pages_delete();
void Pages_X_delete(ProductInfo product);
void Pages_Back();
void Pages_Pay();
void renderCurrentProductsPage(ProductInfoList *list);
void Pages_error();
#endif /* USER_PAGES_H_ */

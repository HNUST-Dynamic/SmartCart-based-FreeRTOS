#ifndef __KEY_H
#define __KEY_H

#include "./SYSTEM/sys/sys.h"

extern volatile uint8_t Key_Num;

void key_init(void);                    /* 按键初始化函数 */
uint8_t key_scan();         /* 按键扫描函数 */

#endif








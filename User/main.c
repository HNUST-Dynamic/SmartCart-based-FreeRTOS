#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LCD/lcd.h"
#include "./MALLOC/malloc.h"
#include "freertos_demo.h"
#include "L610.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);     /* 中断优先级分组2 */
    delay_init(144);                                    /* 延时初始化 */
    USARTx_Init();                                 /* 串口初始化为115200 */
    //my_mem_init(SRAMIN);                                /* 初始化内部SRAM内存池 */

    LCD_Reset_GPIO_Init();                              /*初始化LCD*/
    GPIO_ResetBits(GPIOA,GPIO_Pin_15);
    delay_ms(100);
    GPIO_SetBits(GPIOA,GPIO_Pin_15);
    LCD_Init();
    
   
    freertos_demo();                                    /* 运行FreeRTOS */
}



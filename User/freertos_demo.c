#include "freertos_demo.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LCD/lcd.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "pages.h"
#include "L610.h"
#include "./SYSTEM/usart/usart.h"

#define USART_RBUFFER_SIZE  1024
/******************************************************************************************************/
/* FreeRTOS配置 */

/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  256                 /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */

/* TASK1 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK1_PRIO      2                   /* 任务优先级 */
#define TASK1_STK_SIZE  256                 /* 任务堆栈大小 */
TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
void task1(void *pvParameters);             /* 任务函数 */

/* TASK2 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK2_PRIO      2                   /* 任务优先级 */
#define TASK2_STK_SIZE  256                 /* 任务堆栈大小 */
TaskHandle_t            vSerialTask_Handler;  /* 任务句柄 */
void vSerialTask(void *pvParameters);             /* 任务函数 */

/* TASK3 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK3_PRIO      2                   /* 任务优先级 */
#define TASK3_STK_SIZE  256                 /* 任务堆栈大小 */
TaskHandle_t            vLookupTask_Handler;  /* 任务句柄 */
void vLookupTask(void *pvParameters);             /* 任务函数 */

/******************************************************************************************************/

/* LCD刷屏时使用的颜色 */
uint16_t lcd_discolor[11] = {WHITE, BLACK, BLUE, RED,
                             MAGENTA, GREEN, CYAN, YELLOW,
                             BROWN, BRRED, GRAY};

/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
 */
void freertos_demo(void)
{
    xQueue = xQueueCreate(USART_RBUFFER_SIZE, sizeof(uint8_t));
    if (xQueue == NULL)
    {
        // 处理队列创建失败
        while (1);
    }

    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */
    vTaskStartScheduler();
}

/**
 * @brief       start_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* 进入临界区 */
        
    renderMainPage();
    /* 创建任务1 */
    xTaskCreate((TaskFunction_t )task1,                 /* 任务函数 */
                (const char*    )"task1",               /* 任务名称 */
                (uint16_t       )TASK1_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )TASK1_PRIO,            /* 任务优先级 */
                (TaskHandle_t*  )&Task1Task_Handler);   /* 任务句柄 */
    /* 创建任务2 */
    xTaskCreate((TaskFunction_t )vSerialTask,                 /* 任务函数 */
                (const char*    )"vSerialTask",               /* 任务名称 */
                (uint16_t       )TASK2_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )TASK2_PRIO,            /* 任务优先级 */
                (TaskHandle_t*  )&vSerialTask_Handler);   /* 任务句柄 */
    /* 创建任务3 */
    xTaskCreate((TaskFunction_t )vLookupTask,                 /* 任务函数 */
                (const char*    )"vLookupTask",               /* 任务名称 */
                (uint16_t       )TASK3_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )TASK3_PRIO,            /* 任务优先级 */
                (TaskHandle_t*  )&vLookupTask_Handler);   /* 任务句柄 */
    vTaskDelete(StartTask_Handler);                     /* 删除开始任务 */
    taskEXIT_CRITICAL();                                /* 退出临界区 */
}

/**
 * @brief       task1
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void task1(void *pvParameters)
{
    
    while (1)
    {
        
        
        
    }
}

/**
 * @brief       vSerialTask
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void vSerialTask(void *pvParameters)
{
    uint8_t receivedData;
    while (1)
    {
        // 从队列中接收数据（阻塞）
        if (xQueueReceive(xQueue, &receivedData, portMAX_DELAY) == pdPASS)
        {
            // 将数据存储到缓冲区
            if (USART_Rbuffer_Num < USART_RBUFFER_SIZE)
            {
                USART_Rbuffer[USART_Rbuffer_Num++] = receivedData;
            }
        }
    }
}

/**
 * @brief       vLookupTask
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void vLookupTask(void *pvParameters)
{    
    L610_Init();
    L610_Lookup();
    L610_RequestIP();
    L610_SetAndConnect();
    L610_Sub();
    L610_Pub("apple","delete");
    L610_Recive();

    vTaskDelete(NULL); // 删除任务
}

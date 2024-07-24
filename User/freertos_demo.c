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
#include <ctype.h>
#include "structures.h"
#include "allshow.h"
#include "HX77.h"

#define USART_RBUFFER_SIZE  1536
/******************************************************************************************************/
/* FreeRTOS配置 */

/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  64                 /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */

/* CameraRev 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define CAMERA_REV_PRIO      2                   /* 任务优先级 */
#define CAMERA_REV_STK_SIZE  200                 /* 任务堆栈大小 */
TaskHandle_t            CameraRev_Handler;  /* 任务句柄 */
void vCameraRev(void *pvParameters);             /* 任务函数 */

/* SerialTask 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define SERIAL_TASK_PRIO      2                   /* 任务优先级 */
#define SERIAL_TASK_STK_SIZE  96                 /* 任务堆栈大小 */
TaskHandle_t            SerialTask_Handler;  /* 任务句柄 */
void vSerialTask(void *pvParameters);             /* 任务函数 */

/* LookupTask 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define LOOKUP_TASK_PRIO      2                   /* 任务优先级 */
#define LOOKUP_TASK_STK_SIZE  96                 /* 任务堆栈大小 */
TaskHandle_t            LookupTask_Handler;  /* 任务句柄 */
void vLookupTask(void *pvParameters);             /* 任务函数 */

/* KeyScan 任务配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define KEYSCAN_TASK_PRIO      2                   /* 任务优先级 */
#define KEYSCAN_TASK_STK_SIZE  600                 /* 任务堆栈大小 */
TaskHandle_t            KeyScanTask_Handler;  /* 任务句柄 */
void vKeyScanTask(void *pvParameters);             /* 任务函数 */

/* WeightTask 任务配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define WEIGHT_TASK_PRIO      2                   /* 任务优先级 */
#define WEIGHT_TASK_STK_SIZE  64                 /* 任务堆栈大小 */
TaskHandle_t            WeightTask_Handler;  /* 任务句柄 */
void vWeightTask(void *pvParameters);             /* 任务函数 */

/******************************************************************************************************/

/*全局变量*/
#define GapValue 270
ProductInfoList ProductList;//商品列表

/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
 */
void freertos_demo(void)
{
    xBinarySemaphore = xSemaphoreCreateBinary();//创建二值信号量并传给句柄
    xBinarySemaphore2 = xSemaphoreCreateBinary();//add
    xBinarySemaphore3 = xSemaphoreCreateBinary();
    xBinarySemaphore4 = xSemaphoreCreateBinary(); 
    xBinarySemaphore5 = xSemaphoreCreateBinary();//delete
    // 检查是否成功创建信号量
    if (xBinarySemaphore == NULL||xBinarySemaphore2 == NULL)
    {
        printf("创建二值信号量失败\r\n");
    }
    xQueue1 = xQueueCreate(32, sizeof(uint8_t));
    xQueue2 = xQueueCreate(USART_RBUFFER_SIZE, sizeof(uint8_t));
    xQueue3 = xQueueCreate(1, sizeof(ProductInfo));
    xQueue4 = xQueueCreate(1, sizeof(ProductInfo));
    if (xQueue1 == NULL|| xQueue2 == NULL|| xQueue3 == NULL || xQueue4 == NULL)
    {
        // 处理队列创建失败
        while (1)
        {
            printf("创建队列失败\r\n");
        }
    }
    initProductList(&ProductList);

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
    /* 创建广和通L610串口消息队列任务 */
    xTaskCreate((TaskFunction_t )vSerialTask,                   /* 任务函数 */
                (const char*    )"SerialTask",                  /* 任务名称 */
                (uint16_t       )SERIAL_TASK_STK_SIZE,          /* 任务堆栈大小 */
                (void*          )NULL,                          /* 传入给任务函数的参数 */
                (UBaseType_t    )SERIAL_TASK_PRIO,              /* 任务优先级 */
                (TaskHandle_t*  )&SerialTask_Handler);          /* 任务句柄 */
    /* 创建广和通L610初始化任务 */
    xTaskCreate((TaskFunction_t )vLookupTask,                   /* 任务函数 */
                (const char*    )"LookupTask",                  /* 任务名称 */
                (uint16_t       )LOOKUP_TASK_STK_SIZE,          /* 任务堆栈大小 */
                (void*          )NULL,                          /* 传入给任务函数的参数 */
                (UBaseType_t    )LOOKUP_TASK_PRIO,              /* 任务优先级 */
                (TaskHandle_t*  )&LookupTask_Handler);          /* 任务句柄 */
    
    //创建摄像头任务
    xTaskCreate((TaskFunction_t )vCameraRev,                    /* 任务函数 */
                (const char*    )"CameraRev",                   /* 任务名称 */
                (uint16_t       )CAMERA_REV_STK_SIZE,           /* 任务堆栈大小 */
                (void*          )NULL,                          /* 传入给任务函数的参数 */
                (UBaseType_t    )CAMERA_REV_PRIO,               /* 任务优先级 */
                (TaskHandle_t*  )&CameraRev_Handler);           /* 任务句柄 */
    vTaskSuspend(CameraRev_Handler);


    vTaskDelete(StartTask_Handler);                             /* 删除开始任务 */
    taskEXIT_CRITICAL();                                        /* 退出临界区 */


}

/**
 * @brief       vKeyScanTask
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void vKeyScanTask(void *pvParameters)
{
    printf("Key scan\r\n");
    ProductInfo receivedProduct;
    while(1)
    {
        //按键扫描
        Key_Num=key_scan();

        switch(Key_Num)
        {
            case 1://添加商品
                //渲染扫描提示
                Pages_add();

                vTaskResume(CameraRev_Handler);

                // 等待信号量
                if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE)
                {
                    //信号量被成功获取
                    //从队列中读取product
                    if (xQueueReceive(xQueue3, &receivedProduct, portMAX_DELAY) == pdPASS)
                    {
                        // 处理接收到的 receivedProduct
                        L610_Pub(receivedProduct.productID,"delete");
                        vTaskDelay(3000);
                        receivedProduct = L610_Recive();
                        printf("%s\r\n",receivedProduct.productName);

                        // char taskListBuffer[512];
                        // vTaskList(taskListBuffer);
                        // printf("Task List:\n%s", taskListBuffer);

                        xQueueSend(xQueue4,&receivedProduct,portMAX_DELAY);
                        xSemaphoreGive(xBinarySemaphore2);
                    }
                    Pages_X_add(receivedProduct);
                    vTaskDelay(1000);
                    xSemaphoreGive(xBinarySemaphore3);
                    insertProduct(&ProductList,receivedProduct);

                    if(xSemaphoreTake(xBinarySemaphore4,portMAX_DELAY)==pdTRUE)
                    {
                        renderMainPage();
                    }
                }
                
            break;

            case 2://删除商品
                //渲染扫描提示
                Pages_delete();

                vTaskResume(CameraRev_Handler);

                // 等待信号量
                if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE)
                {
                    //信号量被成功获取
                    //从队列中读取product
                    if (xQueueReceive(xQueue3, &receivedProduct, portMAX_DELAY) == pdPASS)
                    {
                        // 处理接收到的 receivedProduct
                        L610_Pub(receivedProduct.productID,"add");
                        vTaskDelay(2000);
                        receivedProduct = L610_Recive();
                        xQueueSend(xQueue4,&receivedProduct,portMAX_DELAY);
                        xSemaphoreGive(xBinarySemaphore5);
                    }
                    Pages_X_delete(receivedProduct);
                    vTaskDelay(1000);
                    xSemaphoreGive(xBinarySemaphore3);
                    deleteProduct(&ProductList,receivedProduct.productID);
                    if(xSemaphoreTake(xBinarySemaphore4,portMAX_DELAY)==pdTRUE)
                    {
                        renderMainPage();
                    }
                }
            break;

            case 3://返回
                //渲染主页面
                renderMainPage();
                break;

            case 4://展示全部
                renderCurrentProductsPage(&ProductList);
                break;

            case 5:
                break;

            case 6:
                break;

            default:break;
        }
    }
    
}

/**
 * @brief       vCameraRev
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void vCameraRev(void *pvParameters)
{
    uint8_t received_data;
    ProductInfo product;
    while (1)
    {
        
        USART_Cmd(USART1,ENABLE);
        if (xQueueReceive(xQueue1, &received_data, portMAX_DELAY) == pdPASS)
        {
            if(isalpha(received_data))
            {
                if (uart_cnt < sizeof(uart_buf) / sizeof(uart_buf[0]))                      // 检查缓冲区溢出
                {
                    uart_buf[uart_cnt++] = received_data;                                   // 将接收到的数据存储在缓冲区中
                }
            }
            if(received_data=='\n')                                                         // 检查是否接收到换行符
            {
                
                strncpy(product.productID, (char*)uart_buf, sizeof(product.productID) - 1); //将接收到的ID赋值给product
                product.productID[sizeof(product.productID) - 1] = '\0';                    //确保字符串以空字符结尾
                
                xQueueSend(xQueue3,&product,portMAX_DELAY);                                 //将product通过队列传出去
                xSemaphoreGive(xBinarySemaphore);                                           //释放信号量
                uart_cnt = 0;                                                               //清除缓冲区
                memset(uart_buf,0,sizeof(uart_buf));
                USART_Cmd(USART1,DISABLE);                                                  //接收完删除任务
                vTaskSuspend(CameraRev_Handler);                
            }
        }
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
        if (xQueueReceive(xQueue2, &receivedData, portMAX_DELAY) == pdPASS) // 从队列中接收数据（阻塞）
        {
            if (USART_Rbuffer_Num < USART_RBUFFER_SIZE)                     // 将数据存储到缓冲区
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
    

    /* 创建按键扫描任务 */
    xTaskCreate((TaskFunction_t )vKeyScanTask,                  /* 任务函数 */
                (const char*    )"KeyScanTask",                 /* 任务名称 */
                (uint16_t       )KEYSCAN_TASK_STK_SIZE,         /* 任务堆栈大小 */
                (void*          )NULL,                          /* 传入给任务函数的参数 */
                (UBaseType_t    )KEYSCAN_TASK_PRIO,             /* 任务优先级 */
                (TaskHandle_t*  )&KeyScanTask_Handler);         /* 任务句柄 */
    
    xTaskCreate((TaskFunction_t )vWeightTask,                  /* 任务函数 */
                (const char*    )"WeightTask",                 /* 任务名称 */
                (uint16_t       )WEIGHT_TASK_STK_SIZE,         /* 任务堆栈大小 */
                (void*          )NULL,                          /* 传入给任务函数的参数 */
                (UBaseType_t    )WEIGHT_TASK_PRIO,             /* 任务优先级 */
                (TaskHandle_t*  )&WeightTask_Handler);         /* 任务句柄 */

    vTaskDelete(NULL);                             // 删除任务
}

/**
 * @brief       vWeightTask
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void vWeightTask(void *pvParameters)
{

    HX711_GPIO_Init();
    uint32_t pi=HX711_ReadData();
    uint32_t Weight,FormerWeight;
    ProductInfo weightProduct;
    while(1)
    {
        Weight=HX711_ReadData();
        while(Weight>=15000000)
        {
            Weight=HX711_ReadData();
        }
        Weight=(Weight-pi)/GapValue;
        // 等待信号量
        if (xSemaphoreTake(xBinarySemaphore2, portMAX_DELAY) == pdTRUE)
        {
            //信号量被成功获取
            //从队列中读取product
            if (xQueueReceive(xQueue4, &weightProduct, portMAX_DELAY) == pdPASS)
            {
                if(!weight_check_add(weightProduct))
                {
                    if(xSemaphoreTake(xBinarySemaphore3,portMAX_DELAY) == pdTRUE)
                    {
                        Pages_error();
                        vTaskDelay(1000);
                    } 
                }
                FormerWeight=Weight;
                xSemaphoreGive(xBinarySemaphore4);
            }
        }
        else if (xSemaphoreTake(xBinarySemaphore5, portMAX_DELAY) == pdTRUE)
        {
            //信号量被成功获取
            //从队列中读取product
            if (xQueueReceive(xQueue4, &weightProduct, portMAX_DELAY) == pdPASS)
            {
                if(!weight_check_delete(weightProduct))
                {
                    if(xSemaphoreTake(xBinarySemaphore3,portMAX_DELAY) == pdTRUE)
                    {
                        Pages_error();
                        vTaskDelay(1000);
                    } 
                }
                FormerWeight=Weight;
                xSemaphoreGive(xBinarySemaphore4);
            }
        }
    }
}

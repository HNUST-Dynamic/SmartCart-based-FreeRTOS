/********************************** (C) COPYRIGHT *******************************
* File Name          : lcd.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2024/03/05
* Description        : This file contains the headers of the TFTLCD.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "lcd.h"
#include"stdlib.h"
#include "font.h"
#include "./SYSTEM/usart/usart.h"
/* LCD brush and background colors */
u16 POINT_COLOR=0x0000;
u16 BACK_COLOR=0xFFFF;
  
_lcd_dev lcddev;
	 

void LCD_Reset_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_15);
}

/*********************************************************************
 * @fn      LCD_WR_REG
 *
 * @brief   Write register
 *
 * @param   regval - register value
 *
 * @return  none
 */
void LCD_WR_REG(u16 regval)
{   
    //regval=regval;
	LCD->LCD_REG=regval;
}

/*********************************************************************
 * @fn      LCD_WR_DATA
 *
 * @brief   Write data
 *
 * @param   data
 *
 * @return  none
 */
void LCD_WR_DATA(u16 data)
{	 
    //data=data;
	LCD->LCD_RAM=data;		 
}

/*********************************************************************
 * @fn      LCD_RD_DATA
 *
 * @brief   Read data
 *
 * @return  ram - read data
 */
u16 LCD_RD_DATA(void)
{
	vu16 ram;
	ram=LCD->LCD_RAM;	
	return ram;	 
}					   

/*********************************************************************
 * @fn      LCD_WriteReg
 *
 * @brief   Write value to register
 *
 * @param   LCD_Reg - register addr
 *          LCD_RegValue - value
 *
 * @return  none
 */
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;
	LCD->LCD_RAM = LCD_RegValue;
}	   

/*********************************************************************
 * @fn      LCD_ReadReg
 *
 * @brief   Read value from register
 *
 * @param   LCD_Reg - register addr
 *
 * @return  register value
 */
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);
	delay_us(5);		  
	return LCD_RD_DATA();
}   

/*********************************************************************
 * @fn      LCD_WriteRAM_Prepare
 *
 * @brief   Write GRAM prepare
 *
 * @return  none
 */
void LCD_WriteRAM_Prepare(void)
{
 	LCD->LCD_REG=lcddev.wramcmd;	  
}	 

/*********************************************************************
 * @fn      LCD_WriteRAM
 *
 * @brief   Write GRAM
 *
 * @param   RGB_Code - colour value
 *
 * @return  none
 */
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD->LCD_RAM = RGB_Code;
}

/*********************************************************************
 * @fn      LCD_SetCursor
 *
 * @brief   set Cursor
 *
 * @param   Xpos - Abscissa
 *          Ypos - Ordinate
 *
 * @return  none
 */
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
    LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(Xpos>>8);
    LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(Xpos&0XFF);
    LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(Ypos>>8);
    LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(Ypos&0XFF);
} 		 

/*********************************************************************
 * @fn      LCD_Scan_Dir
 *
 * @brief   set scan direction
 *
 * @param   dir - direction
 *
 * @return  none
 */
void LCD_Scan_Dir(void) {
    u16 regval = 0;
    u16 dirreg = 0;
    uint16_t twidth, theight;
    uint16_t sx=0;
    uint16_t sy=0;
    twidth = sx + lcddev.width - 1;
    theight = sy + lcddev.height - 1;

    //u16 temp;

    // "Set display orientation register value."
    //regval |= (0 << 7) | (0 << 6) | (0 << 5);//从左到右，从上到下
    //regval |= (1 << 7) | (0 << 6) | (0 << 5);/* 从左到右,从下到上 */
    //regval |= (0 << 7) | (1 << 6) | (0 << 5);/* 从右到左,从上到下 */
    //regval |= (1 << 7) | (1 << 6) | (0 << 5);/* 从右到左,从下到上 */
    //regval |= (0 << 7) | (0 << 6) | (1 << 5);/* 从上到下,从左到右 */
    regval |= (0 << 7) | (1 << 6) | (1 << 5);/* 从上到下,从右到左 */
    //regval |= (1 << 7) | (0 << 6) | (1 << 5);/* 从下到上,从左到右 */
    //regval |= (1 << 7) | (1 << 6) | (1 << 5);/* 从下到上,从右到左 */
    dirreg = 0X3600;
    regval |= 0X08;

    // "Write to display orientation register."
    LCD_WriteReg(dirreg, regval);

    // "Set pixel display range."
    LCD_WR_REG(lcddev.setxcmd);
    LCD_WR_DATA(sx >> 8);
    LCD_WR_REG(lcddev.setxcmd + 1);
    LCD_WR_DATA(sx & 0xFF);
    LCD_WR_REG(lcddev.setxcmd + 2);
    LCD_WR_DATA(twidth >> 8);
    LCD_WR_REG(lcddev.setxcmd + 3);
    LCD_WR_DATA(twidth & 0xFF);
    LCD_WR_REG(lcddev.setycmd);
    LCD_WR_DATA(sy >> 8);
    LCD_WR_REG(lcddev.setycmd + 1);
    LCD_WR_DATA(sy & 0xFF);
    LCD_WR_REG(lcddev.setycmd + 2);
    LCD_WR_DATA(theight >> 8);
    LCD_WR_REG(lcddev.setycmd + 3);
    LCD_WR_DATA(theight & 0xFF);
}

/*********************************************************************
 * @fn      LCD_Display_Dir
 *
 * @brief   set display direction
 *
 * @param   dir - direction
 *
 * @return  none
 */
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)
	{
		lcddev.dir=0;
		lcddev.width=480;
		lcddev.height=800;
		lcddev.wramcmd=0X2C00;
	 	lcddev.setxcmd=0X2A00;
		lcddev.setycmd=0X2B00;
	}
	else
	{	  				
		lcddev.dir=1;
		lcddev.width=800;
		lcddev.height=480;
		lcddev.wramcmd=0X2C00;
	 	lcddev.setxcmd=0X2A00;
		lcddev.setycmd=0X2B00;
	} 
	LCD_Scan_Dir();
}	 

/*********************************************************************
 * @fn      LCD_Init
 *
 * @brief   Init LCD
 *
 * @return  none
 */
void LCD_Init(void)
{ 					
 	GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure); 

    /*   RS:PG0___PD12  */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* CS: PG12___PD11*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOD,GPIO_Pin_11);

    readWriteTiming.FSMC_AddressSetupTime = 0x01;
    readWriteTiming.FSMC_AddressHoldTime = 0x00;
    readWriteTiming.FSMC_DataSetupTime = 0x0f;
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

    writeTiming.FSMC_AddressSetupTime = 0x00;
    writeTiming.FSMC_AddressHoldTime = 0x00;
    writeTiming.FSMC_DataSetupTime = 0x03;
    writeTiming.FSMC_BusTurnAroundDuration = 0x00;
    writeTiming.FSMC_CLKDivision = 0x00;
    writeTiming.FSMC_DataLatency = 0x00;
    writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
 
	delay_ms(50);
  	lcddev.id=LCD_ReadReg(0x0000);
  	LCD_WR_REG(0XD3);
	lcddev.id=LCD_RD_DATA();	//dummy read
 	lcddev.id=LCD_RD_DATA();
  	lcddev.id=LCD_RD_DATA();
 	lcddev.id<<=8;
	lcddev.id|=LCD_RD_DATA();

    //尝试9341 ID的读取
    LCD_WR_REG(0XD3);
    lcddev.id = LCD_RD_DATA();  //dummy read
    lcddev.id = LCD_RD_DATA();  //读到0X00
    lcddev.id = LCD_RD_DATA();      //读取93
    lcddev.id <<= 8;
    lcddev.id |= LCD_RD_DATA();     //读取41

    if (lcddev.id != 0X9341)        //非9341,尝试看看是不是NT35310
    {
        LCD_WR_REG(0X04);
        lcddev.id = LCD_RD_DATA();      //dummy read
        lcddev.id = LCD_RD_DATA();      //读到0X85
        lcddev.id = LCD_RD_DATA();      //读取0X85
        lcddev.id <<= 8;
        lcddev.id |= LCD_RD_DATA();     //读取0X52

        if (lcddev.id == 0X8552)        //将8552的ID转换成7789
        {
            lcddev.id = 0x7789;
        }

        if (lcddev.id != 0x7789)        //也不是ST7789, 尝试是不是 NT35310
        {
            LCD_WR_REG(0XD4);
            lcddev.id = LCD_RD_DATA(); //dummy read
            lcddev.id = LCD_RD_DATA(); //读回0X01
            lcddev.id = LCD_RD_DATA(); //读回0X53
            lcddev.id <<= 8;
            lcddev.id |= LCD_RD_DATA(); //这里读回0X10

            if (lcddev.id != 0X5310)    //也不是NT35310,尝试看看是不是NT35510
            {
                LCD_WR_REG(0XD3);
                lcddev.id = LCD_RD_DATA();  /* dummy read */
                lcddev.id = LCD_RD_DATA();  /* 读到0X00 */
                lcddev.id = LCD_RD_DATA();  /* 读取0X77 */
                lcddev.id <<= 8;
                lcddev.id |= LCD_RD_DATA(); /* 读取0X96 */

                if (lcddev.id != 0x7796)    /* 也不是ST7796,尝试看看是不是NT35510 */
                {
                    //发送秘钥（厂家提供,照搬即可）
                    LCD_WriteReg(0xF000, 0x0055);
                    LCD_WriteReg(0xF001, 0x00AA);
                    LCD_WriteReg(0xF002, 0x0052);
                    LCD_WriteReg(0xF003, 0x0008);
                    LCD_WriteReg(0xF004, 0x0001);

                    LCD_WR_REG(0xC500);             //读取ID高8位
                    lcddev.id = LCD_RD_DATA();      //读回0X55
                    lcddev.id <<= 8;

                    LCD_WR_REG(0xC501);             //读取ID低8位
                    lcddev.id |= LCD_RD_DATA();     //读回0X10
                    delay_ms(5);

                    if (lcddev.id != 0X5510)        //也不是NT5510,尝试看看是不是SSD1963
                    {
                        LCD_WR_REG(0XD3);
                        lcddev.id = LCD_RD_DATA();  /* dummy read */
                        lcddev.id = LCD_RD_DATA();  /* 读回0X00 */
                        lcddev.id = LCD_RD_DATA();  /* 读回0X98 */
                        lcddev.id <<= 8;
                        lcddev.id |= LCD_RD_DATA(); /* 读回0X06 */

                        if (lcddev.id != 0x9806)    /* 也不是ILI9806,尝试看看是不是SSD1963 */
                        {
                            LCD_WR_REG(0XA1);
                            lcddev.id = LCD_RD_DATA();
                            lcddev.id = LCD_RD_DATA();  //读回0X57
                            lcddev.id <<= 8;
                            lcddev.id |= LCD_RD_DATA(); //读回0X61

                            if (lcddev.id == 0X5761)lcddev.id = 0X1963; //SSD1963读回的ID是5761H,为方便区分,我们强制设置为1963
                        }
                    }
                }
            }
        }
    }
    //printf(" LCD ID:%x\r\n",lcddev.id);
        if (lcddev.id == 0x5510)
        {
            LCD_WriteReg(0xF000, 0x55);
            LCD_WriteReg(0xF001, 0xAA);
            LCD_WriteReg(0xF002, 0x52);
            LCD_WriteReg(0xF003, 0x08);
            LCD_WriteReg(0xF004, 0x01);
            //AVDD Set AVDD 5.2V
            LCD_WriteReg(0xB000, 0x0D);
            LCD_WriteReg(0xB001, 0x0D);
            LCD_WriteReg(0xB002, 0x0D);
            //AVDD ratio
            LCD_WriteReg(0xB600, 0x34);
            LCD_WriteReg(0xB601, 0x34);
            LCD_WriteReg(0xB602, 0x34);
            //AVEE -5.2V
            LCD_WriteReg(0xB100, 0x0D);
            LCD_WriteReg(0xB101, 0x0D);
            LCD_WriteReg(0xB102, 0x0D);
            //AVEE ratio
            LCD_WriteReg(0xB700, 0x34);
            LCD_WriteReg(0xB701, 0x34);
            LCD_WriteReg(0xB702, 0x34);
            //VCL -2.5V
            LCD_WriteReg(0xB200, 0x00);
            LCD_WriteReg(0xB201, 0x00);
            LCD_WriteReg(0xB202, 0x00);
            //VCL ratio
            LCD_WriteReg(0xB800, 0x24);
            LCD_WriteReg(0xB801, 0x24);
            LCD_WriteReg(0xB802, 0x24);
            //VGH 15V (Free pump)
            LCD_WriteReg(0xBF00, 0x01);
            LCD_WriteReg(0xB300, 0x0F);
            LCD_WriteReg(0xB301, 0x0F);
            LCD_WriteReg(0xB302, 0x0F);
            //VGH ratio
            LCD_WriteReg(0xB900, 0x34);
            LCD_WriteReg(0xB901, 0x34);
            LCD_WriteReg(0xB902, 0x34);
            //VGL_REG -10V
            LCD_WriteReg(0xB500, 0x08);
            LCD_WriteReg(0xB501, 0x08);
            LCD_WriteReg(0xB502, 0x08);
            LCD_WriteReg(0xC200, 0x03);
            //VGLX ratio
            LCD_WriteReg(0xBA00, 0x24);
            LCD_WriteReg(0xBA01, 0x24);
            LCD_WriteReg(0xBA02, 0x24);
            //VGMP/VGSP 4.5V/0V
            LCD_WriteReg(0xBC00, 0x00);
            LCD_WriteReg(0xBC01, 0x78);
            LCD_WriteReg(0xBC02, 0x00);
            //VGMN/VGSN -4.5V/0V
            LCD_WriteReg(0xBD00, 0x00);
            LCD_WriteReg(0xBD01, 0x78);
            LCD_WriteReg(0xBD02, 0x00);
            //VCOM
            LCD_WriteReg(0xBE00, 0x00);
            LCD_WriteReg(0xBE01, 0x64);
            //Gamma Setting
            LCD_WriteReg(0xD100, 0x00);
            LCD_WriteReg(0xD101, 0x33);
            LCD_WriteReg(0xD102, 0x00);
            LCD_WriteReg(0xD103, 0x34);
            LCD_WriteReg(0xD104, 0x00);
            LCD_WriteReg(0xD105, 0x3A);
            LCD_WriteReg(0xD106, 0x00);
            LCD_WriteReg(0xD107, 0x4A);
            LCD_WriteReg(0xD108, 0x00);
            LCD_WriteReg(0xD109, 0x5C);
            LCD_WriteReg(0xD10A, 0x00);
            LCD_WriteReg(0xD10B, 0x81);
            LCD_WriteReg(0xD10C, 0x00);
            LCD_WriteReg(0xD10D, 0xA6);
            LCD_WriteReg(0xD10E, 0x00);
            LCD_WriteReg(0xD10F, 0xE5);
            LCD_WriteReg(0xD110, 0x01);
            LCD_WriteReg(0xD111, 0x13);
            LCD_WriteReg(0xD112, 0x01);
            LCD_WriteReg(0xD113, 0x54);
            LCD_WriteReg(0xD114, 0x01);
            LCD_WriteReg(0xD115, 0x82);
            LCD_WriteReg(0xD116, 0x01);
            LCD_WriteReg(0xD117, 0xCA);
            LCD_WriteReg(0xD118, 0x02);
            LCD_WriteReg(0xD119, 0x00);
            LCD_WriteReg(0xD11A, 0x02);
            LCD_WriteReg(0xD11B, 0x01);
            LCD_WriteReg(0xD11C, 0x02);
            LCD_WriteReg(0xD11D, 0x34);
            LCD_WriteReg(0xD11E, 0x02);
            LCD_WriteReg(0xD11F, 0x67);
            LCD_WriteReg(0xD120, 0x02);
            LCD_WriteReg(0xD121, 0x84);
            LCD_WriteReg(0xD122, 0x02);
            LCD_WriteReg(0xD123, 0xA4);
            LCD_WriteReg(0xD124, 0x02);
            LCD_WriteReg(0xD125, 0xB7);
            LCD_WriteReg(0xD126, 0x02);
            LCD_WriteReg(0xD127, 0xCF);
            LCD_WriteReg(0xD128, 0x02);
            LCD_WriteReg(0xD129, 0xDE);
            LCD_WriteReg(0xD12A, 0x02);
            LCD_WriteReg(0xD12B, 0xF2);
            LCD_WriteReg(0xD12C, 0x02);
            LCD_WriteReg(0xD12D, 0xFE);
            LCD_WriteReg(0xD12E, 0x03);
            LCD_WriteReg(0xD12F, 0x10);
            LCD_WriteReg(0xD130, 0x03);
            LCD_WriteReg(0xD131, 0x33);
            LCD_WriteReg(0xD132, 0x03);
            LCD_WriteReg(0xD133, 0x6D);
            LCD_WriteReg(0xD200, 0x00);
            LCD_WriteReg(0xD201, 0x33);
            LCD_WriteReg(0xD202, 0x00);
            LCD_WriteReg(0xD203, 0x34);
            LCD_WriteReg(0xD204, 0x00);
            LCD_WriteReg(0xD205, 0x3A);
            LCD_WriteReg(0xD206, 0x00);
            LCD_WriteReg(0xD207, 0x4A);
            LCD_WriteReg(0xD208, 0x00);
            LCD_WriteReg(0xD209, 0x5C);
            LCD_WriteReg(0xD20A, 0x00);

            LCD_WriteReg(0xD20B, 0x81);
            LCD_WriteReg(0xD20C, 0x00);
            LCD_WriteReg(0xD20D, 0xA6);
            LCD_WriteReg(0xD20E, 0x00);
            LCD_WriteReg(0xD20F, 0xE5);
            LCD_WriteReg(0xD210, 0x01);
            LCD_WriteReg(0xD211, 0x13);
            LCD_WriteReg(0xD212, 0x01);
            LCD_WriteReg(0xD213, 0x54);
            LCD_WriteReg(0xD214, 0x01);
            LCD_WriteReg(0xD215, 0x82);
            LCD_WriteReg(0xD216, 0x01);
            LCD_WriteReg(0xD217, 0xCA);
            LCD_WriteReg(0xD218, 0x02);
            LCD_WriteReg(0xD219, 0x00);
            LCD_WriteReg(0xD21A, 0x02);
            LCD_WriteReg(0xD21B, 0x01);
            LCD_WriteReg(0xD21C, 0x02);
            LCD_WriteReg(0xD21D, 0x34);
            LCD_WriteReg(0xD21E, 0x02);
            LCD_WriteReg(0xD21F, 0x67);
            LCD_WriteReg(0xD220, 0x02);
            LCD_WriteReg(0xD221, 0x84);
            LCD_WriteReg(0xD222, 0x02);
            LCD_WriteReg(0xD223, 0xA4);
            LCD_WriteReg(0xD224, 0x02);
            LCD_WriteReg(0xD225, 0xB7);
            LCD_WriteReg(0xD226, 0x02);
            LCD_WriteReg(0xD227, 0xCF);
            LCD_WriteReg(0xD228, 0x02);
            LCD_WriteReg(0xD229, 0xDE);
            LCD_WriteReg(0xD22A, 0x02);
            LCD_WriteReg(0xD22B, 0xF2);
            LCD_WriteReg(0xD22C, 0x02);
            LCD_WriteReg(0xD22D, 0xFE);
            LCD_WriteReg(0xD22E, 0x03);
            LCD_WriteReg(0xD22F, 0x10);
            LCD_WriteReg(0xD230, 0x03);
            LCD_WriteReg(0xD231, 0x33);
            LCD_WriteReg(0xD232, 0x03);
            LCD_WriteReg(0xD233, 0x6D);
            LCD_WriteReg(0xD300, 0x00);
            LCD_WriteReg(0xD301, 0x33);
            LCD_WriteReg(0xD302, 0x00);
            LCD_WriteReg(0xD303, 0x34);
            LCD_WriteReg(0xD304, 0x00);
            LCD_WriteReg(0xD305, 0x3A);
            LCD_WriteReg(0xD306, 0x00);
            LCD_WriteReg(0xD307, 0x4A);
            LCD_WriteReg(0xD308, 0x00);
            LCD_WriteReg(0xD309, 0x5C);
            LCD_WriteReg(0xD30A, 0x00);

            LCD_WriteReg(0xD30B, 0x81);
            LCD_WriteReg(0xD30C, 0x00);
            LCD_WriteReg(0xD30D, 0xA6);
            LCD_WriteReg(0xD30E, 0x00);
            LCD_WriteReg(0xD30F, 0xE5);
            LCD_WriteReg(0xD310, 0x01);
            LCD_WriteReg(0xD311, 0x13);
            LCD_WriteReg(0xD312, 0x01);
            LCD_WriteReg(0xD313, 0x54);
            LCD_WriteReg(0xD314, 0x01);
            LCD_WriteReg(0xD315, 0x82);
            LCD_WriteReg(0xD316, 0x01);
            LCD_WriteReg(0xD317, 0xCA);
            LCD_WriteReg(0xD318, 0x02);
            LCD_WriteReg(0xD319, 0x00);
            LCD_WriteReg(0xD31A, 0x02);
            LCD_WriteReg(0xD31B, 0x01);
            LCD_WriteReg(0xD31C, 0x02);
            LCD_WriteReg(0xD31D, 0x34);
            LCD_WriteReg(0xD31E, 0x02);
            LCD_WriteReg(0xD31F, 0x67);
            LCD_WriteReg(0xD320, 0x02);
            LCD_WriteReg(0xD321, 0x84);
            LCD_WriteReg(0xD322, 0x02);
            LCD_WriteReg(0xD323, 0xA4);
            LCD_WriteReg(0xD324, 0x02);
            LCD_WriteReg(0xD325, 0xB7);
            LCD_WriteReg(0xD326, 0x02);
            LCD_WriteReg(0xD327, 0xCF);
            LCD_WriteReg(0xD328, 0x02);
            LCD_WriteReg(0xD329, 0xDE);
            LCD_WriteReg(0xD32A, 0x02);
            LCD_WriteReg(0xD32B, 0xF2);
            LCD_WriteReg(0xD32C, 0x02);
            LCD_WriteReg(0xD32D, 0xFE);
            LCD_WriteReg(0xD32E, 0x03);
            LCD_WriteReg(0xD32F, 0x10);
            LCD_WriteReg(0xD330, 0x03);
            LCD_WriteReg(0xD331, 0x33);
            LCD_WriteReg(0xD332, 0x03);
            LCD_WriteReg(0xD333, 0x6D);
            LCD_WriteReg(0xD400, 0x00);
            LCD_WriteReg(0xD401, 0x33);
            LCD_WriteReg(0xD402, 0x00);
            LCD_WriteReg(0xD403, 0x34);
            LCD_WriteReg(0xD404, 0x00);
            LCD_WriteReg(0xD405, 0x3A);
            LCD_WriteReg(0xD406, 0x00);
            LCD_WriteReg(0xD407, 0x4A);
            LCD_WriteReg(0xD408, 0x00);
            LCD_WriteReg(0xD409, 0x5C);
            LCD_WriteReg(0xD40A, 0x00);
            LCD_WriteReg(0xD40B, 0x81);

            LCD_WriteReg(0xD40C, 0x00);
            LCD_WriteReg(0xD40D, 0xA6);
            LCD_WriteReg(0xD40E, 0x00);
            LCD_WriteReg(0xD40F, 0xE5);
            LCD_WriteReg(0xD410, 0x01);
            LCD_WriteReg(0xD411, 0x13);
            LCD_WriteReg(0xD412, 0x01);
            LCD_WriteReg(0xD413, 0x54);
            LCD_WriteReg(0xD414, 0x01);
            LCD_WriteReg(0xD415, 0x82);
            LCD_WriteReg(0xD416, 0x01);
            LCD_WriteReg(0xD417, 0xCA);
            LCD_WriteReg(0xD418, 0x02);
            LCD_WriteReg(0xD419, 0x00);
            LCD_WriteReg(0xD41A, 0x02);
            LCD_WriteReg(0xD41B, 0x01);
            LCD_WriteReg(0xD41C, 0x02);
            LCD_WriteReg(0xD41D, 0x34);
            LCD_WriteReg(0xD41E, 0x02);
            LCD_WriteReg(0xD41F, 0x67);
            LCD_WriteReg(0xD420, 0x02);
            LCD_WriteReg(0xD421, 0x84);
            LCD_WriteReg(0xD422, 0x02);
            LCD_WriteReg(0xD423, 0xA4);
            LCD_WriteReg(0xD424, 0x02);
            LCD_WriteReg(0xD425, 0xB7);
            LCD_WriteReg(0xD426, 0x02);
            LCD_WriteReg(0xD427, 0xCF);
            LCD_WriteReg(0xD428, 0x02);
            LCD_WriteReg(0xD429, 0xDE);
            LCD_WriteReg(0xD42A, 0x02);
            LCD_WriteReg(0xD42B, 0xF2);
            LCD_WriteReg(0xD42C, 0x02);
            LCD_WriteReg(0xD42D, 0xFE);
            LCD_WriteReg(0xD42E, 0x03);
            LCD_WriteReg(0xD42F, 0x10);
            LCD_WriteReg(0xD430, 0x03);
            LCD_WriteReg(0xD431, 0x33);
            LCD_WriteReg(0xD432, 0x03);
            LCD_WriteReg(0xD433, 0x6D);
            LCD_WriteReg(0xD500, 0x00);
            LCD_WriteReg(0xD501, 0x33);
            LCD_WriteReg(0xD502, 0x00);
            LCD_WriteReg(0xD503, 0x34);
            LCD_WriteReg(0xD504, 0x00);
            LCD_WriteReg(0xD505, 0x3A);
            LCD_WriteReg(0xD506, 0x00);
            LCD_WriteReg(0xD507, 0x4A);
            LCD_WriteReg(0xD508, 0x00);
            LCD_WriteReg(0xD509, 0x5C);
            LCD_WriteReg(0xD50A, 0x00);
            LCD_WriteReg(0xD50B, 0x81);

            LCD_WriteReg(0xD50C, 0x00);
            LCD_WriteReg(0xD50D, 0xA6);
            LCD_WriteReg(0xD50E, 0x00);
            LCD_WriteReg(0xD50F, 0xE5);
            LCD_WriteReg(0xD510, 0x01);
            LCD_WriteReg(0xD511, 0x13);
            LCD_WriteReg(0xD512, 0x01);
            LCD_WriteReg(0xD513, 0x54);
            LCD_WriteReg(0xD514, 0x01);
            LCD_WriteReg(0xD515, 0x82);
            LCD_WriteReg(0xD516, 0x01);
            LCD_WriteReg(0xD517, 0xCA);
            LCD_WriteReg(0xD518, 0x02);
            LCD_WriteReg(0xD519, 0x00);
            LCD_WriteReg(0xD51A, 0x02);
            LCD_WriteReg(0xD51B, 0x01);
            LCD_WriteReg(0xD51C, 0x02);
            LCD_WriteReg(0xD51D, 0x34);
            LCD_WriteReg(0xD51E, 0x02);
            LCD_WriteReg(0xD51F, 0x67);
            LCD_WriteReg(0xD520, 0x02);
            LCD_WriteReg(0xD521, 0x84);
            LCD_WriteReg(0xD522, 0x02);
            LCD_WriteReg(0xD523, 0xA4);
            LCD_WriteReg(0xD524, 0x02);
            LCD_WriteReg(0xD525, 0xB7);
            LCD_WriteReg(0xD526, 0x02);
            LCD_WriteReg(0xD527, 0xCF);
            LCD_WriteReg(0xD528, 0x02);
            LCD_WriteReg(0xD529, 0xDE);
            LCD_WriteReg(0xD52A, 0x02);
            LCD_WriteReg(0xD52B, 0xF2);
            LCD_WriteReg(0xD52C, 0x02);
            LCD_WriteReg(0xD52D, 0xFE);
            LCD_WriteReg(0xD52E, 0x03);
            LCD_WriteReg(0xD52F, 0x10);
            LCD_WriteReg(0xD530, 0x03);
            LCD_WriteReg(0xD531, 0x33);
            LCD_WriteReg(0xD532, 0x03);
            LCD_WriteReg(0xD533, 0x6D);
            LCD_WriteReg(0xD600, 0x00);
            LCD_WriteReg(0xD601, 0x33);
            LCD_WriteReg(0xD602, 0x00);
            LCD_WriteReg(0xD603, 0x34);
            LCD_WriteReg(0xD604, 0x00);
            LCD_WriteReg(0xD605, 0x3A);
            LCD_WriteReg(0xD606, 0x00);
            LCD_WriteReg(0xD607, 0x4A);
            LCD_WriteReg(0xD608, 0x00);
            LCD_WriteReg(0xD609, 0x5C);
            LCD_WriteReg(0xD60A, 0x00);
            LCD_WriteReg(0xD60B, 0x81);

            LCD_WriteReg(0xD60C, 0x00);
            LCD_WriteReg(0xD60D, 0xA6);
            LCD_WriteReg(0xD60E, 0x00);
            LCD_WriteReg(0xD60F, 0xE5);
            LCD_WriteReg(0xD610, 0x01);
            LCD_WriteReg(0xD611, 0x13);
            LCD_WriteReg(0xD612, 0x01);
            LCD_WriteReg(0xD613, 0x54);
            LCD_WriteReg(0xD614, 0x01);
            LCD_WriteReg(0xD615, 0x82);
            LCD_WriteReg(0xD616, 0x01);
            LCD_WriteReg(0xD617, 0xCA);
            LCD_WriteReg(0xD618, 0x02);
            LCD_WriteReg(0xD619, 0x00);
            LCD_WriteReg(0xD61A, 0x02);
            LCD_WriteReg(0xD61B, 0x01);
            LCD_WriteReg(0xD61C, 0x02);
            LCD_WriteReg(0xD61D, 0x34);
            LCD_WriteReg(0xD61E, 0x02);
            LCD_WriteReg(0xD61F, 0x67);
            LCD_WriteReg(0xD620, 0x02);
            LCD_WriteReg(0xD621, 0x84);
            LCD_WriteReg(0xD622, 0x02);
            LCD_WriteReg(0xD623, 0xA4);
            LCD_WriteReg(0xD624, 0x02);
            LCD_WriteReg(0xD625, 0xB7);
            LCD_WriteReg(0xD626, 0x02);
            LCD_WriteReg(0xD627, 0xCF);
            LCD_WriteReg(0xD628, 0x02);
            LCD_WriteReg(0xD629, 0xDE);
            LCD_WriteReg(0xD62A, 0x02);
            LCD_WriteReg(0xD62B, 0xF2);
            LCD_WriteReg(0xD62C, 0x02);
            LCD_WriteReg(0xD62D, 0xFE);
            LCD_WriteReg(0xD62E, 0x03);
            LCD_WriteReg(0xD62F, 0x10);
            LCD_WriteReg(0xD630, 0x03);
            LCD_WriteReg(0xD631, 0x33);
            LCD_WriteReg(0xD632, 0x03);
            LCD_WriteReg(0xD633, 0x6D);
            //LV2 Page 0 enable
            LCD_WriteReg(0xF000, 0x55);
            LCD_WriteReg(0xF001, 0xAA);
            LCD_WriteReg(0xF002, 0x52);
            LCD_WriteReg(0xF003, 0x08);
            LCD_WriteReg(0xF004, 0x00);
            //Display control
            LCD_WriteReg(0xB100, 0xCC);
            LCD_WriteReg(0xB101, 0x00);
            //Source hold time
            LCD_WriteReg(0xB600, 0x05);
            //Gate EQ control
            LCD_WriteReg(0xB700, 0x70);
            LCD_WriteReg(0xB701, 0x70);
            //Source EQ control (Mode 2)
            LCD_WriteReg(0xB800, 0x01);
            LCD_WriteReg(0xB801, 0x03);
            LCD_WriteReg(0xB802, 0x03);
            LCD_WriteReg(0xB803, 0x03);
            //Inversion mode (2-dot)
            LCD_WriteReg(0xBC00, 0x02);
            LCD_WriteReg(0xBC01, 0x00);
            LCD_WriteReg(0xBC02, 0x00);
            //Timing control 4H w/ 4-delay
            LCD_WriteReg(0xC900, 0xD0);
            LCD_WriteReg(0xC901, 0x02);
            LCD_WriteReg(0xC902, 0x50);
            LCD_WriteReg(0xC903, 0x50);
            LCD_WriteReg(0xC904, 0x50);
            LCD_WriteReg(0x3500, 0x00);
            LCD_WriteReg(0x3A00, 0x55); //16-bit/pixel
            LCD_WR_REG(0x1100);
            delay_us(120);
            LCD_WR_REG(0x2900);
        }
    if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510||lcddev.id==0X1963)
	{
	 //重新配置写时序控制寄存器的时序
     writeTiming.FSMC_AddressSetupTime&=~(0XF<<0); //地址建立时间(ADDSET)清零
     writeTiming.FSMC_DataSetupTime&=~(0XF<<8); //数据保存时间清零
     writeTiming.FSMC_AddressSetupTime|=4<<0; //地址建立时间(ADDSET)为 4 个 HCLK =21ns
     writeTiming.FSMC_DataSetupTime|=4<<8;//数据保存时间(DATAST) 为 21ns
	}

	LCD_Display_Dir(1);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	LCD_Clear(LIGHTBLUE);
}  

/*********************************************************************
 * @fn      LCD_Clear
 *
 * @brief   Clear screen
 *
 * @param   color - fill color
 *
 * @return  none
 */
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height;
    LCD_SetCursor(0x00,0x0000);
	LCD_WriteRAM_Prepare();
	for(index=0;index<totalpoint;index++)
	{
		LCD->LCD_RAM=color;	
	}
}  

/*********************************************************************
 * @fn      LCD_ShowString
 *
 * @brief   Display string
 *
 * @param   x - X coordinate
 *          y - Y coordinate
 *          width - String width
 *          height - String height
 *          size - font size
 *          *p - String start address
 *
 * @return  none
 */
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{
    u8 x0=x;
    width+=x;
    height+=y;
    while((*p<='~')&&(*p>=' '))
    {
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;
        LCD_ShowChar(x,y,*p,size,1);
        x+=size/2;
        p++;
    }
}

/*********************************************************************
 * @fn      LCD_Pow
 *
 * @brief   m^n function
 *
 * @return  result - m^n
 */
u32 LCD_Pow(u8 m,u8 n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}

/*********************************************************************
 * @fn      LCD_ShowNum
 *
 * @brief   Display number
 *
 * @param   x - X coordinate
 *          y - Y coordinate
 *          len - number lenth
 *          size -font size
 *          color - font color
 *          num - value(0~4294967295)
 *
 * @return  none
 */
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{
    u8 t,temp;
    u8 enshow=0;
    for(t=0;t<len;t++)
    {
        temp=(num/LCD_Pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                LCD_ShowChar(x+(size/2)*t,y,' ',size,1);
                continue;
            }else enshow=1;

        }
        LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,1);
    }
}

/*********************************************************************
 * @fn      LCD_ShowChar
 *
 * @brief   Displays a character in the specified position
 *
 * @param   x - X coordinate
 *          y - Y coordinate
 *          num - Displays a character
 *          size -font size
 *          mode - superposition mode
 *
 * @return  none
 */
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{
    u8 temp,t1,t;
    u16 y0=y;
    u8 csize=(size/8+((size%8)?1:0))*(size/2);
    num=num-' ';
    for(t=0;t<csize;t++)
    {
        if(size==12)temp=asc2_1206[num][t];
        else if(size==16)temp=asc2_1608[num][t];
        else if(size==24)temp=asc2_2412[num][t];
        else if(size==32)temp=asc2_3216[num][t];
        else return;
        for(t1=0;t1<8;t1++)
        {
            if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
            else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
            temp<<=1;
            y++;
            if(y>=lcddev.height)return;
            if((y-y0)==size)
            {
                y=y0;
                x++;
                if(x>=lcddev.width)return;
                break;
            }
        }
    }
}
// 画线
void LCD_DrawPoint(u16 x,u16 y)
{
    LCD_SetCursor(x,y);
    LCD_WriteRAM_Prepare();
    LCD->LCD_RAM=POINT_COLOR;
}
/*********************************************************************
 * @fn      LCD_Fast_DrawPoint
 *
 * @brief   fast draw point
 *
 * @param   x - X coordinate
 *          y - Y coordinate
 *          color - font color
 *
 * @return  none
 */
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{
    if (lcddev.id == 0X5510)
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(x >> 8);
        LCD_WR_REG(lcddev.setxcmd + 1);
        LCD_WR_DATA(x & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(y >> 8);
        LCD_WR_REG(lcddev.setycmd + 1);
        LCD_WR_DATA(y & 0XFF);
    }
    LCD->LCD_REG=lcddev.wramcmd;
    LCD->LCD_RAM=color;
}

/**
 * @brief       在指定区域内填充指定颜色块
 * @param       (sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex - sx + 1) * (ey - sy + 1)
 * @param       color: 要填充的颜色数组首地址
 * @retval      无
 */
void LCD_Color_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
    uint16_t height, width;
    uint16_t i, j;

    width = ex - sx + 1;            /* 得到填充的宽度 */
    height = ey - sy + 1;           /* 高度 */

    for (i = 0; i < height; i++)
    {
        LCD_SetCursor(sx, sy + i); /* 设置光标位置 */
        LCD_WriteRAM_Prepare();    /* 开始写入GRAM */

        for (j = 0; j < width; j++)
        {
            //LCD->LCD_RAM = color[i * width + j]; /* 写入数据 */
            LCD->LCD_RAM = color;
        }
    }
}
//画线的
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
    u16 t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;
    delta_x=x2-x1;
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0)incx=1;
    else if(delta_x==0)incx=0;
    else {incx=-1;delta_x=-delta_x;}
    if(delta_y>0)incy=1;
    else if(delta_y==0)incy=0;
    else{incy=-1;delta_y=-delta_y;}
    if( delta_x>delta_y)distance=delta_x;
    else distance=delta_y;
    for(t=0;t<=distance+1;t++ )
    {
        LCD_Fast_DrawPoint(uRow,uCol,WHITE);
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}

//画矩形
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
    LCD_DrawLine(x1,y1,x2,y1);
    LCD_DrawLine(x1,y1,x1,y2);
    LCD_DrawLine(x1,y2,x2,y2);
    LCD_DrawLine(x2,y1,x2,y2);
}
//画圆
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
    int a,b;
    int di;
    a=0;b=r;
    di=3-(r<<1);
    while(a<=b)
    {
        LCD_Fast_DrawPoint(x0+a,y0-b,WHITE);
        LCD_Fast_DrawPoint(x0+b,y0-a,WHITE);
        LCD_Fast_DrawPoint(x0+b,y0+a,WHITE);
        LCD_Fast_DrawPoint(x0+a,y0+b,WHITE);
        LCD_Fast_DrawPoint(x0-a,y0+b,WHITE);
        LCD_Fast_DrawPoint(x0-b,y0+a,WHITE);
        LCD_Fast_DrawPoint(x0-a,y0-b,WHITE);
        LCD_Fast_DrawPoint(x0-b,y0-a,WHITE);
        a++;

        if(di<0)di +=4*a+6;
        else
        {
            di+=10+4*(a-b);
            b--;
        }
    }
}

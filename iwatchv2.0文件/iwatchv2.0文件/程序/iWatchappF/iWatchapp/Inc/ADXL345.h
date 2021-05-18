/************************************************************************************
文件名称：adxl345.h
文件功能：adxl345加速度传感器相关定义和声明
文件作者：Dennis-Zhou
编写日期：2013年8月17日
************************************************************************************/

//=====包含头文件=====
#ifndef __ADXL345_H
#define __ADXL345_H 
#include "sys.h"        
#include <stm32f1xx.h>
//=====adxl345指令宏定义=====
#define DEVICE_ID  0X00  //器件ID,0XE5
#define THRESH_TAP  0X1D    //敲击阀值
#define OFSX   0X1E
#define OFSY   0X1F
#define OFSZ   0X20
#define DUR    0X21
#define Latent   0X22
#define Window    0X23
#define THRESH_ACT  0X24
#define THRESH_INACT 0X25
#define TIME_INACT  0X26
#define ACT_INACT_CTL 0X27 
#define THRESH_FF  0X28
#define TIME_FF   0X29
#define TAP_AXES  0X2A 
#define ACT_TAP_STATUS  0X2B
#define BW_RATE   0X2C
#define POWER_CTL  0X2D
#define INT_ENABLE  0X2E
#define INT_MAP   0X2F
#define INT_SOURCE   0X30
#define DATA_FORMAT     0X31
#define DATA_X0   0X32
#define DATA_X1   0X33
#define DATA_Y0   0X34
#define DATA_Y1   0X35
#define DATA_Z0   0X36
#define DATA_Z1   0X37
#define FIFO_CTL  0X38
#define FIFO_STATUS  0X39
#define ADXL_READ     0XA7
#define ADXL_WRITE    0XA6

#define	SlaveAddress   0xA6	
//=====adxl345相关函数声明=====
u8   ADXL345_Init(void);           //初始化ADXL345
void  ADXL345_WR_Reg(uint8_t REG_Address,uint8_t REG_data);        //写ADXL345寄存器
u8   ADXL345_RD_Reg(uint8_t REG_Address);         //读ADXL345寄存器
void  ADXL345_RD_XYZ(short *x,short *y,short *z);     //读取一次值
void  ADXL345_RD_Avval(short *x,short *y,short *z);    //读取平均值
void  ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval);  //自动校准
void  ADXL345_Read_Average(short *x,short *y,short *z,u8 times); //连续读取times次,取平均
short  ADXL345_Get_Angle(float x,float y,float z,u8 dir);   //获取角度值
void  Adxl_Show_Num(u16 x,u16 y,short num,u8 mode);    //显示ADXL345的加速度值或角度值
u8   ADXL345_Read_Angle(void);         //转换ADX345角度值
#endif



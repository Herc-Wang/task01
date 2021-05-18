#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"



//IO操作函数	  MPU6050
#define IIC_SDA_H      HAL_GPIO_WritePin(GPIOB, SDA_345_Pin, GPIO_PIN_SET) 
#define IIC_SDA_L      HAL_GPIO_WritePin(GPIOB, SDA_345_Pin, GPIO_PIN_RESET) 
#define IIC_SCL_H      HAL_GPIO_WritePin(GPIOB, SCL_345_Pin, GPIO_PIN_SET)
#define IIC_SCL_L      HAL_GPIO_WritePin(GPIOB, SCL_345_Pin, GPIO_PIN_RESET)	 

#define READ_SDA      (HAL_GPIO_ReadPin(GPIOB, SDA_345_Pin) != GPIO_PIN_RESET)



//IO操作函数	DS3231 
#define IIC2_SDA_H     HAL_GPIO_WritePin(GPIOB, DS_SDA_Pin, GPIO_PIN_SET) 
#define IIC2_SDA_L     HAL_GPIO_WritePin(GPIOB, DS_SDA_Pin, GPIO_PIN_RESET) 
#define IIC2_SCL_H     HAL_GPIO_WritePin(GPIOB, DS_SCL_Pin, GPIO_PIN_SET)
#define IIC2_SCL_L     HAL_GPIO_WritePin(GPIOB, DS_SCL_Pin, GPIO_PIN_RESET)	 


#define READ2_SDA     (HAL_GPIO_ReadPin(GPIOB, DS_SDA_Pin) != GPIO_PIN_RESET)  //输入SDA 
  
	
//IO操作函数	   
#define IIC3_SDA_H     HAL_GPIO_WritePin(GPIOA, SDA_7020_Pin, GPIO_PIN_SET) 
#define IIC3_SDA_L     HAL_GPIO_WritePin(GPIOA, SDA_7020_Pin, GPIO_PIN_RESET) 
#define IIC3_SCL_H     HAL_GPIO_WritePin(GPIOB, SCL_7020_Pin, GPIO_PIN_SET)
#define IIC3_SCL_L     HAL_GPIO_WritePin(GPIOB, SCL_7020_Pin, GPIO_PIN_RESET)	 


#define READ3_SDA     (HAL_GPIO_ReadPin(GPIOA, SDA_7020_Pin) != GPIO_PIN_RESET)  //输入SDA 


//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号



void IIC2_Init(void);                //初始化IIC的IO口
void IIC2_Start(void);				//发送IIC开始信号
void IIC2_Stop(void);	  			//发送IIC停止信号
void IIC2_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC2_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC2_Wait_Ack(void); 				//IIC等待ACK信号
void IIC2_Ack(void);					//IIC发送ACK信号
void IIC2_NAck(void);				//IIC不发送ACK信号



void IIC3_Init(void);                //初始化IIC的IO口
void IIC3_Start(void);				//发送IIC开始信号
void IIC3_Stop(void);	  			//发送IIC停止信号
void IIC3_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC3_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC3_Wait_Ack(void); 				//IIC等待ACK信号
void IIC3_Ack(void);					//IIC发送ACK信号
void IIC3_NAck(void);				//IIC不发送ACK信号



#endif

















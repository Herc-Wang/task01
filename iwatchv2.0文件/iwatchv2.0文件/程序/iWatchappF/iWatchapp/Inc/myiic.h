#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"



//IO��������	  MPU6050
#define IIC_SDA_H      HAL_GPIO_WritePin(GPIOB, SDA_345_Pin, GPIO_PIN_SET) 
#define IIC_SDA_L      HAL_GPIO_WritePin(GPIOB, SDA_345_Pin, GPIO_PIN_RESET) 
#define IIC_SCL_H      HAL_GPIO_WritePin(GPIOB, SCL_345_Pin, GPIO_PIN_SET)
#define IIC_SCL_L      HAL_GPIO_WritePin(GPIOB, SCL_345_Pin, GPIO_PIN_RESET)	 

#define READ_SDA      (HAL_GPIO_ReadPin(GPIOB, SDA_345_Pin) != GPIO_PIN_RESET)



//IO��������	DS3231 
#define IIC2_SDA_H     HAL_GPIO_WritePin(GPIOB, DS_SDA_Pin, GPIO_PIN_SET) 
#define IIC2_SDA_L     HAL_GPIO_WritePin(GPIOB, DS_SDA_Pin, GPIO_PIN_RESET) 
#define IIC2_SCL_H     HAL_GPIO_WritePin(GPIOB, DS_SCL_Pin, GPIO_PIN_SET)
#define IIC2_SCL_L     HAL_GPIO_WritePin(GPIOB, DS_SCL_Pin, GPIO_PIN_RESET)	 


#define READ2_SDA     (HAL_GPIO_ReadPin(GPIOB, DS_SDA_Pin) != GPIO_PIN_RESET)  //����SDA 
  
	
//IO��������	   
#define IIC3_SDA_H     HAL_GPIO_WritePin(GPIOA, SDA_7020_Pin, GPIO_PIN_SET) 
#define IIC3_SDA_L     HAL_GPIO_WritePin(GPIOA, SDA_7020_Pin, GPIO_PIN_RESET) 
#define IIC3_SCL_H     HAL_GPIO_WritePin(GPIOB, SCL_7020_Pin, GPIO_PIN_SET)
#define IIC3_SCL_L     HAL_GPIO_WritePin(GPIOB, SCL_7020_Pin, GPIO_PIN_RESET)	 


#define READ3_SDA     (HAL_GPIO_ReadPin(GPIOA, SDA_7020_Pin) != GPIO_PIN_RESET)  //����SDA 


//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�



void IIC2_Init(void);                //��ʼ��IIC��IO��
void IIC2_Start(void);				//����IIC��ʼ�ź�
void IIC2_Stop(void);	  			//����IICֹͣ�ź�
void IIC2_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC2_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC2_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC2_Ack(void);					//IIC����ACK�ź�
void IIC2_NAck(void);				//IIC������ACK�ź�



void IIC3_Init(void);                //��ʼ��IIC��IO��
void IIC3_Start(void);				//����IIC��ʼ�ź�
void IIC3_Stop(void);	  			//����IICֹͣ�ź�
void IIC3_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC3_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC3_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC3_Ack(void);					//IIC����ACK�ź�
void IIC3_NAck(void);				//IIC������ACK�ź�



#endif

















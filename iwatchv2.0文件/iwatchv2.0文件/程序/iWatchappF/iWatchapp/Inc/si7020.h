#ifndef __SI7020_H
#define __SI7020_H
#include <stdio.h>
#include <stdint.h>

#include <stm32f1xx.h>
#define SI7020_ADDRESS 0X80 //SI7020器件地址
#define SI7020_READ    0X01        //读数据





#define SI7020_TEMPERATURE      0xE3
#define SI7020_HUMIDITY         0xE5
#define SI7020_SOFT_RESET       0xFE


//#define SI7020_TEMPERATURE      0xF3
//#define SI7020_HUMIDITY         0xF5
//#define SI7020_SOFT_RESET       0xFE


void SI7020_Init(void); //初始化IIC
uint16_t SI7020_ReadOneByte(uint8_t ReadAddr);
int16_t SI7020_Read_Humidity(void);
int16_t SI7020_Read_Temperture(void);

#endif

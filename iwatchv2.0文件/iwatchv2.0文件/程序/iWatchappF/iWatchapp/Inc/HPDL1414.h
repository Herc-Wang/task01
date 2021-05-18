#ifndef __HPDL1414_H
#define __HPDL1414_H 			   
#include "sys.h"
#define D0_1     HAL_GPIO_WritePin(GPIOB, D0_Pin, GPIO_PIN_SET) 
#define D0_0     HAL_GPIO_WritePin(GPIOB, D0_Pin, GPIO_PIN_RESET) 
#define D1_1     HAL_GPIO_WritePin(GPIOB, D1_Pin, GPIO_PIN_SET) 
#define D1_0     HAL_GPIO_WritePin(GPIOB, D1_Pin, GPIO_PIN_RESET) 
#define D2_1     HAL_GPIO_WritePin(GPIOA, D2_Pin, GPIO_PIN_SET) 
#define D2_0     HAL_GPIO_WritePin(GPIOA, D2_Pin, GPIO_PIN_RESET) 
#define D3_1     HAL_GPIO_WritePin(GPIOA, D3_Pin, GPIO_PIN_SET) 
#define D3_0     HAL_GPIO_WritePin(GPIOA, D3_Pin, GPIO_PIN_RESET) 
#define D4_1     HAL_GPIO_WritePin(GPIOA, D4_Pin, GPIO_PIN_SET) 
#define D4_0     HAL_GPIO_WritePin(GPIOA, D4_Pin, GPIO_PIN_RESET) 
#define D5_1     HAL_GPIO_WritePin(GPIOA, D5_Pin, GPIO_PIN_SET) 
#define D5_0     HAL_GPIO_WritePin(GPIOA, D5_Pin, GPIO_PIN_RESET) 
#define D6_1     HAL_GPIO_WritePin(GPIOA, D6_Pin, GPIO_PIN_SET) 
#define D6_0     HAL_GPIO_WritePin(GPIOA, D6_Pin, GPIO_PIN_RESET) 
#define A0_1     HAL_GPIO_WritePin(GPIOA, A0_Pin, GPIO_PIN_SET) 
#define A0_0     HAL_GPIO_WritePin(GPIOA, A0_Pin, GPIO_PIN_RESET) 
#define A1_1     HAL_GPIO_WritePin(GPIOA, A1_Pin, GPIO_PIN_SET) 
#define A1_0     HAL_GPIO_WritePin(GPIOA, A1_Pin, GPIO_PIN_RESET) 
#define WR1_1     HAL_GPIO_WritePin(GPIOB, WR1_Pin, GPIO_PIN_SET) 
#define WR1_0     HAL_GPIO_WritePin(GPIOB, WR1_Pin, GPIO_PIN_RESET) 
//#define P1_1     HAL_GPIO_WritePin(GPIOB, P1_Pin, GPIO_PIN_SET) 
//#define P1_0     HAL_GPIO_WritePin(GPIOB, P1_Pin, GPIO_PIN_RESET) 
#define WR2_1     HAL_GPIO_WritePin(GPIOB, WR2_Pin, GPIO_PIN_SET) 
#define WR2_0     HAL_GPIO_WritePin(GPIOB, WR2_Pin, GPIO_PIN_RESET) 




void HPDL1414_INT(void);
void write_1414(u8 word,u8 dig);
void HPDL1414_show(u8 word[8]);

#endif

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2020 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdlib.h"
#include "string.h"
#include "HPDL1414.h"
#include "DS3231.h"
#include "sys.h"
#include "delay.h" 
#include "si7020.h" 
//#include "mpuiic.h"
#include "myiic.h"
#include "ADXL345.h"
#include <stdio.h>
#include <math.h>
#include "adxl345.h"
#define MAX              0x39            //??????
#define MIN              0x30             //??????
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void showTemperture(void);
void showHumidity(void);
void showtime(void);
void showdata(void);
//void showtemp(void);
void showweek(void);
void hextoascii(int16_t num,u8 *word);
void showfrist(void);
unsigned int random(void);
void init_all(void);
void weakupshow(void);
//void wifi_bt_on(void);
void SendAtCommand(char *patcm);
void Sendword(char *patcm);
void showsteps(void);
void getzero(void);
void SleepMode_Measure(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
struct stuff{
        char time;
        char Temperture;
	      char Humidity;
	      char jd;
	      char onshow;
	      char okon;//用于限制0度时一直显示
	      char bluetoothon;
	      char steps;
}flag;
u8  Angle[6];
u8 aacx[2];
u8 word1[8]={' ',' ',' ',' ',' ',' ',' ',' '};
char *wifi1="RAYPAI";
char *code1="56831513";
int v=40;
short test2=0;
int16_t Temperture=0;
int16_t Temperture1=0;
int16_t Humidity=0;
int16_t Humidity1=0;
int16_t t1=0;
int daytemp=0;//用于判断是否过了一天，如果过了一天则清零步数
int timenum=0;
int stepsnum=0;
int buletoothnum=0;
char jdnum=0;
int16_t onshownum=0;
int RxBuffernum=0;
char breakflag=0;
char StartRx0=0;//防止串口被打断
int16_t Temperturenum=0;
u8 rbuf[6];
uint8_t blueTxBuffer[20];
uint8_t wifiTxBuffer[200];
uint8_t blueRxBuffer[20];
uint8_t wifiRxBuffer[200];
u8 devid=0;

/* 传感器数据修正值（消除芯片固定误差） */
/* 坐标角度结构体 */
short int Acc_X=0,Acc_Y=0,Acc_Z=0;
double Angle_X=0,Angle_Y=0,Angle_Z=0;
//void ADXL345_Get_Angle(ADXL345_Angle *data);
//int16_t Humiditynum=0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  //	MPU6050_Angle data;
  //	int i=0;
  flag.time=0;
  flag.Humidity=0;
  flag.Temperture=0;
	 flag.onshow=0;
	 flag.jd=0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
	//HAL_UART_Receive_IT(&huart3,(uint8_t *)&wifiRxBuffer[RxBuffernum],1);
	showfrist();
	init_all();
	SleepMode_Measure();
//	getzero();
	//HAL_GPIO_WritePin(GPIOB, poweron_Pin, GPIO_PIN_SET);
//	wifi_bt_on();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
if(flag.bluetoothon==1)
{
			if(HAL_UART_Receive_IT(&huart1,(uint8_t *)&blueRxBuffer,15)==0)	//命令要发两遍	
  {
  if(blueRxBuffer[0]==0x54)
	{
	//HAL_UART_Receive_IT(&huart1,(uint8_t *)&aRxBuffer+1,14);
	if((blueRxBuffer[1]==0x01)&&(blueRxBuffer[14]==0x64))
	{
    blueRxBuffer[3]=(blueRxBuffer[3]/16)*10+(blueRxBuffer[3]%16);
 	  blueRxBuffer[4]=(blueRxBuffer[4]/16)*10+(blueRxBuffer[4]%16);
		blueRxBuffer[5]=(blueRxBuffer[5]/16)*10+(blueRxBuffer[5]%16);
		blueRxBuffer[6]=(blueRxBuffer[6]/16)*10+(blueRxBuffer[6]%16);
		blueRxBuffer[7]=(blueRxBuffer[7]/16)*10+(blueRxBuffer[7]%16);
		blueRxBuffer[8]=(blueRxBuffer[8]/16)*10+(blueRxBuffer[8]%16);
		blueRxBuffer[9]=(blueRxBuffer[9]/16)*10+(blueRxBuffer[9]%16);
    DS3231_Set(blueRxBuffer[3],blueRxBuffer[4],blueRxBuffer[5],blueRxBuffer[6],blueRxBuffer[7],blueRxBuffer[8],blueRxBuffer[9]);
		memset(blueRxBuffer,0x00,20);
		get_show_time();	
		HAL_GPIO_WritePin(GPIOB, led1_Pin, GPIO_PIN_SET);
	  flag.onshow=1;//开显示
		//flag.bluetoothon=1;//开蓝牙
		flag.okon=0;  //关闭标志位用来限制一直显示
		showfrist();
    calendar.hour&=0x3f;  
    word1[0]=BCD2ASC_H(calendar.hour); 
    word1[1]=BCD2ASC_L(calendar.hour);	
    word1[2]='-';
    word1[3]=BCD2ASC_H(calendar.min); 
    word1[4]=BCD2ASC_L(calendar.min);	
    word1[5]='-';
    word1[6]=BCD2ASC_H(calendar.sec); 
    word1[7]=BCD2ASC_L(calendar.sec);		
    HPDL1414_show(word1);
		weakupshow();
  }		
	}	
  if(blueRxBuffer[0]=='O'&&blueRxBuffer[1]=='K')
		{
			memset(blueRxBuffer,0x00,20);
		}
      memset(blueRxBuffer,0x00,20);
  }
	
}



	if(flag.jd==1)
	{   
    flag.jd=0;		
		ADXL345_Read_Angle();
		//jibu
		if((Angle[2]=='-')&&(Angle[3]>=0x10))
		{
		flag.steps=1;
		}
		if((Angle[2]==' ')&&(flag.steps==1)&&(Angle[3]>=0x10))
		{
		flag.steps=0;
		stepsnum++;
    if(stepsnum>=50000)	
		{
		stepsnum=0;
		}			
		}
		
		
		//huanxing
		if((Angle[3]<0x15)&&(Angle[2]==' '))
		{
		if(flag.okon==1)
		{
		get_show_time();	
		HAL_GPIO_WritePin(GPIOB, led1_Pin, GPIO_PIN_SET);
		flag.onshow=1;//开显示
		flag.bluetoothon=1;//开蓝牙
		MX_USART1_UART_Init();
	  HAL_GPIO_WritePin(GPIOB,poweron_Pin, GPIO_PIN_SET);
   	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	  __HAL_RCC_GPIOA_CLK_ENABLE();
    MX_USART1_UART_Init();
		flag.okon=0;  //关闭标志位用来限制一直显示
		showfrist();
    calendar.hour&=0x3f;  
    word1[0]=BCD2ASC_H(calendar.hour); 
    word1[1]=BCD2ASC_L(calendar.hour);	
    word1[2]='-';
    word1[3]=BCD2ASC_H(calendar.min); 
    word1[4]=BCD2ASC_L(calendar.min);	
    word1[5]='-';
    word1[6]=BCD2ASC_H(calendar.sec); 
    word1[7]=BCD2ASC_L(calendar.sec);		
    HPDL1414_show(word1);
		}
		}
		else if((Angle[3]>0x2d))
		{
		flag.okon=1;
		}
	}
   if(flag.onshow==1)
	 {
	  weakupshow();
	 }
	 else
	 {
	
	 }
	//SleepMode_Measure();//digonghao
//led1_Pin
	//HAL_GPIO_WritePin(GPIOB, poweron_Pin, GPIO_PIN_RESET);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 80;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 100;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D5_Pin|D4_Pin|A1_Pin|A0_Pin 
                          |D6_Pin|D3_Pin|D2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D1_Pin|D0_Pin|led1_Pin|poweron_Pin 
                          |WR1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SDA_7020_GPIO_Port, SDA_7020_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SCL_7020_Pin|SCL_345_Pin|SDA_345_Pin|DS_SDA_Pin 
                          |DS_SCL_Pin|WR2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : D5_Pin D4_Pin A1_Pin A0_Pin 
                           D6_Pin D3_Pin D2_Pin */
  GPIO_InitStruct.Pin = D5_Pin|D4_Pin|A1_Pin|A0_Pin 
                          |D6_Pin|D3_Pin|D2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D1_Pin D0_Pin WR1_Pin */
  GPIO_InitStruct.Pin = D1_Pin|D0_Pin|WR1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : led1_Pin poweron_Pin */
  GPIO_InitStruct.Pin = led1_Pin|poweron_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SDA_7020_Pin */
  GPIO_InitStruct.Pin = SDA_7020_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SDA_7020_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SCL_7020_Pin SCL_345_Pin SDA_345_Pin DS_SDA_Pin 
                           DS_SCL_Pin WR2_Pin */
  GPIO_InitStruct.Pin = SCL_7020_Pin|SCL_345_Pin|SDA_345_Pin|DS_SDA_Pin 
                          |DS_SCL_Pin|WR2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void SleepMode_Measure(void)
{
 
  HAL_SuspendTick();
  

  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
  

  HAL_ResumeTick();
  
  
  HAL_Delay(200);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)

{
    if (htim->Instance == htim2.Instance)

 {
        
			  flag.jd=1;
			if(	flag.onshow==1)
	  {  
			flag.jd=0;
			timenum++;
			if(timenum==8100)
			{
			timenum=0;
			flag.onshow=0;
			}
	  }
		if(flag.bluetoothon==1)
		{
			buletoothnum++;
			if(buletoothnum==45000)//60秒蓝牙结束后关闭电源
			{
				buletoothnum=0;
				flag.bluetoothon=0;
		    getzero();
			}
		}
		
		
  }
}

void getzero()
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  //__HAL_RCC_GPIOB_CLK_ENABLE();
	
		    HAL_GPIO_WritePin(GPIOB, poweron_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
 GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/*
void HAL_SYSTICK_Callback(void)
{
			  
}*/


unsigned int random()
{
  unsigned int value;
 
    value=rand()%(MAX-MIN+1)+MIN;               //???????(1-16)
  
  return value;
}


void hextoascii(int16_t num,u8 *word)
{
	word[6]=(num%10)+0x30;
  word[4]=(num/10%10)+0x30;
	word[3]=(num/100%10)+0x30;
}

void HPDL1414_INT()
{
HPDL1414_show(word1);
//P1_1;
//P2_1;
}
void showsteps()
{
	     // stepsnum=9;
	    	word1[7]=(stepsnum%10)+0x30;
        word1[6]=(stepsnum/10%10)+0x30;
	      word1[5]=(stepsnum/100%10)+0x30;
	      word1[4]=(stepsnum/1000%100)+0x30;
	      word1[3]=(stepsnum/1000%100)+0x30;
	    if(stepsnum<10)
			{
			 word1[6]=' ';
				word1[5]=' ';
				word1[4]=' ';
				word1[3]=' ';
			}
	    else if(stepsnum>=10)
      {
		
				word1[5]=' ';
				word1[4]=' ';
				word1[3]=' ';
			}	 
      else if(stepsnum>=100)
			{
				word1[4]=' ';
				word1[3]=' ';
			}
      else if(stepsnum>=1000)	
			{
			  word1[3]=' ';
			}
      else if(stepsnum>=10000)	
			{
			
			}				
			word1[0]='S';
			word1[1]='T';
			word1[2]='P';
			
			HPDL1414_show(word1);
}
void showHumidity()
{
Humidity=SI7020_Read_Humidity();
if(((Humidity&0x0fff)==0x01fa)||((Humidity&0x0fff)==0x04a1))
			{
			Humidity=Humidity1;
			}
			else
			{
			Humidity1=Humidity;
			}
      hextoascii(Humidity,word1);
			word1[0]='H';
			word1[1]=' ';
			word1[2]=' ';
			word1[5]='.';
			word1[7]='%';
			HPDL1414_show(word1);
}

void showTemperture()
{
	
	Temperture=SI7020_Read_Temperture();
	if((Temperture&0x0fff)==0x0e2c)
			{
			Temperture=Temperture1;
			}
			else
			{
			Temperture1=Temperture;
			}
	    hextoascii(Temperture,word1);		
			word1[0]='T';
			word1[1]=' ';
			word1[2]=' ';
			word1[5]='.';
			word1[7]='C';
			HPDL1414_show(word1);
}

void showweek()
{
	switch(calendar.week)	
{
    case 0x01:
		word1[0]='M';
		word1[1]='O';
		word1[2]='N';
		   break;
    case 0x02:
		word1[0]='T';
		word1[1]='E';
		word1[2]='U';	
       break; 
    case 0x03:
    word1[0]='W';
		word1[1]='E';
		word1[2]='D';		
       break; 
		case 0x04:
    word1[0]='T';
		word1[1]='H';
		word1[2]='U';		
       break; 
		case 0x05:
		word1[0]='F';
		word1[1]='R';
		word1[2]='I';
       break; 
		case 0x06:
		word1[0]='S';
		word1[1]='A';
		word1[2]='T';
       break; 
		case 0x07:
		word1[0]='S';
		word1[1]='U';
		word1[2]='N';
	     break; 
    default : break;
}
    word1[3]=' ';
    word1[4]=' ';
    word1[5]=' ';
	  word1[6]=' ';
	  word1[7]=' ';
    HPDL1414_show(word1);
}
void showdata()
{
//get_show_time();	
word1[0]=BCD2ASC_H(calendar.w_year); 
word1[1]=BCD2ASC_L(calendar.w_year);	
word1[2]='-';
word1[3]=BCD2ASC_H(calendar.w_month); 
word1[4]=BCD2ASC_L(calendar.w_month);	
word1[5]='-';
word1[6]=BCD2ASC_H(calendar.w_date); 
word1[7]=BCD2ASC_L(calendar.w_date);	
//calendar.week=I2cByteRead(0x03);  
//calendar.week=BCD2HEX(calendar.week);
HPDL1414_show(word1);
}

void showtime()
{	
get_show_time();	
calendar.hour&=0x3f;  
word1[0]=BCD2ASC_H(calendar.hour); 
word1[1]=BCD2ASC_L(calendar.hour);	
word1[2]='-';
word1[3]=BCD2ASC_H(calendar.min); 
word1[4]=BCD2ASC_L(calendar.min);	
word1[5]='-';
word1[6]=BCD2ASC_H(calendar.sec); 
word1[7]=BCD2ASC_L(calendar.sec);		
HPDL1414_show(word1);
}
void showfrist()
{	

	
	HAL_GPIO_WritePin(GPIOB, led1_Pin, GPIO_PIN_SET);
	int i=0;
	for(i=0;i<8;i++)
	{
    word1[i]='-';
	}
	for(i=0;i<8;i++)
	{
    word1[i]=0x29;
		HPDL1414_show(word1);
		delay_ms(300);
	}
	for(i=0;i<12;i++)
	{
    word1[0]=random();
		word1[1]=random();
		word1[2]='-';
		word1[3]=random();
		word1[4]=random();
		word1[5]='-';
		word1[6]=random();
		word1[7]=random();
		HPDL1414_show(word1);
		delay_ms(200);
	}
	
}

void init_all()
{
	flag.bluetoothon=1;
	MX_USART1_UART_Init();
	HAL_GPIO_WritePin(GPIOB,poweron_Pin, GPIO_PIN_SET);
 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	__HAL_RCC_GPIOA_CLK_ENABLE();
  MX_USART1_UART_Init();
	word1[0]='I';
  word1[1]='N';
	word1[2]='I';
	word1[3]='T';
	word1[4]=' ';
	word1[5]='N';
	word1[6]='O';
	word1[7]='W';
	HPDL1414_show(word1);
	ADXL345_Init();
	
  //Init_ADXL345();
	//delay_ms(100);
	HPDL1414_INT();
  DS3231_Init(); 					   //??????IIC2???
	SI7020_Init();
	DS3231_Set(20,10,3,6,19,15,18);
	
	word1[0]='S';
  word1[1]='T';
	word1[2]='R';
	word1[3]='A';
	word1[4]='T';
	word1[5]=' ';
	word1[6]='O';
	word1[7]='K';
	HPDL1414_show(word1);
	delay_ms(500);
	delay_ms(500);
	//Init_ADXL345();
	//devid=Single_Read_ADXL345(0X00);	//读出的数据为0XE5,表示正确
	//showtime();
	HAL_GPIO_WritePin(GPIOB, led1_Pin, GPIO_PIN_RESET);
	
  word1[0]=' ';
  word1[1]=' ';
	word1[2]=' ';
	word1[3]=' ';
	word1[4]=' ';
	word1[5]=' ';
	word1[6]=' ';
	word1[7]=' ';
	HPDL1414_show(word1);
	flag.okon=1;//使能显示
	WR1_0;	
	WR2_0;
	A1_0;
	A0_0;
	D0_0;
	D1_0;
	D2_0;
	D3_0;
	D4_0;
	D5_0;
	D6_0;
	
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{ 
	/*
 if(huart->Instance==USART3)
{
   if(StartRx0==0)
    {
	  	
		
		 RxBuffernum++;
			AL_UART_Receive_IT(&huart3,(uint8_t *)&wifiRxBuffer[RxBuffernum],1);
			 	  if(RxBuffernum>189)
		   {
				RxBuffernum=0;
			  breakflag=1;
		    StartRx0=1;
				memset(wifiRxBuffer,0x00,189);
	      memset(wifiTxBuffer,0x00,189);
		   }
			 
	   
	
	  */
	/*	else if(wifiRxBuffer[0]=='T')
        {
				
				
				 HAL_UART_Receive_IT(&huart3,(uint8_t *)&wifiRxBuffer[RxBuffernum],1);
		     RxBuffernum++;
			 	  if(RxBuffernum>189)
		   {
				RxBuffernum=0;
			  breakflag=1;
		    StartRx0=1;
				memset(wifiRxBuffer,0x00,189);
	      memset(wifiTxBuffer,0x00,189);
		   } 	 
				
				
				
				}*/
	/*		 }
		else{
		HAL_UART_Receive_IT(&huart3,(uint8_t *)&wifiRxBuffer[RxBuffernum],1);
			
		}
			
} */






}
/*
void wifi_bt_on()
{ 
	int k,i; 
	int flag1=0;
	HAL_UART_Receive_IT(&huart3,(uint8_t *)&wifiRxBuffer[RxBuffernum],1);	
	///////////////////////at
	SendAtCommand("AT\r\n");
	delay_ms(1000);
	Sendword("W-------");
	delay_ms(1000);
	delay_ms(1000);
				Sendword("WA------");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAI-----");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT----");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT.---");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT..--");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT...-");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT....");
				delay_ms(1000);
				delay_ms(1000);
				memset(wifiRxBuffer,0x00,99);
	      memset(wifiTxBuffer,0x00,99);
		////////////////////////////////切换模式
  SendAtCommand("AT+CWMODE_DEF=3\r\n");
  delay_ms(1000);
	Sendword("W-------");
	delay_ms(1000);
	delay_ms(1000);
				Sendword("WA------");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAI-----");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT----");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT.---");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT..--");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT...-");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT....");
				delay_ms(1000);
				delay_ms(1000);
      	memset(wifiRxBuffer,0x00,99);
	      memset(wifiTxBuffer,0x00,99);
				delay_ms(1000);
				delay_ms(1000);
					Sendword("W-------");
	delay_ms(1000);
	delay_ms(1000);
				Sendword("WA------");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAI-----");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT----");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT.---");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT..--");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT...-");
				delay_ms(1000);
				delay_ms(1000);
				Sendword("WAIT....");
				delay_ms(1000);
				delay_ms(1000);
      	memset(wifiRxBuffer,0x00,99);
	      memset(wifiTxBuffer,0x00,99);
				delay_ms(1000);
				delay_ms(1000);
	///////////////////////////////	联网	
	
  memcpy(wifiTxBuffer,"AT+CWJAP_DEF=",13);
  wifiTxBuffer[13]='"';
	memcpy(wifiTxBuffer+14,wifi1,strlen(wifi1));
	wifiTxBuffer[14+strlen(wifi1)]='"';
	wifiTxBuffer[15+strlen(wifi1)]=',';
	wifiTxBuffer[16+strlen(wifi1)]='"';
	memcpy(wifiTxBuffer+17+strlen(wifi1),code1,strlen(code1));	
	wifiTxBuffer[17+strlen(wifi1)+strlen(code1)]='"';
	wifiTxBuffer[18+strlen(wifi1)+strlen(code1)]=0X0D;
	wifiTxBuffer[19+strlen(wifi1)+strlen(code1)]=0X0A;
  HAL_UART_Transmit_IT(&huart3 ,(uint8_t*)wifiTxBuffer,20+strlen(wifi1)+strlen(code1));
  //HAL_UART_Receive_IT(&huart3,(uint8_t *)&wifiRxBuffer[RxBuffernum],1);	
//	SendAtCommand("AT\r\n");
	delay_ms(1000);
  for(i=0;i<6;i++)
		{	  
				Sendword("W-------");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("WA------");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("WAI-----");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("WAIT----");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("WAIT.---");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("WAIT..--");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("WAIT...-");
				delay_ms(1000);
						delay_ms(1000);
				Sendword("WAIT....");
				delay_ms(1000);
						delay_ms(1000);
				for(k=40;k<129;k++)
         {
				 if((wifiRxBuffer[k]=='O')&&(wifiRxBuffer[k+1]=='K'))
				  {
					 StartRx0=1;//停止接受
				   breakflag=1;
					 flag1=1;
				   break;
				  }
				 }		
				if(breakflag==1)
				{
				RxBuffernum=0;
				break;
				}
		}
		delay_ms(200);
	memset(wifiRxBuffer,0x00,129);
	memset(wifiTxBuffer,0x00,129);

		
		if(flag1==1)
		{		
	memcpy(wifiTxBuffer,"AT+CIPSTART=",12);
  wifiTxBuffer[12]='"';
	memcpy(wifiTxBuffer+13,"TCP",3);
	wifiTxBuffer[16]='"';
	wifiTxBuffer[17]=',';
	wifiTxBuffer[18]='"';
	memcpy(wifiTxBuffer+19,"api.seniverse.com",17);	
	wifiTxBuffer[36]='"';
	wifiTxBuffer[37]=',';	
	wifiTxBuffer[38]='8';
	wifiTxBuffer[39]='0';
	wifiTxBuffer[40]=0X0D;
	wifiTxBuffer[41]=0X0A;
  HAL_UART_Transmit_IT(&huart3 ,(uint8_t*)wifiTxBuffer,42);
		   
			for(i=0;i<8;i++)
				{
				Sendword("G-------");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GE------");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET-----");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET ----");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET D---");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET DA--");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET DAT-");
				delay_ms(1000);
						delay_ms(1000);
				Sendword("GET DATA");
				delay_ms(1000);
						delay_ms(1000);			
					}
			
						
				SendAtCommand("AT+CIPMODE=1\r\n");	
  	
				for(i=0;i<8;i++)
				{
				Sendword("G-------");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GE------");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET-----");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET ----");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET D---");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET DA--");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET DAT-");
				delay_ms(1000);
						delay_ms(1000);
				Sendword("GET DATA");
				delay_ms(1000);
						delay_ms(1000);			
					}
						
				SendAtCommand("AT+CIPSEND\r\n");	
				
				for(i=0;i<8;i++)
				{
				Sendword("G-------");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GE------");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET-----");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET ----");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET D---");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET DA--");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET DAT-");
				delay_ms(1000);
						delay_ms(1000);
				Sendword("GET DATA");
				delay_ms(1000);
						delay_ms(1000);			
					}
				StartRx0=0;//开启接收
				RxBuffernum=0;
				SendAtCommand("GET https://api.seniverse.com/v3/weather/now.json?key=SCMjpaUeMaUGIap5M&location=xian&language=en&unit=c");	
				
					
				for(i=0;i<8;i++)
				{
				Sendword("G-------");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GE------");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET-----");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET ----");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET D---");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET DA--");
				delay_ms(1000);
					delay_ms(1000);
				Sendword("GET DAT-");
				delay_ms(1000);
						delay_ms(1000);
				Sendword("GET DATA");
				delay_ms(1000);
						delay_ms(1000);			
					}
					delay_ms(1000);		
		}
		
		
		
		
}*/
/*
void SendAtCommand(char *patcm)
{
  memcpy(wifiTxBuffer,patcm,strlen(patcm));
  HAL_UART_Transmit_IT(&huart3 ,(uint8_t*)wifiTxBuffer,strlen(patcm));
}
*/
void Sendword(char *patcm)
{
  memcpy(word1,patcm,8);
	HPDL1414_show(word1);
}
	

void weakupshow()
{
	
	//int i=0;	
		if(timenum==1000)
		{
		showtime();
			if(daytemp==calendar.w_date)
			{

			}
			else
			{
			daytemp=calendar.w_date;
				stepsnum=0;
			}
		}	
		else if(timenum==2000)
		{
		showtime();
		}
		else if(timenum==3000)
		{  
		 showsteps();
		}
		else if(timenum==4000)
		{
		  showTemperture();	
		}
				else if(timenum==5000)
		{
				showHumidity();		
		}
				else if(timenum==6000)
		{
				showweek();
		}
    else if(timenum==7000)
		{
		showdata();	
		}
		if(timenum>8000)
		{
		HAL_GPIO_WritePin(GPIOB, led1_Pin, GPIO_PIN_RESET);
    word1[0]=' ';
    word1[1]=' ';
	  word1[2]=' ';
	  word1[3]=' ';
   	word1[4]=' ';
	  word1[5]=' ';
  	word1[6]=' ';
	  word1[7]=' ';
	  HPDL1414_show(word1);
	WR1_0;	
	WR2_0;
	A1_0;
	A0_0;
	D0_0;
	D1_0;
	D2_0;
	D3_0;
	D4_0;
	D5_0;
	D6_0;
	HAL_GPIO_WritePin(GPIOB, DS_SCL_Pin|DS_SDA_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SCL_7020_Pin|SDA_7020_Pin, GPIO_PIN_SET);
		SleepMode_Measure();	
		
		}
		
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

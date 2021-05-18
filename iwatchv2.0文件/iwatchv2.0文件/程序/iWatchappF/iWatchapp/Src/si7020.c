
#include "si7020.h" 
#include "myiic.h"
#include "delay.h"
void SI7020_Init(void)
{
        IIC3_Init();
}



//读取湿度
//返回值为湿度



uint16_t SI7020_ReadOneByte(uint8_t ReadAddr)
{                                  
        //uint8_t error=1;
        uint8_t temp[2];
        uint16_t value=0;
        IIC3_Start();
        IIC3_Send_Byte(SI7020_ADDRESS);
        IIC3_Wait_Ack();
        IIC3_Send_Byte(ReadAddr);
        IIC3_Wait_Ack();
        IIC3_Start();
        IIC3_Send_Byte(SI7020_ADDRESS|SI7020_READ);
        IIC3_Wait_Ack();
        delay_ms(200); 
        delay_ms(200);
        delay_ms(200);
        delay_ms(200);	
        temp[1]=IIC3_Read_Byte(1);
        temp[0]=IIC3_Read_Byte(0);
        IIC3_Stop();
        value=temp[0]|(temp[1]<<8);
        return value;
}

int16_t SI7020_Read_Humidity(void)
{        
        uint16_t value=0;
        double temp;
        value=SI7020_ReadOneByte(SI7020_HUMIDITY);
        temp=(double)value;
        temp=(temp/65536.0f)*125.0f-6.0f;
        return (int16_t)(temp*10);                                //返回湿度值，此处放大了10倍
}
//读取湿度
//返回值为湿度
int16_t SI7020_Read_Temperture(void)
{

        uint16_t value=0;
        double temp;
        value=SI7020_ReadOneByte(SI7020_TEMPERATURE);
        temp=(double)value;
        temp=(temp/65536.0f) * 175.72f - 46.85f;
        return (int16_t)(temp*10);                                        //返回温度值，此处放大了10倍
        
}
 












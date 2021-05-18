#include "myiic.h"
#include "delay.h"

//6050��ʼ��IIC
void IIC_Init(void)
{					     
	 HAL_GPIO_WritePin(GPIOB, SCL_345_Pin|SDA_345_Pin, GPIO_PIN_SET);
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	//SDA2_OUT();     //sda�����
	IIC_SDA_H;
	delay_us(8);	  	  
	IIC_SCL_H;
	delay_us(8);
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(8);
	IIC_SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
	delay_us(8);
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	//SDA2_OUT();//sda�����
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
	IIC_SCL_H;
 	delay_us(8);
	IIC_SDA_H;//����I2C���߽����ź�
	delay_us(8);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	//SDA2_IN();      //SDA����Ϊ����  
	//IIC2_SDA_H;
   
	IIC_SCL_H;
	delay_us(10);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_L;
	//SDA2_OUT();
	IIC_SDA_L;
	delay_us(10);
	IIC_SCL_H;
	delay_us(10);
	IIC_SCL_L;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_L;
	//SDA2_OUT();
	IIC_SDA_H;
	delay_us(10);
	IIC_SCL_H;
	delay_us(10);
	IIC_SCL_L;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{         
    u8 t;   
	//IIC_SDA_H;	    
    for(t=0;t<8;t++)
    {              
      IIC_SCL_L;//����ʱ�ӿ�ʼ���ݴ���  
			delay_us(10);
		if((txd&0x80)>>7)
			IIC_SDA_H;
		else
			IIC_SDA_L;
			  delay_us(10);  
		txd<<=1; 	
		IIC_SCL_H;	
	  delay_us(10);  		
    }	 
		
    IIC_SCL_L;
		delay_us(10); 

		IIC_SDA_H;
	//	delay_us(2); 
		
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L; 
        delay_us(1);
		    IIC_SCL_H;
        receive<<=1;
         if(READ_SDA)
				{
					receive|=1;
				}
         else
				 {
					 receive&=~0X01;
				 }	  
		delay_us(1); 
    }					 
    if (!ack)
		{ IIC_NAck();}//����nACK
    else
		{  IIC_Ack();} //����ACK   
    return receive;	
}








//��ʼ��IIC
void IIC2_Init(void)
{					     
	 HAL_GPIO_WritePin(GPIOB, DS_SCL_Pin|DS_SDA_Pin, GPIO_PIN_SET);
}
//����IIC��ʼ�ź�
void IIC2_Start(void)
{
	//SDA2_OUT();     //sda�����
	IIC2_SDA_H;
	delay_us(1);	  	  
	IIC2_SCL_H;
	delay_us(5);
 	IIC2_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(5);
	IIC2_SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
	delay_us(2);
}	  
//����IICֹͣ�ź�
void IIC2_Stop(void)
{
	//SDA2_OUT();//sda�����
	IIC2_SCL_L;
	IIC2_SDA_H;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC2_SCL_H; 
	delay_us(5);
	IIC2_SDA_H;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC2_Wait_Ack(void)
{
	u8 ucErrTime=0;
	//SDA2_IN();      //SDA����Ϊ����  
	//IIC2_SDA_H;
   
	IIC2_SCL_H;
	delay_us(2);	 
	while(READ2_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC2_Stop();
			return 1;
		}
	}
	IIC2_SCL_L;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC2_Ack(void)
{
	IIC2_SCL_L;
	//SDA2_OUT();
	IIC2_SDA_L;
	delay_us(2);
	IIC2_SCL_H;
	delay_us(2);
	IIC2_SCL_L;
}
//������ACKӦ��		    
void IIC2_NAck(void)
{
	IIC2_SCL_L;
	//SDA2_OUT();
	IIC2_SDA_H;
	delay_us(2);
	IIC2_SCL_H;
	delay_us(2);
	IIC2_SCL_L;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC2_Send_Byte(u8 txd)
{                        
    u8 t;   
	//SDA2_OUT(); 	    
    for(t=0;t<8;t++)
    {              
      IIC2_SCL_L;//����ʱ�ӿ�ʼ���ݴ���  
			delay_us(20);
		if((txd&0x80)>>7)
			IIC2_SDA_H;
		else
			IIC2_SDA_L;
			  delay_us(10);  
		txd<<=1; 	
		IIC2_SCL_H;	
	  delay_us(10);  		
    }	 
		
    IIC2_SCL_L;
		delay_us(2); 

		IIC2_SDA_H;
	//	delay_us(2); 
		
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC2_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	//SDA2_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC2_SCL_L; 
        delay_us(2);
		   IIC2_SCL_H;
        receive<<=1;
         if(READ2_SDA)
				{
					receive|=1;
				}
         else
				 {
					 receive&=~0X01;
				 }	  
		delay_us(1); 
    }					 
    if (!ack)
		{ IIC2_NAck();}//����nACK
    else
		{  IIC2_Ack();} //����ACK   
    return receive;
}




//��ʼ��IIC
void IIC3_Init(void)
{					     
	IIC3_SDA_H;
  IIC3_SCL_H;
}


//����IIC��ʼ�ź�
void IIC3_Start(void)
{
	//SDA2_OUT();     //sda�����
	IIC3_SDA_H;
	delay_us(1);	  	  
	IIC3_SCL_H;
	delay_us(1);
 	IIC3_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(1);
	IIC3_SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
	delay_us(1);
}	  
//����IICֹͣ�ź�
void IIC3_Stop(void)
{
	//SDA2_OUT();//sda�����
	IIC3_SCL_L;
	IIC3_SDA_H;//STOP:when CLK is high DATA change form low to high
 	delay_us(1);
	IIC3_SCL_H; 
	delay_us(1);
	IIC3_SDA_H;//����I2C���߽����ź�
	delay_us(1);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC3_Wait_Ack(void)
{
	u8 ucErrTime=0;
	//SDA2_IN();      //SDA����Ϊ����  
	//IIC2_SDA_H;
   
	IIC3_SCL_H;
	delay_us(2);	 
	while(READ3_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC3_Stop();
			return 1;
		}
	}
	IIC3_SCL_L;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC3_Ack(void)
{
	IIC3_SCL_L;
	//SDA2_OUT();
	IIC3_SDA_L;
	delay_us(1);
	IIC3_SCL_H;
	delay_us(1);
	IIC3_SCL_L;
}
//������ACKӦ��		    
void IIC3_NAck(void)
{
	IIC3_SCL_L;
	//SDA2_OUT();
	IIC3_SDA_H;
	delay_us(1);
	IIC3_SCL_H;
	delay_us(1);
	IIC3_SCL_L;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC3_Send_Byte(u8 txd)
{                        
    u8 t;   
	//SDA2_OUT(); 	    
    for(t=0;t<8;t++)
    {              
      IIC3_SCL_L;//����ʱ�ӿ�ʼ���ݴ���  
			delay_us(2);
		if((txd&0x80)>>7)
			IIC3_SDA_H;
		else
			IIC3_SDA_L;
			  delay_us(2);  
		txd<<=1; 	
		IIC3_SCL_H;	
	  delay_us(2);  		
    }	 
		
    IIC3_SCL_L;
		delay_us(2); 

		IIC3_SDA_H;
	//	delay_us(2); 
		
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC3_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	//SDA2_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC3_SCL_L; 
        delay_us(1);
		    IIC3_SCL_H;
        receive<<=1;
         if(READ3_SDA)
				{
					receive|=1;
				}
         else
				 {
					 receive&=~0X01;
				 }	  
		delay_us(1); 
    }					 
    if (!ack)
		{ IIC3_NAck();}//����nACK
    else
		{  IIC3_Ack();} //����ACK   
    return receive;
}


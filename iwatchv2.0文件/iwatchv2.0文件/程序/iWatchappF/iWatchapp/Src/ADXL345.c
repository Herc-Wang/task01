/************************************************************************************
�ļ����ƣ�adxl345.c
�ļ����ܣ�ADXL345���ٶȴ���������
�ļ����ߣ�Dennis-Zhou
��д���ڣ�2013��8��17��
************************************************************************************/

//=====����ͷ�ļ�=====
#include "adxl345.h"
#include "sys.h"
#include "delay.h"
#include "math.h"
#include "stdlib.h"
#include "myiic.h"
//=====�궨��=====
#define threshold 5  //��б�Ƕ���ֵ����λ���ȣ�

//=====ȫ�ֱ�������=====
short  x,y,z;      
short  angx,angy,angz;
short  actual_X,actual_Y,actual_Z;
extern u8  Angle[6];
u8 JDbuf[6];
/************************************************************************************
�������ƣ�u8 ADXL345_Init(void)
�������ܣ���ʼ��ADXL345
��ڲ�������
���ز����� 0����ʼ���ɹ�
   1����ʼ��ʧ��
************************************************************************************/
u8 ADXL345_Init(void)
{     
IIC_Init();        //��ʼ��IIC����
if(ADXL345_RD_Reg(DEVICE_ID)==0XE5)  //��ȡ����ID
{   
  //=====��ʼ��=====
  ADXL345_WR_Reg(DATA_FORMAT,0X0B); //�͵�ƽ�ж����,13λȫ�ֱ���,��������Ҷ���,16g����
  ADXL345_WR_Reg(BW_RATE,0x08);      //��������ٶ�Ϊ100Hz
  ADXL345_WR_Reg(POWER_CTL,0x08);     //����ʹ��,����ģʽ
 // ADXL345_WR_Reg(INT_ENABLE,0x80);    //DATA_READY �жϿ���

  ADXL345_WR_Reg(OFSX,0x00);
  ADXL345_WR_Reg(OFSY,0x00);
  ADXL345_WR_Reg(OFSZ,0x05);

 // ADXL345_WR_Reg(INT_MAP,0x00);       //���õ��ж�����1��
 
 // ADXL345_AUTO_Adjust((char*)&x,(char*)&y,(char*)&z); //�Զ�У׼

 // ADXL345_Read_Angle();    //��һ��ADX345����ֹУ׼���һ�ζ����ݴ���

  return 0;
}

return 1;             
}

/************************************************************************************
�������ƣ�void ADXL345_WR_Reg(u8 addr,u8 val)
�������ܣ�дADXL345�Ĵ���
��ڲ����� addr:�Ĵ�����ַ
   val:Ҫд���ֵ
���ز�������
************************************************************************************/   
void ADXL345_WR_Reg(uint8_t REG_Address,uint8_t REG_data)
{
    IIC_Start();                  //��ʼ�ź�
    IIC_Send_Byte(SlaveAddress);   //�����豸��ַ+д�ź�
	  IIC_Wait_Ack();
    IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ
    IIC_Wait_Ack();	
    IIC_Send_Byte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ 
	  IIC_Wait_Ack();
    IIC_Stop();                   //����ֹͣ�ź�   
}

/************************************************************************************
�������ƣ�u8 ADXL345_RD_Reg(u8 addr)
�������ܣ���ADXL345�Ĵ���
��ڲ����� addr:�Ĵ�����ַ
���ز����������ļĴ���ֵ
************************************************************************************/   
uint8_t ADXL345_RD_Reg(uint8_t REG_Address)  
{
    uint8_t REG_data;
    IIC_Start();                          //��ʼ�ź�
	  
    IIC_Send_Byte(SlaveAddress);           //�����豸��ַ+д�ź�
	  IIC_Wait_Ack();
    IIC_Send_Byte(REG_Address);            //���ʹ洢��Ԫ��ַ����0��ʼ	
	  IIC_Wait_Ack();
    IIC_Start();                          //��ʼ�ź�
    IIC_Send_Byte(SlaveAddress+1);         //�����豸��ַ+���ź�
	  IIC_Wait_Ack();
    //delay_ms(200);	
    REG_data=IIC_Read_Byte(0);              //�����Ĵ�������   
	  IIC_Stop();                           //ֹͣ�ź�
    return REG_data; 
} 

/************************************************************************************
�������ƣ�void ADXL345_RD_Avval(short *x,short *y,short *z)
�������ܣ���ȡADXL��ƽ��ֵ
��ڲ�����x,y,z:��ȡ10�κ�ȡƽ��ֵ
���ز�������
************************************************************************************/   
void ADXL345_RD_Avval(short *x,short *y,short *z)
{
short tx=0,ty=0,tz=0;   
u8 i; 
for(i=0;i<10;i++)
{
  ADXL345_RD_XYZ(x,y,z);
  delay_ms(10);
  tx+=(short)*x;
  ty+=(short)*y;
  tz+=(short)*z;   
}
*x=tx/10;
*y=ty/10;
*z=tz/10;
}

/************************************************************************************
�������ƣ�void ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval)
�������ܣ��Զ�У׼ADXL345
��ڲ�����xval,yval,zval:x,y,z���У׼ֵ
���ز�������
************************************************************************************/    
void ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval)
{
short tx,ty,tz;
u8 i;
short offx=0,offy=0,offz=0;

//=====��ʼ��=====
ADXL345_WR_Reg(POWER_CTL,0x00);     //�Ƚ�������ģʽ.
ADXL345_WR_Reg(INT_ENABLE,0x00);    //DATA_READY �жϹر�
delay_ms(100);
ADXL345_WR_Reg(DATA_FORMAT,0X2F); //�͵�ƽ�ж����,13λȫ�ֱ���,��������Ҷ���,16g����
ADXL345_WR_Reg(BW_RATE,0x0A);  //��������ٶ�Ϊ100Hz


ADXL345_WR_Reg(THRESH_ACT,0x01);    //�������ֵΪ187.5mgʱ�����ж�
// ADXL345_WR_Reg(DUR,0xF0);       //ʱ�䷶Χ10*625uS
    ADXL345_WR_Reg(ACT_INACT_CTL,0xEE); //ʹ��X��Y��Z�����Activity��Inactivity����
ADXL345_WR_Reg(INT_MAP,0x00);       //���õ��ж�����1��
ADXL345_WR_Reg(INT_ENABLE,0x80);    //DATA_READY�жϿ���
ADXL345_WR_Reg(POWER_CTL,0x28);     //����ʹ��,����ģʽ

//=====================================
ADXL345_WR_Reg(OFSX,0x00);
ADXL345_WR_Reg(OFSY,0x00);
ADXL345_WR_Reg(OFSZ,0x05);
delay_ms(12);
for(i=0;i<10;i++)
{
  ADXL345_RD_Avval(&tx,&ty,&tz);
  offx+=tx;
  offy+=ty;
  offz+=tz;
}   
offx/=10;
offy/=10;
offz/=10;
*xval=-offx/4;
*yval=-offy/4;
*zval=-(offz-256)/4;  
  ADXL345_WR_Reg(OFSX,*xval);
ADXL345_WR_Reg(OFSY,*yval);
ADXL345_WR_Reg(OFSZ,*zval);

}

/************************************************************************************
�������ƣ�void ADXL345_RD_XYZ(short *x,short *y,short *z)
�������ܣ���ȡ3���������
��ڲ�����x,y,z:��ȡ��������
���ز�������
************************************************************************************/     
void ADXL345_RD_XYZ(short *x,short *y,short *z)
{

//u8 i;

JDbuf[0]=ADXL345_RD_Reg(0X32);

JDbuf[1]=ADXL345_RD_Reg(0X33);

JDbuf[2]=ADXL345_RD_Reg(0X34);

JDbuf[3]=ADXL345_RD_Reg(0X35);

JDbuf[4]=ADXL345_RD_Reg(0X36);

JDbuf[5]=ADXL345_RD_Reg(0X37);

*x=(short)(((u16)JDbuf[1]<<8)+JDbuf[0]);     
*y=(short)(((u16)JDbuf[3]<<8)+JDbuf[2]);     
*z=(short)(((u16)JDbuf[5]<<8)+JDbuf[4]);    
}

/************************************************************************************
�������ƣ�void ADXL345_Read_Average(short *x,short *y,short *z,u8 times)
�������ܣ���ȡADXL345������times��,��ȡƽ��
��ڲ����� x,y,z:��ȡ��������
   times:��ȡ���ٴ�
���ز�������
************************************************************************************/     
void ADXL345_Read_Average(short *x,short *y,short *z,u8 times)
{
u8 i;
short tx,ty,tz;
*x=0;
*y=0;
*z=0;
if(times)//��ȡ������Ϊ0
{
  for(i=0;i<times;i++)//������ȡtimes��
  {
   ADXL345_RD_XYZ(&tx,&ty,&tz);
   *x+=tx;
   *y+=ty;
   *z+=tz;
   delay_ms(5);
  }
  *x/=times;
  *y/=times;
  *z/=times;
}
}

/************************************************************************************
�������ƣ�short ADXL345_Get_Angle(float x,float y,float z,u8 dir)
�������ܣ���ȡ�Ƕ�ֵ
��ڲ����� x,y,z:x,y,z������������ٶȷ���(����Ҫ��λ,ֱ����ֵ����)
   dir:Ҫ��õĽǶ�.0,��Z��ĽǶ�;1,��X��ĽǶ�;2,��Y��ĽǶ� 
���ز������Ƕ�ֵ����λ0.1��
************************************************************************************/     
short ADXL345_Get_Angle(float x,float y,float z,u8 dir)
{
float temp;
  float res=0;
switch(dir)
{
  case 0://����ȻZ��ĽǶ�
    temp=sqrt((x*x+y*y))/z;
    res=atan(temp);
    break;
  case 1://����ȻX��ĽǶ�
    temp=x/sqrt((y*y+z*z));
    res=atan(temp);
    break;
   case 2://����ȻY��ĽǶ�
    temp=y/sqrt((x*x+z*z));
    res=atan(temp);
    break;
  }
return res*1800/3.14;
}

/************************************************************************************
�������ƣ�u8 ADXL345_Read_Angle(void)
�������ܣ���ȡADX345����
��ڲ�������
���ز�������
************************************************************************************/
u8 ADXL345_Read_Angle(void)
{
//=====��ȡADXL345������=====       
ADXL345_Read_Average(&x,&y,&z,3);

//=====�õ��Ƕ�ֵ=====
angx=ADXL345_Get_Angle(x,y,z,1);   
angy=ADXL345_Get_Angle(x,y,z,2);  
angz=ADXL345_Get_Angle(x,y,z,0);

//=====ת������ʵֵ=====
actual_X = angx/10;
actual_Y = angy/10;
actual_Z = angz/10;

//===�� X,Y,Z 3����ĽǶ�ֵת�������浽Angle����=====
if(actual_X<0)
{
  Angle[0] = '-';
  Angle[1] = (u8)abs(actual_X);//ȡ����ֵ��ǿ��ת����u8��������
}
else
{
  Angle[0] = ' ';
  Angle[1] = (u8)actual_X;
}

if(actual_Y<0)
{
  Angle[2] = '-';
  Angle[3] = (u8)abs(actual_Y);
}
else
{
  Angle[2] = ' ';
  Angle[3] = (u8)actual_Y;
}

if(actual_Z<0)
{
  Angle[4] = '-';
  Angle[5] = (u8)abs(actual_Z);
}
else
{
  Angle[4] = ' ';
  Angle[5] = (u8)actual_Z;
}
/*
//=====�жϽǶ��Ƿ�����б���������+5�Ȼ�-5�ȣ��ͱ���=====
if(    Angle[1]>threshold || (Angle[0]=='-' && Angle[1]>threshold)
  || Angle[3]>threshold || (Angle[2]=='-' && Angle[3]>threshold)
  || Angle[5]>threshold || (Angle[4]=='-' && Angle[5]>threshold) )
{
  return 1; //����
}    
else
  return 0; //������
*/
return 1; //����
}

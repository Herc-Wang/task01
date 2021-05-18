/************************************************************************************
文件名称：adxl345.c
文件功能：ADXL345加速度传感器驱动
文件作者：Dennis-Zhou
编写日期：2013年8月17日
************************************************************************************/

//=====包含头文件=====
#include "adxl345.h"
#include "sys.h"
#include "delay.h"
#include "math.h"
#include "stdlib.h"
#include "myiic.h"
//=====宏定义=====
#define threshold 5  //倾斜角度阈值（单位：度）

//=====全局变量定义=====
short  x,y,z;      
short  angx,angy,angz;
short  actual_X,actual_Y,actual_Z;
extern u8  Angle[6];
u8 JDbuf[6];
/************************************************************************************
函数名称：u8 ADXL345_Init(void)
函数功能：初始化ADXL345
入口参数：无
返回参数： 0：初始化成功
   1：初始化失败
************************************************************************************/
u8 ADXL345_Init(void)
{     
IIC_Init();        //初始化IIC总线
if(ADXL345_RD_Reg(DEVICE_ID)==0XE5)  //读取器件ID
{   
  //=====初始化=====
  ADXL345_WR_Reg(DATA_FORMAT,0X0B); //低电平中断输出,13位全分辨率,输出数据右对齐,16g量程
  ADXL345_WR_Reg(BW_RATE,0x08);      //数据输出速度为100Hz
  ADXL345_WR_Reg(POWER_CTL,0x08);     //链接使能,测量模式
 // ADXL345_WR_Reg(INT_ENABLE,0x80);    //DATA_READY 中断开启

  ADXL345_WR_Reg(OFSX,0x00);
  ADXL345_WR_Reg(OFSY,0x00);
  ADXL345_WR_Reg(OFSZ,0x05);

 // ADXL345_WR_Reg(INT_MAP,0x00);       //配置到中断引脚1上
 
 // ADXL345_AUTO_Adjust((char*)&x,(char*)&y,(char*)&z); //自动校准

 // ADXL345_Read_Angle();    //读一次ADX345，防止校准后第一次读数据错误

  return 0;
}

return 1;             
}

/************************************************************************************
函数名称：void ADXL345_WR_Reg(u8 addr,u8 val)
函数功能：写ADXL345寄存器
入口参数： addr:寄存器地址
   val:要写入的值
返回参数：无
************************************************************************************/   
void ADXL345_WR_Reg(uint8_t REG_Address,uint8_t REG_data)
{
    IIC_Start();                  //起始信号
    IIC_Send_Byte(SlaveAddress);   //发送设备地址+写信号
	  IIC_Wait_Ack();
    IIC_Send_Byte(REG_Address);    //内部寄存器地址，请参考中文pdf22页
    IIC_Wait_Ack();	
    IIC_Send_Byte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
	  IIC_Wait_Ack();
    IIC_Stop();                   //发送停止信号   
}

/************************************************************************************
函数名称：u8 ADXL345_RD_Reg(u8 addr)
函数功能：读ADXL345寄存器
入口参数： addr:寄存器地址
返回参数：读到的寄存器值
************************************************************************************/   
uint8_t ADXL345_RD_Reg(uint8_t REG_Address)  
{
    uint8_t REG_data;
    IIC_Start();                          //起始信号
	  
    IIC_Send_Byte(SlaveAddress);           //发送设备地址+写信号
	  IIC_Wait_Ack();
    IIC_Send_Byte(REG_Address);            //发送存储单元地址，从0开始	
	  IIC_Wait_Ack();
    IIC_Start();                          //起始信号
    IIC_Send_Byte(SlaveAddress+1);         //发送设备地址+读信号
	  IIC_Wait_Ack();
    //delay_ms(200);	
    REG_data=IIC_Read_Byte(0);              //读出寄存器数据   
	  IIC_Stop();                           //停止信号
    return REG_data; 
} 

/************************************************************************************
函数名称：void ADXL345_RD_Avval(short *x,short *y,short *z)
函数功能：读取ADXL的平均值
入口参数：x,y,z:读取10次后取平均值
返回参数：无
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
函数名称：void ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval)
函数功能：自动校准ADXL345
入口参数：xval,yval,zval:x,y,z轴的校准值
返回参数：无
************************************************************************************/    
void ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval)
{
short tx,ty,tz;
u8 i;
short offx=0,offy=0,offz=0;

//=====初始化=====
ADXL345_WR_Reg(POWER_CTL,0x00);     //先进入休眠模式.
ADXL345_WR_Reg(INT_ENABLE,0x00);    //DATA_READY 中断关闭
delay_ms(100);
ADXL345_WR_Reg(DATA_FORMAT,0X2F); //低电平中断输出,13位全分辨率,输出数据右对齐,16g量程
ADXL345_WR_Reg(BW_RATE,0x0A);  //数据输出速度为100Hz


ADXL345_WR_Reg(THRESH_ACT,0x01);    //检测活动的阈值为187.5mg时产生中断
// ADXL345_WR_Reg(DUR,0xF0);       //时间范围10*625uS
    ADXL345_WR_Reg(ACT_INACT_CTL,0xEE); //使能X、Y、Z三轴的Activity和Inactivity功能
ADXL345_WR_Reg(INT_MAP,0x00);       //配置到中断引脚1上
ADXL345_WR_Reg(INT_ENABLE,0x80);    //DATA_READY中断开启
ADXL345_WR_Reg(POWER_CTL,0x28);     //链接使能,测量模式

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
函数名称：void ADXL345_RD_XYZ(short *x,short *y,short *z)
函数功能：读取3个轴的数据
入口参数：x,y,z:读取到的数据
返回参数：无
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
函数名称：void ADXL345_Read_Average(short *x,short *y,short *z,u8 times)
函数功能：读取ADXL345的数据times次,再取平均
入口参数： x,y,z:读取到的数据
   times:读取多少次
返回参数：无
************************************************************************************/     
void ADXL345_Read_Average(short *x,short *y,short *z,u8 times)
{
u8 i;
short tx,ty,tz;
*x=0;
*y=0;
*z=0;
if(times)//读取次数不为0
{
  for(i=0;i<times;i++)//连续读取times次
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
函数名称：short ADXL345_Get_Angle(float x,float y,float z,u8 dir)
函数功能：获取角度值
入口参数： x,y,z:x,y,z方向的重力加速度分量(不需要单位,直接数值即可)
   dir:要获得的角度.0,与Z轴的角度;1,与X轴的角度;2,与Y轴的角度 
返回参数：角度值：单位0.1°
************************************************************************************/     
short ADXL345_Get_Angle(float x,float y,float z,u8 dir)
{
float temp;
  float res=0;
switch(dir)
{
  case 0://与自然Z轴的角度
    temp=sqrt((x*x+y*y))/z;
    res=atan(temp);
    break;
  case 1://与自然X轴的角度
    temp=x/sqrt((y*y+z*z));
    res=atan(temp);
    break;
   case 2://与自然Y轴的角度
    temp=y/sqrt((x*x+z*z));
    res=atan(temp);
    break;
  }
return res*1800/3.14;
}

/************************************************************************************
函数名称：u8 ADXL345_Read_Angle(void)
函数功能：读取ADX345数据
入口参数：无
返回参数：无
************************************************************************************/
u8 ADXL345_Read_Angle(void)
{
//=====读取ADXL345的数据=====       
ADXL345_Read_Average(&x,&y,&z,3);

//=====得到角度值=====
angx=ADXL345_Get_Angle(x,y,z,1);   
angy=ADXL345_Get_Angle(x,y,z,2);  
angz=ADXL345_Get_Angle(x,y,z,0);

//=====转换成真实值=====
actual_X = angx/10;
actual_Y = angy/10;
actual_Z = angz/10;

//===将 X,Y,Z 3个轴的角度值转换并保存到Angle数组=====
if(actual_X<0)
{
  Angle[0] = '-';
  Angle[1] = (u8)abs(actual_X);//取绝对值并强制转换成u8数据类型
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
//=====判断角度是否发生倾斜，如果超过+5度或-5度，就报警=====
if(    Angle[1]>threshold || (Angle[0]=='-' && Angle[1]>threshold)
  || Angle[3]>threshold || (Angle[2]=='-' && Angle[3]>threshold)
  || Angle[5]>threshold || (Angle[4]=='-' && Angle[5]>threshold) )
{
  return 1; //报警
}    
else
  return 0; //不报警
*/
return 1; //报警
}

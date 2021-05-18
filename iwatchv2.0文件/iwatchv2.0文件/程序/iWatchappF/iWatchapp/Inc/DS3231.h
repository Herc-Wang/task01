
#ifndef __DS3231_H__
#define __DS3231_H__

#include "sys.h"
typedef struct 
{
	u8 hour;
	u8 min;
	u8 sec;			
	u8 w_year;
	u8 w_month;
	u8 w_date;
	u8 week;		 
}_calendar_obj;	
				 
extern _calendar_obj calendar;	//日历结构体

extern u8 const mon_table[12];	//月份日期数据表

void I2cByteWrite(u8 addr,u8 bytedata);
void DS3231_Init(void);
void get_show_time(void);      
void DS3231_Set(u8 syear,u8 smon,u8 sday,u8 week,u8 hour,u8 min,u8 sec);//设置时间	
unsigned short B_BCD(u8 val);
u8 BCD2ASC_H(u8 bcd);
u8 BCD2ASC_L(u8 bcd);
#endif



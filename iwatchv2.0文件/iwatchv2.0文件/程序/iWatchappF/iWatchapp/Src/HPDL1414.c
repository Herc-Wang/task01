#include "HPDL1414.h"
#include "delay.h"   
#include "stm32f1xx_hal.h"

//write_1414('a',0)
void write_1414(u8 word,u8 dig)
{
	u8 bit[7]={' ',' ',' ',' ',' ',' ',' '};
		if(dig==0)
		{
			A0_0;
			A1_0;
		}
			else if(dig==1)
			{
			A0_1;
			A1_0;
			}
			else if(dig==2)
			{
			A0_0;
			A1_1;
			}
			else if(dig==3)
			{
			A0_1;
			A1_1;
			}
			else
			{
	  	}
			// word=~word;
				bit[0]=word&1;
				bit[1]=(word&2)>>1;
				bit[2]=(word&4)>>2;	
				bit[3]=(word&8)>>3;	
				bit[4]=(word&16)>>4;
				bit[5]=(word&32)>>5;
				bit[6]=(word&64)>>6;
			
					    if(bit[0]==1)
					{
					D0_1;
					}
					else
					{
					D0_0;
					}
							if(bit[1]==1)
					{
					D1_1;
					}
					else
					{
					D1_0;
					}
							if(bit[2]==1)
					{
					D2_1;
					}
					else
					{
					D2_0;
					}
							if(bit[3]==1)
					{
					D3_1;
					}
					else
					{
					D3_0;
					}
							if(bit[4]==1)
					{
					D4_1;
					}
					else
					{
					D4_0;
					}
							if(bit[5]==1)
					{
					D5_1;
					}
					else
					{
					D5_0;
					}
							if(bit[6]==1)
					{
					D6_1;
					}
					else
					{
					D6_0;
					}
		
	
}
void HPDL1414_show( u8 word[8])
{
	
	

write_1414(word[0],3);
WR1_0;	
delay_ms(1);
WR1_1;
delay_ms(20);	
write_1414(word[1],2);
WR1_0;	
delay_ms(1);
WR1_1;	
delay_ms(20);	
write_1414(word[2],1);
WR1_0;	
delay_ms(1);
WR1_1;	
delay_ms(20);	
write_1414(word[3],0);
WR1_0;	
delay_ms(1);
WR1_1;
delay_ms(20);


	
	
write_1414(word[4],3);
WR2_0;	
delay_ms(1);
WR2_1;
delay_ms(20);
write_1414(word[5],2);
WR2_0;	
delay_ms(1);
WR2_1;	
delay_ms(20);		
write_1414(word[6],1);
WR2_0;	
delay_ms(1);
WR2_1;	
delay_ms(20);
write_1414(word[7],0);
WR2_0;	
delay_ms(1);
WR2_1;
delay_ms(20);


	
}


 

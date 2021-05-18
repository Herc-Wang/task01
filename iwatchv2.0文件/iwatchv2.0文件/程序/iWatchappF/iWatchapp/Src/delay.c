
#include "sys.h"
#include "delay.h"
void delay_ms(u16 ms)
{
  unsigned int x , y;
  for(x = ms; x > 0; x--)          
    for(y = 250 ; y > 0 ; y--);
}


void delay_us(u32 us)
{
    u8	i = 0;
    u8 delay = us;
    while (delay--)
    {
       i = 100;// i = 10;
        while (i--);
    }
}

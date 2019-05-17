/*
 * GccApplication5.c
 *
 * Created: 5/15/2019 9:38:10 AM
 * Author : Hasa
 */ 

#include <avr/io.h>
#define LED PB0

int main(void)
{
    uint8_t timerOverflowcount=0;
	DDRB=0xff; //PORTB as output
	TCNT0=0x00;
	TCCR0=(1<<CS00)|(1<<CS02);
    while (1) 
    {
		while((TIFR & 0x01)==0);
		
		TCNT0=0X00;
		
		TIFR=0X01;//clear timer1 overflow flag
		timerOverflowcount++;
		if(timerOverflowcount>=254)
		{
				
			PORTB^=(0X01<<LED);
			timerOverflowcount=0;
		}
    }
}


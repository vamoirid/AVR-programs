#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << PINB0);    //Data Direction Register output PINB0
	DDRB &= ~(1 << PINB1);   //Data Direction Register input PINB1
	PORTB |= (1 << PINB1);   //Set PINB1 to a HIGH reading 
	
	while(1)
	{
		PORTB ^= (1 << PINB0);
		
		if (bit_is_clear(PINB, 1))
		{
			_delay_ms(10);
		}
		else
		{
			_delay_ms(100);
		}
	}
	
	return 0;
}
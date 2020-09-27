#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= ((1 << 4) | (1 << 5));      // Data Direction Register output for only pin0 on portB
	
	
	while(1)
	{
		PORTD |= ((1 << 4) | (1 << 5));      // instead of all this i could use                                      
		_delay_ms(10);                      // PORTB ^= (1 << PINB0);
		PORTD &= ~((1 << 4) | (1 << 5));    // _delay_ms(10);
		_delay_ms(10);                     // which is faster.
	}                                      
	
	return 0;
}
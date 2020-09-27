#include <avr/io.h>
#include <inttypes.h>

int main(void)
{
	DDRB |= (1 << PINB0);     //Data Direction Register sets PINB0 as an output.
	PORTB ^= (1 << PINB0);    //Toggling PINB0 to HIGH.We don't want to SET it tO HIGH (like PINB2) because then it will always be HIGH.
	DDRB |= (1 << PINB1);     //Data Direction Register sets PINB1 as an output.
	DDRB &= ~(1 << PINB2);    //Data Direction Refister sets PINB2 as an input.
	PORTB |= (1 << PINB2);    //Set PINB2 to 5V.
	
	int pressed = 0; 
	
	while(1)
	{	
		if (bit_is_clear(PINB, 2))
		{
			if (pressed == 0)
			{
				PORTB ^= (1 << PINB0);
				PORTB ^= (1 << PINB1);
				pressed = 1;
			}	
		}
		else
		{
			pressed = 0;
		}
	}

	return 0;
}
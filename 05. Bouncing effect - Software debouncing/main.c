#include <avr/io.h>

int main(void)
{
	DDRB |= (1 << PINB0);        //Set Direction as output for PINB0
	PORTB ^= (1 << PINB0);       //Toggle PINB0 from the begining.
	DDRB |= (1 << PINB1);        //Set Direction as output for PINB1
	DDRB &= ~(1 << PINB2);       //Set Direction as input for PINB2
	PORTB |= (1 << PINB2);       //Set PINB2 on a high reading
	
	int pressed = 0;
	int pressed_confidence_level = 0;
	int released_confidence_level = 0;
	
	while(1)
	{
		if (bit_is_clear(PINB, 2))
		{
			pressed_confidence_level++;
			
			if (pressed_confidence_level > 200)
			{
				if (pressed == 0)
				{
					PORTB ^= (1 << PINB0);
					PORTB ^= (1 << PINB1);
					pressed = 1;
					pressed_confidence_level = 0;
				}	
			}
		}
		else
		{
			released_confidence_level++;
			
			if (released_confidence_level > 200)
			{
				pressed = 0;
				released_confidence_level = 0;
			}	
		}
	}
	return 0;
}
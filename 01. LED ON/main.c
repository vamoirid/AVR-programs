#include <avr/io.h>

void main(void) 
{
	DDRB = 0b00000001;
	PORTB = 0b00000001;
	
	while(1)
	{
		
	}
	
	return 0;
}
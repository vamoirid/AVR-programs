/*
 * ButtonLibraryTest1.c
 *
 * Created: 5/11/2017 3:18:42 AM
 * Author : Vasileios Amoiridis
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "ButtonPress.h"


int main(void)
{
    
	DDRD |= ((1 << PIND0)|(1 << PIND1)|(1 << PIND2));
	DDRD &= ~((1 << PIND3)|(1 << PIND4)|(1 << PIND5));
	
	PORTD &= ~((1 << PIND0)|(1 << PIND1)|(1 << PIND2));
	PORTD |= ((1 << PIND3)|(1 << PIND4)|(1 << PIND5));

	ButtonInit(3);
    while (1) 
    {
		if(isButtonPressed(PIND, 3, 100, 1))
		{
			PORTD ^= (1 << PIND0);
		}
		if(isButtonPressed(PIND, 4, 100, 2))
		{
			PORTD ^= (1 << PIND1);
		}
		if (isButtonPressed(PIND, 5, 100, 3))
		{
			PORTD ^= (1 << PIND2);
		}
    }

	return 0;
}


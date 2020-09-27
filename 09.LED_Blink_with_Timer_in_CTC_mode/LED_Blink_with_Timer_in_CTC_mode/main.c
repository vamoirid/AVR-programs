/*
 * LED_Blink_with_Timer_in_CTC_mode.c
 *
 * Created: 5/12/2017 1:23:51 AM
 * Author : Vasileios Amoiridis
 */ 

#include <avr/io.h>


int main(void)
{
    DDRB |= (1 << DDB0);                               //Set PINB0 as output
	PORTB &= ~(1 << PORTB0);                           //Set PINB0 to 0v
	TCCR1B |= (1 << WGM12);                            //Set Timer to CTC mode
	TCCR1B |= ((1 << CS10) | (1 << CS11));             //Set Timer to 64 prescale
	OCR1A = 15624;                                     //Set CTC compare value to 1Hz at 1MHz AVR Clock with prescale at 64

    while (1) 
    {
		if (TIFR & (1 << OCF1A))                       //Check if OCF1A flag is set
		{ 
			PORTB ^= (1 << PORTB0);                    //Toggle the LED

			TIFR |= (1 << OCF1A);                      //Clear OCF1A flag (by setting it)
		}
    }
	return 0;
}


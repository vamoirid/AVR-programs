/*
 * 08.LED_Blink_with_prescaled_Timer.c
 *
 * Created: 5/12/2017 1:37:32 AM
 * Author : Vasileios Amoiridis
 */ 

#include <avr/io.h>


int main(void)
{
    DDRB |= (1 << DDB0);                                                        //Set PINB0 as output
	PORTB &= ~(1 << PORTB0);                                                    //Set PINB0 to 0V
	TCCR1B |= ((1 << CS10) | (1 << CS11));                                      //Set Timer to 64 prescaler
	 
    while (1) 
    {
		if (TCNT1 >= 15624)
		{
			PORTB ^= (1 << PORTB0);                                             //Toggle PINB0
			TCNT1 = 0;                                                          //Resetting counter
		}
    }
}


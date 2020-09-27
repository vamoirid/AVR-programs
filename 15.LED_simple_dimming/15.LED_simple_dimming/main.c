/*
 * 15.LED_simple_dimming.c
 *
 * Created: 5/21/2017 6:25:18 PM
 * Author : Vasileios Amoiridis
 */ 

#define F_CPU 1000000ul

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << DDB3);                                 //Set PINB3 (OC0) as output
	PORTB &= ~(1 << PORTB3);                             //Clear PINB3
	TCCR0 |= (1 << CS01);                                //Set a prescaler of 8
	TCCR0 |= ((1 << WGM00) | (WGM01));                   //Set Timer0 on Fast PWM mode
	TCCR0 |= (1 << COM01);                               //Clear OC0 on Compare Match and set it on BOTTOM 
	OCR0 = 0;

	int dutyCycle = 0;

    while (1) 
    {
		while (dutyCycle < 255)
		{
			OCR0 = dutyCycle++;
			_delay_ms(3);
		}

		while (dutyCycle > 0)
		{
			OCR0 = dutyCycle--;
			_delay_ms(3);
		}
    }
}

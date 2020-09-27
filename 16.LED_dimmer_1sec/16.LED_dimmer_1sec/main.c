/*
 * 16.LED_dimmer_1sec.c
 *
 * Created: 5/22/2017 11:41:42 PM
 * Author : Vasileios Amoiridis
 */ 

#define F_CPU 1000000ul

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long int milliseconds = 0;

ISR(TIMER0_COMP_vect)
{
	++milliseconds;
}


int main(void)
{
	DDRD |= (1 << DDD5);                                     //Set PIND5 (OC1A) as output
	PORTD &= ~(1 << PORTD5);                                 //Clear PIND5
	
	//Timer0 use for counting milliseconds

	TCCR0 |= (1 << CS01);                                    //Set a prescaler of 8
	TCCR0 |= (1 << WGM01);                                   //Enable CTC mode
	OCR0 = 125;                                              //Set a 1kHz clock at 1MHz AVR clock, with a prescaler of 8
	sei();                                                   //Enable global interrupts
	TIMSK |= (1 << OCIE0);                                    //Enable Compare interrupt for Timer0


	//Timer1 use for 10-bit Fast PWM mode

	TCCR1B |= (1 << CS11);                                   //Set a prescaler of 8
	TCCR1A |= ((1 << WGM10) | (1 << WGM11));                 //Enable 10-bit Fast PWM mode
	TCCR1B |= (1 << WGM12);                                  //Remaining bits for enabling 10-bit Fast PWM
	OCR1A = 0;
	TCCR1A |= (1 << COM1A1);                                 //Clear OC1A on Compare Match and set it on BOTTOM

	//int dutyCycle = 0;
	
	while(1)
	{
		TCNT0 = 0;
		milliseconds = 0;
		OCR1A = 0;
		TCNT1 = 0;

		while (milliseconds < 1000)
		{
			OCR1A += 8;
		}
		
		milliseconds = 0;
		TCNT0 = 0;
		TCNT1 = 0;

		while (milliseconds < 1000)
		{
			OCR1A -= 8;
		}
	}
}
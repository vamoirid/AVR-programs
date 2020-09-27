/*
 * 11.LED_Blink_with_Interrupts.c
 *
 * Created: 5/15/2017 4:13:01 AM
 * Author : Vasileios Amoiridis
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PORTB0);                                          //Toggle PINB0
}

int main(void)
{
	sei();                                                          //Enable global interrupts
    DDRB |= (1 << DDB0);                                            //Set PINB0 as output
	PORTB &= ~(1 << PORTB0);                                        //Set PINB0 to 0V reading 
	TCCR1B |= (1 << WGM12);                                         //Configure timer in CTC mode
	TCCR1B |= ((1 << CS10) | (1 << CS11));                          //Set a prescale of 64
	OCR1A = 15624;                                                  //Set 1Hz cycle in 1MHz AVR clock with a prescaler at 64
	TIMSK |= (1 << OCIE1A);                                         //Enable CTC Interrupt
	                                    
    while (1) 
    {
    }
}




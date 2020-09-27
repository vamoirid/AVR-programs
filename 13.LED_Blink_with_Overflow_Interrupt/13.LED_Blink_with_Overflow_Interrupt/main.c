/*
 * 13.LED_Blink_with_Overflow_Interrupt.c
 *
 * Created: 5/15/2017 10:58:15 PM
 * Author : Vasileios Amoiridis
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect)
{
	PORTB ^= (1 << PORTB0);
}

int main(void)
{
    DDRB |= (1 << DDB0);
	PORTB &= ~(1 << PORTB0);
	TCCR1B |= (1 << CS11);
	sei();
	TIMSK |= (1 << TOIE1);

    while (1) 
    {
    }
}


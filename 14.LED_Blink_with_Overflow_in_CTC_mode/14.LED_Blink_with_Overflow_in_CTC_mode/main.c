/*
 * 14.LED_Blink_with_Overflow_in_CTC_mode.c
 *
 * Created: 5/15/2017 11:09:36 PM
 * Author : Vasileios Amoiridis
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect)
{
	PORTB ^= (1 << PORTB0);
	TCNT1 = 49910;
}

int main(void)
{
    DDRB |= (1 << DDB0);
	PORTB &= ~(1 << PORTB0);
	TCCR1B |= (1 << CS11);
	TIMSK |= (1 << TOIE1);
	sei();
	TCNT1 = 49910;
    while (1) 
    {
    }
}


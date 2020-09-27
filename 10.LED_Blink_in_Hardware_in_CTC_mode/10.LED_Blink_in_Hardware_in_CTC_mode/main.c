/*
 * 10.LED_Blink_in_Hardware_in_CTC_mode.c
 *
 * Created: 5/15/2017 3:57:35 AM
 * Author : Vasileios Amoiridis
 */ 

#include <avr/io.h>


int main(void)
{
    DDRD |= (1 << DDD5);                                  //This is the OC1A pin
	TCCR1B |= ((1 << CS10) | (1 << CS11));               //Prescaler of 64
	TCCR1B |= (1 << WGM12);                               //Configure Timer in CTC mode
	OCR1A = 15624;                                        //Set 1Hz time interrupt in 1MHz AVR clock with a prescaler of 64
	TCCR1A |= (1 << COM1A0);                              //Toggle OC1A and OC1B pins.

    while (1) 
    {
    }
}


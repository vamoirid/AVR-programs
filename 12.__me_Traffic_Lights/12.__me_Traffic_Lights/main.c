/*
 * 12.__me_Traffic_Lights.c
 *
 * Created: 5/15/2017 4:47:06 AM
 * Author : Vasileios Amoiridis
 */ 

 #define F_CPU 1000000ul

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "ButtonPress.h"

//Naming the pins

static const uint8_t RedCarLight = 0;
static const uint8_t YellowCarLight = 1;
static const uint8_t GreenCarLight = 2;
static const uint8_t RedPedLight = 4;
static const uint8_t GreenPedLight = 5;
static const uint8_t ButtonPin = 6;

//Value for counting milliseconds

volatile unsigned long int milliseconds = 0;

//Interrupt Function

ISR(TIMER2_COMP_vect)
{
	++milliseconds;
}

int main(void)
{
	//Configuring outputs

	DDRB |= (1 << RedCarLight);
	DDRB |= (1 << YellowCarLight);
	DDRB |= (1 << GreenCarLight);
	DDRD |= (1 << RedPedLight);
	DDRD |= (1 << GreenPedLight);

	//Configuring inputs

	DDRD &= ~(1 << ButtonPin);
    
	//Setting outputs to LOW reading

	PORTB &= ~(1 << RedCarLight);
	PORTB &= ~(1 << YellowCarLight);
	PORTB &= ~(1 << GreenCarLight);
	PORTD &= ~(1 << RedPedLight);
	PORTD &= ~(1 << GreenPedLight);

	//Setting inputs to HIGH reading

	PORTD |= (1 << ButtonPin);

	//ButtonPin states

	uint8_t SwitchState = 0;
	uint8_t PreviousSwitchState = 0;

	//Variable in order to keep track of time

	int CurrentTime = 0;

	//Variable in order to check the first time in the while loop

	int FirstTime = 1;

	//About Timer1

	TCCR1B |= ((1 << CS10) | (1 << CS11));                     //Set a prescaler of 64 in 16-bit Timer1

	//About Timer2

	TCCR2 |= (1 << CS21);                 //Set a prescale of 8 in 8-bit Timer2
	OCR2 = 125;                           //Set 1kHz cycle at 1MHz AVR clock with a prescale of 8
	TCCR2 |= (1 << WGM21);                //Set 8-bit Timer2 in CTC mode
	sei();                                //Set global interrupt enable bit
	TIMSK |= (1 << OCIE2);                //Enable CTC interrupt for timer2

	//Initialize Buttons for ButtonPress.h

	ButtonInit(1);

	//TEST CODE

	int i;

	for (i = 0; i < 3; i++)
	{
		TCNT1 = 0;
		CurrentTime = TCNT1;

		do
		{
			PORTB |= ((1 << RedCarLight) | (1 << YellowCarLight) | (1 << GreenCarLight));
			PORTD |= ((1 << RedPedLight) | (1 << GreenPedLight));
		} while (TCNT1 - CurrentTime < 15624);

		do
		{
			PORTB &= ~((1 << RedCarLight) | (1 << YellowCarLight) | (1 << GreenCarLight));
			PORTD &= ~((1 << RedPedLight) | (1 << GreenPedLight));
		} while (TCNT1 - CurrentTime < 2*15624);
	}

	//Default state for the lights
	
	PORTB |= (1 << GreenCarLight);
	PORTD |= (1 << RedPedLight);

	//Initialize timer

	TCNT1 = 0;

	//Loop operation

    while (1) 
    {
		SwitchState = isButtonPressed(PIND, 6, 200, 1);

		if (SwitchState == 1)
		{	
			TCNT1 = 0;
			
			if (FirstTime == 1)
			{
				FirstTime = 0;
			}
			else 
			{
				do 
				{
				} while (milliseconds < 6000);
			}
			if (SwitchState != PreviousSwitchState)
			{	
				PORTB &= ~(1 << GreenCarLight);
				TCNT1 = 0;

				do {
					PORTB |= (1 << YellowCarLight);
				} while (TCNT1 < 3*15624);

				PORTB &= ~(1 << YellowCarLight);
				PORTD &= ~(1 << RedPedLight);

				for (i = 0; i < 2; i++)
				{
					TCNT1 = 0;
					

					do 
					{
						PORTB |= (1 << RedCarLight);
						PORTD |= (1 << GreenPedLight);
					} while (TCNT1 < 3*15624);
				}

				PORTD &= ~(1 << GreenPedLight);
				PORTD |= (1 << RedPedLight);
				TCNT1 = 0;
				
				do 
				{
				} while (TCNT1 < 3*15624);
			}
			milliseconds = 0;
		}
		PORTB &= ~(1 << RedCarLight);
		PORTD &= ~(1 << GreenPedLight);
		PORTB |= (1 << GreenCarLight);
		PORTD |= (1 << RedPedLight);

		PreviousSwitchState = SwitchState;
    }
	return 0;
}
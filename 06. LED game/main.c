#include <avr/io.h>
#include <util/delay.h>

void ProcessPressedButton(void);
void ProcessReleasedButton(void);

int pressed = 0;
int LEDNumber = 0;
int i;

int main(void)
{
	DDRD = 0b00111111;
	PORTD = 0b11000000;
	
	while(1)
	{
		if(bit_is_clear(PIND, 6))
		{
			ProcessPressedButton();
		}
		else
		{
			ProcessReleasedButton();
		}
	}
	return 0;
}

void ProcessPressedButton(void)
{
	if (pressed == 0)
	{
		pressed = 1;
		PORTD |= (1 << LEDNumber);
		LEDNumber++;
		if (LEDNumber > 5)
		{
			for (i = 0; i < 10; i++)         //When somebody wins this happens.
			{
				PORTD = 0b11111111;
				_delay_ms(10);
				PORTD = 0b11000000;
				_delay_ms(10);
			}
			PORTD = 0b11000000;                 //Initialize  in order to play again.
		LEDNumber = 0;
		}
	}
}

void ProcessReleasedButton(void)
{
	pressed = 0;
}






























/*include <avr/io.h>
#include <util/delay.h>

void ProcessPressedButton(void);
void ProcessReleasedButton(void);

int pressed = 0;
int pressed_confidence_level = 0;
int released_confidence_level = 0;
int LEDNumber = 0;

int main(void)
{
	//Initialization area. Setting up ports and data direction registers.
	DDRB = 0b10111111;
	PORTB = 0b01000000;
	
	while(1)
	{
		if (bit_is_clear(PINB, 6))
		{
			ProcessPressedButton();
		}
		else
		{
			ProcessReleasedButton();
		}
	}
	return 0;
}

void ProcessPressedButton(void)
{
	pressed_confidence_level++;			
			if (pressed_confidence_level > 500)
			{
				if (pressed == 0)
				{
					pressed = 1;
					PORTB |= 1 << LEDNumber;
					LEDNumber++;
					if(LEDNumber > 5)
					{
						for (int i =0; i < 10; i++)
						{
							PORTB = 0b01000000;
							_delay_ms(10);
							PORTB = 0b01111111;
							_delay_ms(10);
						}
						LEDNumber = 0;
						PORTB = 0b01000000;
					}
				}
				pressed_confidence_level = 0;
			}
}

void ProcessReleasedButton(void)
{
	released_confidence_level++;
			if (released_confidence_level > 500)
			{
				pressed = 0;
			}
			released_confidence_level = 0;
}*/
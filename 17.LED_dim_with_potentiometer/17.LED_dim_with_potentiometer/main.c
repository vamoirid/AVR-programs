/*
 * 17.LED_dim_with_potentiometer.c
 *
 * Created: 5/23/2017 12:07:55 PM
 * Author : Vasileios Amoiridis
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

ISR(ADC_vect)
{
	uint8_t LowValue = ADCL;
	uint16_t AdcResult = ((ADCH << 8) | LowValue);

	OCR1A = AdcResult;

	ADCSRA |= (1 << ADSC);
}

int main(void)
{
	DDRD |= (1 << DDD5);                                                                    //Set PIND5 (OC1A) as output
	PORTD |= (1 << PORTD5);                                                                 //Clear PIND5

	//Configure ADC

	ADMUX |= (1 << REFS0);                                                                  //Set Reference Voltage to Vcc
	ADCSRA |= (1 << ADIE);																	//Enable ADC Interrupt
	ADCSRA |= (1 << ADPS2);																	//Enable a prescaler of 16
	ADCSRA |= (1 << ADEN);																	//Enable ADC mode of PORTA
	ADMUX |= (1 << MUX0);                                                                   //Set PINA1 as input
	sei();																					//Enable global Interrupts
	ADCSRA |= (1 << ADSC);																	//Start first conversion

	//Configure Timer1 for 10-bit Fast PWM mode

	TCCR1A |= (1 << WGM10) | (1 << WGM11);													//Configure 10-bit Fast PWM mode
	TCCR1B |= (1 << WGM12);																	//Enable remaining bits
	TCCR1B |= (1 << CS11);																	//Set a prescaler of 8
	TCCR1A |= (1 << COM1A1);                                                                //Clear OC1A bit on Compare Match and set it on BOTTOM
	OCR1A = 0;

	while(1)
	{
	}
}

/*uint16_t readAdc(uint8_t chan)
{
	ADMUX = (chan & 7) | (1<<REFS0);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1<<ADSC));

	return ADC;
}*/
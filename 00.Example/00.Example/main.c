/*
 * 00.Example.c
 *
 * Created: 5/13/2017 9:40:44 PM
 * Author : Vasileios Amoiridis
 */ 

#include <avr/io.h>

ISR(ADC_vect)
{
	uint8_t temp_low;
	uint16_t adc_value;
	
	temp_low = ADCL;
	adc_value = (ADCH << 8) | temp_low;
	
	ADCSRA |= (1 << ADSC);                         //Start next conversion
}

int main(void)
{
	ADMUX |= (1 << REFS0);                         //Use Vcc as reference
	ADCSRA |= (1 << ADIE);                         //Enable ADC Interrupt
	ADMUX |= (1 << MUX0);                          //Use Channel 1
	ADCSRA |= ((1 << ADPS0) | (1 << ADPS1));       //Use a prescaler of 8
	ADCSRA |= (1 << ADEN);                         //Enable ADC Mode for PORTA 
	sei();                                         //Enable global Interrupts
	ADCSRA |= (1 << ADSC);                         //Start conversion
	   

	while(1)
	{
		
	}
}
































/*
 * 18.UART_Tutorial.c
 *
 * Created: 6/23/2017 4:58:39 PM
 * Author : Vasileios Amoiridis
 */ 

#define F_CPU 1000000L

#include <avr/io.h>
//#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "ButtonPress.h"
#include "UART.h"

unsigned char N;

int main(void)
{
	//Pin Configuration

	DDRB &= ~(1 << DDB0);                              //Set ButtonPin as input
	DDRB |= (1 << DDB1);                               //Set LEDPin as output
	PORTB |= (1 << PORTB0);                            //Set ButtonPin HIGH
	PORTB &= ~(1 << PORTB1);                           //Set LEDPin LOW

	 UART_Init(4800,0,8,N,1);
	 //Button Configuration
	 ButtonInit(1);
	         
    
    while (1) 
    {
		if (isButtonPressed(PINB, 0, 300, 1))                  
		{
			PORTB ^= (1 << PORTB1);            //Toggle Pin
			//UART_Transmit('c');
			UART_Send_String("ab");
			
			//while (! (UCSRA & (1 << UDRE)));
			//UDR = 0b11110000;
		}     
    }
}
/*
 * Receive_Uart.c
 *
 * Created: 11/2/2017 12:30:40 PM
 * Author : Vasileios Amoiridis
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "UART.h"
#include "lcd.h"

#define Data_Port			PORTA
#define DataDir_Data		DDRA
#define Control_Port		PORTD
#define DataDir_Control	    DDRD
#define RS_Pin				4
#define Enable_Pin			6
#define Read_Write			5

volatile unsigned char receiveData;
unsigned char N;
volatile char* receiveDataString;
volatile char cnt;
unsigned char flag;
char* buff = "ab";

int main(void)
{
    DDRB |= (1 << PINB0);

	UART_Init(4800,0,8,N,1);

	DataDir_Control |= ((1 << Enable_Pin) | (1 << Read_Write) | (1 << RS_Pin));
	_delay_ms(15);

	Send_Command(0x01);                          //Clear screen 0x01 = 00000001
	_delay_ms(2);
	Send_Command(0x38);                          //Enable 8-bit mode
	_delay_us(50);
	Send_Command(0b00001110);                    //LCD configuration
	_delay_us(50);

	/*int UBRR_Value = 25;                                               //Baud Value for 2400 BAUD
	UBRRH = (unsigned char) (UBRR_Value >> 8);                         //Taking last 3 bits 9-11
	UBRRL = (unsigned char) UBRR_Value;
	
	UCSRB = (1 << RXEN) | (1 << TXEN);                                 //Enable Receiver and Transmitter
	UCSRC |= (1 << USBS);                                              //Stop bit
	UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);         */                     //8-bit data length
	UCSRB |= (1 << RXCIE);

	sei();

    while (1) 
    {
		//while(!(UCSRA & (1 << RXC)));

		
		/*receiveData = UART_Receive();
		if (receiveData == 'c') PORTB ^= (1 << PINB0);
		Send_Character(receiveData);*/

		/*while(!(UCSRA & (1 << RXC)));
		int i = 0;
		//receiveDataString = UART_Receive_String();
		while (UCSRA & (1 << RXC))
		{
			receiveDataString[i] = UDR;
			i++;
		}*/
		//receiveDataString[i] = '\0';

	/*	if(flag)
		{
			Send_String(receiveDataString);

			if (!strcmp(receiveDataString,buff))
			{
				PORTB ^= (1 << PINB0);
			}

			flag = 0;

		}
		receiveDataString = UART_Receive_String();
		Send_String(receiveDataString);

		if (!strcmp(receiveDataString,buff))
		{
			PORTB ^= (1 << PINB0);
		}*/
		
    }
}


ISR(USART_RXC_vect)
{
	/*receiveDataString[cnt] = UDR;	
	
	if(receiveDataString[cnt] == '\0')
	{
		flag = 1;
		cnt = 0;
	}
	else 
	{
		cnt++;
	}*/
	
	receiveData = UDR;
	if (receiveData == 'a') 
	{
			PORTB ^= (1 << PINB0);
			Send_Character(receiveData);
	}

}

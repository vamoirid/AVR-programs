#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <math.h>

unsigned int i;

unsigned char UART_Receive(void)
{
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}

void UART_Transmit(unsigned char data)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = data;
}

void UART_Send_String(char* str)
{
	unsigned int str_length = strlen(str);
	for (i = 0; i < str_length; i++)
	{
		UART_Transmit(str[i]);
	}
	UART_Transmit('\0');
}

char* UART_Receive_String(void)
{
	char str[20];
	int i = 0;

	while (UCSRA & (1 << RXC))
	{
		str[i] = UDR;
		i++;
	}
	//str[i] = '\0';

	return str;
}

void UART_Init(int baud, char doubleSpeed, char dataBits, char parityBit, char stopBits)
{
	uint16_t UBRRValue = lrint((F_CPU / (16L * baud)) - 1);

	if (doubleSpeed == 1) UCSRA = (1 << U2X);	//set the U2X bit for double speed

	UBRRH = (unsigned char) (UBRRValue >> 8);
	UBRRL = (unsigned char) UBRRValue;
	UCSRB = (1 << RXEN) | (1 << TXEN);			//Enable Receiver and Transmitter

	UCSRC |= (1 << USBS);						//Set one Stop bit

	if (dataBits == 5) UCSRC &= ~((1 << UCSZ0) | (1 << UCSZ1) | (1 << UCSZ2));
	if (dataBits == 6) UCSRC |= (1 << UCSZ0);
	if (dataBits == 7) UCSRC |= (1 << UCSZ1);
	if (dataBits == 8) UCSRC |= (1 << UCSZ0) | (1 << UCSZ1);
	if (dataBits == 9) UCSRC |= (1 << UCSZ0) | (1 << UCSZ1) | (1 << UCSZ2);

	if (parityBit == 'E') UCSRC |= (1 << UPM1);
	if (parityBit == 'O') UCSRC |= (1 << UPM0) | (1 << UPM1);
	if (parityBit == 'N') UCSRC &= ~((1 << UPM0) | (1 << UPM1));

	if (stopBits == 1) UCSRC &= ~(1 << USBS);
	if (stopBits == 2) UCSRC |= (1 << USBS);
}

#endif
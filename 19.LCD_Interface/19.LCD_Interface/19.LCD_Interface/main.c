/*
 * 19.LCD_Interface.c
 *
 * Created: 6/24/2017 2:59:01 PM
 * Author : Vasileios Amoiridis
 */ 

 #define F_CPU 1000000UL

 #include <avr/io.h>
 #include <util/delay.h>
 #include "lcd.h"

#define Data_Port			PORTA
#define DataDir_Data		DDRA
#define Control_Port		PORTD
#define DataDir_Control	    DDRD
#define RS_Pin				4
#define Enable_Pin			6
#define Read_Write			5

 int main(void)
 {
	 DataDir_Control |= ((1 << Enable_Pin) | (1 << Read_Write) | (1 << RS_Pin));
	 _delay_ms(15);

	 Send_Command(0x01);                          //Clear screen 0x01 = 00000001
	 _delay_ms(2);
	 Send_Command(0x38);                          //Enable 8-bit mode
	 _delay_us(50);
	 Send_Command(0b00001110);                    //LCD configuration
	 _delay_us(50);

	 

	 while (1)
	 {
		move_string(1,"Delhzwna");
		move_string(2,"Gamiesai");
	 }
 }

 

 

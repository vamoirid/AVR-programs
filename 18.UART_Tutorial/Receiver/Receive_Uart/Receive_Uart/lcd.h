#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU
#define F_CPU 1000000UL
#endif


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <inttypes.h>

#define Data_Port			PORTA
#define DataDir_Data		DDRA
#define Control_Port		PORTD
#define DataDir_Control	    DDRD
#define RS_Pin				4
#define Enable_Pin			6
#define Read_Write			5

void isBusy(void);
void Flash_LCD(void);
void Send_Command(char command);
void Send_Character(char character);
void Send_String(char* StringOfChars);
void Write_to(uint8_t x, uint8_t y);
void lcdInit(void);
void Send_String_to_Location(uint8_t x, uint8_t y, char* stringOfChars);
void Send_Integer(uint8_t x,uint8_t y,int integerToDisplay, char NumberofDigits);
void move_string(uint8_t y, char* stringOfChars);

#endif /*   LCD_H_   */
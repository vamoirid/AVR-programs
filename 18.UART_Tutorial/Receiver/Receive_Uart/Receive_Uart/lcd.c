#include "lcd.h"

void isBusy()
{
	DataDir_Data = 0;
	Control_Port |= (1 << Read_Write);                                  //Enable Read Mode
	Control_Port &= ~(1 << RS_Pin);                                     //Command Mode

	while(Data_Port >= 0x80)                                      //LCD is busy (datasheet)
	{
		Flash_LCD();
	}
	DataDir_Data = 0xFF;
}

void Flash_LCD()
{
	Control_Port |= (1 << Enable_Pin);
	asm volatile ("nop");
	asm volatile ("nop");
	Control_Port &= ~(1 << Enable_Pin);
}

void Send_Command(char command)
{
	isBusy();
	Data_Port = command;                                               //Send the command to the LCD PORT
	Control_Port &= ~((1 << Read_Write) | (1 << RS_Pin));              //Write Mode and setting it ready to accept commands
	Flash_LCD();                                                      //Flash the screen in order the LCD sees the info
	Data_Port = 0;                                                     //Erase th info from Data port
}

void Send_Character(char character)
{
	isBusy();
	Data_Port = character;                                             //Send the character to LCD PORT
	Control_Port &= ~(1 << Read_Write);                                //Write Mode
	Control_Port |= (1 << RS_Pin);                                     //Setting it ready to accept data
	Flash_LCD();                                                      //Flash the screen in order the LCD sees the info
	Data_Port = 0;                                                     //Erase th info from Data port
}

void Send_String(char* StringOfChars)
{
	while(*StringOfChars > 0)
	{
		Send_Character(*StringOfChars);
		*StringOfChars++;
	}
}

char firstColumnPosition[2] = {0,64};

void Write_to(uint8_t x, uint8_t y)
{
	Send_Command(0x80 + firstColumnPosition[y - 1] + (x - 1));
}

void lcdInit()
{
	DataDir_Control |= ((1 << Enable_Pin) | (1 << Read_Write) | (1 << RS_Pin));
	_delay_ms(15);

	Send_Command(0x01);                          //Clear screen 0x01 = 00000001
	_delay_ms(2);
	Send_Command(0x38);                          //Enable 8-bit mode
	_delay_us(50);
	Send_Command(0b00001110);                    //LCD configuration
	_delay_us(50);
}

void Send_Integer(uint8_t x,uint8_t y,int integerToDisplay, char NumberofDigits)
{
	char stringToDisplay[NumberofDigits];
	itoa(integerToDisplay,stringToDisplay,10);

	for (int i = 0; i < NumberofDigits; i++)
	{
		Send_String(" ");
	}

	Send_String_to_Location(x, y, stringToDisplay);
	
}

void Send_String_to_Location(uint8_t x, uint8_t y, char* stringOfChars)
{
	Write_to(x,y);
	Send_String(stringOfChars);
}

void move_string(uint8_t y, char* stringOfChars)
{
	for (int cnt = 1; cnt <= 16; cnt++)
	{
		Send_String_to_Location(cnt,y,stringOfChars);
		_delay_ms(200);
		Send_String_to_Location(cnt,y," ");
	}
}
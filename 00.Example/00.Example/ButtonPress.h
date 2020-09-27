#ifndef ButtonPress
#define ButtonPress

#include <stdint.h>

void ButtonInit(uint8_t NumberOfButtons);
uint8_t isButtonPressed(uint8_t PINRegister, uint8_t ButtonPin, uint16_t ConfidenceLevel, uint8_t ButtonNumber);

uint8_t SIZE;
uint8_t *pressed;
unsigned int *PressedConfidenceLevel;
unsigned int *ReleasedConfidenceLevel;


void ButtonInit(uint8_t NumberOfButtons)
{
	pressed = malloc(sizeof(uint8_t)*NumberOfButtons);
	PressedConfidenceLevel = malloc(sizeof(uint8_t)*NumberOfButtons);
	ReleasedConfidenceLevel = malloc(sizeof(uint8_t)*NumberOfButtons);
}

uint8_t isButtonPressed(uint8_t PINRegister, uint8_t ButtonPin, uint16_t ConfidenceLevel, uint8_t ButtonNumber)
{
	if(bit_is_clear(PINRegister, ButtonPin))
	{
		PressedConfidenceLevel[ButtonNumber]++;
		if(PressedConfidenceLevel[ButtonNumber] > ConfidenceLevel)
		{
			if (pressed[ButtonNumber] == 0)
			{
				pressed[ButtonNumber] = 1;
				PressedConfidenceLevel[ButtonNumber] = 0;
				return 1;
			}
		}
	}
	else
	{
		ReleasedConfidenceLevel[ButtonNumber]++;
		if(ReleasedConfidenceLevel[ButtonNumber] > ConfidenceLevel)
		{
			pressed[ButtonNumber] = 0;
		}
	}
	return 0;
}

#endif
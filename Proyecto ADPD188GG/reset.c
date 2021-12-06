#include "Records.h"
#include "I2C.h"
#include <stdio.h>

void reset(void)
{
	wiringPiSetup();
	wiringPiI2CSetup(0x64);
	I2CWrite(SW_RESET, 0x0001);
}
#include "Records.h"
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdint.h>

int rotar(int x, int n)
{
	unsigned int maso = 0x01;
	int32_t masl = 0x8000;
	unsigned int temp = 0;
	int32_t i = 0;

	while(i != n)
	{
		i++;
		
		temp = x & maso;
		x = x >> 1;
		
		if(temp == 1)
		{
			x = x | masl;
		}
	}
	
	return x;
}

void I2CWrite(unsigned int direction, unsigned int value)
{
	int32_t dir = 0;
	int32_t var = 0;
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x64);
	
	var = rotar(value, 8);
	
	wiringPiI2CWriteReg16(dir, direction,var);
}

int I2CRead(int direction)
{
	int dir = 0;
	int32_t var = 0;
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x64);
	var = wiringPiI2CReadReg16(dir, direction);
	//close(dir);
	return var;
}

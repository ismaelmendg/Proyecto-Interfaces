#include "Records.h"
#include <stdio.h>
#include "I2C.h"

void check(unsigned int var)
{

  int value = 0, var1 = 0;

    value = I2CRead(MODE);
    var1 = rotar(value, 8);

	if(var != var1)
	{
	    printf("Error mode %d\n", var);
	}
}

void ADPD_MODE(unsigned int mode)
{
	int var = mode;
	switch(mode)
	{
		case 0x0000:
			I2CWrite(MODE, mode);
			check(var);
		break;
		
		case 0x0001:
			I2CWrite(MODE, mode);
			check(var);			
		break;
		
		case 0x0002: 
			I2CWrite(MODE, mode);	
	        check(var);			
		break;
	}

}

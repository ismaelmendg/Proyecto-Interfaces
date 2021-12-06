#include "Records.h"
#include "I2C.h"
#include <stdio.h>

void FloatMode(void)
{
	//I2CWrite(BG_STATUS,       var);
	//I2CWrite(BG_MEAS_A,       var);
	//I2CWrite(BG_MEAS_B,       var);
	I2CWrite(SLOTA_FLOAT_LED, 0x0311);
	I2CWrite(SLOTB_FLOAT_LED, 0x0311);
	//I2CWrite(Math,       0x0080);
	I2CWrite(FLT_CONFIG_B,   0x1000);
	I2CWrite(FLT_LED_FIRE,   0x9000);
	I2CWrite(FLT_CONFIG_A,   0x1000);
	
}

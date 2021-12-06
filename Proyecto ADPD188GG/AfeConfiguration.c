#include "Records.h"
#include "I2C.h"
#include <stdio.h>

void AfeConfiguration(void)
{
	//I2CWrite(ALT_PWR_DN,       var);
	I2CWrite(AFE_PWR_CFG1,  0x31C6);
	//I2CWrite(AFE_PWR_CFG2,     var);
	//I2CWrite(TIA_INDEP_GAIN,   var);
	//I2CWrite(INT_SEQ_A,        var);
	I2CWrite(SLOTA_AFE_WINDOW, 0x1A38);
	//I2CWrite(SLOTA_TIA_CFG,    0x1C35);
	//I2CWrite(SLOTA_AFE_CFG,    0xADA5);
	//I2CWrite(INT_SEQ_B,        var);
	I2CWrite(SLOTB_AFE_WINDOW, 0x1A38);
	//I2CWrite(SLOTB_TIA_CFG,    0x1C35);	
	//I2CWrite(SLOTB_AFE_CFG,    0xADA5);
}

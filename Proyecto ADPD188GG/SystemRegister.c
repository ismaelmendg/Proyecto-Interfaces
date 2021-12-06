#include "Records.h"
#include "I2C.h"
#include <stdio.h>

void SystemRegister(void)
{
	//I2CWrite(STATUS,            var);
	I2CWrite(INT_MASK,          0x009F);
	I2CWrite(GPIO_DRIV,         0x0007);
	I2CWrite(FIFO_THRESH,       0x1600);
	//I2CWrite(DEVID,             var);
	//I2CWrite(I2CS_ID,           var);
	//I2CWrite(CLK_RATIO,         var);
	//I2CWrite(GPIO_CTRL,         var);
	//I2CWrite(SLAVE_ADDRESS_KEY, var);
	//I2CWrite(SW_RESET,          var);
	I2CWrite(SLOT_EN,           0x3131);
	//I2CWrite(EXT_SYNC_STARTUP,  var);
	//I2CWrite(SAMPLE_CLK,        var);
	//I2CWrite(CLK32M_ADJUST,     var);
	//I2CWrite(EXT_SYNC_SEL,      var);
	//I2CWrite(CLK32M_CAL_EN,     var);
	I2CWrite(DATA_ACCESS_CTL,   0x0001);
	
}

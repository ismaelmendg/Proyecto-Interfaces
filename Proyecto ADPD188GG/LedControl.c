#include "Records.h"
#include "I2C.h"
#include <stdio.h>
#include <stdint.h>

void LedControl(void)
{

	I2CWrite(PD_LED_SELECT, 0x0110);//PDET1 y PDET2 en CH 1 modo float
	//I2CRead(PD_LED_SELECT);
	I2CWrite(ILED3_COARSE,  0x0000);//CONTROLADOR 3 inhabilitado
	I2CWrite(ILED1_COARSE,  0x3031);
	I2CWrite(ILED2_COARSE,  0x0000);//CONTROLADOR 2 inhabilitado
	I2CWrite(ILED_FINE,     0x0001);//Ajuste para corriente de 45mA
	I2CWrite(SLOTA_LED_PULSE, 0x021E);//Ancho de pulso 2us
	I2CWrite(SLOTA_NUMPULSES, 0x0010);//Periodo foltante de 16us
	//I2CWrite(LED_DISABLE,     led_disable);
	I2CWrite(SLOTB_LED_PULSE, 0x021E);//Ancho de pulso 2us
	I2CWrite(SLOTB_NUMPULSES, 0x0010);//Periodo foltante de 16us
	
//	return 0;
}

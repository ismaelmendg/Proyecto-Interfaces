#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define dir 0x64
#define NPulses_SlotA 0x31 //0x0118 - 1 pulsos de LED
#define NPulses_SlotB 0x36 //0x0418 - 4 pulsos de LED
#define FMuestra 0x12 //Frecuencia de muestreo
#define SLOTA_LEDMODE 0x30//0x319
#define SLOTB_LEDMODE 0x35//0x319
#define SLOTA_AFEMODE 0x39//0x2209
#define SLOTB_AFEMODE 0x3B//0x2209
#define SLOTB_PD_SEL 0x14//0x100 - fotodiodo 1 y 2 en canal 1 en tiempo B
#define SLOTA_PD_SEL 0x14//0x10 - fotodiodo 1 y 2 en canal 1 en tiempo A
#define Estado 0x10
#define CLK32K_EN 0x4B 
#define GPIO_CTRL 0x0B
//NOTAS-Direcciones a revisar (FIFO): 0x5F-0x11-0x58-0x42-0x44-0x06-0x23-0x24-0x15--200mA-3u_ancho de pulso

void config(void)
{
	printf("I2C Init\n");
	wiringPiSetup();
	wiringPiI2CSetup(dir);
	wiringPiI2CWriteReg16(dir, Estado, 0x01);
	wiringPiI2CWriteReg16(dir, CLK32K_EN, 0x80);
	wiringPiI2CWriteReg16(dir, NPulses_SlotA, 0x0118);
	wiringPiI2CWriteReg16(dir, NPulses_SlotB, 0x0418);
	wiringPiI2CWriteReg16(dir, FMuestra,0x12);
	wiringPiI2CWriteReg16(dir, SLOTA_LEDMODE, 0x319);
	wiringPiI2CWriteReg16(dir, SLOTB_LEDMODE, 0x319);
	wiringPiI2CWriteReg16(dir, SLOTA_AFEMODE, 0x2209);
	wiringPiI2CWriteReg16(dir, SLOTB_AFEMODE, 0x2209);
	wiringPiI2CWriteReg16(dir, SLOTB_PD_SEL, 0x100);
	wiringPiI2CWriteReg16(dir, SLOTA_PD_SEL, 0x10);
	wiringPiI2CWriteReg16(dir, Estado, 0x02);
	printf("Config finish\n");
}

int main (void)
{

	config();
    	return 0;
}


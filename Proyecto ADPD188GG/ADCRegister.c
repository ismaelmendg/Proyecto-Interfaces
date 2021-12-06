#include "Records.h"
#include "I2C.h"
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
void ADCRegister(void)
{
	wiringPiSetup();
	
	wiringPiI2CSetup(0x64);
	int fifo = 0;/*slota_pd2,slota_pd3,slota_pd4,
					slotb_pd1,slotb_pd2,slotb_pd3,slotb_pd4,
					a_pd1_l ,a_pd2_l ,a_pd3_l ,a_pd4_l ,
					a_pd1_h,a_pd2_h,a_pd3_h,a_pd4_h,
					b_pd1_l ,b_pd2_l ,b_pd3_l ,b_pd4_l ,
					b_pd1_h,b_pd2_h,b_pd3_h,b_pd4_h;*/
	//while(1){	
	I2CWrite(FSAMPLE,    0x0320);//Frecuencia de muestro 10Hz
	//slota_pd1 = wiringPiI2CReadReg16(dir, B_PD4_HIGH);	
	//fifo =  I2CRead(FIFO_ACCESS);
	//slota_pd1 =  I2CRead(SLOTA_PD1_16BIT);
	//slota_pd2 = I2CRead(SLOTA_PD2_16BIT);
	//slota_pd3 = I2CRead(SLOTA_PD3_16BIT);
	//slota_pd4 = I2CRead(SLOTA_PD4_16BIT);
	/*slotb_pd1 = I2CRead(SLOTB_PD1_16BIT);
	slotb_pd2 = I2CRead(SLOTB_PD2_16BIT);
	slotb_pd3 = I2CRead(SLOTB_PD3_16BIT);
	slotb_pd4 = I2CRead(SLOTB_PD4_16BIT);
	a_pd1_l = I2CRead(A_PD1_LOW);
	a_pd2_l = I2CRead(A_PD2_LOW);
	a_pd3_l = I2CRead(A_PD3_LOW);
	a_pd4_l = I2CRead(A_PD4_LOW);
	a_pd1_h = I2CRead(A_PD1_HIGH);
	a_pd2_h = I2CRead(A_PD2_HIGH);
	a_pd3_h = I2CRead(A_PD3_HIGH);	
	a_pd4_h = I2CRead(A_PD4_HIGH);
	b_pd1_l = I2CRead(B_PD1_LOW);
	b_pd2_l = I2CRead(B_PD2_LOW);
	b_pd3_l = I2CRead(B_PD3_LOW);
	b_pd4_l = I2CRead(B_PD4_LOW);
	b_pd1_h = I2CRead(B_PD1_HIGH);
	b_pd2_h = I2CRead(B_PD2_HIGH);
	b_pd3_h = I2CRead(B_PD3_HIGH);
	b_pd4_h = I2CRead(B_PD4_HIGH);*/
	printf("%d\n",fifo);
	//printf("%d\n",slota_pd1);
	//printf("%d\n",slota_pd2);
	//printf("%d\n",slota_pd3);
	//printf("%d\n",slota_pd4);
	/*printf("%d\n",slotb_pd1);
	printf("%d\n",slotb_pd2);
	printf("%d\n",slotb_pd3);	
	printf("%d\n",slotb_pd4);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);	
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);
	printf("%d\n",);*/	
	
}
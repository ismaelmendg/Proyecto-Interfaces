#include <stdio.h>
#include "I2C.h"
#include "carlet.h"
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#define rango 127
#define Filtro 250

unsigned char LCD_screen_buffer[1024];
char LCD_line1[18];
char LCD_line2[18];
char LCD_line3[18];
char LCD_line4[18];
int arreglo[Filtro];
int arreglo_y[rango];
int arreglo_x[rango];
static int cont;

void LCD_send_Command(unsigned char* commands,unsigned int command_length )
{
	int lcd;
	wiringPiSetup();
	lcd = wiringPiI2CSetup(0x3C);

	for (int x=0; x<command_length; x++)
	{
       wiringPiI2CWriteReg8(lcd, 0x00, commands[x]);
	}

	return;
}
void LCD_send_Data(unsigned char* data_, unsigned int data_lenght)
{

	int lcd;
	wiringPiSetup();
	lcd = wiringPiI2CSetup(0x3C);
	for (int x=0; x<data_lenght; x++)
	{
		wiringPiI2CWriteReg8(lcd, 0x40, data_[x]);
	}
	return;
}

void LCD_init()
{

	
	unsigned char init_sequence[27]={0xAE,0xD5,0x80,0xA8,63,0xD3,0x00,0x40,0x8D,
			0xD5,0x14,0x20,0x00,0xA1,0xC8,0xDA,0x12,0x81,0xCF,0xD9,0xF1,  0xDB,0x40,
			0xA4,0xA6,0x2E,0xAF};
	LCD_send_Command(init_sequence,27);

}

void LCD_print()
{

	unsigned char start_screen[6]={0x22,0x00,0xFF,0x21,0x00,127};
	LCD_send_Command(start_screen,6);

	LCD_send_Data(LCD_screen_buffer,1024);

}

void LCD_print_text()
{
	char buffer_letra[8];
	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line1[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[129+ (7*y) +z] = buffer_letra[0+z];
		}
	}

	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line2[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[385+ (7*y) +z] = buffer_letra[0+z];
		}
	}
	//////////
	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line3[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[641+ (7*y) +z] = buffer_letra[0+z];
		}
	}
	////////////
	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line4[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[897+ (7*y) +z] = buffer_letra[0+z];
		}
	}
	LCD_print();
}

void LCD_clear()
{
	memset(&LCD_screen_buffer, 0, 1024);
	LCD_print();
}

void punto(char corx, char cory, char ClearClean){

	int filasCom=0, caracter = 0, pixel =0;
	unsigned char bits = 0x1;
	cory = 65 - cory;
	if((corx <= 128) && (cory <= 64)){
		filasCom = cory/8;
		caracter = (filasCom * 128) + corx;
		pixel = cory - (filasCom * 8);
		bits = bits << (pixel -1);
		if(ClearClean == 1){
		LCD_screen_buffer[caracter] = LCD_screen_buffer[caracter] | bits;
		}else{
			bits = ~bits;
			LCD_screen_buffer[caracter] = LCD_screen_buffer[caracter] & bits;
		}

		LCD_print();

	}
}

void grafica(int y, int contx){

	int cleany, cleanx,i;

	cont++;
	punto(contx, y, 1);
	for(i = rango-1; i > 0; i--){
		arreglo_y[i] = arreglo_y[i-1];
		arreglo_x[i] = arreglo_x[i-1];
       	}

       	arreglo_y[0] = y;
       	arreglo_x[0] = contx;
       	cleany = arreglo_y[126];
       	cleanx = arreglo_x[126];
		punto(cleanx, cleany, 0);

	if(cont >= 135){
		cont = 0;
}
}
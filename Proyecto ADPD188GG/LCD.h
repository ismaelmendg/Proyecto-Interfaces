#ifndef LCD_H_
#define LCD_H_

//void delay(void);
void LCD_send_Command(unsigned char* commands,unsigned int command_length );
void LCD_send_Data(unsigned char* data_, unsigned int data_lenght);
void LCD_init();
void LCD_print();
void LCD_print_text();
void LCD_clear();
void punto(char corx, char cory, char ClearClean);
void grafica(int y, int contx);
#endif

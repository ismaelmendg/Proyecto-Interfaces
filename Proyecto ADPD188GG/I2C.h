#ifndef I2C_H_
#define I2C_H_
#include <wiringPi.h>
#include <wiringPiI2C.h>
int rotar(int x, char n);
void I2CWrite(unsigned int direction, unsigned int value);
int I2CRead(int direction);

#endif

CC = gcc
CFLAGS = -Wall  -lwiringPi -lpthread
OUTPUT = ADPD188GG.out
RECORDS = Records.h
ADC = ADCRegister.c
AFE = AfeConfiguration.c
FLOAT = FloatMode.c
I2C = I2C.c
LED = LedControl.c
MODE = MODE.c
SYSTEM = SystemRegister.c
RESET = reset.c
LCD = LCD.c
CARLET = carlet.c
DEBUG = -g
SOURCES = ADPD188GG.c

all:
	$(CC) $(SOURCES) $(CFLAGS) $(RECORDS) $(ADC) $(AFE) $(FLOAT) $(I2C) $(LED) $(MODE) $(SYSTEM) $(RESET) $(LCD) $(CARLET) -o $(OUTPUT)
debug:
	$(CC) $(SOURCES) $(CFLAGS) $(DEBUG) $(RECORDS) $(ADC) $(AFE) $(FLOAT) $(I2C) $(LED) $(MODE) $(SYSTEM) $(RESET) $(LCD) $(CARLET) -o $(OUTPUT)
clean:
	rm -f $(OUTPUT)
fresh:
	make clean
	make all

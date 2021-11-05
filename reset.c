#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define STATUS           0x00
#define INT_MASK         0x01
#define GPIO_DRIV        0x02
#define BG_STATUS        0x04
#define FIFO_THRESH      0x06
#define DEVID            0x08
#define I2CS_ID          0x09
#define CLK_RATIO        0x0A
#define GPIO_CTRL         0x0B
#define SLAVE_ADDRESS_KEY 0x0D
#define SW_RESET         0x0F
#define MODE             0x10
#define SLOT_EN          0x11
#define FSAMPLE          0x12
#define PD_LED_SELECT    0x14
#define NUM_AVG          0x15
#define BG_MEAS_A       0x16
#define INT_SEQ_A        0x17
#define SLOTA_CH1_OFFSET 0x18
#define SLOTA_CH2_OFFSET 0x19
#define SLOTA_CH3_OFFSET 0x1A
#define SLOTA_CH4_OFFSET 0x1B
#define BG_MEAS_B        0x1C
#define INT_SEQ_B        0x1D
#define SLOTB_CH1_OFFSET 0x1E
#define SLOTB_CH2_OFFSET 0x1F
#define SLOTB_CH3_OFFSET 0x20
#define SLOTB_CH4_OFFSET 0x21 
#define ILED3_COARSE     0x22
#define ILED1_COARSE     0x23
#define ILED2_COARSE     0x24
#define ILED_FINE        0x25
#define SLOTA_LED_PULSE  0x30
#define SLOTA_NUMPULSES 0x31
#define LED_DISABLE      0x34
#define SLOTB_LED_PULSE  0x35
#define SLOTB_NUMPULSES  0x36
#define ALT_PWR_DN       0x37
#define EXT_SYNC_STARTUP 0x38
#define SLOTA_AFE_WINDOW 0x39
#define SLOTB_AFE_WINDOW 0x3B
#define AFE_PWR_CFG1     0x3C 
#define SLOTA_FLOAT_LED  0x3E
#define SLOTB_FLOAT_LED  0x3F
#define SLOTA_TIA_CFG    0x42
#define SLOTA_AFE_CFG    0x43
#define SLOTB_TIA_CFG    0x44
#define SLOTB_AFE_CFG    0x45
#define SAMPLE_CLK      0x4B
#define CLK32M_ADJUST   0x4D
#define EXT_SYNC_SEL    0x4F
#define CLK32M_CAL_EN   0x50
#define AFE_PWR_CFG2    0x54
#define TIA_INDEP_GAIN  0x55
#define Math             0x58
#define FLT_CONFIG_B    0x59
#define FLT_LED_FIRE    0x5A
#define FLT_CONFIG_A    0x5E
#define DATA_ACCESS_CTL 0x5F
#define FIFO_ACCESS     0x60
#define SLOTA_PD1_16BIT 0x64
#define SLOTA_PD2_16BIT 0x65
#define SLOTA_PD3_16BIT 0x66
#define SLOTA_PD4_16BIT 0x67
#define SLOTB_PD1_16BIT 0x68
#define SLOTB_PD2_16BIT 0x69
#define SLOTB_PD3_16BIT 0x6A
#define SLOTB_PD4_16BIT 0x6B
#define A_PD1_LOW        0x70
#define A_PD2_LOW        0x71
#define A_PD3_LOW        0x72
#define A_PD4_LOW        0x73
#define A_PD1_HIGH       0x74
#define A_PD2_HIGH       0x75
#define A_PD3_HIGH       0x76
#define A_PD4_HIGH       0x77
#define B_PD1_LOW        0x78
#define B_PD2_LOW        0x79
#define B_PD3_LOW        0x7A
#define B_PD4_LOW        0x7B
#define B_PD1_HIGH       0x7C
#define B_PD2_HIGH       0x7D
#define B_PD3_HIGH       0x7E
#define B_PD4_HIGH       0x7F

void config()
{
	int dir;
	printf("I2C Init\n");
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x64);

	wiringPiI2CWriteReg16(dir,SAMPLE_CLK, 0x8000);//Enciende reloj para maquina de estados
///////////////////Control del LED
	wiringPiI2CWriteReg16(dir, MODE, 0x0100);
	wiringPiI2CWriteReg16(dir, SLOTA_LED_PULSE,0x1903);
	wiringPiI2CWriteReg16(dir, SLOTB_LED_PULSE,0x1903);
	wiringPiI2CWriteReg16(dir, SLOTA_AFE_WINDOW,0x0922);
	wiringPiI2CWriteReg16(dir, SLOTB_AFE_WINDOW,0x0922);
	wiringPiI2CWriteReg16(dir, PD_LED_SELECT, 0x0555);//LED 1(canal3-tiempoA) y 2(canal4-tiempoB) 
	wiringPiI2CWriteReg16(dir, FSAMPLE,0x0028);
	wiringPiI2CWriteReg16(dir, ILED1_COARSE,0x3630);
	wiringPiI2CWriteReg16(dir, ILED3_COARSE,0x3010);
	wiringPiI2CWriteReg16(dir, ILED2_COARSE,0x3010);
	wiringPiI2CWriteReg16(dir, ILED_FINE,0x0C36);
	wiringPiI2CWriteReg16(dir, SLOTA_LED_PULSE,0x2002);//////////
	wiringPiI2CWriteReg16(dir, SLOTA_NUMPULSES,0x0F02);////////
	wiringPiI2CWriteReg16(dir, LED_DISABLE,0x0000);
	wiringPiI2CWriteReg16(dir, SLOTB_LED_PULSE,0x2002);///////////
	wiringPiI2CWriteReg16(dir, SLOTB_NUMPULSES,0x0F02);///////////
//////////////////CONFIGURACIÓN AFE
	wiringPiI2CWriteReg16(dir, ALT_PWR_DN,0x0000);
	wiringPiI2CWriteReg16(dir, AFE_PWR_CFG1,0x0670);///////////////////
	wiringPiI2CWriteReg16(dir, AFE_PWR_CFG1,0xA00A);
	wiringPiI2CWriteReg16(dir, SLOTA_TIA_CFG,0x351C);
	wiringPiI2CWriteReg16(dir, SLOTA_AFE_CFG,0xA5AD);
	wiringPiI2CWriteReg16(dir, SLOTB_AFE_CFG,0x351C);
	wiringPiI2CWriteReg16(dir, SLOTB_AFE_CFG,0xA5AD);
	wiringPiI2CWriteReg16(dir, Math,0x0000);
	wiringPiI2CWriteReg16(dir, FLT_CONFIG_B, 0x0808);
	wiringPiI2CWriteReg16(dir, FLT_LED_FIRE,0x1000);
///////////REGISTROS DEL SISTEMA
	wiringPiI2CWriteReg16(dir, STATUS,0xFF80);
	wiringPiI2CWriteReg16(dir, GPIO_DRIV,0x00);
	wiringPiI2CWriteReg16(dir, SAMPLE_CLK,0xA101);
	wiringPiI2CWriteReg16(dir, CLK32M_ADJUST,0x0200);
	wiringPiI2CWriteReg16(dir, DATA_ACCESS_CTL,0x0001);
//////////Registros ADC
	wiringPiI2CWriteReg16(dir, SLOTA_CH1_OFFSET,0xFF3F);
	wiringPiI2CWriteReg16(dir, SLOTA_CH2_OFFSET,0xFF3F);
	wiringPiI2CWriteReg16(dir, SLOTA_CH3_OFFSET,0x001F);
	wiringPiI2CWriteReg16(dir, SLOTA_CH4_OFFSET,0x001F);
	wiringPiI2CWriteReg16(dir, SLOTB_CH1_OFFSET,0xFF3F);
	wiringPiI2CWriteReg16(dir, SLOTB_CH2_OFFSET,0xFF3F);
	wiringPiI2CWriteReg16(dir, SLOTB_CH3_OFFSET,0x001F);
	wiringPiI2CWriteReg16(dir, SLOTB_CH4_OFFSET,0x001F);
	wiringPiI2CWriteReg16(dir, MODE,0x0200);
}


void reset()
{
	int dir;
	printf("I2C Init\n");
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x64);

	wiringPiI2CWriteReg16(dir, MODE, 0x0001);
	wiringPiI2CWriteReg16(dir, INT_MASK, 0xFF00);
	wiringPiI2CWriteReg16(dir, GPIO_DRIV, 0x0000);
	wiringPiI2CWriteReg16(dir, BG_STATUS, 0x0000);
	wiringPiI2CWriteReg16(dir, FIFO_THRESH, 0x0000);
	wiringPiI2CWriteReg16(dir, DEVID, 0x160A);
	wiringPiI2CWriteReg16(dir, I2CS_ID, 0xC800);
	wiringPiI2CWriteReg16(dir, CLK_RATIO, 0x0000);
	wiringPiI2CWriteReg16(dir, GPIO_CTRL, 0x0000);
	wiringPiI2CWriteReg16(dir, SLAVE_ADDRESS_KEY, 0x0000);
	wiringPiI2CWriteReg16(dir, SW_RESET, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOT_EN, 0x0010);
	wiringPiI2CWriteReg16(dir, FSAMPLE, 0x2800);
	wiringPiI2CWriteReg16(dir, PD_LED_SELECT, 0x4105);
	wiringPiI2CWriteReg16(dir, NUM_AVG, 0x0006);
	wiringPiI2CWriteReg16(dir, BG_MEAS_A, 0x0000);
	wiringPiI2CWriteReg16(dir, INT_SEQ_B, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTA_CH1_OFFSET, 0x0020);
	wiringPiI2CWriteReg16(dir, SLOTA_CH2_OFFSET, 0x0020);
	wiringPiI2CWriteReg16(dir, SLOTA_CH3_OFFSET, 0x0020);
	wiringPiI2CWriteReg16(dir, SLOTA_CH4_OFFSET, 0x0020);
	wiringPiI2CWriteReg16(dir, BG_MEAS_B, 0x0000);
	wiringPiI2CWriteReg16(dir, INT_SEQ_B, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTB_CH1_OFFSET, 0x0020);
	wiringPiI2CWriteReg16(dir, SLOTB_CH2_OFFSET, 0x0020);
	wiringPiI2CWriteReg16(dir, SLOTB_CH3_OFFSET, 0x0020);
	wiringPiI2CWriteReg16(dir, SLOTB_CH4_OFFSET, 0x0020);
	wiringPiI2CWriteReg16(dir, ILED3_COARSE, 0x0030);
	wiringPiI2CWriteReg16(dir, ILED1_COARSE, 0x0030);
	wiringPiI2CWriteReg16(dir, ILED2_COARSE, 0x0030);
	wiringPiI2CWriteReg16(dir, ILED_FINE, 0x0C63);
	wiringPiI2CWriteReg16(dir, SLOTA_LED_PULSE, 0x2003);
	wiringPiI2CWriteReg16(dir, SLOTA_NUMPULSES, 0x1808);
	wiringPiI2CWriteReg16(dir, LED_DISABLE, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTB_LED_PULSE, 0x2003);
	wiringPiI2CWriteReg16(dir, SLOTB_NUMPULSES, 0x1808);
	wiringPiI2CWriteReg16(dir, ALT_PWR_DN , 0x0000);
	wiringPiI2CWriteReg16(dir, EXT_SYNC_STARTUP, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTA_AFE_WINDOW, 0xFC22);
	wiringPiI2CWriteReg16(dir, SLOTB_AFE_WINDOW, 0xFC22);
	wiringPiI2CWriteReg16(dir, AFE_PWR_CFG1, 0x0630);
	wiringPiI2CWriteReg16(dir, SLOTA_FLOAT_LED, 0x2003);
	wiringPiI2CWriteReg16(dir, SLOTB_FLOAT_LED, 0x2003);
	wiringPiI2CWriteReg16(dir, SLOTA_TIA_CFG, 0x381C);
	wiringPiI2CWriteReg16(dir, SLOTA_AFE_CFG, 0xA5AD);
	wiringPiI2CWriteReg16(dir, SLOTB_TIA_CFG, 0x381C);
	wiringPiI2CWriteReg16(dir, SLOTB_AFE_CFG, 0xA5AD);
	wiringPiI2CWriteReg16(dir, SAMPLE_CLK, 0x91226);
	wiringPiI2CWriteReg16(dir, CLK32M_ADJUST, 0x9800);
	wiringPiI2CWriteReg16(dir, EXT_SYNC_SEL, 0x9020);
	wiringPiI2CWriteReg16(dir, CLK32M_CAL_EN, 0x0000);
	wiringPiI2CWriteReg16(dir, AFE_PWR_CFG2,0x2000);
	wiringPiI2CWriteReg16(dir, TIA_INDEP_GAIN, 0x0000);
	wiringPiI2CWriteReg16(dir, Math, 0x0000);
	wiringPiI2CWriteReg16(dir, FLT_CONFIG_B, 0x0808);
	wiringPiI2CWriteReg16(dir, FLT_LED_FIRE, 0x1000);
	wiringPiI2CWriteReg16(dir, FLT_CONFIG_A, 0x0808);
	wiringPiI2CWriteReg16(dir, DATA_ACCESS_CTL, 0x0000);
	wiringPiI2CWriteReg16(dir, FIFO_ACCESS, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTA_PD1_16BIT, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTA_PD2_16BIT, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTA_PD3_16BIT,0x0000 );
	wiringPiI2CWriteReg16(dir, SLOTA_PD4_16BIT, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTB_PD1_16BIT, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTB_PD2_16BIT, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTB_PD3_16BIT, 0x0000);
	wiringPiI2CWriteReg16(dir, SLOTB_PD4_16BIT, 0x0000);
	wiringPiI2CWriteReg16(dir, A_PD1_LOW,0x0000 );
	wiringPiI2CWriteReg16(dir, A_PD2_LOW, 0x0000);
	wiringPiI2CWriteReg16(dir, A_PD3_LOW, 0x0000);
	wiringPiI2CWriteReg16(dir, A_PD4_LOW, 0x0000);
	wiringPiI2CWriteReg16(dir, A_PD1_HIGH , 0x0000);
	wiringPiI2CWriteReg16(dir, A_PD2_HIGH , 0x0000);
	wiringPiI2CWriteReg16(dir, A_PD3_HIGH , 0x0000);
	wiringPiI2CWriteReg16(dir, A_PD4_HIGH , 0x0000);
	wiringPiI2CWriteReg16(dir, B_PD1_LOW, 0x0000);
	wiringPiI2CWriteReg16(dir, B_PD2_LOW,0x0000 );
	wiringPiI2CWriteReg16(dir, B_PD3_LOW, 0x0000);
	wiringPiI2CWriteReg16(dir, B_PD4_LOW, 0x0000);
	wiringPiI2CWriteReg16(dir, B_PD1_HIGH, 0x0000);
	wiringPiI2CWriteReg16(dir, B_PD2_HIGH, 0x0000);
	wiringPiI2CWriteReg16(dir, B_PD3_HIGH,0x0000 );
	wiringPiI2CWriteReg16(dir, B_PD4_HIGH, 0x0000);
	wiringPiI2CWriteReg16(dir, MODE, 0x0000);
}

int main(void)
{
        int dir, fifo;
        printf("I2C Init\n");
        wiringPiSetup();
        dir = wiringPiI2CSetup(0x64);

	config();
	lectura();

	return 0;
}

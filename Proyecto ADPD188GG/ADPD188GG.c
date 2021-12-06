#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "Records.h"
#include "SystemRegister.h"
#include "FloatMode.h"
#include "LedControl.h"
#include "AfeConfiguration.h"
#include "ADCRegister.h"
#include "MODE.h"
#include "I2C.h"
#include "reset.h"
#include "LCD.h"

char LCD_line1[18];
char LCD_line2[18];
char LCD_line3[18];
char LCD_line4[18];
	
#define N 8
#define PORT 8080
#define STANDBY 0x0000
#define PROGRAM 0x0001
#define NORMAL_OPERATION 0x0002
int newScoketConnectionFD = 0;//storage_socketID[5] = {0};
int32_t x = 0, var = 0;
int8_t important = 0;
pthread_mutex_t socketMutex;


void *SendMessages (void *ptr)
{

	int dir;
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x64);	
	
	int32_t  i = 0;
	char CS = 0;
	int32_t buffer[1024] = {0};	
	char *Buffer_server = "SELECT";
	int8_t Noperation = 0, noperation = 0;
	int8_t STAND      = 0, stand      = 0;
	int8_t m1         = 0, m2         = 0;
	int8_t valor_AD   = 0;
	int8_t CONFIG     = 0;	
	int32_t alt_pwr_dn      = 0,afe_pwr_cfg1     = 0,afe_pwr_cfg2  = 0,tia_indep_gain  = 0, adc = 0;
	int32_t int_seq_a       = 0,alota_afe_window = 0,slota_tai_cfg = 0,slota_afe_cfg   = 0;
	int32_t int_seq_b       = 0,slotb_afe_window = 0,slotb_tai_cfg = 0,slotb_afe_cfg   = 0;
	int32_t bg_status       = 0,bg_meas_a        = 0,bg_meas_b     = 0,slota_float_led = 0;
	int32_t slotb_float_led = 0,math             = 0,flt_config_b  = 0,flt_led_fire    = 0,flt_config_a = 0;	
	int32_t pd_lec_select   = 0,iled3_coarse     = 0,iled1_coarse  = 0,iled2_coarse    = 0,iled_fine    = 0;
	int32_t slota_led_pulse = 0,slota_numpulses  = 0,led_disable   = 0,slotb_led_pulse = 0,slotb_numpulses = 0;
	int32_t status          = 0,gpio_driv        = 0,fifo_thresh   = 0,devid           = 0,i2cs_id      = 0;
	int32_t clk_ratio       = 0,gpio_ctrl        = 0,slave_addr_key= 0,ext_sync_start  = 0;
	int32_t sample_clk      = 0,clk32m_ad        = 0,ext_sync_s    = 0,clk32m_cal      = 0,data_acces   = 0;
	
    while (1)
    {		

	pthread_mutex_lock(&socketMutex);		
	
	if(newScoketConnectionFD != var){

	if(important == 1)
	{
	sprintf(LCD_line1,"{}{}{}{}{}{}{}{}{");	
	sprintf(LCD_line2,"    adpd188gg    ");
	sprintf(LCD_line3,"   not detected  ");
	sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{");
	LCD_print_text();	
	m1 = 0;
	m2 = 0;
	valor_AD = 0;
	CONFIG = 0;
	STAND = 0;
	Noperation = 0;
	}else
	{
	if(m1 == 0)
	{	
	sprintf(LCD_line1,"{}{}{}{}{}{}{}{}{");	
	sprintf(LCD_line2,"     select      ");
	sprintf(LCD_line3,"      mode       ");
	sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{");
	LCD_print_text();
	sleep(2);
	sprintf(LCD_line1,"1-default values ");	
	sprintf(LCD_line2,"2-standby      ");
	sprintf(LCD_line3,"3-read logs    ");
	sprintf(LCD_line4,"4-normal operation");		
	LCD_print_text();
	m1 = 1;
	}else
	{
		//printf("\n");
	}	

	read( newScoketConnectionFD, buffer, 1024);

	while(i != 4)
	{
		CS = CS + buffer[i];
		i++;
	}
	
	CS = CS | buffer[4];//OR de CS obtenido con el calculado por datos de entrada
	
	if(CS == 0xFF)
	{
		printf("CS correcto\n");
	}	
				if(valor_AD == 0)
				{
					valor_AD = buffer[3];
					buffer[3] = 0;
				}else
				{
					printf("\n");
				}
				
		switch(valor_AD)
		{
			case 0x0001:
				ADPD_MODE(PROGRAM);
				SystemRegister();
				ADCRegister();
				AfeConfiguration();
				FloatMode();
				LedControl();
				ADPD_MODE(STANDBY);
				sprintf(LCD_line1,"{}{}{}{}{}{}{}{}{");				
				sprintf(LCD_line2,"    succesful    ");
				sprintf(LCD_line3,"   programming   ");
				sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{");				
				LCD_print_text();
				sleep(3);	
				valor_AD = 0;
				m1 = 0;
			break;
			
			case 0x0002: 

				STAND = stand == 0? stand  = buffer[3]: stand;
				
				if(STAND == 4)
				{
					valor_AD = 0;
					m1 = 0;
				}else
				{	
				LCD_clear();
				ADPD_MODE(STANDBY);
				sprintf(LCD_line1,"{}{}{}{}{}{}{}{}{");
				sprintf(LCD_line2,"  modo standby  ");	
				sprintf(LCD_line3,"4 - exit        ");				
				sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{");
				LCD_print_text();
				}
				
			break;

			case 0x0003: 
				
				if(m2 == 0)
				{
				LCD_clear();
				sprintf(LCD_line1,"seleccione...    ");
				sprintf(LCD_line2,"1 - adc          ");
				sprintf(LCD_line3,"2 - afe          ");
				sprintf(LCD_line4,"3 - float mode   ");		
				LCD_print_text();
				sleep(2);
				LCD_clear();
				sprintf(LCD_line1,"continue...      ");				
				sprintf(LCD_line2,"4 - led          ");
				sprintf(LCD_line3,"5 - system       ");
				sprintf(LCD_line4,"6 - reset        ");				
				LCD_print_text();
				sleep(2);
				LCD_clear();
				m2 = 1;
				}else
				{
					printf("\n");
				}	
				
				if(CONFIG == 0)
				{
					CONFIG = buffer[3];
					buffer[3] = 0;
				}else
				{
					printf("e\n");
				}

				switch(CONFIG)
				{
					case 0x0001: 
								adc = wiringPiI2CReadReg16(dir, FSAMPLE);				
								sprintf(LCD_line1,"{}{}{}{}{}{}{}{}{");				
								sprintf(LCD_line2,"     fsample     ");
								sprintf(LCD_line3,"      %x         ",adc);
								sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{");				
								LCD_print_text();
								sleep(3);						
								valor_AD = 0;
								CONFIG = 0;
								m1 = 0;	
								m2 = 0;							
						
					break;
					
					case 0x0002:
							
								alt_pwr_dn       = wiringPiI2CReadReg16(dir, ALT_PWR_DN);
									alt_pwr_dn       = rotar(alt_pwr_dn, N);
								afe_pwr_cfg1     = wiringPiI2CReadReg16(dir, AFE_PWR_CFG1);
									afe_pwr_cfg1     = rotar(afe_pwr_cfg1, N);
								afe_pwr_cfg2     = wiringPiI2CReadReg16(dir, AFE_PWR_CFG2);
									afe_pwr_cfg2     = rotar(afe_pwr_cfg2, N);
								tia_indep_gain   = wiringPiI2CReadReg16(dir, TIA_INDEP_GAIN);
									tia_indep_gain   = rotar(tia_indep_gain, N);
								int_seq_a        = wiringPiI2CReadReg16(dir, INT_SEQ_A);
									int_seq_a        = rotar(int_seq_a, N);
								alota_afe_window = wiringPiI2CReadReg16(dir, SLOTA_AFE_WINDOW);
									alota_afe_window = rotar(alota_afe_window, N);
								slota_tai_cfg    = wiringPiI2CReadReg16(dir, SLOTA_TIA_CFG);
									slota_tai_cfg    = rotar(slota_tai_cfg, N);
								slota_afe_cfg    = wiringPiI2CReadReg16(dir, SLOTA_AFE_CFG);
									slota_afe_cfg    = rotar(slota_afe_cfg, N);
								int_seq_b        = wiringPiI2CReadReg16(dir, INT_SEQ_B);
									int_seq_b        = rotar(int_seq_b, N);
								slotb_afe_window = wiringPiI2CReadReg16(dir, SLOTB_AFE_WINDOW);
									slotb_afe_window = rotar(slotb_afe_window, N);
								slotb_tai_cfg    = wiringPiI2CReadReg16(dir, SLOTB_TIA_CFG);
									slotb_tai_cfg    = rotar(slotb_tai_cfg, N);
								slotb_afe_cfg    = wiringPiI2CReadReg16(dir, SLOTB_AFE_CFG);
									slotb_afe_cfg    = rotar(slotb_afe_cfg, N);

								LCD_clear();
								sprintf(LCD_line1,"alt_pwr_dn %x    ",alt_pwr_dn);
								sprintf(LCD_line2,"afe_pwr_cfg1 %x  ",afe_pwr_cfg1);
								sprintf(LCD_line3,"afe_pwr_cfg2 %x  ",afe_pwr_cfg2);
								sprintf(LCD_line4,"tia_indep %x     ",tia_indep_gain);		
								LCD_print_text();
								sleep(3);
								LCD_clear();
								sprintf(LCD_line1,"int_seq_a %x     ",int_seq_a);				
								sprintf(LCD_line2,"alota_afe %x     ",alota_afe_window);
								sprintf(LCD_line3,"slota_tai %x     ",slota_tai_cfg);
								sprintf(LCD_line4,"slota_afe %x     ",slota_afe_cfg);				
								LCD_print_text();
								sleep(3);
								LCD_clear();	
								sprintf(LCD_line1,"int_seq_b %x     ",int_seq_b);				
								sprintf(LCD_line2,"slotb_afe %x     ",slotb_afe_window);
								sprintf(LCD_line3,"slotb_tai %x     ",slotb_tai_cfg);
								sprintf(LCD_line4,"slotb_afe %x     ",slotb_afe_cfg);				
								LCD_print_text();
								sleep(3);
								LCD_clear();
								valor_AD = 0;
								CONFIG = 0;
								m1 = 0;	
								m2 = 0;
									
					break;
					
					case 0x0003:
					
								bg_status         = wiringPiI2CReadReg16(dir, BG_STATUS);
									bg_status       = rotar(bg_status, N);
								bg_meas_a         = wiringPiI2CReadReg16(dir, BG_MEAS_A);
									bg_meas_a       = rotar(bg_meas_a, N);
								bg_meas_b         = wiringPiI2CReadReg16(dir, BG_MEAS_B);
									bg_meas_b       = rotar(bg_meas_b, N);
								slota_float_led   = wiringPiI2CReadReg16(dir, SLOTA_FLOAT_LED);
									slota_float_led = rotar(slota_float_led, N);
								slotb_float_led   = wiringPiI2CReadReg16(dir, SLOTB_FLOAT_LED);
									slotb_float_led = rotar(slotb_float_led, N);
								math              = wiringPiI2CReadReg16(dir, Math);
									math            = rotar(math, N);
								flt_config_b      = wiringPiI2CReadReg16(dir, FLT_CONFIG_B);
									flt_config_b    = rotar(flt_config_b, N);
								flt_led_fire      = wiringPiI2CReadReg16(dir, FLT_LED_FIRE);
									flt_led_fire    = rotar(flt_led_fire, N);
								flt_config_a      = wiringPiI2CReadReg16(dir, FLT_CONFIG_A);
									flt_config_a    = rotar(flt_config_a, N);
								
								LCD_clear();
								sprintf(LCD_line1,"bg_status %x     ",bg_status);
								sprintf(LCD_line2,"bg_meas_a %x     ",bg_meas_a);
								sprintf(LCD_line3,"bg_meas_b %x     ",bg_meas_b);
								sprintf(LCD_line4,"slota_float %x   ",slota_float_led);		
								LCD_print_text();
								sleep(3);
								LCD_clear();
								sprintf(LCD_line1,"slotb_float %x   ",slotb_float_led);				
								sprintf(LCD_line2,"math %x          ",math);
								sprintf(LCD_line3,"flt_config_b %x  ",flt_config_b);
								sprintf(LCD_line4,"flt_led_fire %x  ",flt_led_fire);				
								LCD_print_text();
								sleep(3);
								LCD_clear();	
								sprintf(LCD_line1,"flt_config_a %x  ",flt_config_a);				
								sprintf(LCD_line2,"                 ");
								sprintf(LCD_line3,"                 ");
								sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{");				
								LCD_print_text();
								sleep(3);
								LCD_clear();							
								valor_AD = 0;
								CONFIG = 0;
								m1 = 0;	
								m2 = 0;	
					break;
					
					case 0x0004:

								pd_lec_select   = wiringPiI2CReadReg16(dir, PD_LED_SELECT);
									pd_lec_select   = rotar(pd_lec_select, N);
								iled3_coarse    = wiringPiI2CReadReg16(dir, ILED3_COARSE);
									iled3_coarse    = rotar(iled3_coarse, N);
								iled1_coarse    = wiringPiI2CReadReg16(dir, ILED1_COARSE);
									iled1_coarse    = rotar(iled1_coarse, N);
								iled2_coarse    = wiringPiI2CReadReg16(dir, ILED2_COARSE);
									iled2_coarse    = rotar(iled2_coarse, N);
								iled_fine       = wiringPiI2CReadReg16(dir, ILED_FINE);
									iled_fine       = rotar(iled_fine, N);
								slota_led_pulse = wiringPiI2CReadReg16(dir, SLOTA_LED_PULSE);
									slota_led_pulse = rotar(slota_led_pulse, N);
								slota_numpulses = wiringPiI2CReadReg16(dir, SLOTA_NUMPULSES);
									slota_numpulses = rotar(slota_numpulses, N);
								led_disable     = wiringPiI2CReadReg16(dir, LED_DISABLE);
									led_disable     = rotar(led_disable, N);
								slotb_led_pulse  = wiringPiI2CReadReg16(dir, SLOTB_LED_PULSE);
									slotb_led_pulse = rotar(slotb_led_pulse, N);
								slotb_numpulses = wiringPiI2CReadReg16(dir, SLOTB_NUMPULSES);
									slotb_numpulses = rotar(slotb_numpulses, N);	
									
								LCD_clear();
								sprintf(LCD_line1,"pd_lec_selec %x  ",pd_lec_select);
								sprintf(LCD_line2,"iled3_coarse %x  ",iled3_coarse);
								sprintf(LCD_line3,"iled1_coarse %x  ",iled1_coarse);
								sprintf(LCD_line4,"iled2_coarse %x  ",iled2_coarse);		
								LCD_print_text();
								sleep(3);
								LCD_clear();
								sprintf(LCD_line1,"iled_fine %x     ",iled_fine);				
								sprintf(LCD_line2,"slota_led_pu %x ",slota_led_pulse);
								sprintf(LCD_line3,"slota_numpul %x  ",slota_numpulses);
								sprintf(LCD_line4,"led_disable %x   ",led_disable);				
								LCD_print_text();
								sleep(3);
								LCD_clear();	
								sprintf(LCD_line1,"slotb_led_pu %x ",slotb_led_pulse);				
								sprintf(LCD_line2,"slotb_numpul %x  ",slotb_numpulses);
								sprintf(LCD_line3,"                 ");
								sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{");				
								LCD_print_text();
								sleep(3);
								LCD_clear();							
								valor_AD = 0;
								CONFIG = 0;
								m1 = 0;	
								m2 = 0;						
					
					break;
					
					case 0x0005:

								status         = wiringPiI2CReadReg16(dir, STATUS);
									status         = rotar(status, N);
								gpio_driv      = wiringPiI2CReadReg16(dir, GPIO_DRIV);
									gpio_driv      = rotar(gpio_driv, N);
								fifo_thresh    = wiringPiI2CReadReg16(dir, FIFO_THRESH);
									fifo_thresh    = rotar(fifo_thresh, N);
								devid          = wiringPiI2CReadReg16(dir, DEVID);
									devid          = rotar(devid, N);
								i2cs_id        = wiringPiI2CReadReg16(dir, I2CS_ID);
									i2cs_id        = rotar(i2cs_id, N);
								clk_ratio      = wiringPiI2CReadReg16(dir, CLK_RATIO);
									clk_ratio      = rotar(clk_ratio, N);
								gpio_ctrl      = wiringPiI2CReadReg16(dir, GPIO_CTRL);
									gpio_ctrl      = rotar(gpio_ctrl, N);
								slave_addr_key = wiringPiI2CReadReg16(dir, SLAVE_ADDRESS_KEY);
									slave_addr_key = rotar(slave_addr_key, N);
								ext_sync_start = wiringPiI2CReadReg16(dir, EXT_SYNC_STARTUP);
									ext_sync_start = rotar(ext_sync_start, N);
								sample_clk     = wiringPiI2CReadReg16(dir, SAMPLE_CLK);
									sample_clk     = rotar(sample_clk, N);
								clk32m_ad      = wiringPiI2CReadReg16(dir, CLK32M_ADJUST);
									clk32m_ad      = rotar(clk32m_ad, N);
								ext_sync_s     = wiringPiI2CReadReg16(dir, EXT_SYNC_SEL);
									ext_sync_s     = rotar(ext_sync_s, N);
								clk32m_cal     = wiringPiI2CReadReg16(dir, CLK32M_CAL_EN);
									clk32m_cal     = rotar(clk32m_cal, N);	
								data_acces     = wiringPiI2CReadReg16(dir, DATA_ACCESS_CTL);
									data_acces     = rotar(data_acces, N);										
									
								LCD_clear();
								sprintf(LCD_line1,"status %x        ",status);
								sprintf(LCD_line2,"gpio_driv %x     ",gpio_driv);
								sprintf(LCD_line3,"fifo_thresh %x   ",fifo_thresh);
								sprintf(LCD_line4,"devid %x         ",devid);		
								LCD_print_text();
								sleep(3);
								LCD_clear();
								sprintf(LCD_line1,"i2cs_id %x       ",i2cs_id);				
								sprintf(LCD_line2,"clk_ratio %x     ",clk_ratio);
								sprintf(LCD_line3,"gpio_ctrl %x     ",gpio_ctrl);
								sprintf(LCD_line4,"slave_addr%x     ",slave_addr_key);				
								LCD_print_text();
								sleep(3);
								LCD_clear();	
								sprintf(LCD_line1,"ext_sync_s %x    ",ext_sync_start);				
								sprintf(LCD_line2,"sample_clk %x    ",sample_clk);
								sprintf(LCD_line3,"clk32m_ad  %x    ",clk32m_ad);
								sprintf(LCD_line4,"ext_sync_s  %x   ",ext_sync_s);				
								LCD_print_text();
								sleep(3);
								LCD_clear();	
								sprintf(LCD_line1,"clk32m_cal %x    ",clk32m_cal);				
								sprintf(LCD_line2,"data_acces %x    ",data_acces);
								sprintf(LCD_line3,"                 ");
								sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{");				
								LCD_print_text();
								sleep(3);								
								LCD_clear();							
								valor_AD = 0;
								CONFIG = 0;
								m1 = 0;	
								m2 = 0;					

					break;
					
					case 0x0006: 
						reset();
								sprintf(LCD_line1,"{}{}{}{}{}{}{}{}{");				
								sprintf(LCD_line2,"    adpd188gg    ");
								sprintf(LCD_line3," succesful reset ");
								sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{");				
								LCD_print_text();
								sleep(3);
								valor_AD = 0;
								CONFIG = 0;
								m1 = 0;	
								m2 = 0;	
					
					break;
				}
			break;
			
			case 0x0004:

				Noperation = noperation == 0? noperation  = buffer[3]: noperation;
				if(Noperation == 4)
				{
					valor_AD = 0;
					m1 = 0;
				}else
				{	
				LCD_clear();
				ADPD_MODE(STANDBY);
				sprintf(LCD_line1,"{}{}{}{}{}{}{}{}{");
				sprintf(LCD_line2,"normal operation ");	
				sprintf(LCD_line3," 4 - exit        ");				
				sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{");
				LCD_print_text();
				}
				
			break;
		}

	send(newScoketConnectionFD, Buffer_server, strlen(Buffer_server),0);

	}
	}
		pthread_mutex_unlock(&socketMutex);

	}
}

int main(int argc, char *argv[])
{	 
	
    int32_t server_fd; 
    struct sockaddr_in address;
    int32_t opt = 1;
    int32_t addrlen = sizeof(address);
	int32_t iPthRc, m1 = 0;
	int dir, adpd = 0;
	char *error_adpd = "FALLO DE CONEXION ADPD188GG";
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x64);		
	
	pthread_t tid[1];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	LCD_init();
    LCD_clear();
	
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        return 1;
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        return -1;
    }
	
	iPthRc = pthread_create(&tid[0],&attr, SendMessages, argv[1]);
    if (iPthRc < 0)
      {
        printf("There was an error trying to create the pthread, iPthRc:%d\n", iPthRc);
        exit(1);
      }

	while(1){  
					
		if(m1 == 0)
		{

			pthread_mutex_lock(&socketMutex);
			
			sprintf(LCD_line1,"{}{}{}{}{}{}{}{}");
			sprintf(LCD_line2,"    waiting     ");
			sprintf(LCD_line3,"  for costumer  ");
			sprintf(LCD_line4,"{}{}{}{}{}{}{}{}");			
			LCD_print_text();
				if(newScoketConnectionFD == 0)
				{
				  newScoketConnectionFD = accept(server_fd, (struct sockaddr *)&address, 
								   (socklen_t*)&addrlen);
								   

						if (newScoketConnectionFD < 0)
					{
						printf("There was an error trying to accept in the socket, errno:%d\n", errno);
						continue;
					}	
				}else{}

			sprintf(LCD_line1,"{}{}{}{}{}{}{}{}");
			sprintf(LCD_line2,"     welcome    ");
			sprintf(LCD_line3,"     client     ");
			sprintf(LCD_line4,"{}{}{}{}{}{}{}{}");			
			LCD_print_text();		
			sleep(1);
			m1 = 1;
			pthread_mutex_unlock(&socketMutex);
		}else
		{
			adpd = wiringPiI2CReadReg16(dir, DEVID);
			
			if(adpd == -1)
			{
				printf("ADPD188GG NOT DETECTED ERROR: %d\n", adpd);
				send(newScoketConnectionFD, error_adpd, strlen(error_adpd),0);
				sleep(3);
				adpd = 0;
				important = 1;
			}else
			{
				important = 0;
			}				
		}		
	}
}





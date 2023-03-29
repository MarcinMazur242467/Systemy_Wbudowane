/*****************************************************************************
 *   Peripherals such as temp sensor, light sensor, accelerometer,
 *   and trim potentiometer are monitored and values are written to
 *   the OLED display.
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/



#include "lpc17xx_pinsel.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_timer.h"
#include "stdio.h"

#include "light.h"
#include "oled.h"
#include "temp.h"
#include "acc.h"
#include "diskio.h"
#include "ff.h"

#define UART_DEV LPC_UART3

static FILINFO Finfo;
static FIL file;
static FATFS Fatfs[1];


static uint32_t msTicks = 0;
static uint8_t buf[10];

static void intToString(int value, uint8_t* pBuf, uint32_t len, uint32_t base)
{
    static const char* pAscii = "0123456789abcdefghijklmnopqrstuvwxyz";
    int pos = 0;
    int tmpValue = value;

    // the buffer must not be null and at least have a length of 2 to handle one
    // digit and null-terminator
    if (pBuf == NULL || len < 2)
    {
        return;
    }

    // a valid base cannot be less than 2 or larger than 36
    // a base value of 2 means binary representation. A value of 1 would mean only zeros
    // a base larger than 36 can only be used if a larger alphabet were used.
    if (base < 2 || base > 36)
    {
        return;
    }

    // negative value
    if (value < 0)
    {
        tmpValue = -tmpValue;
        value    = -value;
        pBuf[pos++] = '-';
    }

    // calculate the required length of the buffer
    do {
        pos++;
        tmpValue /= base;
    } while(tmpValue > 0);


    if (pos > len)
    {
        // the len parameter is invalid.
        return;
    }

    pBuf[pos] = '\0';

    do {
        pBuf[--pos] = pAscii[value % base];
        value /= base;
    } while(value > 0);

    return;

}

void SysTick_Handler(void) {
    msTicks++;
}

static uint32_t getTicks(void)
{
    return msTicks;
}
static void init_uart(void)
{
	PINSEL_CFG_Type PinCfg;
	UART_CFG_Type uartCfg;

	/* Initialize UART3 pin connect */
	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 0;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg);

	uartCfg.Baud_rate = 115200;
	uartCfg.Databits = UART_DATABIT_8;
	uartCfg.Parity = UART_PARITY_NONE;
	uartCfg.Stopbits = UART_STOPBIT_1;

	UART_Init(UART_DEV, &uartCfg);

	UART_TxCmd(UART_DEV, ENABLE);

}


static void init_ssp(void)
{
	SSP_CFG_Type SSP_ConfigStruct;
	PINSEL_CFG_Type PinCfg;

	/*
	 * Initialize SPI pin connect
	 * P0.7 - SCK;
	 * P0.8 - MISO
	 * P0.9 - MOSI
	 * P2.2 - SSEL - used as GPIO
	 */
	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 7;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = 0;
	PinCfg.Portnum = 2;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);

	SSP_ConfigStructInit(&SSP_ConfigStruct);

	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP1, ENABLE);

}


static void init_i2c(void)
{
	PINSEL_CFG_Type PinCfg;

	/* Initialize I2C2 pin connect */
	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 10;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);

	// Initialize I2C peripheral
	I2C_Init(LPC_I2C2, 100000);

	/* Enable I2C1 operation */
	I2C_Cmd(LPC_I2C2, ENABLE);
}

static void init_adc(void)
{
	PINSEL_CFG_Type PinCfg;

	/*
	 * Init ADC pin connect
	 * AD0.0 on P0.23
	 */
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 23;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);

	/* Configuration for ADC :
	 * 	Frequency at 0.2Mhz
	 *  ADC channel 0, no Interrupt
	 */
	ADC_Init(LPC_ADC, 200000);
	ADC_IntConfig(LPC_ADC,ADC_CHANNEL_0,DISABLE);
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_0,ENABLE);

}



int main (void)
{
    int32_t xoff = 0;
    int32_t yoff = 0;
    int32_t zoff = 0;

    int8_t x = 0;
    int8_t y = 0;
    int8_t z = 0;

    int32_t t = 0;
    uint32_t lux = 0;
    uint32_t trim = 0;


    init_i2c();
    init_adc();

    init_ssp();
    init_uart();
    oled_init();
    light_init();
    acc_init();

    temp_init (&getTicks);


	if (SysTick_Config(SystemCoreClock / 1000)) {
		    while (1);  // Capture error
	}

    /*
     * Assume base board in zero-g position when reading first value.
     */
    acc_read(&x, &y, &z);
    xoff = 0-x;
    yoff = 0-y;
    zoff = 64-z;

    light_enable();
    light_setRange(LIGHT_RANGE_4000);

    oled_clearScreen(OLED_COLOR_WHITE);

    oled_putString(1,1,  (uint8_t*)"Young Leosia", OLED_COLOR_BLACK, OLED_COLOR_WHITE);

    DSTATUS stat;
      DWORD p2;
      WORD w1;
      BYTE res, b1;
      DIR dir;

      int i = 0;





      printf("MMC/SD example\r\n");

      SysTick_Config(SystemCoreClock / 100);

      Timer0_Wait(500);

      stat = disk_initialize(0);
      if (stat & STA_NOINIT) {
      	printf("MMC: not initialized\r\n");
      }

      if (stat & STA_NODISK) {
      	printf("MMC: No Disk\r\n");
      }

      if (stat != 0) {
          return 1;
      }

      printf("MMC: Initialized\r\n");

      printf("Reading FLASH");

      res = f_mount(0, &Fatfs[0]);
      if(res != FR_OK) {
    	  printf("Failed to mount");
    	  return 1;
      }


      res = f_opendir(&dir, "/");
      if(res) {
    	  printf("Failed to open dir /");
    	  return 1;
      }

      char fileNames[20][13];
      int index = 0;
      char wavFiles[20][13];

      for(;;) {
    	  res = f_readdir(&dir, &Finfo);
    	  if ((res != FR_OK) || !Finfo.fname[0])
    		  break;

    	  char substring[4];
    	  int j = 0;
    	  int len = strlen(Finfo.fname);
    	  for(int k = len-4; k < len; k++) {
    		  substring[j] = Finfo.fname[k];
    		  j++;
    	  }
    	  char wav[4] = ".wav";
    	  if(strcmp(wav, substring) != 32)
    		  continue;



    	  for(int j = 0; j < 13; j++) {
        	  wavFiles[index][j] = Finfo.fname[j];
    		  if(j < strlen(Finfo.fname)-4)
        		  fileNames[index][j] = Finfo.fname[j];
    		  else
    			  fileNames[index][j] = '\0';
    	  }
    	  index++;
      }
      for(int i = 0; i < index; i++) {
    	  printf((uint8_t*)&(fileNames[i][0]));
    	  printf("\n");
      }




      int prevChosenFileIndex = 0;
      int chosenFileIndex = 0;

    while(1) {
        // Accelerometer
        acc_read(&x, &y, &z);
        x = x+xoff;
        y = y+yoff;
        z = z+zoff;

        //switch songs on tilt
    	prevChosenFileIndex = chosenFileIndex;
        if((x >= 30 && z <=30)&&chosenFileIndex != 0)
        	chosenFileIndex-=1;

        if((x <= -30 && z <=30)&&chosenFileIndex != index)
        	chosenFileIndex+=1;

        if(chosenFileIndex != prevChosenFileIndex){
			oled_clearScreen(OLED_COLOR_WHITE);
			char name[strlen(fileNames[chosenFileIndex]+3)];
			sprintf(name, "%i. %s", chosenFileIndex+1, fileNames[chosenFileIndex]);
			oled_putString(1,1,name, OLED_COLOR_BLACK, OLED_COLOR_WHITE);

			UINT br;
			UINT btr[10];
			f_open(&file, "FLOYD.WAV", 0x01);//&wavFiles[chosenFileIndex]
			//f_read(&file, btr, 10, &br);
			printf(btr);
        }
        char str[80];
        //sprintf(str, "x:%i y:%i z:%i\n", x,y,z);
        //printf(str);
        /* delay */
        Timer0_Wait(200);
    }
}

void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
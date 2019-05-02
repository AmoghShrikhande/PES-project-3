/**
 * @file    DMA.c
 * @brief   Application entry point.
 */

/***************************************************************************************
 *                          HEADER FILES                                                *
 ***************************************************************************************/
#include <stdio.h>
#include <math.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "../dma/includes/uart.h"
#include "../dma/includes/adc.h"
#include "../dma/includes/dma.h"

/***************************************************************************************
 *                          GLOBAL VARIABLES                                            *
 ***************************************************************************************/
int8_t str[20];
int8_t str1[20];
int8_t str2[50];

int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	// Initialize
	adc_init();
 	dma_init();

	extern uint8_t dma_interrupt_flag;
	extern uint8_t flag;
	extern uint32_t buffer1[256];
	extern uint16_t data_buff[256];
	extern uint32_t double_buff1;
	extern uint32_t double_buff2;
    extern bool buff_check_flag;
    float max;
	float max1 = 0;
	float alpha = 0.5;
	float j;
	int i;
	int k,m;
    float dBFS_value[66];
	float x;




	for(i = 0 , j = 500; i<= 66 && j <= 65500;i++, j= j+1000)
	{
		dBFS_value[i] = (20 *( log10(j/32768)));

	}




//	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
//	PORTB->PCR[11] |= PORT_PCR_MUX(0x1);
//	GPIOB->PDDR |= 0x800;

//	while(1)
//		{
//			PRINTF("\n\r in main");
//			if(flag == 1)
//			{
//				PRINTF("\n \r pin set");
//				flag =0;
//				GPIOB->PSOR |= 0x800;
//			}
//		}

	while(1)
	{

		if(flag == 1)
		{
			flag =0;
			GPIOB->PSOR |= 0x800;
		}

		if(dma_interrupt_flag ==1)
		{

			max=0;
			dma_interrupt_flag =0;

			if(buff_check_flag == 0)
			{
				buff_check_flag =1;
				for (int i = 0; i< 128; i++)
				{

					if (max < data_buff[double_buff2+i])
					{
						max = data_buff[double_buff2+i];
					}

					sprintf(str,"\n \r arr val %d: %d",i,data_buff[double_buff2+i]);
					putst(str);
				}
			}
			else if(buff_check_flag == 1)
			{
				buff_check_flag =0;
				for (int i = 0; i< 128; i++)
				{

					if (max < data_buff[double_buff1+i])
					{
						max = data_buff[double_buff1+i];
					}

					sprintf(str,"\n \r arr val %d: %d",i,data_buff[double_buff1+i]);
					putst(str);
				}
			}
			if ( max1 < max)
			{
				max1 = max;
			}

			else
			{
				max1 =  alpha * max1;
			}

			sprintf(str1,"\n \r Peak value :  %d",(uint16_t)max1);
			putst(str1);

			for(m = 0, k = 1000; m<=66 && k < 66000; m++,k = k+1000)
			{
				if(max1< k)
				{
					sprintf(str2,"\n\rdBFS value corresponding to the peak value: %f" , dBFS_value[m]);
					putst(str2);
					break;
				}

			}
		}
	}
	return 0 ;
}

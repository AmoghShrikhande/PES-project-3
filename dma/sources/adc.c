/*
 * adc.c
 *
 *  Created on: Apr 22, 2019
 *      Author: srina
 */
#include "../includes/adc.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

void adc_init()
{
	SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV4(2);
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	ADC0->CFG1 |= ADC_CFG1_ADIV(3);
	ADC0->CFG1 |= ADC_CFG1_ADLSMP(1);
	ADC0->CFG1 |= ADC_CFG1_MODE(3);
	ADC0->CFG1 |= ADC_CFG1_ADICLK(1);

	ADC0->SC3 |= ADC_SC3_ADCO_MASK;
	ADC0->SC3 |= ADC_SC3_AVGE_MASK;
	ADC0->SC3 |= ADC_SC3_AVGS_MASK;

	ADC0->SC1[0] &= ~ADC_SC1_ADCH_MASK;
	ADC0->SC1[0] |=  ADC_SC1_AIEN_MASK;



	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[18] |= PORT_PCR_MUX(0x1);
	GPIOB->PDDR |= 0x40000;


	NVIC_EnableIRQ(ADC0_IRQn);
	__enable_irq();


}

void GPIO_toggle()
{

		GPIOB->PSOR |= 0x40000;
		delayms1(1000);
		GPIOB->PCOR |= 0x40000;
}

void ADC0_IRQHandler(void)
{
	PRINTF("\n Entered IRQ");
	__disable_irq();
	uint32_t var = ADC0->R[0];
	PRINTF("\n The adc value is:%d", var);
	GPIO_toggle();
	//flag = 1;
	__enable_irq();
}

void delayms1(int t)
{
	int i,j;

	for(i=0;i<t;i++)
	{
		for(j=0;j<10000;j++)
		{

		}
	}
}



uint32_t adc_read_polling()
{
	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
	{

	}
	return ADC0->R[0];
	//PRINTF("ADC: %d",adc_value_read);
}

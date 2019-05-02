/*
 * adc.c
 *
 *  Created on: Apr 22, 2019
 *      Author: srina
 */

/***************************************************************************************
 *                          HEADER FILES                                                *
 ***************************************************************************************/
#include "../includes/adc.h"

/***************************************************************************************
 *                          GLOBAL VARIABLES                                            *
 ***************************************************************************************/
volatile uint8_t flag =0;

/*******************************************************************************
 * Function Name: adc_init
 ********************************************************************************
 *
 * Summary
 *  This function helps the user to enable the adc for channel 0 in continuous sample mode
 *  with a 16 bit resolution
 *
 * Parameters:
 *  None
 *
 * Return:
 *  None.
 *
 * Reentrant:
 *  No.
 *
 * Reference:
 *  Mazidi
 *******************************************************************************/
void adc_init()
{

	// Divide bus clock by 3
	SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV4(2);

	// Enable clock to the ADC
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	// Set Clock divide as 3, the clock frequency is reduced by 8, Select long sample time, Select 16 bit mode for ADC, Divide the bus frequency by 2
	ADC0->CFG1 |= ADC_CFG1_ADICLK(1) | ADC_CFG1_MODE(3) | ADC_CFG1_ADLSMP(1) | ADC_CFG1_ADIV(3);

	// Enable Continuous Conversion, Enable Hardware average,  16 samples averaged
	ADC0->SC3 |= ADC_SC3_ADCO_MASK | ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(2);

	// Enable ADC in Differential mode
	ADC0->SC1[0] |= ADC_SC1_DIFF(0);

	// Select channel 0 for ADC transfer
	ADC0->SC1[0] &= ~ADC_SC1_ADCH_MASK;

	// Enable the DMA
	ADC0->SC2 |= ADC_SC2_DMAEN_MASK;

	// Enable the Interrupt when COCO flag is 1
	ADC0->SC1[0] |=  ADC_SC1_AIEN_MASK;

	// Enable clock for port B
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

	// Select port pin as GPIO pin
	PORTB->PCR[18] |= PORT_PCR_MUX(0x1);

	// Pin configured as output
	GPIOB->PDDR |= 0x40000;


	// Enable Global interrupts for ADC0
//	NVIC_EnableIRQ(ADC0_IRQn);

	// Enable Interrupts
//	__enable_irq();
}
//
//void ADC0_IRQHandler(void)
//{
//	__disable_irq();
//	PRINTF("\n \r In ADC ISR");
//	if(flag == 0)
//	{
//		PRINTF("\n \r pin clear");
//		GPIOB->PCOR |= 0x800;
//		flag = 1;
//	}
//	__enable_irq();
//}

/*
 * uart.c
 *
 *  Created on: Apr 10, 2019
 *      Author: amosh
 */

/* Mazidi : https://electrovolt.ir/wp-content/uploads/2017/07/Freescale_ARM_Cortex_M_Embedded_ElectroVolt.ir_.pdf */

/***************************************************************************************
 *                          HEADER FILES                                                *
 ***************************************************************************************/
#include "../includes/uart.h"

/***************************************************************************************
 *                          HEADER FILES                                                *
 ***************************************************************************************/
#define BDH_VALUE 0x00
#define BDL_VALUE 0x18

/***************************************************************************************
 *                          GLOBAL VARIABLES                                            *
 ***************************************************************************************/
extern uint8_t data_poll;

/*******************************************************************************
 * Function Name: interrupt_enable
 ********************************************************************************
 *
 * Summary
 *  This function helps the user to enable the interrupts
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
 *  Self
 *******************************************************************************/

void interrupt_enable()
{
	// Enable Interrupts for UART0
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable the receive interrupt for UART
	UART0->C2 |= UART0_C2_RIE(1);

	//Enable global interrupts (IRQs)
	__enable_irq();
}

/*******************************************************************************
 * Function Name: uart_init
 ********************************************************************************
 *
 * Summary
 *  This function helps the user to enable the uart in interrupt and polling mode
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
void uart_init()
{
	// Enabling clock for port A
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Enable UART0 clock (D10 bit in SIM_SCSC4 register)
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; //clock

	// Configuring the PTA2 UART0_Rx pin
	PORTA->PCR[1] |= PORT_PCR_MUX(0x2);

	// Configuring the PTA2 UART0_Tx pin
	PORTA->PCR[2] |= PORT_PCR_MUX(0x2);

	// Select FLL clock o/p for UART0 to obtain 41.94 MHz frequency
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

	// Disable Interrupts and UART Transmit and Receive for polling
	UART0->C2 &= 0x00;

	// Set values in BDH and BDL to set the required baud rate
	UART0->BDH = BDH_VALUE ;
	UART0->BDL = BDL_VALUE ;

	// Disable the UART
	UART0->C1 &= 0x00;

	// Enable Transmit and receive for UART0
	UART0->C2 |= (UART0_C2_TE(1) | UART0_C2_RE(1));

	// Set OSR required to achieve the baud rate
	UART0->C4 = 0x0f;
}

/*******************************************************************************
 * Function Name: putch
 ********************************************************************************
 *
 * Summary
 *  This function enables the user to print a character on serial terminal
 *
 * Parameters:
 *  Integer pointer
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

void putch(uint8_t *data_poll)
{
	// poll till the transmit buffer is empty and the transmission complete flag is 1
	while(!(UART0->S1 & UART0_S1_TDRE_MASK) && !(UART0->S1 & UART0_S1_TC_MASK))
	{
	}
	UART0->D = *data_poll;
}



/*******************************************************************************
 * Function Name: getch
 ********************************************************************************
 *
 * Summary
 *  This function enables the user to create a required delay in ms
 *
 * Parameters:
 *  Integer, the value of integer gives the value of delay in ms
 *
 * Return:
 *  None.
 *
 * Reentrant:
 *  No.
 *
 * Reference:
 *  Project 2
 *******************************************************************************/

void getch()
{
#ifdef POLLING
	while(!(UART0->S1 & UART0_S1_RDRF_MASK) )
	{

	}
	data_poll = UART0->D;
#endif
}

/********************************************************************************
 * Function Name: putst                                                         *
 ********************************************************************************
 *
 * Summary
 *  This function enables the user to print strings on serial term
 *
 * Parameters:
 *  Character pointer
 *
 * Return:
 *  None.
 *
 * Reentrant:
 *  No.
 *
 * Reference:
 *  Project 2
 *******************************************************************************/
void putst(char *string)
{
	while(*string != '\0')
	{
		while(!(UART0->S1 & UART0_S1_TDRE_MASK) && !(UART0->S1 & UART0_S1_TC_MASK))
		{

		}

		UART0->D = *string;
		string++;
	}
}



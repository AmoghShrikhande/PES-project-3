/*
 * uart.h
 *
 *  Created on: Apr 10, 2019
 *      Author: amosh
 */

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_




#define INTERRUPTS 1
/**
 * @file    MKL25Z128xxx4_Project_UART_Srinath_Amogh.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"










void interrupt_enable();
void uart_init();
void getch();
void putstr(char *ch);
void putch(data_poll);


#endif /* INCLUDES_UART_H_ */

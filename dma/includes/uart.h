
/*
 * uart.h
 *
 *  Created on: Apr 10, 2019
 *      Author: amosh
 */

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_

/***************************************************************************************
*                          HEADERS & MACROS                                            *
***************************************************************************************/
#include "MKL25Z4.h"
#include <stdio.h>
#define POLLING 1

/***************************************************************************************
*                          GLOBAL VARIABLES                                            *
***************************************************************************************/
extern int count[256];
extern char report_charac[256];
extern int character_entred_flag;
extern int GPIO_flag;

/***************************************************************************************
*                          FUNCTION PROTOTYPES                                         *
***************************************************************************************/
void interrupt_enable();
void uart_init();
void getch();
void putstr(char *ch);
void putch(data_poll);

#endif /* INCLUDES_UART_H_ */


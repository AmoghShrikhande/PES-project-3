/*
 * adc.h
 *
 *  Created on: Apr 26, 2019
 *      Author: Amogh and Srinath
 */

#ifndef INCLUDES_ADC_H_
#define INCLUDES_ADC_H_

/***************************************************************************************
*                          HEADERS & MACROS                                            *
***************************************************************************************/
#include "peripherals.h"
#include "MKL25Z4.h"
#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

/***************************************************************************************
*                          FUNCTION PROTOTYPES                                         *
***************************************************************************************/
void adc_init();
uint32_t adc_read_polling();


#endif /* INCLUDES_ADC_H_ */

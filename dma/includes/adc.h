/*
 * adc.h
 *
 *  Created on: Apr 26, 2019
 *      Author: srina
 */

#ifndef INCLUDES_ADC_H_
#define INCLUDES_ADC_H_


#include "peripherals.h"
#include "MKL25Z4.h"

void adc_init();
uint32_t adc_read_polling();

#endif /* INCLUDES_ADC_H_ */

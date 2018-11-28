/*
 * utilitarioTiva.h
 *
 *  Created on: 28 de mai de 2018
 *      Author: jhonathan
 */

#ifndef BIBLIOTECAS_UTILITARIOTIVA_H_
#define BIBLIOTECAS_UTILITARIOTIVA_H_
#include <tm4c123gh6pm.h>
#include <inttypes.h>

void configurarSysTick(uint32_t reload, uint32_t ctrl);
void delay(uint32_t millis);
uint32_t getMillis();
uint32_t getMicro();
void itoa(uint32_t value, char* result, int base);
void trataST();
#endif /* BIBLIOTECAS_UTILITARIOTIVA_H_ */

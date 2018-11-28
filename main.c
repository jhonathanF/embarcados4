#include "bibliotecas/utilitarioTiva.h"
#include "bibliotecas/gpioUtils.h"
#include <tm4c123gh6pm.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void trataPortA(void);
void trataPortB(void);
void trataPortC(void);
void trataPortD(void);
void trataPortE(void);
uint32_t leituraX;
uint32_t leituraY;
int pausado = 0;
int filaEnvios[20];
int index = 0;
#define UART_FR_TXFF            0x00000020          // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010
void setup()
{
    configurarSysTick(16, 0x03);

    //-----ATIVAR OS PORTS-----//
    ativarRCGC(RCGC_PORT_A);
    ativarRCGC(RCGC_PORT_B);
    ativarRCGC(RCGC_PORT_C);
    ativarRCGC(RCGC_PORT_D);
    ativarRCGC(RCGC_PORT_E);
    ativarRCGC(RCGC_PORT_F);
    SYSCTL_RCGCADC_R |= 0x01;
    SYSCTL_RCGCADC_R |= 0x02;

    //-----CONFIGURAR ADC-----//
    habilitarADCPorts(&GPIO_PORTD_AFSEL_R, &GPIO_PORTD_AMSEL_R, 1);
    configurarADC0(0x0F, 0x06, 0x02, 0x01, 0x01, 0);
    configurarADC1(0x0F, 0x07, 0x02, 0x01, 0x01, 0);

    //-----CONFIGURAR INTERRUPÇÕES-----//

    //-----CONFIGURAR PINOS-----//
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 2, INPUT);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 3, INPUT);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 4, INPUT);
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, 2, INPUT);
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, 3, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, 4, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, 5, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, 6, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, 7, INPUT);
    configurarPino(&GPIO_PORTD_DIR_R, &GPIO_PORTD_DEN_R, 6, INPUT);

    configurarPino(&GPIO_PORTF_DIR_R, &GPIO_PORTF_DEN_R, 4, INPUT);

    configurarUART0(0x01, &GPIO_PORTA_AFSEL_R, &GPIO_PORTA_PCTL_R, 8, 44, 0x70,
                    0x00, 0x301);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 0, INPUT);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 1, INPUT);
}

typedef struct
{
    uint32_t lightness;
    uint32_t temperature;
    uint32_t distance;
} Data;
Data data;

void sendUartText(char* texto)
{
    uint32_t i, length = strlen(texto);

    for (i = 0; i < length; i++)
    {
        escreverUART0(texto[i]);
    }
}

void sendStruct()
{
    char buf[200] = { 0 };
    sprintf(buf,
            "{\"lightness\": \"%d\", \"temperature\": \"%d\", \"distance\": \"%d\"}\n",
            data.lightness, data.temperature, data.distance);
    sendUartText(buf);
}

int main(void)
{
    data.distance = 5;
    data.lightness = 0;
    data.temperature = 0;
    setup();
    escreverUART0(116);
    escreverUART0(104);
    escreverUART0(105);
    while (1)
    {
        sendStruct();
        delay(1000);
        data.distance = 5;
        data.lightness = ADC0_SSFIFO0_R;
        data.temperature = 0;
    }
}

void trataPortA()
{

}

void trataPortB()
{

}

void trataPortC()
{

}

void trataPortD()
{

}

void trataPortE()
{
}

void trataPortF()
{

}


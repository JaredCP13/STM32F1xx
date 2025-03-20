#include "stm32f10x.h"
#include "timers.h"

void GPIO_Init(void);

int main(void) {
    // Inicializar GPIO
    GPIO_Init();

    // Inicializar Timer 2
    TIM2_Init();

    while (1) {
        // Código principal en bucle infinito
    }
}

void GPIO_Init(void) {
    // Habilitar reloj para GPIOB
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // Configurar PB0 como salida de propósito general
    GPIOB->CRL &= ~GPIO_CRL_MODE0;  // Limpiar configuración previa
    GPIOB->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1; // Salida 50 MHz
    GPIOB->CRL &= ~GPIO_CRL_CNF0;  // Salida push-pull

    // Apagar PB0 al inicio
    GPIOB->BSRR = GPIO_BSRR_BR0;
}
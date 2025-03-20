#include "timers.h"
#include "stm32f10x.h"


void TIM2_Init(void) {
    // Habilitar el reloj del Timer 2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Configurar el prescaler para 10 kHz (72 MHz / 7200)
    TIM2->PSC = 7200 - 1;

    // Configurar el periodo a 200 (para generar interrupción cada 20 ms)
    TIM2->ARR = 200 - 1;

    // Habilitar interrupción de actualización
    TIM2->DIER |= TIM_DIER_UIE;

    // Habilitar la interrupción en el NVIC
    NVIC_EnableIRQ(TIM2_IRQn);

    // Iniciar el timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

volatile uint8_t pulse_state = 0;

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF; // Limpiar la bandera de interrupción

        if (pulse_state == 0) {
            GPIOB->BSRR = GPIO_BSRR_BS0;  // Encender PB0
            pulse_state = 1;
        } else {
            for (volatile int i = 0; i < 72000; i++); // Aproximadamente 1ms de retardo
            GPIOB->BSRR = GPIO_BSRR_BR0;  // Apagar PB0
            pulse_state = 0;
        }
    }
}
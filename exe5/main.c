#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define BOTAO_PIN 28
#define LED_PIN 4
#define TEMPO_LONGO 800

static uint32_t tempo_inicio = 0;

void botao_callback(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_FALL) {
        tempo_inicio = to_ms_since_boot(get_absolute_time());
    }
    
    if (events & GPIO_IRQ_EDGE_RISE) {
        uint32_t tempo_fim = to_ms_since_boot(get_absolute_time());
        uint32_t duracao = tempo_fim - tempo_inicio;
        
        if (duracao >= TEMPO_LONGO) {
            printf("Aperto longo!\n");
        } else {
            printf("Aperto curto!\n");
        }
    }
}

int main() {
    stdio_init_all();
    
    gpio_init(BOTAO_PIN);
    gpio_set_dir(BOTAO_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_PIN);
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    gpio_set_irq_enabled_with_callback(BOTAO_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, 1, &botao_callback);

    while (true) {
        tight_loop_contents();
    }
}

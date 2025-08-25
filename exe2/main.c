#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define BUTTON_PIN 28
#define LED_PIN 4

volatile int button_pressed = 0;

void gpio_irq_handler(uint gpio, uint32_t events) {
    if (gpio == BUTTON_PIN && events & GPIO_IRQ_EDGE_FALL) {
        button_pressed = 1;
    }
}

int main() {
    stdio_init_all();
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    
    bool led_state = false;
    
    while (true) {
        if (button_pressed) {
            led_state = !led_state;
            gpio_put(LED_PIN, led_state);
            button_pressed = 0;
        }
    }
}

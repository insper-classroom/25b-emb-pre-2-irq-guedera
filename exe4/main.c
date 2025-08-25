#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED_RED = 4;
const int LED_GREEN = 6;
const int BTN_RED = 28;
const int BTN_GREEN = 26;

void btn_callback(uint gpio, uint32_t events) {
    if (gpio == BTN_RED && events == GPIO_IRQ_EDGE_FALL) {
        //led v
        gpio_put(LED_RED, !gpio_get(LED_RED));
    } else if (gpio == BTN_GREEN && events == GPIO_IRQ_EDGE_RISE) {
        //led g
        gpio_put(LED_GREEN, !gpio_get(LED_GREEN));
    }
}

int main() {
    stdio_init_all();

    //init leds
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);

    //init btns
    gpio_init(BTN_RED);
    gpio_set_dir(BTN_RED, GPIO_IN);
    gpio_pull_up(BTN_RED);

    gpio_init(BTN_GREEN);
    gpio_set_dir(BTN_GREEN, GPIO_IN);
    gpio_pull_up(BTN_GREEN);

    //interrps
    gpio_set_irq_enabled_with_callback(BTN_RED, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled(BTN_GREEN, GPIO_IRQ_EDGE_RISE, true);

    while (true) {
    }
}

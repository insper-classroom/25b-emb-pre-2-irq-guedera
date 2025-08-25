#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED_RED = 4;
const int LED_GREEN = 6;
const int BTN_RED = 28;
const int BTN_GREEN = 26;

void btn_callback(uint gpio, uint32_t events) {
    static int led_v_estado = 0;
    static int led_g_estado = 0;
    
    if (gpio == BTN_RED && events == GPIO_IRQ_EDGE_FALL) {
        //led v
        led_v_estado = !led_v_estado;
        gpio_put(LED_RED, led_v_estado);
    } else if (gpio == BTN_GREEN && events == GPIO_IRQ_EDGE_RISE) {
        //led g
        led_g_estado = !led_g_estado;
        gpio_put(LED_GREEN, led_g_estado);
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
    gpio_set_irq_enabled_with_callback(BTN_RED, GPIO_IRQ_EDGE_FALL, 1, &btn_callback);
    gpio_set_irq_enabled(BTN_GREEN, GPIO_IRQ_EDGE_RISE, 1);

    while (true) {
    }
}
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;

volatile int button_event_flag = 0;
volatile int button_fall_event = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    button_fall_event = 1;
    button_event_flag = 1;
  } else if (events == 0x8) { // rise edge
    button_fall_event = 0;
    button_event_flag = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if (button_event_flag) {
      button_event_flag = 0;
      if (button_fall_event) {
        printf("fall \n");
      } else {
        printf("rise \n");
      }
    }
  }
}

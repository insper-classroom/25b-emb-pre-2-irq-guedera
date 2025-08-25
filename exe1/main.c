#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;

volatile bool button_event_flag = false;
volatile bool button_fall_event = false;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    button_fall_event = true;
    button_event_flag = true;
  } else if (events == 0x8) { // rise edge
    button_fall_event = false;
    button_event_flag = true;
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
      button_event_flag = false;
      if (button_fall_event) {
        printf("fall \n");
      } else {
        printf("rise \n");
      }
    }
  }
}

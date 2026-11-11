#include <stdio.h>
#include <pico/stdlib.h>
#include "blink.h"

void init_led(void)
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
}

void blink_loop(void)
{
    int count = 0;
    while (true)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, count & 1);
        printf("blink %d\n", count++);
        sleep_ms(500);
    }
}


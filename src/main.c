#include <stdio.h>
#include <pico/stdlib.h>
#include "blink.h"


int main(void)
{
    stdio_init_all();
    init_led();
    blink_loop();
}

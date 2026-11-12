#include <stdio.h>
#include <pico/stdlib.h>
#include "tusb.h"
#include "blink.h"


int main(void)
{
    stdio_init_all();
    tusb_init();
    init_led();
    blink_loop();
}

uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO: Not implemented
  (void) itf;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  // TODO: Not implemented
  (void) itf;
  (void) report_id;
  (void) report_type;

  // echo back anything we received from host
  tud_hid_report(0, buffer, bufsize);
}


#include "tusb.h"

static const uint8_t desc_hid_report[] = {
    TUD_HID_REPORT_DESC_FIDO_U2F(CFG_TUD_HID_EP_BUFSIZE)
};

uint8_t const *tud_hid_descriptor_report_cb(uint8_t itf)
{
  (void) itf;
  return desc_hid_report;
}

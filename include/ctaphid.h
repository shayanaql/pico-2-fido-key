#ifndef CTAPHID_H
#define CTAPHID_H

#include <stdint.h>
#include "tusb_config.h"

typedef enum {
    CTAPHID_PING = 0x01,
    CTAPHID_MSG = 0x03,
    CTAPHID_INIT = 0x06,
    CTAPHID_CBOR = 0x10,
    CTAPHID_CANCEL = 0x11,
    CTAPHID_KEEPALIVE = 0x3B,
    CTAPHID_ERROR = 0x3F
} ctaphid_cmds;

typedef struct {
    uint32_t cid;                             // Channel identifier
    uint8_t cmd;                              // Command identifier
    uint8_t bcnth;                            // High part of payload length
    uint8_t bcntl;                            // Low part of payload length
    uint8_t data[CFG_TUD_HID_EP_BUFSIZE - 7]; // Payload data
} ctaphid_init_packet; 

typedef struct {
    uint32_t cid;                             // Channel identifier
    uint8_t seq;                              // Packet sequence
    uint8_t data[CFG_TUD_HID_EP_BUFSIZE - 5]; // Payload data
} ctaphid_cont_packet;

#endif //CTAPHID_H


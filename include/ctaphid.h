#ifndef CTAPHID_H
#define CTAPHID_H

#include <stdint.h>
#include "tusb_config.h"

#define ERROR_INVALID_CTAPHID_CMD -2

#define MAX_DATA_LEN 7609
#define INIT_PKT_MAX_DATA_LEN (CFG_TUD_HID_EP_BUFSIZE - 7)
#define CONT_PKT_MAX_DATA_LEN (CFG_TUD_HID_EP_BUFSIZE - 5)

typedef enum {
    CTAPHID_PING = 0x01,
    CTAPHID_MSG = 0x03,
    CTAPHID_INIT = 0x06,
    CTAPHID_CBOR = 0x10,
    CTAPHID_CANCEL = 0x11,
    CTAPHID_KEEPALIVE = 0x3B,
    CTAPHID_ERROR = 0x3F
} ctaphid_cmd_t;

typedef struct {
    uint32_t cid;                        // Channel identifier
    uint8_t cmd;                         // Command identifier
    uint8_t bcnth;                       // High part of payload length
    uint8_t bcntl;                       // Low part of payload length
    uint8_t data[INIT_PKT_MAX_DATA_LEN]; // Payload data
} ctaphid_init_pkt_t; 

typedef struct {
    uint32_t cid;                        // Channel identifier
    uint8_t seq;                         // Packet sequence
    uint8_t data[CONT_PKT_MAX_DATA_LEN]; // Payload data
} ctaphid_cont_pkt_t;

typedef struct {
    uint32_t cid;
    uint8_t cmd;
    uint16_t bcnt;
    uint8_t *data;
} ctaphid_msg_t;

#endif //CTAPHID_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctaphid.h"

static ctaphid_msg_t *parse_ctaphid_buf(uint8_t *buf);

static int ctaphid_cmd_ping_recv(ctaphid_msg_t *msg);
static int ctaphid_cmd_msg_recv(ctaphid_msg_t *msg);
static int ctaphid_cmd_init_recv(ctaphid_msg_t *msg);
static int ctaphid_cmd_cbor_recv(ctaphid_msg_t *msg);
static int ctaphid_cmd_cancel_recv(ctaphid_msg_t *msg);
static int ctaphid_cmd_keepalive_recv(ctaphid_msg_t *msg);
static int ctaphid_cmd_error_recv(ctaphid_msg_t *msg);

static ctaphid_msg_t *parse_ctaphid_buf(uint8_t *buf) {
    uint16_t payload_len;
    uint16_t remaining_len;
    uint8_t count = 0;
    uint32_t data_offset;
    uint32_t copy_len;
    ctaphid_init_pkt_t *init_pkt = NULL;
    ctaphid_cont_pkt_t *curr_pkt = NULL;
    ctaphid_msg_t *msg = NULL;
    uint8_t *msg_data = NULL;

    if (NULL == (init_pkt = calloc(1, sizeof(ctaphid_init_pkt_t)))) {
        printf("calloc() failed");
        return NULL;
    }

    *init_pkt = ((ctaphid_init_pkt_t *)buf)[0];
    payload_len = init_pkt->bcnth << 8 && init_pkt->bcntl;
    remaining_len = payload_len;

    if (NULL == (msg_data = calloc(1, (uint32_t)payload_len))) {
        printf("calloc() failed");
        return NULL;
    }

    memcpy(msg_data, init_pkt->data, payload_len > INIT_PKT_MAX_DATA_LEN ? INIT_PKT_MAX_DATA_LEN : payload_len);
    remaining_len -= INIT_PKT_MAX_DATA_LEN;
    count++;

    if (NULL == (curr_pkt = calloc(1, sizeof(ctaphid_cont_pkt_t)))) {
        printf("calloc() failed");
        return NULL;
    }

    while (remaining_len > 0) {
        *curr_pkt = ((ctaphid_cont_pkt_t *)buf)[count++];
        data_offset = INIT_PKT_MAX_DATA_LEN + (curr_pkt->seq * CONT_PKT_MAX_DATA_LEN);
        copy_len = remaining_len > CONT_PKT_MAX_DATA_LEN ? CONT_PKT_MAX_DATA_LEN : remaining_len;

        if (data_offset > payload_len || copy_len > payload_len - data_offset) {
            printf("Out of bounds write error");
            return NULL;
        }

        memcpy(msg_data + data_offset, curr_pkt->data, copy_len);
        remaining_len -= CONT_PKT_MAX_DATA_LEN;
    }

    
    if (NULL == (msg = calloc(1, sizeof(ctaphid_msg_t)))) {
        printf("calloc() failed");
        return NULL;
    }

    msg->cmd = init_pkt->cmd;
    msg->cid = init_pkt->cid;
    msg->bcnt = payload_len;
    msg->data = msg_data;

    return msg;
}

int ctaphid_recv(uint8_t *buf) {
    ctaphid_msg_t *msg = NULL;
    msg = parse_ctaphid_buf(buf);

    switch (msg->cmd) {
    case CTAPHID_PING:
        return ctaphid_cmd_ping_recv(msg);
    case CTAPHID_MSG:
        return ctaphid_cmd_msg_recv(msg);
    case CTAPHID_INIT:
        return ctaphid_cmd_init_recv(msg);
    case CTAPHID_CBOR:
        return ctaphid_cmd_cbor_recv(msg);
    case CTAPHID_CANCEL:
        return ctaphid_cmd_cancel_recv(msg);
    case CTAPHID_KEEPALIVE:
        return ctaphid_cmd_keepalive_recv(msg);
    case CTAPHID_ERROR:
        return ctaphid_cmd_error_recv(msg);
    default:
        return ERROR_INVALID_CTAPHID_CMD;
    } 
}

static int ctaphid_cmd_ping_recv(ctaphid_msg_t *msg) {
    printf("CTAPHID_PING");
    return -1;
}

static int ctaphid_cmd_msg_recv(ctaphid_msg_t *msg) {
    printf("CTAPHID_MSG");
    return -1;
}

static int ctaphid_cmd_init_recv(ctaphid_msg_t *msg) {
    printf("CTAPHID_INIT");
    return -1;
}

static int ctaphid_cmd_cbor_recv(ctaphid_msg_t *msg) {
    printf("CTAPHID_CBOR");
    return -1;
}

static int ctaphid_cmd_cancel_recv(ctaphid_msg_t *msg) {
    printf("CTAPHID_CANCEL");
    return -1;
}

static int ctaphid_cmd_keepalive_recv(ctaphid_msg_t *msg) {
    printf("CTAPHID_KEEPALIVE");
    return -1;
}

static int ctaphid_cmd_error_recv(ctaphid_msg_t *msg) {
    printf("CTAPHID_ERROR");
    return -1;
}


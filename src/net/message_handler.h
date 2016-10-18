//
// Created by Leon on 18/10/2016.
//

#pragma once

#include "uv.h"
#include "buffer/buffer.h"

typedef struct {
    int message_id;
    void (*handler)(hh_buffer_t *, uv_stream_t *);
} hh_message_handler_t;

hh_message_handler_t *create_handler(int message_id, void (*handler)(hh_buffer_t *, uv_stream_t *));

const hh_message_handler_t *handlers[4001];

void load_message_handlers();

void handle_message(hh_buffer_t *buffer, uv_stream_t *handle);
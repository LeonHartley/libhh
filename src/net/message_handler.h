//
// Created by Leon on 18/10/2016.
//

#pragma once

#include <stdlib.h>
#include "uv.h"

typedef struct {
    int message_id;
    void (*handler)(char *, uv_stream_t *);
} hh_message_handler_t;

hh_message_handler_t *create_handler(int message_id, void (*handler)(char *, uv_stream_t *));

const hh_message_handler_t *handlers[4000];

void load_message_handlers();

void handle_message(char *buffer, uv_stream_t *handle);
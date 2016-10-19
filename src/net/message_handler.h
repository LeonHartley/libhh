//
// Created by Leon on 18/10/2016.
//

#pragma once

#include "uv.h"
#include "buffer/buffer.h"

void (*handlers[4001]);

void load_message_handlers();

void handle_message(hh_buffer_t *buffer, uv_stream_t *handle);
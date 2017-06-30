//
// Created by Leon on 18/10/2016.
//

#pragma once

#include "sessions/session.h"
#include "uv.h"
#include "buffer/buffer.h"

void hh_initialise_message_handler();

void handle_message(hh_buffer_t *buffer, hh_session_t *session);

void write_message(hh_buffer_t* message, hh_session_t *session);

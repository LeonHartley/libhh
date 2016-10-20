//
// Created by Leon on 18/10/2016.
//

#pragma once

#include <stdlib.h>
#include "uv.h"
#include "../buffer/buffer.h"
#include "../composers/handshake_composers.h"

void read_release_message_handler(hh_buffer_t *buffer, uv_stream_t *session);

void init_cryptography_message_handler(hh_buffer_t *buffer, uv_stream_t *session);

void read_unique_id_handler(hh_buffer_t *buffer, uv_stream_t *session);

void read_sso_ticket_handler(hh_buffer_t *buffer, uv_stream_t *session);
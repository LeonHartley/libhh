//
// Created by Leon on 18/10/2016.
//

#pragma once

#include <stdlib.h>

#include "../sessions/session.h"
#include "../buffer/buffer.h"

void read_release_message_handler(hh_buffer_t *buffer, hh_session_t *session);

void init_cryptography_message_handler(hh_buffer_t *buffer, hh_session_t *session);

void read_sso_ticket_handler(hh_buffer_t *buffer, hh_session_t *session);

void info_retrieve_handler(hh_buffer_t *buffer, hh_session_t *session);

void send_balance_handler(hh_buffer_t *buffer, hh_session_t *session);

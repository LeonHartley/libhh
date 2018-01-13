#pragma once

#include "../../buffer/buffer.h"
#include "../../sessions/session.h"

void get_user_categories_handler(hh_buffer_t *buffer, hh_session_t *session);

void official_rooms_handler(hh_buffer_t *buffer, hh_session_t *session);

void navigator_text_search_test(hh_buffer_t *buffer, hh_session_t *session);
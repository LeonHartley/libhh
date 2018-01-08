#pragma once

#include "../../sessions/session.h"
#include "../../buffer/buffer.h"

void catalog_index_handler(hh_buffer_t *buffer, hh_session_t *session);

void catalog_page_handler(hh_buffer_t *buffer, hh_session_t *session);
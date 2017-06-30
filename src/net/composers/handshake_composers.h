#pragma once

#include "../buffer/buffer.h"

hh_buffer_t *session_params_composer();

hh_buffer_t *authentication_ok_composer();

hh_buffer_t *motd_composer(char* text);
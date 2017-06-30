#pragma once 

#include "../buffer/buffer.h"
#include "../../players/player.h"

#include <uv.h>

typedef struct {
    uv_stream_t *client;
    hh_buffer_t *buffer;
    char *ip_address;
    hh_player_t *player;
} hh_session_t;

hh_session_t *hh_session_create(uv_stream_t *stream, char *ip_address);

void hh_session_dispose(hh_session_t *session);
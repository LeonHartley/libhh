#include "session.h"

#include <stdlib.h>

void hh_session_dispose(hh_session_t *session) {
    if(session->player != NULL) {
        hh_player_dispose(session->player);
    }

    free(session);
}

hh_session_t *hh_session_create(uv_stream_t *stream, char *ip_address) {
    hh_session_t *session = malloc(sizeof(hh_session_t));

    session->ip_address = ip_address;
    session->client = stream;

    return session;
}


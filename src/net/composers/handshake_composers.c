#include "handshake_composers.h"

hh_buffer_t *authentication_ok_composer() {
    hh_buffer_t *auth_ok = hh_buffer_create(6, ((char *) malloc(6)));

    hh_buffer_initialise(auth_ok);
    hh_buffer_write_short(1552, auth_ok);

    return auth_ok;
}

hh_buffer_t *motd_composer(char* text) {
    int msg_size = strlen(text) + 8;

    hh_buffer_t *motd = hh_buffer_create(msg_size, ((char *) malloc(msg_size)));

    hh_buffer_initialise(motd);

    hh_buffer_write_short(773, motd);
    hh_buffer_write_int(1, motd);
    hh_buffer_write_string(text, motd);

    return motd;
}
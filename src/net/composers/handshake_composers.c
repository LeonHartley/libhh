#include "handshake_composers.h"

#include "composers.h"

#include <stdlib.h>
#include <string.h>

const char *dd_mm_yy_str = "dd-MM-yyyy";
const char *client_url_str = "/client";

hh_buffer_t *session_params_composer() {
    hh_buffer_t *session_params = hh_buffer_create_empty();

    hh_buffer_initialise(session_params);
    hh_buffer_write_short(SessionParamsMessageComposer, session_params);    

    hh_buffer_write_int(9, session_params);
    hh_buffer_write_int(0, session_params);
    hh_buffer_write_int(1, session_params);
    hh_buffer_write_int(1, session_params);
    hh_buffer_write_int(3, session_params);
    hh_buffer_write_int(0, session_params);
    hh_buffer_write_int(2, session_params);
    hh_buffer_write_int(1, session_params);
    hh_buffer_write_int(4, session_params);
    hh_buffer_write_int(1, session_params);
    hh_buffer_write_int(5, session_params);
    hh_buffer_write_string(dd_mm_yy_str, session_params);
    hh_buffer_write_int(7, session_params);
    hh_buffer_write_byte((char) 0, session_params);
    hh_buffer_write_int(9, session_params);
    hh_buffer_write_string(client_url_str, session_params);
    hh_buffer_write_int(9, session_params);
    hh_buffer_write_byte((char) 0, session_params);

    return session_params;
}

hh_buffer_t *authentication_ok_composer() {
    hh_buffer_t *auth_ok = hh_buffer_create(6, ((char *) malloc(6)));

    hh_buffer_initialise(auth_ok);
    hh_buffer_write_short(AuthenticationOKMessageComposer, auth_ok);
    
    return auth_ok;
}

hh_buffer_t *motd_composer(char* text) {
    int msg_size = strlen(text) + 8;

    hh_buffer_t *motd = hh_buffer_create(msg_size, (char *) malloc(msg_size));

    hh_buffer_initialise(motd);

    hh_buffer_write_short(MotdNotificationMessageComposer, motd);
    hh_buffer_write_int(1, motd);
    hh_buffer_write_string(text, motd);

    return motd;
}
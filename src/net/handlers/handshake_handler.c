#include "handshake_handler.h"


void read_release_message_handler(hh_buffer_t *buffer, uv_stream_t *session) { 
    char *release_version = hh_buffer_read_string(buffer); 
 
    printf("reading release %s\n", release_version); 
    free(release_version); 
} 

void init_cryptography_message_handler(hh_buffer_t *buffer, uv_stream_t *session) {
     printf("initialising cryptography\n");
}

void read_unique_id_handler(hh_buffer_t *buffer, uv_stream_t *session) {
    short unused = hh_buffer_read_short(buffer);
    char *unique_id = hh_buffer_read_string(buffer);

    printf("unique id: %s\n", unique_id);
    
    free(unique_id);
}

void read_sso_ticket_handler(hh_buffer_t *buffer, uv_stream_t *session) {
    char* login_ticket = hh_buffer_read_string(buffer);

    // Find user with login ticket
    printf("recieved login ticket %s\n", login_ticket);

    write_message(authentication_ok_composer(), session);
    write_message(motd_composer("Hey there! :D"), session);

    free(login_ticket);
}
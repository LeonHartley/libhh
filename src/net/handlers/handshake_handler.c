#include "handshake_handler.h"

const char *motd_str = "welcome to the official libhh test server. this hotel is powered by libhh, a high performance lightweight emulator written in pure C.";

void read_release_message_handler(hh_buffer_t *buffer, hh_session_t *session) { 
    char *release_version = hh_buffer_read_string(buffer); 
 
    printf("reading release %s\n", release_version); 
    free(release_version); 
} 

void init_cryptography_message_handler(hh_buffer_t *buffer, hh_session_t *session) {
     printf("initialising cryptography\n");

     hh_write_message(session_params_composer(), session);
}

void read_sso_ticket_handler(hh_buffer_t *buffer, hh_session_t *session) {
    char* login_ticket = hh_buffer_read_string(buffer);

    // Find user with login ticket
    printf("recieved login ticket %s, length %i, ipaddress %s\n", login_ticket, strlen(login_ticket), session->ip_address);

    hh_write_message(authentication_ok_composer(), session);
    hh_write_message(motd_composer(motd_str), session);

    free(login_ticket);
}

void navigator_text_search_test(hh_buffer_t *buffer, hh_session_t *session) {
    char *search_str = hh_buffer_read_string(buffer);

    printf("search str %s, length %i\n", search_str, strlen(search_str));
    free(search_str);
}
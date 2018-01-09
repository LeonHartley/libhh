#include "handshake_handler.h"

#include "../../catalog/catalog.h"
#include "../composers/handshake_composers.h"
#include "../composers/player_composers.h"

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

    if(hh_player_auth(session, login_ticket)) {
        hh_write_message(authentication_ok_composer(), session);
        hh_write_message(motd_composer(motd_str), session);
    } else {
        // disconnect
    }

    free(login_ticket);
}

void info_retrieve_handler(hh_buffer_t *buffer, hh_session_t *session) {
    if(session->player == NULL) {
        return;
    }

    hh_write_message(user_object_composer(session->player->data), session);
}

void send_balance_handler(hh_buffer_t *buffer, hh_session_t *session) {
    if(session->player == NULL) {
        return;
    }

    hh_write_message(credit_balance_composer(session->player->data->credits), session);
}

void get_user_categories_handler(hh_buffer_t *buffer, hh_session_t *session) {
    if(session->player == NULL) {
        return;
    }

    hh_write_message(user_room_categories_composer(), session);
}

void navigator_text_search_test(hh_buffer_t *buffer, hh_session_t *session) {
    char *search_str = hh_buffer_read_string(buffer);

    printf("search str %s, length %i\n", search_str, strlen(search_str));
    free(search_str);
}
//
// Created by Leon on 18/10/2016.
//

#pragma once

#include <stdlib.h>
#include "uv.h"
#include "../buffer/buffer.h"

int read_release_message_handler(hh_buffer_t *buffer, uv_stream_t *session) {
    char *release_version = hh_buffer_read_string(buffer);

    printf("reading release %s\n", release_version);
    free(release_version);
}

//unused atm 
int init_cryptography_message_handler(hh_buffer_t *buffer, uv_stream_t *session) {
     printf("initialising cryptography\n");
}

int read_unique_id_handler(hh_buffer_t *buffer, uv_stream_t *session) {
    short unused = hh_buffer_read_short(buffer);
    char *unique_id = hh_buffer_read_string(buffer);

    printf("unique id: %s\n", unique_id);
    
    free(unique_id);
}

int read_sso_ticket_handler(hh_buffer_t *buffer, uv_stream_t *session) {
    char* login_ticket = hh_buffer_read_string(buffer);

    // Find user with login ticket
    printf("recieved login ticket %s\n", login_ticket);

    hh_buffer_t *motd_buffer = hh_buffer_create(1024, ((char *) malloc(1024)));

    hh_buffer_initialise(motd_buffer);

    hh_buffer_write_short(1244, motd_buffer); // motd header
    hh_buffer_write_int(1, motd_buffer);
    hh_buffer_write_string("hey there! :D", motd_buffer);

    write_message(motd_buffer, session);

    free(login_ticket);
}
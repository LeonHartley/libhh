//
// Created by Leon on 18/10/2016.
//

#include "message_handler.h"
#include "handlers/handshake_handler.h"
#include "server.h"

#include <stdlib.h>
#include <stdio.h>

void load_message_handlers() {
    handlers[4000] = &read_release_message_handler;
    handlers[3659] = &read_unique_id_handler;
    handlers[1490] = &read_sso_ticket_handler;
}

void handle_message(hh_buffer_t *buffer, uv_stream_t *handle) {
    short header_id = hh_buffer_read_short(buffer);

    if(handlers[header_id]) {
        printf("handling message with id %i\n", header_id);

        ((void (*)(hh_buffer_t *, uv_stream_t *)) handlers[header_id])(buffer, handle);
    } else {
        printf("unhandled message with id %i\n", header_id);
    }
}

void write_message(hh_buffer_t* message, uv_stream_t *session) {
    uv_write_t *req;
    if(!(req = malloc(sizeof(uv_write_t)))){
        return;                    
    }

    hh_buffer_prepare(message);

    uv_buf_t buffer = uv_buf_init(message->base, message->index + 4);

    req->handle = session;
    req->data = buffer.base;

    uv_write(req, session, &buffer, 1, hh_on_write);
}
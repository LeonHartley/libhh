//
// Created by Leon on 18/10/2016.
//

#include "message_handler.h"
#include "handlers/handshake_handler.h"
#include <stdlib.h>

hh_message_handler_t *create_handler(int message_id, void (*handler)(hh_buffer_t *, uv_stream_t *)) {
    hh_message_handler_t *msg = malloc(sizeof(hh_message_handler_t));

    msg->message_id = message_id;
    msg->handler = handler;

    return msg;
}

void load_message_handlers() {
    handlers[4000] = create_handler(4000, &read_release_message_handler);
    handlers[260] = create_handler(260, &read_release_message_handler);
}

void handle_message(hh_buffer_t *buffer, uv_stream_t *handle) {
    int header_id = hh_buffer_read_short(buffer);

    if(header_id == -96) {
        header_id = 4000;
    }

    if(handlers[header_id]) {
        handlers[header_id]->handler(buffer, handle);
    }
}
//
// Created by Leon on 18/10/2016.
//

#include "message_handler.h"

hh_message_handler_t *create_handler(int message_id, void (*handler)(char *, uv_stream_t *)) {
    hh_message_handler_t *msg = malloc(sizeof(hh_message_handler_t));

    msg->message_id = message_id;
    msg->handler = handler;

    return msg;
}

void load_message_handlers() {
    //handlers[0] = create_handler(0, &hello_message_handler);
}

void handle_message(char *buffer, uv_stream_t *handle) {
    handlers[0]->handler(buffer, handle);
}
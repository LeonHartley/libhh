//
// Created by Leon on 18/10/2016.
//

#include "events/events.h"
#include "message_handler.h"
#include "handlers/handshake_handler.h"
#include "handlers/catalog/catalog_handler.h"

#include "server.h"

#include <stdlib.h>
#include <stdio.h>

static void(*handlers[4001]) (hh_buffer_t *, hh_session_t *);

void hh_initialise_message_handler() {
    handlers[InitCryptoMessageEvent] = &init_cryptography_message_handler;
    handlers[SSOTicketMessageEvent] = &read_sso_ticket_handler;
    handlers[InfoRetrieveMessageEvent] = &info_retrieve_handler;
    handlers[CatalogIndexMessageEvent] = &catalog_index_handler;
    handlers[CatalogPageMessageEvent] = &catalog_page_handler;
    handlers[GetBalanceMessageEvent] = &send_balance_handler;
    handlers[GetUserCategoriesMessageEvent] = &get_user_categories_handler;
    handlers[RoomTextSearchMessageEvent] = &navigator_text_search_test;
}

void handle_message(hh_buffer_t *buffer, hh_session_t *session) {
    short header_id = hh_buffer_read_short(buffer);

    if(handlers[header_id]) {
        printf("handling message with id %i\n", header_id);

       handlers[header_id](buffer, session);
    } else {
        printf("unhandled message with id %i\n", header_id);
    }
}

void hh_write_message(hh_buffer_t* message, hh_session_t *session) {
    uv_write_t *req;
    if(!(req = malloc(sizeof(uv_write_t)))){
        return;                    
    }

    hh_buffer_prepare(message);

    int message_length = message->index + 4;

    uv_buf_t buffer = uv_buf_init(malloc(message_length), message_length);

    memcpy(buffer.base, message->base, message_length);

    req->handle = (void *)session;
    req->data = buffer.base;

    uv_write(req, session->client, &buffer, 1, &hh_on_write);

    hh_buffer_free(message);
}
#include "server.h"
#include "buffer/buffer.h"
#include "sessions/session.h"

#include <string.h>
#include <stdlib.h>

const char policy_file[208] = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";

void hh_alloc_buffer(uv_handle_t* handle, size_t  size, uv_buf_t* buf) {
    buf->base = malloc(size);
    buf->len = size;
}

void hh_on_connection_close(uv_handle_t *handle) {
    // on connection closed
    printf("[libhh] disposed a connection\n");
}

void hh_on_write(uv_write_t* req, int status) {
    printf("[libhh] write finished\n");

    free(req->data);
}

void hh_close_on_write(uv_write_t *req, int status) {
    //free(req->data);
    uv_close((uv_handle_t *) req->handle, hh_on_connection_close);
}

void hh_on_read(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf) {
    if(nread == UV_EOF) {
        uv_close((uv_handle_t *) handle, hh_on_connection_close);
        return;
    }

    if(nread > 0) {
        if(buf->base[0] == '<') {
            uv_write_t *req = malloc(sizeof(uv_write_t));

            uv_buf_t buffer = uv_buf_init(malloc(sizeof(policy_file)), sizeof(policy_file));

            buffer.base = policy_file;

            req->handle = handle;
            req->data = buffer.base;

            uv_write(req, handle, &buffer, 1, hh_close_on_write);
        } else {
            // here we want to create a buffer
            hh_buffer_t *buffer = hh_buffer_create(nread, buf->base);

            fprintf(stderr, "[libhh] buffer created with length: %i\n", buffer->length);

            int message_length = hh_buffer_read_int(buffer);
            
            handle_message(buffer, (hh_session_t *)handle->data);
            // hh_buffer_free(buffer);
        }
    } else {
        uv_close((uv_handle_t *) handle, hh_on_connection_close);
    }

    free(buf->base);
}

void hh_on_new_connection(uv_stream_t *server, int status) {
    printf("[libhh] accepted a connection\n");

    uv_tcp_t *client = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));

    uv_tcp_init(uv_default_loop(), client);

    struct sockaddr_in client_addr;    
    int client_addr_length;

    uv_tcp_getpeername((uv_stream_t *) client, &client_addr, &client_addr_length);
    char *ip = inet_ntoa(client_addr.sin_addr);

    hh_session_t *session = hh_session_create((uv_stream_t *) client, ip);

    client->data = session;

    int result = uv_accept(server, (uv_stream_t *) client);

    if(result == 0) {
        uv_read_start((uv_stream_t *) client, hh_alloc_buffer, hh_on_read);
    } else {
        // failed to accept client
    }
}

void hh_start_server(const char *ip, int port) {
    uv_loop_t *loop = uv_default_loop();

    uv_tcp_t server;
    struct sockaddr_in bind_addr;

    uv_tcp_init(loop, &server);
    uv_ip4_addr(ip, port, &bind_addr);
    uv_tcp_bind(&server, (const struct sockaddr *) &bind_addr, 0);
    uv_listen((uv_stream_t *) &server, 128, hh_on_new_connection);

    // At the moment, the entire server is single threaded but there are plans
    // to make the entire server multithreaded.

    int result = uv_run(loop, UV_RUN_DEFAULT);

    if(result) {
        // display errors to user.
    }

    uv_loop_close(loop);
}

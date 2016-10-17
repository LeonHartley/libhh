//
// Created by Leon on 17/10/2016.
//

#include "libhh.h"

void alloc_buffer(uv_handle_t* handle, size_t size, uv_buf_t* buf) {
    buf->base = malloc(size);
    buf->len = size;
}

void on_close(uv_handle_t *handle) {
    // on connection closed
    printf("disposed connection");
}

void on_read(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf) {
    if(nread == UV_EOF) {
        uv_close((uv_handle_t *) client, NULL);
        return;
    }

    if(nread >= 0) {
        if(buf->base[0] == '<') {
            printf("received policy request\n");
        } else {
            printf("received game message\n");
        }
    } else {
        uv_close((uv_handle_t *) handle, on_close);
    }

    free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status) {
    printf("accepted connection\n");

    uv_tcp_t *client = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));

    uv_tcp_init(uv_default_loop(), client);

    int result = uv_accept(server, (uv_stream_t *) client);

    if(result == 0) {
        uv_read_start((uv_stream_t *) client, alloc_buffer, on_read);
    } else {
        // failed to accept connection.
    }
}

int main(int argc, char *argv[]) {
    printf("[libhh] habbo emulation written in C\n");
    printf("[libhh] libuv version: %s\n", uv_version_string());
    printf("[libhh] initialising event loop with io on port %i\n", PORT);

    uv_loop_t *loop = uv_default_loop();

    uv_tcp_t server;
    struct sockaddr_in bind_addr;

    uv_tcp_init(loop, &server);
    uv_ip4_addr("0.0.0.0", 3000, &bind_addr);
    uv_tcp_bind(&server, (const struct sockaddr *) &bind_addr, 0);
    uv_listen((uv_stream_t *) &server, 128, on_new_connection);

    int result = uv_run(loop, UV_RUN_DEFAULT);

    if(result) {
        // display errors to user.
    }

    uv_loop_close(loop);

    return 0;
}
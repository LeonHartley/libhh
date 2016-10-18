#pragma once

#include "uv.h"

typedef struct {
  uv_write_t req;
  uv_buf_t buf;
} write_req_t;

void hh_alloc_buffer(uv_handle_t* handle, size_t size, uv_buf_t* buf);

void hh_on_connection_close(uv_handle_t *handle);

void hh_on_write(uv_write_t* req, int status);

void hh_on_read(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);

void hh_on_new_connection(uv_stream_t *server, int status);

void hh_start_server(char* ip, int port);
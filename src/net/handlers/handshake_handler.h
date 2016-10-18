//
// Created by Leon on 18/10/2016.
//

#pragma once

#include <stdlib.h>
#include "uv.h"
#include "../buffer/buffer.h"

void read_release_message_handler(hh_buffer_t *buffer, uv_stream_t *session) {
    char *release_version = hh_buffer_read_string(buffer);

    printf("handling release %s\n", release_version);
    free(release_version);
}
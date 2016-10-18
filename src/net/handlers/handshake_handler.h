//
// Created by Leon on 18/10/2016.
//

#pragma once

#include <stdlib.h>
#include "uv.h"

void hello_message_handler(char *message, uv_stream_t *session) {
    printf("handling hello message\n");
}
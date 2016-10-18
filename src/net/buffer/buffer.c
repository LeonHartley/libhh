//
// Created by Leon on 18/10/2016.
//

#include "buffer.h"
#include <stdlib.h>

hh_buffer_t *hh_buffer_create(int length, char *base) {
    hh_buffer_t *buffer = malloc(sizeof(hh_buffer_t));

    buffer->index = 0;
    buffer->length = length;
    buffer->base = base;

    return buffer;
}

void hh_buffer_free(hh_buffer_t *buffer) {
    free(buffer);
}
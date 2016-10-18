//
// Created by Leon on 18/10/2016.
//

#include "buffer.h"
#include <stdlib.h>
#include <stdio.h>

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

int hh_buffer_read_int(hh_buffer_t *buffer) {
    return (0xff & buffer->base[buffer->index++] << 24) |
        (0xff & buffer->base[buffer->index++] << 16) |
        (0xff & buffer->base[buffer->index++] << 8) | 
        (0xff & buffer->base[buffer->index++]);
}

short hh_buffer_read_short(hh_buffer_t *buffer) {
    return (0xff & buffer->base[buffer->index++]) << 8 |
        (0xff & buffer->base[buffer->index++] << 0);
}

// make sure we free the char*!!!!!!!
char *hh_buffer_read_string(hh_buffer_t *buffer) {
    short length = hh_buffer_read_short(buffer);
    char* string = malloc(length);

    for(int i = 0; i < length; i++) {
        string[i] = buffer->base[buffer->index++];
    }

    return string;
}
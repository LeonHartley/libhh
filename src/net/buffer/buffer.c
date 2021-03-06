//
// Created by Leon on 18/10/2016.
//

#include "buffer.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

hh_buffer_t *hh_buffer_create_empty() {
    hh_buffer_t *buffer = malloc(sizeof(hh_buffer_t));

    buffer->index = 0;
    buffer->length = 256;
    buffer->base = malloc(256);

    return buffer;
}

hh_buffer_t *hh_buffer_expand_if_required(hh_buffer_t *buffer, int req_bytes) {
    if(buffer->index + req_bytes >= buffer->length) {
        char *new_buf = malloc(buffer->length * 2);

        memcpy(new_buf, buffer->base, buffer->index);
        free(buffer->base);

        buffer->base = new_buf;
    }

    return buffer;
}

hh_buffer_t *hh_buffer_create(int length, char *base) {
    hh_buffer_t *buffer = malloc(sizeof(hh_buffer_t));

    buffer->index = 0;
    buffer->length = length;
    buffer->base = malloc(length);

    // copy the memory from the base buffer
    memcpy(buffer->base, base, length);

    return buffer;
}

void hh_buffer_initialise(hh_buffer_t *buffer) {
    buffer->index = 4;
}

void hh_buffer_prepare(hh_buffer_t *buffer) {
    hh_buffer_write_int_at(buffer->index, buffer, 0);
}

void hh_buffer_free(hh_buffer_t *buffer) {
    if(buffer == NULL) {
        return;
    }

   free(buffer->base);
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

char *hh_buffer_read_string(hh_buffer_t *buffer) {
    short length = hh_buffer_read_short(buffer);//banter
    char* string = malloc(length + 1);

    for(int i = 0; i < length; i++) {
        string[i] = buffer->base[buffer->index++];
    }

    string[length] = '\0';


    return string;
}

void hh_buffer_write_string(char* string, hh_buffer_t *buffer) {
    size_t length = strlen(string);

    buffer = hh_buffer_expand_if_required(buffer, 2 + length);

    hh_buffer_write_short(length, buffer);
    
    for(int i = 0; i < length; i++) {
        hh_buffer_write_byte(string[i], buffer);
    }
}

void hh_buffer_write_short(short s, hh_buffer_t *buffer) {
    buffer = hh_buffer_expand_if_required(buffer, 2);
    
    buffer->base[buffer->index++] = ((s >> 8) & 0xff);
    buffer->base[buffer->index++] = (s & 0xff);
}

void hh_buffer_write_int(int i, hh_buffer_t *buffer) {
    buffer = hh_buffer_expand_if_required(buffer, 4);

    buffer->base[buffer->index++] = ((i >> 24) & 0xff);
    buffer->base[buffer->index++] = ((i >> 16) & 0xff);
    buffer->base[buffer->index++] = ((i >> 8) & 0xff);
    buffer->base[buffer->index++] = (i & 0xff);
}

void hh_buffer_write_int_at(int i, hh_buffer_t *buffer, int start) {
    buffer = hh_buffer_expand_if_required(buffer, 4);

    buffer->base[start++] = ((i >> 24) & 0xff);
    buffer->base[start++] = ((i >> 16) & 0xff);
    buffer->base[start++] = ((i >> 8) & 0xff);
    buffer->base[start++] = (i & 0xff);
}

void hh_buffer_write_byte(char byte, hh_buffer_t *buffer) {
    buffer = hh_buffer_expand_if_required(buffer, 1);

    buffer->base[buffer->index++] = byte;
}
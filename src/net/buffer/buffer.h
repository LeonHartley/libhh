//
// Created by Leon on 18/10/2016.
//

#pragma once

typedef struct {
    int index;
    int length;
    char *base;
} hh_buffer_t;

hh_buffer_t *hh_buffer_create(int length, char *base);

void hh_buffer_free(hh_buffer_t *buffer);

int hh_buffer_read_int(hh_buffer_t *buffer);

short hh_buffer_read_short(hh_buffer_t *buffer);

char *hh_buffer_read_string(hh_buffer_t *buffer);
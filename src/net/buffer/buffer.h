//
// Created by Leon on 18/10/2016.
//

#pragma once

typedef struct {
    int *index;
    int *length;
    char *base;
} hh_buffer_t;

hh_buffer_t *hh_buffer_create(int length, char *base);

void hh_buffer_free(hh_buffer_t *buffer);
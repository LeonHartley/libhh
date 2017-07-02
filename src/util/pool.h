#pragma once

#include <stdlib.h>

// TODO: locks, timeouts etc.

typedef struct {
    int index;
    void *value;
} hh_pool_entry_t; 

typedef struct {
    hh_pool_entry_t **pool;
    int size;
    int concurrent;//1=use locks
    void *lock;
} hh_pool_t;

typedef void (*hh_pool_initialise_entry_cb) (hh_pool_entry_t *entry);

hh_pool_t *hh_pool_create(int size, int concurrent, hh_pool_initialise_entry_cb init_cb);

hh_pool_entry_t *hh_pool_take(hh_pool_t *pool);

void hh_pool_return(hh_pool_entry_t *entry, hh_pool_t *pool);
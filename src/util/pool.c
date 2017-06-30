#include "pool.h"

hh_pool_t *hh_pool_create(int size, int concurrent, hh_pool_initialise_entry_cb init_cb) {
    hh_pool_t *pool = malloc(sizeof(hh_pool_t));

    pool->pool = calloc(size, sizeof(hh_pool_entry_t));
    pool->concurrent = concurrent;
    pool->size = size;

    for(int i = 0; i < size; i++) {
        pool->pool[i] = malloc(sizeof(hh_pool_entry_t));
        pool->pool[i]->index = i;
        init_cb(pool->pool[i]);
    }

    return pool;
}

hh_pool_entry_t *hh_pool_take(hh_pool_t *pool) {
    hh_pool_entry_t *ret;
    
    for(int i = 0; i < pool->size; i++) {
        hh_pool_entry_t *entry = pool->pool[i];

        if(entry != NULL) {
            pool->pool[i] = NULL;
            ret = entry;
            break;
        }
    }

    return ret;
}

void hh_pool_return(hh_pool_entry_t *entry, hh_pool_t *pool) {
    pool->pool[entry->index] = entry;
}
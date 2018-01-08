#pragma once

#include <uv.h>

#define DICTIONARY_MAX_BUCKETS 64

typedef struct hh_dictionary_s {
    int total_items;

    int total_buckets;
    
    hh_dictionary_bucket_entry_t **entries;
    hh_dictionary_bucket_t **buckets;

    uv_rwlock_t *mutex;
} hh_dictionary_t;

typedef struct hh_dictionary_bucket_s {
    hh_dictionary_bucket_entry_t *entry;
} hh_dictionary_bucket_t;

typedef struct hh_dictionary_bucket_entry_s {
    int id;
    void *data;
    hh_dictionary_bucket_entry_t *next;
} hh_dictionary_bucket_entry_t;

hh_dictionary_t *hh_dictionary_create() {
    hh_dictionary_t *dict = malloc(sizeof(hh_dictionary_t));

    return dict;
}
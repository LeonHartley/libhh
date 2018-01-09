#pragma once

#include <uv.h>

#define DICTIONARY_MAX_BUCKETS 64

typedef struct hh_dictionary_s {
    int total_items;

    int total_buckets;
    
    hh_dictionary_bucket_entry_t *entries;
    hh_dictionary_bucket_t *buckets[DICTIONARY_MAX_BUCKETS];

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

hh_dictionary_t *hh_dictionary_create(int max_entries) {
    hh_dictionary_t *dict = malloc(sizeof(hh_dictionary_t));

    dict->entries = calloc(max_entries, sizeof(hh_dictionary_entry_t));
    dict->buckets = calloc(DICTIONARY_MAX_BUCKETS, sizeof(hh_dictionary_bucket_t));
        
    return dict;
}

void hh_dictionary_dispose(hh_dictionary_t *dict) {

}

void hh_dictionary_add(int id, void *data, hh_dictionary_t *dict) {

}

void hh_dictionary_remove(int id, hh_dictionary_t *dict) {

}
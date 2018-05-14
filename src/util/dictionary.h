#pragma once

#include <uv.h>

#define DICTIONARY_MAX_BUCKETS 64

typedef struct hh_dictionary_bucket_entry_s {
    int id;
    void *data;
    struct hh_dictionary_bucket_entry_s *previous;
    struct hh_dictionary_bucket_entry_s *next;
} hh_dictionary_bucket_entry_t;

typedef struct hh_dictionary_bucket_s {
    hh_dictionary_bucket_entry_t *entry;
} hh_dictionary_bucket_t;

typedef struct hh_dictionary_s {
    hh_dictionary_bucket_t **buckets;

    uv_rwlock_t *mutex;
} hh_dictionary_t;

hh_dictionary_t *hh_dictionary_create(int max_entries) {
    hh_dictionary_t *dict = malloc(sizeof(hh_dictionary_t));

    dict->buckets = calloc(DICTIONARY_MAX_BUCKETS, sizeof(hh_dictionary_bucket_t));
    dict->mutex = malloc(sizeof(uv_rwlock_t));

    uv_rwlock_init(dict->mutex);

    return dict;
}

void hh_dictionary_dispose(hh_dictionary_t *dict) {

}

void hh_dictionary_add(int id, void *data, hh_dictionary_t *dict) {
    uv_rwlock_wrlock(dict->mutex);

    if(dict->buckets[id % DICTIONARY_MAX_BUCKETS] == NULL) {
        dict->buckets[id % DICTIONARY_MAX_BUCKETS] = malloc(sizeof(hh_dictionary_bucket_t));
    }

    hh_dictionary_bucket_t *bucket = dict->buckets[id % DICTIONARY_MAX_BUCKETS];
    hh_dictionary_bucket_entry_t *entry = bucket->entry;

    while(entry->next != NULL) {
        entry = entry->next;
    }

    entry->next = malloc(sizeof(hh_dictionary_bucket_entry_t));
    entry->next->id = id;
    entry->next->data = data;
    entry->next->previous = entry;

    uv_rwlock_wrunlock(dict->mutex);
}

void *hh_dictionary_get(int id, hh_dictionary_t *dict) {
    uv_rwlock_rdlock(dict->mutex);

    hh_dictionary_bucket_t *bucket = dict->buckets[id % DICTIONARY_MAX_BUCKETS];

    if(bucket == NULL) {
        uv_rwlock_rdunlock(dict->mutex);
        return NULL;
    }

    hh_dictionary_bucket_entry_t *entry = bucket->entry;

    while(entry->next != NULL) {
        entry = entry->next;

        if(entry->id == id) {
            uv_rwlock_rdunlock(dict->mutex);
            return entry->data;
        }
    }

    uv_rwlock_rdunlock(dict->mutex);
    return NULL;
}

void *hh_dictionary_remove(int id, hh_dictionary_t *dict) {
    uv_rwlock_wrlock(dict->mutex);

    hh_dictionary_bucket_t *bucket = dict->buckets[id % DICTIONARY_MAX_BUCKETS];

    if(bucket == NULL) {
        uv_rwlock_rdunlock(dict->mutex);
        return NULL;
    }

    hh_dictionary_bucket_entry_t *entry = bucket->entry;

    while(entry->next != NULL) {
        if(entry->next->id == id) {
            hh_dictionary_bucket_entry_t *remove = entry->next;

            entry->next = remove->next;

            free(remove);
            uv_rwlock_wrunlock(dict->mutex);
            return remove->data;
        }

        entry = entry->next;
    }

    uv_rwlock_wrunlock(dict->mutex);
    return NULL;
}
#pragma once

#include <uv.h>
#include <dispatch/dispatch.h>

#define DICTIONARY_MAX_BUCKETS 128

typedef void (*hh_dictionary_cb_t)(int id, void *data, void *ctx);

typedef struct hh_dictionary_bucket_entry_s {
    int id;
    void *data;
    struct hh_dictionary_bucket_entry_s *next;
    void *ctx;
} hh_dictionary_bucket_entry_t;

typedef struct hh_dictionary_bucket_s {
    hh_dictionary_bucket_entry_t *entry;
} hh_dictionary_bucket_t;

typedef struct hh_dictionary_s {
    hh_dictionary_bucket_t **buckets;

    int size;
    uv_rwlock_t *mutex;
} hh_dictionary_t;

typedef struct hh_dictionary_iter_ctx_s {
    int id;
    void *data;
    char dispatch_group;
    hh_dictionary_cb_t cb;
} hh_dictionary_iter_ctx_t;

hh_dictionary_t *hh_dictionary_create() {
    hh_dictionary_t *dict = malloc(sizeof(hh_dictionary_t));

    dict->size = 0;
    dict->buckets = calloc(DICTIONARY_MAX_BUCKETS, sizeof(hh_dictionary_bucket_t));
    dict->mutex = malloc(sizeof(uv_rwlock_t));

    uv_rwlock_init(dict->mutex);

    return dict;
}

void hh_dictionary_dispose(hh_dictionary_t *dict) {

}

void hh_dictionary_add(int id, void *data, hh_dictionary_t *dict) {
    uv_rwlock_wrlock(dict->mutex);

    if (dict->buckets[id % DICTIONARY_MAX_BUCKETS] == NULL) {
        dict->buckets[id % DICTIONARY_MAX_BUCKETS] = malloc(sizeof(hh_dictionary_bucket_t));
        dict->buckets[id % DICTIONARY_MAX_BUCKETS]->entry = NULL;
    }

    hh_dictionary_bucket_t *bucket = dict->buckets[id % DICTIONARY_MAX_BUCKETS];
    hh_dictionary_bucket_entry_t *new_entry = malloc(sizeof(hh_dictionary_bucket_entry_t));

    new_entry->id = id;
    new_entry->data = data;
    new_entry->next = NULL;

    if (bucket->entry == NULL || bucket->entry->id == 0) {
        dict->size++;
        bucket->entry = new_entry;
    } else {
        hh_dictionary_bucket_entry_t *entry = bucket->entry;

        while (entry->next != NULL) {
            entry = entry->next;
        }
        dict->size++;
        entry->next = new_entry;
    }

    uv_rwlock_wrunlock(dict->mutex);
}

void *hh_dictionary_get(int id, hh_dictionary_t *dict) {
    uv_rwlock_rdlock(dict->mutex);

    hh_dictionary_bucket_t *bucket = dict->buckets[id % DICTIONARY_MAX_BUCKETS];

    if (bucket == NULL) {
        uv_rwlock_rdunlock(dict->mutex);
        return NULL;
    }

    hh_dictionary_bucket_entry_t *entry = bucket->entry;

    if (entry->id == id) {
        uv_rwlock_rdunlock(dict->mutex);

        return entry->data;
    }

    while (entry->next != NULL) {
        entry = entry->next;

        if (entry->id == id) {
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

    if (bucket == NULL) {
        uv_rwlock_wrunlock(dict->mutex);
        return NULL;
    }

    hh_dictionary_bucket_entry_t *entry = bucket->entry;

    while (entry->next != NULL) {
        if (entry->next->id == id) {
            hh_dictionary_bucket_entry_t *remove = entry->next;

            entry->next = remove->next;
            void *data = remove->data;

            free(remove);

            dict->size--;

            uv_rwlock_wrunlock(dict->mutex);
            return data;
        }

        entry = entry->next;
    }

    uv_rwlock_wrunlock(dict->mutex);
    return NULL;
}

void exec_callback(hh_dictionary_iter_ctx_t *ctx) {
    ctx->cb(ctx->id, ctx->data, NULL);

    free(ctx);
}

void init_callback(int id, void *data, void *ctx) {
    hh_dictionary_iter_ctx_t *iter = malloc(sizeof(hh_dictionary_iter_ctx_t));

    memcpy(iter, ctx, sizeof(hh_dictionary_iter_ctx_t));
    iter->id = id;
    iter->data = data;

    hh_dispatch(iter->dispatch_group, (hh_dispatch_cb_t) &exec_callback, iter);
}

void hh_dictionary_iterate(hh_dictionary_cb_t cb, void *ctx, hh_dictionary_t *dict) {
    uv_rwlock_rdlock(dict->mutex);

    for (int d = 0; d < DICTIONARY_MAX_BUCKETS; d++) {
        if (dict->buckets[d] != NULL) {
            hh_dictionary_bucket_entry_t *entry = dict->buckets[d]->entry;

            while (entry != NULL) {
                cb(entry->id, entry->data, ctx);

                entry = entry->next;
            }
        }
    }

    uv_rwlock_rdunlock(dict->mutex);
}

void hh_dictionary_iterate_async(hh_dictionary_cb_t cb, char dispatch_group, hh_dictionary_t *dict) {
    hh_dictionary_iter_ctx_t *ctx = malloc(sizeof(hh_dictionary_iter_ctx_t));

    ctx->cb = cb;
    ctx->dispatch_group = dispatch_group;

    printf("ctx id %i %s %i %i\n", ctx->id, (char *) ctx->data, (int) ctx->cb, (int) ctx);
    hh_dictionary_iterate(&init_callback, ctx, dict);
    free(ctx);
}

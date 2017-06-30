#pragma once

/**
 *  @Author Leon Hartley
 *
 *  This is my first attempt at creating a simple hashtable in C.
 *  The principal here is create a hash from the key that can be 
 *  used as an index in the **table.
 *  
 *  If that index is used, it will use the next available one.
 *
 *  When searching, it will find the index via hashing the key
 *  and then searching through 
 *
 */

#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define HH_HASHTABLE_OK 0
#define HH_HASHTABLE_KEY_TAKEN -1

struct hh_hashtable_entry_s {
    char *key;
    char *value;
    struct hh_hashtable_entry_s *next;
};

typedef struct hh_hashtable_entry_s hh_hashtable_entry_t;

typedef struct {
    int size;
    int stored;
    hh_hashtable_entry_t **store;
} hh_hashtable_t;

hh_hashtable_t *hh_hashtable_create(int size) {
    hh_hashtable_t *table = malloc(sizeof(hh_hashtable_t));

    table->store = malloc(sizeof(hh_hashtable_entry_t *) * size);
    table->size = size;

    return table;
}

void hh_hashtable_free(hh_hashtable_t *hashtable) {
    free(hashtable->store);
    free(hashtable);
}

hh_hashtable_t *hh_hashtable_expand_if_required(hh_hashtable_t *table) {
    if(table->stored >= table->size) {
        int new_size = table->size * 2;
        hh_hashtable_t *new_table = hh_hashtable_create(new_size);

        new_table->store = malloc(sizeof(hh_hashtable_entry_t *) * new_size);
        new_table->size = new_size;

        memcpy(new_table->store, table->store, new_size);
        hh_hashtable_free(table);
    }


    return table;
}

int hh_hashtable_put(char *key, void *value, hh_hashtable_t *table) {
    // in this particular implementation of a hashtable, we dont want to allow the user to  
    // replace values. we will return -1 if this is taken.
    if(hh_hashtable_get_index(key, table) != -1) {
        return HH_HASHTABLE_KEY_TAKEN;
    }

    int index = hh_hashtable_hash(key, table);

    table = hh_hashtable_expand_if_required(table);

    // put it!
    table->stored = table->stored + 1;

    char *entry_key = strdup(key);
    
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;
	next = hashtable->table[index];

	while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
		last = next;
		next = next->next;
	}

	/* There's already a pair.  Let's replace that string. */
	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

		free( next->value );
		next->value = strdup( value );

	/* Nope, could't find it.  Time to grow a pair. */
	} else {
		newpair = ht_newpair( key, value );

		/* We're at the start of the linked list in this bin. */
		if( next == hashtable->table[index] ) {
			newpair->next = next;
			hashtable->table[ bin ] = newpair;
	
		/* We're at the end of the linked list in this bin. */
		} else if ( next == NULL ) {
			last->next = newpair;
	
		/* We're in the middle of the list. */
		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}


    //table->store[index]->value = value;
   /* hh_hashtable_entry_t *entry = table->store[index];
    entry->
*/
    return HH_HASHTABLE_OK;
}

int hh_hashtable_get_index(char *key, hh_hashtable_t *table) {
    hh_hashtable_entry_t *entry;

    // index is basically a hint as to where to start, it wont always give you the
    // correct index straight off the bat.
    int index = hh_hashtable_hash(key);

    entry = table->store[index];

    while(entry != NULL && entry->key != NULL && strcmp(key, entry->key) > 0) {
        index++;
        entry = entry->next;
    }

    if(entry == NULL || entry->key == NULL, strcmp(key, entry->key) != 0) {
        return -1;
    } else {
        return index;
    }
}

void *hh_hashtable_get(char *key, hh_hashtable_t *table) {
    int index = hh_hashtable_get_index(key, table);

    if(index < 0) {
        return NULL;
    }

    return table->store[index];
}

void *hh_hashtable_remove(char *key, hh_hashtable_t *table) {
     int index = hh_hashtable_get_index(key, table);

    if(index < 0) {
        return NULL;
    }

    hh_hashtable_entry_t *entry = table->store[index];

    if(entry->next != NULL) {
        free(entry->key);// we allocated the key, we delete it.

        void *value = entry->value;

        entry->value = NULL;
        entry->next = NULL;

        return value;
    } 
}

int hh_hashtable_hash(char *key, hh_hashtable_t *table) {
    unsigned long int value;
    int i = 0;

    while(value < ULONG_MAX && i < strlen(key) ) {
        value = value << 8;
        value += key[i];
        i++;
    }

    return value % table->size;
}
#include "navigator.h"

#include "storage/storage.h"

#include <stdlib.h>
#include <uv.h>

uv_rwlock_t nav_mutex;
hh_navigator_state_t nav_state;

void hh_navigator_initialise() {    
    hh_navigator_mutex_write_lock();

    for(int i = 0; i < nav_state.loaded_categories; i++) {
        hh_navigator_free_category(nav_state.categories[i]);
    }

    for(int i = 0; i < nav_state.loaded_featured; i++) {
        hh_navigator_free_featured(nav_state.featured[i]);
    }

    nav_state.loaded_categories = 0;
    nav_state.loaded_featured = 0;

    if(nav_state.categories == NULL) {
        nav_state.categories = calloc(MAX_NAVIGATOR_CATEGORIES, sizeof(hh_navigator_category_t));
    }

    if(nav_state.featured == NULL) {
        nav_state.featured = calloc(MAX_NAVIGATOR_FEATURED, sizeof(hh_navigator_featured_t));
    }

    hh_navigator_dao->load_categories();
    hh_navigator_dao->load_featured();

    printf("[libhh] Loaded %i navigator categories, %i featured rooms\n", nav_state.loaded_categories, nav_state.loaded_featured);

    hh_navigator_mutex_write_unlock();
}

hh_navigator_state_t *hh_navigator_state() {
    return &nav_state;
}

void hh_navigator_add_category(int id, char *name, int min_rank) {
    hh_navigator_category_t *category = malloc(sizeof(hh_navigator_category_t));

    category->id = id;
    category->name = strdup(name);
    category->min_rank = min_rank;

    nav_state.categories[nav_state.loaded_categories++] = category;
}

void hh_navigator_add_featured(int id, int banner_type, char *caption, char *image,
     int image_type, int room_id, int category_id, int category_parent_id) {
    hh_navigator_featured_t *featured = malloc(sizeof(hh_navigator_featured_t));

    featured->id = id;
    featured->banner_type = banner_type;
    featured->caption = strdup(caption);
    featured->image = strdup(image);
    featured->image_type = image_type;
    featured->room_id = room_id;
    featured->category_id = category_id;
    featured->category_parent_id;
    
    nav_state.featured[nav_state.loaded_featured++] = featured;
}

void hh_navigator_free_category(hh_navigator_category_t *category) {
    free(category->name);

    free(category);
}    
    
void hh_navigator_free_featured(hh_navigator_featured_t *featured) {
    free(featured->caption);
    free(featured->image);

    free(featured);
}    

void hh_navigator_mutex_init() {
    uv_rwlock_init(&nav_mutex);
}

void hh_navigator_mutex_read_lock() {
    uv_rwlock_rdlock(&nav_mutex);
}

void hh_navigator_mutex_read_unlock() {
    uv_rwlock_rdunlock(&nav_mutex);
}

void hh_navigator_mutex_write_lock() {
    uv_rwlock_wrlock(&nav_mutex);
}

void hh_navigator_mutex_write_unlock() {
    uv_rwlock_wrunlock(&nav_mutex);
}
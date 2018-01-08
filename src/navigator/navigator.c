#include "navigator.h"

#include <uv.h>

uv_rwlock_t nav_mutex;
hh_navigator_state_t nav_state;

void hh_navigator_initialise() {    
    for(int i = 0; i < nav_state.loaded_categories; i++) {
        free)
    }

    for(int i = 0; i < nav_state.loaded_featured; i++) {

    }

    nav_state.
}

void hh_navigator_add_category(int id, char *name, int min_rank) {

}

void hh_navigator_add_featured(int id, int banner_type, char *caption, char *image,
     int image_type, int room_id, int category_id, int category_parent_id) {

}

void hh_navigator_free_category(hh_navigator_category_t *category) {
    
}    
    
void hh_navigator_free_category(hh_navigator_category_t *category) {
        
}    

void hh_navigator_mutex_init() {
    uv_rwlock_init(&nav_mutex);
}

void hh_navigator_mutex_read_lock() {
       
}
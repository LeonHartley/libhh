#pragma once 

#define MAX_NAVIGATOR_CATEGORIES 24
#define MAX_NAVIGATOR_FEATURED 64

typedef struct hh_navigator_category_s {
    int id;
    char *name;
    int min_rank;
} hh_navigator_category_t;

typedef struct hh_navigator_featured_s {
    int id;
    int banner_type;
    char *caption;
    char *image;
    int image_type;
    int room_id;
    int category_id;
    int category_parent_id;
} hh_navigator_featured_t;

typedef struct hh_navigator_state_s {
    int loaded_categories;
    int loaded_featured;

    hh_navigator_featured_t **featured;
    hh_navigator_category_t **categories;

} hh_navigator_state_t;

void hh_navigator_initialise();

hh_navigator_state_t *hh_navigator_state();

void hh_navigator_add_category(int id, char *name, int min_rank);

void hh_navigator_add_featured(int id, int banner_type, char *caption, char *image,
     int image_type, int room_id, int category_id, int category_parent_id);

void hh_navigator_free_category(hh_navigator_category_t *category);

void hh_navigator_free_featured(hh_navigator_featured_t *featured);

void hh_navigator_mutex_init();

void hh_navigator_mutex_read_lock();

void hh_navigator_mutex_read_unlock();

void hh_navigator_mutex_write_lock();

void hh_navigator_mutex_write_unlock();
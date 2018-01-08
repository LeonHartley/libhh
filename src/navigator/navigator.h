#pragma once 

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

} hh_navigator_state_t;

void hh_navigator_initialise();

void hh_navigator_add_category(int id, char *name, int min_rank);

void hh_navigator_add_featured(int id, int banner_type, char *caption, char *image,
     int image_type, int room_id, int category_id, int category_parent_id);
#pragma once

#define MAX_CATALOG_PAGES 200
#define MAX_CATALOG_ITEMS 2048
#define MAX_CATALOG_ITEMS_PER_PAGE 128

typedef struct hh_catalog_item_s {
    int id;
    int page_id;
    char *code;
    int item_def_id;
    int amount;

    int price_credits;
    int price_activity_points;
    int price_vip_points;
} hh_catalog_item_t;

typedef struct hh_catalog_page_s { 
    int id;
    int parent_id;
    char *name;
    int min_rank;

    int enabled;
    int is_category;

    int icon_colour;
    int icon_img;

    char *layout;
    char *headline_img;
    char *teaser_img;
    char *special_img;
    char *text_1;
    char *text_2;
    char *details;
    char *teaser_txt;

    int total_items;
    hh_catalog_item_t **items;
} hh_catalog_page_t; 

typedef struct hh_catalog_state_s {
    int loaded_items;
    int loaded_pages;
    hh_catalog_page_t **pages;
    hh_catalog_item_t **items;
} hh_catalog_state_t;

void hh_catalog_initialise();

hh_catalog_state_t *hh_catalog_state();

hh_catalog_page_t *hh_catalog_find_page(int id);

void hh_catalog_add_page(int id, int parent_id, char *name, int min_rank, int enabled, int is_category, int icon_colour, int icon_img, char *layout, char *headline_img, char *teaser_img, char *special_img, char *text_1, char *text_2, char *details, char *teaser_txt);

void hh_catalog_add_item(int id, int page_id, char *code, int item_def_id, int amount, int price_credits, int price_activity_points, int price_vip_points);

void hh_catalog_free_item(hh_catalog_item_t *item);

void hh_catalog_mutex_init();
void hh_catalog_mutex_read_lock();
void hh_catalog_mutex_read_unlock();
void hh_catalog_mutex_write_lock();
void hh_catalog_mutex_write_unlock();
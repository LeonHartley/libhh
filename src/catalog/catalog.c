#include "catalog.h"

#include "../storage/storage.h"

#include <stdlib.h>
#include <uv.h>

uv_rwlock_t catalog_mutex;
hh_catalog_state_t catalog_state;

void hh_catalog_initialise() {
    hh_catalog_mutex_write_lock();

    for(int i = 0; i < catalog_state.loaded_items; i++) {
        hh_catalog_free_item(catalog_state.items[i]);
    }

    for(int i = 0; i < catalog_state.loaded_pages; i++) {
        hh_catalog_free_page(catalog_state.pages[i]);
    }

    catalog_state.loaded_items = 0;
    catalog_state.loaded_pages = 0;

    if(catalog_state.pages == NULL) {
        catalog_state.pages = calloc(MAX_CATALOG_PAGES, sizeof(hh_catalog_page_t));
    }

    if(catalog_state.items == NULL) {
        catalog_state.items = calloc(MAX_CATALOG_ITEMS, sizeof(hh_catalog_item_t));
    }

    hh_catalog_dao->load_pages();
    hh_catalog_dao->load_items();

    hh_catalog_mutex_write_unlock();

    printf("[libhh] Loaded %i catalog pages, %i catalog items\n", catalog_state.loaded_pages, catalog_state.loaded_items);
}
 
hh_catalog_state_t *hh_catalog_state() {
    return &catalog_state;
}

void hh_catalog_add_page(int id, int parent_id, char *name, int min_rank, int enabled, int is_category,
        int icon_colour, int icon_img, char *layout, char *headline_img, char *teaser_img, 
        char *special_img, char *text_1, char *text_2, char *details, char *teaser_txt) {
    
    hh_catalog_page_t *page = malloc(sizeof(hh_catalog_page_t));
    
    page->id = id;
    page->parent_id = parent_id;
    page->name = strdup(name);
    page->min_rank = min_rank;
    page->enabled = enabled;
    page->is_category = is_category;
    page->icon_colour = icon_colour;
    page->icon_img = icon_img;
    page->layout = strdup(layout);
    page->headline_img = strdup(headline_img);
    page->teaser_img = strdup(teaser_img);
    page->special_img = strdup(special_img);
    page->text_1 = strdup(text_1);
    page->text_2 = strdup(text_2);
    page->details = strdup(details);
    page->teaser_txt = strdup(teaser_txt);

    page->total_items = 0;
    page->items = NULL;

    catalog_state.pages[catalog_state.loaded_pages++] = page;
}

void hh_catalog_add_item(int id, int page_id, char *code, int item_def_id,
     int amount, int price_credits, int price_activity_points, int price_vip_points) {
         
    hh_catalog_item_t *item = malloc(sizeof(hh_catalog_item_t));

    item->id = id;
    item->page_id = page_id;
    item->code = strdup(code);
    item->item_def_id = item_def_id;
    item->amount = amount;
    item->price_credits = price_credits;
    item->price_activity_points = price_activity_points;
    item->price_vip_points = price_vip_points;

    hh_catalog_page_t *page = hh_catalog_find_page(page_id);

    if(page != NULL) {
        if(page->items == NULL) {
            page->items = calloc(MAX_CATALOG_ITEMS_PER_PAGE, sizeof(hh_catalog_item_t));
        }

        page->items[page->total_items++] = item;
    }

    catalog_state.items[catalog_state.loaded_items++] = item;
}

hh_catalog_page_t *hh_catalog_find_page(int id) {
    for(int i = 0; i < catalog_state.loaded_pages; i++) {
        if(catalog_state.pages[i]->id == id) {
            return catalog_state.pages[i];
        }
    }

    return NULL;
}

void hh_catalog_free_item(hh_catalog_item_t *item) {
    free(item->code);

    free(item);
}

void hh_catalog_free_page(hh_catalog_page_t *page) {
    free(page->name);
    free(page->layout);
    free(page->headline_img);
    free(page->teaser_img);
    free(page->special_img);
    free(page->text_1);
    free(page->text_2);
    free(page->details);
    free(page->teaser_txt);

    free(page->items);

    free(page);
}

void hh_catalog_mutex_init() {
    uv_rwlock_init(&catalog_mutex);
}

void hh_catalog_mutex_read_lock() {
    uv_rwlock_rdlock(&catalog_mutex);
}

void hh_catalog_mutex_read_unlock() {
    uv_rwlock_rdunlock(&catalog_mutex);
}

void hh_catalog_mutex_write_lock() {
    uv_rwlock_wrlock(&catalog_mutex);
}

void hh_catalog_mutex_write_unlock() {
    uv_rwlock_wrunlock(&catalog_mutex);
}
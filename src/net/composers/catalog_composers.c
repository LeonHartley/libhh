#include "catalog_composers.h"

#include "composers.h"

hh_buffer_t *catalog_index_composer(int total_pages, hh_catalog_page_t **pages, int player_rank) {
    hh_buffer_t *catalog_index = hh_buffer_create_empty();
    
    hh_buffer_initialise(catalog_index);
    hh_buffer_write_short(CatalogIndexMessageComposer, catalog_index);    

    hh_buffer_write_byte(1, catalog_index);
    hh_buffer_write_int(0, catalog_index);
    hh_buffer_write_int(0, catalog_index);
    hh_buffer_write_int(-1, catalog_index);
    
    hh_buffer_write_short(0, catalog_index);//empty string

    int count = 0;
    hh_catalog_page_t *page;

    for(int i = 0; i < total_pages; i++) {
        page = pages[i];
        
        if(page->parent_id == -1 && page->min_rank <= player_rank) {
            count++;
        }
    }

    hh_buffer_write_int(count, catalog_index);

    for(int i = 0; i < total_pages; i++) {
        page = pages[i];
        
        if(page->parent_id == -1 && page->min_rank <= player_rank) {
            catalog_write_page_meta(page, catalog_index);

            count = 0;

            for(int j = 0; j < total_pages; j++) {
                if(pages[j]->parent_id == page->id && pages[j]->min_rank <= player_rank) {
                    count++;
                }
            }

            hh_buffer_write_int(count, catalog_index);// tree

            for(int j = 0; j < total_pages; j++) {
                if(pages[j]->parent_id == page->id && pages[j]->min_rank <= player_rank) {
                    catalog_write_page_meta(pages[j], catalog_index);
                    hh_buffer_write_int(0, catalog_index);//children
                }
            }            
        }
    }

    return catalog_index;
}

hh_buffer_t *catalog_page_composer(hh_catalog_page_t *page) {
    hh_buffer_t *catalog_page = hh_buffer_create_empty();
    
    hh_buffer_initialise(catalog_page);
    hh_buffer_write_short(CatalogPageMessageComposer, catalog_page);

    hh_buffer_write_int(page->id, catalog_page);
    hh_buffer_write_string(page->layout, catalog_page);
    
    hh_buffer_write_int(3, catalog_page);
    hh_buffer_write_string(page->headline_img, catalog_page);
    hh_buffer_write_string(page->teaser_img, catalog_page);
    hh_buffer_write_string(page->special_img, catalog_page);

    hh_buffer_write_int(4, catalog_page);
    hh_buffer_write_string(page->text_1, catalog_page);
    hh_buffer_write_string(page->text_2, catalog_page);
    hh_buffer_write_string(page->details, catalog_page);
    hh_buffer_write_string(page->teaser_txt, catalog_page);
    
    hh_buffer_write_int(page->total_items, catalog_page); // items count

    for(int i = 0; i < page->total_items; i++) {
        hh_catalog_item_t *item = page->items[i];

        hh_buffer_write_int(item->id, catalog_page); 
        hh_buffer_write_string(item->code, catalog_page);

        hh_buffer_write_int(item->price_credits, catalog_page);       
        hh_buffer_write_int(item->price_activity_points, catalog_page);
        hh_buffer_write_int(item->price_vip_points, catalog_page);

        hh_buffer_write_int(1, catalog_page);//?? item count (for deals etc)
        hh_buffer_write_string("s", catalog_page);// change this when ive done item definitions
        hh_buffer_write_int(item->item_def_id, catalog_page);
        hh_buffer_write_string("", catalog_page);
        hh_buffer_write_int(item->amount, catalog_page);
        hh_buffer_write_int(-1, catalog_page);
        hh_buffer_write_int(0, catalog_page);//club restriction?
    }

    hh_buffer_write_int(-1, catalog_page);

    return catalog_page;
}

void catalog_write_page_meta(hh_catalog_page_t *page, hh_buffer_t *catalog_index) {
    hh_buffer_write_byte(1, catalog_index);
    hh_buffer_write_int(page->icon_colour, catalog_index);
    hh_buffer_write_int(page->icon_img, catalog_index);
    hh_buffer_write_int(page->id, catalog_index);
    hh_buffer_write_string(page->name, catalog_index);
}

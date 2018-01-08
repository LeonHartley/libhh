#include "catalog_handler.h"

#include "../../../catalog/catalog.h"
#include "../../composers/catalog_composers.h"

void catalog_index_handler(hh_buffer_t *buffer, hh_session_t *session) {
    if(session->player == NULL) {
        return;
    }
    
    hh_catalog_state_t *catalog_state = hh_catalog_state();

    // Moved this to the credit balance event temporarily..
    //hh_write_message(catalog_index_composer(catalog_state->loaded_pages, catalog_state->pages, session->player->data->rank), session);
}

void catalog_page_handler(hh_buffer_t *buffer, hh_session_t *session) {
    if(session->player == NULL) {
        return;
    }

    int page_id = hh_buffer_read_int(buffer);

    hh_catalog_state_t *catalog_state = hh_catalog_state();

    hh_catalog_page_t *page = NULL;

    for(int i = 0; i < catalog_state->loaded_pages; i++) {
        if(catalog_state->pages[i]->id == page_id) {
            page = catalog_state->pages[i];
        }
    }

    if(page != NULL) {
        hh_write_message(catalog_page_composer(page), session);
    }
}
#include "catalog_handler.h"

#include "../../../catalog/catalog.h"
#include "../../composers/catalog_composers.h"

void catalog_index_handler(hh_buffer_t *buffer, hh_session_t *session) {
    if(session->player == NULL) {
        return;
    }

    // Moved this to the credit balance event temporarily..
    //hh_catalog_state_t *catalog_state = hh_catalog_state();

    //hh_write_message(catalog_index_composer(catalog_state->loaded_pages, catalog_state->pages, session->player->data->rank), session);
}

void catalog_page_handler(hh_buffer_t *buffer, hh_session_t *session) {
    if(session->player == NULL) {
        return;
    }

    int page_id = hh_buffer_read_int(buffer);

    hh_catalog_mutex_read_lock();

    hh_catalog_state_t *catalog_state = hh_catalog_state();

    hh_catalog_page_t *page = hh_catalog_find_page(page_id);

    if(page != NULL) {
        hh_write_message(catalog_page_composer(page), session);
    }

    hh_catalog_mutex_read_unlock();
}
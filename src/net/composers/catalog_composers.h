#pragma once

#include "../buffer/buffer.h"
#include "../../catalog/catalog.h"

hh_buffer_t *catalog_index_composer(int total_pages, hh_catalog_page_t **pages, int player_rank);

hh_buffer_t *catalog_page_composer(hh_catalog_page_t *page);

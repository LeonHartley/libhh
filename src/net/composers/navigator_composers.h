#pragma once

#include "../buffer/buffer.h"
#include "../../navigator/navigator.h"

hh_buffer_t *user_room_categories_composer(int total_categories, hh_navigator_category_t **categories);

hh_buffer_t *featured_rooms_message_composer(int total_featured, hh_navigator_featured_t **featured);
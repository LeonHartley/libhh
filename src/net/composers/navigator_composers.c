#include "navigator_composers.h"

#include "composers.h"

hh_buffer_t *user_room_categories_composer(int total_categories, hh_navigator_category_t **categories) {
    hh_buffer_t *categories = hh_buffer_create(128, (char *) malloc(128));

    hh_buffer_initialise(categories);
    hh_buffer_write_short(UserRoomCategoriesMessageComposer, categories);
    
    hh_buffer_write_int(total_categories, categories);

    for(int i = 0; i < total_categories; i++) {
        hh_navigator_category_t *category = categories[i];

        hh_buffer_write_int(category->id, categories);
        hh_buffer_write_string(category->name, categories);
        hh_buffer_write_short(0, categories);
    }

    return categories;
}

hh_buffer_t *featured_rooms_message_composer(int total_featured, hh_navigator_featured_t **featured) {
    hh_buffer_t *buffer = hh_buffer_create(256, (char *) malloc(256));

    hh_buffer_write_int(total_featured, buffer);
    /*
   // for(int i = 0; i < total_featured; i++) {
      //  hh_navigator_featured_t *featured = featured[i];

        hh_buffer_write_int(featured->id, buffer);
     //   hh_buffer_write_int(featured->)
 //   }
*/
    return buffer;
}

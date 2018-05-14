#include "navigator_composers.h"

#include "composers.h"

hh_buffer_t *user_room_categories_composer(int total_categories, hh_navigator_category_t **categories) {
    hh_buffer_t *c = hh_buffer_create_empty();

    hh_buffer_initialise(c);
    hh_buffer_write_short(UserRoomCategoriesMessageComposer, c);
    
    hh_buffer_write_int(0, c);

    for(int i = 0; i < total_categories; i++) {
        hh_navigator_category_t *category = categories[i];

        hh_buffer_write_int(category->id, c);
        hh_buffer_write_string(category->name, c);
        hh_buffer_write_short(0, c);
    }

    return c;
}

hh_buffer_t *featured_rooms_message_composer(int total_featured, hh_navigator_featured_t **featured) {
    hh_buffer_t *buffer = hh_buffer_create_empty();

    hh_buffer_initialise(buffer);
    hh_buffer_write_short(FeaturedRoomsMessageComposer, buffer);

    hh_buffer_write_int(total_featured, buffer);
    
    for(int i = 0; i < total_featured; i++) {
        hh_navigator_featured_t *f = featured[i];
        
        hh_buffer_write_int(f->id, buffer);
        hh_buffer_write_string(f->caption, buffer);
        hh_buffer_write_string("", buffer);
        hh_buffer_write_int(0, buffer);
        hh_buffer_write_string(f->caption, buffer);
        hh_buffer_write_string(f->image, buffer);// image length, empty if internal :-)
        hh_buffer_write_int(0, buffer);//parent id
        hh_buffer_write_int(0, buffer);//users now-1 to test
        hh_buffer_write_int(3, buffer);//type: public room
        
        hh_buffer_write_string(f->image, buffer);
        hh_buffer_write_int(0, buffer);
        hh_buffer_write_int(0, buffer);
        hh_buffer_write_string("", buffer);
        hh_buffer_write_int(0, buffer);
        hh_buffer_write_int(0, buffer);
    }
    
    hh_buffer_write_int(0, buffer);

    return buffer;
}

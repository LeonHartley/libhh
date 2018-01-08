#include "player_composers.h"

#include "composers.h"
#include <stdio.h>

hh_buffer_t *user_object_composer(hh_player_data_t *player_data) {
    hh_buffer_t *user_obj = hh_buffer_create(512, ((char *) malloc(512)));
    
    hh_buffer_initialise(user_obj);
    hh_buffer_write_short(UserObjectMessageComposer, user_obj);
    
    hh_buffer_write_int(player_data->id, user_obj);
    
    hh_buffer_write_string(player_data->username, user_obj);
    hh_buffer_write_string(player_data->figure, user_obj);
    hh_buffer_write_string("M", user_obj);
    hh_buffer_write_string("motto", user_obj);
    hh_buffer_write_string("Name", user_obj);

    hh_buffer_write_byte(0, user_obj);
    hh_buffer_write_int(0, user_obj);
    hh_buffer_write_int(0, user_obj);

    hh_buffer_write_int(0, user_obj);
    hh_buffer_write_int(3, user_obj);
    hh_buffer_write_int(3, user_obj);

    hh_buffer_write_byte(0, user_obj);
    return user_obj;
}

hh_buffer_t *credit_balance_composer(int balance) {
    hh_buffer_t *credits = hh_buffer_create(64, (char *) malloc(64));

    hh_buffer_initialise(credits);
    hh_buffer_write_short(CreditBalanceMessageComposer, credits);
    
    char data[16];

    sprintf(data, "%i.0", balance);

    hh_buffer_write_string(&data, credits);

    return credits;
}

hh_buffer_t *user_room_categories_composer() {
    hh_buffer_t *categories = hh_buffer_create(64, (char *) malloc(64));

    hh_buffer_initialise(categories);
    hh_buffer_write_short(UserRoomCategoriesMessageComposer, categories);
    
    hh_buffer_write_int(1, categories);

    hh_buffer_write_int(1, categories);
    hh_buffer_write_string("Rooms", categories);
    hh_buffer_write_byte(1, categories);

    return categories;
}

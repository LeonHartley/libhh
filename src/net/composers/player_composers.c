#include "player_composers.h"

#include "composers.h"
#include <stdio.h>

const char *gender_m = "M";
const char *gender_f = "F";

hh_buffer_t *user_object_composer(hh_player_data_t *player_data) {
    hh_buffer_t *user_obj = hh_buffer_create_empty();
    
    hh_buffer_initialise(user_obj);
    hh_buffer_write_short(UserObjectMessageComposer, user_obj);
    
    hh_buffer_write_int(player_data->id, user_obj);
    
    hh_buffer_write_string(player_data->username, user_obj);
    hh_buffer_write_string(player_data->figure, user_obj);
    hh_buffer_write_string(player_data->gender == 1 ? gender_f : gender_m, user_obj);
    hh_buffer_write_string("yo", user_obj);
    hh_buffer_write_string("Real Name", user_obj);

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
    hh_buffer_t *credits = hh_buffer_create_empty();

    hh_buffer_initialise(credits);
    hh_buffer_write_short(CreditBalanceMessageComposer, credits);
    
    char data[16];

    sprintf(data, "%i.0", balance);

    hh_buffer_write_string(&data, credits);

    return credits;
}
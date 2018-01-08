#pragma once

#include "../buffer/buffer.h"
#include "../../players/player.h"

hh_buffer_t *user_object_composer(hh_player_data_t *player_data);

hh_buffer_t *credit_balance_composer(int balance);

hh_buffer_t *user_room_categories_composer();
#pragma once

#include "../../util/pos.h"

typedef struct hh_room_tile_s {
    hh_pos_t *position;
    
    int state;
} hh_room_tile_t;
#pragma once

#include "room.h"

void hh_room_directory_initialise();

hh_room_t *hh_room_get(int id);

hh_room_data_t *hh_room_data_get(int id);

int hh_room_is_active(int id);
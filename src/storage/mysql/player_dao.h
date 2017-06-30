#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "../../players/player.h"

hh_player_data_t *hh_player_dao_authenticate(const char *auth_ticket) {
    hh_player_data_t *player_data = malloc(sizeof(hh_player_data_t));
        
    player_data->username = "Leon";
    
    return player_data;
}

void hh_player_dao_initialise(hh_player_dao_t *player_dao) {
    player_dao->authenticate = &hh_player_dao_authenticate;
}

#include "storage.h"
#include "mysql/player_dao.h"

#include <stdlib.h>

void hh_storage_initialise() {
    hh_player_dao_t *player_dao = malloc(sizeof(hh_player_dao_t));
    
    hh_player_dao_initialise(player_dao);
    hh_player_dao = player_dao;
}
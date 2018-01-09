#include "storage.h"

#include "sqlite/database.h"
#include "sqlite/player_dao.h"
#include "sqlite/catalog_dao.h"
#include "sqlite/navigator_dao.h"

#include <stdlib.h>

void hh_storage_initialise() {
    hh_player_dao_t *player_dao = malloc(sizeof(hh_player_dao_t));
    
    hh_player_dao_initialise(player_dao);
    hh_player_dao = player_dao;

    hh_catalog_dao_t *catalog_dao = malloc(sizeof(hh_catalog_dao_t));

    hh_catalog_dao_initialise(catalog_dao);
    hh_catalog_dao = catalog_dao;

    hh_navigator_dao_t *navigator_dao = malloc(sizeof(hh_navigator_dao_t));

    hh_navigator_dao_initialise(navigator_dao);
    hh_navigator_dao = navigator_dao;
}
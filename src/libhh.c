//
// Created by Leon on 17/10/2016.
//

#include "libhh.h"

#include <stdlib.h>

#include "net/message_handler.h"
#include "net/server.h"

#include "util/hashmap.h"

#include "storage/storage.h"
#include "storage/connection.h"

#include "players/player.h"
#include <mysql/mysql_version.h>

int main(int argc, char *argv[]) {
    printf("[libhh] habbo emulation written in C\n");

    printf("[libhh] libuv version: %s\n", uv_version_string());
    printf("[libhh] mysql client version: %s\n", MYSQL_SERVER_VERSION);

    printf("[libhh] initialising message handlers\n");
    hh_initialise_message_handler();    

    hh_mysql_config_t config = {
        .hostname = "localhost",
        .username = "root",
        .password = "",
        .database = "cometsrv",
        .connection_count = 2
    };

    hh_mysql_create_pool(&config);

    //

 /*   hh_player_data_t *player_data = hh_player_data_create(1, "Leon", "figure-code-123", 'M');

    map_t players = hashmap_new();
    hashmap_put(players, "Leon", player_data);
    hh_player_data_t *found_player;

    hashmap_get(players, "Leon", &found_player);
    printf("[libhh] found player with figure %s\n", found_player->figure);

    /*char *name = "Leon";



    //*/

    hh_storage_initialise();

    hh_player_data_t *stored = hh_player_dao->authenticate("Leon");

    //printf("found username %s\n", stored->username);

    // hh_player_data_dispose(stored);

    printf("[libhh] initialising event loop with io on port %i\n", PORT);
    hh_start_server(HOST, PORT);

    return 0;
}
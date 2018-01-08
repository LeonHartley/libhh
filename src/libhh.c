//
// Created by Leon on 17/10/2016.
//

#include "libhh.h"

#include <stdlib.h>

#include "net/message_handler.h"
#include "net/server.h"

#include "util/hashmap.h"

#include "storage/storage.h"
#include "storage/sqlite/database.h"

#include "players/player.h"
#include "catalog/catalog.h"

int main(int argc, char *argv[]) {
    printf("[libhh] habbo emulation written in C\n");

    printf("[libhh] libuv version: %s\n", uv_version_string());

    printf("[libhh] initialising message handlers\n");
    hh_initialise_message_handler();    

    hh_sqlite_config_t sqlite_config = {
        .server_db = "database/server.sqlite",  
        .log_db = "database/logs.sqlite"
    };

    if(hh_sqlite_initialise_dbs(&sqlite_config)) {
        printf("[libhh] Failed to load databases!");
        return 1;
    }

    hh_storage_initialise();
    
    hh_catalog_mutex_init();
    hh_catalog_initialise();

    printf("[libhh] initialising event loop with io on port %i\n", PORT);
    hh_start_server(HOST, PORT);

    return 0;
}
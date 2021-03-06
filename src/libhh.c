//
// Created by Leon on 17/10/2016.
//

#include "libhh.h"

#include <stdlib.h>
#include <zconf.h>
#include <util/dictionary.h>

#include "dispatch/dispatch.h"

#include "net/message_handler.h"
#include "net/server.h"

#include "util/hashmap.h"

#include "storage/storage.h"
#include "storage/sqlite/database.h"

#include "util/collections/hashtable.h"

#include "players/player.h"
#include "catalog/catalog.h"

#include "navigator/navigator.h"

int main(int argc, char *argv[]) {
    printf("[libhh] habbo emulation written in C\n");

    printf("[libhh] libuv version: %s\n", uv_version_string());

    printf("[libhh] initialising message handlers\n");
    hh_initialise_message_handler();

    hh_sqlite_config_t sqlite_config = {
            .server_db = "database/server.sqlite",
            .log_db = "database/logs.sqlite"
    };

    if (hh_sqlite_initialise_dbs(&sqlite_config)) {
        printf("[libhh] Failed to load databases!");
        return 1;
    }

    hh_dictionary_t *dictionary = hh_dictionary_create();

    for(int i = 0; i < 10000; i++) {
        void *data = "Leon";
        hh_dictionary_add(i, data, dictionary);

        printf("Adding dict element %i, value: %s\n", i, (char *) data);
    }

    for(int i = 0; i < 10000; i++) {
        printf("Removing dict element %i, value: %s\n", i, (char *) hh_dictionary_remove(i, dictionary));
    }

    /*
     *  3 for rooms, 2 for others.
     *  This ensures the server is using a total
     *  of 8 threads. (1 thread is used for listening)
     */
    hh_dispatch_initialise(2, 3, 2);

    hh_storage_initialise();

    hh_catalog_mutex_init();
    hh_catalog_initialise();

    hh_navigator_mutex_init();
    hh_navigator_initialise();

    printf("[libhh] initialising event loop with io on port %i\n", PORT);

    hh_start_server(HOST, PORT);

    return 0;
}
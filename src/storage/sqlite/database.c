#include "database.h"

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

hh_sqlite_ctx_t *sqlite_context;

int hh_sqlite_initialise_dbs(hh_sqlite_config_t *config) {
    hh_sqlite_ctx_t *ctx = malloc(sizeof(hh_sqlite_ctx_t *));
    int server_db_status = sqlite3_open(config->server_db, &ctx->server_db);

    if(server_db_status) {
        printf("[libhh] Failed to load server database (%s)!\n", config->server_db);
        return 1;
    }

    sqlite_context = ctx;
}

sqlite3 *hh_sqlite_server_db() {
    return sqlite_context->server_db;
}
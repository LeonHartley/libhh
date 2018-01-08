#pragma once

#include <sqlite3.h>

typedef struct {
    const char *server_db;
    const char *log_db;
} hh_sqlite_config_t;

typedef struct {
    sqlite3 *server_db;
    sqlite3 *log_db;
} hh_sqlite_ctx_t;

int hh_sqlite_initialise_dbs(hh_sqlite_config_t *config);
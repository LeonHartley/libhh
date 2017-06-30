#pragma once

#include "../util/pool.h"

hh_pool_t *sql_connection_pool;

typedef struct {
    char *hostname;
    char *username;
    char *password;
    char *database;
    int connection_count;
} hh_mysql_config_t;

hh_mysql_config_t 

void hh_mysql_initialise_connection(hh_pool_entry_t *connection) {
    // create a connection and add it to the pool
    MYSQL *con = mysql_init(NULL);
    
    if(con == NULL) {
        return;
    }

    if (mysql_real_connect(con, "localhost", "user12", "34klq*", "testdb", 0, NULL, 0) == NULL) {
        return;
    }
}

void hh_mysql_create_pool(hh_mysql_config_t *config) {
    //int size, int concurrent, hh_pool_initialise_entry_cb init_cb)
    sql_connection_pool = hh_pool_create(2, 0, &hh_mysql_initialise_connection);
}
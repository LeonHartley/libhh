// #include "connection.h"

// #include "../util/pool.h"

// #include <stdio.h>

// hh_pool_t *sql_connection_pool;

// hh_mysql_config_t *config;

// #define MYSQL_PACKET_SIZE "SET GLOBAL max_allowed_packet=1000000000;"

// void hh_mysql_initialise_connection(hh_pool_entry_t *connection) {
//     // create a connection and add it to the pool
//     MYSQL *con = mysql_init(NULL);
    
//     if(con == NULL) {
//         return;
//     }

//     if (mysql_real_connect(con, config->hostname, config->username, config->password, config->database, 0, NULL, 0) == NULL) {
//         printf("[libhh] Failed to MySQL initialise connection. Error: %i %s\n", mysql_errno(con), mysql_error(con));
//         return;
//     }

//     int r = mysql_real_query(con, MYSQL_PACKET_SIZE, strlen(MYSQL_PACKET_SIZE));

//     printf("%i %s\n", r, mysql_error(con));

//     con->extension    = (void *) connection;
//     connection->value = (void *) con;
// }

// void hh_mysql_create_pool(hh_mysql_config_t *dbconf) {
//     config = dbconf;

//     sql_connection_pool = hh_pool_create(2, 0, &hh_mysql_initialise_connection);
// }

// MYSQL *hh_mysql_connection_get() {
//     hh_pool_entry_t *entry = hh_pool_take(sql_connection_pool);

//     if(entry == NULL) {
//         return NULL;
//     }

//     return (MYSQL *) entry->value;
// }

// void hh_mysql_connection_return(MYSQL *con) {
//     hh_pool_entry_t *entry = (hh_pool_entry_t *) con->extension;
//     hh_pool_return(entry, sql_connection_pool);
// }
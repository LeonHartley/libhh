#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../storage/connection.h"
#include "../../players/player.h"

#define PLAYER_AUTHENTICATE_QUERY "SELECT `id`, `username` FROM `players` WHERE `username` = ?"

// TODO: Better error catching haha
// TODO: move all this stuff to macros & helper functions
hh_player_data_t *hh_player_dao_authenticate(char *auth_ticket) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];

    MYSQL *con = hh_mysql_connection_get();

    stmt = mysql_stmt_init(con);

    if(!stmt) {
        // error
        printf("Initialising statement failed, error %s\n", mysql_stmt_error(stmt));
        return NULL;
    }

    if(mysql_stmt_prepare(stmt, PLAYER_AUTHENTICATE_QUERY, strlen(PLAYER_AUTHENTICATE_QUERY))) {
        printf("Preparing statement failed, error %s\n", mysql_stmt_error(stmt));
        return NULL;
    }

    memset(bind, 0, sizeof(bind));

    int ticket_length = strlen(auth_ticket);

    bind[0].buffer_type     = MYSQL_TYPE_STRING;
    bind[0].buffer          = auth_ticket;
    bind[0].buffer_length   = 50;
    bind[0].is_null         = 0;
    bind[0].length          = &ticket_length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        printf("Binding params failed, error %s\n", mysql_error(con));
        
        goto CLEANUP;
    }

    if (mysql_stmt_execute(stmt)) {
        printf("Failed to execute statement, error %i\n", mysql_errno(con));

        goto CLEANUP;
    }

    printf("Found %i players\n", mysql_stmt_affected_rows(stmt));

    // todo: create & return player struct etc
    goto CLEANUP;

    CLEANUP:
        mysql_stmt_close(stmt);
        hh_mysql_connection_return(con);
        return NULL;
}

void hh_player_dao_initialise(hh_player_dao_t *player_dao) {
    player_dao->authenticate = &hh_player_dao_authenticate;
}

/*
  hh_player_data_t *player_data = malloc(sizeof(hh_player_data_t));
        
    player_data->username = "Leon";
    
    return player_data; */
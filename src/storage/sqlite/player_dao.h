#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../storage/sqlite/database.h"
#include "../../players/player.h"

#include "sqlite3.h"

// TODO: Better error catching haha
// TODO: move all this stuff to macros & helper functions
hh_player_data_t *hh_player_dao_authenticate(char *auth_ticket) {
    sqlite3 *player_db = hh_sqlite_server_db();
    sqlite3_stmt *stmt;

    int status = sqlite3_prepare_v2(player_db, "SELECT id, username, figure, motto FROM player_data WHERE sso_ticket = ?", -1, &stmt, 0);

    if (status == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, auth_ticket, -1, SQLITE_STATIC);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(player_db));
    }

    int step = sqlite3_step(stmt);

    hh_player_t *player = NULL;

    if (step == SQLITE_ROW) {
        player = hh_player_data_create(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2),
            0 /*male*/
        );
    } 

    sqlite3_finalize(stmt);
    return player;
}

void hh_player_dao_initialise(hh_player_dao_t *player_dao) {
    player_dao->authenticate = &hh_player_dao_authenticate;
}

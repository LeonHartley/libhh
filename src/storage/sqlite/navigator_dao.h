#pragma once 

#include "../storage.h"

#include "../../navigator/navigator.h"

void hh_navigator_dao_load_categories() {
    sqlite3 *db = hh_sqlite_server_db();
    sqlite3_stmt *stmt;

    int status = sqlite3_prepare_v2(db, "SELECT id, name, min_rank FROM navigator_categories;", -1, &stmt, 0);

    if (status != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    while ((sqlite3_step(stmt) == SQLITE_ROW)) {
        hh_navigator_add_category(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_int(stmt, 2)
        );
    } 

    sqlite3_finalize(stmt);
}

void hh_navigator_dao_load_featured() {
    sqlite3 *db = hh_sqlite_server_db();
    sqlite3_stmt *stmt;

    int status = sqlite3_prepare_v2(db, "SELECT id, banner_type, caption, image, image_type, room_id, category_id, category_parent_id FROM navigator_featured;", -1, &stmt, 0);

    if (status != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    while ((sqlite3_step(stmt) == SQLITE_ROW)) {
        hh_navigator_add_featured(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_text(stmt, 3),
            sqlite3_column_int(stmt, 4),
            sqlite3_column_int(stmt, 5),
            sqlite3_column_int(stmt, 6),
            sqlite3_column_int(stmt, 7)
        );
    } 

    sqlite3_finalize(stmt);
}

void hh_navigator_dao_initialise(hh_navigator_dao_t *navigator_dao) {
    navigator_dao->load_featured = &hh_navigator_dao_load_featured;
    navigator_dao->load_categories = &hh_navigator_dao_load_categories;
}

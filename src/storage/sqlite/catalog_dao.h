#pragma once 

#include "../storage.h"

#include "../../catalog/catalog.h"

void hh_catalog_dao_load_pages() {
    sqlite3 *db = hh_sqlite_server_db();
    sqlite3_stmt *stmt;

    int status = sqlite3_prepare_v2(db, "SELECT id, parent_id, name, min_rank, enabled, is_category, icon_colour, icon_img, layout, headline_img, teaser_img, special_img, text_1, text_2, details, teaser_txt FROM catalog_pages;", -1, &stmt, 0);

    if (status != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    int rc;
    
    while ((sqlite3_step(stmt) == SQLITE_ROW)) {
        hh_catalog_add_page(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_int(stmt, 3),
            sqlite3_column_int(stmt, 4),
            sqlite3_column_int(stmt, 5),
            sqlite3_column_int(stmt, 6),
            sqlite3_column_int(stmt, 7),
            sqlite3_column_text(stmt, 8),
            sqlite3_column_text(stmt, 9),
            sqlite3_column_text(stmt, 10),
            sqlite3_column_text(stmt, 11),
            sqlite3_column_text(stmt, 12),
            sqlite3_column_text(stmt, 13),
            sqlite3_column_text(stmt, 14),
            sqlite3_column_text(stmt, 15)
        );
    } 

    sqlite3_finalize(stmt);
}

void hh_catalog_dao_load_items() {
    sqlite3 *db = hh_sqlite_server_db();
    sqlite3_stmt *stmt;

    int status = sqlite3_prepare_v2(db, "SELECT id, page_id, name, item_id, amount, price_credits, price_activity_points, price_vip_points FROM catalog_items;", -1, &stmt, 0);

    if (status != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    while ((sqlite3_step(stmt) == SQLITE_ROW)) {
        hh_catalog_add_item(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_int(stmt, 3),
            sqlite3_column_int(stmt, 4),
            sqlite3_column_int(stmt, 5),
            sqlite3_column_int(stmt, 6),
            sqlite3_column_int(stmt, 7)
        );
    } 

    sqlite3_finalize(stmt);
}

void hh_catalog_dao_initialise(hh_catalog_dao_t *catalog_dao) {
    catalog_dao->load_pages = &hh_catalog_dao_load_pages;
    catalog_dao->load_items = &hh_catalog_dao_load_items;
}

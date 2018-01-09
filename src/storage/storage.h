#pragma once

#include "../players/player.h"

typedef hh_player_data_t *(*hh_player_dao_authenticate_cb) (char *auth_ticket);

typedef void (*hh_catalog_dao_load_cb) ();
typedef void (*hh_navigator_dao_load_cb) ();

typedef struct {
    hh_player_dao_authenticate_cb authenticate;
} hh_player_dao_t;

typedef struct {
    hh_catalog_dao_load_cb load_items;
    hh_catalog_dao_load_cb load_pages;
} hh_catalog_dao_t;

typedef struct {
    hh_navigator_dao_load_cb load_categories;
    hh_navigator_dao_load_cb load_featured;
} hh_navigator_dao_t;

hh_player_dao_t *hh_player_dao;
hh_catalog_dao_t *hh_catalog_dao;
hh_navigator_dao_t *hh_navigator_dao;

typedef struct {
    const char *host;
    const char *username;
} hh_storage_config_t;

void hh_storage_initialise();


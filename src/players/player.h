#pragma once

#include <stdlib.h>

typedef struct {
    int id;
    char *username;
    char *figure;
    int gender;
} hh_player_data_t;

typedef struct {
    hh_player_data_t *data;
} hh_player_t;

/**
 *  Creates a player with the set session
 */
hh_player_t *hh_player_create();

hh_player_data_t *hh_player_data_create(int id, char *username, char *figure, char gender);

/**
 *  Frees any memory associated with the player data & frees 
 *  the player data itself.
 */
void hh_player_data_dispose(hh_player_data_t *player_data);

/**
 * Frees any memory associated with the player & the player itself
 */
void hh_player_dispose(hh_player_t *player);
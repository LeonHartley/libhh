#include "player.h"

/**
 *  Creates a player with the set session
 */
hh_player_t *hh_player_create() {
    hh_player_t *player = malloc(sizeof(hh_player_t));

    return player;
}

hh_player_data_t *hh_player_data_create(int id, char *username, char *figure, char gender) {
    hh_player_data_t *data = malloc(sizeof(hh_player_data_t));

    data->id = id;
    data->username = strdup(username);
    data->figure = strdup(figure);
    data->gender = gender;

    return data;
}

/**
 *  Frees any memory associated with the player data & frees 
 *  the player data itself.
 */
void hh_player_data_dispose(hh_player_data_t *player_data) {
    free(player_data->username);
    free(player_data->figure);
    free(player_data);
}

/**
 * Frees any memory associated with the player & the player itself
 */
void hh_player_dispose(hh_player_t *player) {
    hh_player_data_dispose(player->data);

    free(player);
}
#include "player.h"

/**
 *  Creates a player with the set session
 */
hh_player_t *hh_player_create(hh_player_data_t *player_data) {
    hh_player_t *player = malloc(sizeof(hh_player_t));

    player->data = player_data;

    return player;
}

hh_player_data_t *hh_player_data_create(int id, const char *username, const char *figure, char gender) {
    hh_player_data_t *data = malloc(sizeof(hh_player_data_t));

    data->id = id;
    data->username = strdup(username);
    data->figure = strdup(figure);
    data->gender = gender;
    data->rank = 7;/*load this from db*/
    data->credits = 1000;

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
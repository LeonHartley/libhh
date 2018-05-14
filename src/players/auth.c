#include "auth.h"

#include "../storage/storage.h"

int hh_player_auth(hh_session_t *session, char *sso_ticket) {
    hh_player_data_t *player_data = hh_player_dao->authenticate(sso_ticket);

    if(player_data == NULL) {
        // Failed to authenticate player
        return 0;
    }

    hh_player_t *player = hh_player_create(player_data);

    session->player = player;

    printf("[libhh] player logged in: %s\n", player->data->username);
    return 1;
}
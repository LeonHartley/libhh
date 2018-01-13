#include "navigator_handler.h"

#include "../../composers/navigator_composers.h"


void get_user_categories_handler(hh_buffer_t *buffer, hh_session_t *session) {
    if(session->player == NULL) {
        return;
    }

    hh_navigator_mutex_read_lock();
    
    hh_navigator_state_t *state = hh_navigator_state();

    hh_write_message(user_room_categories_composer(state->loaded_categories, state->categories), session);

    hh_navigator_mutex_read_unlock();
}

void official_rooms_handler(hh_buffer_t *buffer, hh_session_t *session) {
    if(session->player == NULL) {
        return;
    }

    hh_navigator_mutex_read_lock();
    
    hh_navigator_state_t *state = hh_navigator_state();

    hh_write_message(featured_rooms_message_composer(state->loaded_featured, state->featured), session);

    hh_navigator_mutex_read_unlock();
}

void navigator_text_search_test(hh_buffer_t *buffer, hh_session_t *session) {
    char *search_str = hh_buffer_read_string(buffer);

    printf("search str %s, length %i\n", search_str, strlen(search_str));
    free(search_str);
}
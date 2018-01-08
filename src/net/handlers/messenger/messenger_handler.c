#include "messenger_handler.h"

#include "../../composers/messenger_composers.h"

void init_messenger_handler(hh_buffer_t *buffer, hh_session_t *session) {
    if(session->player == NULL) {
        return;
    }

    hh_write_message(initialise_messenger_composer(), session);
}
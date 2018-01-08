#include "messenger_composers.h"

#include "composers.h"

hh_buffer_t *initialise_messenger_composer() {
    hh_buffer_t *msgr = hh_buffer_create_empty();

    hh_buffer_initialise(msgr);
    hh_buffer_write_short(MessengerInitMessageComposer, msgr);    
    
    hh_buffer_write_int(300, msgr);
    hh_buffer_write_int(300, msgr);
    hh_buffer_write_int(800, msgr);
    hh_buffer_write_int(1100, msgr);
    hh_buffer_write_int(0, msgr);
    hh_buffer_write_int(0, msgr);    

    return msgr;
}

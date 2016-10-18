//
// Created by Leon on 17/10/2016.
//

#include <stdlib.h>

#include "libhh.h"
#include "net/server.h"

int main(int argc, char *argv[]) {
    printf("[libhh] habbo emulation written in C\n");
    printf("[libhh] libuv version: %s\n", uv_version_string());
    printf("[libhh] initialising message handlers\n");

    load_message_handlers();

    printf("[libhh] initialising event loop with io on port %i\n", PORT);

    hh_start_server("0.0.0.0", 3000);
    return 0;
}
//
// Created by Leon on 17/10/2016.
//

#include <stdlib.h>
#include <gmp.h>

#include "libhh.h"

// linux only, todo: macro n constants to check os n set the pid accordingly.
#include <sys/types.h>
#include <unistd.h>

#include "mysql/mysql.h"

#include "net/message_handler.h"
#include "net/server.h"

int main(int argc, char *argv[]) {
    printf("[libhh] habbo emulation written in C\n");

    printf("[libhh] process id: %i\n", getpid());
    printf("[libhh] libuv version: %s\n", uv_version_string());

    printf("[libhh] connecting to mysql database");

    printf("[libhh] initialising message handlers\n");
    load_message_handlers();    

    printf("[libhh] initialising event loop with io on port %i\n", PORT);
    hh_start_server("0.0.0.0", 3000);

    return 0;
}
cmake_minimum_required(VERSION 3.5)
project(libhh C)

set(EXECUTABLE_NAME libhh)
set(CMAKE_C_STANDARD 11)
set(PROJECT_DIR src)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules" CACHE STRING "Modules for CMake" FORCE)

find_package (Libuv)

include_directories(src)

add_executable(${EXECUTABLE_NAME}
        src/libhh.c
        src/dispatch/dispatch.h
        src/dispatch/dispatch.c
        src/net/server.h
        src/net/server.c
        src/net/message_handler.h
        src/net/message_handler.c
        src/net/handlers/handshake_handler.h
        src/net/handlers/handshake_handler.c
        src/net/buffer/buffer.h
        src/net/buffer/buffer.c
        src/net/handlers/handshake_handler.h
        src/net/handlers/handshake_handler.c
        src/net/handlers/catalog/catalog_handler.h
        src/net/handlers/catalog/catalog_handler.c
        src/net/handlers/messenger/messenger_handler.h
        src/net/handlers/messenger/messenger_handler.c
        src/net/handlers/navigator/navigator_handler.h
        src/net/handlers/navigator/navigator_handler.c
        src/net/composers/handshake_composers.h
        src/net/composers/handshake_composers.c
        src/net/composers/player_composers.h
        src/net/composers/player_composers.c
        src/net/composers/catalog_composers.h
        src/net/composers/catalog_composers.c
        src/net/composers/messenger_composers.h
        src/net/composers/messenger_composers.c
        src/net/composers/navigator_composers.h
        src/net/composers/navigator_composers.c
        src/net/composers/composers.h
        src/net/sessions/session.h
        src/net/sessions/session.c
        src/net/events/events.h
        src/players/player.h
        src/players/player.c
        src/players/auth.h
        src/players/auth.c
        src/catalog/catalog.h
        src/catalog/catalog.c
        src/rooms/room.h
        src/navigator/navigator.h
        src/navigator/navigator.c
        src/util/hashmap.h
        src/util/hashmap.c
        src/storage/storage.h
        src/storage/storage.c
        src/storage/sqlite/player_dao.h
        src/storage/sqlite/navigator_dao.h
        src/storage/sqlite/database.h
        src/storage/sqlite/database.c
        src/util/pool.h
        src/util/pool.c
        src/util/dictionary.h)

target_link_libraries(${EXECUTABLE_NAME} uv sqlite3)

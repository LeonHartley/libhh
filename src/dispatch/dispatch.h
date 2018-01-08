#pragma once

#include <uv.h>

/*
 *  GameDispatch is the main loop which all messages are handled on,
 *  which means pretty much everything other than room stuff happens here.
 */
#define GameDispatch 0

/*  
 *  RoomDispatch is the loop which room processing is handled on.
 */
#define RoomDispatch 1

typedef struct {
    void *data;
} hh_dispatch_work_t;

typedef struct {
    uv_thread_t *thread;
    uv_loop_t *loop;
} hh_dispatch_loop_t;
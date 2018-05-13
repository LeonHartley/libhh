#include "dispatch.h"

#include <stdlib.h>
#include <unistd.h>

int runner_count = 0;
hh_dispatch_loop_group_t game_dispatch;
hh_dispatch_loop_group_t room_dispatch;
hh_dispatch_loop_group_t storage_dispatch;

void dispatch_async_test(uv_async_t *handle) {
    printf("async operation test\n");
}

void dispatch_initialise_loop_thread(void *data) {
    hh_dispatch_loop_t *loop = (hh_dispatch_loop_t *) data;
    uv_async_t async;

    uv_loop_init(loop->loop);

    // We gotta add atleast 1 thing to the loop before we run it.
    uv_async_init(loop->loop, &async, &dispatch_async_test);
    uv_async_send(&async);

    printf("[libhh] starting async loop thread %i\n", loop->id);

    int r = uv_run(loop->loop, UV_RUN_DEFAULT);

    printf("[libhh] runner has exited: %i\n", r);
}

void dispatch_initialise_loops(hh_dispatch_loop_group_t *group, int count) {
    // setup dispatch with counts
    group->total_loops = count;
    group->current_index = 0;
    group->mutex = (uv_rwlock_t *) malloc(sizeof(uv_rwlock_t));

    uv_rwlock_init(group->mutex);

    group->loops = calloc((size_t) count, sizeof(hh_dispatch_loop_t));

    for(int i = 0; i < count; i++) {
        hh_dispatch_loop_t *loop = malloc(sizeof(hh_dispatch_loop_t));

        loop->id = ++runner_count;
        loop->loop = malloc(sizeof(uv_loop_t));
        loop->thread = malloc(sizeof(uv_thread_t));

        uv_thread_create(loop->thread, &dispatch_initialise_loop_thread, loop);

        group->loops[i] = loop;
    }
}

void hh_dispatch_initialise(int game_dispatch_count, int room_dispatch_count, int storage_dispatch_count) {
    dispatch_initialise_loops(&game_dispatch, game_dispatch_count);
    dispatch_initialise_loops(&room_dispatch, room_dispatch_count);
    dispatch_initialise_loops(&storage_dispatch, storage_dispatch_count);
}

void hh_dispatch_shutdown() {

}

hh_dispatch_loop_group_t *dispatch_get_group(char group) {
    switch(group) {
        default: return &game_dispatch;

        case GameDispatch: return &game_dispatch;
        case RoomDispatch: return &room_dispatch;
        case StorageDispatch: return &storage_dispatch;
    }
}

void hh_dispatch(char group_id, hh_dispatch_cb_t *cb, void *data) {
    hh_dispatch_loop_group_t *group = dispatch_get_group(group_id);

    uv_rwlock_rdlock(group->mutex);

    // find a loop & dispatch our work to it

    uv_rwlock_rdlock(group->mutex);
}

#pragma once

#include "../tiles/tile.h"
#include "../../util/pos.h"

#include <stdlib.h>
#include <limits.h>

#define PATHFINDER_MAX_STEPS 256

hh_pos_t move_points[8] = {
    { -1, -1 }, 
    { 0 , -1 },
    { 1, 1 },
    { 0, 1 },
    { 1, -1 },
    { 1, 0 },
    { -1, 1 },
    { -1, 0 }
};

typedef struct hh_pathfinder_node_s {
    hh_pos_t *position;
    int cost;

    int in_open;
    int in_closed;

    hh_pathfinder_node_t *next;
} hh_pathfinder_node_t;

hh_pathfinder_node_t *hh_pathfinder_find_path(hh_pos_t *from, hh_pos_t *to, hh_room_tile_t **tiles,
     const int room_size_x, int room_size_y) {
    
    hh_pathfinder_node_t **map = hh_pathfinder_create_map(room_size_x, room_size_y);
    hh_pathfinder_node_t *node;

    hh_pathfinder_node_t current = {
        from, 0, 0, 0, NULL            
    }

    hh_pathfinder_node_t finish = {
        from, INT_MAX, 0, 0, NULL            
    }

    hh_pos_t tmp;

    path[0] = current;

    int path_size = 1;
    int diff;
    int cost;

    while(path_size > 0) {
        path_size--;
        
        current.in_closed = 1;

        for(int i = 0; i < 8; i++) {
            hh_pos_t move_point = move_points[i];

            tmp = hh_pos_add(current.position, &move_point);

            // todo: check with room map if is valid move.
            
            if(tmp.x >= room_size_x || tmp.y >= room_size_y) {
                continue;
            }

            if(map[tmp.x][tmp.y]->pos == NULL) {
                map[tmp.x][tmp.y]->pos = &tmp;
                map[tmp.x][tmp.y]->cost = INT_MAX;

                node = map[tmp.x][tmp.y];
            } else {
                node = map[tmp.x][tmp.y];
            }

            if(!node->in_closed) {
                diff = 0;

                if(current.pos->x != node->pos->x) {
                    diff += 1;
                }

                if(current.pos->y != node->pos->y) {
                    diff += 1;
                }
                
                cost = current.cost + diff + hh_pos_distance_sq(node->pos, finish.pos);

                if(cost < node->cost) {
                    node->cost = cost;
                    node->next = current;
                }

                if(!node->in_open) {
                    if(node->pos->x == finish.pos->x && node->pos->y == finish.pos->y) {
                        node->next = current;

                        hh_pathfinder_free_map(map);                        
                        return node;
                    }

                    node.in_open = 1;
                    path_size++;
                    current = &node;
                }
            }
        }
    }

    hh_pathfinder_free_map(map);

    return NULL;
}

hh_pathfinder_node_t **hh_pathfinder_create_map(int room_size_x, int room_size_y) {
    hh_pathfinder_node_t **map = (hh_pathfinder_node_t **) malloc(room_size_x * sizeof(hh_pathfinder_node_t));

    for(int x = 0; x < room_size_x; x++) {
        map[x] = (hh_pathfinder_node_t *) malloc(room_size_y * sizeof(hh_pathfinder_t));
    }

    return map;
}

void hh_pathfinder_free_map(hh_pathfinder_node_t **map, int room_size_x) {
    for(int x = 0; x < room_size_x; x++) {
        free(map[x]);
    }

    free(map);
}
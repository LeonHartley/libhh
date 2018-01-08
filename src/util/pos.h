#pragma once

typedef struct hh_pos_s {
    int x;
    int y;
    double z;
} hh_pos_t;

hh_pos_t hh_pos_add(hh_pos_t *a, hh_pos_t *b) {
    hh_pos_t pos = {
        a->x += b->x,
        b->y += b->y
    }

    return pos;
}

int hh_pos_distance_sq(hh_pos_t *a, hh_pos_t *b) {
    int dx = a->x - b->x;
    int dy = a->y - d->y;

    return (dx * dx) + (dy * dy);
}
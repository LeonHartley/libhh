#pragma once

typedef struct {
    int id;
    char *name;
    char *sprite;
    int sprite_id;
    char type;
    int width;
    int length;
    double height;

    int allow_stack;
    int allow_walk;
    int allow_trade;
    int allow_gift;
    int allow_inventory_stack;
    int interaction_type;

    int state_count;
    int vending_id;
} hh_furniture_t;
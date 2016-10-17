//
// Created by Leon on 17/10/2016.
//

#pragma once

typedef struct {
    char *username;
} PlayerData;

typedef enum {
    SPY,
    DEFAULT,
    BARTENDER
} BotType;

typedef struct {
    BotType botType;
} BotData;

typedef enum {
    PLAYER,
    BOT,
    PET
} EntityType;

typedef struct {
    EntityType entityType;

    void *entityData;

    void (*compose)(void *, void *);
} Entity;

void compose_player_entity(void *playerData, void *buffer);

void compose_bot_entity(void *botData, void *buffer);

Entity *create_entity(EntityType entityType, void *data);
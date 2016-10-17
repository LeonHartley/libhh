#include "entity.h"
#include <stdlib.h>
#include <stdio.h>

// buffer is a void pointer cos we dont have a buffer obj yet lols
void compose_player_entity(void *playerData, void *buffer) {
    printf("printing player entity data\n");
}

// buffer is a void pointer cos we dont have a buffer obj yet lols
void compose_bot_entity(void *botData, void *buffer) {
    printf("printing bot entity data\n");
}

Entity *create_entity(EntityType entityType, void *data) {
    Entity *entity = malloc(sizeof(Entity));

    entity->entityData = data;

    switch (entityType) {
        case PLAYER:
            entity->compose = &compose_player_entity;
            break;

        case BOT:
            entity->compose = &compose_bot_entity;
            break;

        case PET:
            break;
    }

    return entity;
}
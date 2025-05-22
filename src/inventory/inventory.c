/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** inventory
*/

#include "frame.h"

static void destory_item(frame_t *frame, item_t *item)
{
    int item_index = -1;

    for (int i = 0; i < NBITEMS; i++)
        if (ITEM[i].id == item->id) {
            item_index = i;
            break;
        }
    if (item_index < 0)
        return;
    for (int j = item_index; j < NBITEMS - 1; j++)
        ITEM[j] = ITEM[j + 1];
    NBITEMS--;
    ITEM = realloc(ITEM, sizeof(item_t) * NBITEMS);
    if (!ITEM) {
        fprintf(stderr, "Failed to reallocate memory for items\n");
        return;
    }
}

static item_t copy_item(item_t *item)
{
    item_t new_item = {0};

    new_item.pos = item->pos;
    new_item.texture = item->texture;
    new_item.scale = item->scale;
    new_item.rec = item->rec;
    strcpy(new_item.name, item->name);
    new_item.pickable = item->pickable;
    new_item.id = item->id;
    new_item.useable = item->useable;
    strcpy(new_item.description, item->description);
    return (new_item);
}

static float distance_to_player(frame_t *frame, sfVector3f item_pos)
{
    float dx = item_pos.x - PLAYER->pos.x;
    float dy = item_pos.y - PLAYER->pos.y;

    return sqrtf(dx * dx + dy * dy);
}

void pick_item(frame_t *frame, item_t *item)
{
    if (!item->pickable)
        return;
    if (PLAYER->inventory->nb_items >= MAX_ITEMS)
        return;
    if (distance_to_player(frame, item->pos) > 50.0f)
        return;
    for (int i = 0; i < PLAYER->inventory->nb_items; i++)
        if (strcmp(PLAYER->inventory->items[i].name, item->name) == 0) {
            PLAYER->inventory->item_coun[i]++;
            destory_item(frame, item);
            return;
        }
    PLAYER->inventory->items[PLAYER->inventory->nb_items] = copy_item(item);
    PLAYER->inventory->item_coun[PLAYER->inventory->nb_items] = 1;
    PLAYER->inventory->nb_items++;
    destory_item(frame, item);
}

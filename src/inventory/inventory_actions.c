/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** inventory_actions
*/

#include "frame.h"

static void create_dropped_item(frame_t *frame, item_t *inventory_item)
{
    float angle = PLAYER->angle.x;

    ITEM = realloc(ITEM, sizeof(item_t) * (NBITEMS + 1));
    if (!ITEM) {
        fprintf(stderr, "Failed to reallocate memory for items\n");
        return;
    }
    ITEM[NBITEMS] = *inventory_item;
    ITEM[NBITEMS].pos.x = PLAYER->pos.x + cosf(angle) * 1.5f;
    ITEM[NBITEMS].pos.y = PLAYER->pos.y + sinf(angle) * 1.5f;
    ITEM[NBITEMS].pos.z = inventory_item->pos.z;
    NBITEMS++;
}

void drop_item(frame_t *frame, int item_index)
{
    if (item_index < 0 || item_index >= INVENTORY->nb_items)
        return;
    INVENTORY->item_coun[item_index]--;
    if (INVENTORY->item_coun[item_index] <= 0) {
        create_dropped_item(frame, &INVENTORY->items[item_index]);
        for (int i = item_index; i < INVENTORY->nb_items - 1; i++) {
            INVENTORY->items[i] = INVENTORY->items[i + 1];
            INVENTORY->item_coun[i] = INVENTORY->item_coun[i + 1];
        }
        INVENTORY->nb_items--;
    } else {
        create_dropped_item(frame, &INVENTORY->items[item_index]);
    }
}

void use_item(frame_t *frame, int item_index)
{
    if (item_index < 0 || item_index >= INVENTORY->nb_items)
        return;
    if (strcmp(INVENTORY->items[item_index].name, "Heal") == 0) {
        PLAYER->life += 20;
        if (PLAYER->life > PLAYER->max_life)
            PLAYER->life = PLAYER->max_life;
    }
    INVENTORY->item_coun[item_index]--;
    if (INVENTORY->item_coun[item_index] <= 0) {
        for (int i = item_index; i < INVENTORY->nb_items - 1; i++) {
            INVENTORY->items[i] = INVENTORY->items[i + 1];
            INVENTORY->item_coun[i] = INVENTORY->item_coun[i + 1];
        }
        INVENTORY->nb_items--;
        INVENTORY->selected_item = -1;
    }
}

bool use_item_key(frame_t *frame)
{
    int index = -1;

    for (int i = 0; i < INVENTORY->nb_items; i++) {
        if (strcmp(INVENTORY->items[i].name, "key") == 0) {
            index = i;
            break;
        }
    }
    if (index < 0)
        return false;
    use_item(frame, index);
    return true;
}

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
        if (add_life(frame, 20))
            return;
    }
    if (strcmp(INVENTORY->items[item_index].name, "Ammo_box") == 0) {
        if (add_ammo(frame, 40))
            return;
    }
    delete_used_item(frame, item_index);
}

void drop_item_at_pos(frame_t *frame, int item_index, sfVector2f pos)
{
    if (create_item(frame, ITEM_INFOS[item_index].path,
        ITEM_INFOS[item_index].scale,
        v3f(pos.x, pos.y, ITEM_INFOS[item_index].pos.z)) == 84)
        return;
    ITEM[NBITEMS - 1].rec = ITEM_INFOS[item_index].rec;
    strcpy(ITEM[NBITEMS - 1].name, ITEM_INFOS[item_index].name);
    ITEM[NBITEMS - 1].pickable = ITEM_INFOS[item_index].pickable;
    ITEM[NBITEMS - 1].useable = ITEM_INFOS[item_index].useable;
    strcpy(ITEM[NBITEMS - 1].description, ITEM_INFOS[item_index].description);
}

int get_item_index(char *name)
{
    if (name == NULL)
        return -1;
    for (int i = 0; ITEM_INFOS[i].path; i++) {
        if (strcmp(ITEM_INFOS[i].name, name) == 0)
            return i;
    }
    return -1;
}

bool use_item_key(frame_t *frame)
{
    int index = -1;

    for (int i = 0; i < INVENTORY->nb_items; i++) {
        if (strcmp(INVENTORY->items[i].name, "Key") == 0) {
            index = i;
            break;
        }
    }
    if (index < 0)
        return false;
    use_item(frame, index);
    return true;
}

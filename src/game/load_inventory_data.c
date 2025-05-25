/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** load_inventory_data
*/

#include "frame.h"

static bool read_inventory_data(FILE *file, inventory_t *inventory_temp)
{
    if (fread(inventory_temp, sizeof(inventory_t), 1, file) != 1) {
        fprintf(stderr, "Error reading inventory data\n");
        return false;
    }
    return true;
}

static sfTexture* find_item_texture(const char *item_name)
{
    for (int j = 0; ITEM_INFOS[j].path; j++)
        if (strcmp(item_name, ITEM_INFOS[j].name) == 0)
            return sfTexture_createFromFile(ITEM_INFOS[j].path, NULL);
    return NULL;
}

static void copy_inventory_item(frame_t *frame,
    inventory_t *inventory_temp, int index)
{
    PLAYER->inventory->items[index] = inventory_temp->items[index];
    PLAYER->inventory->items[index].texture =
        find_item_texture(inventory_temp->items[index].name);
    PLAYER->inventory->item_coun[index] = inventory_temp->item_coun[index];
}

static void copy_inventory_data(frame_t *frame, inventory_t *inventory_temp)
{
    PLAYER->inventory->nb_items = inventory_temp->nb_items;
    for (int i = 0; i < inventory_temp->nb_items; i++)
        copy_inventory_item(frame, inventory_temp, i);
    PLAYER->inventory->selected_item = inventory_temp->selected_item;
}

bool load_inventory_data(frame_t *frame, FILE *file)
{
    inventory_t inventory_temp;

    if (!read_inventory_data(file, &inventory_temp))
        return false;
    if (PLAYER->inventory && inventory_temp.nb_items <= MAX_ITEMS)
        copy_inventory_data(frame, &inventory_temp);
    else {
        fprintf(stderr, "Invalid inventory data (NULL or too many items)\n");
        return false;
    }
    return true;
}

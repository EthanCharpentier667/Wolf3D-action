/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_inventory
*/

#include "frame.h"

static void init_item_buttons(frame_t *frame)
{
    for (int i = 0; i < MAX_ITEMS; i++) {
        INVENTORY->item_buttons[i].sprite = sfSprite_create();
        INVENTORY->item_buttons[i].hover = false;
        INVENTORY->item_buttons[i].clicked = false;
        INVENTORY->item_buttons[i].disabled = false;
        INVENTORY->item_buttons[i].action = i;
    }
}

static void init_inventory_infos(frame_t *frame)
{
    INVENTORY->padding = 40.0f;
    INVENTORY->grid_size = (int)sqrt(MAX_ITEMS);
    INVENTORY->cell_size = 70.0f;
    INVENTORY->gap = 10.0f;
    INVENTORY->inv_width = INVENTORY->padding * 2 + INVENTORY->grid_size *
        (INVENTORY->cell_size + INVENTORY->gap) - INVENTORY->gap;
    INVENTORY->inv_height = INVENTORY->padding * 2 + INVENTORY->grid_size *
        (INVENTORY->cell_size + INVENTORY->gap) - INVENTORY->gap;
    INVENTORY->pos_x = 50.0f;
    INVENTORY->pos_y = (frame->window_size.y - INVENTORY->inv_height) / 2;
}

static void init_background(frame_t *frame)
{
    INVENTORY->bg = sfRectangleShape_create();
    sfRectangleShape_setFillColor(INVENTORY->bg,
        sfColor_fromRGBA(0, 0, 0, 180));
    sfRectangleShape_setOutlineColor(INVENTORY->bg,
        sfColor_fromRGB(200, 200, 200));
    sfRectangleShape_setOutlineThickness(INVENTORY->bg, 2);
}

static void init_items(frame_t *frame)
{
    for (int i = 0; i < MAX_ITEMS; i++) {
        INVENTORY->items[i].id = -1;
        INVENTORY->items[i].texture = NULL;
        INVENTORY->item_coun[i] = 0;
    }
}

bool init_inventory(frame_t *frame)
{
    PLAYER->inventory = malloc(sizeof(inventory_t));
    if (!PLAYER->inventory)
        return (false);
    INVENTORY->nb_items = 0;
    INVENTORY->is_open = false;
    init_background(frame);
    init_items(frame);
    init_item_buttons(frame);
    init_inventory_infos(frame);
    INVENTORY->font = sfFont_createFromFile(FONTPATH);
    if (!INVENTORY->font)
        return (false);
    INVENTORY->selected_item = -1;
    return (true);
}

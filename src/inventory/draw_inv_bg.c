/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** draw_inv_bg
*/

#include "frame.h"

void draw_inventory_background(frame_t *frame)
{
    sfRectangleShape_setSize(INVENTORY->bg,
        v2f(INVENTORY->inv_width, INVENTORY->inv_height));
    sfRectangleShape_setPosition(INVENTORY->bg,
        v2f(INVENTORY->pos_x, INVENTORY->pos_y));
    sfRenderWindow_drawRectangleShape(WINDOW, INVENTORY->bg, NULL);
}

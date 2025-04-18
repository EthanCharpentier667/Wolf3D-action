/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game
*/

#include "frame.h"

static void draw_items(frame_t *frame)
{
    for (int i = 0; i < NBITEMS; i++)
        draw_item(frame, ITEM[i].pos, ITEM[i].texture, ITEM[i].scale);
}

static void draw_enemies(frame_t *frame)
{
    for (int i = 0; i < NBENEMIES; i++)
        draw_enemy(frame, i);
}

int game(frame_t *frame)
{
    update_player(PLAYER, &(frame->clock[1]), frame);
    cast_floor_ceiling_rays(frame);
    cast_all_rays(frame);
    draw_items(frame);
    draw_enemies(frame);
    return 0;
}

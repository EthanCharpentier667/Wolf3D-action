/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game
*/

#include "frame.h"

int game(frame_t *frame)
{
    update_player(frame, &(frame->clock[1]));
    cast_floor_ceiling_rays(frame);
    cast_all_rays(frame);
    draw_item(frame, v3f(250, 250, 10), MAP->lamptexture, v2f(1, 1));
    return 0;
}

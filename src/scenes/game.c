/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game
*/

#include "frame.h"

int game(frame_t *frame)
{
    update_player(PLAYER, &frame->clock[0]);
    draw_floor_and_ceiling(WINDOW);
    cast_all_rays(frame);
    return 0;
}

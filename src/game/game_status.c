/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_status
*/

#include "frame.h"

int check_game_status(frame_t *frame)
{
    if (PLAYER->life <= 0 || frame->game_over) {
        frame->game_over = true;
        change_scene(frame, GAME_OVER);
        return 1;
    }
    return 0;
}

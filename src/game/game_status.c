/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_status
*/

#include "frame.h"

static void stop_sounds(void)
{
    manage_windup_sound(false);
    manage_firing_sound(false);
    manage_cuting_sound(false);
}

int check_game_status(frame_t *frame)
{
    if (PLAYER->life <= 0 || frame->game_over) {
        stop_sounds();
        frame->game_over = true;
        UI->pause = true;
        change_scene(frame, GAME_OVER);
        return 1;
    }
    return 0;
}

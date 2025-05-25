/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_status
*/

#include "frame.h"

static void stop_sounds(void)
{
    manage_windup_sound(false, 0);
    manage_firing_sound(false, 0);
    manage_cuting_sound(false, 0);
}

int check_game_status(frame_t *frame)
{
    if (PLAYER->life <= 0 || frame->game_over) {
        stop_sounds();
        frame->game_over = true;
        UI->pause = true;
        change_scene(frame, GAME_OVER);
        sfMusic_stop(UI->musics[1].music);
        return 1;
    }
    return 0;
}

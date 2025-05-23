/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** play
*/

#include "frame.h"

int do_resume(frame_t *frame)
{
    UI->pause = false;
    PLAYER->pause = false;
    return 0;
}

int do_play(frame_t *frame)
{
    UI->pause = false;
    PLAYER->pause = false;
    change_scene(frame, GAME);
    frame->game->level = 1;
    frame->played = true;
    sfRenderWindow_setMouseCursorVisible(WINDOW, sfFalse);
    sfMouse_setPositionRenderWindow(v2i(WINDOWX / 2, WINDOWY / 2), WINDOW);
    return 0;
}

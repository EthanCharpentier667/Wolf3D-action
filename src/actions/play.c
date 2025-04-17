/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** play
*/

#include "frame.h"

int do_play(frame_t *frame)
{
    frame->ui->scene = GAME;
    frame->game->level = 1;
    sfRenderWindow_setMouseCursorVisible(WINDOW, sfFalse);
    sfMouse_setPositionRenderWindow(v2i(WINDOWX / 2, WINDOWY / 2), WINDOW);
    return 0;
}

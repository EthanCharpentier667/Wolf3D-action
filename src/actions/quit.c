/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** quit
*/

#include "frame.h"

int do_game_quit(frame_t *frame)
{
    UI->pause = !UI->pause;
    do_save(frame);
    change_scene(frame, MAINMENU);
    sfRenderWindow_setMouseCursorVisible(WINDOW, sfTrue);
    return 0;
}

int do_mm_quit(frame_t *frame)
{
    sfRenderWindow_close(frame->window);
    return 0;
}

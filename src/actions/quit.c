/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** quit
*/

#include "frame.h"

int do_mm_quit(frame_t *frame)
{
    sfRenderWindow_close(frame->window);
    return 0;
}

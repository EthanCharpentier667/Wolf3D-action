/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** resolution
*/

#include "frame.h"

int do_add_resolution(frame_t *frame)
{
    frame->ui->settings->resolution.x = 1200;
    frame->ui->settings->resolution.y = 800;
    sfRenderWindow_setSize(WINDOW, frame->ui->settings->resolution);
    return 0;
}

int do_sub_resolution(frame_t *frame)
{
    frame->ui->settings->resolution.x = 800;
    frame->ui->settings->resolution.y = 600;
    sfRenderWindow_setSize(WINDOW, frame->ui->settings->resolution);
    return 0;
}

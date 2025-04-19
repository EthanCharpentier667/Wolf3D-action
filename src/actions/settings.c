/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** settings
*/

#include "frame.h"

int do_mainmenu(frame_t *frame)
{
    frame->ui->scene = MAINMENU;
    return 0;
}

int do_settings(frame_t *frame)
{
    frame->ui->scene = SETTINGS;
    return 0;
}

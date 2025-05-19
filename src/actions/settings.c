/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** settings
*/

#include "frame.h"

int do_mainmenu(frame_t *frame)
{
    free_save(frame->game->saves, frame);
    frame->ui->scene = MAINMENU;
    return 0;
}

int do_settings(frame_t *frame)
{
    frame->ui->scene = SETTINGS_AUDIO;
    return 0;
}

int do_settings_control(frame_t *frame)
{
    frame->ui->scene = SETTINGS_CONTROLS;
    return 0;
}

int do_settings_video(frame_t *frame)
{
    frame->ui->scene = SETTINGS_RESOLUTION;
    return 0;
}

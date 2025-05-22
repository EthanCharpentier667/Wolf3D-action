/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** settings
*/

#include "frame.h"

int do_goback(frame_t *frame)
{
    free_save(frame->game->saves, frame);
    change_scene(frame, frame->ui->last_scene);
    return 0;
}

int do_settings(frame_t *frame)
{
    change_scene(frame, SETTINGS_AUDIO);
    return 0;
}

int do_settings_control(frame_t *frame)
{
    change_scene(frame, SETTINGS_CONTROLS);
    return 0;
}

int do_settings_video(frame_t *frame)
{
    change_scene(frame, SETTINGS_RESOLUTION);
    return 0;
}

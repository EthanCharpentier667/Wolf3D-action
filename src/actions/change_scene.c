/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** change_scene
*/

#include "frame.h"

void change_scene(frame_t *frame, int scene)
{
    if (scene == frame->ui->scene)
        return;
    if (scene & (SETTINGS_CONTROLS | SETTINGS_RESOLUTION) ||
        UI->scene & (SETTINGS_CONTROLS | SETTINGS_RESOLUTION)) {
        UI->scene = scene;
        return;
    }
    UI->last_scene = UI->scene;
    UI->scene = scene;
}

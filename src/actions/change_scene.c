/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** change_scene
*/

#include "frame.h"

bool change_scene(frame_t *frame, int scene)
{
    if (scene == frame->ui->scene)
        return true;
    if (scene & (SETTINGS_CONTROLS | SETTINGS_RESOLUTION) ||
        UI->scene & (SETTINGS_CONTROLS | SETTINGS_RESOLUTION)) {
        UI->scene = scene;
        return true;
    }
    UI->last_scene = UI->scene;
    UI->scene = scene;
    return false;
}

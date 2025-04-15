/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** scenes_manager
*/

#include "frame.h"

int scene_manager(frame_t *frame)
{
    draw_all(frame);
    switch (UI->scene) {
        case MAINMENU:
            return mainmenu(frame);
        default:
            break;
    }
    return 0;
}

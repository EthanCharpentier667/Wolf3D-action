/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** scenes_manager
*/

#include "frame.h"

int scene_manager(frame_t *frame)
{
    switch (UI->scene) {
        case MAINMENU:
            mainmenu(frame);
            break;
        case GAME:
            game(frame);
            break;
        default:
            break;
    }
    draw_all(frame);
    return 0;
}

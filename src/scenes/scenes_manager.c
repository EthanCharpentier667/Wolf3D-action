/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** scenes_manager
*/

#include "frame.h"

static void enable_buttons(frame_t *frame)
{
    for (int i = 0; BUTTON_INFOS[i].path != NULL; i++) {
        if (BUTTON_INFOS[i].scene == UI->scene) {
            UI->button[i].disabled = false;
        } else {
            UI->button[i].disabled = true;
        }
    }
}

int scene_manager(frame_t *frame)
{
    enable_buttons(frame);
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

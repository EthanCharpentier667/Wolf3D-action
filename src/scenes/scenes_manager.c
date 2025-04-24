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
        if (BUTTON_INFOS[i].scene & UI->scene && UI->button) {
            UI->button[i].disabled = false;
        } else {
            UI->button[i].disabled = true;
        }
    }
}

int scene_manager(frame_t *frame)
{
    draw_images(frame);
    enable_buttons(frame);
    for (int i = 0; SCENES_INFOS[i].scene != END; i++) {
        if (frame->ui->scene & SCENES_INFOS[i].scene) {
            SCENES_INFOS[i].func(frame);
            break;
        }
    }
    draw_all(frame);
    return 0;
}

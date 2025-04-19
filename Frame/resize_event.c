/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** resize_event
*/

#include "frame.h"

void resize_event(frame_t *frame)
{
    static sfVector2u last_size = {1, 1};

    if (frame->event.type == sfEvtResized) {
        last_size = frame->window_size;
        frame->window_size = sfRenderWindow_getSize(WINDOW);
        UI->refactor.x = (float)frame->window_size.x / last_size.x;
        UI->refactor.y = (float)frame->window_size.y / last_size.y;
    }
}

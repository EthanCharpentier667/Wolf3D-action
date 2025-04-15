/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** resize_event
*/

#include "frame.h"

void resize_event(frame_t *frame)
{
    if (frame->event.type == sfEvtResized) {
        frame->window_size = sfRenderWindow_getSize(WINDOW);
    }
}

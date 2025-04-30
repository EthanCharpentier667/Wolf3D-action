/*
** EPITECH PROJECT, 2024
** DuckHuntTest
** File description:
** handle_event
*/
#include <SFML/Graphics.h>
#include <stdio.h>
#include <SFML/Audio.h>
#include "frame.h"
#include <stdlib.h>

int handle_event(sfEvent *event, frame_t *frame)
{
    while (sfRenderWindow_pollEvent(WINDOW, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
        resize_event(frame);
        buttons_event(event, frame);
        handle_slider_events(frame, event);
        handle_inventory_event(frame, event);
    }
    frame->real_mouse = sfMouse_getPosition(NULL);
    frame->mouse = get_mouseposition(WINDOW);
    return 0;
}

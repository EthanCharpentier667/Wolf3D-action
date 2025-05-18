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

static void handle_doors_event(frame_t *frame, sfEvent *event)
{
    static bool e_key_pressed = false;
    bool current_e_key_state = sfKeyboard_isKeyPressed(sfKeyE);

    if (current_e_key_state && !e_key_pressed) {
        interact_with_door(frame);
    }
    e_key_pressed = current_e_key_state;
}

int handle_event(sfEvent *event, frame_t *frame)
{
    frame->real_mouse = sfMouse_getPosition(NULL);
    frame->mouse = get_mouseposition(WINDOW);
    while (sfRenderWindow_pollEvent(WINDOW, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
        resize_event(frame);
        buttons_event(event, frame);
        handle_slider_events(frame, event);
        handle_inventory_event(frame, event);
        handle_doors_event(frame, event);
    }
    return 0;
}

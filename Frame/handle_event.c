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

static void active_cursor(frame_t *frame)
{
    static bool active = false;

    if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
        active = !active;
        sfRenderWindow_setMouseCursorVisible(WINDOW, active);
    }
}

int handle_event(sfEvent *event, frame_t *frame)
{
    while (sfRenderWindow_pollEvent(WINDOW, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
        active_cursor(frame);
        resize_event(frame);
        buttons_event(event, frame);
        frame->mouse = get_mouseposition(WINDOW);
    }
    return 0;
}

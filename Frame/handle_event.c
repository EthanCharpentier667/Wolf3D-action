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
        if (event->type == sfEvtClosed ||
            sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(WINDOW);
        resize_event(frame);
        buttons_event(event, frame);
    }
    frame->mouse = get_mouseposition(WINDOW);
    return 0;
}

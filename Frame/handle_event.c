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

static void handle_pause_event(frame_t *frame)
{
    if (sfKeyboard_isKeyPressed(sfKeyEscape) ||
        sfKeyboard_isKeyPressed(KEYBIND->pause)) {
        PLAYER->pause = !PLAYER->pause;
        UI->pause = !UI->pause;
        if (PLAYER->pause) {
            frame->sceenshot = sfRenderWindow_capture(WINDOW);
            sfRenderWindow_setMouseCursorVisible(WINDOW, true);
            PLAYER->inventory->is_open = false;
        }
    }
}

static void handle_keybinds_event(frame_t *frame, sfEvent *event)
{
    sfKeyCode *key_code = NULL;

    if (frame->ui->settings->keybinding == false)
        return;
    key_code = get_button_keycode(frame, UI->settings->last_action);
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code != sfKeyEscape)
            *key_code = event->key.code;
        frame->ui->settings->keybinding = false;
        UI->settings->last_action = -1;
    }
}

static void handle_doors_event(frame_t *frame)
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
        handle_doors_event(frame);
        handle_keybinds_event(frame, event);
        handle_pause_event(frame);
    }
    return 0;
}

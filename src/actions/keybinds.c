/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** keybinds
*/

#include "frame.h"

int set_keybinds(frame_t *frame, int keybind)
{
    UI->settings->keybinding = true;
    UI->settings->last_action = keybind;
    return 0;
}

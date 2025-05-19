/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_settings
*/

#include "frame.h"

static bool init_keybinds(frame_t *frame)
{
    KEYBIND = malloc(sizeof(keybind_t));
    if (!KEYBIND)
        return false;
    KEYBIND->up = sfKeyZ;
    KEYBIND->down = sfKeyS;
    KEYBIND->left = sfKeyQ;
    KEYBIND->right = sfKeyD;
    KEYBIND->shoot = sfKeyL;
    KEYBIND->interact = sfKeyE;
    KEYBIND->pause = sfKeyP;
    KEYBIND->inventory = sfKeyI;
    return true;
}

bool init_settings(frame_t *frame)
{
    UI->settings = malloc(sizeof(settings_t));
    if (!UI->settings)
        return false;
    UI->settings->music_volume = 0.5f;
    UI->settings->sound_volume = 0.5f;
    UI->settings->resolution = (sfVector2u){WINDOWX, WINDOWY};
    return init_keybinds(frame);
}

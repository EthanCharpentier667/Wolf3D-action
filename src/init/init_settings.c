/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_settings
*/

#include "frame.h"

static bool init_keybinds(frame_t *frame)
{
    UI->settings->keybinds = malloc(sizeof(keybind_t));
    if (!UI->settings->keybinds)
        return false;
    UI->settings->keybinds->up = sfKeyZ;
    UI->settings->keybinds->down = sfKeyS;
    UI->settings->keybinds->left = sfKeyQ;
    UI->settings->keybinds->right = sfKeyD;
    UI->settings->keybinds->shoot = sfKeyP;
    UI->settings->keybinds->interact = sfKeyE;
    UI->settings->keybinds->pause = sfKeyEscape;
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

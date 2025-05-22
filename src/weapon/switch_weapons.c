/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** switch_weapons
*/

#include "frame.h"

void switch_weapon(frame_t *frame, int weapon_index)
{
    int old_index = 0;

    if (weapon_index < 0 || weapon_index >= HUD->nb_weapons)
        return;
    old_index = HUD->selected_weapon;
    if (old_index == weapon_index)
        return;
    HUD->weapon[old_index]->state = WEAPON_IDLE;
    HUD->weapon[old_index]->current_frame = 0;
    HUD->weapon[old_index]->animation_timer = 0;
    HUD->selected_weapon = weapon_index;
}

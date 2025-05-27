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
    weapon_t *current_weapon = HUD->weapon[HUD->selected_weapon];

    if (weapon_index < 0 || weapon_index >= HUD->nb_weapons ||
        (current_weapon->state == WEAPON_ATTACKING ||
        current_weapon->state == WEAPON_FIRING))
        return;
    old_index = HUD->selected_weapon;
    if (old_index == weapon_index)
        return;
    HUD->weapon[old_index]->state = WEAPON_IDLE;
    HUD->weapon[old_index]->current_frame = 0;
    HUD->weapon[old_index]->animation_timer = 0;
    HUD->selected_weapon = weapon_index;
    if (!(HUD->weapon[HUD->selected_weapon]->unlocked))
        HUD->selected_weapon = old_index;
}
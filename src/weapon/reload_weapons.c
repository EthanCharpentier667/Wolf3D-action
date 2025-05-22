/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** reload_weapons
*/

#include "frame.h"

void reload_weapon(frame_t *frame)
{
    weapon_t *weapon = CURRENT_WEAPON;

    if (!weapon || weapon->ammo_capacity == 0)
        return;
    weapon->ammo = weapon->ammo_capacity;
}

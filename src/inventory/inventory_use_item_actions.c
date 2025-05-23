/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** inventory_use_item_actions
*/

#include "frame.h"

int add_life(frame_t *frame, int life)
{
    if ((PLAYER->life >= PLAYER->max_life))
        return 1;
    PLAYER->life += life;
    if (PLAYER->life > PLAYER->max_life)
        PLAYER->life = PLAYER->max_life;
    return 0;
}

int add_ammo(frame_t *frame, int ammo)
{
    weapon_t *weapon = HUD->weapon[HUD->selected_weapon];

    if (weapon->ammo_capacity == 0)
        return 1;
    weapon->ammo += ammo;
    if (weapon->ammo > weapon->ammo_capacity)
        weapon->ammo = weapon->ammo_capacity;
    return 0;
}

void delete_used_item(frame_t *frame, int item_index)
{
    if (item_index < 0 || item_index >= INVENTORY->nb_items)
        return;
    INVENTORY->item_coun[item_index]--;
    if (INVENTORY->item_coun[item_index] <= 0) {
        for (int i = item_index; i < INVENTORY->nb_items - 1; i++) {
            INVENTORY->items[i] = INVENTORY->items[i + 1];
            INVENTORY->item_coun[i] = INVENTORY->item_coun[i + 1];
        }
        INVENTORY->nb_items--;
        INVENTORY->selected_item = -1;
    }
}


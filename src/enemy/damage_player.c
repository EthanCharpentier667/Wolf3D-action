/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** damage_player
*/

#include "frame.h"

void damage_player(frame_t *frame, enemy_t *enemy, int damage)
{
    if (!enemy->can_attack)
        return;
    PLAYER->life -= damage;
    enemy->can_attack = false;
    sfClock_restart(enemy->attack_cd_clock);
}

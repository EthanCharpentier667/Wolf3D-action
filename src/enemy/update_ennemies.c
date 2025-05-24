/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** update_ennemies
*/

#include "frame.h"

static bool handle_enemies(frame_t *frame, enemy_t *enemy)
{
    if (enemy->type == BASIC)
            handle_basic_enemy(frame, enemy);
    if (enemy->type == HITLER || enemy->type == HITLER2)
        if (handle_hitler_enemy(frame, enemy))
            return false;
    return true;
}

void update_enemies(frame_t *frame)
{
    for (int i = 0; i < NBENEMIES; i++) {
        if (!handle_enemies(frame, &ENEMY[i]))
            return;
    }
}

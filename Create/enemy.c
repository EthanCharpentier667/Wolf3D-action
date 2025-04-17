/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** create_enemy
*/

#include "frame.h"

int create_enemy(frame_t *frame, char *str, sfVector2f scale, sfVector3f pos)
{
    if (NBENEMIES == 0)
        ENEMY = malloc(sizeof(enemy_t));
    else
        ENEMY = realloc(ENEMY, sizeof(enemy_t) * (NBENEMIES + 1));
    if (!ENEMY)
        return 84;
    ENEMY[NBENEMIES].texture = sfTexture_createFromFile(str, NULL);
    if (!ENEMY[NBENEMIES].texture)
        return 84;
    ENEMY[NBENEMIES].scale = scale;
    ENEMY[NBENEMIES].pos = pos;
    ENEMY[NBENEMIES].angle = 0;
    ENEMY[NBENEMIES].is_moving = false;
    NBENEMIES++;
    return 0;
}

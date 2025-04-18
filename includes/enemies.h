/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** enemies
*/

#include "frame.h"

#ifndef ENEMIES_H_
    #define ENEMIES_H_

struct enemy_infos_s {
    char *path;
    sfVector2f scale;
    sfVector3f pos;
    sfIntRect rec;
    float speed;
};
extern const struct enemy_infos_s ENEMY_INFOS[];

#endif /* !ENEMIES_H_ */

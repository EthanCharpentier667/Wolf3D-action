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
    int life;
    float attack_range;
    float damages;
    float attack_cooldown;
    char *drop_item;
    int type;
};

enum enemy_type_e {
    BASIC = 1,
    HITLER,
    HITLER2,
};

extern const struct enemy_infos_s ENEMY_INFOS[];

#endif /* !ENEMIES_H_ */

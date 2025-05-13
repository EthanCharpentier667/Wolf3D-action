/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** environnement
*/

#include "frame.h"

#ifndef ENVIRONNEMENT_H_
    #define ENVIRONNEMENT_H_

struct env_infos_s {
    char *texture;
    sfIntRect rec;
    sfVector2f scale;
    bool isrec;
    bool isanimated;
    bool isobstacle;
    int type;
};

extern const struct env_infos_s ENVIRONNEMENT_INFOS[];

#endif /* !ENVIRONNEMENT_H_ */

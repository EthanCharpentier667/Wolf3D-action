/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** item
*/

#include "frame.h"

#ifndef ITEM_H_
    #define ITEM_H_

struct item_infos_s {
    char *path;
    sfVector2f scale;
    sfVector3f pos;
    sfIntRect rec;
    char *name;
    bool pickable;
    bool useable;
    char *description;
};

extern const struct item_infos_s ITEM_INFOS[];

#endif /* !ITEM_H_ */

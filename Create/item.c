/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** item
*/

#include "frame.h"

static int find_id(frame_t *frame)
{
    int id = 0;

    for (int i = 0; i < NBITEMS; i++) {
        if (ITEM[i].id != id)
            break;
        id++;
    }
    return (id);
}

int create_item(frame_t *frame, char *str, sfVector2f scale, sfVector3f pos)
{
    if (NBITEMS == 0)
        ITEM = malloc(sizeof(item_t));
    else
        ITEM = realloc(ITEM, sizeof(item_t) * (NBITEMS + 1));
    if (!ITEM)
        return 84;
    ITEM[NBITEMS].texture = sfTexture_createFromFile(str, NULL);
    if (!ITEM[NBITEMS].texture)
        return 84;
    ITEM[NBITEMS].scale = scale;
    ITEM[NBITEMS].pos = pos;
    ITEM[NBITEMS].id = find_id(frame);
    NBITEMS++;
    return 0;
}

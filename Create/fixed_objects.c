/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** fixed_objects
*/

#include "frame.h"

bool create_fixed_object(frame_t *frame, sfVector3f pos,
    float angle, char *path)
{
    if (NB_FIXED_OBJECTS > 0)
        FIXED_OBJECTS = realloc(FIXED_OBJECTS,
            sizeof(fixed_object_t) * (NB_FIXED_OBJECTS + 1));
    if (!FIXED_OBJECTS)
        return false;
    FIXED_OBJECTS[NB_FIXED_OBJECTS].position = pos;
    FIXED_OBJECTS[NB_FIXED_OBJECTS].angle = angle;
    FIXED_OBJECTS[NB_FIXED_OBJECTS].texture
        = sfTexture_createFromFile(path, NULL);
    if (!FIXED_OBJECTS[NB_FIXED_OBJECTS].texture)
        return false;
    FIXED_OBJECTS[NB_FIXED_OBJECTS].offset = 0;
    return true;
}

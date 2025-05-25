/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_objects
*/

#include "frame.h"

static bool create_objects(frame_t *frame)
{
    for (int i = 0; FIXED_OBJECT_INFOS[i].path; i++) {
        if (!create_fixed_object(frame, FIXED_OBJECT_INFOS[i].position,
            FIXED_OBJECT_INFOS[i].angle, FIXED_OBJECT_INFOS[i].path))
            return false;
        FIXED_OBJECTS[NB_FIXED_OBJECTS].dimensions =
            FIXED_OBJECT_INFOS[i].dimensions;
        FIXED_OBJECTS[NB_FIXED_OBJECTS].solid = FIXED_OBJECT_INFOS[i].solid;
        FIXED_OBJECTS[NB_FIXED_OBJECTS].rec = FIXED_OBJECT_INFOS[i].rec;
        if (FIXED_OBJECTS[NB_FIXED_OBJECTS].solid == DOOR_CLOSED)
            MAP2D[(int)FIXED_OBJECT_INFOS[i].position.y / TILE_SIZE]
                [(int)FIXED_OBJECT_INFOS[i].position.x / TILE_SIZE] = -1;
        NB_FIXED_OBJECTS++;
    }
    return true;
}

bool init_objects(frame_t *frame)
{
    FIXED_OBJECTS = malloc(sizeof(fixed_object_t));
    if (!FIXED_OBJECTS)
        return false;
    NB_FIXED_OBJECTS = 0;
    if (!create_objects(frame))
        return false;
    return true;
}

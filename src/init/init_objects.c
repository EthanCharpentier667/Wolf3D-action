/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_objects
*/

#include "frame.h"

static void place_door_in_map_level(frame_t *frame,
    sfVector3f position, int lvl)
{
    int map_x = (int)(position.x / TILE_SIZE);
    int map_y = (int)(position.y / TILE_SIZE);

    frame->game->levels[lvl].map[map_y][map_x] = -1;
}

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
        FIXED_OBJECTS[NB_FIXED_OBJECTS].lvl = FIXED_OBJECT_INFOS[i].lvl;
        if (FIXED_OBJECTS[NB_FIXED_OBJECTS].solid == DOOR_CLOSED)
            place_door_in_map_level(frame,
                FIXED_OBJECT_INFOS[i].position, FIXED_OBJECT_INFOS[i].lvl);
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

/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** fixed_object
*/

#include "frame.h"

#ifndef FIXED_OBJECT_H_
    #define FIXED_OBJECT_H_

typedef struct fixed_object_s fixed_object_t;

typedef struct segment_data_s {
    float x;
    float y;
    float dist;
    float angle;
    float corrected_dist;
    int screen_x;
    float screen_y;
    float height;
    float light;
} segment_data_t;

typedef struct render_context_s {
    fixed_object_t *object;
    int obj_segments;
    float segment_width;
    float offset_x;
    float offset_y;
    float world_angle;
    float camera_pitch_offset;
} render_context_t;

typedef struct fixed_object_infos_s {
    char *path;
    sfVector3f position;
    float angle;
    sfVector2f dimensions;
    int solid;
    sfIntRect rec;
} fixed_object_infos_t;

extern const fixed_object_infos_t FIXED_OBJECT_INFOS[];

#endif /* !FIXED_OBJECT_H_ */

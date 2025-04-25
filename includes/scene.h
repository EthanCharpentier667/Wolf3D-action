/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** scene
*/

#ifndef SCENE_H_
    #define SCENE_H_

    #include "frame.h"

typedef struct scenes_infos_s {
    int scene;
    int (*func)(frame_t *frame);
} scenes_infos_t;

extern const struct scenes_infos_s SCENES_INFOS[];

#endif /* !SCENE_H_ */

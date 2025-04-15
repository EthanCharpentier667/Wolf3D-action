/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** images
*/

#include "frame.h"

#ifndef IMAGES_H_
    #define IMAGES_H_

typedef enum scenes scenes_t;

struct images_infos_s {
    char *path;
    sfVector2f scale;
    sfVector2f pos;
    int scene;
};

struct images_rec_infos_s {
    char *path;
    sfFloatRect scale_pos;
    sfIntRect rec;
    int scene;
};

extern const struct images_infos_s IMAGES_INFOS[];

extern const struct images_rec_infos_s IMAGES_REC_INFOS[];

#endif /* !IMAGES_H_ */

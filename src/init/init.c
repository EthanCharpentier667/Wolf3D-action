/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** init
*/

#include "frame.h"

static bool create_images(frame_t *frame)
{
    int result = 0;

    for (int i = 0; IMAGES_INFOS[i].path; i++)
        result += create_obj(frame->img, IMAGES_INFOS[i].path,
            IMAGES_INFOS[i].scale, IMAGES_INFOS[i].pos);
    for (int i = 0; IMAGES_REC_INFOS[i].path; i++)
        result += create_rec_obj(frame->img, IMAGES_REC_INFOS[i].path,
            IMAGES_REC_INFOS[i].scale_pos, IMAGES_REC_INFOS[i].rec);
    if (result != 0)
        return false;
    return true;
}

static bool init_images(frame_t *frame)
{
    frame->img = malloc(sizeof(images_t));
    if (!frame->img)
        return false;
    frame->img->nb_img = 0;
    frame->img->img = malloc(sizeof(img_t));
    if (!frame->img->img)
        return false;
    if (!create_images(frame))
        return false;
    applied(frame->img);
    return true;
}

static bool init_clocks(frame_t *frame)
{
    int result = 0;
    int nbclocks = 10;

    CLOCK = malloc(sizeof(clocks_t) * nbclocks);
    if (!CLOCK)
        return false;
    frame->nb_clocks = nbclocks;
    for (int i = 0; i < nbclocks; i++)
        result += create_clock(frame, i);
    if (result != 0)
        return false;
    return true;
}

bool init_frame(frame_t *frame)
{
    WINDOW = create_window(WINDOWX, WINDOWY, "Wolfenstein 3D");
    if (!WINDOW)
        return false;
    sfRenderWindow_clear(WINDOW, sfBlack);
    sfRenderWindow_display(WINDOW);
    sfRenderWindow_setFramerateLimit(WINDOW, 120);
    if (!init_images(frame) || !init_ui(frame) ||
        !init_clocks(frame) || !init_ambiants(frame) ||
        !init_game(frame) || !init_objects(frame)) {
        sfRenderWindow_destroy(WINDOW);
        return false;
    }
    frame->save = NULL;
    frame->name = NULL;
    frame->sceenshot = NULL;
    frame->played = false;
    frame->victory = false;
    frame->game_over = false;
    return true;
}

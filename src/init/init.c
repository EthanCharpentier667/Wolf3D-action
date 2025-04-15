/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** init
*/

#include "frame.h"

static int create_images(frame_t *frame)
{
    int result = 0;

    for (int i = 0; IMAGES_INFOS[i].path; i++)
        result += create_obj(frame->img, IMAGES_INFOS[i].path,
            IMAGES_INFOS[i].scale, IMAGES_INFOS[i].pos);
    for (int i = 0; IMAGES_REC_INFOS[i].path; i++)
        result += create_rec_obj(frame->img, IMAGES_REC_INFOS[i].path,
            IMAGES_REC_INFOS[i].scale_pos, IMAGES_REC_INFOS[i].rec);
    return result;
}

static int init_images(frame_t *frame)
{
    frame->img = malloc(sizeof(images_t));
    if (!frame->img)
        return 84;
    frame->img->nb_img = 0;
    frame->img->img = malloc(sizeof(img_t));
    if (!frame->img->img)
        return 84;
    if (create_images(frame) > 0)
        return 84;
    applied(frame->img);
    return 0;
}

static int init_clocks(frame_t *frame)
{
    int result = 0;
    int nbclocks = 1;

    frame->clock = malloc(sizeof(clocks_t) * nbclocks);
    if (!frame->clock)
        return 84;
    frame->nb_clocks = nbclocks;
    for (int i = 0; i < nbclocks; i++)
        result += create_clock(frame, i);
    if (result > 0)
        return 84;
    return 0;
}

int init_frame(frame_t *frame)
{
    WINDOW = create_window(WINDOWX, WINDOWY, "Wolfenstein 3D");
    if (!WINDOW)
        return 84;
    sfRenderWindow_clear(WINDOW, sfBlack);
    sfRenderWindow_display(WINDOW);
    sfRenderWindow_setFramerateLimit(WINDOW, 120);
    if (init_ui(frame) == 84 || init_images(frame) == 84 ||
        init_clocks(frame) == 84 || init_ambiants(frame) == 84 ||
        init_game(frame) == 84) {
        sfRenderWindow_destroy(WINDOW);
        return 84;
    }
    frame->ui->scene = MAINMENU;
    return 0;
}

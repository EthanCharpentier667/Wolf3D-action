/*
** EPITECH PROJECT, 2025
** BASE
** File description:
** draw
*/

#include "frame.h"

static int draw_buttons(frame_t *frame)
{
    for (int j = 0; BUTTON_INFOS[j].path; j++)
        if (frame->ui->scene == BUTTON_INFOS[j].scene)
            sfRenderWindow_drawSprite(frame->window,
                    UI->button[j].sprite, NULL);
    return 0;
}

static int draw_texts(frame_t *frame)
{
    for (int i = 0; TEXTS_INFOS[i].text; i++)
        if (frame->ui->scene == BUTTON_INFOS[i].scene)
            sfRenderWindow_drawText(frame->window, UI->texts[i].text, NULL);
    return 0;
}

static int draw_images(frame_t *frame)
{
    int i = 0;

    for (i = 0; IMAGES_INFOS[i].path; i++)
        if (frame->ui->scene == IMAGES_INFOS[i].scene)
            sfRenderWindow_drawSprite(frame->window,
                frame->img->img[i].sprite, NULL);
    for (; IMAGES_REC_INFOS[i].path; i++)
        if (frame->ui->scene == IMAGES_REC_INFOS[i].scene)
            sfRenderWindow_drawSprite(frame->window,
                frame->img->img[i].sprite, NULL);
    return 0;
}

int draw_all(frame_t *frame)
{
    draw_buttons(frame);
    draw_texts(frame);
    draw_images(frame);
    return 0;
}

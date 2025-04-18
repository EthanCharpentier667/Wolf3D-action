/*
** EPITECH PROJECT, 2025
** BASE
** File description:
** draw
*/

#include "frame.h"

static void draw_helpboxes(frame_t *frame)
{
    sfVector2f helpboxpos = {frame->mouse.x + 20, frame->mouse.y - 20};

    for (int i = 0; i < frame->ui->nb_buttons; i++)
        if (BUTTON[i].hover == true && BUTTON[i].help_box != NULL) {
            sfRectangleShape_setPosition(BUTTON[i].help_box->box,
                (sfVector2f) {helpboxpos.x - 3, helpboxpos.y});
            sfText_setPosition(BUTTON[i].help_box->text, helpboxpos);
            sfRenderWindow_drawRectangleShape
                (WINDOW, BUTTON[i].help_box->box, NULL);
            sfRenderWindow_drawText(WINDOW, BUTTON[i].help_box->text, NULL);
        }
}

static int draw_buttons(frame_t *frame)
{
    for (int j = 0; BUTTON_INFOS[j].path; j++)
        if (frame->ui->scene == BUTTON_INFOS[j].scene)
            sfRenderWindow_drawSprite(frame->window,
                    UI->button[j].sprite, NULL);
    draw_helpboxes(frame);
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
    draw_images(frame);
    draw_texts(frame);
    draw_buttons(frame);
    return 0;
}

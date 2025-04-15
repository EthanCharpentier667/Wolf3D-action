/*
** EPITECH PROJECT, 2024
** graphic
** File description:
** Destoy_all
*/

#include "frame.h"

static void destroy_images(images_t *img)
{
    for (int i = 0; i < img->nb_img - 1; i++) {
        sfSprite_destroy(img->img[i].sprite);
        sfTexture_destroy(img->img[i].texture);
    }
    free(img->img);
    free(img);
}

static void destroy_clocks(frame_t *frame)
{
    for (int i = 0; i < frame->nb_clocks - 1; i++) {
        sfClock_destroy(frame->clock[i].clock);
    }
    free(frame->clock);
}

static void destroy_texts(ui_t *ui)
{
    for (int i = 0; i < ui->nb_texts; i++) {
        sfText_destroy(ui->texts[i].text);
        sfFont_destroy(ui->texts[i].font);
    }
    free(ui->texts);
}

static void destroy_buttons(ui_t *ui)
{
    for (int i = 0; i < ui->nb_buttons; i++) {
        sfSprite_destroy(ui->button[i].sprite);
        if (ui->button[i].help_box) {
            sfText_destroy(ui->button[i].help_box->text);
            sfFont_destroy(ui->button[i].help_box->font);
            sfRectangleShape_destroy(ui->button[i].help_box->box);
            free(ui->button[i].help_box);
        }
        if (ui->button[i].type == 0) {
            sfTexture_destroy(ui->button[i].texture[0]);
            continue;
        }
        for (int j = 0; j < 4; j++) {
            sfTexture_destroy(ui->button[i].texture[j]);
        }
    }
    free(ui->button);
}

void destroy_all(frame_t *frame)
{
    destroy_images(frame->img);
    destroy_texts(frame->ui);
    destroy_buttons(frame->ui);
    destroy_clocks(frame);
    sfRenderWindow_destroy(frame->window);
    free(frame);
}

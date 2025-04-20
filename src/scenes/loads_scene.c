/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** loads_scene
*/

#include "frame.h"

static void draw_saves(frame_t *frame)
{
    for (int i = 0; i < frame->game->saves->nb_saves; i++) {
        sfRenderWindow_drawSprite(frame->window,
            frame->game->saves->buttons[i].sprite, NULL);
        sfRenderWindow_drawText(frame->window,
            frame->game->saves->texts[i].text, NULL);
    }
    if (frame->game->saves->nb_saves == 0) {
        sfRenderWindow_drawText(frame->window,
            frame->game->saves->texts[0].text, NULL);
    }
}

int load_scene(frame_t *frame)
{
    draw_saves(frame);
    return 0;
}

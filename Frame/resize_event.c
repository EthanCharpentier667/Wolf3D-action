/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** resize_event
*/

#include "frame.h"

static void apply_resize(frame_t *frame)
{
    sfVector2f current_scale = sfSprite_getScale(BUTTON[0].sprite);
    sfVector2f new_scale = {UI->refactor.x, UI->refactor.y};
    sfVector2f current_pos = sfSprite_getPosition(BUTTON[0].sprite);
    sfVector2f pos = {current_pos.x * UI->refactor.x,
        current_pos.y * UI->refactor.y};

    for (int i = 0; i < frame->ui->nb_buttons; i++) {
        current_scale = sfSprite_getScale(BUTTON[i].sprite);
        new_scale = v2f(current_scale.x * UI->refactor.x,
            current_scale.y * UI->refactor.y);
        sfSprite_setScale(BUTTON[i].sprite, new_scale);
        current_pos =
            sfSprite_getPosition(BUTTON[i].sprite);
        pos = v2f(current_pos.x * UI->refactor.x,
            current_pos.y * UI->refactor.y);
        sfSprite_setPosition(BUTTON[i].sprite, pos);
    }
}

void resize_event(frame_t *frame)
{
    static sfVector2u last_size = {1, 1};

    if (frame->event.type == sfEvtResized) {
        last_size = frame->window_size;
        frame->window_size = sfRenderWindow_getSize(WINDOW);
        UI->refactor.x = (float)frame->window_size.x / last_size.x;
        UI->refactor.y = (float)frame->window_size.y / last_size.y;
        apply_resize(frame);
    }
}

/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** update_windows
*/

#include "frame.h"

static char *get_texture_path(int random_value)
{
    switch (random_value) {
        case 0:
            return RES "window.png";
        case 1:
            return RES "window2.png";
        case 2:
            return RES "window3.png";
        case 3:
            return RES "window4.png";
        default:
            return RES "window.png";
    }
}

static void change_all_windows_texture(frame_t *frame)
{
    fixed_object_t *object = NULL;
    int random_value = rand() % 4;

    for (int i = 0; i < NB_FIXED_OBJECTS; i++) {
        object = &frame->game->fixed_objects[i];
        if (object->solid == WINDOW_CLOSED) {
            sfTexture_destroy(object->texture);
            object->texture = sfTexture_createFromFile(
                get_texture_path(random_value), NULL);
        }
        if (!object->texture)
            sfTexture_createFromFile(RES "window.png", NULL);
    }
}

void update_windows(frame_t *frame)
{
    float delta_time = sfTime_asSeconds(frame->clock[6].time);

    frame->clock[6].time = sfClock_getElapsedTime(frame->clock[6].clock);
    if (delta_time > 100.0f) {
        change_all_windows_texture(frame);
        sfClock_restart(frame->clock[6].clock);
    }
}

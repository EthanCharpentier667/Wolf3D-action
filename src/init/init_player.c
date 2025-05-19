/*
** EPITECH PROJECT, 2025
** bswolf3D
** File description:
** init_player
*/

#include "frame.h"

bool init_flashlight(frame_t *frame)
{
    frame->light_map = malloc(sizeof(int *) * MAP_HEIGHT);
    if (!frame->light_map)
        return false;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        frame->light_map[i] = malloc(sizeof(int) * MAP_WIDTH);
        if (!frame->light_map[i])
            return false;
    }
    return true;
}

bool init_player(frame_t *frame)
{
    PLAYER = malloc(sizeof(player_t));
    if (!PLAYER)
        return false;
    PLAYER->pos.x = 100;
    PLAYER->pos.y = 100;
    PLAYER->size = 20;
    PLAYER->angle = (sfVector2f){0, 0};
    PLAYER->fut_angle = (sfVector2f){0, 0};
    PLAYER->speed = 75;
    PLAYER->turn_speed = 3.25;
    PLAYER->flashlight_on = true;
    PLAYER->flashlight_angle = 0.0f;
    PLAYER->flashlight_range = 250.0f;
    PLAYER->flashlight_width = 2 * M_PI;
    PLAYER->flashlight_intensity = 1.0f;
    PLAYER->life = 100;
    PLAYER->max_life = 100;
    return true;
}

/*
** EPITECH PROJECT, 2025
** bswolf3D
** File description:
** init_player
*/

#include "frame.h"

int init_player(frame_t *frame)
{
    PLAYER = malloc(sizeof(player_t));
    if (!PLAYER)
        return 84;
    PLAYER->pos.x = 100;
    PLAYER->pos.y = 100;
    PLAYER->size = 20;
    PLAYER->angle = (sfVector2f){0, 0};
    PLAYER->fut_angle = (sfVector2f){0, 0};
    PLAYER->speed = 75;
    PLAYER->turn_speed = 3.25;
    return 0;
}

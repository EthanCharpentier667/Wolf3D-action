/*
** EPITECH PROJECT, 2025
** bswolf3D
** File description:
** player
*/

#include "frame.h"

float get_delta_time(clocks_t *clock)
{
    float delta_time = 0;

    clock->time = sfClock_getElapsedTime(clock->clock);
    delta_time = sfTime_asSeconds(clock->time);
    sfClock_restart(clock->clock);
    return delta_time;
}

static void check_collisions(sfVector2f new_pos, player_t *player)
{
    if (is_wall(new_pos.x, new_pos.y) == 0 &&
        is_wall(new_pos.x + 10, new_pos.y) == 0 &&
        is_wall(new_pos.x - 10, new_pos.y) == 0 &&
        is_wall(new_pos.x, new_pos.y + 10) == 0 &&
        is_wall(new_pos.x, new_pos.y - 10) == 0) {
        player->pos.x = new_pos.x;
        player->pos.y = new_pos.y;
    }
}

static void move_player(player_t *player)
{
    sfVector2f new_pos = {player->pos.x, player->pos.y};

    if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        new_pos.x += player->dir.x * player->speed * player->delta_time;
        new_pos.y += player->dir.y * player->speed * player->delta_time;
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        new_pos.x -= player->dir.x * player->speed * player->delta_time;
        new_pos.y -= player->dir.y * player->speed * player->delta_time;
    }
    check_collisions(new_pos, player);
}

static void rotate_player(player_t *player)
{
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        player->angle -= player->turn_speed * player->delta_time;
        player->dir.x = cos(player->angle);
        player->dir.y = sin(player->angle);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        player->angle += player->turn_speed * player->delta_time;
        player->dir.x = cos(player->angle);
        player->dir.y = sin(player->angle);
    }
}

void update_player(player_t *player, clocks_t *clock)
{
    player->delta_time = get_delta_time(clock);
    rotate_player(player);
    move_player(player);
}

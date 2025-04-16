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

static bool check_collisions(sfVector2f new_pos)
{
    return (is_wall(new_pos.x, new_pos.y) &&
        is_wall(new_pos.x + 10, new_pos.y) &&
        is_wall(new_pos.x - 10, new_pos.y) &&
        is_wall(new_pos.x, new_pos.y + 10) &&
        is_wall(new_pos.x, new_pos.y - 10));
}

static void rotate_player(player_t *player)
{
    int cam_angle = 0;

    cam_angle = sfKeyboard_isKeyPressed(sfKeyRight) -
        sfKeyboard_isKeyPressed(sfKeyLeft);
    player->angle += cam_angle * player->turn_speed * player->delta_time;
}

static sfVector2f set_walk_pos(sfVector2i move, float angle,
    sfVector2f pos, float speed)
{
    sfVector2f res = {0, 0};
    int input_nb = ((bool)move.x + (bool)move.y);
    bool collision = 1;

    if (!input_nb)
        return res;
    res.x = (cos(angle) * move.x + sin(angle) * move.y) * speed / input_nb;
    res.y = (sin(angle) * move.x + cos(angle) * -1 * move.y)
        * speed / input_nb;
    collision = 1;
    res.x *= collision;
    res.y *= collision;
    return res;
}

static void move_player(player_t *player)
{
    sfVector2i move = {0, 0};
    sfVector2f pos = {0, 0};

    move.x += sfKeyboard_isKeyPressed(sfKeyZ) -
        sfKeyboard_isKeyPressed(sfKeyS);
    move.y += sfKeyboard_isKeyPressed(sfKeyQ) -
        sfKeyboard_isKeyPressed(sfKeyD);
    pos = set_walk_pos(move, player->angle,
        (sfVector2f){player->pos.x, player->pos.y}, player->speed);
    player->pos.x += pos.x * player->delta_time;
    player->pos.y += pos.y * player->delta_time;
}

void update_player(player_t *player, clocks_t *clock)
{
    dprintf(1, "%f %f\n", player->pos.x, player->pos.y);
    player->delta_time = get_delta_time(clock);
    move_player(player);
    rotate_player(player);
}

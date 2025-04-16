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

static bool get_axis_collision(sfVector2f apos, sfVector2f bpos, float size)
{
    size /= 2;
    return is_osbtacle(apos.x, bpos.y) != 0 ||
    is_osbtacle(apos.x + size, bpos.y + size) != 0 ||
    is_osbtacle(apos.x - size, bpos.y - size) != 0 ||
    is_osbtacle(apos.x - size, bpos.y + size) != 0 ||
    is_osbtacle(apos.x + size, bpos.y - size) != 0;
}

static sfVector2i check_collisions(sfVector2f new_pos, sfVector2f old_pos,
    float size)
{
    sfVector2i res = {0, 0};

    res.x = get_axis_collision(new_pos, old_pos, size);
    res.y = get_axis_collision(old_pos, new_pos, size);
    return res;
}

static void rotate_player(player_t *player)
{
    int cam_angle = 0;

    cam_angle = sfKeyboard_isKeyPressed(sfKeyRight) -
        sfKeyboard_isKeyPressed(sfKeyLeft);
    player->angle += cam_angle * player->turn_speed * player->delta_time;
}

static sfVector2f set_walk_pos(sfVector2i move, player_t *player)
{
    sfVector2f res = {0, 0};
    int input_nb = ((bool)move.x + (bool)move.y);
    float angle = player->angle;
    sfVector2f pos = player->pos;
    sfVector2i collision = {0, 0};

    if (!input_nb)
        return res;
    res.x = (cos(angle) * move.x + sin(angle) * move.y);
    res.x *= player->speed * player->delta_time;
    res.y = (sin(angle) * move.x + cos(angle) * -1 * move.y);
    res.y *= player->speed * player->delta_time;
    collision = check_collisions((sfVector2f){pos.x + res.x, pos.y + res.y},
        player->pos, player->size);
    res.x *= !collision.x;
    res.y *= !collision.y;
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
    pos = set_walk_pos(move, player);
    player->pos.x += pos.x;
    player->pos.y += pos.y;
}

void update_player(player_t *player, clocks_t *clock)
{
    player->delta_time = get_delta_time(clock);
    move_player(player);
    rotate_player(player);
}

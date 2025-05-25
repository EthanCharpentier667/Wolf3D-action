/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** update_ennemies
*/

#include "frame.h"

static bool enemy_can_see_player(frame_t *frame, enemy_t *enemy)
{
    float angle_to_player = atan2f(PLAYER->pos.y - enemy->pos.y,
        PLAYER->pos.x - enemy->pos.x);
    float ray_length = 0;
    float ray_step = 0.5f;
    sfVector2f ray_dir = {cos(angle_to_player), sin(angle_to_player)};
    sfVector2f ray_pos = v2f(enemy->pos.x, enemy->pos.y);
    float distance_to_player = sqrtf(powf(PLAYER->pos.x - enemy->pos.x, 2) +
        powf(PLAYER->pos.y - enemy->pos.y, 2));
    int obstacle = 0;

    while (ray_length < distance_to_player) {
        ray_pos.x += ray_dir.x * ray_step;
        ray_pos.y += ray_dir.y * ray_step;
        obstacle = is_osbtacle(frame, ray_pos.x, ray_pos.y);
        if (obstacle > 0) {
            return false;
        }
        ray_length += ray_step;
    }
    return true;
}

static bool handle_enemies(frame_t *frame, enemy_t *enemy)
{
    if (enemy->type == BASIC)
            handle_basic_enemy(frame, enemy);
    if (enemy->type == HITLER || enemy->type == HITLER2)
        if (handle_hitler_enemy(frame, enemy))
            return false;
    return true;
}

void update_enemies(frame_t *frame)
{
    for (int i = 0; i < NBENEMIES; i++) {
        if (!enemy_can_see_player(frame, &ENEMY[i])) {
            ENEMY[i].is_moving = false;
            ENEMY[i].is_attacking = false;
            continue;
        }
        if (!handle_enemies(frame, &ENEMY[i]))
            return;
    }
}

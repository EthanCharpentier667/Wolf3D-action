/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** find_enemy_in_range
*/

#include "frame.h"

static bool is_enemy_valid(const enemy_t *enemy)
{
    return enemy->life > 0 && !enemy->is_dead;
}

static float calculate_distance(const enemy_t *enemy, const player_t *player)
{
    float dist_x = enemy->pos.x - player->pos.x;
    float dist_y = enemy->pos.y - player->pos.y;

    return sqrtf(dist_x * dist_x + dist_y * dist_y);
}

static bool is_in_field_of_view(const enemy_t *enemy, const player_t *player)
{
    float dist_x = enemy->pos.x - player->pos.x;
    float dist_y = enemy->pos.y - player->pos.y;
    float angle_to_enemy = atan2f(dist_y, dist_x);
    float angle_diff =
        fabsf(normalize_weapon_angle(angle_to_enemy - player->angle.x));

    return angle_diff < FOV / 2;
}

static void process_enemy(int index, float *closest_dist,
    enemy_t **closest_enemy, frame_t *frame)
{
    enemy_t *current = &ENEMY[index];
    weapon_t *weapon = HUD->weapon;
    float distance = 0.0f;

    if (!is_enemy_valid(current))
        return;
    distance = calculate_distance(current, PLAYER);
    if (distance >= *closest_dist || distance >= weapon->attack_range)
        return;
    if (!is_in_field_of_view(current, PLAYER))
        return;
    *closest_dist = distance;
    *closest_enemy = current;
}

enemy_t *find_enemy_in_range(frame_t *frame)
{
    float closest_dist = HUD->weapon->attack_range;
    enemy_t *closest_enemy = NULL;

    for (int i = 0; i < NBENEMIES; i++)
        process_enemy(i, &closest_dist, &closest_enemy, frame);
    return closest_enemy;
}

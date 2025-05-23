/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** find_enemy_in_range
*/

#include "frame.h"
#include <limits.h>

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

static float calculate_center_offset(const enemy_t *enemy,
    const player_t *player)
{
    float dist_x = enemy->pos.x - player->pos.x;
    float dist_y = enemy->pos.y - player->pos.y;
    float angle_to_enemy = atan2f(dist_y, dist_x);
    float angle_diff =
        normalize_weapon_angle(angle_to_enemy - player->angle.x);

    return fabsf(angle_diff);
}

static void update_best_target(enemy_target_t *best_target, enemy_t *enemy,
    sfVector3f enm)
{
    if (best_target->enemy == NULL || enm.z < best_target->combined_score) {
        best_target->distance = enm.x;
        best_target->center_offset = enm.y;
        best_target->combined_score = enm.z;
        best_target->enemy = enemy;
    }
}

static void process_enemy(int index, enemy_target_t *best_target,
    frame_t *frame)
{
    enemy_t *current = &ENEMY[index];
    weapon_t *weapon = HUD->weapon[HUD->selected_weapon];
    float distance = 0;
    float center_offset = 0;
    float combined_score = 0;
    float center_weight = 2.0f;

    if (!is_enemy_valid(current))
        return;
    distance = calculate_distance(current, PLAYER);
    if (distance >= weapon->attack_range)
        return;
    center_offset = calculate_center_offset(current, PLAYER);
    if (center_offset >= (FOV - weapon->attack_width) / 2)
        return;
    combined_score = center_offset * center_weight +
        distance / weapon->attack_range;
    update_best_target(best_target, current,
        v3f(distance, center_offset, combined_score));
}

enemy_t *find_enemy_in_range(frame_t *frame)
{
    enemy_target_t best_target = {0};

    best_target.enemy = NULL;
    best_target.combined_score = INT_MAX;
    for (int i = 0; i < NBENEMIES; i++)
        process_enemy(i, &best_target, frame);
    return best_target.enemy;
}

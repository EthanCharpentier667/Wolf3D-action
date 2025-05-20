/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** pathfinding
*/

#include "frame.h"

static void calcul_angle(enemy_t *enemy)
{
    float angle_rad = atan2f(enemy->direction.y, enemy->direction.x);

    enemy->angle = angle_rad * 180.0f / M_PI;
    while (enemy->angle < 0)
        enemy->angle += 360.0f;
    while (enemy->angle >= 360.0f)
        enemy->angle -= 360.0f;
}

static void calculate_direction_to_player(enemy_t *enemy,
    sfVector2f player_pos)
{
    sfVector2f enemy_pos = v2f(enemy->pos.x, enemy->pos.y);
    float dx = player_pos.x - enemy_pos.x;
    float dy = player_pos.y - enemy_pos.y;
    float length = sqrtf(dx * dx + dy * dy);

    if (length < enemy->attack_range || length > 200.0f) {
        enemy->is_moving = false;
        return;
    }
    enemy->direction.x = dx / length;
    enemy->direction.y = dy / length;
    enemy->is_moving = true;
}

static void move_enemy_with_collision(frame_t *frame, enemy_t *enemy)
{
    sfVector2f enemy_pos = v2f(enemy->pos.x, enemy->pos.y);
    sfVector2f new_pos_x = v2f(enemy_pos.x + enemy->direction.x
        * enemy->speed, enemy_pos.y);
    sfVector2f new_pos_y = v2f(enemy_pos.x, enemy_pos.y +
        enemy->direction.y * enemy->speed);

    if (is_osbtacle(frame, new_pos_x.x, new_pos_x.y) == 0)
        enemy->pos.x = new_pos_x.x;
    if (is_osbtacle(frame, new_pos_y.x, new_pos_y.y) == 0)
        enemy->pos.y = new_pos_y.y;
}

void follow_player(frame_t *frame, enemy_t *enemy)
{
    sfVector2f player_pos = v2f(PLAYER->pos.x, PLAYER->pos.y);

    calculate_direction_to_player(enemy, player_pos);
    if (!enemy->is_moving)
        return;
    move_enemy_with_collision(frame, enemy);
    calcul_angle(enemy);
}

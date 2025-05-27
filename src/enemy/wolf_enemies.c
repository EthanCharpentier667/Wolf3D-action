/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** wolf_enemies
*/

#include "frame.h"

static void animate_die(enemy_t *enemy)
{
    float elapsed_time = sfTime_asSeconds(
        sfClock_getElapsedTime(enemy->clock));
    int animation_total = 3;
    float animation_duration = 0.5f;
    int current_frame = (int)(elapsed_time /
        (animation_duration / animation_total));

    if (current_frame >= animation_total)
        current_frame = animation_total - 1;
    enemy->rec.top = enemy->rec.height * 2;
    enemy->rec.left = enemy->rec.width * current_frame;
}

static void handle_die(frame_t *frame, enemy_t *enemy)
{
    int item_index = 0;

    if (enemy->life <= 0 && enemy->is_dead == false) {
        sfClock_restart(enemy->clock);
        item_index = get_item_index(enemy->drop);
        if (item_index >= 0)
            drop_item_at_pos(frame, item_index,
                v2f(enemy->pos.x, enemy->pos.y));
        enemy->is_dead = true;
        enemy->is_moving = false;
        enemy->is_attacking = false;
    }
}

static void animate_enemy(enemy_t *enemy)
{
    float game_time = sfTime_asSeconds(
        sfClock_getElapsedTime(enemy->clock));
    int animation_frame = (int)(game_time * 5.0f) % 4;

    if (enemy->is_moving && !enemy->is_dead) {
        enemy->rec.top = enemy->rec.height;
        enemy->rec.left = animation_frame * enemy->rec.width;
        return;
    } else if (!enemy->is_dead)
        enemy->rec.left = 0;
}

static void animate_attack(frame_t *frame, enemy_t *enemy)
{
    float elapsed_time = sfTime_asSeconds(
        sfClock_getElapsedTime(enemy->clock));
    int animation_total = 3;
    float animation_duration = 0.75f;
    int current_frame = (int)(elapsed_time /
        (animation_duration / animation_total));

    if (current_frame >= animation_total) {
        if (enemy->can_attack)
            damage_player(frame, enemy, enemy->damages);
        sfClock_restart(enemy->clock);
        current_frame = 0;
    }
    enemy->rec.top = enemy->rec.height * 0;
    enemy->rec.left = enemy->rec.width * current_frame;
}

static void handle_attack(frame_t *frame, enemy_t *enemy)
{
    float dx = PLAYER->pos.x - enemy->pos.x;
    float dy = PLAYER->pos.y - enemy->pos.y;
    float length = sqrtf(dx * dx + dy * dy);
    float elapsed = 0.0f;

    if (!enemy->can_attack) {
        elapsed =
            sfTime_asSeconds(sfClock_getElapsedTime(enemy->attack_cd_clock));
        if (elapsed >= enemy->attack_cooldown)
            enemy->can_attack = true;
    }
    if (length >= enemy->attack_range) {
        enemy->is_attacking = false;
        return;
    } else if (length < enemy->attack_range) {
        animate_attack(frame, enemy);
        enemy->is_attacking = true;
        enemy->is_moving = false;
    }
}

void handle_wolf_enemy(frame_t *frame, enemy_t *enemy)
{
    if (enemy->is_dead) {
        animate_die(enemy);
        return;
    }
    animate_enemy(enemy);
    handle_die(frame, enemy);
    handle_attack(frame, enemy);
    if (enemy->follow_player)
        follow_player(frame, enemy);
}

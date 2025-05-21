/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** update_ennemies
*/

#include "frame.h"

static void animate_die(enemy_t *enemy)
{
    float elapsed_time = sfTime_asSeconds(
        sfClock_getElapsedTime(enemy->clock));
    int animation_total = 5;
    float animation_duration = 0.5f;
    int current_frame = (int)(elapsed_time /
        (animation_duration / animation_total));

    if (current_frame >= animation_total)
        current_frame = animation_total - 1;
    enemy->rec.top = enemy->rec.height * 5;
    enemy->rec.left = enemy->rec.width * current_frame;
}

static void handle_die(frame_t *frame, enemy_t *enemy)
{
    int item_index = 0;

    if (enemy->life <= 0 && enemy->is_dead == false) {
        sfClock_restart(enemy->clock);
        item_index = get_item_index(enemy->drop);
        if (item_index > 0)
            drop_item_at_pos(frame, item_index,
                v2f(enemy->pos.x, enemy->pos.y));
        enemy->is_dead = true;
        enemy->is_moving = false;
        enemy->is_attacking = false;
    }
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
    enemy->rec.top = enemy->rec.height * 6;
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
    } else if (length < 75) {
        animate_attack(frame, enemy);
        enemy->is_attacking = true;
        enemy->is_moving = false;
    }
}

void update_enemies(frame_t *frame)
{
    for (int i = 0; i < NBENEMIES; i++) {
        if (ENEMY[i].is_dead) {
            animate_die(&ENEMY[i]);
            continue;
        }
        handle_die(frame, &ENEMY[i]);
        handle_attack(frame, &ENEMY[i]);
        if (ENEMY[i].follow_player)
            follow_player(frame, &ENEMY[i]);
    }
}

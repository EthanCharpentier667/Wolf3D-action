/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** hitler_enemy
*/

#include "frame.h"

static bool create_hitler_enemy(frame_t *frame, sfVector3f pos)
{
    int result = 0;
    static bool first = true;

    if (!first)
        return false;
    result = create_enemy(frame,
        RES"Hitler.png", v2f(2.5, 2.5), v3f(pos.x, pos.y, -1.0f));
    ENEMY[NBENEMIES - 1].rec = irct(0, 0, 60, 62);
    ENEMY[NBENEMIES - 1].max_life = 500;
    ENEMY[NBENEMIES - 1].life = 500;
    ENEMY[NBENEMIES - 1].damages = 20;
    ENEMY[NBENEMIES - 1].attack_range = 100;
    ENEMY[NBENEMIES - 1].attack_cooldown = 1.0f;
    ENEMY[NBENEMIES - 1].speed = 0.75f;
    ENEMY[NBENEMIES - 1].drop = NULL;
    ENEMY[NBENEMIES - 1].type = HITLER2;
    ENEMY[NBENEMIES - 1].id = NBENEMIES - 1;
    first = false;
    return result == 0;
}

static bool animate_die(enemy_t *enemy, int gap)
{
    float elapsed_time = sfTime_asSeconds(
        sfClock_getElapsedTime(enemy->clock));
    int animation_total = 4;
    float animation_duration = 1.0f;
    int current_frame = (int)(elapsed_time /
        (animation_duration / animation_total));

    if (enemy->type == HITLER2)
        animation_total = 6;
    if (current_frame >= animation_total)
        current_frame = animation_total - 1;
    enemy->rec.left = enemy->rec.width * current_frame + gap;
    if (enemy->type == HITLER2)
        enemy->rec.top = enemy->rec.height * 6 + gap;
    else {
        enemy->rec.top = enemy->rec.height * 5 + gap;
    }
    return false;
}

static bool handle_die(frame_t *frame, enemy_t *enemy)
{
    sfVector3f pos = {0};

    if (enemy->life <= 0 && enemy->is_dead == false) {
        sfClock_restart(enemy->clock);
        enemy->is_dead = true;
        enemy->is_moving = false;
        enemy->is_attacking = false;
        pos = v3f(enemy->pos.x, enemy->pos.y, enemy->pos.z + 1);
        if (enemy->type == HITLER) {
            create_hitler_enemy(frame, enemy->pos);
            vfx_explosion(frame, pos, 1);
        }
        if (enemy->type == HITLER2) {
            frame->victory = true;
        }
    }
    return false;
}

static void animate_enemy(enemy_t *enemy, int gap)
{
    float game_time = sfTime_asSeconds(
        sfClock_getElapsedTime(enemy->clock));
    int animation_frame = (int)(game_time * 5.0f) % 4;

    if (enemy->type == HITLER2)
        animation_frame = (int)(game_time * 5.0f) % 6;
    if (enemy->is_moving && !enemy->is_dead) {
        enemy->rec.top = animation_frame * enemy->rec.height + gap;
    } else if (!enemy->is_dead) {
        enemy->rec.left = 0;
        enemy->rec.top = gap;
    }
}

static void animate_attack(frame_t *frame, enemy_t *enemy, int gap)
{
    float elapsed_time = sfTime_asSeconds(
        sfClock_getElapsedTime(enemy->clock));
    int animation_total = 2;
    float animation_duration = 0.75f;
    int current_frame = (int)(elapsed_time /
        (animation_duration / animation_total));

    if (current_frame >= animation_total) {
        if (enemy->can_attack)
            damage_player(frame, enemy, enemy->damages);
        sfClock_restart(enemy->clock);
        current_frame = 0;
    }
    enemy->rec.left = enemy->rec.width;
    enemy->rec.top = enemy->rec.height * current_frame + gap;
}

static void handle_attack(frame_t *frame, enemy_t *enemy, int gap)
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
        animate_attack(frame, enemy, gap);
        enemy->is_attacking = true;
        enemy->is_moving = false;
    }
}

bool handle_hitler_enemy(frame_t *frame, enemy_t *enemy)
{
    int gap = 10;

    if (enemy->type == HITLER2)
        gap = 0;
    if (enemy->is_dead) {
        return animate_die(enemy, gap);
    }
    animate_enemy(enemy, gap);
    handle_attack(frame, enemy, gap);
    if (enemy->follow_player || enemy->type == HITLER2)
        follow_player(frame, enemy);
    handle_die(frame, enemy);
    return false;
}

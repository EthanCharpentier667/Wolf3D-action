/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** update_ennemies
*/

#include "frame.h"

static void animate_die(frame_t *frame, enemy_t *enemy)
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
    if (enemy->life <= 0 && enemy->is_dead == false) {
        sfClock_restart(enemy->clock);
        enemy->is_dead = true;
        enemy->is_moving = false;
        enemy->is_attacking = false;
    }
    if (sfKeyboard_isKeyPressed(sfKeyK)) {
        enemy->life--;
    }
}

void update_enemies(frame_t *frame)
{
    for (int i = 0; i < NBENEMIES; i++) {
        if (ENEMY[i].is_dead) {
            animate_die(frame, &ENEMY[i]);
            continue;
        }
        handle_die(frame, &ENEMY[i]);
        if (ENEMY[i].follow_player)
            follow_player(frame, &ENEMY[i]);
    }
}

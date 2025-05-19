/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** update_weapon
*/

#include "frame.h"

float normalize_weapon_angle(float angle)
{
    while (angle > M_PI)
        angle -= 2 * M_PI;
    while (angle < (- M_PI))
        angle += 2 * M_PI;
    return angle;
}

void damage_enemy(frame_t *frame, enemy_t *enemy, int damage)
{
    enemy->life -= damage;
    if (enemy->life <= 0) {
        enemy->life = 0;
        enemy->is_dead = true;
        ENEMIESALIVE--;
    }
}

static void update_weapon_cooldown(weapon_t *weapon, float delta_time)
{
    if (weapon->attack_cooldown > 0)
        weapon->attack_cooldown -= delta_time;
}

static void handle_idle_state(weapon_t *weapon)
{
    weapon->current_frame = 0;
    if ((sfMouse_isButtonPressed(sfMouseLeft) ||
        sfKeyboard_isKeyPressed(sfKeyL)) &&
        weapon->attack_cooldown <= 0) {
        weapon->state = WEAPON_ATTACKING;
        weapon->animation_timer = 0;
        weapon->current_frame = 0;
    }
}

static void attempt_weapon_damage(frame_t *frame, weapon_t *weapon)
{
    enemy_t *target = find_enemy_in_range(frame);

    if (target)
        damage_enemy(frame, target, weapon->damage);
}

static void handle_attack_state(weapon_t *weapon,
    frame_t *frame, float delta_time)
{
    weapon->animation_timer += delta_time;
    if (weapon->animation_timer >= 0.05f) {
        weapon->animation_timer = 0;
        weapon->current_frame++;
        if (weapon->current_frame == 2)
            attempt_weapon_damage(frame, weapon);
        if (weapon->current_frame >= weapon->total_frames) {
            weapon->state = WEAPON_COOLDOWN;
            weapon->attack_cooldown = 0.3f;
            weapon->current_frame = 0;
            weapon->animation_timer = 0;
        }
    }
}

static void handle_cooldown_state(weapon_t *weapon)
{
    if (weapon->attack_cooldown <= 0) {
        weapon->state = WEAPON_IDLE;
        weapon->current_frame = 0;
    }
}

static void update_weapon_visual(frame_t *frame, weapon_t *weapon)
{
    sfIntRect frame_rect = {
        weapon->current_frame * weapon->frame_width,
        0,
        weapon->frame_width,
        weapon->frame_height
    };
    sfVector2u window_size = sfRenderWindow_getSize(WINDOW);
    sfVector2f weapon_pos = {
        window_size.x / 1.4f - (weapon->frame_width * weapon->scale.x) / 2.0f,
        window_size.y - (weapon->frame_height * weapon->scale.y)
    };

    sfSprite_setTextureRect(weapon->sprite, frame_rect);
    sfSprite_setPosition(weapon->sprite, weapon_pos);
}

void update_weapon(frame_t *frame, float delta_time)
{
    weapon_t *weapon = HUD->weapon;

    update_weapon_cooldown(weapon, delta_time);
    switch (weapon->state) {
        case WEAPON_IDLE:
            handle_idle_state(weapon);
            break;
        case WEAPON_ATTACKING:
            handle_attack_state(weapon, frame, delta_time);
            break;
        case WEAPON_COOLDOWN:
            handle_cooldown_state(weapon);
            break;
    }
    update_weapon_visual(frame, weapon);
}

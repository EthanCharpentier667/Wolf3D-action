/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** Knife weapon behavior
*/

#include "frame.h"

static bool attempt_knife_damage(weapon_t *weapon, frame_t *frame)
{
    enemy_t *target = find_enemy_in_range(frame);

    if (target) {
        damage_enemy(target, weapon->damage);
        return true;
    }
    return false;
}

static void handle_knife_idle(frame_t *frame, weapon_t *weapon)
{
    weapon->current_frame = 0;
    if ((sfMouse_isButtonPressed(sfMouseLeft) ||
        sfKeyboard_isKeyPressed(sfKeyL)) &&
        weapon->attack_cooldown <= 0 &&
        !PLAYER->pause) {
        weapon->state = WEAPON_ATTACKING;
        weapon->animation_timer = 0;
        weapon->current_frame = 0;
    }
}

static void handle_knife_attacking(weapon_t *weapon,
    frame_t *frame, float delta_time)
{
    weapon->animation_timer += delta_time;
    if (weapon->animation_timer >= 0.05f) {
        weapon->animation_timer = 0;
        weapon->current_frame++;
        if (weapon->current_frame == 2)
            attempt_knife_damage(weapon, frame);
        if (weapon->current_frame >= weapon->total_frames) {
            weapon->state = WEAPON_COOLDOWN;
            weapon->attack_cooldown = 0.3f;
            weapon->current_frame = 0;
            weapon->animation_timer = 0;
        }
    }
}

static void handle_knife_cooldown(weapon_t *weapon)
{
    if (weapon->attack_cooldown <= 0) {
        weapon->state = WEAPON_IDLE;
        weapon->current_frame = 0;
    }
}

void update_knife_behavior(weapon_t *weapon,
    frame_t *frame, float delta_time)
{
    if (weapon->attack_cooldown > 0) {
        weapon->attack_cooldown -= delta_time;
    }
    switch (weapon->state) {
        case WEAPON_IDLE:
            handle_knife_idle(frame, weapon);
            break;
        case WEAPON_ATTACKING:
            handle_knife_attacking(weapon, frame, delta_time);
            break;
        case WEAPON_COOLDOWN:
            handle_knife_cooldown(weapon);
            break;
        default:
            weapon->state = WEAPON_IDLE;
            weapon->current_frame = 0;
            break;
    }
}

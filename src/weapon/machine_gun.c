/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** Machine Gun weapon behavior
*/

#include "frame.h"

static bool attempt_machinegun_damage(weapon_t *weapon, frame_t *frame)
{
    enemy_t *target = find_enemy_in_range(frame);

    weapon->ammo--;
    if (target) {
        damage_enemy(target, weapon->damage);
        return true;
    }
    return false;
}

static void handle_machinegun_idle(weapon_t *weapon)
{
    weapon->current_frame = 0;
    if (weapon->is_trigger_held && weapon->ammo > 0 &&
        weapon->attack_cooldown <= 0) {
        weapon->state = WEAPON_WINDUP;
        weapon->animation_timer = 0;
        weapon->windup_timer = 0;
        weapon->current_frame = 0;
    }
}

static void update_windup_animation(weapon_t *weapon)
{
    weapon->current_frame++;
    if (weapon->current_frame >= 2)
        weapon->current_frame = 2;
}

static void handle_machinegun_windup(weapon_t *weapon, float delta_time)
{
    weapon->windup_timer += delta_time;
    weapon->animation_timer += delta_time;
    if (!weapon->is_trigger_held) {
        weapon->state = WEAPON_WINDDOWN;
        weapon->current_frame = 2;
        weapon->animation_timer = 0;
        return;
    }
    if (weapon->animation_timer >= 0.1f) {
        weapon->animation_timer = 0;
        update_windup_animation(weapon);
        if ((weapon->current_frame >= 2) &&
            (weapon->windup_timer >= weapon->windup_time) &&
            (weapon->ammo > 0)) {
            weapon->state = WEAPON_FIRING;
            weapon->current_frame = 0;
        }
    }
}

static void handle_out_of_ammo(weapon_t *weapon)
{
    if (weapon->ammo <= 0) {
        weapon->state = WEAPON_WINDDOWN;
        weapon->current_frame = 2;
        weapon->animation_timer = 0;
    }
}

static void handle_machinegun_firing(weapon_t *weapon,
    frame_t *frame, float delta_time)
{
    float fire_interval = 1.0f / weapon->fire_rate;

    if (!weapon->is_trigger_held || weapon->ammo <= 0) {
        weapon->state = WEAPON_WINDDOWN;
        weapon->current_frame = 2;
        weapon->animation_timer = 0;
        return;
    }
    weapon->animation_timer += delta_time;
    if (weapon->animation_timer >= fire_interval) {
        weapon->animation_timer = 0;
        weapon->current_frame = (weapon->current_frame + 1) % 2;
        if (weapon->current_frame == 0) {
            attempt_machinegun_damage(weapon, frame);
            handle_out_of_ammo(weapon);
        }
    }
}

static void handle_windown(weapon_t *weapon)
{
    if (weapon->current_frame == 2) {
        weapon->current_frame = 3;
    } else if (weapon->current_frame == 3) {
        weapon->current_frame = 0;
        weapon->state = WEAPON_COOLDOWN;
        weapon->attack_cooldown = 0.5f;
    }
}

static void handle_machinegun_winddown(weapon_t *weapon, float delta_time)
{
    weapon->animation_timer += delta_time;
    if (weapon->animation_timer >= 0.1f) {
        weapon->animation_timer = 0;
        handle_windown(weapon);
    }
}

static void handle_machinegun_cooldown(weapon_t *weapon)
{
    if (weapon->attack_cooldown <= 0) {
        weapon->state = WEAPON_IDLE;
        weapon->current_frame = 0;
    }
}

void update_machinegun_behavior(weapon_t *weapon,
    frame_t *frame, float delta_time)
{
    if (weapon->attack_cooldown > 0)
        weapon->attack_cooldown -= delta_time;
    switch (weapon->state) {
        case WEAPON_IDLE:
            handle_machinegun_idle(weapon);
            break;
        case WEAPON_WINDUP:
            handle_machinegun_windup(weapon, delta_time);
            break;
        case WEAPON_FIRING:
            handle_machinegun_firing(weapon, frame, delta_time);
            break;
        case WEAPON_WINDDOWN:
            handle_machinegun_winddown(weapon, delta_time);
            break;
        case WEAPON_COOLDOWN:
            handle_machinegun_cooldown(weapon);
            break;
        default:
    }
}

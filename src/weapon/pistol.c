/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** pistol
*/

#include "frame.h"
#include "weapon.h"

static bool attempt_pistol_damage(weapon_t *weapon, frame_t *frame)
{
    enemy_t *target = find_enemy_in_range(frame);

    weapon->ammo--;
    vfx_bullet_drop(frame, get_front(PLAYER, 21, v3f(0, 0, -0.1)));
    play_sound(frame, 5, 100);
    if (target) {
        damage_enemy(frame, target, weapon->damage);
        return true;
    }
    return false;
}

static void handle_pistol_idle(frame_t *frame, weapon_t *weapon)
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

static void handle_pistol_attacking(weapon_t *weapon,
    frame_t *frame, float delta_time)
{
    if (weapon->ammo <= 0) {
        weapon->state = WEAPON_COOLDOWN;
        weapon->current_frame = 0;
        weapon->animation_timer = 0;
        weapon->attack_cooldown = 0.0f;
    }
    weapon->animation_timer += delta_time;
    if (weapon->animation_timer >= 0.05f) {
        weapon->animation_timer = 0;
        weapon->current_frame++;
        if (weapon->current_frame == 1)
            attempt_pistol_damage(weapon, frame);
        if (weapon->current_frame >= weapon->total_frames) {
            weapon->state = WEAPON_COOLDOWN;
            weapon->attack_cooldown = 0.3f;
            weapon->current_frame = 0;
            weapon->animation_timer = 0;
        }
    }
}

static void handle_pistol_cooldown(weapon_t *weapon)
{
    if (weapon->attack_cooldown <= 0) {
        weapon->state = WEAPON_IDLE;
        weapon->current_frame = 0;
    }
}

void update_pistol_behavior(weapon_t *weapon,
    frame_t *frame, float delta_time)
{
    if (weapon->attack_cooldown > 0)
        weapon->attack_cooldown -= delta_time;
    switch (weapon->state) {
        case WEAPON_IDLE:
            handle_pistol_idle(frame, weapon);
            break;
        case WEAPON_ATTACKING:
            handle_pistol_attacking(weapon, frame, delta_time);
            break;
        case WEAPON_COOLDOWN:
            handle_pistol_cooldown(weapon);
            break;
        default:
            weapon->state = WEAPON_IDLE;
            weapon->current_frame = 0;
            break;
    }
}

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

void damage_enemy(enemy_t *enemy, int damage)
{
    enemy->life -= damage;
}

static void update_weapon_visual(weapon_t *weapon)
{
    sfIntRect frame_rect = {0, 0, 0, 0};

    if (weapon->state == WEAPON_FIRING && weapon->alt_texture) {
        sfSprite_setTexture(weapon->sprite, weapon->alt_texture, sfFalse);
        frame_rect = irct(weapon->current_frame * weapon->frame_width,
            0, weapon->frame_width, weapon->frame_height);
        sfSprite_setTextureRect(weapon->sprite, frame_rect);
    } else {
        sfSprite_setTexture(weapon->sprite, weapon->texture, sfFalse);
        frame_rect = irct(weapon->current_frame * weapon->frame_width,
            0, weapon->frame_width, weapon->frame_height);
        sfSprite_setTextureRect(weapon->sprite, frame_rect);
    }
    sfSprite_setPosition(weapon->sprite, weapon->position);
}

void handle_weapon_input(frame_t *frame)
{
    if (sfKeyboard_isKeyPressed(sfKeyC)) {
        switch_weapon(frame, 0);
    } else if (sfKeyboard_isKeyPressed(sfKeyV)) {
        switch_weapon(frame, 1);
    }
    if (sfKeyboard_isKeyPressed(sfKeyR)) {
        reload_weapon(frame);
    }
}

void update_weapon(frame_t *frame, float delta_time)
{
    weapon_t *weapon = CURRENT_WEAPON;
    bool trigger_pressed = (sfMouse_isButtonPressed(sfMouseLeft) ||
        sfKeyboard_isKeyPressed(sfKeyL)) && !INVENTORY->is_open;

    if (!weapon)
        return;
    handle_weapon_input(frame);
    if (trigger_pressed && !weapon->is_trigger_held)
        weapon->is_trigger_held = true;
    else if (!trigger_pressed && weapon->is_trigger_held)
        weapon->is_trigger_held = false;
    if (weapon->update_behavior)
        weapon->update_behavior(weapon, frame, delta_time);
    update_weapon_visual(weapon);
}

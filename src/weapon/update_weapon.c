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
    sfVector3f pos = enemy->pos;
    float rand = 7;

    enemy->life -= damage;
    pos.x = rand_range(pos.x - rand, pos.x + rand);
    pos.y = rand_range(pos.y - rand, pos.y + rand);
    pos.z = rand_range(pos.z - rand, pos.z + rand) / 100;
    vfx_blood(frame, pos);
    play_sound(frame, 4, 2500 / hypot3f(pos.x - PLAYER->pos.x,
        pos.x - PLAYER->pos.y, pos.z));
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
    if (sfKeyboard_isKeyPressed(sfKeyNum1)) {
        switch_weapon(frame, 0);
    } else if (sfKeyboard_isKeyPressed(sfKeyNum2)) {
        switch_weapon(frame, 1);
    }
    if (frame->event.type == sfEvtMouseWheelScrolled) {
        if (frame->event.mouseWheelScroll.delta > 0)
            switch_weapon(frame, (HUD->selected_weapon + 1) % HUD->nb_weapons);
        else
            switch_weapon(frame, (HUD->selected_weapon - 1 + HUD->nb_weapons)
                % HUD->nb_weapons);
    }
    if (sfKeyboard_isKeyPressed(sfKeyR))
        reload_weapon(frame);
}

void update_weapon(frame_t *frame, float delta_time)
{
    weapon_t *weapon = CURRENT_WEAPON;
    bool trigger_pressed = (sfMouse_isButtonPressed(sfMouseLeft) ||
        sfKeyboard_isKeyPressed(sfKeyL)) && !PLAYER->pause;

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

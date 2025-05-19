/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** weapon
*/

#include "frame.h"

static weapon_t *allocate_weapon(void)
{
    weapon_t *weapon = malloc(sizeof(weapon_t));

    if (!weapon)
        return NULL;
    weapon->texture = NULL;
    weapon->sprite = NULL;
    weapon->name = NULL;
    return weapon;
}

static int load_weapon_texture(weapon_t *weapon, const char *texture_path)
{
    weapon->texture = sfTexture_createFromFile(texture_path, NULL);
    if (!weapon->texture)
        return 84;
    return 0;
}

static int create_weapon_sprite(weapon_t *weapon)
{
    weapon->sprite = sfSprite_create();
    if (!weapon->sprite)
        return 84;
    sfSprite_setTexture(weapon->sprite, weapon->texture, sfTrue);
    return 0;
}

static void set_weapon_properties(weapon_t *weapon, const weapon_infos_t *info)
{
    weapon->rec = info->rec;
    weapon->scale = info->scale;
    weapon->total_frames = info->total_frames;
    weapon->frame_width = info->frame_width;
    weapon->frame_height = info->frame_height;
    weapon->attack_range = info->attack_range;
    weapon->damage = info->damage;
    if (info->name)
        weapon->name = strdup(info->name);
}

static void init_weapon_animation(weapon_t *weapon)
{
    sfIntRect first_frame = {0, 0, weapon->frame_width, weapon->frame_height};

    weapon->current_frame = 0;
    weapon->state = WEAPON_IDLE;
    weapon->animation_timer = 0;
    weapon->attack_cooldown = 0;
    sfSprite_setTextureRect(weapon->sprite, first_frame);
}

static void position_weapon_on_screen(frame_t *frame, weapon_t *weapon)
{
    sfVector2u window_size = sfRenderWindow_getSize(WINDOW);
    sfVector2f weapon_pos = {
        window_size.x / 2.0f - (weapon->frame_width * weapon->scale.x) / 2.0f,
        window_size.y - (weapon->frame_height * weapon->scale.y)
    };

    sfSprite_setPosition(weapon->sprite, weapon_pos);
    sfSprite_setScale(weapon->sprite, weapon->scale);
}

static void cleanup_weapon_on_error(weapon_t *weapon)
{
    if (!weapon)
        return;
    if (weapon->sprite)
        sfSprite_destroy(weapon->sprite);
    if (weapon->texture)
        sfTexture_destroy(weapon->texture);
    if (weapon->name)
        free(weapon->name);
    free(weapon);
}

int create_weapon(frame_t *frame, int weapon_index)
{
    int result = 0;
    const weapon_infos_t *info = &WEAPON_INFOS[weapon_index];
    weapon_t *weapon = allocate_weapon();

    if (!weapon)
        return 84;
    result = load_weapon_texture(weapon, info->texture_path);
    result = create_weapon_sprite(weapon);
    if (result != 0) {
        cleanup_weapon_on_error(weapon);
        return result;
    }
    set_weapon_properties(weapon, info);
    init_weapon_animation(weapon);
    position_weapon_on_screen(frame, weapon);
    HUD->weapon = weapon;
    return 0;
}

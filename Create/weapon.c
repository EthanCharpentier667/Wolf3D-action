/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** weapon
*/

#include "frame.h"

static void set_weapon_behavior(weapon_t *weapon)
{
    switch (weapon->type) {
        case WEAPON_TYPE_MELEE:
            weapon->update_behavior = update_knife_behavior;
            break;
        case WEAPON_TYPE_AUTOMATIC:
            weapon->update_behavior = update_machinegun_behavior;
            break;
        case WEAPON_TYPE_PISTOL:
            weapon->update_behavior = update_pistol_behavior;
            break;
        default:
            weapon->update_behavior = NULL;
    }
}

static bool load_weapon_resources(weapon_t *weapon, const weapon_infos_t *info)
{
    weapon->texture = sfTexture_createFromFile(info->texture_path, NULL);
    if (!weapon->texture)
        return false;
    weapon->alt_texture = NULL;
    if (info->alt_texture_path) {
        weapon->alt_texture =
            sfTexture_createFromFile(info->alt_texture_path, NULL);
        if (!weapon->alt_texture) {
            sfTexture_destroy(weapon->texture);
            return false;
        }
    }
    weapon->sprite = sfSprite_create();
    if (!weapon->sprite) {
        sfTexture_destroy(weapon->texture);
        if (weapon->alt_texture)
            sfTexture_destroy(weapon->alt_texture);
        return false;
    }
    return true;
}

static void copy_weapon_properties(weapon_t *weapon,
    const weapon_infos_t *info)
{
    weapon->scale = info->scale;
    weapon->rec = info->rec;
    weapon->total_frames = info->total_frames;
    weapon->alt_total_frames = info->alt_total_frames;
    weapon->frame_width = info->frame_width;
    weapon->frame_height = info->frame_height;
    weapon->attack_range = info->attack_range;
    weapon->attack_width = info->attack_width;
    weapon->damage = info->damage;
    weapon->ammo_capacity = info->ammo_capacity;
    weapon->ammo = 0;
    weapon->fire_rate = info->fire_rate;
    weapon->windup_time = info->windup_time;
    weapon->type = info->type;
}

static bool set_weapon_name(weapon_t *weapon, const char *name)
{
    if (!name) {
        weapon->name = NULL;
        return true;
    }
    weapon->name = strdup(name);
    return (weapon->name != NULL);
}

static void init_weapon_state(weapon_t *weapon)
{
    weapon->current_frame = 0;
    weapon->state = WEAPON_IDLE;
    weapon->animation_timer = 0;
    weapon->attack_cooldown = 0;
    weapon->windup_timer = 0;
    weapon->is_trigger_held = false;
}

static void configure_weapon_sprite(frame_t *frame, weapon_t *weapon)
{
    sfVector2u window_size = sfRenderWindow_getSize(WINDOW);
    sfIntRect rect = {0, 0, weapon->frame_width, weapon->frame_height};

    weapon->position.x = window_size.x / 1.7f -
        (weapon->frame_width * weapon->scale.x) / 2.0f;
    weapon->position.y = window_size.y -
        (weapon->frame_height * weapon->scale.y);
    sfSprite_setTexture(weapon->sprite, weapon->texture, sfTrue);
    sfSprite_setPosition(weapon->sprite, weapon->position);
    sfSprite_setScale(weapon->sprite, weapon->scale);
    sfSprite_setTextureRect(weapon->sprite, rect);
}

static weapon_t *create_single_weapon(frame_t *frame, int weapon_index)
{
    const weapon_infos_t *info = &WEAPON_INFOS[weapon_index];
    weapon_t *weapon = malloc(sizeof(weapon_t));

    if (!weapon)
        return NULL;
    weapon->texture = NULL;
    weapon->alt_texture = NULL;
    weapon->sprite = NULL;
    weapon->name = NULL;
    if (!load_weapon_resources(weapon, info))
        return NULL;
    copy_weapon_properties(weapon, info);
    if (!set_weapon_name(weapon, info->name))
        return NULL;
    init_weapon_state(weapon);
    set_weapon_behavior(weapon);
    configure_weapon_sprite(frame, weapon);
    return weapon;
}

static weapon_t **allocate_weapon_array(int weapon_count)
{
    weapon_t **weapons = malloc(sizeof(weapon_t *) * weapon_count);

    if (!weapons)
        return NULL;
    for (int i = 0; i < weapon_count; i++)
        weapons[i] = NULL;
    return weapons;
}

static int create_all_weapons(frame_t *frame, int weapon_count)
{
    HUD->weapon = allocate_weapon_array(weapon_count);
    if (!HUD->weapon)
        return 84;
    for (int i = 0; i < weapon_count; i++)
        HUD->weapon[i] = create_single_weapon(frame, i);
    return 0;
}

int create_weapon(frame_t *frame, int start_weapon_index)
{
    int result = 0;
    int weapon_count = 0;

    while (WEAPON_INFOS[weapon_count].texture_path != NULL)
        weapon_count++;
    if (weapon_count == 0)
        return 84;
    result = create_all_weapons(frame, weapon_count);
    if (result != 0)
        return result;
    HUD->nb_weapons = weapon_count;
    HUD->selected_weapon = start_weapon_index;
    return 0;
}

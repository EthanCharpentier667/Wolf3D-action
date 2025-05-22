/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** weapon
*/

#ifndef WEAPON_H_
    #define WEAPON_H_

typedef struct frame_s frame_t;
typedef struct enemy_s enemy_t;
typedef struct weapon_s weapon_t;

typedef enum weapon_type {
    WEAPON_TYPE_MELEE,
    WEAPON_TYPE_AUTOMATIC
} weapon_type_t;

typedef struct weapon_infos_s {
    char *texture_path;
    char *alt_texture_path;
    sfVector2f scale;
    sfIntRect rec;
    int total_frames;
    int alt_total_frames;
    int frame_width;
    int frame_height;
    char *name;
    float attack_range;
    int damage;
    int ammo_capacity;
    float fire_rate;
    float windup_time;
    weapon_type_t type;
} weapon_infos_t;

int create_weapon(frame_t *frame, int weapon_index);
void update_weapon(frame_t *frame, float delta_time);
void update_knife_behavior(weapon_t *weapon, frame_t *frame, float delta_time);
void update_machinegun_behavior(weapon_t *weapon,
    frame_t *frame, float delta_time);
void draw_weapon(frame_t *frame);
enemy_t *find_enemy_in_range(frame_t *frame);
void damage_enemy(frame_t *frame, enemy_t *enemy, int damage);
float normalize_weapon_angle(float angle);
void switch_weapon(frame_t *frame, int weapon_index);
void reload_weapon(frame_t *frame);

extern const struct weapon_infos_s WEAPON_INFOS[];

#endif /* !WEAPON_H_ */

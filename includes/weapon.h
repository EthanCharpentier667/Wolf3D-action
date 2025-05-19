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

typedef struct weapon_infos_s {
    char *texture_path;
    sfVector2f scale;
    sfIntRect rec;
    int total_frames;
    int frame_width;
    int frame_height;
    char *name;
    float attack_range;
    int damage;
} weapon_infos_t;

int create_weapon(frame_t *frame, int weapon_index);
void update_weapon(frame_t *frame, float delta_time);
void draw_weapon(frame_t *frame);
enemy_t *find_enemy_in_range(frame_t *frame);
void damage_enemy(frame_t *frame, enemy_t *enemy, int damage);
float normalize_weapon_angle(float angle);

extern const struct weapon_infos_s WEAPON_INFOS[];

#endif /* !WEAPON_H_ */

/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** load_enemies_data
*/

#include "frame.h"

static enemy_t *allocate_temporary_enemies(int num_enemies)
{
    if (num_enemies <= 0)
        return NULL;
    return malloc(sizeof(enemy_t) * (size_t)num_enemies);
}

static bool read_enemies_from_file(FILE *file,
    enemy_t *enemies_temp, int num_enemies)
{
    size_t read_count = 0;

    if (num_enemies <= 0)
        return true;
    if (!enemies_temp)
        return false;
    read_count = fread(enemies_temp, sizeof(enemy_t),
        (size_t)num_enemies, file);
    return (read_count == (size_t)num_enemies);
}

static bool initialize_enemy_resources(enemy_t *enemy, enemy_t *enemies_temp)
{
    enemy->angle = enemies_temp->angle;
    enemy->pos = enemies_temp->pos;
    enemy->scale = enemies_temp->scale;
    enemy->direction = enemies_temp->direction;
    enemy->speed = enemies_temp->speed;
    enemy->damages = enemies_temp->damages;
    enemy->attack_range = enemies_temp->attack_range;
    enemy->follow_range = enemies_temp->follow_range;
    enemy->attack_cooldown = enemies_temp->attack_cooldown;
    enemy->is_moving = enemies_temp->is_moving;
    enemy->follow_player = enemies_temp->follow_player;
    enemy->is_attacking = enemies_temp->is_attacking;
    enemy->is_dead = enemies_temp->is_dead;
    enemy->life = enemies_temp->life;
    enemy->max_life = enemies_temp->max_life;
    enemy->type = enemies_temp->type;
    enemy->id = enemies_temp->id;
    enemy->can_attack = enemies_temp->can_attack;
    return true;
}

static bool initialize_enemy_resources_all(frame_t *frame,
    enemy_t *enemies_temp)
{
    int num_enemies = frame->game->nb_enemies;

    if (num_enemies <= 0 || !frame->game->enemies)
        return true;
    for (int i = 0; i < num_enemies; i++)
        initialize_enemy_resources(&ENEMY[i], &enemies_temp[i]);
    return true;
}

static void cleanup_temporary_enemies(enemy_t *enemies_temp)
{
    if (enemies_temp)
        free(enemies_temp);
}

bool load_enemies_data(frame_t *frame, FILE *file)
{
    int num_enemies = frame->game->nb_enemies;
    enemy_t *enemies_temp = NULL;

    enemies_temp = allocate_temporary_enemies(num_enemies);
    if (!enemies_temp && num_enemies > 0)
        return false;
    if (!read_enemies_from_file(file, enemies_temp, num_enemies)) {
        cleanup_temporary_enemies(enemies_temp);
        return false;
    }
    if (!initialize_enemy_resources_all(frame, enemies_temp)) {
        cleanup_temporary_enemies(enemies_temp);
        return false;
    }
    cleanup_temporary_enemies(enemies_temp);
    return true;
}

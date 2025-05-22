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

static bool allocate_game_enemies(frame_t *frame)
{
    int num_enemies = frame->game->nb_enemies;

    if (num_enemies <= 0)
        return true;
    if (frame->game->enemies)
        free(frame->game->enemies);
    frame->game->enemies = malloc(sizeof(enemy_t) * (size_t)num_enemies);
    return (frame->game->enemies != NULL);
}

static void copy_enemies_to_game(frame_t *frame, enemy_t *enemies_temp)
{
    int num_enemies = frame->game->nb_enemies;

    if (num_enemies <= 0 || !enemies_temp || !frame->game->enemies)
        return;
    memcpy(frame->game->enemies, enemies_temp,
        sizeof(enemy_t) * (size_t)num_enemies);
    frame->game->nb_enemies = frame->game->nb_enemies;
    frame->game->nb_enemies_alive = frame->game->nb_enemies_alive;
}

static bool initialize_enemy_resources(enemy_t *enemy, int enemy_index)
{
    enemy->texture =
        sfTexture_createFromFile(ENEMY_INFOS[enemy_index].path, NULL);
    if (!enemy->texture)
        return false;
    enemy->clock = sfClock_create();
    enemy->attack_cd_clock = sfClock_create();
    enemy->drop = strdup(ENEMY_INFOS[enemy_index].drop_item);
    if (!enemy->clock || !enemy->attack_cd_clock ||
        !enemy->drop) {
        if (enemy->texture)
            sfTexture_destroy(enemy->texture);
        if (enemy->clock)
            sfClock_destroy(enemy->clock);
        if (enemy->attack_cd_clock)
            sfClock_destroy(enemy->attack_cd_clock);
        return false;
    }
    return true;
}

static void destroy_already_created_enemies(frame_t *frame, int i)
{
    for (int j = 0; j < i; j++) {
        sfTexture_destroy(ENEMY[j].texture);
        sfClock_destroy(ENEMY[j].clock);
        sfClock_destroy(ENEMY[j].attack_cd_clock);
        free(ENEMY[j].drop);
    }
}

static bool initialize_enemy_resources_all(frame_t *frame)
{
    int num_enemies = frame->game->nb_enemies;

    if (num_enemies <= 0 || !frame->game->enemies)
        return true;
    for (int i = 0; i < num_enemies; i++) {
        if (!initialize_enemy_resources(&ENEMY[i], i)) {
            destroy_already_created_enemies(frame, i);
            return false;
        }
    }
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
    if (!read_enemies_from_file(file, enemies_temp, num_enemies) ||
        !allocate_game_enemies(frame)) {
        cleanup_temporary_enemies(enemies_temp);
        return false;
    }
    copy_enemies_to_game(frame, enemies_temp);
    if (!initialize_enemy_resources_all(frame)) {
        cleanup_temporary_enemies(enemies_temp);
        return false;
    }
    cleanup_temporary_enemies(enemies_temp);
    return true;
}

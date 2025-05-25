/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** load_frame
*/

#include "frame.h"

static char *load_game_infos(FILE *file)
{
    game_infos_t game_infos_temp;

    if (fread(&game_infos_temp, sizeof(game_infos_t), 1, file) != 1) {
        fprintf(stderr, "Error reading game_infos\n");
        fclose(file);
        return NULL;
    }
    return strdup(game_infos_temp.name);
}

static bool load_frame_data(frame_t *frame, FILE *file)
{
    frame_t frame_temp;

    if (fread(&frame_temp, sizeof(frame_t), 1, file) != 1) {
        fprintf(stderr, "Error reading frame data\n");
        return false;
    }
    frame->played = frame_temp.played;
    return true;
}

static bool load_game_data(frame_t *frame, FILE *file)
{
    game_t game_temp;

    if (fread(&game_temp, sizeof(game_t), 1, file) != 1) {
        fprintf(stderr, "Error reading game data\n");
        return false;
    }
    frame->game->nb_fixed_objects = game_temp.nb_fixed_objects;
    frame->game->nb_items = game_temp.nb_items;
    frame->game->nb_enemies = game_temp.nb_enemies;
    frame->game->nb_enemies_alive = game_temp.nb_enemies_alive;
    frame->game->level = game_temp.level;
    frame->game->timer = game_temp.timer;
    frame->game->difficulty = game_temp.difficulty;
    return true;
}

static bool load_player_data(frame_t *frame, FILE *file)
{
    player_t player_temp;

    if (fread(&player_temp, sizeof(player_t), 1, file) != 1) {
        fprintf(stderr, "Error reading player data\n");
        return false;
    }
    PLAYER->pos = player_temp.pos;
    PLAYER->angle = player_temp.angle;
    PLAYER->max_life = player_temp.max_life;
    PLAYER->life = player_temp.life;
    PLAYER->speed = player_temp.speed;
    PLAYER->turn_speed = player_temp.turn_speed;
    PLAYER->flashlight_on = player_temp.flashlight_on;
    PLAYER->flashlight_angle = player_temp.flashlight_angle;
    PLAYER->flashlight_range = player_temp.flashlight_range;
    PLAYER->flashlight_width = player_temp.flashlight_width;
    PLAYER->flashlight_intensity = player_temp.flashlight_intensity;
    return true;
}

static bool load_environment_data(frame_t *frame, FILE *file)
{
    environment_ray_t *env_temp = malloc(sizeof(environment_ray_t) *
        frame->game->nb_env);

    if (!env_temp)
        return false;
    if (fread(env_temp, sizeof(environment_ray_t), frame->game->nb_env, file)
            != (unsigned long) frame->game->nb_env)
        return false;
    free(env_temp);
    return true;
}

static bool load_ui_data(frame_t *frame, FILE *file)
{
    ui_t ui_temp;
    settings_t settings_temp;
    keybind_t keybind_temp;

    if (fread(&ui_temp, sizeof(ui_t), 1, file) != 1 ||
        fread(&settings_temp, sizeof(settings_t), 1, file) != 1 ||
        fread(&keybind_temp, sizeof(keybind_t), 1, file) != 1)
        return false;
    UI->settings->music_volume = settings_temp.music_volume;
    UI->settings->sound_volume = settings_temp.sound_volume;
    UI->settings->resolution = settings_temp.resolution;
    UI->settings->keybinds->up = keybind_temp.up;
    UI->settings->keybinds->down = keybind_temp.down;
    UI->settings->keybinds->left = keybind_temp.left;
    UI->settings->keybinds->right = keybind_temp.right;
    UI->settings->keybinds->interact = keybind_temp.interact;
    UI->settings->keybinds->pause = keybind_temp.pause;
    UI->settings->keybinds->inventory = keybind_temp.inventory;
    return true;
}

static bool load_weapons_data(frame_t *frame, FILE *file)
{
    weapon_t weapons_temp;
    hud_t hud_temp;

    for (int i = 0; i < HUD->nb_weapons; i++)
        if (fread(&weapons_temp, sizeof(weapon_t), 1, file) == 1)
            HUD->weapon[i]->ammo = weapons_temp.ammo;
    if (fread(&hud_temp, sizeof(hud_t), 1, file) != 1)
        return false;
    HUD->selected_weapon = hud_temp.selected_weapon;
    return true;
}

static void restore_pointer(frame_t *frame)
{
    UI->pause_menu->background = &(frame->img->img[4]);
    UI->pause_menu->logo = &(frame->img->img[5]);
    UI->pause_menu->resume = &(BUTTON[11]);
    UI->pause_menu->settings = &(BUTTON[12]);
    UI->pause_menu->quit = &(BUTTON[10]);
}

bool load_frame(frame_t *frame, char *save)
{
    FILE *file = fopen(save, "r");

    if (!file)
        return false;
    frame->name = load_game_infos(file);
    if (!load_frame_data(frame, file) || !load_game_data(frame, file) ||
        !load_map_data(frame, file) || !load_player_data(frame, file) ||
        !load_inventory_data(frame, file) || !frame->name ||
        !load_environment_data(frame, file) || !load_objects_data(frame, file)
        || !load_items_data(frame, file) || !load_enemies_data(frame, file)
        || !load_ui_data(frame, file) || !load_weapons_data(frame, file)) {
        fclose(file);
        return false;
    }
    restore_pointer(frame);
    fclose(file);
    return true;
}

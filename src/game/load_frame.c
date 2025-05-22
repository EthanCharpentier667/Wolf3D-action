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
    return true;
}

static bool load_map_data(frame_t *frame, FILE *file)
{
    map_t map_temp;
    int map[MAP_HEIGHT][MAP_WIDTH];

    if (fread(&map_temp, sizeof(map_t), 1, file) != 1)
        return false;
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (fread(&map[i][j], sizeof(int), 1, file) != 1)
                return false;
            MAP2D[i][j] = map[i][j];
        }
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

static bool load_inventory_data(frame_t *frame, FILE *file)
{
    inventory_t inventory_temp;

    if (fread(&inventory_temp, sizeof(inventory_t), 1, file) != 1) {
        fprintf(stderr, "Error reading inventory data\n");
        return false;
    }
    if (PLAYER->inventory && inventory_temp.nb_items <= MAX_ITEMS) {
        PLAYER->inventory->nb_items = inventory_temp.nb_items;
        for (int i = 0; i < inventory_temp.nb_items; i++) {
            PLAYER->inventory->items[i] = inventory_temp.items[i];
            for (int j = 0; ITEM_INFOS[j].path; j++) {
                if (strcmp(PLAYER->inventory->items[i].name, ITEM_INFOS[j].name) == 0) {
                    PLAYER->inventory->items[i].texture = sfTexture_createFromFile(ITEM_INFOS[j].path, NULL);
                    break;
                }
            }
            PLAYER->inventory->item_coun[i] = inventory_temp.item_coun[i];
        }
        PLAYER->inventory->selected_item = inventory_temp.selected_item;
    }
    return true;
}

static bool load_environment_data(frame_t *frame, FILE *file)
{
    environment_ray_t *env_temp = malloc(sizeof(environment_ray_t) * frame->game->nb_env);

    if (!env_temp)
        return false;
    if (fread(env_temp, sizeof(environment_ray_t), frame->game->nb_env, file)
            != (unsigned long) frame->game->nb_env)
        return false;
    return true;
}

static bool load_objects_data(frame_t *frame, FILE *file)
{
    fixed_object_t *fixed_objects_temp = malloc(sizeof(fixed_object_t) *
        (unsigned long) frame->game->nb_fixed_objects);

    if (!fixed_objects_temp && frame->game->nb_fixed_objects > 0)
        return false;
    if (fread(fixed_objects_temp, sizeof(fixed_object_t),
            frame->game->nb_fixed_objects, file)
            != (unsigned long) frame->game->nb_fixed_objects
            && frame->game->nb_fixed_objects > 0)
        return false;
    frame->game->fixed_objects = fixed_objects_temp;
    if (frame->game->nb_fixed_objects > 0 && fixed_objects_temp) {
        if (frame->game->fixed_objects)
            free(frame->game->fixed_objects);
        frame->game->fixed_objects = malloc(sizeof(fixed_object_t) * frame->game->nb_fixed_objects);
        if (frame->game->fixed_objects) {
            memcpy(frame->game->fixed_objects, fixed_objects_temp, sizeof(fixed_object_t) * frame->game->nb_fixed_objects);
            frame->game->nb_fixed_objects = frame->game->nb_fixed_objects;
        }
        for (int i = 0; i < frame->game->nb_fixed_objects; i++) {
            frame->game->fixed_objects[i].texture = sfTexture_createFromFile(FIXED_OBJECT_INFOS[i].path, NULL);
            if (!frame->game->fixed_objects[i].texture) {
                return NULL;
            }
        }
    }
    return true;
}

static bool load_items_data(frame_t *frame, FILE *file)
{
    item_t *items_temp = malloc(sizeof(item_t) * frame->game->nb_items);

    if (!items_temp && frame->game->nb_items > 0)
        return false;
    if (fread(items_temp, sizeof(item_t), frame->game->nb_items, file)
            != (unsigned long) frame->game->nb_items && frame->game->nb_items > 0)
        return false;
    if (frame->game->nb_items > 0 && items_temp) {
        if (frame->game->items) {
            free(frame->game->items);
        }
        frame->game->items = malloc(sizeof(item_t) * frame->game->nb_items);
        if (frame->game->items) {
            memcpy(frame->game->items, items_temp, sizeof(item_t) * frame->game->nb_items);
            NBITEMS = frame->game->nb_items;
            for (int i = 0; i < NBITEMS; i++) {
                strcpy(ITEM[i].name, items_temp[i].name);
                strcpy(ITEM[i].description, items_temp[i].description);
                ITEM[i].texture = NULL;
                for (int j = 0; ITEM_INFOS[j].path; j++) {
                    if (strcmp(ITEM[i].name, ITEM_INFOS[j].name) == 0) {
                        ITEM[i].texture = sfTexture_createFromFile(ITEM_INFOS[j].path, NULL);
                        break;
                    }
                }
                if (!ITEM[i].texture) {
                    return NULL;
                }
            }
        }
    }
    return true;
}

static bool load_enemies_data(frame_t *frame, FILE *file)
{
    enemy_t *enemies_temp = malloc(sizeof(enemy_t) * frame->game->nb_enemies);

    if (!enemies_temp && frame->game->nb_enemies > 0)
        return false;
    if (fread(enemies_temp, sizeof(enemy_t), frame->game->nb_enemies, file)
            != (unsigned long) frame->game->nb_enemies && frame->game->nb_enemies > 0)
        return false;
    memccpy(frame->game->enemies, enemies_temp, sizeof(enemy_t), frame->game->nb_enemies);
    if (frame->game->nb_enemies > 0 && enemies_temp) {
        if (frame->game->enemies)
            free(frame->game->enemies);
        frame->game->enemies = malloc(sizeof(enemy_t) * frame->game->nb_enemies);
        if (frame->game->enemies) {
            memcpy(frame->game->enemies, enemies_temp, sizeof(enemy_t) * frame->game->nb_enemies);
            frame->game->nb_enemies = frame->game->nb_enemies;
            frame->game->nb_enemies_alive = frame->game->nb_enemies_alive;
            for (int i = 0; i < NBENEMIES; i++) {
                ENEMY[i].texture = sfTexture_createFromFile(ENEMY_INFOS[i].path, NULL);
                ENEMY[i].clock = sfClock_create();
                ENEMY[i].attack_cd_clock = sfClock_create();
                ENEMY[i].drop = strdup(ENEMY_INFOS[i].drop_item);
                if (!ENEMY[i].texture) {
                    return NULL;
                }
            }
        }
    }
    return true;
}

static bool load_ui_data(frame_t *frame, FILE *file)
{
    ui_t ui_temp;
    settings_t settings_temp;
    keybind_t keybind_temp;

    if (fread(&ui_temp, sizeof(ui_t), 1, file) != 1)
        return false;
    if (fread(&settings_temp, sizeof(settings_t), 1, file) != 1)
        return false;
    if (fread(&keybind_temp, sizeof(keybind_t), 1, file) != 1)
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
    frame->save = strdup(save);
    return true;
}
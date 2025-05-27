/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** save
*/

#include "frame.h"
#include <time.h>

static void write_level_maps(frame_t *frame, FILE *file, int x)
{
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            fwrite(&LEVELS[x].map[i][j], sizeof(int), 1, file);
        }
    }
}

static void write_frame(frame_t *frame, FILE *file)
{
    fwrite(frame, sizeof(frame_t), 1, file);
    fwrite(frame->game, sizeof(game_t), 1, file);
    fwrite(frame->game->map, sizeof(map_t), 1, file);
    for (int i = 0; i < NBLEVELS; i++)
        write_level_maps(frame, file, i);
    fwrite(PLAYER, sizeof(player_t), 1, file);
    fwrite(PLAYER->inventory, sizeof(inventory_t), 1, file);
    fwrite(frame->game->environment, sizeof(environment_ray_t),
        frame->game->nb_env, file);
    fwrite(frame->game->fixed_objects, sizeof(fixed_object_t),
        frame->game->nb_fixed_objects, file);
    fwrite(frame->game->items, sizeof(item_t), NBITEMS, file);
    fwrite(frame->game->enemies, sizeof(enemy_t),
        frame->game->nb_enemies, file);
    fwrite(UI, sizeof(ui_t), 1, file);
    fwrite(UI->settings, sizeof(settings_t), 1, file);
    fwrite(UI->settings->keybinds, sizeof(keybind_t), 1, file);
    for (int i = 0; i < HUD->nb_weapons; i++)
        fwrite(HUD->weapon[i], sizeof(weapon_t), 1, file);
}

static void write_save_file(frame_t *frame, FILE *file)
{
    time_t current_time;
    char *save_image = NULL;
    game_infos_t game_infos;

    time(&current_time);
    strftime(game_infos.date, sizeof(game_infos.date), "%Y-%m-%d %H:%M:%S",
        localtime(&current_time));
    strncpy(game_infos.name, frame->name, sizeof(game_infos.name) - 1);
    fwrite(&game_infos, sizeof(game_infos_t), 1, file);
    write_frame(frame, file);
    fwrite(HUD, sizeof(hud_t), 1, file);
    save_image = malloc(sizeof(char) * (strlen(frame->name) +
        strlen("sswolfs/save-.png") + 1));
    snprintf(save_image, sizeof(char) * (strlen(frame->name) +
        strlen("sswolfs/save-.png") + 1),
        "sswolfs/save-%s.png", frame->name);
    if (frame->sceenshot)
        sfImage_saveToFile(frame->sceenshot, save_image);
    free(save_image);
}

void create_save_directory(void)
{
    struct stat st = {0};

    if (stat("sswolfs", &st) == -1) {
        mkdir("sswolfs", 0700);
    }
}

static bool save_game(frame_t *frame)
{
    FILE *file = NULL;
    char *save = malloc(sizeof(char) * (strlen(frame->name) +
        strlen("sswolfs/save-.ww2") + 1));

    if (!frame->name)
        frame->name = "EthanLeGrand";
    snprintf(save, (strlen(frame->name) + strlen("sswolfs/save-.ww2") + 1),
        "sswolfs/save-%s.ww2", frame->name);
    file = fopen(save, "w+");
    if (file == NULL)
        return false;
    write_save_file(frame, file);
    fclose(file);
    free(save);
    return true;
}

static void delete_save(char *save, char *name)
{
    char image_path[256];

    if (!save)
        save = "sswolfs/save-EthanLeGrand.ww2";
    if (!name)
        name = "EthanLeGrand";
    snprintf(image_path, sizeof(image_path),
        "sswolfs/save-%s.png", name);
    if (remove(save) != 0)
        fprintf(stderr, "Error deleting save file: %s\n", save);
    if (remove(image_path) != 0)
        fprintf(stderr, "Error deleting save image: %s\n", image_path);
}

int do_save(frame_t *frame)
{
    create_save_directory();
    if (frame->victory) {
        delete_save(frame->save, frame->name);
        return 0;
    }
    if (frame->game_over)
        return 0;
    return save_game(frame);
}

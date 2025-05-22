/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_game
*/

#include "frame.h"

/*const int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 2, 1, 1, 1, 1},
    {3, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 4},
    {1, 0, 0, 0, 0, 0, 0, 4},
    {3, 0, 1, 0, 0, 1, 0, 3},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 3, 1, 1, 1, 1}
};*/

const int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 2, 1, 1, 1, 1, 3, 2, 3, 1, 1, 1, 1, 1},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 2, 1, 1, 1, 1, 3, 2, 3, 1, 1, 1, 1, 1}
};

static bool init_environment(frame_t *frame)
{
    int result = 0;

    frame->game->environment = malloc(sizeof(environment_ray_t));
    if (!frame->game->environment)
        return false;
    frame->game->nb_env = 0;
    for (int i = 0; ENVIRONNEMENT_INFOS[i].texture; i++) {
        result += create_environment(frame, ENVIRONNEMENT_INFOS[i].texture,
            ENVIRONNEMENT_INFOS[i].rec, ENVIRONNEMENT_INFOS[i].scale);
        frame->game->environment[frame->game->nb_env - 1].isanimated =
            ENVIRONNEMENT_INFOS[i].isanimated;
        frame->game->environment[frame->game->nb_env - 1].isobstacle =
            ENVIRONNEMENT_INFOS[i].isobstacle;
        frame->game->environment[frame->game->nb_env - 1].type =
            ENVIRONNEMENT_INFOS[i].type;
    }
    if (result != 0)
        return false;
    return true;
}

static bool init_hud(frame_t *frame)
{
    int result = 0;

    frame->game->hud = malloc(sizeof(hud_t));
    if (!frame->game->hud)
        return false;
    HUD->weapon = NULL;
    HUD->nb_weapons = 0;
    HUD->selected_weapon = 0;
    result += create_hud(frame);
    if (!init_minimap(frame))
        return false;
    if (WEAPON_INFOS[0].texture_path)
        result += create_weapon(frame, 0);
    else {
        printf("ERROR: No weapon definitions found!\n");
        return false;
    }
    if (result != 0)
        return false;
    return true;
}

static bool init_enemies(frame_t *frame)
{
    int result = 0;

    NBENEMIES = 0;
    for (int i = 0; ENEMY_INFOS[i].path; i++) {
        result += create_enemy(frame, ENEMY_INFOS[i].path,
            ENEMY_INFOS[i].scale, ENEMY_INFOS[i].pos);
        ENEMY[NBENEMIES - 1].can_attack = false;
        ENEMY[NBENEMIES - 1].rec = ENEMY_INFOS[i].rec;
        ENEMY[NBENEMIES - 1].speed = ENEMY_INFOS[i].speed;
        ENEMY[NBENEMIES - 1].life = ENEMY_INFOS[i].life;
        ENEMY[NBENEMIES - 1].max_life = ENEMY_INFOS[i].life;
        ENEMY[NBENEMIES - 1].attack_range = ENEMY_INFOS[i].attack_range;
        ENEMY[NBENEMIES - 1].damages = ENEMY_INFOS[i].damages;
        ENEMY[NBENEMIES - 1].attack_cooldown = ENEMY_INFOS[i].attack_cooldown;
    }
    if (result != 0)
        return false;
    ENEMIESALIVE = NBENEMIES;
    return true;
}

static bool init_items(frame_t *frame)
{
    int result = 0;

    NBITEMS = 0;
    for (int i = 0; ITEM_INFOS[i].path; i++) {
        result += create_item(frame, ITEM_INFOS[i].path,
            ITEM_INFOS[i].scale, ITEM_INFOS[i].pos);
        ITEM[NBITEMS - 1].rec = ITEM_INFOS[i].rec;
        ITEM[NBITEMS - 1].name = ITEM_INFOS[i].name;
        ITEM[NBITEMS - 1].pickable = ITEM_INFOS[i].pickable;
        ITEM[NBITEMS - 1].useable = ITEM_INFOS[i].useable;
        ITEM[NBITEMS - 1].description = ITEM_INFOS[i].description;
    }
    if (result != 0)
        return false;
    return true;
}

static bool allocate_map(frame_t *frame)
{
    MAP = malloc(sizeof(map_t));
    if (!MAP)
        return false;
    return true;
}

static bool init_map_2d(frame_t *frame)
{
    MAP2D = malloc(sizeof(int *) * MAP_HEIGHT);
    if (!MAP2D)
        return false;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        MAP2D[i] = malloc(sizeof(int) * MAP_WIDTH);
        if (!MAP2D[i])
            return false;
        for (int j = 0; j < MAP_WIDTH; j++)
            MAP2D[i][j] = map[i][j];
    }
    return true;
}

static bool load_map_textures(frame_t *frame)
{
    MAP->floortexture = sfTexture_createFromFile(RES"concrete.png", NULL);
    MAP->ceilingtexture = sfTexture_createFromFile(RES"w_ceiling.jpg", NULL);
    if (!MAP->floortexture || !MAP->ceilingtexture)
        return false;
    return true;
}

static bool init_map(frame_t *frame)
{
    if (!allocate_map(frame) || !init_map_2d(frame))
        return false;
    MAP->width = MAP_WIDTH;
    MAP->height = MAP_HEIGHT;
    if (!load_map_textures(frame))
        return false;
    return true;
}

bool init_game(frame_t *frame)
{
    sfVideoMode desktop = sfVideoMode_getDesktopMode();

    frame->game = malloc(sizeof(game_t));
    if (!frame->game)
        return false;
    frame->game->level = 0;
    frame->ui->scene = MAINMENU;
    frame->center = (sfVector2i){desktop.width / 2, desktop.height / 2};
    if (!init_player(frame) || !init_map(frame)
        || !init_items(frame) || !init_enemies(frame)
        || !init_hud(frame) || !init_inventory(frame)
        || !init_environment(frame) || !init_flashlight(frame))
        return false;
    frame->game->saves = malloc(sizeof(saves_t));
    if (!frame->game->saves)
        return false;
    frame->game->saves->nb_saves = 0;
    return true;
}

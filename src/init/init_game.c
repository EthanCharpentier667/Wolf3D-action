/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_game
*/

#include "frame.h"

const int map[MAP_HEIGHT][MAP_WIDTH] = {
    {2, 2, 2, 2, 2, 2, 2, 2},
    {2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 2},
    {2, 2, 2, 2, 2, 2, 2, 2}
};

static int init_hud(frame_t *frame)
{
    int result = 0;

    frame->game->hud = malloc(sizeof(hud_t));
    if (!frame->game->hud)
        return 84;
    result += create_rec_obj(frame->img, RES"life.png",
        frct(0.0, 0.0, 0, 0), irct(0, 0, 400, 400));
    frame->game->hud->life = &frame->img->img[frame->img->nb_img - 1];
    result += create_text(frame->ui, "LIFE", sfWhite, v3f(1, 2000, 2000));
    frame->game->hud->life_text = &frame->ui->texts[frame->ui->nb_texts - 1];
    result = init_minimap(frame);
    if (result != 0)
        return 84;
    return 0;
}

static int init_enemies(frame_t *frame)
{
    int result = 0;

    NBENEMIES = 0;
    for (int i = 0; ENEMY_INFOS[i].path; i++) {
        result += create_enemy(frame, ENEMY_INFOS[i].path,
            ENEMY_INFOS[i].scale, ENEMY_INFOS[i].pos);
        ENEMY[NBENEMIES - 1].rec = ENEMY_INFOS[i].rec;
        ENEMY[NBENEMIES - 1].speed = ENEMY_INFOS[i].speed;
    }
    if (result != 0)
        return 84;
    ENEMIESALIVE = NBENEMIES;
    return 0;
}

static int init_items(frame_t *frame)
{
    int result = 0;

    NBITEMS = 0;
    for (int i = 0; ITEM_INFOS[i].path; i++) {
        result += create_item(frame, ITEM_INFOS[i].path,
            ITEM_INFOS[i].scale, ITEM_INFOS[i].pos);
        ITEM[NBITEMS - 1].rec = ITEM_INFOS[i].rec;
    }
    if (result != 0)
        return 84;
    return 0;
}

static int allocate_map(frame_t *frame)
{
    MAP = malloc(sizeof(map_t));
    if (!MAP)
        return 84;
    return 0;
}

// Allocate and initialize the 2D map array
static int init_map_2d(frame_t *frame)
{
    MAP2D = malloc(sizeof(int *) * MAP_HEIGHT);
    if (!MAP2D)
        return 84;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        MAP2D[i] = malloc(sizeof(int) * MAP_WIDTH);
        if (!MAP2D[i])
            return 84;
        for (int j = 0; j < MAP_WIDTH; j++)
            MAP2D[i][j] = map[i][j];
    }
    return 0;
}

static int load_map_textures(frame_t *frame)
{
    MAP->walltexture = sfTexture_createFromFile(RES"wall.jpg", NULL);
    MAP->floortexture = sfTexture_createFromFile(RES"concrete.png", NULL);
    MAP->ceilingtexture = sfTexture_createFromFile(RES"w_ceiling.jpg", NULL);
    if (!MAP->walltexture || !MAP->floortexture || !MAP->ceilingtexture)
        return 84;
    return 0;
}

// Main map initialization function
static int init_map(frame_t *frame)
{
    int status = 0;

    status = allocate_map(frame);
    if (status != 0)
        return status;
    status = init_map_2d(frame);
    if (status != 0)
        return status;
    MAP->width = MAP_WIDTH;
    MAP->height = MAP_HEIGHT;
    status = load_map_textures(frame);
    if (status != 0)
        return status;
    return 0;
}

int init_game(frame_t *frame)
{
    sfVideoMode desktop = sfVideoMode_getDesktopMode();

    frame->game = malloc(sizeof(game_t));
    if (!frame->game)
        return 84;
    frame->game->level = 0;
    frame->ui->scene = MAINMENU;
    frame->center = (sfVector2i){desktop.width / 2, desktop.height / 2};
    if (init_player(frame) == 84 || init_map(frame) == 84
        || init_items(frame) == 84 || init_enemies(frame) == 84 ||
        init_hud(frame) == 84)
        return 84;
    frame->game->saves = malloc(sizeof(saves_t));
    if (!frame->game->saves)
        return 84;
    frame->game->saves->nb_saves = 0;
    return 0;
}

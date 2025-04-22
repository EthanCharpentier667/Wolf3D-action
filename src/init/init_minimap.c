/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** init_minimap
*/

#include "frame.h"

static int allocate_minimap(frame_t *frame)
{
    HUD->minimap = malloc(sizeof(minimap_t));
    if (!HUD->minimap)
        return 84;
    HUD->minimap->size = 150;
    HUD->minimap->position = v2f(WINDOWX - 170, 20);
    HUD->minimap->cell_size = HUD->minimap->size / MAX(MAP_WIDTH, MAP_HEIGHT);
    HUD->minimap->nb_walls = 0;
    return 0;
}

static int init_minimap_background(frame_t *frame)
{
    HUD->minimap->background = sfRectangleShape_create();
    if (!HUD->minimap->background)
        return 84;
    sfRectangleShape_setSize(HUD->minimap->background,
        v2f(HUD->minimap->size, HUD->minimap->size));
    sfRectangleShape_setPosition(HUD->minimap->background,
        HUD->minimap->position);
    sfRectangleShape_setFillColor(HUD->minimap->background,
        sfColor_fromRGBA(0, 0, 0, 150));
    sfRectangleShape_setOutlineThickness(HUD->minimap->background, 2);
    sfRectangleShape_setOutlineColor(HUD->minimap->background, sfWhite);
    return 0;
}

static int allocate_wall_shapes(frame_t *frame, int total_cells)
{
    HUD->minimap->walls = malloc(sizeof(sfRectangleShape*) * total_cells);
    if (!HUD->minimap->walls)
        return 84;
    HUD->minimap->nb_walls = 0;
    return 0;
}

static int create_wall_shape(frame_t *frame)
{
    HUD->minimap->walls[HUD->minimap->nb_walls] = sfRectangleShape_create();
    if (!HUD->minimap->walls[HUD->minimap->nb_walls])
        return 84;
    return 0;
}

static void configure_wall_shape(frame_t *frame, int x, int y, int wall_index)
{
    sfRectangleShape *wall = HUD->minimap->walls[wall_index];

    sfRectangleShape_setSize(wall,
        v2f(HUD->minimap->cell_size, HUD->minimap->cell_size));
    sfRectangleShape_setPosition(wall,
        v2f(HUD->minimap->position.x + x * HUD->minimap->cell_size,
        HUD->minimap->position.y + y * HUD->minimap->cell_size));
    sfRectangleShape_setFillColor(wall, sfColor_fromRGB(120, 120, 120));
}

static int process_map_cell(frame_t *frame, int x, int y)
{
    if (MAP2D[y][x] > 0) {
        if (create_wall_shape(frame) != 0)
            return 84;
        configure_wall_shape(frame, x, y, HUD->minimap->nb_walls);
        HUD->minimap->nb_walls++;
    }
    return 0;
}

static int init_minimap_walls(frame_t *frame)
{
    int total_cells = MAP_WIDTH * MAP_HEIGHT;
    int status = 0;

    status = allocate_wall_shapes(frame, total_cells);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            status = process_map_cell(frame, x, y);
        }
    }
    if (status != 0)
        return 84;
    return 0;
}

static int init_minimap_player(frame_t *frame)
{
    HUD->minimap->player = sfCircleShape_create();
    if (!HUD->minimap->player)
        return 84;
    sfCircleShape_setRadius(HUD->minimap->player,
        HUD->minimap->cell_size / 2.5f);
    sfCircleShape_setFillColor(HUD->minimap->player, sfRed);
    HUD->minimap->direction = sfConvexShape_create();
    if (!HUD->minimap->direction)
        return 84;
    sfConvexShape_setPointCount(HUD->minimap->direction, 3);
    sfConvexShape_setFillColor(HUD->minimap->direction, sfYellow);
    return 0;
}

int init_minimap(frame_t *frame)
{
    int status = 0;

    status = allocate_minimap(frame);
    status = init_minimap_background(frame);
    status = init_minimap_walls(frame);
    status = init_minimap_player(frame);
    if (status != 0)
        return 84;
    return 0;
}

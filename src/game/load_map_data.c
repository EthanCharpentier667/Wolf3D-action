/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** load_map_data
*/

#include "frame.h"

static bool read_map_header(FILE *file, map_t *map_header)
{
    if (fread(map_header, sizeof(map_t), 1, file) != 1)
        return false;
    return true;
}

static bool read_map_cell(frame_t *frame, FILE *file,
    sfVector2i coords, int x)
{
    if (fread(&LEVELS[x].map[coords.x][coords.y],
        sizeof(int), 1, file) != 1)
        return false;
    return true;
}

static bool read_map_row(frame_t *frame, FILE *file,
    int row, int x)
{
    for (int j = 0; j < MAP_WIDTH; j++) {
        if (!read_map_cell(frame, file, v2i(row, j), x))
            return false;
    }
    return true;
}

static bool read_level_map(frame_t *frame, FILE *file, int x)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
        if (!read_map_row(frame, file, i, x))
            return false;
    return true;
}

bool load_map_data(frame_t *frame, FILE *file)
{
    map_t map_header;

    if (!read_map_header(file, &map_header))
        return false;
    for (int i = 0; i < NBLEVELS; i++)
        if (!read_level_map(frame, file, i))
            return false;
    return true;
}

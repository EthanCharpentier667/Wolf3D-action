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

static bool read_map_cell(FILE *file, int *cell_value)
{
    if (fread(cell_value, sizeof(int), 1, file) != 1)
        return false;
    return true;
}

static bool read_map_row(FILE *file, int row[MAP_WIDTH])
{
    for (int j = 0; j < MAP_WIDTH; j++)
        if (!read_map_cell(file, &row[j]))
            return false;
    return true;
}

static void copy_map_to_game(frame_t *frame,
    int temp_map[MAP_HEIGHT][MAP_WIDTH])
{
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
            MAP2D[i][j] = temp_map[i][j];
}

bool load_map_data(frame_t *frame, FILE *file)
{
    map_t map_header;
    int temp_map[MAP_HEIGHT][MAP_WIDTH];

    if (!read_map_header(file, &map_header))
        return false;
    for (int i = 0; i < MAP_HEIGHT; i++)
        if (!read_map_row(file, temp_map[i]))
            return false;
    copy_map_to_game(frame, temp_map);
    return true;
}

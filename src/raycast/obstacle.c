/*
** EPITECH PROJECT, 2025
** bswolf3D
** File description:
** wall
*/

#include "frame.h"

int is_osbtacle(int x, int y)
{
    int x_pos = x / TILE_SIZE;
    int y_pos = y / TILE_SIZE;

    if (x_pos < 0 || x_pos >= MAP_WIDTH || y_pos < 0 || y_pos >= MAP_HEIGHT)
        return 0;
    return map[y_pos][x_pos];
}

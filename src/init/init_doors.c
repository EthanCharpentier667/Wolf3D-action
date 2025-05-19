/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_doors
*/

#include "frame.h"

static int get_map_count(void)
{
    int door_count = 0;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            door_count += (map[y][x] == DOOR_CLOSED
                || map[y][x] == DOOR_OPEN) ? 1 : 0;
        }
    }
    return door_count;
}

static void add_door(frame_t *frame, int x, int y)
{
    if (map[y][x] == DOOR_CLOSED || map[y][x] == DOOR_OPEN) {
        DOORS[frame->game->doors->door_count].map_x = x;
        DOORS[frame->game->doors->door_count].map_y = y;
        DOORS[frame->game->doors->door_count].offset = 0.0f;
        DOORS[frame->game->doors->door_count].state = map[y][x];
        DOORS[frame->game->doors->door_count].anim_clock = sfClock_create();
        frame->game->doors->door_count++;
    }
}

static int create_doors(frame_t *frame)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++)
            add_door(frame, x, y);
    return frame->game->doors->door_count;
}

bool init_doors(frame_t *frame)
{
    int door_count = get_map_count();

    frame->game->doors = malloc(sizeof(doors_t));
    if (!frame->game->doors)
        return false;
    frame->game->doors->doors = malloc(sizeof(door_t) * door_count);
    if (!frame->game->doors->doors)
        return false;
    if (create_doors(frame) != door_count)
        return false;
    frame->game->doors->door_count = door_count;
    return true;
}

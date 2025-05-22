/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** load_items_data
*/

#include "frame.h"

static item_t *allocate_temporary_items(int num_items)
{
    if (num_items <= 0)
        return NULL;
    return malloc(sizeof(item_t) * (size_t)num_items);
}

static bool read_items_from_file(FILE *file, item_t *items_temp, int num_items)
{
    size_t read_count = 0;

    if (num_items <= 0)
        return true;
    if (!items_temp)
        return false;
    read_count = fread(items_temp, sizeof(item_t), (size_t)num_items, file);
    return (read_count == (size_t)num_items);
}

static bool allocate_game_items(frame_t *frame)
{
    int num_items = frame->game->nb_items;

    if (num_items <= 0)
        return true;
    if (frame->game->items)
        free(frame->game->items);
    frame->game->items = malloc(sizeof(item_t) * (size_t)num_items);
    return (frame->game->items != NULL);
}

static void copy_basic_item_data(frame_t *frame, item_t *items_temp)
{
    int num_items = frame->game->nb_items;

    if (num_items <= 0 || !items_temp || !frame->game->items)
        return;
    memcpy(frame->game->items, items_temp, sizeof(item_t) * (size_t)num_items);
    NBITEMS = num_items;
}

static bool load_item_texture(item_t *item)
{
    item->texture = NULL;
    for (int j = 0; ITEM_INFOS[j].path; j++) {
        if (strcmp(item->name, ITEM_INFOS[j].name) == 0) {
            item->texture = sfTexture_createFromFile(ITEM_INFOS[j].path, NULL);
            break;
        }
    }
    return (item->texture != NULL);
}

static void destroy_item_textures(frame_t *frame, int i)
{
    for (int j = 0; j < i; j++) {
        if (ITEM[j].texture) {
            sfTexture_destroy(ITEM[j].texture);
            ITEM[j].texture = NULL;
        }
    }
}

static bool load_item_textures_and_data(frame_t *frame, item_t *items_temp)
{
    int num_items = frame->game->nb_items;

    if (num_items <= 0 || !frame->game->items)
        return true;
    for (int i = 0; i < num_items; i++) {
        strcpy(ITEM[i].name, items_temp[i].name);
        strcpy(ITEM[i].description, items_temp[i].description);
        if (!load_item_texture(&ITEM[i])) {
            destroy_item_textures(frame, i);
            return false;
        }
    }
    return true;
}

static void cleanup_temporary_items(item_t *items_temp)
{
    if (items_temp)
        free(items_temp);
}

bool load_items_data(frame_t *frame, FILE *file)
{
    int num_items = frame->game->nb_items;
    item_t *items_temp = NULL;

    items_temp = allocate_temporary_items(num_items);
    if (!items_temp && num_items > 0)
        return false;
    if (!read_items_from_file(file, items_temp, num_items) ||
        !allocate_game_items(frame)) {
        cleanup_temporary_items(items_temp);
        return false;
    }
    copy_basic_item_data(frame, items_temp);
    if (!load_item_textures_and_data(frame, items_temp)) {
        cleanup_temporary_items(items_temp);
        return false;
    }
    cleanup_temporary_items(items_temp);
    return true;
}

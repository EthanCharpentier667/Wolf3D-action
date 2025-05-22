/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** load_objects_data
*/

#include "frame.h"

static fixed_object_t *allocate_temporary_objects(int num_objects)
{
    if (num_objects <= 0)
        return NULL;
    return malloc(sizeof(fixed_object_t) * (unsigned long)num_objects);
}

static bool read_objects_from_file(FILE *file,
    fixed_object_t *objects_temp, int num_objects)
{
    size_t read_count = 0;

    if (num_objects <= 0)
        return true;
    if (!objects_temp)
        return false;
    read_count = fread(objects_temp, sizeof(fixed_object_t),
        (unsigned long)num_objects, file);
    return (read_count == (unsigned long)num_objects);
}

static bool allocate_game_objects(frame_t *frame)
{
    int num_objects = frame->game->nb_fixed_objects;

    if (num_objects <= 0)
        return true;
    if (frame->game->fixed_objects)
        free(frame->game->fixed_objects);
    frame->game->fixed_objects = malloc(sizeof(fixed_object_t) *
        (unsigned long)num_objects);
    return (frame->game->fixed_objects != NULL);
}

static void copy_objects_to_game(frame_t *frame, fixed_object_t *objects_temp)
{
    int num_objects = frame->game->nb_fixed_objects;

    if (num_objects <= 0 || !objects_temp || !frame->game->fixed_objects)
        return;
    memcpy(frame->game->fixed_objects, objects_temp,
        sizeof(fixed_object_t) * (unsigned long)num_objects);
}

static void destroy_on_error(frame_t *frame, int i)
{
    for (int j = 0; j < i; j++)
        sfTexture_destroy(frame->game->fixed_objects[j].texture);
}

static bool load_object_textures(frame_t *frame)
{
    int num_objects = frame->game->nb_fixed_objects;

    if (num_objects <= 0 || !frame->game->fixed_objects)
        return true;
    for (int i = 0; i < num_objects; i++) {
        frame->game->fixed_objects[i].texture =
            sfTexture_createFromFile(FIXED_OBJECT_INFOS[i].path, NULL);
        if (!frame->game->fixed_objects[i].texture) {
            destroy_on_error(frame, i);
            return false;
        }
    }
    return true;
}

static void cleanup_temporary_objects(fixed_object_t *objects_temp)
{
    if (objects_temp)
        free(objects_temp);
}

bool load_objects_data(frame_t *frame, FILE *file)
{
    int num_objects = frame->game->nb_fixed_objects;
    fixed_object_t *objects_temp = NULL;

    objects_temp = allocate_temporary_objects(num_objects);
    if (!objects_temp && num_objects > 0)
        return false;
    if (!read_objects_from_file(file, objects_temp, num_objects) ||
        !allocate_game_objects(frame)) {
        cleanup_temporary_objects(objects_temp);
        return false;
    }
    copy_objects_to_game(frame, objects_temp);
    if (!load_object_textures(frame)) {
        cleanup_temporary_objects(objects_temp);
        return false;
    }
    cleanup_temporary_objects(objects_temp);
    return true;
}

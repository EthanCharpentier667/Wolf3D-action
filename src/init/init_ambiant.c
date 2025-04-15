/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** init_ambiant
*/

#include "frame.h"

static int init_sounds(ui_t *iu)
{
    int result = 0;

    iu->sounds = malloc(sizeof(sound_t));
    if (!iu->sounds)
        return 84;
    iu->nb_sounds = 0;
    for (int i = 0; SOUNDS_INFOS[i].path; i++)
        result += create_sound(iu, SOUNDS_INFOS[i].path);
    if (result > 0)
        return 84;
    return 0;
}

static int init_musics(ui_t *iu)
{
    int result = 0;

    iu->musics = malloc(sizeof(musics_t));
    if (!iu->musics)
        return 84;
    iu->nb_musics = 0;
    for (int i = 0; MUSICS_INFOS[i].path; i++)
        result += create_music(iu, MUSICS_INFOS[i].path);
    if (result > 0)
        return 84;
    return 0;
}

int init_ambiants(frame_t *frame)
{
    if (init_sounds(frame->ui) > 0)
        return 84;
    if (init_musics(frame->ui) > 0)
        return 84;
    return 0;
}

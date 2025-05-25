/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** sounds
*/

#include "frame.h"

#ifndef SOUNDS_H_
    #define SOUNDS_H_

struct sound_infos_s {
    char *path;
};

struct musics_infos_s {
    char *path;
};

extern const struct sound_infos_s SOUNDS_INFOS[];

extern const struct musics_infos_s MUSICS_INFOS[];

void play_sound(frame_t *frame, unsigned int sound, float volume);

#endif /* !SOUNDS_H_ */

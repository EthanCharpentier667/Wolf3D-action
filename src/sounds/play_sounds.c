/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** play_sounds
*/

#include "frame.h"

void play_sound(frame_t *frame, unsigned int id, float volume)
{
    sfSound *sound = UI->sounds[id].sound;

    sfSound_setVolume(sound, volume);
    sfSound_play(sound);
}

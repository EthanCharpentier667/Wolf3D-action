/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** weapon_sounds
*/

#include "frame.h"

void manage_windup_sound(bool should_play)
{
    static sfSound *sound_wdup = NULL;
    static sfSoundBuffer *sb = NULL;

    if (!sound_wdup) {
        sound_wdup = sfSound_create();
        sb = sfSoundBuffer_createFromFile(RES "windup_mg.wav");
        sfSound_setBuffer(sound_wdup, sb);
        sfSound_setLoop(sound_wdup, sfTrue);
    }
    if (should_play && (sfSound_getStatus(sound_wdup) != sfPlaying)) {
        sfSound_play(sound_wdup);
    } else if (!should_play && (sfSound_getStatus(sound_wdup) == sfPlaying)) {
        sfSound_stop(sound_wdup);
    }
}

void manage_firing_sound(bool should_play)
{
    static sfSound *sound_fire = NULL;
    static sfSoundBuffer *sb = NULL;

    if (!sound_fire) {
        sound_fire = sfSound_create();
        sb = sfSoundBuffer_createFromFile(RES "shot_mg.wav");
        sfSound_setBuffer(sound_fire, sb);
        sfSound_setLoop(sound_fire, sfTrue);
    }
    if (should_play && (sfSound_getStatus(sound_fire) != sfPlaying)) {
        sfSound_play(sound_fire);
    } else if (!should_play && (sfSound_getStatus(sound_fire) == sfPlaying)) {
        sfSound_stop(sound_fire);
    }
}

void manage_cuting_sound(bool should_play)
{
    static sfSound *sound_cut = NULL;
    static sfSoundBuffer *sb = NULL;

    if (!sound_cut) {
        sound_cut = sfSound_create();
        sb = sfSoundBuffer_createFromFile(RES "knife_slash.wav");
        sfSound_setBuffer(sound_cut, sb);
    }
    if (should_play && (sfSound_getStatus(sound_cut) != sfPlaying)) {
        sfSound_play(sound_cut);
    } else if (!should_play && (sfSound_getStatus(sound_cut) == sfPlaying)) {
        sfSound_stop(sound_cut);
    }
}

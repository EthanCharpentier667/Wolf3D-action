/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** weapon_sounds
*/

#include "frame.h"

void manage_windup_sound(bool should_play, int volume)
{
    static sfSound *sound_wdup = NULL;
    static sfSoundBuffer *sb = NULL;

    if (!sound_wdup) {
        sound_wdup = sfSound_create();
        sb = sfSoundBuffer_createFromFile(RES "windup_mg.wav");
        if (!sb || !sound_wdup)
            return;
        sfSound_setBuffer(sound_wdup, sb);
        sfSound_setVolume(sound_wdup, volume);
        sfSound_setLoop(sound_wdup, sfTrue);
    }
    if (!sound_wdup)
        return;
    if (should_play && (sfSound_getStatus(sound_wdup) != sfPlaying)) {
        sfSound_play(sound_wdup);
        sfSound_setVolume(sound_wdup, volume);
    } else if (!should_play && (sfSound_getStatus(sound_wdup) == sfPlaying)) {
        sfSound_setLoop(sound_wdup, sfFalse);
        sfSound_setVolume(sound_wdup, 0);
    }
}

void manage_firing_sound(bool should_play, int volume)
{
    static sfSound *sound_fire = NULL;
    static sfSoundBuffer *sb = NULL;

    if (!sound_fire) {
        sound_fire = sfSound_create();
        sb = sfSoundBuffer_createFromFile(RES "shot_mg.wav");
        if (!sb || !sound_fire)
            return;
        sfSound_setBuffer(sound_fire, sb);
        sfSound_setLoop(sound_fire, sfTrue);
        sfSound_setVolume(sound_fire, volume);
    }
    if (!sound_fire)
        return;
    if (should_play && (sfSound_getStatus(sound_fire) != sfPlaying)) {
        sfSound_play(sound_fire);
        sfSound_setVolume(sound_fire, volume);
    } else if (!should_play && (sfSound_getStatus(sound_fire) == sfPlaying)) {
        sfSound_setLoop(sound_fire, sfFalse);
        sfSound_setVolume(sound_fire, 0);
    }
}

void manage_cuting_sound(bool should_play, int volume)
{
    static sfSound *sound_cut = NULL;
    static sfSoundBuffer *sb = NULL;

    if (!sound_cut) {
        sound_cut = sfSound_create();
        sb = sfSoundBuffer_createFromFile(RES "knife_slash.wav");
        if (!sb || !sound_cut)
            return;
        sfSound_setBuffer(sound_cut, sb);
        sfSound_setVolume(sound_cut, volume);
    }
    if (!sound_cut)
        return;
    if (should_play && (sfSound_getStatus(sound_cut) != sfPlaying)) {
        sfSound_play(sound_cut);
        sfSound_setVolume(sound_cut, volume);
    } else if (!should_play && (sfSound_getStatus(sound_cut) == sfPlaying)) {
        sfSound_setLoop(sound_cut, sfFalse);
        sfSound_setVolume(sound_cut, 0);
    }
}

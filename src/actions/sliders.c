/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** sliders
*/

#include "frame.h"

int apply_volume_change_sounds(frame_t *frame, float volume)
{
    for (int i = 0; i < frame->ui->nb_sounds; i++) {
        sfSound_setVolume(frame->ui->sounds[i].sound, volume * 100.0f);
    }
    UI->settings->sound_volume = volume;
    return 0;
}

int apply_volume_change_musics(frame_t *frame, float volume)
{
    for (int i = 0; i < frame->ui->nb_musics; i++) {
        sfMusic_setVolume(frame->ui->musics[i].music, volume * 100.0f);
    }
    UI->settings->music_volume = volume;
    return 0;
}

int apply_difficulty_change(frame_t *frame, float difficulty)
{
    if (frame->ui->scene == GAME || frame->played)
        return 0;
    frame->game->difficulty = 3 * (1 - difficulty);
    if (frame->game->difficulty < 1)
        frame->game->difficulty = 1;
    else if (frame->game->difficulty > 3)
        frame->game->difficulty = 3;
    frame->game->timer = 600 * frame->game->difficulty / 3;
    return 0;
}

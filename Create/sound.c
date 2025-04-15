/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** sound
*/

#include "frame.h"

int create_sound(ui_t *ui, char *path)
{
    ui->sounds = realloc(ui->sounds, sizeof(sound_t) * (ui->nb_sounds + 1));
    if (!ui->sounds)
        return 84;
    ui->sounds[ui->nb_sounds].buffer = sfSoundBuffer_createFromFile(path);
    if (!ui->sounds[ui->nb_sounds].buffer)
        return 84;
    ui->sounds[ui->nb_sounds].sound = sfSound_create();
    if (!ui->sounds[ui->nb_sounds].sound)
        return 84;
    sfSound_setBuffer(ui->sounds[ui->nb_sounds].sound,
        ui->sounds[ui->nb_sounds].buffer);
    ui->nb_sounds++;
    return 0;
}

int create_music(ui_t *ui, char *path)
{
    ui->musics = realloc(ui->musics, sizeof(musics_t) * (ui->nb_musics + 1));
    if (!ui->musics)
        return 84;
    ui->musics[ui->nb_musics].music = sfMusic_createFromFile(path);
    if (!ui->musics[ui->nb_musics].music)
        return 84;
    ui->nb_musics++;
    return 0;
}

/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** quit
*/

#include "frame.h"

int change_music(frame_t *frame, int music)
{
    static int last_music = -1;

    if (music > frame->ui->nb_musics)
        return -1;
    if (last_music == music)
        return 0;
    if (last_music != -1)
        sfMusic_stop(frame->ui->musics[last_music].music);
    sfMusic_play(frame->ui->musics[music].music);
    sfMusic_setLoop(frame->ui->musics[music].music, sfTrue);
    last_music = music;
    return 0;
}

int do_game_quit(frame_t *frame)
{
    UI->pause = !UI->pause;
    do_save(frame);
    change_scene(frame, MAINMENU);
    change_music(frame, 0);
    sfRenderWindow_setMouseCursorVisible(WINDOW, sfTrue);
    return 0;
}

int do_mm_quit(frame_t *frame)
{
    sfMusic_stop(frame->ui->musics[0].music);
    sfRenderWindow_close(frame->window);
    return 0;
}

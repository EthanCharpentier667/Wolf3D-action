/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** play
*/

#include "frame.h"

int do_resume(frame_t *frame)
{
    UI->pause = false;
    PLAYER->pause = false;
    return 0;
}

static bool get_name(frame_t *frame, char *buffer)
{
    char *sswolfs_part = NULL;

    buffer[strcspn(buffer, "\n")] = 0;
    sswolfs_part = strstr(buffer, "sswolfs/");
    if (sswolfs_part != NULL) {
        frame->save = strdup(sswolfs_part);
    } else {
        system("zenity --error --text=\"La sauvegarde"
            " doit être dans le dossier sswolfs/\"");
        return false;
    }
    frame->name = strdup(sswolfs_part + strlen("sswolfs/"));
    return true;
}

static bool get_save_name(frame_t *frame)
{
    FILE *fp = popen("zenity --file-selection --save --filename=\"hilter\" "
        "--title=\"Nom de la partie\"", "r");
    char buffer[256] = {0};
    bool result = false;

    if (fp == NULL) {
        fprintf(stderr, "Failed to run zenity command\n");
        return false;
    }
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        result = get_name(frame, buffer);
        pclose(fp);
        if (!result)
            return get_save_name(frame);
        return true;
    }
    pclose(fp);
    return false;
}

static void check_save(frame_t *frame)
{
    if (!frame->played) {
        create_save_directory();
        if (get_save_name(frame)) {
            change_scene(frame, GAME);
            sfRenderWindow_setMouseCursorVisible(WINDOW, sfFalse);
            sfMouse_setPositionRenderWindow(v2i(WINDOWX / 2,
                WINDOWY / 2), WINDOW);
            change_music(frame, 1);
            frame->played = true;
        }
    } else {
        LEVEL = LEVEL0;
        change_music(frame, 1);
        change_scene(frame, GAME);
    }
}

int do_play(frame_t *frame)
{
    UI->pause = false;
    PLAYER->pause = false;
    check_save(frame);
    return 0;
}

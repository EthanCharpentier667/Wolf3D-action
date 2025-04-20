/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** load
*/

#include "frame.h"
#include <dirent.h>
#include <sys/types.h>

int load_save_callback(frame_t *frame, int button_index)
{
    int save_index = -1;
    char filepath[256];

    for (int i = 0; i < frame->ui->nb_buttons; i++) {
        if (BUTTON[i].action == SAVES_LIST)
            save_index++;
        if (save_index == button_index)
            break;
    }
    if (button_index < 0 || button_index >= frame->ui->nb_buttons) {
        fprintf(stderr, "Error: Button index out of range\n");
        return 84;
    }
    snprintf(filepath, sizeof(filepath), "sswolfs/save-%s.ww2",
        frame->game->saves->name[save_index]);
    printf("Loading save name: %s\n", frame->game->saves->name[save_index]);
    printf("Loading save file: %s\n", filepath);
    return 0;
}

static void free_save(saves_t *saves)
{
    for (int i = 0; i < saves->nb_saves; i++) {
        free(saves->name[i]);
        sfSprite_destroy(saves->buttons[i].sprite);
        sfText_destroy(saves->texts[i].text);
    }
}

int do_load(frame_t *frame)
{
    free_save(frame->game->saves);
    if (loads_saved_games(frame) == 84)
        return 84;
    UI->scene = LOADS;
    return 0;
}

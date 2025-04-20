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

    for (int i = 0; i < UI->nb_buttons; i++) {
        if (BUTTON[i].action == SAVES_LIST)
            save_index++;
        if (save_index == button_index)
            break;
    }
    if (button_index < 0 || button_index >= UI->nb_buttons) {
        fprintf(stderr, "Error: Button index out of range\n");
        return 84;
    }
    snprintf(filepath, sizeof(filepath), "sswolfs/save-%s.ww2",
        frame->game->saves->name[save_index]);
    printf("Loading save name: %s\n", frame->game->saves->name[save_index]);
    printf("Loading save file: %s\n", filepath);
    return 0;
}

static void destroy_buttons(frame_t *frame)
{
    for (int i = 0; i < UI->nb_buttons; i++) {
        if (UI->button[i].action != SAVES_LIST)
            continue;
        sfRectangleShape_destroy(UI->button[i].help_box->box);
        sfText_destroy(UI->button[i].help_box->text);
        free(UI->button[i].help_box);
        sfSprite_destroy(UI->button[i].sprite);
        sfTexture_destroy(UI->button[i].texture[0]);
        for (int j = i; j < UI->nb_buttons - 1; j++)
            UI->button[j] = UI->button[j + 1];
        UI->nb_buttons--;
        i--;
    }
    UI->button = realloc(UI->button, UI->nb_buttons * sizeof(button_t));
}

void free_save(saves_t *saves, frame_t *frame)
{
    for (int i = 0; i < saves->nb_saves; i++) {
        free(saves->name[i]);
        sfText_destroy(saves->texts[i].text);
    }
    destroy_buttons(frame);
    frame->game->saves->nb_saves = 0;
}

int do_load(frame_t *frame)
{
    free_save(frame->game->saves, frame);
    if (loads_saved_games(frame) == 84)
        return 84;
    UI->scene = LOADS;
    return 0;
}

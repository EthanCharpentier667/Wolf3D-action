/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** load
*/

#include "frame.h"
#include <dirent.h>
#include <sys/types.h>

static int init_save_button(ui_t *ui, char *path,
    sfFloatRect infos, char *htext)
{
    int result = 0;
    sfFloatRect textRect;

    result += create_helpboxed_button(ui, path, infos, SAVES_LIST);
    sfText_setString(BUTTONS[NB_BUTTONS - 1].help_box->text, htext);
    wrap_text(BUTTONS[NB_BUTTONS - 1].help_box->text, 200);
    textRect = sfText_getGlobalBounds(BUTTONS[NB_BUTTONS - 1].help_box->text);
    sfRectangleShape_setSize(BUTTONS[NB_BUTTONS - 1].help_box->box,
    (sfVector2f){textRect.width + 10, textRect.height + 10});
    return result;
}

static int scan_save_file(const char *filepath,
    const char *imagepath, save_info_t *save)
{
    FILE *save_file = fopen(filepath, "r");
    char name[64] = {0};
    char date[32] = {0};

    if (!save_file)
        return 84;
    fscanf(save_file, "Name: %63[^\n]\n", name);
    fscanf(save_file, "Date: %31[^\n]\n", date);
    fclose(save_file);
    strncpy(save->filename, filepath, sizeof(save->filename));
    strncpy(save->imagepath, imagepath, sizeof(save->imagepath));
    strncpy(save->name, name, sizeof(save->name));
    strncpy(save->date, date, sizeof(save->date));
    return 0;
}

static int check_and_prepare_save_file(struct dirent *entry,
    char *filepath, char *imagepath)
{
    char base_name[268];
    char *ext = strrchr(entry->d_name, '.');

    if (entry->d_type != DT_REG || !ext || strcmp(ext, ".ww2") != 0)
        return 84;
    snprintf(filepath, 268, "sswolfs/%s", entry->d_name);
    strncpy(base_name, entry->d_name, strlen(entry->d_name) - 4);
    base_name[strlen(entry->d_name) - 4] = '\0';
    snprintf(imagepath, 280, "sswolfs/%s.png", base_name);
    return 0;
}

static int open_save_directory(DIR **dir)
{
    *dir = opendir("sswolfs");
    if (!*dir) {
        perror("Failed to open directory");
        return 84;
    }
    return 0;
}

static int process_save_entry(struct dirent *entry, save_info_t *save)
{
    char filepath[256];
    char imagepath[256];
    FILE *img_file = NULL;

    if (check_and_prepare_save_file(entry, filepath, imagepath) == 84)
        return 84;
    img_file = fopen(imagepath, "r");
    save->has_thumbnail = (img_file != NULL);
    if (img_file)
        fclose(img_file);
    return scan_save_file(filepath, imagepath, save);
}

static int find_save_files(save_info_t *saves, int *valid_saves)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;

    if (open_save_directory(&dir) != 0)
        return 84;
    *valid_saves = 0;
    entry = readdir(dir);
    while (entry && *valid_saves < MAX_SAVES_DISPLAYED) {
        if (process_save_entry(entry, &saves[*valid_saves]) == 0)
            (*valid_saves)++;
        entry = readdir(dir);
    }
    closedir(dir);
    return 0;
}

static int create_save_button(frame_t *frame, save_info_t *save,
    sfVector2f pos, int save_index)
{
    int result = 0;
    char save_info[98];

    if (save->has_thumbnail) {
        result = init_save_button(UI, save->imagepath,
            (sfFloatRect){pos.x, pos.y, 0.1, 0.1}, save->name);
    } else {
        result = init_save_button(UI, RES "default_save.png",
            (sfFloatRect){pos.x, pos.y, 0.1, 0.1}, save->name);
    }
    if (result > 0)
        return 84;
    frame->game->saves->buttons[save_index] = BUTTON[UI->nb_buttons - 1];
    snprintf(save_info, sizeof(save_info), "%s - %s", save->name, save->date);
    create_text(UI, save_info, sfWhite, v3f(16, pos.x, pos.y + 120));
    frame->game->saves->texts[save_index] = UI->texts[UI->nb_texts - 1];
    frame->game->saves->name[save_index] = strdup(save->name);
    applied_button(frame->ui);
    return 0;
}

static int create_no_save_message(frame_t *frame)
{
    create_text(UI, "You haven't save yet.", sfRed, v3f(30, 250, 300));
    frame->game->saves->texts[0] = UI->texts[UI->nb_texts - 1];
    return 0;
}

static int display_save_buttons(frame_t *frame,
    save_info_t *saves, int valid_saves)
{
    int result = 0;
    sfVector2f pos = {0, 0};
    sfVector2f rwcl = {0, 0};

    frame->game->saves->nb_saves = 0;
    for (int i = 0; i < valid_saves; i++) {
        rwcl.x = i / 3;
        rwcl.y = i % 3;
        pos.x = 100 + rwcl.y * 180;
        pos.y = 250 + rwcl.x * 180;
        result = create_save_button(frame, &saves[i], pos, i);
        if (result > 0)
            return 84;
        frame->game->saves->nb_saves++;
    }
    if (frame->game->saves->nb_saves == 0)
        return create_no_save_message(frame);
    return 0;
}

int loads_saved_games(frame_t *frame)
{
    save_info_t saves[MAX_SAVES_DISPLAYED];
    int valid_saves = 0;

    if (find_save_files(saves, &valid_saves) != 0)
        return 84;
    return display_save_buttons(frame, saves, valid_saves);
}

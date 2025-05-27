/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** parse_levels
*/

#include "frame.h"
#include "dirent.h"

static bool print_error(const char *message)
{
    char command[512] = {0};

    snprintf(command, sizeof(command),
        "zenity --error --text=\"Error: %s\"", message);
    system(command);
    return false;
}

static bool get_map_infos(levels_t *level, char *line)
{
    char *temp = NULL;

    temp = strtok(line, "x");
    if (!temp)
        return print_error("Invalid level file infos (XxY).");
    level->height = atoi(temp);
    temp = strtok(NULL, "\n");
    if (!temp)
        return print_error("Invalid level file infos (XxY).");
    level->width = atoi(temp);
    if (level->width != MAP_WIDTH || level->height != MAP_HEIGHT)
        return print_error("Incorrect Map size.");
    level->map = malloc(sizeof(int *) * level->height);
    if (!level->map)
        return print_error("Memory allocation failed for map.");
    return true;
}

static bool parse_map(levels_t *level, char *line, int i)
{
    char *tokens = NULL;
    char *temp = NULL;

    level->map[i] = malloc(sizeof(int) * level->width);
    if (!level->map[i])
        return print_error("Memory allocation failed for map row.");
    temp = strtok(line, ",");
    if (!temp)
        return print_error("Invalid map format");
    for (int j = 0; j < level->width - 1; j++) {
        level->map[i][j] = strtol(temp, &tokens, 10);
        if (*tokens != '\0')
            return print_error("Invalid map format, expected integers.");
        temp = strtok(NULL, ",");
        if (temp == NULL)
            return print_error("Invalid map format");
    }
    level->map[i][level->width - 1] = strtol(temp, &tokens, 10);
    return true;
}

static bool get_level_infos(levels_t *level, char *line, FILE *file)
{
    fgets(line, sizeof(line), file);
    if (!get_map_infos(level, line))
        return false;
    return true;
}

static bool parse_level(frame_t *frame, const char *path)
{
    FILE *file = fopen(path, "r");
    char line[256] = {0};
    int line_count = 0;

    if (NBLEVELS > 0)
        LEVELS = realloc(LEVELS, sizeof(levels_t) * (NBLEVELS + 1));
    if (!file)
        return print_error("Could not open level file.");
    if (get_level_infos(&LEVELS[NBLEVELS], line, file) == false)
        return false;
    while (fgets(line, sizeof(line), file)) {
        if (!parse_map(&LEVELS[NBLEVELS], line, line_count))
            return false;
        line_count++;
    }
    if (line_count != LEVELS[NBLEVELS].height)
        return print_error("Map height does not match number of lines.");
    NBLEVELS++;
    fclose(file);
    return true;
}

static bool read_levels(frame_t *frame, DIR *dir_handle, int *count)
{
    struct dirent *dir = NULL;
    char path[256] = {0};

    dir = readdir(dir_handle);
    while (dir != NULL) {
        if (dir->d_type != DT_REG) {
            dir = readdir(dir_handle);
            continue;
        }
        snprintf(path, sizeof(path), "levels/%s", dir->d_name);
        if (parse_level(frame, path))
            (*count)++;
        dir = readdir(dir_handle);
    }
    return true;
}

bool parse_levels(frame_t *frame)
{
    DIR *dir_handle = opendir("levels");
    int count = 0;

    NBLEVELS = 0;
    if (!dir_handle)
        return print_error("Could not open levels directory.");
    LEVELS = malloc(sizeof(levels_t));
    read_levels(frame, dir_handle, &count);
    if (count == 0) {
        closedir(dir_handle);
        return print_error("No levels found in the directory.");
    }
    closedir(dir_handle);
    return true;
}

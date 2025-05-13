/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** environment
*/

#include "frame.h"

int create_environment(frame_t *frame, char *str,
    sfIntRect rec, sfVector2f scale)
{
    frame->game->environment = realloc(frame->game->environment,
        sizeof(environment_t) * (frame->game->nb_env + 1));
    if (!frame->game->environment)
        return 84;
    frame->game->environment[frame->game->nb_env].texture =
        sfTexture_createFromFile(str, NULL);
    if (!frame->game->environment[frame->game->nb_env].texture)
        return 84;
    frame->game->environment[frame->game->nb_env].scale = scale;
    frame->game->environment[frame->game->nb_env].rec = rec;
    if (rec.width == 0 && rec.height == 0 && rec.top == 0 && rec.left == 0)
        frame->game->environment[frame->game->nb_env].isrec = false;
    else
        frame->game->environment[frame->game->nb_env].isrec = true;
    frame->game->environment[frame->game->nb_env].isanimated = false;
    frame->game->environment[frame->game->nb_env].isobstacle = false;
    frame->game->environment[frame->game->nb_env].pos = v2f(0, 0);
    frame->game->environment[frame->game->nb_env].type = 0;
    frame->game->nb_env++;
    return 0;
}

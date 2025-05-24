/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** get_impact_pos
*/

#include "frame.h"

bool get_wall_impact(sfVector3f *buff, frame_t *frame, float range)
{
    float verti_dist = frame->z_buffer[WINDOWX / 2];
    float hori_dist = frame->hori_buffer[WINDOWY / 2];
    float forward = verti_dist;
    sfVector2f dir = {cosf(PLAYER->angle.x), sinf(PLAYER->angle.x)};

    forward = (verti_dist > hori_dist ? hori_dist : forward) - 10;
    if (forward <= 0.0f || forward >= range)
        return true;
    buff->x = PLAYER->pos.x + dir.x * forward;
    buff->y = PLAYER->pos.y + dir.y * forward;
    buff->z = tanf(PLAYER->angle.y) * forward / 100;
    return false;
}

void impact_wall(frame_t *frame, float range)
{
    sfVector3f pos = {0};

    if (get_wall_impact(&pos, frame, range))
        return;
    vfx_dust_impact(frame, pos);
}
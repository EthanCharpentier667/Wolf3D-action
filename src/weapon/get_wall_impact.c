/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** get_impact_pos
*/

#include "frame.h"

float get_wall_impact(sfVector3f *buff, frame_t *frame, float range)
{
    float verti_dist = frame->z_buffer[WINDOWX / 2];
    float hori_dist = frame->hori_buffer[WINDOWY / 2];
    float forward = verti_dist;
    sfVector2f dir = {cosf(PLAYER->angle.x), sinf(PLAYER->angle.x)};

    forward = (verti_dist > hori_dist ? hori_dist : forward) - 4;
    if (forward <= 0.0f || forward >= range)
        return -1;
    buff->x = PLAYER->pos.x + dir.x * forward;
    buff->y = PLAYER->pos.y + dir.y * forward;
    buff->z = tanf(PLAYER->angle.y) * forward / 100;
    play_sound(frame, 2, 3500 / forward);
    return forward;
}

void impact_wall(frame_t *frame, float range)
{
    sfVector3f pos = {0};
    float rand = 0;
    float dist = get_wall_impact(&pos, frame, range);

    if (dist == -1)
        return;
    rand = dist / 50;
    pos.x = rand_range(pos.x - rand, pos.x + rand);
    pos.y = rand_range(pos.y - rand, pos.y + rand);
    pos.z = rand_range(pos.z - rand / 100, pos.z + rand / 100);
    vfx_dust_impact(frame, pos);
}

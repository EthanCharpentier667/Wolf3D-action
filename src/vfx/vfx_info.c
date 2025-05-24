/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** vfx_info
*/

#include "frame.h"

obj_info_t create_obj_info(sfFloatRect cframe, float angle,
    sfColor color, float time_stamp)
{
    obj_info_t info = {0};

    info.cframe = cframe;
    info.angle = angle;
    info.color = color;
    info.time_stamp = time_stamp;
    return info;
}

sfFloatRect calculate_vfx_render(player_t *player,
    sfVector3f vfx_pos, sfFloatRect addon, float velocity)
{
    sfVector2f screen = {0, 0};
    sfVector2f delta = {vfx_pos.x - player->pos.x, vfx_pos.y - player->pos.y};
    sfVector2f dir = {cosf(player->angle.x), sinf(player->angle.x)};
    sfVector2f right = {sinf(player->angle.x) * -1, cosf(player->angle.x)};
    float forward = delta.x * dir.x + delta.y * dir.y;
    float sideways = delta.x * right.x + delta.y * right.y;
    sfFloatRect result = {0};

    if (forward < 0.01f)
        forward = 0.01f;
    screen.x = (int)(WINDOWX / 2 + sideways /
        forward * (WINDOWX / 2) / tanf(FOV / 2));
    screen.y = WINDOWY / 2 - (vfx_pos.z * TILE_SIZE * WINDOWY) / forward
        + (int)(WINDOWY * tanf(player->angle.y) / 2);
    result.left = screen.x + addon.left * WINDOWX / forward;
    result.top = screen.y + (addon.top + velocity) * WINDOWY / forward;
    result.width = addon.width * TILE_SIZE * WINDOWY / forward;
    result.height = addon.height * TILE_SIZE * WINDOWY / forward;
    return result;
}

sfVector3f get_front(player_t *player, float range, sfVector3f addon)
{
    sfVector3f result = {
        player->pos.x + cosf(player->angle.x) *
            cosf(player->angle.y) * range + addon.x,
        player->pos.y + sinf(player->angle.x) *
            cosf(player->angle.y) * range + addon.y,
        (sinf(player->angle.y) * range) / 100 + addon.z
    };

    return result;
}

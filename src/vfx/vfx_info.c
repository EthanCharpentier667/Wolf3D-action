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
    float dx = vfx_pos.x - player->pos.x;
    float dy = vfx_pos.y - player->pos.y;

    float dir_x = cosf(player->angle.x);
    float dir_y = sinf(player->angle.x);
    float right_x = -sinf(player->angle.x);
    float right_y = cosf(player->angle.x);

    float forward = dx * dir_x + dy * dir_y;
    float sideways = dx * right_x + dy * right_y;

    if (forward < 0.01f)
        forward = 0.01f;

    int screen_x = (int)(WINDOWX / 2 + sideways / forward * (WINDOWX / 2) / tanf(FOV / 2));

    float projected_height = addon.height * TILE_SIZE * WINDOWY / forward;
    float projected_width  = addon.width  * TILE_SIZE * WINDOWY / forward;

    int screen_y = WINDOWY / 2 - projected_height / 2
        - (vfx_pos.z * TILE_SIZE * WINDOWY) / forward
        + (int)(WINDOWY * tanf(player->angle.y) / 2);

    sfFloatRect result;
    result.left = screen_x + addon.left * WINDOWX / forward;
    result.top = screen_y + (addon.top + velocity) * WINDOWY / forward;
    result.width = projected_width;
    result.height = projected_height;

    return result;
}

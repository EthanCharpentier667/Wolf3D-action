/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** create_vfx
*/

#include "frame.h"

static void set_vfx_info(obj_info_t *info, obj_info_t *s_info,
    obj_info_t *f_info, float ratio)
{
    info->cframe.left = s_info->cframe.left +
        (f_info->cframe.left - s_info->cframe.left) * ratio;
    info->cframe.top = s_info->cframe.top +
        (f_info->cframe.top - s_info->cframe.top) * ratio;
    info->cframe.width = s_info->cframe.width +
        (f_info->cframe.width - s_info->cframe.width) * ratio;
    info->cframe.height = s_info->cframe.height +
        (f_info->cframe.height - s_info->cframe.height) * ratio;
    info->angle = s_info->angle + (f_info->angle - s_info->angle) * ratio;
    info->color.r = s_info->color.r + (f_info->color.r - s_info->color.r) * ratio;
    info->color.g = s_info->color.g + (f_info->color.g - s_info->color.g) * ratio;
    info->color.b = s_info->color.b + (f_info->color.b - s_info->color.b) * ratio;
    info->color.a = s_info->color.a + (f_info->color.a - s_info->color.a) * ratio;
}

static bool update_vfx_info(vfx_t *vfx, float delta_time)
{
    obj_info_t *infos = &vfx->info;
    obj_info_t *s_infos = &vfx->s_info;
    obj_info_t *f_infos = &vfx->f_info;
    float life_time = f_infos->time_stamp - s_infos->time_stamp;
    float ratio = (infos->time_stamp - s_infos->time_stamp) / life_time;

    if (infos->time_stamp >= f_infos->time_stamp)
        return true;
    set_vfx_info(infos, s_infos, f_infos, ratio);
    infos->time_stamp += delta_time;
    return false;
}

bool update_vfx(vfx_t *vfx, float delta_time)
{
    if (update_vfx_info(vfx, delta_time))
        return true;
    sfSprite_setPosition(vfx->particle, v2f(vfx->info.cframe.left, vfx->info.cframe.top));
    sfSprite_setScale(vfx->particle, v2f(vfx->info.cframe.width, vfx->info.cframe.height));
    sfSprite_setColor(vfx->particle, vfx->info.color);
    sfSprite_setRotation(vfx->particle, vfx->info.angle);
    return false;
}

void update_vfxs(linked_list_t *vfxs, float delta_time)
{
    vfx_t *temp_vfx = NULL;

    for (linked_list_t *elem = vfxs->next; elem->id > 0; elem = elem->next) {
        temp_vfx = (vfx_t *)elem->data;
        if (update_vfx(temp_vfx, delta_time))
            del_element(vfxs, elem);
    }
}

void draw_vfxs(player_t *player, sfRenderWindow *window, linked_list_t *vfxs)
{
    vfx_t *temp_vfx = NULL;
    sfFloatRect temp_rect = {0, 0, 0, 0};
    sfVector2u tex_size = {0, 0};

    for (linked_list_t *elem = vfxs->next; elem->id > 0; elem = elem->next) {
        temp_vfx = (vfx_t *)elem->data;
        temp_rect = calculate_vfx_render(player,
            temp_vfx->origin_pos, temp_vfx->info.cframe);
        tex_size = sfTexture_getSize(sfSprite_getTexture(temp_vfx->particle));
        float scale_x = temp_rect.width  / (float)tex_size.x;
        float scale_y = temp_rect.height / (float)tex_size.y;

        sfSprite_setPosition(temp_vfx->particle, v2f(temp_rect.left, temp_rect.top));
        sfSprite_setScale(temp_vfx->particle, v2f(scale_x, scale_y));
        sfRenderWindow_drawSprite(window, temp_vfx->particle, NULL);
    }
}

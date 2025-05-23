/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** emit
*/

#include "frame.h"

emit_t create_emit(unsigned int min_nb, unsigned int max_nb,
    obj_info_t s_infos, obj_info_t f_infos)
{
    emit_t emit = {0};

    memset(&emit, 0, sizeof(emit));
    emit.min_nb = min_nb;
    emit.max_nb = max_nb;
    emit.start_info = s_infos;
    emit.final_info = f_infos;
    return emit;
}

bool set_emit(emit_t *buff, obj_info_t rands_infos,
    obj_info_t randf_info, float gravity)
{
    if (!buff)
        return true;
    buff->rands_info = rands_infos;
    buff->randf_info = randf_info;
    buff->gravity = gravity;
    return false;
}

static sfColor rand_color_info(sfColor raw_color, sfColor rand_color)
{
    sfColor result;

    result.r = clamp(
        rand_range(raw_color.r - rand_color.r / 2,
            raw_color.r + rand_color.r / 2), 0, 255);
    result.g = clamp(
        rand_range(raw_color.g - rand_color.g / 2,
            raw_color.g + rand_color.g / 2), 0, 255);
    result.b = clamp(
        rand_range(raw_color.b - rand_color.b / 2,
            raw_color.b + rand_color.b / 2), 0, 255);
    result.a = clamp(
        rand_range(raw_color.a - rand_color.a / 2,
            raw_color.a + rand_color.a / 2), 0, 255);
    return result;
}

static void rand_obj_info(obj_info_t *buff, obj_info_t *raw, obj_info_t *rand)
{
    buff->angle = rand_range(raw->angle - rand->angle / 2,
        raw->angle + rand->angle / 2);
    buff->color = rand_color_info(raw->color, rand->color);
    buff->time_stamp = rand_range(raw->time_stamp - rand->time_stamp / 2,
        raw->time_stamp + rand->time_stamp / 2);
    buff->cframe.left = rand_range(raw->cframe.left - rand->cframe.left / 2,
        raw->cframe.left + rand->cframe.left / 2);
    buff->cframe.top = rand_range(raw->cframe.top - rand->cframe.top / 2,
        raw->cframe.top + rand->cframe.top / 2);
    buff->cframe.width = rand_range(raw->cframe.width - rand->cframe.width / 2,
        raw->cframe.width + rand->cframe.width / 2);
    buff->cframe.height = rand_range(raw->cframe.height -
        raw->cframe.height / 2, raw->cframe.height + rand->cframe.height / 2);
}

bool play_emit(linked_list_t *vfxs,
    emit_t *emit, framebuffer_t *fb, sfVector3f origin_pos)
{
    int nb = rand_range(emit->min_nb, emit->max_nb);
    obj_info_t temp_start = {0};
    obj_info_t temp_end = {0};
    linked_list_t *elem = NULL;
    vfx_t *vfx = NULL;

    for (int i = 0; i < nb; i++) {
        rand_obj_info(&temp_start, &emit->start_info, &emit->rands_info);
        rand_obj_info(&temp_end, &emit->final_info, &emit->randf_info);
        elem = create_vfx(vfxs, fb, temp_start, temp_end);
        if (!elem)
            return true;
        vfx = (vfx_t *)elem->data;
        vfx->origin_pos = origin_pos;
        vfx->gravity = emit->gravity;
    }
    return false;
}

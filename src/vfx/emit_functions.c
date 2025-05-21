/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** emit_functions
*/

#include "frame.h"

void emit_splatter(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_s, sfVector3f abs_pos)
{
    sfColor trans = sfColor_fromRGBA(emit_s->color.r,
        emit_s->color.g, emit_s->color.b, 0);
    obj_info_t temps_info = create_obj_info(frct(0, 0, emit_s->sizes,
        emit_s->sizes), 0.0, emit_s->color, 0.0);
    obj_info_t tempf_info = create_obj_info(frct(0, 0, emit_s->sizes,
        emit_s->sizes), 0.0, trans, 0.8);
    emit_t emit = create_emit(10, 25, temps_info, tempf_info);

    temps_info = create_obj_info();
}

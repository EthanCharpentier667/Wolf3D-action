/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** emit_functions
*/

#include "frame.h"

bool emit_splatter(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_s, sfVector3f abs_pos)
{
    sfColor trans = sfColor_fromRGBA(emit_s->color.r,
        emit_s->color.g, emit_s->color.b, 0);
    obj_info_t temps_info = create_obj_info(frct(0, 0, emit_s->sizes,
        emit_s->sizes), 0.0, emit_s->color, 0.0);
    obj_info_t tempf_info = create_obj_info(frct(0, 0, emit_s->sizes,
        emit_s->sizes), 0.0, trans, 2.1);
    emit_t emit = create_emit(4, 25, temps_info, tempf_info);

    temps_info = create_obj_info(frct(0, 0, emit_s->sizes / 7, emit_s->sizes
        / 7), emit_s->rotation, sfColor_fromRGBA(25, 25, 25, 0), 0.0);
    tempf_info = temps_info;
    tempf_info.time_stamp = 1.0;
    tempf_info.cframe = frct(emit_s->strength, emit_s->strength,
        emit_s->sizes / 8, emit_s->sizes / 8);
    set_emit(&emit, temps_info, tempf_info);
    
    return play_emit(vfxs, &emit, fb, abs_pos);
}

bool emit_slow(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_s, sfVector3f abs_pos)
{
    sfColor trans = sfColor_fromRGBA(emit_s->color.r,
        emit_s->color.g, emit_s->color.b, 0);
    obj_info_t temps_info = create_obj_info(frct(0, 0, emit_s->sizes,
        emit_s->sizes), 0.0, emit_s->color, 0.0);
    obj_info_t tempf_info = create_obj_info(frct(0, 0, emit_s->sizes,
        emit_s->sizes), 0.0, trans, 3.3);
    emit_t emit = create_emit(4, 25, temps_info, tempf_info);

    temps_info = create_obj_info(frct(0, 0, emit_s->sizes / 7, emit_s->sizes
        / 7), emit_s->rotation, sfColor_fromRGBA(25, 25, 25, 0), 0.0);
    tempf_info = temps_info;
    tempf_info.time_stamp = 2.3;
    tempf_info.cframe = frct(emit_s->strength, emit_s->strength,
        emit_s->sizes / 8, emit_s->sizes / 8);
    set_emit(&emit, temps_info, tempf_info);
    
    return play_emit(vfxs, &emit, fb, abs_pos);
}

bool absorb_splatter(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_s, sfVector3f abs_pos)
{
    sfColor trans = sfColor_fromRGBA(emit_s->color.r,
        emit_s->color.g, emit_s->color.b, 0);
    obj_info_t tempf_info = create_obj_info(frct(0, 0, emit_s->sizes,
        emit_s->sizes), 0.0, emit_s->color, 2.1);
    obj_info_t temps_info = create_obj_info(frct(0, 0, emit_s->sizes,
        emit_s->sizes), 0.0, trans, 0.0);
    emit_t emit = create_emit(4, 25, temps_info, tempf_info);

    tempf_info = create_obj_info(frct(0, 0, emit_s->sizes / 7, emit_s->sizes
        / 7), emit_s->rotation, sfColor_fromRGBA(25, 25, 25, 0), 1.0);
    temps_info = tempf_info;
    temps_info.time_stamp = 0.0;
    temps_info.cframe = frct(emit_s->strength, emit_s->strength,
        emit_s->sizes / 8, emit_s->sizes / 8);
    set_emit(&emit, temps_info, tempf_info);
    
    return play_emit(vfxs, &emit, fb, abs_pos);
}

bool absorb_slow(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_s, sfVector3f abs_pos)
{
    sfColor trans = sfColor_fromRGBA(emit_s->color.r,
        emit_s->color.g, emit_s->color.b, 0);
    obj_info_t tempf_info = create_obj_info(frct(0, 0, emit_s->sizes,
        emit_s->sizes), 0.0, emit_s->color, 100);
    obj_info_t temps_info = create_obj_info(frct(0, 0, emit_s->sizes,
        emit_s->sizes), 0.0, trans, 0.0);
    emit_t emit = create_emit(4, 25, temps_info, tempf_info);

    tempf_info = create_obj_info(frct(0, 0, emit_s->sizes / 7, emit_s->sizes
        / 7), emit_s->rotation, sfColor_fromRGBA(25, 25, 25, 0), 2.7);
    temps_info = tempf_info;
    temps_info.time_stamp = 0.0;
    temps_info.cframe = frct(emit_s->strength, emit_s->strength,
        emit_s->sizes / 8, emit_s->sizes / 8);
    set_emit(&emit, temps_info, tempf_info);
    
    return play_emit(vfxs, &emit, fb, abs_pos);
}
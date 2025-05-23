/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** emit_functions
*/

#include "frame.h"

bool emit_splatter(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_set, sfVector3f abs_pos)
{
    sfColor trans = sfColor_fromRGBA(emit_set->color.r,
        emit_set->color.g, emit_set->color.b, 0);
    obj_info_t temps_info = create_obj_info(frct(0, 0, emit_set->sizes,
        emit_set->sizes), 0.0, emit_set->color, 0.0);
    obj_info_t tempf_info = create_obj_info(frct(0, 0, emit_set->sizes,
        emit_set->sizes), 0.0, trans, emit_set->lifetime);
    emit_t emit = create_emit(emit_set->nb,
        emit_set->nb + emit_set->nb / 2.5, temps_info, tempf_info);

    temps_info = create_obj_info(frct(0, 0, emit_set->sizes / 7, emit_set->sizes
        / 7), emit_set->rotation, sfColor_fromRGBA(30, 30, 30, 0), 0.0);
    tempf_info = temps_info;
    tempf_info.time_stamp = emit_set->lifetime / 3 + 0.1;
    tempf_info.cframe = frct(emit_set->strength, emit_set->strength,
        emit_set->sizes / 8, emit_set->sizes / 8);
    set_emit(&emit, temps_info, tempf_info, emit_set->gravity);
    return play_emit(vfxs, &emit, fb, abs_pos);
}

bool emit_absorb(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_set, sfVector3f abs_pos)
{
    sfColor trans = sfColor_fromRGBA(emit_set->color.r,
        emit_set->color.g, emit_set->color.b, 0);
    obj_info_t tempf_info = create_obj_info(frct(0, 0, emit_set->sizes,
        emit_set->sizes), 0.0, emit_set->color, 0.0);
    obj_info_t temps_info = create_obj_info(frct(0, 0, emit_set->sizes,
        emit_set->sizes), 0.0, trans, emit_set->lifetime);
    emit_t emit = create_emit(emit_set->nb,
        emit_set->nb + emit_set->nb / 2.5, temps_info, tempf_info);

    tempf_info = create_obj_info(frct(0, 0, emit_set->sizes / 7, emit_set->sizes
        / 7), emit_set->rotation, sfColor_fromRGBA(30, 30, 30, 0),
        emit_set->lifetime / 3 + 0.1);
    temps_info = temps_info;
    temps_info.time_stamp = 0.0;
    temps_info.cframe = frct(emit_set->strength, emit_set->strength,
        emit_set->sizes / 8, emit_set->sizes / 8);
    set_emit(&emit, temps_info, tempf_info, emit_set->gravity);
    return play_emit(vfxs, &emit, fb, abs_pos);
}

bool emit_grow(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_set, sfVector3f abs_pos)
{
    float angle = rand_range(0, emit_set->rotation);
    sfColor trans = sfColor_fromRGBA(emit_set->color.r,
        emit_set->color.g, emit_set->color.b, 0);
    obj_info_t temps_info = create_obj_info(frct(0, 0, 0,
        0), angle, emit_set->color, 0.0);
    obj_info_t tempf_info = create_obj_info(frct(0, 0, emit_set->sizes,
        emit_set->sizes), angle, trans, emit_set->lifetime);
    emit_t emit = create_emit(emit_set->nb,
        emit_set->nb + emit_set->nb / 2.5, temps_info, tempf_info);

    temps_info = create_obj_info(frct(0, 0, 0, 0
        ), 0, sfColor_fromRGBA(30, 30, 30, 0), 0.0);
    tempf_info = temps_info;
    tempf_info.time_stamp = emit_set->lifetime / 3 + 0.1;
    tempf_info.cframe = frct(emit_set->strength, emit_set->strength,
        emit_set->sizes / 5, emit_set->sizes / 5);
    set_emit(&emit, temps_info, tempf_info, emit_set->gravity);
    return play_emit(vfxs, &emit, fb, abs_pos);
}

bool emit_burst(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_set, sfVector3f abs_pos)
{
    float strength = emit_set->strength;
    sfColor trans = sfColor_fromRGBA(emit_set->color.r,
        emit_set->color.g, emit_set->color.b, 0);
    obj_info_t temps_info = create_obj_info(frct(0, 0, emit_set->sizes,
        emit_set->sizes), 0.0, emit_set->color, 0.0);
    obj_info_t tempf_info = create_obj_info(frct(0, -strength / 1.3,
        emit_set->sizes, emit_set->sizes), 0.0, trans, emit_set->lifetime);
    emit_t emit = create_emit(emit_set->nb,
        emit_set->nb + emit_set->nb / 2.5, temps_info, tempf_info);

    temps_info = create_obj_info(frct(0, 0, emit_set->sizes / 7, emit_set->sizes
        / 7), emit_set->rotation, sfColor_fromRGBA(30, 30, 30, 0), 0.0);
    tempf_info = temps_info;
    tempf_info.time_stamp = emit_set->lifetime / 3 + 0.1;
    tempf_info.cframe = frct(rand_range(-strength * 3,
        strength * 3), rand_range(0, -strength / 1.3),
        emit_set->sizes / 8, emit_set->sizes / 8);
    set_emit(&emit, temps_info, tempf_info, emit_set->gravity);
    return play_emit(vfxs, &emit, fb, abs_pos);
}

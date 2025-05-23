/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** tim_vfx
*/

#include "frame.h"

bool vfx_blood(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = 0;

    emit_set = create_emit_settings(25.0, 0.085, 150.0,
        sfColor_fromRGBA(190, 20, 0, 255));
    set_emit_settings(&emit_set, 0.6, 12, 10);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.droplet,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(35.0, 0.035, 150.0,
        sfColor_fromRGBA(180, 20, 0, 255));
    set_emit_settings(&emit_set, 0.6, 10, 10);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.droplet,
        &emit_set, abs_pos);
    return (bool)err;
}
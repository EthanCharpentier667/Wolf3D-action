/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** tim_vfx
*/

#include "frame.h"

bool vfx_dust_impact(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = 0;

    emit_set = create_emit_settings(30.0, 0.1, 360.0,
        sfColor_fromRGBA(210, 210, 210, 120));
    set_emit_settings(&emit_set, 1.5, 6, 7);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.smoke,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(30.0, 0.2, 360.0,
        sfColor_fromRGBA(190, 190, 190, 130));
    set_emit_settings(&emit_set, 1.8, 5, 4);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.smoke,
        &emit_set, abs_pos);
    return (bool)err;
}
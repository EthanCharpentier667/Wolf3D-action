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

    emit_set = create_emit_settings(40.0, 0.1, 360.0,
        sfColor_fromRGBA(150, 150, 150, 70));
    set_emit_settings(&emit_set, 1.2, 8, 10);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.smoke,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(35.0, 0.2, 360.0,
        sfColor_fromRGBA(150, 150, 150, 130));
    set_emit_settings(&emit_set, 1.4, 7, 6);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.smoke,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(50.0, 0.03, 360.0,
        sfColor_fromRGBA(160, 150, 140, 255));
    set_emit_settings(&emit_set, 0.4, 13, 300);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.droplet,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(0, 0.35, 0.0,
        sfColor_fromRGBA(255, 255, 240, 255));
    set_emit_settings(&emit_set, 0.18, 1, 0);
    err += emit_grow(UI->vfx_infos.vfxs, UI->vfx_infos.impact,
        &emit_set, abs_pos);
    return (bool)err;
}
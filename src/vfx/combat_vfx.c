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

    emit_set = create_emit_settings(25.0, 0.04, 150.0,
        sfColor_fromRGBA(190, 20, 0, 255));
    set_emit_settings(&emit_set, 0.6, 20, 190);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.droplet,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(60.0, 0.01, 150.0,
        sfColor_fromRGBA(180, 20, 0, 255));
    set_emit_settings(&emit_set, 0.6, 16, 250);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.droplet,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(0, 0.5, 360,
        sfColor_fromRGBA(255, 130, 130, 255));
    set_emit_settings(&emit_set, 0.3, 1, 0);
    err += emit_grow(UI->vfx_infos.vfxs, UI->vfx_infos.impact,
        &emit_set, abs_pos);
    return (bool)err;
}

bool vfx_bullet_drop(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = 0;

    emit_set = create_emit_settings(35, 0.2, 360.0,
        sfColor_fromRGBA(250, 250, 250, 4));
    set_emit_settings(&emit_set, 3.5, 4, -10);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.smoke,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(40, 0.03, 1000,
        sfColor_fromRGBA(255, 255, 255, 255));
    set_emit_settings(&emit_set, 0.9, 1, 300);
    err += emit_burst(UI->vfx_infos.vfxs, UI->vfx_infos.bullet,
        &emit_set, abs_pos);
    return (bool)err;
}

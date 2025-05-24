/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** tim_vfx
*/

#include "frame.h"

static unsigned int vfx_emit_smoke_and_droplets(frame_t *frame,
    sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = 0;

    emit_set = create_emit_settings(40.0, 0.1, 360.0,
        sfColor_fromRGBA(110, 110, 110, 70));
    set_emit_settings(&emit_set, 1.2, 8, 10);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.smoke,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(35.0, 0.2, 360.0,
        sfColor_fromRGBA(110, 110, 110, 130));
    set_emit_settings(&emit_set, 1.4, 7, 6);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.smoke,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(50.0, 0.03, 360.0,
        sfColor_fromRGBA(160, 150, 140, 255));
    set_emit_settings(&emit_set, 0.4, 13, 300);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.droplet,
        &emit_set, abs_pos);
    return err;
}

bool vfx_dust_impact(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = vfx_emit_smoke_and_droplets(frame, abs_pos);

    emit_set = create_emit_settings(0, 0.35, 360,
        sfColor_fromRGBA(255, 255, 240, 255));
    set_emit_settings(&emit_set, 0.18, 1, 0);
    err += emit_grow(UI->vfx_infos.vfxs, UI->vfx_infos.impact,
        &emit_set, abs_pos);
    return (bool)err;
}

bool vfx_grab(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = 0;

    emit_set = create_emit_settings(35.0, 0.03, 360.0,
        sfColor_fromRGBA(160, 150, 140, 100));
    set_emit_settings(&emit_set, 0.2, 7, 0);
    err += emit_absorb(UI->vfx_infos.vfxs, UI->vfx_infos.droplet,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(0, 0.35, 60,
        sfColor_fromRGBA(255, 255, 255, 255));
    set_emit_settings(&emit_set, 0.3, 1, 0);
    err += emit_shrink(UI->vfx_infos.vfxs, UI->vfx_infos.star,
        &emit_set, abs_pos);
    return (bool)err;
}

bool vfx_unlock(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = 0;

    emit_set = create_emit_settings(0, 1, 20,
        sfColor_fromRGBA(170, 220, 255, 50));
    set_emit_settings(&emit_set, 1.5, 1, 0);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.unlocked,
        &emit_set, abs_pos);
    return (bool)err;
}

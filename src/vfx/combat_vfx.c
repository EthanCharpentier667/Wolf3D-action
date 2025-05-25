/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** tim_vfx
*/

#include "frame.h"

static unsigned int vfx_emit_blood_splatter(frame_t *frame, sfVector3f abs_pos)
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
    return err;
}

bool vfx_blood(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = vfx_emit_blood_splatter(frame, abs_pos);

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

static bool emit_splatter_color(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_set, sfVector3f abs_pos)
{
    sfColor trans = {70, 0, 0, 0};
    obj_info_t temps_info = create_obj_info(frct(0, 0, 0,
        0), 0.0, emit_set->color, 0.0);
    obj_info_t tempf_info = create_obj_info(frct(0, 0, emit_set->sizes,
        emit_set->sizes), 0.0, trans, emit_set->lifetime);
    emit_t emit = create_emit(emit_set->nb,
        emit_set->nb + emit_set->nb / 2.5, temps_info, tempf_info);

    temps_info = create_obj_info(frct(0, 0, 0,
        0), emit_set->rotation,
        sfColor_fromRGBA(30, 30, 30, 0), 0.0);
    tempf_info = temps_info;
    tempf_info.time_stamp = emit_set->lifetime / 3 + 0.1;
    tempf_info.cframe = frct(emit_set->strength, emit_set->strength,
        emit_set->sizes / 10, emit_set->sizes / 10);
    set_emit(&emit, temps_info, tempf_info, emit_set->gravity);
    return play_emit(vfxs, &emit, fb, abs_pos);
}

static unsigned int vfx_emit_explosion_smoke(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = 0;

    emit_set = create_emit_settings(300, 3.8, 400.0,
        sfColor_fromRGBA(150, 150, 150, 100));
    set_emit_settings(&emit_set, 4, 7, 60);
    err += emit_splatter_color(UI->vfx_infos.vfxs,
        UI->vfx_infos.fireball, &emit_set, abs_pos);
    emit_set = create_emit_settings(280, 3.8, 400.0,
        sfColor_fromRGBA(50, 20, 10, 200));
    set_emit_settings(&emit_set, 3.3, 3, 30);
    err += emit_splatter_color(UI->vfx_infos.vfxs,
        UI->vfx_infos.fireball, &emit_set, abs_pos);
    emit_set = create_emit_settings(280, 2.8, 400.0,
        sfColor_fromRGBA(255, 190, 30, 255));
    set_emit_settings(&emit_set, 1.9, 5, 40);
    err += emit_splatter_color(UI->vfx_infos.vfxs,
        UI->vfx_infos.fireball, &emit_set, abs_pos);
    return err;
}


static unsigned int vfx_emit_explosion_light(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = 0;

    emit_set = create_emit_settings(300, 0.05, 150.0,
        sfColor_fromRGBA(255, 240, 170, 255));
    set_emit_settings(&emit_set, 1, 9, 400);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.droplet,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(0, 15, 0,
        sfColor_fromRGBA(255, 250, 230, 90));
    set_emit_settings(&emit_set, 0.25, 1, 0);
    err += emit_splatter(UI->vfx_infos.vfxs,
        UI->vfx_infos.droplet, &emit_set, abs_pos);
    emit_set = create_emit_settings(0, 3, 360.0,
        sfColor_fromRGBA(255, 0, 0, 255));
    set_emit_settings(&emit_set, 0.5, 1, 0);
    err += emit_grow(UI->vfx_infos.vfxs,
        UI->vfx_infos.impact, &emit_set, abs_pos);
    return (bool)err;
}

static unsigned int vfx_emit_explosion_addon(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = 0;

    emit_set = create_emit_settings(330, 0.09, 500.0,
        sfColor_fromRGBA(150, 150, 150, 255));
    set_emit_settings(&emit_set, 3, 16, 300);
    err += emit_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.droplet,
        &emit_set, abs_pos);
    emit_set = create_emit_settings(0, 4.3, 0.0,
        sfColor_fromRGBA(255, 230, 190, 70));
    set_emit_settings(&emit_set, 0.42, 1, 0);
    err += emit_grow(UI->vfx_infos.vfxs,
        UI->vfx_infos.unlocked, &emit_set, abs_pos);
    emit_set = create_emit_settings(0, 1.5, 0,
        sfColor_fromRGBA(255, 250, 140, 110));
    set_emit_settings(&emit_set, 0.22, 1, 0);
    err += emit_splatter(UI->vfx_infos.vfxs,
        UI->vfx_infos.droplet, &emit_set, abs_pos);
    return (bool)err;
}

bool vfx_explosion(frame_t *frame, sfVector3f abs_pos)
{
    emit_settings_t emit_set = {0};
    unsigned int err = 0;

    vfx_emit_explosion_smoke(frame, abs_pos);
    emit_set = create_emit_settings(280, 3.5, 400.0,
        sfColor_fromRGBA(255, 110, 30, 255));
    set_emit_settings(&emit_set, 2.5, 5, 40);
    err += emit_splatter_color(UI->vfx_infos.vfxs,
        UI->vfx_infos.fireball, &emit_set, abs_pos);
    vfx_emit_explosion_addon(frame, abs_pos);
    vfx_emit_explosion_light(frame, abs_pos);
    return (bool)err;
}

static sfVector3f get_hitler_pos(frame_t *frame)
{
    enemy_t *hitler = NULL;

    for (int i = 0; i < frame->game->nb_enemies; i++) {
        if (frame->game->enemies[i].type == HITLER2)
            hitler = &frame->game->enemies[i];
    }
    if (hitler)
        return hitler->pos;
    return v3f(0, 0, 0);
}

bool end_explosions(frame_t *frame)
{
    static unsigned int explosions = 9;
    static float elapsed = 0;
    static float since_last = 0;
    const float interval = 300.0f;
    const float rand = 10.0f;

    if (!frame->victory || explosions == 0)
        return false;
    elapsed += PLAYER->delta_time * 1000.0f;
    since_last += PLAYER->delta_time * 1000.0f;
    if (since_last >= interval) {
        sfVector3f pos = get_hitler_pos(frame);
        pos.x = rand_range(pos.x - rand, pos.x + rand);
        pos.y = rand_range(pos.y - rand, pos.y + rand);
        pos.z = rand_range(pos.z - rand, pos.z + rand) / 100.0f;
        explosions--;
        since_last = 0.0f;
        return vfx_explosion(frame, pos);
    }
    return false;
}

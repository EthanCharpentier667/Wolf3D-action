/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** init_vfx
*/

#include "frame.h"

bool init_vfxs(frame_t *frame)
{
    int err = 0;
    vfxs_infos_t *vfx_infos = &UI->vfx_infos;

    err += framebuffer_create("src/assets/logo.png", &vfx_infos->sparkle);
    err += framebuffer_create("src/assets/vfx_assets/smoke.png",
        &vfx_infos->smoke);
    err += framebuffer_create("src/assets/vfx_assets/droplet.png",
        &vfx_infos->droplet);
    err += framebuffer_create("src/assets/vfx_assets/splash.png",
        &vfx_infos->splash);
    err += framebuffer_create("src/assets/vfx_assets/impact.png",
        &vfx_infos->impact);
    err += framebuffer_create("src/assets/vfx_assets/bullet.png",
        &vfx_infos->bullet);
    err += framebuffer_create("src/assets/vfx_assets/4star.png",
        &vfx_infos->star);
    vfx_infos->vfxs = create_lists(NULL, 1);
    err += !vfx_infos->vfxs;
    return !(bool)err;
}

void free_vfx(void *data)
{
    vfx_t *vfx = (vfx_t *)data;

    if (vfx->particle != NULL) {
        sfSprite_destroy(vfx->particle);
    }
    free(vfx);
}

void free_vfxs(frame_t *frame)
{
    framebuffer_destroy(UI->vfx_infos.sparkle);
    free_list(UI->vfx_infos.vfxs, free_vfx);
}

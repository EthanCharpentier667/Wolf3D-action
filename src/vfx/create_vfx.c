/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** create_vfx
*/

#include "frame.h"

void set_framebuffer_to_sprite(vfx_t *vfx, framebuffer_t *fb)
{
    sfTexture *texture = sfTexture_create(fb->size.x, fb->size.y);
    sfSprite *sprite = sfSprite_create();

    if (!texture || !sprite)
        return;
    sfTexture_updateFromPixels(texture, fb->pixels, fb->size.x,
        fb->size.y, 0, 0);
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setOrigin(sprite,
        v2f(fb->size.x / 2.0, fb->size.y / 2.0));
    vfx->particle = sprite;
}

linked_list_t *create_vfx(linked_list_t *vfxs, framebuffer_t *fb,
    obj_info_t info, obj_info_t f_info)
{
    vfx_t *vfx = malloc(sizeof(vfx_t));
    linked_list_t *new_node = NULL;

    if (!vfx)
        return NULL;
    memset(vfx, 0, sizeof(vfx_t));
    vfx->info = info;
    vfx->s_info = info;
    vfx->f_info = f_info;
    set_framebuffer_to_sprite(vfx, fb);
    new_node = add_element(vfxs, vfx);
    if (!new_node) {
        free(vfx);
        return NULL;
    }
    return new_node;
}

/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** vfx
*/

#include "frame.h"

#ifndef VFX_H_
    #define VFX_H_

typedef struct player_s player_t;

typedef struct linked_list_s {
    void *data;
    int id;
    struct linked_list_s *next;
    struct linked_list_s *previous;
} linked_list_t;

typedef struct framebuffer {
    sfVector2u size;
    sfUint8 *pixels;
} framebuffer_t;

typedef struct {
    sfFloatRect cframe;
    float angle;
    sfColor color;
    float time_stamp;
} obj_info_t;

typedef struct {
    sfSprite *particle;
    obj_info_t info;
    obj_info_t s_info;
    obj_info_t f_info;
    sfVector3f origin_pos;
} vfx_t;

linked_list_t *create_lists(void *data, int len);
linked_list_t *add_element(linked_list_t *head, void *data);
void *del_element(linked_list_t *head, linked_list_t *element);
void free_list(linked_list_t *head, void (*free_func)(void *));

framebuffer_t *framebuffer_alloc(sfVector2u size);
void framebuffer_destroy(framebuffer_t *buffer);
void my_put_pixel(framebuffer_t *buffer, unsigned int x,
    unsigned int y, sfColor color);
bool framebuffer_create(const char *filepath, framebuffer_t **fb);

obj_info_t to_obj_info(sfFloatRect cframe, float angle,
    sfColor color, float time_stamp);
sfFloatRect calculate_vfx_render(player_t *player,
    sfVector3f vfx_pos, sfFloatRect addon);

bool init_vfxs(frame_t *frame);
void free_vfx(void *data);
void free_vfxs(frame_t *frame);
bool update_vfx(vfx_t *vfx, float delta_time);
void update_vfxs(linked_list_t *vfxs, float delta_time);
void draw_vfxs(player_t *player, sfRenderWindow *window, linked_list_t *vfxs);
void set_framebuffer_to_sprite(vfx_t *vfx, framebuffer_t *fb);
linked_list_t *create_vfx(linked_list_t *vfxs, framebuffer_t *fb,
    obj_info_t info, obj_info_t f_info);

#endif /* !VFX_H_ */

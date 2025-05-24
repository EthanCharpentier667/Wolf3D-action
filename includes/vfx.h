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
    float gravity;
    float velocity;
} vfx_t;

typedef struct emit_s {
    unsigned int min_nb;
    unsigned int max_nb;
    obj_info_t start_info;
    obj_info_t final_info;
    obj_info_t randf_info;
    obj_info_t rands_info;
    float gravity;
} emit_t;

typedef struct emit_settings_s {
    float strength;
    float sizes;
    float rotation;
    sfColor color;
    float gravity;
    float lifetime;
    unsigned int nb;
} emit_settings_t;

typedef struct {
    framebuffer_t *sparkle;
    framebuffer_t *smoke;
    framebuffer_t *droplet;
    framebuffer_t *splash;
    framebuffer_t *impact;
    framebuffer_t *bullet;
    framebuffer_t *star;
    linked_list_t *vfxs;
} vfxs_infos_t;

typedef struct {
    float forward;
    float sideways;
} vfx_view_vector_t;

typedef struct {
    int left;
    int right;
    float forward;
} vfx_screen_bounds_t;

linked_list_t *create_lists(void *data, int len);
linked_list_t *add_element(linked_list_t *head, void *data);
void *del_element(linked_list_t *head, linked_list_t *element);
void free_list(linked_list_t *head, void (*free_func)(void *));

framebuffer_t *framebuffer_alloc(sfVector2u size);
void framebuffer_destroy(framebuffer_t *buffer);
void my_put_pixel(framebuffer_t *buffer, unsigned int x,
    unsigned int y, sfColor color);
bool framebuffer_create(const char *filepath, framebuffer_t **fb);

obj_info_t create_obj_info(sfFloatRect cframe, float angle,
    sfColor color, float time_stamp);
sfFloatRect calculate_vfx_render(player_t *player,
    sfVector3f vfx_pos, sfFloatRect addon, float velocity);
sfVector3f get_front(player_t *player, float range, sfVector3f addon);

bool init_vfxs(frame_t *frame);
void free_vfx(void *data);
void free_vfxs(frame_t *frame);
bool update_vfx(vfx_t *vfx, float delta_time);
void update_vfxs(linked_list_t *vfxs, float delta_time);
void draw_vfxs(frame_t *frame, sfRenderWindow *window);
void set_framebuffer_to_sprite(vfx_t *vfx, framebuffer_t *fb);
linked_list_t *create_vfx(linked_list_t *vfxs, framebuffer_t *fb,
    obj_info_t info, obj_info_t f_info);

emit_t create_emit(unsigned int min_nb, unsigned int max_nb,
    obj_info_t s_infos, obj_info_t f_infos);
bool set_emit(emit_t *buff, obj_info_t rands_infos,
    obj_info_t randf_info, float gravity);
bool play_emit(linked_list_t *vfxs,
    emit_t *emit, framebuffer_t *fb, sfVector3f origin_pos);
emit_settings_t create_emit_settings(float strength, float sizes,
    float rot, sfColor color);
void set_emit_settings(emit_settings_t *emit_set,
    float life_time, unsigned int nb, float gravity);

bool emit_splatter(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_set, sfVector3f abs_pos);
bool emit_absorb(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_set, sfVector3f abs_pos);
bool emit_grow(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_set, sfVector3f abs_pos);
bool emit_burst(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_set, sfVector3f abs_pos);
bool emit_shrink(linked_list_t *vfxs, framebuffer_t *fb,
    emit_settings_t *emit_set, sfVector3f abs_pos);

bool vfx_dust_impact(frame_t *frame, sfVector3f abs_pos);
bool vfx_blood(frame_t *frame, sfVector3f abs_pos);
bool vfx_bullet_drop(frame_t *frame, sfVector3f abs_pos);

void impact_wall(frame_t *frame, float range);

#endif /* !VFX_H_ */

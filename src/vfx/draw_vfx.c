/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** create_vfx
*/

#include "frame.h"

static void set_vfx_info(obj_info_t *info, obj_info_t *s_info,
    obj_info_t *f_info, float ratio)
{
    info->cframe.left = s_info->cframe.left +
        (f_info->cframe.left - s_info->cframe.left) * ratio;
    info->cframe.top = s_info->cframe.top +
        (f_info->cframe.top - s_info->cframe.top) * ratio;
    info->cframe.width = s_info->cframe.width +
        (f_info->cframe.width - s_info->cframe.width) * ratio;
    info->cframe.height = s_info->cframe.height +
        (f_info->cframe.height - s_info->cframe.height) * ratio;
    info->angle = s_info->angle + (f_info->angle - s_info->angle) * ratio;
    info->color.r = s_info->color.r +
        (f_info->color.r - s_info->color.r) * ratio;
    info->color.g = s_info->color.g +
        (f_info->color.g - s_info->color.g) * ratio;
    info->color.b = s_info->color.b +
        (f_info->color.b - s_info->color.b) * ratio;
    info->color.a = s_info->color.a +
        (f_info->color.a - s_info->color.a) * ratio;
}

static bool update_vfx_info(vfx_t *vfx, float delta_time)
{
    obj_info_t *infos = &vfx->info;
    obj_info_t *s_infos = &vfx->s_info;
    obj_info_t *f_infos = &vfx->f_info;
    float life_time = f_infos->time_stamp - s_infos->time_stamp;
    float ratio = (infos->time_stamp - s_infos->time_stamp) / life_time;

    if (infos->time_stamp >= f_infos->time_stamp)
        return true;
    set_vfx_info(infos, s_infos, f_infos, ratio);
    infos->time_stamp += delta_time;
    return false;
}

bool update_vfx(vfx_t *vfx, float delta_time)
{
    if (update_vfx_info(vfx, delta_time))
        return true;
    sfSprite_setPosition(vfx->particle,
        v2f(vfx->info.cframe.left, vfx->info.cframe.top));
    sfSprite_setScale(vfx->particle,
        v2f(vfx->info.cframe.width, vfx->info.cframe.height));
    sfSprite_setColor(vfx->particle, vfx->info.color);
    sfSprite_setRotation(vfx->particle, vfx->info.angle);
    if (vfx->gravity > 0)
        vfx->velocity = pow(vfx->gravity, vfx->info.time_stamp * 0.7);
    else
        vfx->velocity = pow(vfx->gravity * -1,
            vfx->info.time_stamp * 0.7) * -1;
    return false;
}

void update_vfxs(linked_list_t *vfxs, float delta_time)
{
    linked_list_t *current = vfxs->next;
    linked_list_t *next = NULL;
    vfx_t *temp_vfx = NULL;

    while (current && current->id > 0) {
        next = current->next;
        temp_vfx = (vfx_t *)current->data;
        if (!temp_vfx) {
            del_element(vfxs, current);
            current = next;
            continue;
        }
        if (update_vfx(temp_vfx, delta_time))
            sfSprite_destroy(del_element(vfxs, current));
        current = next;
    }
}

static vfx_view_vector_t get_vfx_view_vector(sfVector3f pos, player_t *player)
{
    float dx = pos.x - player->pos.x;
    float dy = pos.y - player->pos.y;
    float dir_x = cosf(player->angle.x);
    float dir_y = sinf(player->angle.x);
    float right_dir_x = -sinf(player->angle.x);
    float right_dir_y = cosf(player->angle.x);
    vfx_view_vector_t result = {0};

    result.forward = dx * dir_x + dy * dir_y;
    result.sideways = dx * right_dir_x + dy * right_dir_y;
    return result;
}

static vfx_screen_bounds_t get_vfx_screen_bounds(sfVector3f pos,
    sfFloatRect addon, player_t *player)
{
    vfx_view_vector_t view = get_vfx_view_vector(pos, player);
    vfx_screen_bounds_t bounds = {0};
    float forward = view.forward;
    float sideways = view.sideways;
    int base_screen_x = 0;
    float projected_width = 0;
    int l_screen_x = 0;
    int r_screen_x = 0;

    if (forward < 0.01f)
        forward = 0.01f;
    base_screen_x = (int)(WINDOWX / 2 + sideways /
        forward * (WINDOWX / 2) / tanf(FOV / 2));
    projected_width = addon.width / 8 *
        TILE_SIZE * WINDOWY / forward;
    l_screen_x = (int)(base_screen_x +
        addon.left / 2 * WINDOWX / forward);
    r_screen_x = (int)(l_screen_x + projected_width);
    bounds = (vfx_screen_bounds_t){l_screen_x, r_screen_x, forward};
    return bounds;
}

static bool obstructed_vfx(sfVector3f pos, sfFloatRect addon, frame_t *frame)
{
    int left = 0;
    int right = 0;
    vfx_screen_bounds_t bounds = get_vfx_screen_bounds(pos, addon, PLAYER);

    if (bounds.forward < 0.01f)
        return true;
    if (bounds.right < 0 || bounds.left >= WINDOWX)
        return true;
    left = bounds.left < 0 ? 0 : bounds.left;
    right = bounds.right >= WINDOWX ? WINDOWX - 1 : bounds.right;
    for (int x = left; x <= right; x++) {
        if (bounds.forward >= frame->z_buffer[x])
            return true;
    }
    return false;
}

void draw_vfxs(frame_t *frame, sfRenderWindow *window)
{
    player_t *player = PLAYER;
    linked_list_t *vfxs = frame->ui->vfx_infos.vfxs;
    vfx_t *vfx = NULL;
    sfFloatRect rect = {0, 0, 0, 0};
    sfVector2u tex_size = {0, 0};
    sfVector2f scale = {0};

    for (linked_list_t *elem = vfxs->next; elem->id > 0; elem = elem->next) {
        vfx = (vfx_t *)elem->data;
        if (obstructed_vfx(vfx->origin_pos, vfx->info.cframe, frame))
            continue;
        rect = calculate_vfx_render(player, vfx->origin_pos,
            vfx->info.cframe, vfx->velocity);
        tex_size = sfTexture_getSize(sfSprite_getTexture(vfx->particle));
        scale.x = rect.width / (float)tex_size.x;
        scale.y = rect.height / (float)tex_size.y;
        sfSprite_setPosition(vfx->particle, v2f(rect.left, rect.top));
        sfSprite_setScale(vfx->particle, scale);
        sfRenderWindow_drawSprite(window, vfx->particle, NULL);
    }
}

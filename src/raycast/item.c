/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** item
*/

#include "frame.h"

static void calculate_item_position(frame_t *frame, sfVector3f itempos,
    sfTexture *item_texture, item_render_data_t *data)
{
    data->dx = itempos.x - PLAYER->pos.x;
    data->dy = itempos.y - PLAYER->pos.y;
    data->distance = sqrtf(data->dx * data->dx + data->dy * data->dy);
    data->angle_to_item = atan2f(data->dy, data->dx);
    data->rel_angle = data->angle_to_item - PLAYER->angle;
    while (data->rel_angle < - M_PI)
        data->rel_angle += 2 * M_PI;
    while (data->rel_angle > M_PI)
        data->rel_angle -= 2 * M_PI;
    data->screen_x = (int)((data->rel_angle + FOV / 2) / FOV * WINDOWX);
    data->ceiling_height = itempos.z;
    data->tex_size = sfTexture_getSize(item_texture);
}

static void calculate_item_dimensions(item_render_data_t *data,
    sfVector2f scale)
{
    data->projected_height = TILE_SIZE * WINDOWY / data->distance * scale.y;
    data->scale_factor = data->projected_height
        / (float)data->tex_size.y;
    data->sprite_width = (float)data->tex_size.x
        * data->scale_factor * scale.x;
    data->sprite_height = data->tex_size.y * data->scale_factor * scale.y;
    data->sprite_start_x = data->screen_x - data->sprite_width / 2;
    data->sprite_end_x = data->screen_x + data->sprite_width / 2;
    data->vertical_offset = WINDOWY / 2 - data->projected_height;
    data->vertical_offset -= (data->ceiling_height * WINDOWY)
        / (data->distance * 4);
}

static void render_item_columns(frame_t *frame, sfTexture *item_texture,
    item_render_data_t *data, sfVector2f scale)
{
    float tex_percent_x = 0;
    int tex_x = 0;
    sfSprite *sprite = sfSprite_create();
    sfIntRect subrect = {0, 0, 0, 0};

    for (int x = data->sprite_start_x; x < data->sprite_end_x; x++) {
        if (x < 0 || x >= WINDOWX || data->distance >= frame->z_buffer[x])
            continue;
        tex_percent_x = (float)(x - data->sprite_start_x) / data->sprite_width;
        tex_x = tex_percent_x * data->tex_size.x;
        sfSprite_setTexture(sprite, item_texture, sfTrue);
        subrect = irct(tex_x, 0, 1, (int)data->tex_size.y);
        sfSprite_setTextureRect(sprite, subrect);
        sfSprite_setPosition(sprite, v2f((float)x, data->vertical_offset));
        sfSprite_setScale(sprite, v2f(1.0f, data->scale_factor * scale.y));
        sfRenderWindow_drawSprite(WINDOW, sprite, NULL);
    }
    sfSprite_destroy(sprite);
}

void draw_item(frame_t *frame, sfVector3f itempos,
    sfTexture *item_texture, sfVector2f scale)
{
    item_render_data_t data = {0};

    calculate_item_position(frame, itempos, item_texture, &data);
    calculate_item_dimensions(&data, scale);
    render_item_columns(frame, item_texture, &data, scale);
}

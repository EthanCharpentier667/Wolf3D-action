/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** item
*/

#include "frame.h"

void calculate_item_position(frame_t *frame, sfVector3f itempos,
    sfTexture *item_texture, item_render_data_t *data)
{
    data->dx = itempos.x - PLAYER->pos.x;
    data->dy = itempos.y - PLAYER->pos.y;
    data->distance = sqrtf(data->dx * data->dx + data->dy * data->dy);
    data->angle_to_item = atan2f(data->dy, data->dx);
    data->rel_angle = data->angle_to_item - PLAYER->angle.x;
    while (data->rel_angle < - M_PI)
        data->rel_angle += 2 * M_PI;
    while (data->rel_angle > M_PI)
        data->rel_angle -= 2 * M_PI;
    data->screen_x = (int)((data->rel_angle + FOV / 2) / FOV * WINDOWX);
    data->ceiling_height = itempos.z;
    data->tex_size = sfTexture_getSize(item_texture);
}

void calculate_item_dimensions(item_render_data_t *data,
    sfVector2f scale, player_t *player, sfVector3f itempos)
{
    float perp_distance = data->distance * cosf(data->rel_angle);

    data->projected_height = TILE_SIZE * WINDOWY / perp_distance * scale.y;
    data->scale_factor = data->projected_height / (float)data->tex_size.y;
    data->sprite_width = (float)data->tex_size.x *
        data->scale_factor * scale.x;
    data->sprite_height = data->tex_size.y * data->scale_factor * scale.y;
    data->sprite_start_x = data->screen_x - data->sprite_width / 2;
    data->sprite_end_x = data->screen_x + data->sprite_width / 2;
    data->vertical_offset = WINDOWY / 2 - data->projected_height / 2;
    data->vertical_offset += (int)(WINDOWY * tanf(player->angle.y) / 2);
    data->vertical_offset -= (itempos.z * TILE_SIZE) / perp_distance;
}

void render_item_columns(frame_t *frame, sfTexture *item_texture,
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

void draw_item(frame_t *frame, item_t *item)
{
    item_render_data_t data = {0};
    char *name = NULL;

    calculate_item_position(frame, item->pos, item->texture, &data);
    calculate_item_dimensions(&data, item->scale, PLAYER, item->pos);
    if (data.distance > 1000.0f)
        return;
    render_item_columns(frame, item->texture, &data, item->scale);
    if (item->pickable && data.distance < 100.0f) {
        name = malloc(strlen(item->name) + 5);
        if (name != NULL) {
            snprintf(name, strlen(item->name) + 5, "[E] %s", item->name);
            draw_3d_text(frame, v3f(item->pos.x, item->pos.y,
                item->pos.z + data.tex_size.y * item->scale.y),
                name, v2f(0.4f, 0.4f));
            free(name);
        }
    }
}

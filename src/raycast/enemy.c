/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** enemy
*/

#include "frame.h"

static void calculate_enemy_position(frame_t *frame, int index,
    item_render_data_t *data)
{
    data->dx = ENEMY[index].pos.x - PLAYER->pos.x;
    data->dy = ENEMY[index].pos.y - PLAYER->pos.y;
    data->distance = sqrtf(data->dx * data->dx + data->dy * data->dy);
    data->angle_to_item = atan2f(data->dy, data->dx);
    data->rel_angle = data->angle_to_item - PLAYER->angle.x;
    while (data->rel_angle < - M_PI)
        data->rel_angle += 2 * M_PI;
    while (data->rel_angle > M_PI)
        data->rel_angle -= 2 * M_PI;
    data->screen_x = (int)((data->rel_angle + FOV / 2) / FOV * WINDOWX);
    data->ceiling_height = ENEMY[index].pos.z;
    data->tex_size = sfTexture_getSize(ENEMY[index].texture);
    data->pos = ENEMY[index].pos;
}

static void calculate_enemy_dimensions(item_render_data_t *data,
    frame_t *frame, int index)
{
    float perp_distance = data->distance * cosf(data->rel_angle);
    enemy_t enemy = ENEMY[index];
    sfVector2f scale = enemy.scale;
    sfVector3f enemypos = enemy.pos;
    int sprite_height = enemy.rec.height > 0 ?
        enemy.rec.height : (int)data->tex_size.y;
    int sprite_width = enemy.rec.width > 0 ?
        enemy.rec.width : (int)data->tex_size.x;

    data->projected_height = TILE_SIZE * WINDOWY / perp_distance * scale.y;
    data->scale_factor = data->projected_height / (float)data->tex_size.y;
    data->sprite_width = (float)sprite_width * data->scale_factor * scale.x;
    data->sprite_height = sprite_height * data->scale_factor * scale.y;
    data->sprite_start_x = data->screen_x - data->sprite_width / 2;
    data->sprite_end_x = data->screen_x + data->sprite_width / 2;
    data->vertical_offset = WINDOWY / 2 - data->projected_height / 2;
    data->vertical_offset += (int)(WINDOWY * tanf(PLAYER->angle.y) / 2);
    data->vertical_offset -=
        (enemypos.z * TILE_SIZE * WINDOWY) / perp_distance;
}

static void draw_enemy_column(sfSprite *sprite, enemy_t *enemy,
    item_render_data_t *data, int x)
{
    float tex_percent_x = 0;
    int tex_x = 0;
    sfIntRect subrect = {0, 0, 0, 0};

    tex_percent_x = (float)(x - data->sprite_start_x) / data->sprite_width;
    tex_x = enemy->rec.left + (tex_percent_x * enemy->rec.width);
    subrect = irct(tex_x, enemy->rec.top, 1, enemy->rec.height);
    sfSprite_setTextureRect(sprite, subrect);
    sfSprite_setPosition(sprite, v2f((float)x, data->vertical_offset));
    sfSprite_setScale(sprite, v2f(1, data->scale_factor * enemy->scale.y));
}

static void render_enemy_columns(frame_t *frame, int index,
    item_render_data_t *data)
{
    sfSprite *sprite = sfSprite_create();
    enemy_t enemy = ENEMY[index];
    float perp_distance = data->distance * cosf(data->rel_angle);

    if (fabs(data->rel_angle) > FOV / 1.5f
        && data->distance > TILE_SIZE) {
        sfSprite_destroy(sprite);
        return;
    }
    for (int x = data->sprite_start_x; x < data->sprite_end_x; x++) {
        if (x < 0 || x >= WINDOWX || perp_distance >= frame->z_buffer[x])
            continue;
        sfSprite_setTexture(sprite, enemy.texture, sfTrue);
        draw_enemy_column(sprite, &enemy, data, x);
        sfRenderWindow_drawSprite(frame->window, sprite, NULL);
    }
    sfSprite_destroy(sprite);
}

void draw_enemy(frame_t *frame, int index)
{
    item_render_data_t data = {0};

    calculate_enemy_position(frame, index, &data);
    calculate_enemy_dimensions(&data, frame, index);
    if (data.distance > 1000.0f)
        return;
    render_enemy_columns(frame, index, &data);
    if (ENEMY[index].is_dead)
        return;
    draw_health_bar_3d(frame, index, data.tex_size.y, v2f(0.5f, 0.15f));
}

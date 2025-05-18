/*
** EPITECH PROJECT, 2025
** bswolf3D
** File description:
** drawer
*/

#include "frame.h"

void draw_floor_and_ceiling(frame_t *frame)
{
    sfColor floor_color = sfColor_fromRGB(100, 100, 100);
    sfColor ceiling_color = sfColor_fromRGB(50, 50, 50);
    static sfRectangleShape* floor_rect = NULL;
    static sfRectangleShape* ceiling_rect = NULL;
    int vertical = (int)(WINDOWY * tanf(PLAYER->angle.y) / 2);

    if (!floor_rect)
        floor_rect = sfRectangleShape_create();
    sfRectangleShape_setFillColor(floor_rect, floor_color);
    sfRectangleShape_setPosition(floor_rect, v2f(0, WINDOWY / 2 + vertical));
    sfRectangleShape_setSize(floor_rect, v2f(WINDOWX, WINDOWY / 2 - vertical));
    sfRenderWindow_drawRectangleShape(WINDOW, floor_rect, NULL);
    if (!ceiling_rect)
        ceiling_rect = sfRectangleShape_create();
    sfRectangleShape_setFillColor(ceiling_rect, ceiling_color);
    sfRectangleShape_setPosition(ceiling_rect, v2f(0, 0));
    sfRectangleShape_setSize(ceiling_rect,
        v2f(WINDOWX, WINDOWY / 2 + vertical));
    sfRenderWindow_drawRectangleShape(WINDOW, ceiling_rect, NULL);
}

void render_wall_column(sfRenderWindow *window, int column,
    float wall_height, sfColor color)
{
    sfRectangleShape *wall_rect = sfRectangleShape_create();
    sfVector2f position = {(float)column, (WINDOWY - wall_height) / 2};

    sfRectangleShape_setFillColor(wall_rect, color);
    sfRectangleShape_setPosition(wall_rect, position);
    sfRectangleShape_setSize(wall_rect, (sfVector2f){1, wall_height});
    sfRenderWindow_drawRectangleShape(window, wall_rect, NULL);
    sfRectangleShape_destroy(wall_rect);
}

static int get_base_text_x(bool is_vertical, sfVector2f hits)
{
    int tex_x = 0;

    if (is_vertical)
        tex_x = (int)fmodf(hits.y, TILE_SIZE);
    else
        tex_x = (int)fmodf(hits.x, TILE_SIZE);
    return tex_x;
}

static sfIntRect calculate_wall_texture_rect(wall_render_params_t prms,
    environment_ray_t *env, float *scale_y_out)
{
    int tex_x = 0;
    float scale_y = 0;
    sfVector2u tex_size = sfTexture_getSize(env->texture);
    sfIntRect tex_rect = {0, 0, 1, (int)tex_size.y};

    tex_x = get_base_text_x(prms.is_vertical, prms.hit_position);
    if (env->isrec) {
        tex_x = tex_x * env->rec.width / TILE_SIZE;
        tex_rect = irct(env->rec.left + tex_x,
            env->rec.top, 2, env->rec.height);
        scale_y = prms.column_wall_pos.y / (float)env->rec.height;
    } else {
        tex_x = tex_x * tex_size.x / TILE_SIZE;
        tex_rect = irct(tex_x, 0, 2, (int)tex_size.y);
        scale_y = prms.column_wall_pos.y / (float)tex_size.y;
    }
    *scale_y_out = scale_y;
    return tex_rect;
}

void render_wall_column_textured(frame_t *frame, wall_render_params_t prms)
{
    float scale_y = 0;
    sfSprite *wall_sprite = sfSprite_create();
    int env_index = (int)prms.ray_index;
    environment_ray_t *env = &frame->game->environment[env_index];
    sfIntRect tex_rect = calculate_wall_texture_rect(prms, env, &scale_y);

    sfSprite_setTexture(wall_sprite, env->texture, sfTrue);
    sfSprite_setColor(wall_sprite, prms.light_color);
    sfSprite_setTextureRect(wall_sprite, tex_rect);
    sfSprite_setPosition(wall_sprite, v2f((float)prms.column_wall_pos.x,
        (WINDOWY - prms.column_wall_pos.y) / 2 + prms.vertical_offset));
    sfSprite_setScale(wall_sprite, v2f(1.0f, scale_y));
    sfRenderWindow_drawSprite(WINDOW, wall_sprite, NULL);
    sfSprite_destroy(wall_sprite);
}

/*
** EPITECH PROJECT, 2025
** bswolf3D
** File description:
** drawer
*/

#include "frame.h"

void draw_floor_and_ceiling(sfRenderWindow *window)
{
    sfColor floor_color = sfColor_fromRGB(100, 100, 100);
    sfColor ceiling_color = sfColor_fromRGB(50, 50, 50);
    static sfRectangleShape* floor_rect = NULL;
    static sfRectangleShape* ceiling_rect = NULL;

    if (!floor_rect)
        floor_rect = sfRectangleShape_create();
    sfRectangleShape_setFillColor(floor_rect, floor_color);
    sfRectangleShape_setPosition(floor_rect, (sfVector2f){0, WINDOWY / 2});
    sfRectangleShape_setSize(floor_rect, (sfVector2f){WINDOWX, WINDOWY / 2});
    sfRenderWindow_drawRectangleShape(window, floor_rect, NULL);
    if (!ceiling_rect)
        ceiling_rect = sfRectangleShape_create();
    sfRectangleShape_setFillColor(ceiling_rect, ceiling_color);
    sfRectangleShape_setPosition(ceiling_rect, (sfVector2f){0, 0});
    sfRectangleShape_setSize(ceiling_rect, (sfVector2f){WINDOWX, WINDOWY / 2});
    sfRenderWindow_drawRectangleShape(window, ceiling_rect, NULL);
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

void render_wall_column_textured(frame_t *frame, sfVector2f column_wall_height,
    sfVector2f hits, bool hit_vertical)
{
    int tex_x = 0;
    float scale_y = 0;
    sfSprite *wall_sprite = sfSprite_create();
    sfVector2u tex_size = sfTexture_getSize(frame->game->map->walltexture);
    sfIntRect tex_rect = {0, 0, 1, (int)tex_size.y};

    sfSprite_setTexture(wall_sprite, frame->game->map->walltexture, sfTrue);
    if (hit_vertical)
        tex_x = (int)fmodf(hits.y, TILE_SIZE);
    else
        tex_x = (int)fmodf(hits.x, TILE_SIZE);
    tex_x = tex_x * tex_size.x / TILE_SIZE;
    tex_rect = irct(tex_x, 0, 1, (int)tex_size.y);
    sfSprite_setTextureRect(wall_sprite, tex_rect);
    sfSprite_setPosition(wall_sprite, v2f((float)column_wall_height.x,
        (WINDOWY - column_wall_height.y) / 2));
    scale_y = column_wall_height.y / (float)tex_size.y;
    sfSprite_setScale(wall_sprite, v2f(1.0f, scale_y));
    sfRenderWindow_drawSprite(WINDOW, wall_sprite, NULL);
    sfSprite_destroy(wall_sprite);
}

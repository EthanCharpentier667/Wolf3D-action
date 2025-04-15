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

void render_textured_wall_column(sfRenderWindow *window, int column,
    float wall_height, sfTexture *texture)
{
    sfRectangleShape *wall_rect = sfRectangleShape_create();
    sfVector2f position = {(float)column, (WINDOWY - wall_height) / 2};
    sfVector2u tex_size = sfTexture_getSize(texture);
    int tex_x = column % tex_size.x;
    sfIntRect texture_rect = {tex_x, 0, 1, tex_size.y};

    sfRectangleShape_setTexture(wall_rect, texture, sfTrue);
    sfRectangleShape_setTextureRect(wall_rect, texture_rect);
    sfRectangleShape_setPosition(wall_rect, position);
    sfRectangleShape_setSize(wall_rect, (sfVector2f){1, wall_height});
    sfRenderWindow_drawRectangleShape(window, wall_rect, NULL);
    sfRectangleShape_destroy(wall_rect);
}

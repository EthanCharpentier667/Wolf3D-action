/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** draw_hud
*/

#include "frame.h"

void draw_life(frame_t *frame)
{
    if (PLAYER->life > 0 && PLAYER->life <= QUART_LIFE)
        sfSprite_setTextureRect(HUD->life->sprite, irct(0, 0, 400, 400));
    if (PLAYER->life > QUART_LIFE && PLAYER->life <= MID_LIFE)
        sfSprite_setTextureRect(HUD->life->sprite, irct(400, 0, 400, 400));
    if (PLAYER->life > MID_LIFE && PLAYER->life <= THREE_Q_LIFE)
        sfSprite_setTextureRect(HUD->life->sprite, irct(800, 0, 400, 400));
    if (PLAYER->life > THREE_Q_LIFE && PLAYER->life <= PLAYER->max_life)
        sfSprite_setTextureRect(HUD->life->sprite, irct(1200, 0, 400, 400));
    sfRenderWindow_drawSprite(WINDOW, HUD->life->sprite, NULL);
}

void draw_life_text(frame_t *frame)
{
    char life_text[20];

    snprintf(life_text, sizeof(life_text), "LIFE: %d", PLAYER->life);
    sfText_setString(HUD->life_text->text, life_text);
    sfText_setPosition(HUD->life_text->text,
        v2f(WINDOWX - 200, WINDOWY - 50));
    sfRenderWindow_drawText(WINDOW, HUD->life_text->text, NULL);
}

void draw_minimap(frame_t *frame)
{
    minimap_t *minimap = HUD->minimap;
    float map_p_x = minimap->position.x +
        (PLAYER->pos.x / TILE_SIZE) * minimap->cell_size;
    float map_p_y = minimap->position.y +
        (PLAYER->pos.y / TILE_SIZE) * minimap->cell_size;
    float dir_x = cosf(PLAYER->angle.x);
    float dir_y = sinf(PLAYER->angle.x);
    float radius = minimap->cell_size * 0.8f;

    sfCircleShape_setPosition(minimap->player, v2f(map_p_x -
        minimap->cell_size / 2.5f, map_p_y - minimap->cell_size / 2.5f));
    sfConvexShape_setPoint(minimap->direction, 0, v2f(map_p_x, map_p_y));
    sfConvexShape_setPoint(minimap->direction, 1, v2f(L_VW_X, L_VW_Y));
    sfConvexShape_setPoint(minimap->direction, 2, v2f(R_VW_X, R_VW_Y));
    sfRenderWindow_drawRectangleShape(WINDOW, minimap->background, NULL);
    for (int i = 0; i < minimap->nb_walls; i++)
        sfRenderWindow_drawRectangleShape(WINDOW, minimap->walls[i], NULL);
    sfRenderWindow_drawCircleShape(WINDOW, minimap->player, NULL);
    sfRenderWindow_drawConvexShape(WINDOW, minimap->direction, NULL);
}

void draw_weapon(frame_t *frame)
{
    weapon_t *weapon = HUD->weapon;

    sfRenderWindow_drawSprite(WINDOW, weapon->sprite, NULL);
}

void draw_hud(frame_t *frame)
{
    draw_minimap(frame);
    draw_weapon(frame);
}

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
        sfSprite_setTextureRect(HUD->life->sprite, irct(2400, 0, 800, 600));
    if (PLAYER->life > QUART_LIFE && PLAYER->life <= MID_LIFE)
        sfSprite_setTextureRect(HUD->life->sprite, irct(1600, 0, 800, 600));
    if (PLAYER->life > MID_LIFE && PLAYER->life <= THREE_Q_LIFE)
        sfSprite_setTextureRect(HUD->life->sprite, irct(800, 0, 800, 600));
    if (PLAYER->life > THREE_Q_LIFE && PLAYER->life <= PLAYER->max_life)
        sfSprite_setTextureRect(HUD->life->sprite, irct(0, 0, 800, 600));
    sfRenderWindow_drawSprite(WINDOW, HUD->life->sprite, NULL);
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

void draw_ammo(frame_t *frame, weapon_t *weapon)
{
    sfText *ammo_text = sfText_create();
    sfFont *font = sfFont_createFromFile(RES "contm.ttf");
    char ammo_str[32];

    if (weapon->ammo_capacity > 0) {
        if (ammo_text && font) {
            sprintf(ammo_str, "AMMO: %d/%d",
                weapon->ammo, weapon->ammo_capacity);
            sfText_setFont(ammo_text, font);
            sfText_setCharacterSize(ammo_text, 24);
            sfText_setPosition(ammo_text, (sfVector2f){10, WINDOWY - 40});
            sfText_setString(ammo_text, ammo_str);
            sfText_setColor(ammo_text, sfWhite);
            sfRenderWindow_drawText(WINDOW, ammo_text, NULL);
            sfText_destroy(ammo_text);
            sfFont_destroy(font);
        }
    }
}

void draw_weapon(frame_t *frame)
{
    weapon_t *weapon = CURRENT_WEAPON;

    if (!weapon)
        return;
    sfRenderWindow_drawSprite(WINDOW, weapon->sprite, NULL);
    draw_ammo(frame, weapon);
}

void draw_hud(frame_t *frame)
{
    draw_minimap(frame);
    draw_weapon(frame);
    draw_life(frame);
}

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

void draw_hud(frame_t *frame)
{
    draw_life(frame);
    draw_life_text(frame);
}
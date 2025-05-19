/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** hud
*/

#include "frame.h"

int create_hud(frame_t *frame)
{
    HUD->life = malloc(sizeof(img_t));
    if (!HUD->life)
        return 1;
    HUD->life->sprite = sfSprite_create();
    if (!HUD->life->sprite)
        return 1;
    HUD->life->texture =
        sfTexture_createFromFile(RES "Blood_Overlay.png", NULL);
    if (!HUD->life->texture)
        return 1;
    sfSprite_setTexture(HUD->life->sprite, HUD->life->texture, sfTrue);
    HUD->life->rec = irct(0, 0, 800, 600);
    sfSprite_setTextureRect(HUD->life->sprite, HUD->life->rec);
    return 0;
}

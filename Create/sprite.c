/*
** EPITECH PROJECT, 2024
** graphic
** File description:
** srpite
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include "frame.h"

int create_obj(images_t *images, char *str,
    sfVector2f scale, sfVector2f pos)
{
    IMG = realloc(IMG, (NB + 1) * sizeof(img_t));
    if (!IMG) {
        return 84;
    }
    IMG[NB].texture = sfTexture_createFromFile(str, NULL);
    if (!IMG[NB].texture)
        return 84;
    IMG[NB].sprite = sfSprite_create();
    if (!IMG[NB].sprite)
        return 84;
    IMG[NB].scale.x = scale.x;
    IMG[NB].scale.y = scale.y;
    IMG[NB].pos.x = pos.x;
    IMG[NB].pos.y = pos.y;
    IMG[NB].origin = (sfVector2f) {0, 0};
    IMG[NB].isrec = false;
    NB++;
    return 0;
}

int create_rec_obj(images_t *images, char *path,
    sfFloatRect scale_pos, sfIntRect rec)
{
    IMG = realloc(IMG, (NB + 1) * sizeof(img_t));
    if (!IMG) {
        return 84;
    }
    IMG[NB].texture = sfTexture_createFromFile(path, NULL);
    if (!IMG[NB].texture)
        return 84;
    IMG[NB].sprite = sfSprite_create();
    if (!IMG[NB].sprite)
        return 84;
    IMG[NB].scale.x = scale_pos.left;
    IMG[NB].scale.y = scale_pos.top;
    IMG[NB].pos.x = scale_pos.width;
    IMG[NB].pos.y = scale_pos.height;
    IMG[NB].origin = (sfVector2f) {0.0f, 0.f};
    IMG[NB].rec = rec;
    IMG[NB].isrec = true;
    NB++;
    return 0;
}

void applied(images_t *images)
{
    for (int i = 0; i <= NB - 1; i++) {
        sfSprite_setPosition(IMG[i].sprite, IMG[i].pos);
        sfSprite_setScale(IMG[i].sprite, IMG[i].scale);
        sfSprite_setOrigin(IMG[i].sprite, IMG[i].origin);
        sfSprite_setTexture(IMG[i].sprite, IMG[i].texture, sfTrue);
        if (IMG[i].isrec == true)
            sfSprite_setTextureRect(IMG[i].sprite, IMG[i].rec);
    }
}

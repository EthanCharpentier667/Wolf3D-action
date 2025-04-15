/*
** EPITECH PROJECT, 2024
** DuckHuntTest
** File description:
** window
*/
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdio.h>
#include "fb.h"


sfRenderWindow *create_window(int w, int h, char *name)
{
    sfVideoMode mode = {w, h, 32};
    sfRenderWindow *window =
        sfRenderWindow_create(mode, name, sfClose | sfResize, NULL);

    if (!window)
        return NULL;
    return window;
}

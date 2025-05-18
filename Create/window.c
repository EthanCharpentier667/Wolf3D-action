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
    sfContextSettings settings;
    sfRenderWindow *window = NULL;

    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 2;
    settings.minorVersion = 0;
    settings.attributeFlags = sfContextDefault;
    window = sfRenderWindow_create(mode, name,
        sfClose | sfResize, &settings);
    if (!window) {
        fprintf(stderr, "Failed to create SFML window\n");
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(window, 60);
    return window;
}

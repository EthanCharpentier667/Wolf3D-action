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
    if (!window)
        return NULL;
    sfRenderWindow_setFramerateLimit(window, 60);
    sfRenderWindow_setPosition(window,
        (sfVector2i){(sfVideoMode_getDesktopMode().width - w) / 2,
        (sfVideoMode_getDesktopMode().height - h) / 2});
    return window;
}

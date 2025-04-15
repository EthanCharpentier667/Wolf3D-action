/*
** EPITECH PROJECT, 2024
** DuckHuntTest
** File description:
** create_variables
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <SFML/Window.h>
#include "frame.h"
#include <stdlib.h>

sfVector2i v2i(int x, int y)
{
    sfVector2i vector = (sfVector2i) {x, y};

    return vector;
}

sfVector2f v2f(float x, float y)
{
    sfVector2f vector = (sfVector2f) {x, y};

    return vector;
}

sfVector3f v3f(float x, float y, float z)
{
    sfVector3f vector = (sfVector3f) {x, y, z};

    return vector;
}

sfFloatRect frct(float left, float top, float width, float height)
{
    sfFloatRect vector = (sfFloatRect) {left, top, width, height};

    return vector;
}

sfIntRect irct(int left, int top, int width, int height)
{
    sfIntRect vector = (sfIntRect) {left, top, width, height};

    return vector;
}

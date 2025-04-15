/*
** EPITECH PROJECT, 2024
** DuckHuntTest
** File description:
** framebuffer
*/


#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdio.h>
#include "fb.h"

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height)
{
    framebuffer_t *fb = malloc(sizeof(framebuffer_t));

    if (!fb)
        return NULL;
    fb->height = height;
    fb->width = width;
    return fb;
}

void framebuffer_destroy(framebuffer_t *framebuffer)
{
    free(framebuffer);
}

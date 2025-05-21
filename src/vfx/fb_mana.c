/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** fb_mana
*/

#include "frame.h"

framebuffer_t *framebuffer_alloc(sfVector2u size)
{
    framebuffer_t *fb = malloc(sizeof(framebuffer_t));

    if (!fb)
        return NULL;
    fb->size = size;
    fb->pixels = malloc(size.x * size.y * 4);
    if (!fb->pixels) {
        free(fb);
        return NULL;
    }
    return fb;
}

void framebuffer_destroy(framebuffer_t *buffer)
{
    if (buffer) {
        free(buffer->pixels);
        free(buffer);
    }
}

void my_put_pixel(framebuffer_t *buffer, unsigned int x,
    unsigned int y, sfColor color)
{
    unsigned int index = 0;
    sfVector2u size = buffer->size;

    x %= size.x;
    y %= size.y;
    index = (y * size.x + x) * 4;
    buffer->pixels[index] = color.r;
    buffer->pixels[index + 1] = color.g;
    buffer->pixels[index + 2] = color.b;
    buffer->pixels[index + 3] = color.a;
}

bool framebuffer_create(const char *filepath, framebuffer_t **fb)
{
    sfImage *image = sfImage_createFromFile(filepath);
    framebuffer_t *buffer = NULL;
    sfVector2u size = {0, 0};
    sfColor pixel = {0, 0, 0, 0};

    if (!image)
        return true;
    size = sfImage_getSize(image);
    buffer = framebuffer_alloc(size);
    if (!buffer) {
        return true;
    }
    for (unsigned int y = 0; y < size.y; y++) {
        for (unsigned int x = 0; x < size.x; x++) {
            pixel = sfImage_getPixel(image, x, y);
            my_put_pixel(buffer, x, y, pixel);
        }
    }
    *fb = buffer;
    return false;
}

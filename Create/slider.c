/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** slider
*/

#include "frame.h"

static int create_slider_shape(ui_t *ui, sfVector2f pos, sfVector2f size)
{
    SLIDERS[NB_SLIDERS].bar = sfRectangleShape_create();
    if (!SLIDERS[NB_SLIDERS].bar)
        return 84;
    sfRectangleShape_setPosition(SLIDERS[NB_SLIDERS].bar, pos);
    sfRectangleShape_setSize(SLIDERS[NB_SLIDERS].bar, size);
    sfRectangleShape_setFillColor(SLIDERS[NB_SLIDERS].bar,
        sfColor_fromRGBA(80, 80, 80, 255));
    return 0;
}

static int create_slider_fill(ui_t *ui, sfVector2f pos, sfVector2f size)
{
    SLIDERS[NB_SLIDERS].fill = sfRectangleShape_create();
    if (!SLIDERS[NB_SLIDERS].fill)
        return 84;
    sfRectangleShape_setPosition(SLIDERS[NB_SLIDERS].fill, pos);
    sfRectangleShape_setSize(SLIDERS[NB_SLIDERS].fill, size);
    sfRectangleShape_setFillColor(SLIDERS[NB_SLIDERS].fill,
        sfColor_fromRGBA(180, 180, 180, 255));
    return 0;
}

static int create_slider_handle(ui_t *ui, sfVector2f pos, sfVector2f size)
{
    SLIDERS[NB_SLIDERS].handle = sfCircleShape_create();
    if (!SLIDERS[NB_SLIDERS].handle)
        return 84;
    sfCircleShape_setRadius(SLIDERS[NB_SLIDERS].handle, size.y / 1.5);
    sfCircleShape_setPosition(SLIDERS[NB_SLIDERS].handle, pos);
    sfCircleShape_setFillColor(SLIDERS[NB_SLIDERS].handle,
        sfColor_fromRGBA(220, 220, 220, 255));
    return 0;
}

static void apply_slider(ui_t *ui, sfVector2f pos,
    sfVector2f size, float initial_value)
{
    float fill_width = size.x * initial_value;
    float handle_radius = size.y / 1.5;

    sfRectangleShape_setSize(SLIDERS[NB_SLIDERS].fill,
        v2f(fill_width, size.y));
    sfCircleShape_setPosition(SLIDERS[NB_SLIDERS].handle,
        v2f(pos.x + fill_width - handle_radius,
        pos.y + size.y / 2 - handle_radius));
}

int create_slider(ui_t *ui, sfVector2f pos,
    sfVector2f size, float initial_value)
{
    if (ui->nb_sliders > 0)
        SLIDERS = realloc(SLIDERS, (ui->nb_sliders + 1) * sizeof(slider_t));
    else
        SLIDERS = malloc(sizeof(slider_t));
    if (!SLIDERS)
        return 84;
    if (create_slider_shape(ui, pos, size) ||
        create_slider_fill(ui, pos, size) ||
        create_slider_handle(ui, pos, size)) {
        return 84;
    }
    SLIDERS[NB_SLIDERS].pos = pos;
    SLIDERS[NB_SLIDERS].size = size;
    SLIDERS[NB_SLIDERS].min_value = 0.0f;
    SLIDERS[NB_SLIDERS].max_value = 1.0f;
    SLIDERS[NB_SLIDERS].current_value = initial_value;
    SLIDERS[NB_SLIDERS].dragging = false;
    apply_slider(ui, pos, size, initial_value);
    NB_SLIDERS++;
    return 0;
}

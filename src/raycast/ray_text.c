/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** 3d_text
*/

#include "frame.h"

static sfRenderTexture *create_text_render_texture(sfText *sftext, int margin, sfRectangleShape **background)
{
    sfFloatRect bounds = sfText_getLocalBounds(sftext);
    sfVector2u size = {(unsigned int)(bounds.width + margin * 2),
        (unsigned int)(bounds.height + margin * 2)};
    sfRenderTexture *render_tex = sfRenderTexture_create(size.x,
        size.y, sfFalse);

    if (!render_tex)
        return NULL;
    *background = sfRectangleShape_create();
    sfRectangleShape_setSize(*background, (sfVector2f){size.x, size.y});
    sfRectangleShape_setFillColor(*background, sfColor_fromRGBA(0, 0, 0, 180));
    sfRectangleShape_setOutlineThickness(*background, 2.0f);
    sfRectangleShape_setOutlineColor(*background, sfWhite);
    return render_tex;
}

static sfText *setup_text(sfFont *font, char *text)
{
    sfText *sftext = sfText_create();

    if (!font || !sftext)
        return NULL;
    sfText_setString(sftext, text);
    sfText_setFont(sftext, font);
    sfText_setCharacterSize(sftext, 24);
    sfText_setColor(sftext, sfWhite);
    return sftext;
}

static const sfTexture *render_text_to_texture(sfRenderTexture *render_tex,
    sfText *sftext, sfRectangleShape *background, int margin)
{
    sfFloatRect bounds = sfText_getLocalBounds(sftext);
    float text_x = margin - bounds.left;
    float text_y = margin - bounds.top;

    sfRenderTexture_clear(render_tex, sfTransparent);
    sfRenderTexture_drawRectangleShape(render_tex, background, NULL);
    sfText_setPosition(sftext, (sfVector2f){text_x, text_y});
    sfRenderTexture_drawText(render_tex, sftext, NULL);
    sfRenderTexture_display(render_tex);
    return sfRenderTexture_getTexture(render_tex);
}

static void cleanup_resources(sfRectangleShape *background,
    sfRenderTexture *render_tex, sfText *sftext, sfFont *font)
{
    sfRectangleShape_destroy(background);
    sfRenderTexture_destroy(render_tex);
    sfText_destroy(sftext);
    sfFont_destroy(font);
}

void draw_3d_text(frame_t *frame, sfVector3f pos, char *text, sfVector2f scale)
{
    sfFont *font = sfFont_createFromFile(FONTPATH);
    sfText *sftext = setup_text(font, text);
    item_render_data_t data = {0};
    const sfTexture *text_texture = NULL;
    sfRenderTexture *render_tex = NULL;
    sfRectangleShape *background = NULL;

    if (!sftext)
        return;
    render_tex = create_text_render_texture(sftext, 10, &background);
    if (!render_tex) {
        sfText_destroy(sftext);
        sfFont_destroy(font);
        return;
    }
    text_texture = render_text_to_texture(render_tex, sftext, background, 10);
    calculate_item_position(frame, pos, (sfTexture *) text_texture, &data);
    calculate_item_dimensions(&data, scale, PLAYER, pos);
    render_item_columns(frame, (sfTexture *) text_texture, &data, scale);
    cleanup_resources(background, render_tex, sftext, font);
}

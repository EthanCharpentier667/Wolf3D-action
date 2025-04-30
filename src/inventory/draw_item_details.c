/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** draw_item_details
*/

#include "frame.h"

static void draw_item_panel_background(frame_t *frame, sfVector2f pos,
    sfVector2f size)
{
    sfRectangleShape *panel = sfRectangleShape_create();

    sfRectangleShape_setSize(panel, size);
    sfRectangleShape_setPosition(panel, pos);
    sfRectangleShape_setFillColor(panel,
        sfColor_fromRGBA(30, 30, 30, 230));
    sfRectangleShape_setOutlineColor(panel, sfWhite);
    sfRectangleShape_setOutlineThickness(panel, 2.0f);
    sfRenderWindow_drawRectangleShape(WINDOW, panel, NULL);
    sfRectangleShape_destroy(panel);
}

static void draw_item_title(frame_t *frame, item_t *item,
    sfVector2f pos, float panel_width)
{
    sfText *title = sfText_create();
    sfFloatRect titleBounds;

    sfText_setFont(title, INVENTORY->font);
    sfText_setString(title, item->name);
    sfText_setCharacterSize(title, 24);
    sfText_setColor(title, sfWhite);
    titleBounds = sfText_getLocalBounds(title);
    sfText_setPosition(title, v2f(
        pos.x + (panel_width - titleBounds.width) / 2,
        pos.y + 20
    ));
    sfRenderWindow_drawText(WINDOW, title, NULL);
    sfText_destroy(title);
}

static void draw_item_image(frame_t *frame, item_t *item,
    sfVector2f pos, float panel_width)
{
    sfSprite *sprite = sfSprite_create();
    sfFloatRect bounds;
    float scale_x = 0;
    float scale_y = 0;
    float scale = 0;

    sfSprite_setTexture(sprite, item->texture, sfTrue);
    bounds = sfSprite_getLocalBounds(sprite);
    scale_x = (panel_width * 0.6f) / bounds.width;
    scale_y = (panel_width * 0.6f) / bounds.height;
    scale = (scale_x < scale_y) ? scale_x : scale_y;
    sfSprite_setScale(sprite, v2f(scale, scale));
    sfSprite_setOrigin(sprite, v2f(bounds.width / 2, bounds.height / 2));
    sfSprite_setPosition(sprite, v2f(
        pos.x + panel_width / 2,
        pos.y + 120));
    sfRenderWindow_drawSprite(WINDOW, sprite, NULL);
    sfSprite_destroy(sprite);
}

static void draw_item_description(frame_t *frame, sfVector2f pos,
    float panel_width, item_t *item)
{
    sfText *description = sfText_create();

    sfText_setFont(description, INVENTORY->font);
    sfText_setString(description, !item->description
        ? "No description available" : item->description);
    sfText_setCharacterSize(description, 16);
    sfText_setColor(description, sfWhite);
    wrap_text(description, panel_width - 30);
    sfText_setPosition(description, v2f(
        pos.x + 15,
        pos.y + 200));
    sfRenderWindow_drawText(WINDOW, description, NULL);
    sfText_destroy(description);
}

static void setup_button_shape(frame_t *frame, sfRectangleShape *button,
    sfVector2f pos, sfColor color)
{
    sfVector2f button_size = v2f(120, 40);

    sfRectangleShape_setSize(button, button_size);
    sfRectangleShape_setPosition(button, pos);
    sfRectangleShape_setFillColor(button, color);
    sfRectangleShape_setOutlineColor(button, sfWhite);
    sfRectangleShape_setOutlineThickness(button, 1.0f);
    sfRenderWindow_drawRectangleShape(WINDOW, button, NULL);
}

static void draw_drop_button(frame_t *frame,
    sfVector2f pos, float panel_height)
{
    sfRectangleShape *drop_button = sfRectangleShape_create();
    sfText *drop_text = sfText_create();
    sfFloatRect dropTextBounds;
    sfColor button_color = sfColor_fromRGBA(180, 30, 30, 200);

    setup_button_shape(frame, drop_button,
        v2f(pos.x + 20, pos.y + panel_height - 60), button_color);
    sfText_setFont(drop_text, INVENTORY->font);
    sfText_setString(drop_text, "Drop");
    sfText_setCharacterSize(drop_text, 18);
    sfText_setColor(drop_text, sfWhite);
    dropTextBounds = sfText_getLocalBounds(drop_text);
    sfText_setPosition(drop_text, v2f(
        pos.x + 20 + (120 - dropTextBounds.width) / 2,
        pos.y + panel_height - 60 + (40 - dropTextBounds.height) / 2 - 5));
    sfRenderWindow_drawText(WINDOW, drop_text, NULL);
    sfText_destroy(drop_text);
    sfRectangleShape_destroy(drop_button);
}

static void draw_use_button(frame_t *frame, sfVector2f pos, sfVector2f panel)
{
    sfRectangleShape *use_button = sfRectangleShape_create();
    sfText *use_text = sfText_create();
    sfFloatRect useTextBounds;

    setup_button_shape(frame, use_button,
        v2f(pos.x + panel.x - 140, pos.y + panel.y - 60),
        sfColor_fromRGBA(30, 120, 30, 200));
    sfText_setFont(use_text, INVENTORY->font);
    sfText_setString(use_text, "Use");
    sfText_setCharacterSize(use_text, 18);
    sfText_setColor(use_text, sfWhite);
    useTextBounds = sfText_getLocalBounds(use_text);
    sfText_setPosition(use_text, v2f(
        pos.x + panel.x - 140 + (120 - useTextBounds.width) / 2,
        pos.x + panel.y - 60 + (40 - useTextBounds.height) / 2 - 5
    ));
    sfRenderWindow_drawText(WINDOW, use_text, NULL);
    sfText_destroy(use_text);
    sfRectangleShape_destroy(use_button);
}

void draw_item_details(frame_t *frame, float pos_x, float pos_y)
{
    int selected = INVENTORY->selected_item;
    item_t *item = &INVENTORY->items[selected];
    float panel_width = 300.0f;
    float panel_height = 400.0f;

    draw_item_panel_background(frame, v2f(pos_x, pos_y),
        v2f(panel_width, panel_height));
    draw_item_title(frame, item, v2f(pos_x, pos_y), panel_width);
    draw_item_image(frame, item, v2f(pos_x, pos_y), panel_width);
    draw_item_description(frame, v2f(pos_x, pos_y), panel_width, item);
    draw_drop_button(frame, v2f(pos_x, pos_y), panel_height);
    if (item->useable)
        draw_use_button(frame, v2f(pos_x, pos_y),
            v2f(panel_width, panel_height));
}

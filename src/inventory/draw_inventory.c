/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** draw_inventory
*/

#include "frame.h"

static void setup_inventory_grid(frame_t *frame,
    sfRectangleShape *cell, int i, sfVector2f pos)
{
    sfRectangleShape_setSize(cell,
        v2f(INVENTORY->cell_size, INVENTORY->cell_size));
    sfRectangleShape_setPosition(cell, pos);
    sfRectangleShape_setFillColor(cell, sfColor_fromRGBA(50, 50, 50, 150));
    sfRectangleShape_setOutlineColor(cell, sfColor_fromRGB(100, 100, 100));
    sfRectangleShape_setOutlineThickness(cell, 1);
    sfRenderWindow_drawRectangleShape(WINDOW, cell, NULL);
    if (i < INVENTORY->nb_items) {
        INVENTORY->item_buttons[i].pos = pos;
        INVENTORY->item_buttons[i].scale =
            v2f(INVENTORY->cell_size, INVENTORY->cell_size);
        sfSprite_setPosition(INVENTORY->item_buttons[i].sprite, pos);
        sfSprite_setScale(INVENTORY->item_buttons[i].sprite,
            v2f(INVENTORY->cell_size / 100.0f, INVENTORY->cell_size / 100.0f));
    }
}

static void draw_inventory_grid(frame_t *frame)
{
    sfRectangleShape *cell = sfRectangleShape_create();
    sfVector2f pos;
    int row = 0;
    int col = 0;

    for (int i = 0; i < pow(INVENTORY->grid_size, 2); i++) {
        row = i / INVENTORY->grid_size;
        col = i % INVENTORY->grid_size;
        pos.x = INVENTORY->pos_x + INVENTORY->padding +
            col * (INVENTORY->cell_size + INVENTORY->gap);
        pos.y = INVENTORY->pos_y + INVENTORY->padding +
            row * (INVENTORY->cell_size + INVENTORY->gap);
        setup_inventory_grid(frame, cell, i, pos);
    }
    sfRectangleShape_destroy(cell);
}

static void draw_inventory_title(frame_t *frame, sfFont *font)
{
    sfText *title = sfText_create();
    sfFloatRect titleBounds;

    sfText_setFont(title, font);
    sfText_setString(title, "Inventory");
    sfText_setCharacterSize(title, 24);
    sfText_setColor(title, sfWhite);
    titleBounds = sfText_getLocalBounds(title);
    sfText_setPosition(title, (sfVector2f){
        INVENTORY->pos_x + (INVENTORY->inv_width - titleBounds.width) / 2,
        INVENTORY->pos_y - titleBounds.height - 10
    });
    sfRenderWindow_drawText(WINDOW, title, NULL);
}

static void draw_item_highlight(frame_t *frame, sfVector2f pos)
{
    sfRectangleShape *highlight = sfRectangleShape_create();

    sfRectangleShape_setSize(highlight, v2f(INVENTORY->cell_size,
        INVENTORY->cell_size));
    sfRectangleShape_setPosition(highlight, pos);
    sfRectangleShape_setFillColor(highlight,
        sfColor_fromRGBA(255, 255, 255, 50));
    sfRectangleShape_setOutlineColor(highlight,
        sfColor_fromRGB(200, 200, 200));
    sfRectangleShape_setOutlineThickness(highlight, 2);
    sfRenderWindow_drawRectangleShape(WINDOW, highlight, NULL);
    sfRectangleShape_destroy(highlight);
}

static void draw_item_counter(frame_t *frame, int item_index,
    sfVector2f pos, sfText *count_text)
{
    char count_str[10];
    sfFloatRect textBounds;

    sprintf(count_str, "%d", INVENTORY->item_coun[item_index]);
    textBounds = sfText_getLocalBounds(count_text);
    sfText_setString(count_text, count_str);
    sfText_setPosition(count_text, (sfVector2f){
        pos.x + INVENTORY->cell_size - textBounds.width - 5,
        pos.y + INVENTORY->cell_size - textBounds.height - 5
    });
    sfRenderWindow_drawText(WINDOW, count_text, NULL);
}

static void draw_item_name(frame_t *frame, int i,
    sfVector2f pos, sfFont *font)
{
    sfText *item_name = sfText_create();
    sfFloatRect nameBounds;

    sfText_setFont(item_name, font);
    sfText_setString(item_name, INVENTORY->items[i].name);
    sfText_setCharacterSize(item_name, 12);
    sfText_setColor(item_name, sfWhite);
    nameBounds = sfText_getLocalBounds(item_name);
    sfText_setPosition(item_name, (sfVector2f){
        pos.x + (INVENTORY->cell_size - nameBounds.width) / 2,
        pos.y + INVENTORY->cell_size - nameBounds.height - 5
    });
    sfRenderWindow_drawText(WINDOW, item_name, NULL);
    sfText_destroy(item_name);
}

static void draw_item_sprite(frame_t *frame, int i, sfVector2f pos)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f scale = {0.5f, 0.5f};
    sfFloatRect bounds;

    sfSprite_setTexture(sprite, INVENTORY->items[i].texture, sfTrue);
    bounds = sfSprite_getLocalBounds(sprite);
    scale.x = (INVENTORY->cell_size * 0.7f) / bounds.width;
    scale.y = (INVENTORY->cell_size * 0.7f) / bounds.height;
    sfSprite_setScale(sprite, scale);
    sfSprite_setOrigin(sprite, v2f(bounds.width / 2, bounds.height / 2));
    sfSprite_setPosition(sprite, v2f(pos.x + INVENTORY->cell_size / 2,
        pos.y + INVENTORY->cell_size / 2));
    sfRenderWindow_drawSprite(WINDOW, sprite, NULL);
}

static void draw_single_item(frame_t *frame, int i,
    sfVector2f pos, sfFont *font)
{
    draw_item_sprite(frame, i, pos);
    if (INVENTORY->item_buttons[i].hover)
        draw_item_highlight(frame, pos);
    if (INVENTORY->items[i].name)
        draw_item_name(frame, i, pos, font);
}

static void draw_inventory_items(frame_t *frame, sfFont *font)
{
    sfText *count_text = sfText_create();
    sfVector2f pos;
    int row = 0;
    int col = 0;
    float callandgap = INVENTORY->cell_size + INVENTORY->gap;

    sfText_setFont(count_text, font);
    sfText_setCharacterSize(count_text, 16);
    sfText_setColor(count_text, sfWhite);
    for (int i = 0; i < INVENTORY->nb_items; i++) {
        row = i / INVENTORY->grid_size;
        col = i % INVENTORY->grid_size;
        pos = v2f(INVENTORY->pos_x + INVENTORY->padding + col * callandgap,
            INVENTORY->pos_y + INVENTORY->padding + row * callandgap);
        draw_single_item(frame, i, pos, font);
        if (INVENTORY->item_coun[i] > 1)
            draw_item_counter(frame, i, pos, count_text);
    }
    sfText_destroy(count_text);
}

void draw_inventory(frame_t *frame)
{
    if (!INVENTORY->is_open)
        return;
    draw_inventory_background(frame);
    draw_inventory_grid(frame);
    draw_inventory_title(frame, INVENTORY->font);
    draw_inventory_items(frame, INVENTORY->font);
    if (INVENTORY->selected_item >= 0 &&
        INVENTORY->selected_item < INVENTORY->nb_items)
    draw_item_details(frame, INVENTORY->pos_x +
        INVENTORY->inv_width + 20, INVENTORY->pos_y);
}

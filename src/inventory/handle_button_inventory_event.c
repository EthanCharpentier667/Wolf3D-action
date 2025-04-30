/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** handle_button_inventory_event
*/

#include "frame.h"

static void reset_item_hover_states(frame_t *frame)
{
    for (int i = 0; i < INVENTORY->nb_items; i++)
        INVENTORY->item_buttons[i].hover = false;
}

static sfVector2f get_cell_position(frame_t *frame, int index)
{
    int row = index / INVENTORY->grid_size;
    int col = index % INVENTORY->grid_size;
    float cell_x = INVENTORY->pos_x + INVENTORY->padding +
        col * (INVENTORY->cell_size + INVENTORY->gap);
    float cell_y = INVENTORY->pos_y + INVENTORY->padding +
        row * (INVENTORY->cell_size + INVENTORY->gap);

    return v2f(cell_x, cell_y);
}

static bool is_point_in_rect(sfVector2f point, sfVector2f pos, sfVector2f size)
{
    return (point.x >= pos.x && point.x <= pos.x + size.x &&
        point.y >= pos.y && point.y <= pos.y + size.y);
}

static void check_item_grid_interaction(frame_t *frame, sfEvent *event)
{
    sfVector2f mouse = {frame->mouse.x, frame->mouse.y};
    sfVector2f cell_pos;
    sfVector2f cell_size;

    for (int i = 0; i < INVENTORY->nb_items; i++) {
        cell_pos = get_cell_position(frame, i);
        cell_size = v2f(INVENTORY->cell_size, INVENTORY->cell_size);
        if (!is_point_in_rect(mouse, cell_pos, cell_size))
            continue;
        INVENTORY->item_buttons[i].hover = true;
        if (event->type == sfEvtMouseButtonPressed &&
            event->mouseButton.button == sfMouseLeft) {
            INVENTORY->selected_item = i;
        }
    }
}

static void handle_drop_button(frame_t *frame, sfEvent *event,
    sfVector2f details_pos, sfVector2f panel_size)
{
    sfVector2f button_pos = {
        details_pos.x + 20,
        details_pos.y + panel_size.y - 60
    };
    sfVector2f button_size = {120, 40};

    if (event->type != sfEvtMouseButtonPressed ||
        event->mouseButton.button != sfMouseLeft)
        return;
    if (is_point_in_rect(frame->mouse, button_pos, button_size)) {
        drop_item(frame, INVENTORY->selected_item);
        INVENTORY->selected_item = -1;
    }
}

static void handle_use_button(frame_t *frame, sfEvent *event,
    sfVector2f details_pos, sfVector2f panel_size)
{
    int selected = INVENTORY->selected_item;
    sfVector2f mouse = {frame->mouse.x, frame->mouse.y};
    sfVector2f button_pos = {
        details_pos.x + panel_size.x - 140,
        details_pos.y + panel_size.y - 60
    };
    sfVector2f button_size = {120, 40};

    if (!INVENTORY->items[selected].useable ||
        event->type != sfEvtMouseButtonPressed ||
        event->mouseButton.button != sfMouseLeft)
        return;
    if (is_point_in_rect(mouse, button_pos, button_size))
        use_item(frame, selected);
}

static void check_detail_panel_buttons(frame_t *frame, sfEvent *event)
{
    int selected = INVENTORY->selected_item;
    sfVector2f details_pos = {
        INVENTORY->pos_x + INVENTORY->inv_width + 20,
        INVENTORY->pos_y
    };
    sfVector2f panel_size = {300.0f, 400.0f};

    if (selected < 0 || selected >= INVENTORY->nb_items)
        return;
    handle_drop_button(frame, event, details_pos, panel_size);
    handle_use_button(frame, event, details_pos, panel_size);
}

void handle_button_inventory_event(frame_t *frame, sfEvent *event)
{
    if (!INVENTORY->is_open)
        return;
    reset_item_hover_states(frame);
    check_item_grid_interaction(frame, event);
    check_detail_panel_buttons(frame, event);
}

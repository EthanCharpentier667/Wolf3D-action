/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** inventory_events
*/

#include "frame.h"

static void toggle_inventory(frame_t *frame, sfEvent *event)
{
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyI) {
        PLAYER->inventory->is_open = !PLAYER->inventory->is_open;
    }
}

static void pickup_item_event(frame_t *frame, sfEvent *event)
{
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyE) {
        for (int i = 0; i < frame->game->nb_items; i++) {
            pick_item(frame, &frame->game->items[i]);
        }
    }
}

void handle_inventory_event(frame_t *frame, sfEvent *event)
{
    toggle_inventory(frame, event);
    pickup_item_event(frame, event);
    handle_button_inventory_event(frame, event);
}

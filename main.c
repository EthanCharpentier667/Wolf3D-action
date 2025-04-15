/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** main
*/

#include "frame.h"

int main(int argc, char **argv)
{
    frame_t *frame = malloc(sizeof(frame_t));

    if (!frame)
        return 84;
    if (init_frame(frame) == 84) {
        fprintf(stderr, "Error: Could not initialize frame\n");
        free(frame);
        return 84;
    }
    while (sfRenderWindow_isOpen(WINDOW)) {
        handle_event(&(frame->event), frame);
        sfRenderWindow_clear(WINDOW, sfBlack);
        scene_manager(frame);
        update_player(PLAYER, &frame->clock[0]);
        draw_floor_and_ceiling(WINDOW);
        cast_all_rays(frame);
        sfRenderWindow_display(WINDOW);
    }
    return 0;
}

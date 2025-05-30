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
    srand(time(NULL));
    if (!init_frame(frame)) {
        fprintf(stderr, "Error: Could not initialize frame\n");
        free(frame);
        return 84;
    }
    sfRenderWindow_requestFocus(WINDOW);
    while (sfRenderWindow_isOpen(WINDOW)) {
        handle_event(&(frame->event), frame);
        sfRenderWindow_clear(WINDOW, sfBlack);
        scene_manager(frame);
        sfRenderWindow_display(WINDOW);
    }
    if (frame->played)
        do_save(frame);
    return 0;
}

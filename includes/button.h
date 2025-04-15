/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** button
*/

#include "frame.h"

#ifndef BUTTON_H_
    #define BUTTON_H_

typedef struct frame_s frame_t;

    #define HSAVE "Save the map in the file you loaded"
    #define HADDSIZE "ADD a size to the map"
    #define HSUBSIZE "Substract a size x and y to the map width and heigth"
    #define HAPPLYSIZE "Apply the new size to the map"
    #define HUP "When right click on tile/line/vertex, it is moved up"
    #define HDOWN "When right click on tile/line/vertex, it is moved down"
    #define HRESET "Reset all modifications to get a flat map"

enum buttons_actions {
    PLAY
};

struct button_infos_s {
    int action;
    sfFloatRect infos;
    char *path;
    char *help;
    int (*func)(frame_t *frame);
    int scene;
};

int do_play(frame_t *frame);

extern const struct button_infos_s BUTTON_INFOS[];

#endif /* !BUTTON_H_ */

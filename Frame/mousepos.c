/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** mousepos
*/

#include "frame.h"

sfVector2f get_mouseposition(sfRenderWindow *window)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f mouse =
        sfRenderWindow_mapPixelToCoords(window, mouse_pos, view);

    return mouse;
}

/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** play
*/

#include "frame.h"

int do_play(frame_t *frame)
{
    linked_list_t *elem = NULL;
    vfx_t *vfx = NULL;

    frame->ui->scene = GAME;
    frame->game->level = 1;
    sfRenderWindow_setMouseCursorVisible(WINDOW, sfFalse);
    sfMouse_setPositionRenderWindow(v2i(WINDOWX / 2, WINDOWY / 2), WINDOW);
    elem = create_vfx(UI->vfx_infos.vfxs, UI->vfx_infos.sparkle,
        create_obj_info(frct(0, 0, 1, 1), 0.0,
            sfWhite, 0.0), create_obj_info(frct(250, 250, 0.001, 0.001), 10000.0,
            sfBlack, 30.0));
    vfx = elem->data;
    vfx->origin_pos = v3f(500, 500, 0);
/* create_vfx(UI->vfx_infos.vfxs, UI->vfx_infos.sparkle,
    create_obj_info(frct(0, WINDOWY, 0.05, 0.05), 0.0,
        sfWhite, 0.0), create_obj_info(frct(WINDOWX, WINDOWY / 2.0, 0.001, 0.001), 10000.0,
        sfTransparent, 10)); */
    return 0;
}

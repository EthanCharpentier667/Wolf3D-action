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
    emit_settings_t emit_s = {0};

    frame->ui->scene = GAME;
    frame->game->level = 1;
    sfRenderWindow_setMouseCursorVisible(WINDOW, sfFalse);
    sfMouse_setPositionRenderWindow(v2i(WINDOWX / 2, WINDOWY / 2), WINDOW);
/*     elem = create_vfx(UI->vfx_infos.vfxs, UI->vfx_infos.sparkle,
        create_obj_info(frct(0, 0, 1, 1), 0.0,
            sfWhite, 0.0), create_obj_info(frct(250, 250, 0.001, 0.001), 10000.0,
            sfBlack, 30.0));
    vfx = elem->data;
    vfx->origin_pos = v3f(100, 100, 0); */

    emit_s = create_emit_settings(45.0, 0.1, 360.0, sfColor_fromRGBA(210, 210, 210, 130));
    absorb_splatter(UI->vfx_infos.vfxs, UI->vfx_infos.smoke, &emit_s, v3f(150.0, 150.0, 0));
    emit_s = create_emit_settings(30.0, 0.2, 360.0, sfColor_fromRGBA(190, 190, 190, 180));
    absorb_slow(UI->vfx_infos.vfxs, UI->vfx_infos.smoke, &emit_s, v3f(200.0, 100.0, 0));
    return 0;
}

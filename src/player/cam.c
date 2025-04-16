/*
** EPITECH PROJECT, 2025
** bswolf3D
** File description:
** player
*/

#include "frame.h"

static void lerp_cam_angle(player_t *player)
{
    player->angle = lerp(player->angle, player->fut_angle, MOUSE_SLIDE);
}

static void set_future_angle(player_t *player,
    frame_t *frame, sfVector2i center)
{
    int cam_angle = 0;
    float arrow_addon = 0;
    float mouse_addon = 0;
    sfVector2f mouse_pos = frame->mouse;

    cam_angle = sfKeyboard_isKeyPressed(sfKeyRight) -
        sfKeyboard_isKeyPressed(sfKeyLeft);
    arrow_addon = cam_angle * player->turn_speed * player->delta_time;
    mouse_addon = ((float)mouse_pos.x - center.x)
        * player->turn_speed * MOUSE_SENSITIVITY;
    player->fut_angle = player->fut_angle + arrow_addon + mouse_addon;
}

void rotate_player(player_t *player, frame_t *frame)
{
    sfVector2i center = {WINDOWX / 2, WINDOWY / 2};

    set_future_angle(player, frame, center);
    lerp_cam_angle(player);
    sfMouse_setPositionRenderWindow(center, frame->window);
}

/*
** EPITECH PROJECT, 2025
** bswolf3D
** File description:
** player
*/

#include "frame.h"

static void set_future_angle(player_t *player,
    frame_t *frame)
{
    sfVector2i cam_angle = {0, 0};
    sfVector2f arrow_addon = {0, 0};
    sfVector2f mouse_addon = {0, 0};
    sfVector2i mouse_pos = frame->real_mouse;

    cam_angle.x = sfKeyboard_isKeyPressed(sfKeyRight) -
        sfKeyboard_isKeyPressed(sfKeyLeft);
    cam_angle.y = sfKeyboard_isKeyPressed(sfKeyUp) -
        sfKeyboard_isKeyPressed(sfKeyDown);
    arrow_addon.x = cam_angle.x * player->turn_speed * player->delta_time;
    arrow_addon.y = cam_angle.y * player->turn_speed * player->delta_time;
    mouse_addon.x = (mouse_pos.x - (float)frame->center.x)
        * player->turn_speed * MOUSE_SENSITIVITY;
    mouse_addon.y = (mouse_pos.y - (float)frame->center.y)
        * player->turn_speed * MOUSE_SENSITIVITY * -1;
    player->angle.x = player->angle.x + arrow_addon.x + mouse_addon.x;
    player->angle.y = clamp(player->angle.y + arrow_addon.y +
        mouse_addon.y, MAX_CAM_Y / -2, MAX_CAM_Y / 2);
}

void rotate_player(player_t *player, frame_t *frame)
{
    sfRenderWindow_setMouseCursorVisible(WINDOW, false);
    set_future_angle(player, frame);
    player->delta_time = get_delta_time(frame->clock);
    sfMouse_setPosition(frame->center, NULL);
}

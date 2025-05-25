/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** timer
*/

#include "frame.h"

static void set_timer_text(sfText *text, int timer)
{
    char buffer[16];

    snprintf(buffer, sizeof(buffer), "%02d:%02d", timer / 60, timer % 60);
    sfText_setString(text, buffer);
    sfText_setCharacterSize(text, 30);
    sfText_setPosition(text, v2f(10, 10));
}

void update_timer(frame_t *frame)
{
    static float last_check = 0.0f;
    float current_time = sfTime_asSeconds(frame->clock[5].time);

    if (!PLAYER->inventory->is_open && UI->pause)
        return;
    frame->clock[5].time = sfClock_getElapsedTime(frame->clock[5].clock);
    if (current_time - last_check >= 1.0f) {
        frame->game->timer -= 1;
        last_check = current_time;
    }
    if (frame->game->timer < 0) {
        frame->game->timer = 0;
        frame->game_over = true;
    }
    set_timer_text(frame->ui->texts[10].text, frame->game->timer);
}

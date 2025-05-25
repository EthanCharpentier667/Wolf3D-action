/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** victory
*/

#include "frame.h"

static void display_score(frame_t *frame, int score, sfText *text)
{
    char score_text[50];

    snprintf(score_text, sizeof(score_text), "Your score: %d", score);
    sfText_setString(text, score_text);
    sfRenderWindow_drawText(frame->window, text, NULL);
}

int get_storable_item_count(frame_t *frame)
{
    int count = 0;

    for (int i = 0; i < NBITEMS; i++) {
        if (ITEM[i].pickable || ITEM[i].useable) {
            count++;
        }
    }
    return count;
}

static int update_score(frame_t *frame)
{
    int score = 10000 / (frame->game->difficulty);

    score -= frame->game->nb_enemies_alive * 100;
    score -= frame->game->timer / 100;
    score += frame->game->player->life;
    score -= get_storable_item_count(frame) * 100;
    return score;
}

int victory(frame_t *frame)
{
    int score = update_score(frame);

    PLAYER->pause = true;
    sfRenderWindow_setMouseCursorVisible(frame->window, sfTrue);
    display_score(frame, score, frame->ui->texts[11].text);
    return 0;
}

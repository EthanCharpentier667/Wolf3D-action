/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** buttons_events
*/

#include "frame.h"

static void buttons_effect_click_event(button_t *button)
{
    if (button->type == 1 && button->clicked == true)
        sfSprite_setTexture(button->sprite, button->texture[2], sfTrue);
    if (button->type == 0 && button->clicked == true)
        sfSprite_setColor(button->sprite, button->colors[2]);
}

static void buttons_effect_disable(button_t *button)
{
    if (button->type == 1)
        sfSprite_setTexture(button->sprite, button->texture[3], sfTrue);
    if (button->type == 0)
        sfSprite_setColor(button->sprite, button->colors[3]);
}

static void buttons_effect_hover_event(button_t *button)
{
    if (button->hover == true && button->type == 1)
        sfSprite_setTexture(button->sprite, button->texture[1], sfTrue);
    if (button->hover == true && button->type == 0)
        sfSprite_setColor(button->sprite, button->colors[1]);
    if (button->hover == false && button->type == 0)
        sfSprite_setColor(button->sprite, button->colors[0]);
    if (button->hover == false && button->type == 1)
        sfSprite_setTexture(button->sprite, button->texture[0], sfTrue);
}

static int click_action(frame_t *frame, button_t *button)
{
    for (int i = 0; i < frame->ui->nb_buttons; i++) {
        if (button->action == BUTTON_INFOS[i].action)
            return BUTTON_INFOS[i].func(frame);
        if (button->action == SAVES_LIST)
            return load_save_callback(frame, i);
    }
    return 0;
}

static int button_click_event(sfEvent *event, frame_t *frame, button_t *button)
{
    if (event->type == sfEvtMouseButtonPressed
        && event->mouseButton.button == sfMouseLeft) {
        CLOCK[0].time = sfClock_getElapsedTime(CLOCK[0].clock);
        if (sfTime_asMilliseconds(CLOCK[0].time) < 200.0f)
            return 0;
        sfClock_restart(CLOCK[0].clock);
        button->hover = false;
        button->clicked = true;
        sfSound_play(frame->ui->sounds[1].sound);
        return click_action(frame, button);
    }
    return 0;
}

static void play_hoversound(frame_t *frame, int i)
{
    if (!frame->ui->button[i].hover)
        sfSound_play(frame->ui->sounds[0].sound);
}

void disable_all_button(frame_t *frame)
{
    for (int i = 0; i < frame->ui->nb_buttons; i++) {
        frame->ui->button[i].disabled = true;
    }
}

void enable_button(frame_t *frame, int *button_indexes, int nb)
{
    disable_all_button(frame);
    for (int i = 0; i < nb; i++) {
        frame->ui->button[button_indexes[i]].disabled = false;
    }
}

static void click(button_t *button, frame_t *frame)
{
    if (button->clicked == true) {
        CLOCK[1].time = sfClock_getElapsedTime(CLOCK[1].clock);
        if (sfTime_asMilliseconds(CLOCK[1].time) < 10.0f)
            return;
        button->clicked = false;
        sfClock_restart(CLOCK[1].clock);
    }
}

void buttons_event(sfEvent *event, frame_t *frame)
{
    sfFloatRect rect;

    for (int i = 0; i < frame->ui->nb_buttons; i++) {
        if (frame->ui->button[i].disabled == true) {
            buttons_effect_disable(&frame->ui->button[i]);
            continue;
        }
        rect = sfSprite_getGlobalBounds(frame->ui->button[i].sprite);
        if (sfFloatRect_contains(&rect, frame->mouse.x, frame->mouse.y)) {
            play_hoversound(frame, i);
            frame->ui->button[i].hover = true;
            button_click_event(event, frame, &frame->ui->button[i]);
        } else {
            frame->ui->button[i].hover = false;
        }
        buttons_effect_hover_event(&frame->ui->button[i]);
        buttons_effect_click_event(&frame->ui->button[i]);
        click(&frame->ui->button[i], frame);
    }
}

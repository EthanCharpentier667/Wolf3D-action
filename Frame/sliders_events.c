/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** sliders_events
*/

#include "frame.h"

int apply_volume_change_sounds(frame_t *frame, float volume)
{
    for (int i = 0; i < frame->ui->nb_sounds; i++) {
        sfSound_setVolume(frame->ui->sounds[i].sound, volume * 100.0f);
    }
    UI->settings->sound_volume = volume;
    return 0;
}

int apply_volume_change_musics(frame_t *frame, float volume)
{
    for (int i = 0; i < frame->ui->nb_musics; i++) {
        sfMusic_setVolume(frame->ui->musics[i].music, volume * 100.0f);
    }
    UI->settings->music_volume = volume;
    return 0;
}

static bool check_slider_interaction(ui_t *ui, int i,
    sfVector2f mouse_pos, sfEvent *event)
{
    float handle_radius = sfCircleShape_getRadius(ui->sliders[i].handle);
    sfVector2f handle_pos = sfCircleShape_getPosition(ui->sliders[i].handle);
    sfFloatRect handle_bounds = frct(handle_pos.x, handle_pos.y,
        handle_radius * 2, handle_radius * 2);

    if (event->type == sfEvtMouseButtonPressed &&
        event->mouseButton.button == sfMouseLeft &&
        sfFloatRect_contains(&handle_bounds, mouse_pos.x, mouse_pos.y)) {
        ui->sliders[i].dragging = true;
    }
    if (event->type == sfEvtMouseButtonReleased &&
        event->mouseButton.button == sfMouseLeft) {
        ui->sliders[i].dragging = false;
    }
    return ui->sliders[i].dragging;
}

static void update_slider_position(frame_t *frame, int i, sfVector2f mouse_pos)
{
    float handle_radius = sfCircleShape_getRadius(UI->sliders[i].handle);
    float new_x = mouse_pos.x;
    float ratio = 0.0f;
    float fill_width = 0.0f;

    if (new_x < UI->sliders[i].pos.x)
        new_x = UI->sliders[i].pos.x;
    if (new_x > UI->sliders[i].pos.x + UI->sliders[i].size.x)
        new_x = UI->sliders[i].pos.x + UI->sliders[i].size.x;
    ratio = (new_x - UI->sliders[i].pos.x) / UI->sliders[i].size.x;
    UI->sliders[i].current_value = UI->sliders[i].min_value +
        ratio * (UI->sliders[i].max_value - UI->sliders[i].min_value);
    fill_width = UI->sliders[i].size.x * ratio;
    sfRectangleShape_setSize(UI->sliders[i].fill,
        v2f(fill_width, UI->sliders[i].size.y));
    sfCircleShape_setPosition(UI->sliders[i].handle,
        v2f(UI->sliders[i].pos.x + fill_width - handle_radius,
        UI->sliders[i].pos.y + UI->sliders[i].size.y / 2 - handle_radius));
    SLIDERS_INFOS[i].func(frame, UI->sliders[i].current_value);
}

void handle_slider_events(frame_t *frame, sfEvent *event)
{
    sfVector2f mouse_pos = frame->mouse;

    for (int i = 0; i < UI->nb_sliders; i++) {
        if (!(UI->scene & SLIDERS_INFOS[i].scene))
            continue;
        UI->sliders[i].dragging =
            check_slider_interaction(UI, i, mouse_pos, event);
        if (UI->sliders[i].dragging)
            update_slider_position(frame, i, mouse_pos);
    }
}

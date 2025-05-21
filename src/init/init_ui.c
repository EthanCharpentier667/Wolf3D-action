/*
** EPITECH PROJECT, 2025
** G-ING-200-NAN-2-1-myworld-ethan.charpentier
** File description:
** init_ui
*/

#include "frame.h"

static int init_sliders(frame_t *frame)
{
    int result = 0;

    frame->ui->nb_sliders = 0;
    for (int i = 0; SLIDERS_INFOS[i].scene != END; i++) {
        result += create_slider(frame->ui, SLIDERS_INFOS[i].pos,
            SLIDERS_INFOS[i].size, SLIDERS_INFOS[i].initial_value);
    }
    if (result != 0)
        return false;
    return true;
}

bool init_texts(ui_t *iu)
{
    int result = 0;

    iu->nb_texts = 0;
    for (int i = 0; TEXTS_INFOS[i].text; i++)
        result += create_text(iu, TEXTS_INFOS[i].text, TEXTS_INFOS[i].color,
            TEXTS_INFOS[i].infos);
    if (result > 0)
        return false;
    return true;
}

int init_helpboxed_button(ui_t *ui, char *path, sfFloatRect infos, int action)
{
    int result = 0;
    sfFloatRect textRect;

    result += create_helpboxed_button(ui, path, infos, action);
    sfText_setString(BUTTONS[NB_BUTTONS - 1].help_box->text,
        BUTTON_INFOS[NB_BUTTONS - 1].help);
    wrap_text(BUTTONS[NB_BUTTONS - 1].help_box->text, 200);
    textRect = sfText_getGlobalBounds(BUTTONS[NB_BUTTONS - 1].help_box->text);
    sfRectangleShape_setSize(BUTTONS[NB_BUTTONS - 1].help_box->box,
    (sfVector2f){textRect.width + 10, textRect.height + 10});
    return result;
}

bool init_buttons(frame_t *frame)
{
    int result = 0;

    frame->ui->button = malloc(sizeof(button_t));
    if (!frame->ui->button)
        return false;
    frame->ui->nb_buttons = 0;
    for (int i = 0; BUTTON_INFOS[i].path; i++) {
        if (BUTTON_INFOS[i].help == NULL)
            result += create_basic_button(frame->ui, BUTTON_INFOS[i].path,
                BUTTON_INFOS[i].infos, BUTTON_INFOS[i].action);
        else
            result += init_helpboxed_button(frame->ui, BUTTON_INFOS[i].path,
                BUTTON_INFOS[i].infos, BUTTON_INFOS[i].action);
    }
    if (result > 0)
        return false;
    applied_button(frame->ui);
    return true;
}

bool init_ui(frame_t *frame)
{
    frame->ui = malloc(sizeof(ui_t));
    memset(frame->ui, 0, sizeof(ui_t));
    if (!frame->ui)
        return false;
    if (!init_texts(frame->ui) || !init_buttons(frame)
        || !init_sliders(frame) || !init_settings(frame)
        || !init_vfxs(frame))
        return false;
    frame->window_size.x = WINDOWX;
    frame->window_size.y = WINDOWY;
    UI->refactor.x = 1;
    UI->refactor.y = 1;
    return true;
}

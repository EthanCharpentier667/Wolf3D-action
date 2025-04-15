/*
** EPITECH PROJECT, 2025
** G-ING-200-NAN-2-1-myworld-ethan.charpentier
** File description:
** init_ui
*/

#include "frame.h"

int init_texts(ui_t *iu)
{
    int result = 0;

    iu->nb_texts = 0;
    for (int i = 0; TEXTS_INFOS[i].text; i++)
        result += create_text(iu, TEXTS_INFOS[i].text, TEXTS_INFOS[i].color,
            TEXTS_INFOS[i].infos);
    if (result > 0)
        return 84;
    return 0;
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

int init_buttons(frame_t *frame)
{
    int result = 0;

    frame->ui->button = malloc(sizeof(button_t));
    if (!frame->ui->button)
        return 84;
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
        return 84;
    applied_button(frame->ui);
    return 0;
}

int init_ui(frame_t *frame)
{
    frame->ui = malloc(sizeof(ui_t));
    if (!frame->ui)
        return 84;
    init_buttons(frame);
    init_texts(frame->ui);
    return 0;
}

/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** settings
*/

#include "frame.h"

const char *get_key_name(sfKeyCode key_code)
{
    for (size_t i = 0; KEY_NAMES[i].name; i++) {
        if (KEY_NAMES[i].code == key_code) {
            return KEY_NAMES[i].name;
        }
    }
    return "Unknown";
}

static key_mapping_t *initialize_key_mappings(frame_t *frame)
{
    static key_mapping_t mappings[9] = {{KEY_UP, NULL}, {KEY_DOWN, NULL},
        {KEY_LEFT, NULL}, {KEY_RIGHT, NULL}, {KEY_INTERACT, NULL},
        {KEY_SHOOT, NULL}, {KEY_PAUSE, NULL}, {KEY_INVENTORY, NULL},
        {0, NULL}};

    mappings[0].key_address = &KEYBIND->up;
    mappings[1].key_address = &KEYBIND->down;
    mappings[2].key_address = &KEYBIND->left;
    mappings[3].key_address = &KEYBIND->right;
    mappings[4].key_address = &KEYBIND->interact;
    mappings[5].key_address = &KEYBIND->shoot;
    mappings[6].key_address = &KEYBIND->pause;
    mappings[7].key_address = &KEYBIND->inventory;
    return mappings;
}

sfKeyCode *get_button_keycode(frame_t *frame, int action)
{
    key_mapping_t *mappings = initialize_key_mappings(frame);

    for (int i = 0; mappings[i].action != 0; i++) {
        if (mappings[i].action == action) {
            return mappings[i].key_address;
        }
    }
    return &KEYBIND->up;
}

static sfFloatRect set_string_text(frame_t *frame, const char *text)
{
    sfText_setString(UI->texts[2].text, text);
    return sfText_getLocalBounds(UI->texts[2].text);
}

static void set_button_text(frame_t *frame, button_t *button)
{
    sfKeyCode *key_code = get_button_keycode(frame, button->action);
    const char *text = get_key_name(*key_code);
    sfFloatRect text_bounds = set_string_text(frame, text);
    sfFloatRect b_bounds = sfSprite_getGlobalBounds(button->sprite);
    float x_pos = button->pos.x + (b_bounds.width - text_bounds.width) / 2;
    float y_pos = button->pos.y + (b_bounds.height - text_bounds.height) / 2;

    y_pos -= text_bounds.top;
    x_pos -= text_bounds.left;
    sfText_setPosition(UI->texts[2].text, v2f(x_pos, y_pos));
    sfRenderWindow_drawText(WINDOW, UI->texts[2].text, NULL);
}

int settings(frame_t *frame)
{
    if (!(frame->ui->scene & SETTINGS_CONTROLS))
        return 0;
    for (int i = 0; i < frame->ui->nb_buttons; i++) {
        if (frame->ui->button[i].action < 0) {
            set_button_text(frame, &frame->ui->button[i]);
        }
    }
    return 0;
}

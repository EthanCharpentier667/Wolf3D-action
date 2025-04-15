/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** button
*/

#include "frame.h"

static void put_colors(button_t *button)
{
    button->colors[0] = sfColor_fromRGBA(255, 255, 255, 255);
    button->colors[1] = sfColor_fromRGBA(166, 166, 166, 255);
    button->colors[2] = sfColor_fromRGBA(80, 80, 80, 255);
    button->colors[3] = sfColor_fromRGBA(49, 49, 49, 255);
}

static int put_textures(button_t *button, char *path[4])
{
    sfTexture *texture1 = sfTexture_createFromFile(path[0], NULL);
    sfTexture *texture2 = sfTexture_createFromFile(path[1], NULL);
    sfTexture *texture3 = sfTexture_createFromFile(path[2], NULL);
    sfTexture *texture4 = sfTexture_createFromFile(path[3], NULL);

    if (!texture1 || !texture2 || !texture3 || !texture4)
        return 84;
    button->texture[0] = texture1;
    button->texture[1] = texture2;
    button->texture[2] = texture3;
    button->texture[3] = texture4;
    return 0;
}

static void put_infos(button_t *button, sfFloatRect infos)
{
    button->scale = (sfVector2f) {infos.width, infos.height};
    button->pos = (sfVector2f) {infos.left, infos.top};
}

void wrap_text(sfText *text, float max_width)
{
    const char *string = sfText_getString(text);
    char *str = strdup(string);
    int char_size = sfText_getCharacterSize(text);
    int last_space = -1;
    int width = 0;
    const sfFont *font = sfText_getFont(text);
    const sfUint32 *unicode = sfText_getUnicodeString(text);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            last_space = i;
        width += sfFont_getGlyph(font, unicode[i],
            char_size, sfFalse, 1).advance;
        if (width > max_width && last_space != -1) {
            str[last_space] = '\n';
            width = 0;
            last_space = -1;
        }
    }
    sfText_setString(text, str);
}

static int create_helpbox(button_t *button, char *text)
{
    HELPBOX = malloc(sizeof(help_box_t));
    if (!HELPBOX)
        return 84;
    button->help_box->box = sfRectangleShape_create();
    button->help_box->text = sfText_create();
    button->help_box->font = sfFont_createFromFile(FONTPATH);
    if (!HELPBOX->box || !HELPBOX->text || !HELPBOX->font)
        return 84;
    sfText_setFont(HELPBOX->text, HELPBOX->font);
    sfText_setColor(HELPBOX->text, sfYellow);
    sfText_setCharacterSize(HELPBOX->text, 20);
    sfText_setString(HELPBOX->text, text);
    sfRectangleShape_setFillColor(HELPBOX->box, sfBlue);
    sfRectangleShape_setOutlineColor(HELPBOX->box, sfYellow);
    sfRectangleShape_setOutlineThickness(HELPBOX->box, 2);
    return 0;
}

int create_helpboxed_button(ui_t *ui, char *path,
    sfFloatRect infos, int action)
{
    sfTexture *texture = sfTexture_createFromFile(path, NULL);

    BUTTONS = realloc(BUTTONS, (NB_BUTTONS + 1) * sizeof(button_t));
    if (!texture || !BUTTONS)
        return 84;
    BUTTONS[NB_BUTTONS].sprite = sfSprite_create();
    BUTTONS[NB_BUTTONS].texture[0] = texture;
    BUTTONS[NB_BUTTONS].action = action;
    put_colors(&BUTTONS[NB_BUTTONS]);
    put_infos(&BUTTONS[NB_BUTTONS], infos);
    BUTTONS[NB_BUTTONS].texture[1] = NULL;
    BUTTONS[NB_BUTTONS].type = 0;
    BUTTONS[NB_BUTTONS].hover = false;
    BUTTONS[NB_BUTTONS].disabled = false;
    BUTTONS[NB_BUTTONS].clicked = false;
    create_helpbox(&BUTTONS[NB_BUTTONS], "Help");
    NB_BUTTONS++;
    return 0;
}

int create_textured_button(ui_t *ui, char *path[4],
    sfFloatRect infos, int action)
{
    BUTTONS = realloc(BUTTONS, (NB_BUTTONS + 1) * sizeof(button_t));
    if (!BUTTONS)
        return 84;
    BUTTONS[NB_BUTTONS].sprite = sfSprite_create();
    if (put_textures(&BUTTONS[NB_BUTTONS], path) == 84)
        return 84;
    BUTTONS[NB_BUTTONS].action = action;
    put_infos(&BUTTONS[NB_BUTTONS], infos);
    BUTTONS[NB_BUTTONS].type = 1;
    BUTTONS[NB_BUTTONS].disabled = false;
    BUTTONS[NB_BUTTONS].help_box = NULL;
    NB_BUTTONS++;
    return 0;
}

int create_basic_button(ui_t *ui, char *path,
    sfFloatRect infos, int action)
{
    sfTexture *texture = sfTexture_createFromFile(path, NULL);

    BUTTONS = realloc(BUTTONS, (NB_BUTTONS + 1) * sizeof(button_t));
    if (!texture || !BUTTONS)
        return 84;
    BUTTONS[NB_BUTTONS].sprite = sfSprite_create();
    BUTTONS[NB_BUTTONS].texture[0] = texture;
    BUTTONS[NB_BUTTONS].action = action;
    put_colors(&BUTTONS[NB_BUTTONS]);
    put_infos(&BUTTONS[NB_BUTTONS], infos);
    BUTTONS[NB_BUTTONS].texture[1] = NULL;
    BUTTONS[NB_BUTTONS].type = 0;
    BUTTONS[NB_BUTTONS].hover = false;
    BUTTONS[NB_BUTTONS].clicked = false;
    BUTTONS[NB_BUTTONS].disabled = false;
    BUTTONS[NB_BUTTONS].help_box = NULL;
    NB_BUTTONS++;
    return 0;
}

void applied_button(ui_t *ui)
{
    for (int i = 0; i < NB_BUTTONS; i++) {
        sfSprite_setTexture(BUTTONS[i].sprite, BUTTONS[i].texture[0], sfTrue);
        sfSprite_setScale(BUTTONS[i].sprite, BUTTONS[i].scale);
        sfSprite_setPosition(BUTTONS[i].sprite, BUTTONS[i].pos);
    }
}

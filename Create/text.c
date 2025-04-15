/*
** EPITECH PROJECT, 2024
** graphic
** File description:
** text
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include "fb.h"
#include "frame.h"

int create_text(ui_t *ui, char *text,
    sfColor color, sfVector3f infos)
{
    if (ui->nb_texts > 0) {
        TEXTS = realloc(TEXTS, (NBTEXTS + 1) * sizeof(text_t));
        if (!TEXTS)
            return 84;
    } else {
        TEXTS = malloc(sizeof(text_t));
        if (!TEXTS)
            return 84;
    }
    TEXTS[NBTEXTS].font = sfFont_createFromFile(FONTPATH);
    TEXTS[NBTEXTS].text = sfText_create();
    if (!TEXTS[NBTEXTS].text || !TEXTS[NBTEXTS].font)
        return 84;
    sfText_setString(TEXTS[NBTEXTS].text, text);
    sfText_setFont(TEXTS[NBTEXTS].text, TEXTS[NBTEXTS].font);
    sfText_setCharacterSize(TEXTS[NBTEXTS].text, infos.x);
    sfText_setFillColor(TEXTS[NBTEXTS].text, color);
    sfText_setPosition(TEXTS[NBTEXTS].text, (sfVector2f){infos.y, infos.z});
    ui->nb_texts++;
    return 0;
}

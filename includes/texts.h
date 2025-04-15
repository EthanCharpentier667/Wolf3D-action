/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** texts
*/

#include "frame.h"

#ifndef TEXTS_H_
    #define TEXTS_H_

struct text_infos_s {
    char *text;
    sfColor color;
    sfVector3f infos;
    int scene;
};

extern const struct text_infos_s TEXTS_INFOS[];

#endif /* !TEXTS_H_ */

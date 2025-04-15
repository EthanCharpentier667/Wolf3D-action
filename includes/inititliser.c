/*
** EPITECH PROJECT, 2025
** BASE
** File description:
** inititliser
*/

#include "frame.h"

const struct button_infos_s BUTTON_INFOS[] = {
    //{PLAY, {800, 550, 0.5, 0.5}, RES "create.png",
    //  NULL, &do_create, MAINMENU},
    {0, {0, 0, 0, 0}, NULL, NULL, NULL, END}
};

const struct images_infos_s IMAGES_INFOS[] = {
    //{RES "backgound.png", {1, 1}, {0, 0}, MAINMENU},
    {NULL, {0, 0}, {0, 0}, END},
};

const struct images_rec_infos_s IMAGES_REC_INFOS[] = {
    {NULL, {0, 0, 0, 0}, {0, 0, 0, 0}, END},
};

const struct text_infos_s TEXTS_INFOS[] = {
    //{"SIZE :", {0, 0, 0, 255}, {50, 130, 775}, MAINMENU},
    {NULL, {0, 0, 0, 255}, {0, 0, 0}, END},
};

const struct sound_infos_s SOUNDS_INFOS[] = {
    {RES "hover.wav"},
    {RES "click.wav"},
    {NULL}
};

const struct musics_infos_s MUSICS_INFOS[] = {
    //{RES "theme.ogg"},
    {NULL}
};

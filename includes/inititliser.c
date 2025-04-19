/*
** EPITECH PROJECT, 2025
** BASE
** File description:
** inititliser
*/

#include "frame.h"

const struct item_infos_s ITEM_INFOS[] = {
    {RES "lamp.png", {0.7, 0.7}, {250, 250, 40}, {-1, -1, -1, -1}},
    {RES "barrel.png", {0.6, 0.6}, {150, 230, -250}, {-1, -1, -1, -1}},
    {NULL, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}}
};

const struct enemy_infos_s ENEMY_INFOS[] = {
    {RES "enemy.png", {2.5, 2.5}, {250, 250, -550}, {0, 0, 65, 65}, 3},
    {NULL, {0, 0}, {0, 0, 0}, {-1, -1, -1, -1}, 0}
};

const struct button_infos_s BUTTON_INFOS[] = {
    {PLAY, {325, 325, 0.5, 0.5}, RES "play.png",
        NULL, &do_play, MAINMENU},
    {0, {0, 0, 0, 0}, NULL, NULL, NULL, END}
};

const struct images_infos_s IMAGES_INFOS[] = {
    {RES "background.png", {0.325, 0.5}, {0, 0}, MAINMENU},
    {RES "logo.png", {0.7, 0.8}, {125, 50}, MAINMENU},
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

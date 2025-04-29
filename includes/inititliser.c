/*
** EPITECH PROJECT, 2025
** BASE
** File description:
** inititliser
*/

#include "frame.h"

const struct item_infos_s ITEM_INFOS[] = {
    {RES "lamp.png", {0.7, 0.7}, {250, 250, 40},
        {-1, -1, -1, -1}, "lamp", false},
    {RES "barrel.png", {0.6, 0.6}, {150, 230, -250},
        {-1, -1, -1, -1}, "barrel", true},
    {NULL, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}, NULL, false}
};

const struct enemy_infos_s ENEMY_INFOS[] = {
    {RES "enemy.png", {2.5, 2.5}, {250, 250, -550},
        {0, 0, 65, 65}, 3, 100},
    {NULL, {0, 0}, {0, 0, 0}, {-1, -1, -1, -1}, 0, 0}
};

const struct button_infos_s BUTTON_INFOS[] = {
    {PLAY, {325, 300, 0.5, 0.5}, RES "play.png",
        NULL, &do_play, MAINMENU},
    {SETTING, {325, 375, 0.5, 0.5}, RES "settings.png",
        NULL, &do_settings, MAINMENU},
    {BACK_TO_MAINMENU, {5, 5, 0.5, 0.5}, RES "go_back.png",
        NULL, &do_mainmenu, LOADS | SETTINGS_RESOLUTION |
        SETTINGS_CONTROLS | SETTINGS_AUDIO},
    {QUIT, {325, 525, 1.25, 1.25}, RES "quit.png",
        NULL, &do_mm_quit, MAINMENU},
    {LOAD, {325, 450, 1.25, 1.25}, RES "load.png",
        NULL, &do_load, MAINMENU},
    {0, {0, 0, 0, 0}, NULL, NULL, NULL, END}
};

const struct images_infos_s IMAGES_INFOS[] = {
    {RES "background.png", {0.325, 0.5}, {0, 0}, MAINMENU |
        SETTINGS_RESOLUTION | SETTINGS_CONTROLS | SETTINGS_AUDIO | LOADS},
    {RES "logo.png", {0.7, 0.8}, {125, 50}, MAINMENU},
    {RES "settings-logo.png", {0.4, 0.5}, {160, -100}, SETTINGS_AUDIO},
    {RES "loads.png", {0.4, 0.4}, {180, -50}, LOADS},
    {NULL, {0, 0}, {0, 0}, END},
};

const struct images_rec_infos_s IMAGES_REC_INFOS[] = {
    {NULL, {0, 0, 0, 0}, {0, 0, 0, 0}, END},
};

const struct text_infos_s TEXTS_INFOS[] = {
    {"SOUNDS VOLUME:", {255, 255, 255, 255}, {30, 200, 250}, SETTINGS_AUDIO},
    {"MUSICS VOLUME:", {255, 255, 255, 255}, {30, 200, 350}, SETTINGS_AUDIO},
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

const struct slider_infos_s SLIDERS_INFOS[] = {
    {{200, 300}, {300, 20}, 0.5, &apply_volume_change_sounds, SETTINGS_AUDIO},
    {{200, 400}, {300, 20}, 0.5, &apply_volume_change_musics, SETTINGS_AUDIO},
    {{0, 0}, {0, 0}, 0.5, NULL, END},
};

const struct scenes_infos_s SCENES_INFOS[] = {
    {MAINMENU, &mainmenu},
    {GAME, &game},
    {SETTINGS_AUDIO | SETTINGS_CONTROLS | SETTINGS_RESOLUTION, &settings},
    {LOADS, &load_scene},
    {END, NULL}
};

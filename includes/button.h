/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** button
*/

#include "frame.h"

#ifndef BUTTON_H_
    #define BUTTON_H_

typedef struct frame_s frame_t;

    #define HSAVE "Save the map in the file you loaded"
    #define HADDSIZE "ADD a size to the map"
    #define HSUBSIZE "Substract a size x and y to the map width and heigth"
    #define HAPPLYSIZE "Apply the new size to the map"
    #define HUP "When right click on tile/line/vertex, it is moved up"
    #define HDOWN "When right click on tile/line/vertex, it is moved down"
    #define HRESET "Reset all modifications to get a flat map"

enum buttons_actions {
    KEY_UP = -1,
    KEY_DOWN = -2,
    KEY_LEFT = -3,
    KEY_RIGHT = -4,
    KEY_INTERACT = -5,
    KEY_PAUSE = -6,
    KEY_SHOOT = -7,
    KEY_INVENTORY = -8,
    PLAY = 0,
    SETTING,
    BSETTINGS_AUDIO,
    BSETTINGS_CONTROLS,
    BSETTINGS_RESOLUTION,
    ADD_RESOLUTION,
    SUB_RESOLUTION,
    BACK,
    QUIT,
    LOAD,
    SAVE,
    RESUME,
    QUIT_GAME,
    BGAME_OVER,
    AITEM,
    SAVES_LIST,
};

struct button_infos_s {
    int action;
    sfFloatRect infos;
    char *path;
    char *help;
    int (*func)(frame_t *frame);
    int scene;
};

int do_play(frame_t *frame);
int do_settings(frame_t *frame);
int do_goback(frame_t *frame);
int do_game_quit(frame_t *frame);
int do_mm_quit(frame_t *frame);
int do_resume(frame_t *frame);
int do_load(frame_t *frame);
//int do_save(frame_t *frame);
int do_settings_control(frame_t *frame);
int do_settings_video(frame_t *frame);
int do_add_resolution(frame_t *frame);
int do_sub_resolution(frame_t *frame);
int do_save(frame_t *frame);

//SPECIAL - SAVES
int load_save_callback(frame_t *frame, int button_index);
//SPECIAL - KEYBINDS
int set_keybinds(frame_t *frame, int keybind);

extern const struct button_infos_s BUTTON_INFOS[];

#endif /* !BUTTON_H_ */

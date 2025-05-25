/*
** EPITECH PROJECT, 2025
** BASE
** File description:
** inititliser
*/

#include "frame.h"

// PATH ; POS ; ANGLE; SCALE ; TYPE ; REC
const struct fixed_object_infos_s FIXED_OBJECT_INFOS[] = {
    {RES "door.png", {128 + 32, 96, 0}, M_PI / 2,
        {64, 64}, DOOR_CLOSED, {0, 0, 128, 128}},
    {NULL, {0, 0, 0.1}, 0, {0, 0}, 0, {0, 0, 0, 0}}
};

// PATH ; SCALE ; POSITION ; REC ; NAME: ;
// IS_PICKABLE ; IS_USEABLE ; DESCRIPTION
const struct item_infos_s ITEM_INFOS[] = {
    {RES "lamp.png", {0.7, 0.7}, {250, 250, 0.1},
        {-1, -1, -1, -1}, "lamp", false, false, ""},
    {RES "barrel.png", {0.6, 0.6}, {150, 230, -0.50},
        {-1, -1, -1, -1}, "barrel", false, false, ""},
    {RES "key.png", {0.5, 0.5}, {110, 96, -0.50},
        {-1, -1, -1, -1}, "Key", true, false, "The Key Of The Door"},
    {RES "key.png", {0.5, 0.5}, {250, 280, -0.50},
        {-1, -1, -1, -1}, "Key", true, false, "The Key Of The Door"},
    {RES "heal.png", {0.8, 0.8}, {450, 300, -0.50},
        {-1, -1, -1, -1}, "Heal", true, true, "Heal of 20 HP"},
    {RES "ammo_box.png", { 0.5, 0.5}, {450, 350, -0.50},
        {-1, -1, -1, -1}, "Ammo_box", true, true,
        "Take your weapon in hand\nand use it for 40 ammo"},
    {NULL, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}, "", false, false, ""},
};

// PATH ; SCALE ; POSITION ; REC ; SPEED ; LIFE ;
// ATTACK_RANGE; FOLLOW_RANGE ; DAMAGE ; COOLDOWN ; DROP
// (name of item or NULL if no drops)
const struct enemy_infos_s ENEMY_INFOS[] = {
    /*{RES "enemy.png", {2.5, 2.5}, {250, 250, -0.90},
        {0, 0, 65, 65}, 0.5, 100, 150, 200, 10, 1, "Ammo_box", BASIC},
    {RES "enemy2.png", {2.5, 2.5}, {250, 300, -0.90},
        {0, 0, 65, 65}, 0.5, 100, 150, 200, 10, 1, "Heal", BASIC},*/
    {RES "Hitler1.png", {2.5, 2.5}, {250, 350, -0.90},
        {0, 0, 74, 72}, 0.5, 400, 100, 300, 20, 0.5f, NULL, HITLER},
    {NULL, {0, 0}, {0, 0, 0}, {-1, -1, -1, -1}, 0, 0, 0, 0, 0, 0, NULL, 0}
};

// TYPE ; SCALE & POSITION ; REC ; PATH
// HELPBOX_TEXT ; ACTION ; SCENE | SCENES
const struct button_infos_s BUTTON_INFOS[] = {
    {PLAY, {325, 300, 0.5, 0.5}, RES "play.png",
        NULL, &do_play, MAINMENU},
    {SETTING, {325, 375, 0.5, 0.5}, RES "settings.png",
        NULL, &do_settings, MAINMENU},
    {BSETTINGS_CONTROLS, {100, 250, 0.5, 0.5}, RES "controls.png",
        NULL, &do_settings_control, SETTINGS_RESOLUTION |
        SETTINGS_CONTROLS | SETTINGS_AUDIO},
    {BSETTINGS_RESOLUTION, {100, 350, 0.5, 0.5}, RES "resolution.png",
        NULL, &do_settings_video, SETTINGS_RESOLUTION |
        SETTINGS_CONTROLS | SETTINGS_AUDIO},
    {BSETTINGS_AUDIO, {100, 450, 0.5, 0.5}, RES "audio.png",
        NULL, &do_settings, SETTINGS_RESOLUTION |
        SETTINGS_CONTROLS | SETTINGS_AUDIO},
    {ADD_RESOLUTION, {325, 300, 0.5, 0.5}, RES "resadd.png",
        NULL, &do_add_resolution, SETTINGS_RESOLUTION},
    {SUB_RESOLUTION, {325, 375, 0.5, 0.5}, RES "ressub.png",
        NULL, &do_sub_resolution, SETTINGS_RESOLUTION},
    {BACK, {5, 5, 0.5, 0.5}, RES "go_back.png",
        NULL, &do_goback, LOADS | SETTINGS_RESOLUTION |
        SETTINGS_CONTROLS | SETTINGS_AUDIO},
    {QUIT, {325, 525, 1.25, 1.25}, RES "quit.png",
        NULL, &do_mm_quit, MAINMENU},
    {LOAD, {325, 450, 1.25, 1.25}, RES "load.png",
        NULL, &do_load, MAINMENU},
    {QUIT_GAME, {325, 400, 1.5, 1.5}, RES "quit.png",
        NULL, &do_game_quit, PAUSE},
    {RESUME, {325, 200, 1.5, 1.5}, RES "resume.png",
        NULL, &do_resume, PAUSE},
    {SETTING, {325, 300, 0.58, 0.58}, RES "settings.png",
        NULL, &do_settings, PAUSE},
    {KEY_UP, {375, 300, 0.5, 0.5}, RES "keybind.png",
        NULL, NULL, SETTINGS_CONTROLS},
    {KEY_DOWN, {375, 375, 0.5, 0.5}, RES "keybind.png",
        NULL, NULL, SETTINGS_CONTROLS},
    {KEY_LEFT, {375, 450, 0.5, 0.5}, RES "keybind.png",
        NULL, NULL, SETTINGS_CONTROLS},
    {KEY_RIGHT, {375, 525, 0.5, 0.5}, RES "keybind.png",
        NULL, NULL, SETTINGS_CONTROLS},
    {KEY_INTERACT, {575, 300, 0.5, 0.5}, RES "keybind.png",
        NULL, NULL, SETTINGS_CONTROLS},
    {KEY_INVENTORY, {575, 375, 0.5, 0.5}, RES "keybind.png",
        NULL, NULL, SETTINGS_CONTROLS},
    {KEY_PAUSE, {575, 450, 0.5, 0.5}, RES "keybind.png",
        NULL, NULL, SETTINGS_CONTROLS},
    {QUIT, {325, 400, 1.5, 1.5}, RES "quit.png",
        NULL, &do_mm_quit, WIN},
    {QUIT, {325, 400, 1.5, 1.5}, RES "quit.png",
        NULL, &do_mm_quit, GAME_OVER},
    {0, {0, 0, 0, 0}, NULL, NULL, NULL, END}
};

const struct images_infos_s IMAGES_INFOS[] = {
    {RES "background.png", {0.325, 0.5}, {0, 0}, MAINMENU |
        SETTINGS_RESOLUTION | SETTINGS_CONTROLS | SETTINGS_AUDIO | LOADS},
    {RES "logo.png", {0.7, 0.8}, {125, 50}, MAINMENU},
    {RES "settings-logo.png", {0.4, 0.5}, {160, -100}, SETTINGS_AUDIO |
        SETTINGS_CONTROLS | SETTINGS_RESOLUTION},
    {RES "loads.png", {0.4, 0.4}, {180, -50}, LOADS},
    {RES "panel.png", {0.4, 0.5}, {200, 60}, PAUSE},
    {RES "pause.png", {0.3, 0.3}, {250, -50}, PAUSE},
    {RES "victory.png", {3, 3}, {180, 0}, WIN},
    {RES "gameover.png", {3, 3}, {180, 0}, GAME_OVER},
    {NULL, {0, 0}, {0, 0}, END},
};

const struct images_rec_infos_s IMAGES_REC_INFOS[] = {
    {NULL, {0, 0, 0, 0}, {0, 0, 0, 0}, END},
};

const struct text_infos_s TEXTS_INFOS[] = {
    {"SOUNDS VOLUME:", {255, 255, 255, 255}, {30, 200, 250}, SETTINGS_AUDIO},
    {"MUSICS VOLUME:", {255, 255, 255, 255}, {30, 200, 350}, SETTINGS_AUDIO},
    {"E", {255, 255, 255, 255}, {30, 200, 350}, SETTINGS_CONTROLS},
    {"Forward: ", {255, 255, 255, 255}, {30, 240, 305}, SETTINGS_CONTROLS},
    {"Backward: ", {255, 255, 255, 255}, {30, 240, 380}, SETTINGS_CONTROLS},
    {"Left: ", {255, 255, 255, 255}, {30, 240, 455}, SETTINGS_CONTROLS},
    {"Right: ", {255, 255, 255, 255}, {30, 240, 530}, SETTINGS_CONTROLS},
    {"Interact: ", {255, 255, 255, 255}, {30, 440, 305}, SETTINGS_CONTROLS},
    {"Inventory: ", {255, 255, 255, 255}, {30, 440, 380}, SETTINGS_CONTROLS},
    {"Pause: ", {255, 255, 255, 255}, {30, 440, 455}, SETTINGS_CONTROLS},
    {"00:00", {255, 255, 255, 255}, {40, 10, 10}, GAME},
    {"Score :", {255, 255, 255, 255}, {40, 220, 300}, WIN | GAME_OVER},
    {"Difficulty: ", {255, 255, 255, 255}, {40, 220, 230}, SETTINGS_CONTROLS},
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
    {{400, 250}, {300, 20}, 0.0, &apply_difficulty_change, SETTINGS_CONTROLS},
    {{0, 0}, {0, 0}, 0.5, NULL, END},
};

const struct scenes_infos_s SCENES_INFOS[] = {
    {MAINMENU, &mainmenu},
    {GAME, &game},
    {LOADS, &load_scene},
    {WIN, &victory},
    {GAME_OVER, &game_over},
    {END, NULL}
};

const struct env_infos_s ENVIRONNEMENT_INFOS[] = {
    {RES "wall.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 1},
    {RES "wall2.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 2},
    {RES "wall3.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 3},
    {RES "wall4.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 4},
    {NULL, {0, 0, 0, 0}, {0, 0}, false, false, false, 0}
};

//Format: texture_path, alt_texture_path, scale,
//rec, total_frames, alt_total_frames,frame_width, frame_height, name,
//attack_range, atk_width, damage, ammo_capacity, fire_rate, windup_time, type
const struct weapon_infos_s WEAPON_INFOS[] = {
    {RES "knife.png", NULL, {0.6, 0.6}, {0, 0, 728, 650},
        5, 0, 728, 650, "Knife", 40.0f, 0.4f, 50, 0, 0.0f, 0.0f,
        WEAPON_TYPE_MELEE},
    {RES "Machine_Gun_Ajustement.png", RES "Machine_Gun_Tir.png", {0.6, 0.6},
        {0, 0, 728, 650}, 4, 2, 728, 650, "Machine Gun",
        1000.0f, 0.8f, 10, 200,
        20.0f, 0.5f, WEAPON_TYPE_AUTOMATIC},
    {NULL, NULL, {0, 0}, {0, 0, 0, 0}, 0, 0, 0, 0,
        NULL, 0.0f, 0, 0, 0, 0.0f, 0.0f, 0}
};

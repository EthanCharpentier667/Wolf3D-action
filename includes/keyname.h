/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** keyname
*/

#include "frame.h"

#ifndef KEYNAME_H_
    #define KEYNAME_H_

typedef struct {
    sfKeyCode code;
    const char *name;
} key_name_t;

static const key_name_t KEY_NAMES[] = {
    {sfKeyA, "A"}, {sfKeyB, "B"}, {sfKeyC, "C"}, {sfKeyD, "D"},
    {sfKeyE, "E"}, {sfKeyF, "F"}, {sfKeyG, "G"}, {sfKeyH, "H"},
    {sfKeyI, "I"}, {sfKeyJ, "J"}, {sfKeyK, "K"}, {sfKeyL, "L"},
    {sfKeyM, "M"}, {sfKeyN, "N"}, {sfKeyO, "O"}, {sfKeyP, "P"},
    {sfKeyQ, "Q"}, {sfKeyR, "R"}, {sfKeyS, "S"}, {sfKeyT, "T"},
    {sfKeyU, "U"}, {sfKeyV, "V"}, {sfKeyW, "W"}, {sfKeyX, "X"},
    {sfKeyY, "Y"}, {sfKeyZ, "Z"},
    {sfKeyNum0, "0"}, {sfKeyNum1, "1"}, {sfKeyNum2, "2"}, {sfKeyNum3, "3"},
    {sfKeyNum4, "4"}, {sfKeyNum5, "5"}, {sfKeyNum6, "6"}, {sfKeyNum7, "7"},
    {sfKeyNum8, "8"}, {sfKeyNum9, "9"},
    {sfKeyEscape, "Escape"}, {sfKeyLControl, "Left Ctrl"},
    {sfKeyLShift, "Left Shift"}, {sfKeyLAlt, "Left Alt"},
    {sfKeyLSystem, "Left OS"}, {sfKeyRControl, "Right Ctrl"},
    {sfKeyRShift, "Right Shift"}, {sfKeyRAlt, "Right Alt"},
    {sfKeyRSystem, "Right OS"},
    {sfKeyMenu, "Menu"}, {sfKeyLBracket, "["}, {sfKeyRBracket, "]"},
    {sfKeySemicolon, ";"}, {sfKeyComma, ","},
    {sfKeyPeriod, "."}, {sfKeyApostrophe, "'"},
    {sfKeySlash, "/"}, {sfKeyBackslash, "\\"}, {sfKeyGrave, "`"},
    {sfKeyEqual, "="}, {sfKeyHyphen, "-"},
    {sfKeySpace, "Space"}, {sfKeyEnter, "Enter"},
    {sfKeyBackspace, "Backspace"}, {sfKeyTab, "Tab"}, {sfKeyPageUp, "Page Up"},
    {sfKeyPageDown, "Page Down"}, {sfKeyEnd, "End"}, {sfKeyHome, "Home"},
    {sfKeyInsert, "Insert"}, {sfKeyDelete, "Delete"}, {sfKeyAdd, "+"},
    {sfKeySubtract, "-"}, {sfKeyMultiply, "*"}, {sfKeyDivide, "/"},
    {sfKeyLeft, "Left"}, {sfKeyRight, "Right"},
    {sfKeyUp, "Up"}, {sfKeyDown, "Down"},
    {sfKeyNumpad0, "Num 0"}, {sfKeyNumpad1, "Num 1"}, {sfKeyNumpad2, "Num 2"},
    {sfKeyNumpad3, "Num 3"}, {sfKeyNumpad4, "Num 4"}, {sfKeyNumpad5, "Num 5"},
    {sfKeyNumpad6, "Num 6"}, {sfKeyNumpad7, "Num 7"}, {sfKeyNumpad8, "Num 8"},
    {sfKeyNumpad9, "Num 9"},
    {sfKeyF1, "F1"}, {sfKeyF2, "F2"}, {sfKeyF3, "F3"}, {sfKeyF4, "F4"},
    {sfKeyF5, "F5"}, {sfKeyF6, "F6"}, {sfKeyF7, "F7"}, {sfKeyF8, "F8"},
    {sfKeyF9, "F9"}, {sfKeyF10, "F10"}, {sfKeyF11, "F11"}, {sfKeyF12, "F12"},
    {sfKeyF13, "F13"}, {sfKeyF14, "F14"}, {sfKeyF15, "F15"},
    {sfKeyPause, "Pause"},
    {sfKeyUnknown, "Unknown"}
};

#endif /* !KEYNAME_H_ */

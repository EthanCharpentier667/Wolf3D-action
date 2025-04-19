/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** slider
*/

#include "frame.h"

#ifndef SLIDER_H_
    #define SLIDER_H_

struct slider_infos_s {
    sfVector2f pos;
    sfVector2f size;
    float initial_value;
    int (*func)(frame_t *frame, float value);
    int scene;
};

int apply_volume_change(frame_t *frame, float volume);

extern const struct slider_infos_s SLIDERS_INFOS[];

#endif /* !SLIDER_H_ */

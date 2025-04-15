/*
** EPITECH PROJECT, 2024
** graphic
** File description:
** clocks
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include "fb.h"
#include "frame.h"

int create_clock(frame_t *frame, int nb)
{
    CLOCK[nb].clock = sfClock_create();
    if (!CLOCK[nb].clock)
        return 84;
    return 0;
}

/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** math
*/

#include "frame.h"

double view_angle(float angle)
{
    return fmod(angle, 2 * M_PI);
}

float lerp(float a, float b, float mult)
{
    return a + (b - a) * mult;
}

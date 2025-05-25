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

float clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

float rand_range(float min, float max)
{
    return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

float hypot3f(float x, float y, float z)
{
    return sqrtf(x * x + y * y + z * z);
}

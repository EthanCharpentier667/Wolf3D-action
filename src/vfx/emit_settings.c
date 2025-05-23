/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** emit
*/

#include "frame.h"

emit_settings_t create_emit_settings(float strength, float sizes,
    float rot, sfColor color)
{
    emit_settings_t emit_set = {0};

    memset(&emit_set, 0, sizeof(emit_settings_t));
    emit_set.strength = strength;
    emit_set.sizes = sizes;
    emit_set.rotation = rot;
    emit_set.color = color;
    return emit_set;
}

void set_emit_settings(emit_settings_t *emit_set,
    float life_time, unsigned int nb, float gravity)
{
    if (!emit_set)
        return;
    emit_set->lifetime = life_time;
    emit_set->nb = nb;
    emit_set->gravity = gravity;
}

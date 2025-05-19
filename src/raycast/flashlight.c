/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** flashlight
*/

#include "frame.h"

void clear_light_map(frame_t *frame)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++)
            frame->light_map[y][x] = 0;
}

float normalize_angle(float angle)
{
    while (angle > M_PI)
        angle -= 2 * M_PI;
    while (angle < (- M_PI))
        angle += 2 * M_PI;
    return angle;
}

static float calculate_light_intensity(float dist, float range,
    float intensity_multiplier)
{
    float base = 255.0f * (1.0f - fminf(dist / range, 1.0f));
    float falloff = (1.0f - dist / range);

    return base * falloff * intensity_multiplier;
}

static void cmp_wall_l(frame_t *frame, sfVector2f ray_pos, sfVector2f ray_dir,
    sfVector2f intes_step_s)
{
    int map_x = (int)(ray_pos.x / TILE_SIZE);
    int map_y = (int)(ray_pos.y / TILE_SIZE);

    for (int i = 0; i < 3; i++) {
        ray_pos.x += ray_dir.x * intes_step_s.y;
        ray_pos.y += ray_dir.y * intes_step_s.y;
        if (!(map_x >= 0 && map_x < MAP_WIDTH &&
            map_y >= 0 && map_y < MAP_HEIGHT))
            break;
        frame->light_map[map_y][map_x] = fmaxf(frame->light_map[map_y][map_x],
            intes_step_s.x * 0.8f);
    }
}

static float cmp_intensity_ap(frame_t *frame, sfVector2f point)
{
    float dist = sqrtf(powf(point.x - PLAYER->pos.x, 2) +
        powf(point.y - PLAYER->pos.y, 2));

    return calculate_light_intensity(dist,
        PLAYER->flashlight_range, PLAYER->flashlight_intensity);
}

static void apply_light_to_cell(frame_t *frame, sfVector2f point,
    int map_x, int map_y)
{
    float dist = sqrtf(powf(point.x - PLAYER->pos.x, 2) +
        powf(point.y - PLAYER->pos.y, 2));
    float intensity = calculate_light_intensity(
        dist, PLAYER->flashlight_range, PLAYER->flashlight_intensity);

    frame->light_map[map_y][map_x] =
        fmaxf(frame->light_map[map_y][map_x], intensity);
}

static void cast_lighting_ray(frame_t *frame, float ray_angle)
{
    float ray_length = 0;
    sfVector2f rd = {cosf(ray_angle), sinf(ray_angle)};
    sfVector2f rp = PLAYER->pos;
    int mx = 0;
    int my = 0;

    while (ray_length < PLAYER->flashlight_range) {
        rp.x += rd.x * 0.5f;
        rp.y += rd.y * 0.5f;
        mx = (int)(rp.x / TILE_SIZE);
        my = (int)(rp.y / TILE_SIZE);
        if (!(mx >= 0 && mx < MAP_WIDTH && my >= 0 && my < MAP_HEIGHT))
            break;
        apply_light_to_cell(frame, rp, mx, my);
        if (is_osbtacle(frame, rp.x, rp.y) > 0) {
            cmp_wall_l(frame, rp, rd, v2f(cmp_intensity_ap(frame, rp), 0.5f));
            break;
        }
        ray_length += 0.5f;
    }
}

void calculate_player_lighting(frame_t *frame)
{
    float ray_step = (2 * M_PI) / 120;

    for (float ray_angle = 0; ray_angle < 2 * M_PI; ray_angle += ray_step)
        cast_lighting_ray(frame, ray_angle);
}

float get_light_intensity(frame_t *frame, world_pos_t world_pos)
{
    float ambient = 0.15f;
    int map_x = (int)(world_pos.world_x / TILE_SIZE);
    int map_y = (int)(world_pos.world_y / TILE_SIZE);
    float light = 0.0f;

    if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
        return ambient;
    light = frame->light_map[map_y][map_x] / 255.0f;
    return fmaxf(light, ambient);
}

void destroy_flashlight(frame_t *frame)
{
    if (frame->light_map) {
        for (int i = 0; i < MAP_HEIGHT; i++)
            free(frame->light_map[i]);
        free(frame->light_map);
    }
}

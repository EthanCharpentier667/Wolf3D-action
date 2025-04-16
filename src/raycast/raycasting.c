/*
** EPITECH PROJECT, 2025
** bswolf3D
** File description:
** raycasting
*/

#include "frame.h"

/*
static sfColor get_wall_color(sfVector2f ray_pos, sfVector2f ray_dir)
{
    int map_x = ray_pos.x / TILE_SIZE;
    int map_y = ray_pos.y / TILE_SIZE;
    float hit_x = ray_pos.x - (map_x * TILE_SIZE);
    float hit_y = ray_pos.y - (map_y * TILE_SIZE);

    if (hit_x < 1.0 && ray_dir.x > 0)
        return sfColor_fromRGB(180, 0, 0);
    if (hit_x > TILE_SIZE - 1.0 && ray_dir.x < 0)
        return sfColor_fromRGB(150, 0, 0);
    if (hit_y < 1.0 && ray_dir.y > 0)
        return sfColor_fromRGB(255, 0, 0);
    if (hit_y > TILE_SIZE - 1.0 && ray_dir.y < 0)
        return sfColor_fromRGB(220, 0, 0);
    return sfColor_fromRGB(255, 255, 255);
}*/


bool is_wall_vertical(sfVector2f ray_pos)
{
    int map_x = ray_pos.x / TILE_SIZE;
    int map_y = ray_pos.y / TILE_SIZE;
    float hit_x = ray_pos.x - (map_x * TILE_SIZE);
    float hit_y = ray_pos.y - (map_y * TILE_SIZE);
    float dist_to_vertical = fminf(hit_x, TILE_SIZE - hit_x);
    float dist_to_horizontal = fminf(hit_y, TILE_SIZE - hit_y);

    if ((hit_x < 1.0f || hit_x > TILE_SIZE - 1.0f) &&
        !(hit_y < 1.0f || hit_y > TILE_SIZE - 1.0f)) {
        return true;
    }
    if ((hit_y < 1.0f || hit_y > TILE_SIZE - 1.0f) &&
        !(hit_x < 1.0f || hit_x > TILE_SIZE - 1.0f)) {
        return false;
    }
    return dist_to_vertical < dist_to_horizontal;
}

static void draw_wall_cols(frame_t *frame,
    float corrected_dist, float ray_angle, sfVector2f ray_pos)
{
    int wall_height = (WINDOWY * TILE_SIZE) / corrected_dist;
    int ray_column = (int)((ray_angle -
        (PLAYER->angle - FOV / 2)) * WINDOWX / FOV);
    bool hit_vertical = is_wall_vertical(ray_pos);

    render_wall_column_textured(frame, v2f(ray_column, wall_height),
        v2f(ray_pos.x, ray_pos.y), hit_vertical);
}

float cast_single_ray(float ray_angle, frame_t *frame)
{
    float ray_length = 0;
    float ray_step = 0.1;
    sfVector2f ray_dir = {cos(ray_angle), sin(ray_angle)};
    sfVector2f ray_pos = PLAYER->pos;
    float corrected_dist = 0;

    while (ray_length < 1000) {
        ray_pos.x += ray_dir.x * ray_step;
        ray_pos.y += ray_dir.y * ray_step;
        if (is_osbtacle(ray_pos.x, ray_pos.y) == WALL) {
            corrected_dist = ray_length * cos(ray_angle - PLAYER->angle);
            draw_wall_cols(frame, corrected_dist, ray_angle, ray_pos);
            return corrected_dist;
        }
        ray_length += ray_step;
    }
    return 1000;
}

void cast_all_rays(frame_t *frame)
{
    float ray_angle = PLAYER->angle - (FOV / 2);
    float ray_step = FOV / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++) {
        frame->z_buffer[i] = cast_single_ray(ray_angle, frame);
        ray_angle += ray_step;
    }
}

/*
** EPITECH PROJECT, 2025
** bswolf3D
** File description:
** raycasting
*/

#include "frame.h"

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
    sfVector2f corrected_dist_ray_angle, sfVector2f ray_pos, int i)
{
    int wall_height = (WINDOWY * TILE_SIZE) / corrected_dist_ray_angle.x;
    int ray_column = (int)((corrected_dist_ray_angle.y -
        (PLAYER->angle.x - FOV / 2)) * WINDOWX / FOV);
    world_pos_t world_pos = {ray_pos.x, ray_pos.y};
    float light = get_light_intensity(frame, world_pos);
    wall_render_params_t prms = {
        .column_wall_pos = v2f(ray_column, wall_height),
        .hit_position = ray_pos,
        .is_vertical = is_wall_vertical(ray_pos),
        .vertical_offset = (int)(WINDOWY * tanf(PLAYER->angle.y) / 2),
        .ray_index = (i - 1),
        .light_color = sfColor_fromRGBA(
        255 * light, 255 * light, 255 * light, 255)
    };

    render_wall_column_textured(frame, prms);
}

float cast_single_ray(float ray_angle, frame_t *frame)
{
    float ray_length = 0;
    float ray_step = 0.5f;
    sfVector2f ray_dir = {cos(ray_angle), sin(ray_angle)};
    sfVector2f ray_pos = PLAYER->pos;
    float corrected_dist = 0;
    int obstacle = 0;

    while (ray_length < MAX_RAY_LENGTH) {
        ray_pos.x += ray_dir.x * ray_step;
        ray_pos.y += ray_dir.y * ray_step;
        obstacle = is_osbtacle(frame, ray_pos.x, ray_pos.y);
        if (obstacle > 0) {
            corrected_dist = ray_length * cos(ray_angle - PLAYER->angle.x);
            draw_wall_cols(frame, v2f(corrected_dist, ray_angle),
                ray_pos, obstacle);
            return corrected_dist;
        }
        ray_length += ray_step;
    }
    return ray_length;
}

void cast_all_rays(frame_t *frame)
{
    float ray_angle = PLAYER->angle.x - (FOV / 2);
    float ray_step = FOV / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++) {
        frame->z_buffer[i] = cast_single_ray(ray_angle, frame);
        ray_angle += ray_step;
    }
}

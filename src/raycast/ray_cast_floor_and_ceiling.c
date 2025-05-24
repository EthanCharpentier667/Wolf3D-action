/*
** EPITECH PROJECT, 2025
** Wolf3D-action
** File description:
** rau_cast_floor_and_ceiling
*/

#include "frame.h"

static void init_raycasting_resources(frame_t *frame,
    sfSprite **floor_sprite, sfSprite **ceiling_sprite, float *ray_angles)
{
    static bool angles_computed = false;

    if (!*floor_sprite) {
        *floor_sprite = sfSprite_create();
        sfSprite_setTexture(*floor_sprite, MAP->floortexture, sfTrue);
    }
    if (!*ceiling_sprite) {
        *ceiling_sprite = sfSprite_create();
        sfSprite_setTexture(*ceiling_sprite, MAP->ceilingtexture, sfTrue);
    }
    if (!angles_computed) {
        for (int x = 0; x < WINDOWX; x++)
            ray_angles[x] = (x * FOV / WINDOWX) - (FOV / 2);
        angles_computed = true;
    }
}

static int calculate_strip_height(raycasting_data_t *data,
    bool is_floor, sfVector2f pos)
{
    int max_y = is_floor ?
        WINDOWY : (WINDOWY / 2 + data->vertical_offset);
    int current_strip_height = (pos.y + data->strip_height > max_y) ?
        (max_y - pos.y) : data->strip_height;

    return current_strip_height;
}

static ray_data_t calculate_ray_data(raycasting_data_t *data,
    strip_params_t strip)
{
    ray_data_t result;
    float screen_center = WINDOWY / 2 + data->vertical_offset;
    float ray_angle = data->player_angle + data->ray_angles[strip.x];
    float distance_factor = 0.0f;

    result.cos_angle = cosf(ray_angle);
    result.sin_angle = sinf(ray_angle);
    if (strip.is_floor)
        distance_factor = (WINDOWY * TILE_SIZE / 2.0f) /
            (strip.y - screen_center);
    else
        distance_factor = (WINDOWY * TILE_SIZE / 2.0f) /
            (screen_center - strip.y);
    result.distance = distance_factor / cosf(data->ray_angles[strip.x]);
    if (result.distance > MAX_RAY_LENGTH)
        result.distance = MAX_RAY_LENGTH;
    return result;
}

static world_pos_t calculate_world_position(raycasting_data_t *data,
    ray_data_t ray)
{
    world_pos_t pos = {0, 0};

    pos.world_x = data->player_pos.x + ray.cos_angle * ray.distance;
    pos.world_y = data->player_pos.y + ray.sin_angle * ray.distance;
    return pos;
}

static sfVector2i calculate_texture_coordinates(raycasting_data_t *data,
    world_pos_t pos)
{
    int tx = (int)(fmodf(pos.world_x, TILE_SIZE) *
        data->texture_size.x / TILE_SIZE);
    int ty = (int)(fmodf(pos.world_y, TILE_SIZE) *
        data->texture_size.y / TILE_SIZE);

    tx = (tx + data->texture_size.x) % data->texture_size.x;
    ty = (ty + data->texture_size.y) % data->texture_size.y;
    return (sfVector2i){tx, ty};
}

static void draw_sprite_strip(frame_t *frame, raycasting_data_t *data,
    sfVector2i tex_coords, strip_params_t strip)
{
    sfIntRect rect = {tex_coords.x, tex_coords.y,
        data->strip_width, strip.strip_height};
    ray_data_t ray = calculate_ray_data(data, strip);
    world_pos_t world_pos = calculate_world_position(data, ray);
    float light = get_light_intensity(frame, world_pos);
    sfColor light_color = sfColor_fromRGBA(
        255, 255, 255, (sfUint8)(255 * light));

    sfSprite_setColor(data->sprite, light_color);
    sfSprite_setTextureRect(data->sprite, rect);
    sfSprite_setPosition(data->sprite, v2f(strip.x, strip.y));
    sfRenderWindow_drawSprite(WINDOW, data->sprite, NULL);
}

static void draw_strip(frame_t *frame, raycasting_data_t *data,
    sfVector2i pos, bool is_floor)
{
    strip_params_t strip = {
        .x = pos.x,
        .y = pos.y,
        .is_floor = is_floor,
        .strip_height = calculate_strip_height(data,
            is_floor, v2f(pos.x, pos.y))
    };
    ray_data_t ray = calculate_ray_data(data, strip);
    world_pos_t world_pos = {0};
    sfVector2i tex_coords = {0};

    if (ray.distance > MAX_RAY_LENGTH)
        return;
    if (is_floor)
        frame->hori_buffer[strip.y] = ray.distance;
    world_pos = calculate_world_position(data, ray);
    tex_coords = calculate_texture_coordinates(data, world_pos);
    draw_sprite_strip(frame, data, tex_coords, strip);
}

static void draw_floor(frame_t *frame,
    sfSprite *floor_sprite, float *ray_angles)
{
    raycasting_data_t floor_data = {
        .texture = MAP->floortexture,
        .sprite = floor_sprite,
        .texture_size = sfTexture_getSize(frame->game->map->floortexture),
        .player_angle = PLAYER->angle.x,
        .player_pos = PLAYER->pos,
        .vertical_offset = (int)(WINDOWY * tanf(PLAYER->angle.y) / 2),
        .strip_height = 4,
        .strip_width = 4,
        .ray_angles = ray_angles
    };
    int start_y = WINDOWY / 2 + floor_data.vertical_offset;

    for (int y = start_y; y < WINDOWY; y += floor_data.strip_height)
        for (int x = 0; x < WINDOWX; x += floor_data.strip_width)
            draw_strip(frame, &floor_data, v2i(x, y), true);
}

static void draw_ceiling(frame_t *frame,
    sfSprite *ceiling_sprite, float *ray_angles)
{
    raycasting_data_t ceiling_data = {
        .texture = MAP->ceilingtexture,
        .sprite = ceiling_sprite,
        .texture_size = sfTexture_getSize(frame->game->map->ceilingtexture),
        .player_angle = PLAYER->angle.x,
        .player_pos = PLAYER->pos,
        .vertical_offset = (int)(WINDOWY * tanf(PLAYER->angle.y) / 2),
        .strip_height = 3,
        .strip_width = 3,
        .ray_angles = ray_angles
    };
    int end_y = WINDOWY / 2 + ceiling_data.vertical_offset;

    for (int y = 0; y < end_y; y += ceiling_data.strip_height)
        for (int x = 0; x < WINDOWX; x += ceiling_data.strip_width)
            draw_strip(frame, &ceiling_data, v2i(x, y), false);
}

void cast_floor_ceiling_rays(frame_t *frame)
{
    static float ray_angles[WINDOWX];
    static sfSprite *floor_sprite = NULL;
    static sfSprite *ceiling_sprite = NULL;

    init_raycasting_resources(frame, &floor_sprite,
        &ceiling_sprite, ray_angles);
    draw_floor(frame, floor_sprite, ray_angles);
    draw_ceiling(frame, ceiling_sprite, ray_angles);
}

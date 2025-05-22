/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** fixed_object
*/

#include "frame.h"

static float normalize_angle(float angle)
{
    while (angle < - M_PI)
        angle += 2 * M_PI;
    while (angle > M_PI)
        angle -= 2 * M_PI;
    return angle;
}

static int is_object_visible(frame_t *frame, fixed_object_t *object)
{
    float dx = object->position.x - PLAYER->pos.x;
    float dy = object->position.y - PLAYER->pos.y;
    float dist = sqrtf(dx * dx + dy * dy);
    float obj_angle = 0;
    float relative_angle = 0;

    if (dist < 0.001f)
        return 0;
    obj_angle = atan2f(dy, dx);
    relative_angle = normalize_angle(obj_angle - PLAYER->angle.x);
    return (fabs(relative_angle) <= FOV);
}

static render_context_t prepare_render_context(frame_t *frame,
    fixed_object_t *object)
{
    render_context_t ctx;
    float pitch_scale = WINDOWY / 2;

    ctx.object = object;
    ctx.obj_segments = WINDOWX * 2;
    ctx.segment_width = object->dimensions.x / (float)ctx.obj_segments;
    ctx.world_angle = object->angle;
    ctx.offset_x = object->offset * cosf(ctx.world_angle);
    ctx.offset_y = object->offset * sinf(ctx.world_angle);
    ctx.camera_pitch_offset = tanf(PLAYER->angle.y) * pitch_scale;
    return ctx;
}

static void calculate_segment_position(frame_t *frame, render_context_t *ctx,
    int segment_idx, segment_data_t *segment)
{
    float segment_pos = (segment_idx - ctx->obj_segments / 2)
        * ctx->segment_width * -1.0f;
    float seg_dx = 0;
    float seg_dy = 0;

    segment->x = ctx->object->position.x + ctx->offset_x +
        segment_pos * cosf(ctx->world_angle);
    segment->y = ctx->object->position.y + ctx->offset_y +
        segment_pos * sinf(ctx->world_angle);
    seg_dx = segment->x - PLAYER->pos.x;
    seg_dy = segment->y - PLAYER->pos.y;
    segment->dist = sqrtf(seg_dx * seg_dx + seg_dy * seg_dy);
    segment->angle = normalize_angle(atan2f(seg_dy, seg_dx) - PLAYER->angle.x);
    segment->corrected_dist = segment->dist * cosf(segment->angle);
}

static segment_data_t calculate_segment_data(frame_t *frame,
    render_context_t *ctx, int segment_idx)
{
    segment_data_t segment;
    float height_factor = 0;

    calculate_segment_position(frame, ctx, segment_idx, &segment);
    segment.screen_x = (int)((WINDOWX / 2) * (1 + segment.angle / (FOV / 2)));
    height_factor = WINDOWY / segment.corrected_dist;
    segment.height = ctx->object->dimensions.y * height_factor;
    segment.screen_y = (WINDOWY / 2) - (segment.height / 2) +
        (ctx->object->position.z * height_factor) + ctx->camera_pitch_offset;
    segment.light = get_light_intensity(frame,
        (world_pos_t){segment.x, segment.y});
    return segment;
}

static sfIntRect get_segment_rect(fixed_object_t *object,
    int segment_idx, int total_segments)
{
    float tex_pct = (float)segment_idx / total_segments;
    sfIntRect segment_rect = {
        .left = tex_pct * object->rec.width + object->rec.left,
        .top = 0,
        .width = object->rec.width / total_segments + 1,
        .height = object->rec.height
    };

    return segment_rect;
}

static sfSprite* create_segment_sprite(segment_data_t *segment,
    fixed_object_t *object, int segment_idx, int total_segments)
{
    sfSprite *sprite = sfSprite_create();
    sfIntRect segment_rect = get_segment_rect(object,
        segment_idx, total_segments);
    sfColor color = {segment->light * 255, segment->light * 255,
        segment->light * 255, 255};

    sfSprite_setTexture(sprite, object->texture, sfFalse);
    sfSprite_setTextureRect(sprite, segment_rect);
    sfSprite_setPosition(sprite, v2f(segment->screen_x, segment->screen_y));
    sfSprite_setScale(sprite, v2f(1.0f, segment->height / object->rec.height));
    sfSprite_setColor(sprite, color);
    return sprite;
}

static void render_segment(frame_t *frame, render_context_t *ctx,
    segment_data_t *segment, int segment_idx)
{
    sfSprite *sprite = NULL;

    if (segment->corrected_dist < 0.1f)
        return;
    if (segment->screen_x < 0 || segment->screen_x > WINDOWX)
        return;
    if (frame->z_buffer[segment->screen_x] < segment->corrected_dist)
        return;
    sprite = create_segment_sprite(segment, ctx->object,
        segment_idx, ctx->obj_segments);
    sfRenderWindow_drawSprite(WINDOW, sprite, NULL);
    sfSprite_destroy(sprite);
}

void render_fixed_object(frame_t *frame, fixed_object_t *object)
{
    render_context_t ctx;
    segment_data_t segment;

    if (!is_object_visible(frame, object))
        return;
    ctx = prepare_render_context(frame, object);
    for (int i = 0; i < ctx.obj_segments; i++) {
        segment = calculate_segment_data(frame, &ctx, i);
        render_segment(frame, &ctx, &segment, i);
    }
}

void draw_all_fixed_objects(frame_t *frame)
{
    fixed_object_t *object = NULL;

    for (int i = 0; i < NB_FIXED_OBJECTS; i++) {
        object = &frame->game->fixed_objects[i];
        render_fixed_object(frame, object);
    }
}

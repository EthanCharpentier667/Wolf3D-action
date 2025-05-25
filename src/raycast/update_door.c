/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** update_door
*/

#include "frame.h"

static sfVector2i get_player_facing_tile(frame_t *frame)
{
    sfVector2i front = {0, 0};
    float player_x = PLAYER->pos.x;
    float player_y = PLAYER->pos.y;
    float dir_x = cosf(PLAYER->angle.x);
    float dir_y = sinf(PLAYER->angle.x);
    float interaction_distance = 0.8f * TILE_SIZE;
    float target_x = player_x + dir_x * interaction_distance;
    float target_y = player_y + dir_y * interaction_distance;

    front.x = (int)(target_x / TILE_SIZE);
    front.y = (int)(target_y / TILE_SIZE);
    return front;
}

static fixed_object_t *find_door_at_position(frame_t *frame, int x, int y)
{
    fixed_object_t *object = NULL;
    int obj_x = 0;
    int obj_y = 0;

    for (int i = 0; i < NB_FIXED_OBJECTS; i++) {
        object = &frame->game->fixed_objects[i];
        obj_x = (int)(object->position.x / TILE_SIZE);
        obj_y = (int)(object->position.y / TILE_SIZE);
        if (obj_x == x && obj_y == y &&
            (object->solid == DOOR_CLOSED || object->solid == DOOR_OPEN))
            return object;
    }
    return NULL;
}

static void open_door(frame_t *frame, fixed_object_t *door)
{
    int map_x = 0;
    int map_y = 0;

    if (door) {
        door->solid = DOOR_OPENING;
        map_x = (int)(door->position.x / TILE_SIZE);
        map_y = (int)(door->position.y / TILE_SIZE);
        MAP2D[map_y][map_x] = -1;
    }
}

static void close_door(frame_t *frame, fixed_object_t *door)
{
    int map_x = 0;
    int map_y = 0;

    if (door) {
        door->solid = DOOR_CLOSING;
        map_x = (int)(door->position.x / TILE_SIZE);
        map_y = (int)(door->position.y / TILE_SIZE);
        MAP2D[map_y][map_x] = -1;
    }
}

void interact_with_door(frame_t *frame)
{
    sfVector2i front = get_player_facing_tile(frame);
    fixed_object_t *door = find_door_at_position(frame, front.x, front.y);

    if (front.x < 0 || front.x >= MAP_WIDTH
        || front.y < 0 || front.y >= MAP_HEIGHT)
        return;
    if (!door)
        return;
    sfClock_restart(frame->clock[4].clock);
    if (door->solid == DOOR_CLOSED) {
        if (use_item_key(frame))
            open_door(frame, door);
    } else if (door->solid == DOOR_OPEN) {
        close_door(frame, door);
    }
}

static void update_opening_door(frame_t *frame, fixed_object_t *door,
    float dt, float speed)
{
    int map_x = 0;
    int map_y = 0;

    door->offset += speed * dt;
    if (door->offset >= 1.0f) {
        door->offset = 1.0f;
        door->solid = DOOR_OPEN;
        map_x = (int)(door->position.x / TILE_SIZE);
        map_y = (int)(door->position.y / TILE_SIZE);
        MAP2D[map_y][map_x] = 0;
        vfx_unlock(frame, door->position);
    }
    door->rec.left = door->rec.width * door->offset;
}

static void update_closing_door(frame_t *frame, fixed_object_t *door,
    float dt, float speed)
{
    int map_x = 0;
    int map_y = 0;

    door->offset -= speed * dt;
    if (door->offset <= 0.0f) {
        door->offset = 0.0f;
        door->solid = DOOR_CLOSED;
        map_x = (int)(door->position.x / TILE_SIZE);
        map_y = (int)(door->position.y / TILE_SIZE);
        MAP2D[map_y][map_x] = -1;
    }
    door->rec.left = door->rec.width * door->offset;
}

static void update_single_door(frame_t *frame, fixed_object_t *door,
    float dt, float speed)
{
    switch (door->solid) {
        case DOOR_OPENING:
            update_opening_door(frame, door, dt, speed);
            break;
        case DOOR_CLOSING:
            update_closing_door(frame, door, dt, speed);
            break;
        default:
            break;
    }
}

void update_doors(frame_t *frame)
{
    const float door_speed = 0.01f;
    fixed_object_t *object = NULL;
    float dt = sfTime_asSeconds(sfClock_getElapsedTime(frame->clock[4].clock));

    for (int i = 0; i < NB_FIXED_OBJECTS; i++) {
        object = &frame->game->fixed_objects[i];
        if (object->solid == DOOR_OPENING || object->solid == DOOR_CLOSING) {
            update_single_door(frame, object, dt, door_speed);
        }
    }
}

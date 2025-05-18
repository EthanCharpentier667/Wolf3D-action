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
    int player_x = (int)(PLAYER->pos.x / TILE_SIZE);
    int player_y = (int)(PLAYER->pos.y / TILE_SIZE);
    float dir_x = cosf(PLAYER->angle.x);
    float dir_y = sinf(PLAYER->angle.x);

    front.x = player_x + (int)(dir_x * 1.5f);
    front.y = player_y + (int)(dir_y * 1.5f);
    return front;
}

static door_t *find_door_at_position(frame_t *frame, int x, int y)
{
    door_t *door = NULL;

    for (int i = 0; i < frame->game->doors->door_count; i++) {
        door = &frame->game->doors->doors[i];
        if (door->map_x == x && door->map_y == y)
            return door;
    }
    return NULL;
}

static void open_door(frame_t *frame, door_t *door)
{
    if (door) {
        door->state = DOOR_OPENING;
        MAP2D[door->map_y][door->map_x] = DOOR_OPENING;
    }
}

static void close_door(frame_t *frame, door_t *door)
{
    if (door) {
        door->state = DOOR_CLOSING;
        MAP2D[door->map_y][door->map_x] = DOOR_CLOSING;
    }
}

void interact_with_door(frame_t *frame)
{
    sfVector2i front = get_player_facing_tile(frame);
    int tile = MAP2D[front.y][front.x];
    door_t *door = find_door_at_position(frame, front.x, front.y);

    if (front.x < 0 || front.x >= MAP_WIDTH
        || front.y < 0 || front.y >= MAP_HEIGHT)
        return;
    if (!door)
        return;
    if (tile == DOOR_CLOSED || tile == DOOR_CLOSING) {
        open_door(frame, door);
    } else if (tile == DOOR_OPEN || tile == DOOR_OPENING) {
        close_door(frame, door);
    }
}

static void update_opening_door(frame_t *frame, door_t *door,
    float dt, float speed)
{
    door->offset += speed * dt;
    if (door->offset >= 1.0f) {
        door->offset = 1.0f;
        door->state = DOOR_OPEN;
        MAP2D[door->map_y][door->map_x] = DOOR_OPEN;
    }
}

static void update_closing_door(frame_t *frame, door_t *door,
    float dt, float speed)
{
    door->offset -= speed * dt;
    if (door->offset <= 0.0f) {
        door->offset = 0.0f;
        door->state = DOOR_CLOSED;
        MAP2D[door->map_y][door->map_x] = DOOR_CLOSED;
    }
}

static void update_single_door(frame_t *frame, door_t *door,
    float dt, float speed)
{
    switch (door->state) {
        case DOOR_OPENING:
            update_opening_door(frame, door, dt, speed);
            break;
        case DOOR_CLOSING:
            update_closing_door(frame, door, dt, speed);
            break;
        default:
            break;
    }
    sfClock_restart(door->anim_clock);
}

void update_doors(frame_t *frame)
{
    const float door_speed = 0.25f;
    door_t *door = NULL;
    float dt = 0.0f;

    for (int i = 0; i < frame->game->doors->door_count; i++) {
        door = &frame->game->doors->doors[i];
        dt = sfTime_asSeconds(sfClock_getElapsedTime(door->anim_clock));
        update_single_door(frame, door, dt, door_speed);
    }
}

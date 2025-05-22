/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game
*/

#include "frame.h"

static int compare_objects(const void *a, const void *b)
{
    const draw_object_t *obj_a = (const draw_object_t *)a;
    const draw_object_t *obj_b = (const draw_object_t *)b;

    if (obj_a->distance > obj_b->distance)
        return -1;
    if (obj_a->distance < obj_b->distance)
        return 1;
    return 0;
}

static void init_objects_array(frame_t *frame, draw_object_t **objects)
{
    int total = NBITEMS + NBENEMIES + NB_FIXED_OBJECTS;

    *objects = malloc(sizeof(draw_object_t) * total);
    if (*objects == NULL)
        return;
}

static int add_items_to_objects(frame_t *frame,
    draw_object_t *objects, int count)
{
    float dx = 0;
    float dy = 0;

    for (int i = 0; i < NBITEMS; i++) {
        dx = ITEM[i].pos.x - PLAYER->pos.x;
        dy = ITEM[i].pos.y - PLAYER->pos.y;
        objects[count].distance = sqrt(dx * dx + dy * dy);
        objects[count].type = ITEM_OBJ;
        objects[count].data.item.index = i;
        count++;
    }
    return count;
}

static int add_enemies_to_objects(frame_t *frame,
    draw_object_t *objects, int count)
{
    float dx = 0;
    float dy = 0;

    for (int i = 0; i < NBENEMIES; i++) {
        dx = ENEMY[i].pos.x - PLAYER->pos.x;
        dy = ENEMY[i].pos.y - PLAYER->pos.y;
        objects[count].distance = sqrt(dx * dx + dy * dy);
        objects[count].type = ENEMY_OBJ;
        objects[count].data.enemy.index = i;
        count++;
    }
    return count;
}

static int add_fixed_objects_to_objects(frame_t *frame,
    draw_object_t *objects, int count)
{
    float dx = 0;
    float dy = 0;

    for (int i = 0; i < NB_FIXED_OBJECTS; i++) {
        dx = FIXED_OBJECTS[i].position.x - PLAYER->pos.x;
        dy = FIXED_OBJECTS[i].position.y - PLAYER->pos.y;
        objects[count].distance = sqrt(dx * dx + dy * dy);
        objects[count].type = FIXED_OBJ;
        objects[count].data.fixed_object.index = i;
        count++;
    }
    return count;
}

static int calculate_distances(frame_t *frame, draw_object_t **objects)
{
    int count = 0;

    init_objects_array(frame, objects);
    if (*objects == NULL)
        return 0;
    count = add_items_to_objects(frame, *objects, count);
    count = add_enemies_to_objects(frame, *objects, count);
    count = add_fixed_objects_to_objects(frame, *objects, count);
    return count;
}

void draw_objects_by_distance(frame_t *frame)
{
    draw_object_t *objects = NULL;
    int count = calculate_distances(frame, &objects);

    if (count <= 0)
        return;
    qsort(objects, count, sizeof(draw_object_t), compare_objects);
    for (int i = 0; i < count; i++) {
        if (objects[i].type == ITEM_OBJ)
            draw_item(frame, &ITEM[objects[i].data.item.index]);
        if (objects[i].type == ENEMY_OBJ)
            draw_enemy(frame, objects[i].data.enemy.index);
        if (objects[i].type == FIXED_OBJ)
            render_fixed_object(frame,
                &FIXED_OBJECTS[objects[i].data.fixed_object.index]);
    }
    free(objects);
}

static void draw_pausemenu(frame_t *frame)
{
    if (!UI->pause)
        return;
    UI->pause_menu->resume->disabled = false;
    UI->pause_menu->quit->disabled = false;
    UI->pause_menu->settings->disabled = false;
    sfSprite_setColor(UI->pause_menu->background->sprite,
        sfColor_fromRGBA(0, 0, 0, 150));
    sfRenderWindow_drawSprite(WINDOW,
        UI->pause_menu->background->sprite, NULL);
    sfRenderWindow_drawSprite(WINDOW, UI->pause_menu->logo->sprite, NULL);
    sfRenderWindow_drawSprite(WINDOW, UI->pause_menu->resume->sprite, NULL);
    sfRenderWindow_drawSprite(WINDOW, UI->pause_menu->quit->sprite, NULL);
    sfRenderWindow_drawSprite(WINDOW, UI->pause_menu->settings->sprite, NULL);
}

int game(frame_t *frame)
{
    float delta_time = get_delta_time(&(frame->clock[2]));

    sfRenderWindow_clear(WINDOW, sfBlack);
    clear_light_map(frame);
    applied(frame->img);
    update_player(PLAYER, &(frame->clock[1]), frame);
    calculate_player_lighting(frame);
    update_weapon(frame, delta_time);
    cast_floor_ceiling_rays(frame);
    cast_all_rays(frame);
    draw_objects_by_distance(frame);
    draw_inventory(frame);
    update_enemies(frame);
    draw_hud(frame);
    update_doors(frame);
    draw_pausemenu(frame);
    return 0;
}

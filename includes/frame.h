/*
** EPITECH PROJECT, 2025
** bsmyworld
** File description:
** frame
*/

#ifndef FRAME_H_
    #define FRAME_H_

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdio.h>
    #include <SFML/Window.h>
    #include <stdlib.h>
    #include <math.h>
    #include <stdbool.h>
    #include <sys/stat.h>
    #include <string.h>
    #include <unistd.h>
    #include "button.h"
    #include "images.h"
    #include "texts.h"
    #include "sounds.h"
    #include "item.h"
    #include "enemies.h"

typedef struct {
    float dx;
    float dy;
    float distance;
    float angle_to_item;
    float rel_angle;
    int screen_x;
    float ceiling_height;
    sfVector2u tex_size;
    float projected_height;
    float scale_factor;
    float sprite_width;
    int sprite_height;
    int sprite_start_x;
    int sprite_end_x;
    float vertical_offset;
} item_render_data_t;

typedef struct text_s {
    sfFont *font;
    sfText *text;
} text_t;

typedef struct clocks_s {
    sfClock *clock;
    sfTime time;
} clocks_t;

typedef struct tile_s {
    sfVertexArray *tile;
    sfBool is_highlighted;
    sfVector2i coords;
    int depth;
} tile_t;

typedef struct img_s {
    sfTexture *texture;
    char *path;
    sfSprite *sprite;
    sfVector2f scale;
    sfVector2f pos;
    sfVector2f size;
    sfVector2f origin;
    sfIntRect rec;
    int frameCount;
    bool isrec;
} img_t;

typedef struct images_s {
    img_t *img;
    int nb_img;
} images_t;

typedef struct help_box_s {
    sfRectangleShape *box;
    sfText *text;
    sfFont *font;
} help_box_t;

typedef struct {
    sfTexture *texture[4];
    sfColor colors[4];
    sfSprite *sprite;
    sfVector2f scale;
    sfVector2f pos;
    help_box_t *help_box;
    int action;
    int type;
    bool hover;
    bool disabled;
    bool clicked;
} button_t;

typedef enum scenes {
    MAINMENU,
    GAME,
    END
} scenes_t;

typedef enum environment {
    FLOOR,
    CEILING,
    WALL,
    DOOR,
    WINDOW,
    ENEMY,
    PLAYER
} environment_t;

typedef struct sound_s {
    sfSoundBuffer *buffer;
    sfSound *sound;
} sound_t;

typedef struct musics_s {
    sfMusic *music;
} musics_t;

typedef struct ui_s {
    int scene;
    text_t *texts;
    sound_t *sounds;
    musics_t *musics;
    button_t *button;
    int nb_texts;
    int nb_musics;
    int nb_sounds;
    int nb_buttons;
    sfVector2f refactor;
} ui_t;

typedef struct {
    float world_x;
    float world_y;
} world_pos_t;

typedef struct {
    int x;
    int y;
    int strip_height;
    bool is_floor;
} strip_params_t;

typedef struct {
    float cos_angle;
    float sin_angle;
    float distance;
} ray_data_t;

typedef struct {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2u texture_size;
    float player_angle;
    sfVector2f player_pos;
    int vertical_offset;
    int strip_height;
    int strip_width;
    float *ray_angles;
} raycasting_data_t;

typedef struct map_s {
    int **map;
    int width;
    int height;
    sfTexture *floortexture;
    sfTexture *ceilingtexture;
    sfTexture *walltexture;
} map_t;

typedef struct player_s {
    sfVector2f pos;
    float size;
    sfVector2f fut_angle;
    sfVector2f angle;
    float speed;
    float turn_speed;
    float delta_time;
} player_t;

typedef struct item_s {
    sfVector3f pos;
    sfTexture *texture;
    sfVector2f scale;
    sfIntRect rec;
} item_t;

typedef struct enemy_s {
    sfVector3f pos;
    sfTexture *texture;
    sfVector2f scale;
    sfIntRect rec;
    float angle;
    float speed;
    bool is_moving;
    int life;
} enemy_t;

typedef struct game_s {
    player_t *player;
    map_t *map;
    item_t *items;
    enemy_t *enemies;
    int nb_items;
    int nb_enemies;
    int nb_enemies_alive;
    int level;
} game_t;

typedef struct frame_s {
    sfRenderWindow *window;
    sfVector2u window_size;
    sfVector2i center;
    sfEvent event;
    clocks_t *clock;
    sfView *view;
    int nb_clocks;
    images_t *img;
    ui_t *ui;
    game_t *game;
    sfVector2f mouse;
    sfVector2i real_mouse;
    float z_buffer[800];
} frame_t;

    #define FRAME frame

    #define WINDOWX 800
    #define WINDOWY 600
    #define WINDOW frame->window

    #define PLAYER frame->game->player
    #define TILE_SIZE 64
    #define MAX_RAY_LENGTH 400.0f
    #define MAP_WIDTH 8
    #define MAP_HEIGHT 8

extern const int map[MAP_HEIGHT][MAP_WIDTH];

    #define MAP frame->game->map
    #define MAP2D frame->game->map->map

    #define FOV (M_PI / 3)
    #define NUM_RAYS 800
    #define MOUSE_SENSITIVITY 0.0015
    #define MOUSE_SLIDE 16.5
    #define MAX_CAM_Y M_PI / 2

    #define CLOCK frame->clock
    #define NBCLKS frame->nb_clocks

    #define IMG images->img
    #define NB images->nb_img

    #define BUTTONS ui->button
    #define HELPBOX button->help_box
    #define BUTTON frame->ui->button
    #define NB_BUTTONS ui->nb_buttons

    #define SOUNDS frame->ui->sounds
    #define NB_SOUNDS frame->ui->nb_sounds

    #define TEXTS ui->texts
    #define NBTEXTS ui->nb_texts
    #define FONTPATH RES "contm.ttf"

    #define ITEM frame->game->items
    #define ENEMY frame->game->enemies
    #define NBITEMS frame->game->nb_items
    #define NBENEMIES frame->game->nb_enemies
    #define ENEMIESALIVE frame->game->nb_enemies_alive

    #define RES "src/assets/"

    #define UI frame->ui


//CREATION
int create_clock(frame_t *frame, int nb);
int create_obj(images_t *images, char *str,
    sfVector2f scale, sfVector2f pos);
int create_rec_obj(images_t *images, char *path,
    sfFloatRect scale_pos, sfIntRect rec);
int create_text(ui_t *ui, char *text,
    sfColor color, sfVector3f infos);
sfRenderWindow *create_window(int w, int h, char *name);
int create_textured_button(ui_t *ui, char *path[4],
    sfFloatRect infos, int action);
int create_basic_button(ui_t *ui, char *path,
    sfFloatRect infos, int action);
int create_helpboxed_button(ui_t *ui, char *path,
    sfFloatRect infos, int action);
void wrap_text(sfText *text, float max_width);
int create_sound(ui_t *ui, char *path);
int create_music(ui_t *ui, char *path);
void applied_button(ui_t *ui);
void applied(images_t *images);
int create_enemy(frame_t *frame, char *str, sfVector2f scale, sfVector3f pos);
int create_item(frame_t *frame, char *str, sfVector2f scale, sfVector3f pos);

//DRAW
int draw_all(frame_t *frame);

// INIT
int init_frame(frame_t *frame);
int init_ambiants(frame_t *frame);
int init_game(frame_t *frame);
int init_ui(frame_t *frame);
int init_player(frame_t *frame);
void destroy_all(frame_t *frame);

//UTILS
sfVector2i v2i(int x, int y);
sfVector2f v2f(float x, float y);
sfVector3f v3f(float x, float y, float z);
sfFloatRect frct(float left, float top, float width, float height);
sfIntRect irct(int left, int top, int width, int height);

//EVENTS
int handle_event(sfEvent *event, frame_t *frame);
void buttons_event(sfEvent *event, frame_t *frame);
void resize_event(frame_t *frame);

//BUTTONS
void disable_all_button(frame_t *frame);
void enable_button(frame_t *frame, int *button_indexes, int nb_buttons);

sfVector2f get_mouseposition(sfRenderWindow *window);

int scene_manager(frame_t *frame);
//SCENES
int mainmenu(frame_t *frame);
int game(frame_t *frame);

//RAYCAST
int is_osbtacle(int x, int y);
double view_angle(float angle);
void draw_floor_and_ceiling(frame_t *frame);
void cast_floor_ceiling_rays(frame_t *frame);
void render_wall_column(sfRenderWindow *window, int column,
    float wall_height, sfColor color);
void cast_all_rays(frame_t *frame);
void render_wall_column_textured(frame_t *frame, sfVector2f column_wall_height,
    sfVector2f hits, sfVector2i vertical);
void draw_item(frame_t *frame, sfVector3f itempos,
    sfTexture *item_texture, sfVector2f scale);
void draw_enemy(frame_t *frame, int index);

//PLAYER
void rotate_player(player_t *player, frame_t *frame);
void update_player(player_t *player, clocks_t *clock, frame_t *frame);
float get_delta_time(clocks_t *clock);

//MATH
float lerp(float a, float b, float mult);
float clamp(float value, float min, float max);

#endif /* !FRAME_H_ */

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
    #include "slider.h"
    #include "scene.h"
    #include "environnement.h"

    #define MAX_SAVES_DISPLAYED 6
    #define MAX_ITEMS 20

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
    MAINMENU = 1,
    GAME = 2,
    SETTINGS_AUDIO = 4,
    SETTINGS_CONTROLS = 8,
    SETTINGS_RESOLUTION = 16,
    LOADS = 32,
    END = 64
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

typedef struct slider_s {
    sfRectangleShape *bar;
    sfRectangleShape *fill;
    sfCircleShape *handle;
    sfVector2f pos;
    sfVector2f size;
    float min_value;
    float max_value;
    float current_value;
    bool dragging;
} slider_t;

typedef struct save_info_s {
    char filename[256];
    char imagepath[256];
    char name[64];
    char date[32];
    bool has_thumbnail;
    sfSprite *thumbnail;
} save_info_t;

typedef struct saves_s {
    button_t buttons[MAX_SAVES_DISPLAYED];
    text_t texts[MAX_SAVES_DISPLAYED];
    char *name[MAX_SAVES_DISPLAYED];
    int nb_saves;
} saves_t;

typedef struct ui_s {
    int scene;
    text_t *texts;
    sound_t *sounds;
    musics_t *musics;
    button_t *button;
    slider_t *sliders;
    int nb_sliders;
    int nb_texts;
    int nb_musics;
    int nb_sounds;
    int nb_buttons;
    sfVector2f refactor;
} ui_t;

typedef struct minimap_s {
    sfVector2f position;
    float size;
    float cell_size;
    sfRectangleShape *background;
    sfRectangleShape **walls;
    int nb_walls;
    sfCircleShape *player;
    sfConvexShape *direction;
} minimap_t;

typedef struct hud_s {
    img_t *life;
    text_t *life_text;
    minimap_t *minimap;
} hud_t;

typedef struct wall_render_params_s {
    sfVector2f column_wall_pos;
    sfVector2f hit_position;
    bool is_vertical;
    int vertical_offset;
    int ray_index;
    sfColor light_color;
} wall_render_params_t;

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
} map_t;

typedef struct draw_object_s {
    float distance;
    enum {
        ITEM_OBJ,
        ENEMY_OBJ
    } type;
    union {
        struct {
            int index;
        } item;
        struct {
            int index;
        } enemy;
    } data;
} draw_object_t;

typedef struct item_s {
    sfVector3f pos;
    sfTexture *texture;
    sfVector2f scale;
    sfIntRect rec;
    char *name;
    bool pickable;
    bool useable;
    int id;
    char *description;
} item_t;

typedef struct enemy_s {
    sfClock *clock;
    sfVector3f pos;
    sfTexture *texture;
    sfVector2f scale;
    sfVector2f direction;
    sfIntRect rec;
    float angle;
    float speed;
    float damages;
    float attack_range;
    bool is_moving;
    bool follow_player;
    bool is_attacking;
    bool is_dead;
    int life;
    int max_life;
} enemy_t;

typedef struct inventory_s {
    item_t items[MAX_ITEMS];
    button_t item_buttons[MAX_ITEMS];
    int item_coun[MAX_ITEMS];
    int nb_items;
    int selected_item;
    sfBool is_open;
    sfRectangleShape *bg;
    float padding;
    int grid_size;
    float cell_size;
    float gap;
    float inv_width;
    float inv_height;
    float pos_x;
    float pos_y;
    sfFont *font;
} inventory_t;

typedef struct door_s {
    int map_x;
    int map_y;
    float offset;
    int state;
    sfClock *anim_clock;
} door_t;

typedef struct doors_s {
    door_t *doors;
    int door_count;
} doors_t;

typedef struct player_s {
    sfVector2f pos;
    float size;
    sfVector2f fut_angle;
    sfVector2f angle;
    float speed;
    float turn_speed;
    float delta_time;
    unsigned int life;
    unsigned int max_life;
    inventory_t *inventory;
    bool flashlight_on;
    float flashlight_angle;
    float flashlight_range;
    float flashlight_width;
    float flashlight_intensity;
} player_t;

typedef struct environment_ray_s {
    sfTexture *texture;
    sfVector2f scale;
    sfVector2f pos;
    sfIntRect rec;
    int type;
    bool isrec;
    bool isanimated;
    bool isobstacle;
} environment_ray_t;

typedef struct game_s {
    player_t *player;
    map_t *map;
    item_t *items;
    enemy_t *enemies;
    saves_t *saves;
    hud_t *hud;
    environment_ray_t *environment;
    doors_t *doors;
    int nb_items;
    int nb_enemies;
    int nb_enemies_alive;
    int level;
    int nb_env;
} game_t;

    #define WINDOWX 800
    #define WINDOWY 600

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
    int **light_map;
    float z_buffer[WINDOWX];
} frame_t;

    #define FRAME frame

    #define DOOR_CLOSED 5
    #define DOOR_OPENING 6
    #define DOOR_OPEN 7
    #define DOOR_CLOSING 8

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
    #define NUM_RAYS WINDOWX
    #define MOUSE_SENSITIVITY 0.0015
    #define MOUSE_SLIDE 16.5
    #define MAX_CAM_Y M_PI / 2

    #define SLIDERS ui->sliders
    #define NB_SLIDERS ui->nb_sliders

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

    #define ENVIRONMENT frame->game->environment
    #define ENV_TEXTURE frame->game->environment[(int) prms.ray_index].texture
    #define DOORS frame->game->doors->doors

    #define INVENTORY frame->game->player->inventory

    #define RES "src/assets/"

    #define UI frame->ui

    #define HUD frame->game->hud
    #define QUART_LIFE (PLAYER->max_life / 4)
    #define MID_LIFE (PLAYER->max_life / 2)
    #define THREE_Q_LIFE (PLAYER->max_life * 3 / 4)
    #define MAX(a, b) ((a) > (b) ? (a) : (b))
    #define L_VW_X (map_p_x + dir_x * radius + dir_y * radius * 0.5f)
    #define L_VW_Y (map_p_y + dir_y * radius - dir_x * radius * 0.5f)
    #define R_VW_X (map_p_x + dir_x * radius - dir_y * radius * 0.5f)
    #define R_VW_Y (map_p_y + dir_y * radius + dir_x * radius * 0.5f)


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
int create_slider(ui_t *ui, sfVector2f pos,
    sfVector2f size, float initial_value);
int create_environment(frame_t *frame, char *str,
    sfIntRect rec, sfVector2f scale);

//DRAW
int draw_all(frame_t *frame);
int draw_images(frame_t *frame);

// INIT
int init_frame(frame_t *frame);
int init_ambiants(frame_t *frame);
int init_game(frame_t *frame);
int init_ui(frame_t *frame);
int init_player(frame_t *frame);
int init_minimap(frame_t *frame);
int init_doors(frame_t *frame);
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
void handle_slider_events(frame_t *frame, sfEvent *event);
void handle_button_inventory_event(frame_t *frame, sfEvent *event);

//BUTTONS
void disable_all_button(frame_t *frame);
void enable_button(frame_t *frame, int *button_indexes, int nb_buttons);

sfVector2f get_mouseposition(sfRenderWindow *window);

int scene_manager(frame_t *frame);
//SCENES
int mainmenu(frame_t *frame);
int game(frame_t *frame);
int settings(frame_t *frame);
int load_scene(frame_t *frame);

//RAYCAST
int is_osbtacle(frame_t *frame, int x, int y);
double view_angle(float angle);
void draw_floor_and_ceiling(frame_t *frame);
void cast_floor_ceiling_rays(frame_t *frame);
void render_wall_column(sfRenderWindow *window, int column,
    float wall_height, sfColor color);
void cast_all_rays(frame_t *frame);
void render_wall_column_textured(frame_t *frame, wall_render_params_t prms);

//FLASHLIGHT
int init_flashlight(frame_t *frame);
void clear_light_map(frame_t *frame);
void calculate_player_lighting(frame_t *frame);
float get_light_intensity(frame_t *frame, world_pos_t world_pos);
void destroy_flashlight(frame_t *frame);
void update_doors(frame_t *frame);
void interact_with_door(frame_t *frame);
void draw_all_doors(frame_t *frame);

//ITEMS
void draw_item(frame_t *frame, item_t *item);
void calculate_item_position(frame_t *frame, sfVector3f itempos,
    sfTexture *item_texture, item_render_data_t *data);
void calculate_item_dimensions(item_render_data_t *data,
    sfVector2f scale, player_t *player, sfVector3f itempos);
void render_item_columns(frame_t *frame, sfTexture *item_texture,
    item_render_data_t *data, sfVector2f scale);
void draw_3d_text(frame_t *frame, sfVector3f pos,
    char *text, sfVector2f scale);
//ENEMIES

void draw_enemy(frame_t *frame, int index);
void draw_health_bar_3d(frame_t *frame, int index,
    float enemyheight, sfVector2f bar_scale);
void follow_player(frame_t *frame, enemy_t *enemy);
void update_enemies(frame_t *frame);

//INVENTORY
int init_inventory(frame_t *frame);
void pick_item(frame_t *frame, item_t *item);
void draw_inventory(frame_t *frame);
void handle_inventory_event(frame_t *frame, sfEvent *event);
void draw_item_details(frame_t *frame, float pos_x, float pos_y);
void use_item(frame_t *frame, int item_index);
void drop_item(frame_t *frame, int item_index);
void draw_inventory_background(frame_t *frame);

void draw_hud(frame_t *frame);

//PLAYER
void rotate_player(player_t *player, frame_t *frame);
void update_player(player_t *player, clocks_t *clock, frame_t *frame);
float get_delta_time(clocks_t *clock);

//MATH
float lerp(float a, float b, float mult);
float clamp(float value, float min, float max);

//GAME
int loads_saved_games(frame_t *frame);
void free_save(saves_t *saves, frame_t *frame);

#endif /* !FRAME_H_ */

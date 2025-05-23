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
    #include <time.h>
    #include "button.h"
    #include "images.h"
    #include "texts.h"
    #include "sounds.h"
    #include "item.h"
    #include "enemies.h"
    #include "slider.h"
    #include "scene.h"
    #include "environnement.h"
    #include "weapon.h"
    #include "keyname.h"
    #include "fixed_object.h"
    #include "vfx.h"

    #define MAX_SAVES_DISPLAYED 6
    #define MAX_ITEMS 20
    #define CURRENT_WEAPON (HUD->weapon[HUD->selected_weapon])

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
    sfVector3f pos;
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
    PAUSE = 64,
    END = 128
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

typedef struct {
    int action;
    sfKeyCode *key_address;
} key_mapping_t;

typedef struct keybind_s {
    sfKeyCode up;
    sfKeyCode down;
    sfKeyCode left;
    sfKeyCode right;
    sfKeyCode interact;
    sfKeyCode shoot;
    sfKeyCode pause;
    sfKeyCode inventory;
} keybind_t;

typedef struct settings_s {
    float sound_volume;
    float music_volume;
    sfVector2u resolution;
    keybind_t *keybinds;
    int last_action;
    bool keybinding;
} settings_t;

typedef struct pause_menu_s {
    img_t *background;
    img_t *logo;
    button_t *resume;
    button_t *settings;
    button_t *quit;
} pause_menu_t;

typedef struct ui_s {
    int scene;
    int last_scene;
    text_t *texts;
    sound_t *sounds;
    musics_t *musics;
    button_t *button;
    pause_menu_t *pause_menu;
    slider_t *sliders;
    settings_t *settings;
    vfxs_infos_t vfx_infos;
    int nb_sliders;
    int nb_texts;
    int nb_musics;
    int nb_sounds;
    int nb_buttons;
    sfVector2f refactor;
    bool pause;
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

typedef enum weapon_state_e {
    WEAPON_IDLE,
    WEAPON_ATTACKING,
    WEAPON_COOLDOWN,
    WEAPON_WINDUP,
    WEAPON_FIRING,
    WEAPON_WINDDOWN
} weapon_state_t;

typedef struct weapon_s {
    sfTexture *texture;
    sfTexture *alt_texture;
    sfSprite *sprite;
    sfIntRect rec;
    sfVector2f scale;
    sfVector2f position;
    int total_frames;
    int alt_total_frames;
    int frame_width;
    int frame_height;
    char *name;
    float animation_timer;
    float attack_cooldown;
    float attack_range;
    float attack_width;
    int damage;
    weapon_state_t state;
    int current_frame;
    int ammo;
    int ammo_capacity;
    float fire_rate;
    float windup_timer;
    float windup_time;
    bool is_trigger_held;
    weapon_type_t type;
    void (*update_behavior)(struct weapon_s *, struct frame_s *, float);
} weapon_t;

typedef struct hud_s {
    img_t *life;
    text_t *life_text;
    minimap_t *minimap;
    weapon_t **weapon;
    int nb_weapons;
    int selected_weapon;
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
        ENEMY_OBJ,
        FIXED_OBJ
    } type;
    union {
        struct {
            int index;
        } item;
        struct {
            int index;
        } enemy;
        struct {
            int index;
        } fixed_object;
    } data;
} draw_object_t;

    #define MAXITEM_NAMELENGTH 256
    #define MAXITEM_DESCRIPTIONLENGTH 512

typedef struct item_s {
    sfVector3f pos;
    sfTexture *texture;
    sfVector2f scale;
    sfIntRect rec;
    char name[MAXITEM_NAMELENGTH];
    bool pickable;
    bool useable;
    int id;
    char description[MAXITEM_NAMELENGTH];
} item_t;

typedef struct enemy_s {
    sfClock *clock;
    sfVector3f pos;
    sfTexture *texture;
    sfVector2f scale;
    sfVector2f direction;
    sfIntRect rec;
    char *drop;
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
    sfClock *attack_cd_clock;
    float attack_cooldown;
    bool can_attack;
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

typedef struct fixed_object_s {
    sfVector3f position;
    float angle;
    sfTexture *texture;
    sfVector2f dimensions;
    int solid;
    sfIntRect rec;
    float offset;
} fixed_object_t;

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
    bool pause;
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
    fixed_object_t *fixed_objects;
    int nb_fixed_objects;
    int nb_items;
    int nb_enemies;
    int nb_enemies_alive;
    int level;
    int nb_env;
} game_t;

    #define WINDOWX 800
    #define WINDOWY 600

typedef struct game_infos_s {
    char name[128];
    char date[128];
} game_infos_t;

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
    sfImage *sceenshot;
    char *save;
    char *name;
    int **light_map;
    float z_buffer[WINDOWX];
    bool played;
} frame_t;

    #define FRAME frame

    #define DOOR_CLOSED 4
    #define DOOR_OPENING 2
    #define DOOR_OPEN 1
    #define DOOR_CLOSING 3
    #define WINDOW_CLOSED 5

    #define WINDOW frame->window

    #define PLAYER frame->game->player
    #define TILE_SIZE 64
    #define MAX_RAY_LENGTH 1500.0f
    #define MAP_WIDTH 16
    #define MAP_HEIGHT 16

extern const int map[MAP_HEIGHT][MAP_WIDTH];

    #define MAP frame->game->map
    #define MAP2D frame->game->map->map

    #define FOV (M_PI / 3)
    #define NUM_RAYS WINDOWX
    #define MOUSE_SENSITIVITY 0.0008
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
    #define FIXED_OBJECTS frame->game->fixed_objects
    #define NB_FIXED_OBJECTS frame->game->nb_fixed_objects

    #define INVENTORY frame->game->player->inventory

    #define RES "src/assets/"

    #define UI frame->ui

    #define KEYBIND frame->ui->settings->keybinds

    #define HUD frame->game->hud
    #define QUART_LIFE (PLAYER->max_life / 4)
    #define MID_LIFE (PLAYER->max_life / 2)
    #define THREE_Q_LIFE (PLAYER->max_life * 3 / 4)
    #define MAX(a, b) ((a) > (b) ? (a) : (b))
    #define L_VW_X (map_p_x + dir_x * radius + dir_y * radius * 0.5f)
    #define L_VW_Y (map_p_y + dir_y * radius - dir_x * radius * 0.5f)
    #define R_VW_X (map_p_x + dir_x * radius - dir_y * radius * 0.5f)
    #define R_VW_Y (map_p_y + dir_y * radius + dir_x * radius * 0.5f)

    #define SPRINT_MOD 1.8f


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
int create_hud(frame_t *frame);
bool create_fixed_object(frame_t *frame, sfVector3f pos,
    float angle, char *path);

//DRAW
int draw_all(frame_t *frame);
int draw_images(frame_t *frame);

// INIT
bool init_frame(frame_t *frame);
bool init_ambiants(frame_t *frame);
bool init_game(frame_t *frame);
bool init_ui(frame_t *frame);
bool init_player(frame_t *frame);
bool init_minimap(frame_t *frame);
bool init_objects(frame_t *frame);
bool init_settings(frame_t *frame);
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
void change_scene(frame_t *frame, int scene);
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
bool init_flashlight(frame_t *frame);
void clear_light_map(frame_t *frame);
void calculate_player_lighting(frame_t *frame);
float get_light_intensity(frame_t *frame, world_pos_t world_pos);
void destroy_flashlight(frame_t *frame);
void update_doors(frame_t *frame);
void interact_with_door(frame_t *frame);
void set_light_color(frame_t *frame, sfSprite *sprite,
    item_render_data_t *data);

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

//OBJECT - NON BILLBOARD

void render_fixed_object(frame_t *frame, fixed_object_t *object);
void draw_all_fixed_objects(frame_t *frame);

//ENEMIES
void draw_enemy(frame_t *frame, int index);
void draw_health_bar_3d(frame_t *frame, int index,
    float enemyheight, sfVector2f bar_scale);
void follow_player(frame_t *frame, enemy_t *enemy);
void update_enemies(frame_t *frame);

//INVENTORY
bool init_inventory(frame_t *frame);
void pick_item(frame_t *frame, item_t *item);
void draw_inventory(frame_t *frame);
void handle_inventory_event(frame_t *frame, sfEvent *event);
void draw_item_details(frame_t *frame, float pos_x, float pos_y);
void use_item(frame_t *frame, int item_index);
void drop_item(frame_t *frame, int item_index);
void draw_inventory_background(frame_t *frame);
bool use_item_key(frame_t *frame);
int get_item_index(char *name);
void drop_item_at_pos(frame_t *frame, int item_index, sfVector2f pos);
int add_ammo(frame_t *frame, int ammo);
int add_life(frame_t *frame, int life);
void delete_used_item(frame_t *frame, int item_index);

//HUD
void draw_hud(frame_t *frame);

//PLAYER
void rotate_player(player_t *player, frame_t *frame);
void update_player(player_t *player, clocks_t *clock, frame_t *frame);
float get_delta_time(clocks_t *clock);
void damage_player(frame_t *frame, enemy_t *enemy, int damage);

//MATH
float lerp(float a, float b, float mult);
float clamp(float value, float min, float max);
float rand_range(float min, float max);

//GAME
bool load_frame(frame_t *frame, char *save);
int loads_saved_games(frame_t *frame);
void free_save(saves_t *saves, frame_t *frame);

//KEYBINDS
sfKeyCode *get_button_keycode(frame_t *frame, int action);
const char *get_key_name(sfKeyCode key_code);

//LOAD
bool load_map_data(frame_t *frame, FILE *file);
bool load_inventory_data(frame_t *frame, FILE *file);
bool load_objects_data(frame_t *frame, FILE *file);
bool load_items_data(frame_t *frame, FILE *file);
bool load_enemies_data(frame_t *frame, FILE *file);

#endif /* !FRAME_H_ */

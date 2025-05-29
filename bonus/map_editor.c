/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** test
*/

/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** Map Editor
*/

#include "frame.h"
#include <float.h> 

#define GRID_SIZE 32
#define CELL_SIZE 20
#define PALETTE_WIDTH 300
#define WINDOW_WIDTH (GRID_SIZE * CELL_SIZE + PALETTE_WIDTH)
#define WINDOW_HEIGHT (GRID_SIZE * CELL_SIZE)

typedef struct palette_item_s {
    int type;
    int subtype;
    sfColor color;
    char name[64];
    sfTexture* texture;
    sfSprite* sprite;
} palette_item_t;

typedef struct editor_s {
    sfRenderWindow* window;
    int map[GRID_SIZE][GRID_SIZE];
    int selected_type;
    int selected_subtype;
    palette_item_t* palette;
    int palette_count;
    int current_page;
    int pages;
    sfFont* font;
    char map_name[64];
    int drag_active;
    sfVector2i last_cell;
    int selected_cell_x;
    int selected_cell_y;
} editor_t;

const struct enemy_infos_s ENEMY_INFOS[] = {
    {"../" RES "enemy_blu.png", {2.5, 2.5}, {320, 384, -0.90},
        {0, 0, 65, 65}, 1, 100, 250, 500, 10, 1, NULL, BASICBLUE, LEVEL0},
    {"../" RES "enemy2.png", {2.5, 2.5}, {640 + 32, 832 + 32, -0.90},
        {0, 0, 65, 65}, 1, 150, 250, 500, 10, 1, NULL, BASIC, LEVEL0},
    {"../" RES "enemy_white.png", {2.5, 2.5}, {896 + 32, 64 + 32, -0.90},
        {0, 0, 65, 65}, 1, 100, 250, 500, 12, 1, NULL, BASIC, LEVEL0},
    {"../" RES "enemy.png", {2.5, 2.5}, {1792 + 32, 1408 + 32, -0.90},
        {0, 0, 65, 65}, 1, 100, 150, 500, 10, 1, NULL, BASIC, LEVEL0},
    {"../" RES "Hitler1.png", {2.5, 2.5}, {256 + 32, 1088 + 32, -0.90},
        {0, 0, 74, 72}, 1.5, 400, 150, 700, 20, 0.5f, NULL, HITLER, LEVEL0},
    {"../" RES "matthieu.png", {1.5, 1.5}, {320, 384, -0.85},
        {0, 0, 134, 154}, 2, 100, 40, 500, 20, 1, NULL, WOLF, LEVEL0},
    {NULL, {0, 0}, {0, 0, 0}, {-1, -1, -1, -1}, 0, 0, 0, 0, 0, 0, NULL, 0, -1}
};

const struct env_infos_s ENVIRONNEMENT_INFOS[] = {
    {"../" RES "wall.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 1},
    {"../" RES "wall2.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 2},
    {"../" RES "wall3.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 3},
    {"../" RES "wall4.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 4},
    {"../" RES "wall_blue.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 5},
    {"../" RES "wall_blue_door.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 6},
    {"../" RES "wall_blue_skull.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 7},
    {"../" RES "wall_blue_temple.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 8},
    {"../" RES "wall_sand.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 9},
    {"../" RES "wall_sand_blood.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 10},
    {"../" RES "wall_sand_cobble.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 11},
    {"../" RES "wall_wood.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 12},
    {"../" RES "wall_wood2.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 13},
    {"../" RES "wall_wood3.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 14},
    {"../" RES "wall_wood4.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 15},
    {"../" RES "wall_metal.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 16},
    {"../" RES "wall_metal2.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 17},
    {"../" RES "wall_mossy.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 18},
    {"../" RES "wall_mossy2.png", {0, 0, 0, 0}, {1, 1}, false, false, true, 19},
    {NULL, {0, 0, 0, 0}, {0, 0}, false, false, false, 0}
};

const struct fixed_object_infos_s FIXED_OBJECT_INFOS[] = {
    {"../" RES "door2.png", {192 + 32, 96, 0}, M_PI / 2,
        {64, 64}, DOOR_CLOSED, {0, 0, 128, 128}, LEVEL0},
    {"../" RES "door.png", {256 + 32, 1792 + 32, 0}, M_PI * 2,
        {64, 64}, DOOR_CLOSED, {0, 0, 128, 128}, LEVEL0},
    {NULL, {0, 0, 0.1}, 0, {0, 0}, 0, {0, 0, 0, 0}, LEVEL0}
};

const struct item_infos_s ITEM_INFOS[] = {
    {"../" RES "pillar.png", {1, 1}, {224, 288, 0},
        {-1, -1, -1, -1}, "Pillar", false, false, "pillar", LEVEL0},
    {"../" RES "barrel.png", {0.5, 0.5}, {1584, 192, -0.5},
        {-1, -1, -1, -1}, "Barrel", false, false, "barrel", LEVEL0},
    {"../" RES "armor.png", {1, 1}, {1376, 480, 0},
        {-1, -1, -1, -1}, "Armor", false, false, "armor", LEVEL0},
    {"../" RES "key.png", {0.5, 0.5}, {164, 96, -0.50},
        {-1, -1, -1, -1}, "Key", true, false, "The Key Of The Door", LEVEL0},
    {"../" RES "ammo_box.png", { 0.5, 0.5}, { 64 + 32, 450 + 32, -0.50},
        {-1, -1, -1, -1}, "Ammo_box", true, true,
        "Take your weapon in hand\nand use it for 40 ammo", LEVEL0},
    {"../" RES "heal.png", {0.8, 0.8}, {64 + 32, 192 + 32, -0.50},
        {-1, -1, -1, -1}, "Heal", true, true, "Heal of 20 HP", LEVEL0},
    {"../" RES "lamp.png", {0.7, 0.7}, {250, 250, 0.1},
        {-1, -1, -1, -1}, "lamp", false, false, "", LEVEL0},
    {NULL,  {0, 0}, {0, 0, 0}, {-1, -1, -1, -1}, "", false, false, "", LEVEL0}
};

void initialize_editor(editor_t* editor);
void initialize_palette(editor_t* editor);
void process_events(editor_t* editor);
void update(editor_t* editor);
void render(editor_t* editor);
void save_map(editor_t* editor);
void clean_up(editor_t* editor);
void draw_grid(editor_t* editor);
void draw_palette(editor_t* editor);
void draw_map_cells(editor_t* editor);
void handle_click(editor_t* editor, sfMouseButtonEvent event);
void handle_drag(editor_t* editor, sfMouseMoveEvent event);
void select_palette_item(editor_t* editor, sfMouseButtonEvent event);
void clear_map(editor_t* editor);
void add_border_walls(editor_t* editor);
void load_map(editor_t* editor, const char* filename);

static int is_entering_filename = 0;

int main(void)
{
    editor_t editor;
    
    initialize_editor(&editor);
    initialize_palette(&editor);
    while (sfRenderWindow_isOpen(editor.window)) {
        process_events(&editor);
        update(&editor);
        if (!is_entering_filename) {
            render(&editor);
        }
    }
    clean_up(&editor);
    return 0;
}

void load_map(editor_t* editor, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file for reading: %s\n", filename);
        return;
    }
    clear_map(editor);
    char map_name[64] = {0};
    const char* last_slash = strrchr(filename, '/');
    if (last_slash) {
        strncpy(map_name, last_slash + 1, sizeof(map_name) - 1);
    } else {
        strncpy(map_name, filename, sizeof(map_name) - 1);
    }
    char* dot = strrchr(map_name, '.');
    if (dot) {
        *dot = '\0';
    }
    strncpy(editor->map_name, map_name, sizeof(editor->map_name) - 1);
    int width, height;
    if (fscanf(file, "%dx%d\n", &width, &height) != 2) {
        printf("Error: Invalid map format\n");
        fclose(file);
        return;
    }
    for (int y = 0; y < GRID_SIZE && y < height; y++) {
        for (int x = 0; x < GRID_SIZE && x < width; x++) {
            int value;
            if (fscanf(file, "%d", &value) == 1) {
                if (value > 0) {
                    editor->map[y][x] = 1 * 1000 + value;
                }
                char c = fgetc(file);
                while (c != ',' && c != '\n' && c != EOF) {
                    c = fgetc(file);
                }
            }
        }
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) <= 1 || line[0] == '#') {
            continue;
        }
        if (strstr(line, "Door positions") != NULL) {
            while (fgets(line, sizeof(line), file)) {
                if (strlen(line) <= 1 || line[0] == '#') {
                    break;
                }
                int x, y;
                float angle;
                if (sscanf(line, "%d,%d,%f", &x, &y, &angle) == 3) {
                    int grid_x = x / TILE_SIZE;
                    int grid_y = y / TILE_SIZE;
                    for (int i = 0; FIXED_OBJECT_INFOS[i].path != NULL; i++) {
                        if (FIXED_OBJECT_INFOS[i].solid == DOOR_CLOSED) {
                            if (fabs(FIXED_OBJECT_INFOS[i].angle - angle) < 0.1) {
                                editor->map[grid_y][grid_x] = 3 * 1000 + i;
                                break;
                            }
                        }
                    }
                }
            }
        }
        else if (strstr(line, "Enemy positions") != NULL) {
            printf("Found enemy positions section\n");
            while (fgets(line, sizeof(line), file)) {
                if (strlen(line) <= 1 || line[0] == '#') {
                    break;
                }
                
                int x, y, type;
                if (sscanf(line, "%d,%d,%d", &x, &y, &type) == 3) {
                    int grid_x = x / TILE_SIZE;
                    int grid_y = y / TILE_SIZE;
                    editor->map[grid_y][grid_x] = 2 * 1000 + type;
                }
            }
        }
        else if (strstr(line, "Object positions") != NULL) {
            while (fgets(line, sizeof(line), file)) {
                if (strlen(line) <= 1 || line[0] == '#') {
                    break;
                }
                
                int x, y, type;
                if (sscanf(line, "%d,%d,%d", &x, &y, &type) == 3) {
                    int grid_x = x / TILE_SIZE;
                    int grid_y = y / TILE_SIZE;
                    editor->map[grid_y][grid_x] = 4 * 1000 + type;
                }
            }
        }
        else if (strstr(line, "Item positions") != NULL) {
            while (fgets(line, sizeof(line), file)) {
                if (strlen(line) <= 1 || line[0] == '#') {
                    break;
                }
                int x, y, type;
                if (sscanf(line, "%d,%d,%d", &x, &y, &type) == 3) {
                    int grid_x = x / TILE_SIZE;
                    int grid_y = y / TILE_SIZE;
                    editor->map[grid_y][grid_x] = 5 * 1000 + type;
                }
            }
        }
    }
    fclose(file);
    printf("Map loaded from %s\n", filename);
}


void add_border_walls(editor_t* editor)
{
    int wall_type = 1 * 1000 + 1;
    
    for (int x = 0; x < GRID_SIZE; x++) {
        editor->map[0][x] = wall_type;
        editor->map[GRID_SIZE - 1][x] = wall_type;
    }
    for (int y = 1; y < GRID_SIZE - 1; y++) {
        editor->map[y][0] = wall_type;
        editor->map[y][GRID_SIZE - 1] = wall_type;
    }
}

void initialize_editor(editor_t* editor)
{
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    editor->window = sfRenderWindow_create(mode, "Wolf3D Map Editor", sfClose, NULL);
    
    editor->font = sfFont_createFromFile("../src/assets/contm.ttf");
    if (!editor->font) {
        printf("Could not load font\n");
        exit(1);
    }
    
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            editor->map[y][x] = 0;
        }
    }
    
    editor->selected_type = 1;
    editor->selected_subtype = 1;
    editor->current_page = 0;
    editor->drag_active = 0;
    editor->selected_cell_x = -1;
    editor->selected_cell_y = -1;
    strcpy(editor->map_name, "level");
}

void initialize_palette(editor_t* editor)
{
    int wall_count = 0;
    int enemy_count = 0;
    int object_count = 0;
    int door_count = 0;
    int item_count = 0;

    for (int i = 0; ENVIRONNEMENT_INFOS[i].texture != NULL; i++) {
        if (ENVIRONNEMENT_INFOS[i].isobstacle)
            wall_count++;
    }

    for (int i = 0; ENEMY_INFOS[i].path != NULL; i++) {
        enemy_count++;
    }

    for (int i = 0; FIXED_OBJECT_INFOS[i].path != NULL; i++) {
        if (FIXED_OBJECT_INFOS[i].solid == DOOR_CLOSED)
            door_count++;
        else
            object_count++;
    }

    for (int i = 0; ITEM_INFOS[i].path != NULL; i++) {
        item_count++;
    }

    int total_items = wall_count + enemy_count + object_count + door_count + item_count;
    editor->palette = malloc(sizeof(palette_item_t) * total_items);
    editor->palette_count = total_items;
    const int items_per_page = (WINDOW_HEIGHT - 100) / 40;
    editor->pages = (total_items + items_per_page - 1) / items_per_page;
    int index = 0;
    
    for (int i = 0; ENVIRONNEMENT_INFOS[i].texture != NULL; i++) {
        if (ENVIRONNEMENT_INFOS[i].isobstacle) {
            editor->palette[index].type = 1;
            editor->palette[index].subtype = ENVIRONNEMENT_INFOS[i].type;
            editor->palette[index].color = sfColor_fromRGB(120, 120, 120);
            sprintf(editor->palette[index].name, "Wall %d", ENVIRONNEMENT_INFOS[i].type);
            editor->palette[index].texture = sfTexture_createFromFile(ENVIRONNEMENT_INFOS[i].texture, NULL);
            editor->palette[index].sprite = sfSprite_create();
            sfSprite_setTexture(editor->palette[index].sprite, editor->palette[index].texture, sfTrue);
            
            index++;
        }
    }
    
    for (int i = 0; ENEMY_INFOS[i].path != NULL; i++) {
        editor->palette[index].type = 2;
        editor->palette[index].subtype = i+1;
        editor->palette[index].color = sfRed;
        sprintf(editor->palette[index].name, "Enemy %d", i+1);
        
        editor->palette[index].texture = sfTexture_createFromFile(ENEMY_INFOS[i].path, NULL);
        editor->palette[index].sprite = sfSprite_create();
        if (editor->palette[index].texture) {
            sfSprite_setTexture(editor->palette[index].sprite, editor->palette[index].texture, sfTrue);
            if (ENEMY_INFOS[i].rec.width > 0 && ENEMY_INFOS[i].rec.height > 0) {
                sfSprite_setTextureRect(editor->palette[index].sprite, ENEMY_INFOS[i].rec);
            }
        }
        index++;
    }
    
   for (int i = 0; FIXED_OBJECT_INFOS[i].path != NULL; i++) {
        if (FIXED_OBJECT_INFOS[i].solid == DOOR_CLOSED) {
            editor->palette[index].type = 3;
            editor->palette[index].subtype = i;
            editor->palette[index].color = sfColor_fromRGB(139, 69, 19);
            sprintf(editor->palette[index].name, "Door %d", i);
            
            editor->palette[index].texture = sfTexture_createFromFile(FIXED_OBJECT_INFOS[i].path, NULL);
            editor->palette[index].sprite = sfSprite_create();
            if (editor->palette[index].texture) {
                sfSprite_setTexture(editor->palette[index].sprite, editor->palette[index].texture, sfTrue);
                if (FIXED_OBJECT_INFOS[i].rec.width > 0 && FIXED_OBJECT_INFOS[i].rec.height > 0) {
                    sfSprite_setTextureRect(editor->palette[index].sprite, FIXED_OBJECT_INFOS[i].rec);
                }
            }
            index++;
        }
    }
    
    for (int i = 0; FIXED_OBJECT_INFOS[i].path != NULL; i++) {
        if (FIXED_OBJECT_INFOS[i].solid != DOOR_CLOSED) {
            editor->palette[index].type = 4;
            editor->palette[index].subtype = i;
            editor->palette[index].color = sfBlue;
            sprintf(editor->palette[index].name, "Object %d", i);
            index++;
        }
    }
    
    for (int i = 0; ITEM_INFOS[i].path != NULL; i++) {
        editor->palette[index].type = 5;
        editor->palette[index].subtype = i;
        editor->palette[index].color = sfGreen;
        sprintf(editor->palette[index].name, "Item %s", ITEM_INFOS[i].name);
        editor->palette[index].texture = sfTexture_createFromFile(ITEM_INFOS[i].path, NULL);
        editor->palette[index].sprite = sfSprite_create();
        if (editor->palette[index].texture) {
            sfSprite_setTexture(editor->palette[index].sprite, editor->palette[index].texture, sfTrue);
            if (ITEM_INFOS[i].rec.width > 0 && ITEM_INFOS[i].rec.height > 0) {
                sfSprite_setTextureRect(editor->palette[index].sprite, ITEM_INFOS[i].rec);
            }
        }
        index++;
    }
}

void process_events(editor_t* editor)
{
    sfEvent event;
    static char load_filename[128] = {0};
    
    while (sfRenderWindow_pollEvent(editor->window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(editor->window);
        } else if (is_entering_filename) {
            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyEscape) {
                    is_entering_filename = 0;
                    load_filename[0] = '\0';
                } else if (event.key.code == sfKeyReturn) {
                    is_entering_filename = 0;
                    load_map(editor, load_filename);
                } else if (event.key.code == sfKeyBackspace) {
                    int len = strlen(load_filename);
                    if (len > 0) {
                        load_filename[len-1] = '\0';
                    }
                }
            } else if (event.type == sfEvtTextEntered) {
                if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\n') {
                    unsigned long len = strlen(load_filename);
                    if (len < sizeof(load_filename) - 1 && event.text.unicode != '\b') {
                        load_filename[len] = event.text.unicode;
                        load_filename[len+1] = '\0';
                    }
                }
            } } else if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyS && event.key.control) {
                save_map(editor);
            } else if (event.key.code == sfKeyL && event.key.control) {
                is_entering_filename = 1;
                load_filename[0] = '\0';
            } else if (event.key.code == sfKeyC && event.key.control) {
                clear_map(editor);
            } else if (event.key.code == sfKeyB && event.key.control) {
                add_border_walls(editor);
            } else if (event.key.code == sfKeyUp) {
                editor->current_page = (editor->current_page + 1) % editor->pages;
            } else if (event.key.code == sfKeyDown) {
                editor->current_page = (editor->current_page - 1 + editor->pages) % editor->pages;
            }
        } else if (event.type == sfEvtMouseButtonPressed) {
            if (event.mouseButton.x < GRID_SIZE * CELL_SIZE) {
                int x = event.mouseButton.x / CELL_SIZE;
                int y = event.mouseButton.y / CELL_SIZE;
                
                editor->selected_cell_x = x;
                editor->selected_cell_y = y;
                
                handle_click(editor, event.mouseButton);
                editor->drag_active = 1;
                editor->last_cell.x = x;
                editor->last_cell.y = y;
            } else {
                editor->selected_cell_x = -1;
                editor->selected_cell_y = -1;
                select_palette_item(editor, event.mouseButton);
            }
        } else if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyS && event.key.control) {
                save_map(editor);
            } else if (event.key.code == sfKeyL && event.key.control) {
                is_entering_filename = 1;
                load_filename[0] = '\0';
            } else if (event.key.code == sfKeyC && event.key.control) {
                clear_map(editor);
            } else if (event.key.code == sfKeyB && event.key.control) {
                add_border_walls(editor);
            } else if (event.key.code == sfKeyUp) {
                editor->current_page = (editor->current_page + 1) % editor->pages;
            } else if (event.key.code == sfKeyDown) {
                editor->current_page = (editor->current_page - 1 + editor->pages) % editor->pages;
            }
        } else if (event.type == sfEvtMouseButtonPressed) {
            if (event.mouseButton.x < GRID_SIZE * CELL_SIZE) {
                handle_click(editor, event.mouseButton);
                editor->drag_active = 1;
                editor->last_cell.x = event.mouseButton.x / CELL_SIZE;
                editor->last_cell.y = event.mouseButton.y / CELL_SIZE;
            } else {
                select_palette_item(editor, event.mouseButton);
            }
        }
        else if (event.type == sfEvtMouseButtonReleased) {
            editor->drag_active = 0;
        }
        else if (event.type == sfEvtMouseMoved && editor->drag_active) {
            handle_drag(editor, event.mouseMove);
        }
    }
    if (is_entering_filename) {
        sfRectangleShape* overlay = sfRectangleShape_create();
        sfRectangleShape_setSize(overlay, (sfVector2f){WINDOW_WIDTH, WINDOW_HEIGHT});
        sfRectangleShape_setPosition(overlay, (sfVector2f){0, 0});
        sfRectangleShape_setFillColor(overlay, sfColor_fromRGBA(0, 0, 0, 180));
        sfRenderWindow_drawRectangleShape(editor->window, overlay, NULL);
        sfRectangleShape_destroy(overlay);
        
        // Afficher la boîte de dialogue
        sfRectangleShape* dialog = sfRectangleShape_create();
        sfRectangleShape_setSize(dialog, (sfVector2f){400, 100});
        sfRectangleShape_setPosition(dialog, (sfVector2f){(WINDOW_WIDTH - 400) / 2, (WINDOW_HEIGHT - 100) / 2});
        sfRectangleShape_setFillColor(dialog, sfColor_fromRGB(50, 50, 50));
        sfRectangleShape_setOutlineThickness(dialog, 2);
        sfRectangleShape_setOutlineColor(dialog, sfWhite);
        sfRenderWindow_drawRectangleShape(editor->window, dialog, NULL);
        sfRectangleShape_destroy(dialog);
        
        // Afficher le texte d'invite
        sfText* prompt = sfText_create();
        sfText_setFont(prompt, editor->font);
        sfText_setString(prompt, "Enter file name to load:");
        sfText_setCharacterSize(prompt, 16);
        sfText_setPosition(prompt, (sfVector2f){(WINDOW_WIDTH - 380) / 2, (WINDOW_HEIGHT - 80) / 2});
        sfText_setColor(prompt, sfWhite);
        sfRenderWindow_drawText(editor->window, prompt, NULL);
        sfText_destroy(prompt);
        
        // Afficher le nom de fichier saisi
        sfText* filename_text = sfText_create();
        sfText_setFont(filename_text, editor->font);
        sfText_setString(filename_text, load_filename);
        sfText_setCharacterSize(filename_text, 16);
        sfText_setPosition(filename_text, (sfVector2f){(WINDOW_WIDTH - 380) / 2, (WINDOW_HEIGHT - 40) / 2});
        sfText_setColor(filename_text, sfYellow);
        sfRenderWindow_drawText(editor->window, filename_text, NULL);
        sfText_destroy(filename_text);
        
        // Instructions
        sfText* instructions = sfText_create();
        sfText_setFont(instructions, editor->font);
        sfText_setString(instructions, "Press Enter to load, Escape to cancel");
        sfText_setCharacterSize(instructions, 12);
        sfText_setPosition(instructions, (sfVector2f){(WINDOW_WIDTH - 380) / 2, (WINDOW_HEIGHT + 60) / 2});
        sfText_setColor(instructions, sfColor_fromRGB(200, 200, 200));
        sfRenderWindow_drawText(editor->window, instructions, NULL);
        sfText_destroy(instructions);
        
        sfRenderWindow_display(editor->window);
    }
}

void update(editor_t* editor)
{

}

void render(editor_t* editor)
{
    sfRenderWindow_clear(editor->window, sfBlack);
    
    draw_grid(editor);
    draw_map_cells(editor);
    draw_palette(editor);
    
    sfRenderWindow_display(editor->window);
}

void draw_grid(editor_t* editor)
{
    sfRectangleShape* line = sfRectangleShape_create();
    sfRectangleShape_setFillColor(line, sfColor_fromRGB(50, 50, 50));
    
    for (int x = 0; x <= GRID_SIZE; x++) {
        sfRectangleShape_setSize(line, (sfVector2f){1, WINDOW_HEIGHT});
        sfRectangleShape_setPosition(line, (sfVector2f){x * CELL_SIZE, 0});
        sfRenderWindow_drawRectangleShape(editor->window, line, NULL);
    }
    
    for (int y = 0; y <= GRID_SIZE; y++) {
        sfRectangleShape_setSize(line, (sfVector2f){GRID_SIZE * CELL_SIZE, 1});
        sfRectangleShape_setPosition(line, (sfVector2f){0, y * CELL_SIZE});
        sfRenderWindow_drawRectangleShape(editor->window, line, NULL);
    }
    
    sfRectangleShape_destroy(line);
}

void draw_map_cells(editor_t* editor)
{
    sfRectangleShape* cell = sfRectangleShape_create();
    sfRectangleShape_setOutlineThickness(cell, 1);
    sfRectangleShape_setOutlineColor(cell, sfBlack);
    
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            int cell_value = editor->map[y][x];
            if (cell_value != 0) {
                int type = cell_value / 1000;
                int subtype = cell_value % 1000;
                sfSprite* sprite = NULL;
                int palette_index = -1;
                
                for (int i = 0; i < editor->palette_count; i++) {
                    if (editor->palette[i].type == type && 
                        editor->palette[i].subtype == subtype) {
                        sprite = editor->palette[i].sprite;
                        palette_index = i;
                        break;
                    }
                }
                
                sfRectangleShape_setSize(cell, (sfVector2f){CELL_SIZE - 1, CELL_SIZE - 1});
                sfRectangleShape_setPosition(cell, (sfVector2f){x * CELL_SIZE + 1, y * CELL_SIZE + 1});
                
                if (sprite && palette_index >= 0 && editor->palette[palette_index].texture) {
                    sfSprite* cell_sprite = sfSprite_create();
                    sfSprite_setTexture(cell_sprite, editor->palette[palette_index].texture, sfTrue);
                    
                    sfIntRect textureRect = sfSprite_getTextureRect(sprite);
                    if (textureRect.width > 0 && textureRect.height > 0) {
                        sfSprite_setTextureRect(cell_sprite, textureRect);
                    }
                    float scale_factor;
                    if (type == 2) {
                        scale_factor = (float)(CELL_SIZE - 2) / textureRect.width * 2.0f;
                    } else {
                        scale_factor = (float)(CELL_SIZE - 2) / textureRect.width;
                        float scale_y = (float)(CELL_SIZE - 2) / textureRect.height;
                        scale_factor = (scale_factor < scale_y) ? scale_factor : scale_y;
                    }
                    sfSprite_setScale(cell_sprite, (sfVector2f){scale_factor, scale_factor});
                    float pos_x = x * CELL_SIZE + (CELL_SIZE - textureRect.width * scale_factor) / 2;
                    float pos_y = y * CELL_SIZE + (CELL_SIZE - textureRect.height * scale_factor) / 2;
                    sfSprite_setPosition(cell_sprite, (sfVector2f){pos_x, pos_y});
                    sfRenderWindow_drawSprite(editor->window, cell_sprite, NULL);
                    sfSprite_destroy(cell_sprite);
                } else {
                    switch (type) {
                        case 1: // Wall
                            sfRectangleShape_setFillColor(cell, sfColor_fromRGB(120, 120, 120));
                            break;
                        case 2: // Enemy
                            sfRectangleShape_setFillColor(cell, sfRed);
                            break;
                        case 3: // Door
                            sfRectangleShape_setFillColor(cell, sfColor_fromRGB(139, 69, 19));
                            break;
                        case 4: // Fixed Object
                            sfRectangleShape_setFillColor(cell, sfBlue);
                            break;
                        case 5: // Item
                            sfRectangleShape_setFillColor(cell, sfGreen);
                            break;
                        default:
                            sfRectangleShape_setFillColor(cell, sfTransparent);
                    }
                    sfRenderWindow_drawRectangleShape(editor->window, cell, NULL);
                }
            }
        }
    }
    if (editor->selected_cell_x >= 0 && editor->selected_cell_y >= 0) {
        sfRectangleShape* selection = sfRectangleShape_create();
        sfRectangleShape_setSize(selection, (sfVector2f){CELL_SIZE, CELL_SIZE});
        sfRectangleShape_setPosition(selection, 
                                   (sfVector2f){editor->selected_cell_x * CELL_SIZE, editor->selected_cell_y * CELL_SIZE});
        sfRectangleShape_setFillColor(selection, sfTransparent);
        sfRectangleShape_setOutlineColor(selection, sfYellow);
        sfRectangleShape_setOutlineThickness(selection, 2);
        sfRenderWindow_drawRectangleShape(editor->window, selection, NULL);
        sfRectangleShape_destroy(selection);
    }
    sfRectangleShape_destroy(cell);
}

void draw_palette(editor_t* editor)
{
    sfRectangleShape* background = sfRectangleShape_create();
    sfRectangleShape_setSize(background, (sfVector2f){PALETTE_WIDTH, WINDOW_HEIGHT});
    sfRectangleShape_setPosition(background, (sfVector2f){GRID_SIZE * CELL_SIZE, 0});
    sfRectangleShape_setFillColor(background, sfColor_fromRGB(30, 30, 30));
    sfRenderWindow_drawRectangleShape(editor->window, background, NULL);
    sfRectangleShape_destroy(background);
    
    const int items_per_page = (WINDOW_HEIGHT - 100) / 40;
    const int start_index = editor->current_page * items_per_page;
    const int end_index = (start_index + items_per_page < editor->palette_count) ? 
                          start_index + items_per_page : editor->palette_count;
    
    for (int i = start_index; i < end_index; i++) {
        int y_pos = (i - start_index) * 40;
        
        sfRectangleShape* item_bg = sfRectangleShape_create();
        sfRectangleShape_setSize(item_bg, (sfVector2f){30, 30});
        sfRectangleShape_setPosition(item_bg, (sfVector2f){GRID_SIZE * CELL_SIZE + 20, y_pos + 5});
        
        if (editor->selected_type == editor->palette[i].type && 
            editor->selected_subtype == editor->palette[i].subtype) {
            sfRectangleShape_setOutlineThickness(item_bg, 2);
            sfRectangleShape_setOutlineColor(item_bg, sfYellow);
        }
        sfRectangleShape_setFillColor(item_bg, sfColor_fromRGB(60, 60, 60));
        sfRenderWindow_drawRectangleShape(editor->window, item_bg, NULL);
        sfRectangleShape_destroy(item_bg);
        if (editor->palette[i].sprite && editor->palette[i].texture) {
            sfSprite* display_sprite = sfSprite_create();
            sfSprite_setTexture(display_sprite, editor->palette[i].texture, sfTrue);
            sfIntRect textureRect = sfSprite_getTextureRect(editor->palette[i].sprite);
            if (textureRect.width > 0 && textureRect.height > 0) {
                sfSprite_setTextureRect(display_sprite, textureRect);
            }
            float scale;
            if (editor->palette[i].type == 2) {
                scale = 26.0f / textureRect.width * 1.2f;
            } else if (editor->palette[i].type == 3) {
                scale = 20.0f / textureRect.width;
            } else {
                scale = 30.0f / textureRect.width;
                float scale_y = 28.0f / textureRect.height;
                scale = (scale < scale_y) ? scale : scale_y;
            }
            sfSprite_setScale(display_sprite, (sfVector2f){scale, scale});
            float pos_x = GRID_SIZE * CELL_SIZE + 20 + (30 - textureRect.width * scale) / 2;
            float pos_y = y_pos + 5 + (30 - textureRect.height * scale) / 2;
            sfSprite_setPosition(display_sprite, (sfVector2f){pos_x, pos_y});
            sfRenderWindow_drawSprite(editor->window, display_sprite, NULL);
            sfSprite_destroy(display_sprite);
        } else {
            sfRectangleShape* item = sfRectangleShape_create();
            sfRectangleShape_setSize(item, (sfVector2f){30, 30});
            sfRectangleShape_setPosition(item, (sfVector2f){GRID_SIZE * CELL_SIZE + 20, y_pos + 5});
            sfRectangleShape_setFillColor(item, editor->palette[i].color);
            sfRenderWindow_drawRectangleShape(editor->window, item, NULL);
            sfRectangleShape_destroy(item);
        }
        
        sfText* text = sfText_create();
        sfText_setFont(text, editor->font);
        sfText_setString(text, editor->palette[i].name);
        sfText_setCharacterSize(text, 14);
        sfText_setPosition(text, (sfVector2f){GRID_SIZE * CELL_SIZE + 60, y_pos + 10});
        sfText_setColor(text, sfWhite);
        sfRenderWindow_drawText(editor->window, text, NULL);
        sfText_destroy(text);
    }
    
    char page_text[32];
    sprintf(page_text, "Page %d/%d", editor->current_page + 1, editor->pages);
    sfText* page_info = sfText_create();
    sfText_setFont(page_info, editor->font);
    sfText_setString(page_info, page_text);
    sfText_setCharacterSize(page_info, 14);
    sfText_setPosition(page_info, (sfVector2f){GRID_SIZE * CELL_SIZE + 20, WINDOW_HEIGHT - 30});
    sfText_setColor(page_info, sfWhite);
    sfRenderWindow_drawText(editor->window, page_info, NULL);
    sfText_destroy(page_info);
    
    sfText* instructions = sfText_create();
    sfText_setFont(instructions, editor->font);
    sfText_setString(instructions, "Controls:\n"
                              "- Ctrl+S: Save map\n"
                              "- Ctrl+L: Load map\n"
                              "- Ctrl+C: Clear map\n"
                              "- Ctrl+B: Add borders\n"
                              "- Up/Dwn: Change page\n"
                              "- Left click: Place item\n"
                              "- Right click: Delete item");
    sfText_setCharacterSize(instructions, 12);
    sfText_setPosition(instructions, (sfVector2f){GRID_SIZE * CELL_SIZE + 150, 0});
    sfText_setColor(instructions, sfColor_fromRGB(200, 200, 200));
    sfRenderWindow_drawText(editor->window, instructions, NULL);
    sfText_destroy(instructions);
}

void handle_click(editor_t* editor, sfMouseButtonEvent event)
{
    int x = event.x / CELL_SIZE;
    int y = event.y / CELL_SIZE;
    
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
        if (event.button == sfMouseLeft) {
            editor->map[y][x] = editor->selected_type * 1000 + editor->selected_subtype;
        } else if (event.button == sfMouseRight) {
            editor->map[y][x] = 0;
        }
    }
}

void handle_drag(editor_t* editor, sfMouseMoveEvent event)
{
    int x = event.x / CELL_SIZE;
    int y = event.y / CELL_SIZE;
    
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
        if (x != editor->last_cell.x || y != editor->last_cell.y) {
            editor->map[y][x] = editor->selected_type * 1000 + editor->selected_subtype;
            editor->last_cell.x = x;
            editor->last_cell.y = y;
        }
    }
}

void select_palette_item(editor_t* editor, sfMouseButtonEvent event)
{
    const int items_per_page = (WINDOW_HEIGHT - 100) / 40;
    const int start_index = editor->current_page * items_per_page;
    
    int item_index = event.y / 40;
    if (start_index + item_index < editor->palette_count) {
        int palette_index = start_index + item_index;
        editor->selected_type = editor->palette[palette_index].type;
        editor->selected_subtype = editor->palette[palette_index].subtype;
    }
}

void clear_map(editor_t* editor)
{
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            editor->map[y][x] = 0;
        }
    }
}

void save_map(editor_t* editor)
{
    char filename[128];
    sprintf(filename, "%s.legend", editor->map_name);
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }
    fprintf(file, "%dx%d\n", GRID_SIZE, GRID_SIZE);
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            int value = editor->map[y][x];
            int output_value;
            
            if (value == 0) {
                output_value = 0;
            } else {
                int type = value / 1000;
                int subtype = value % 1000;
                
                if (type == 1) {
                    output_value = subtype;
                } else {
                    output_value = 0;
                }
            }
            
            fprintf(file, "%d", output_value);
            if (x < GRID_SIZE - 1)
                fprintf(file, ",");
        }
        fprintf(file, "\n");
    }
    
    fprintf(file, "\nDoor positions (x,y,angle)\n");
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            int value = editor->map[y][x];
            if (value / 1000 == 3) {
                int door_index = value % 1000;
                float angle = FIXED_OBJECT_INFOS[door_index].angle;
                fprintf(file, "%d,%d,%.2f\n", x * TILE_SIZE + TILE_SIZE/2, y * TILE_SIZE + TILE_SIZE/2, angle);
            }
        }
    }
    
    fprintf(file, "\nEnemy positions (x,y,type)\n");
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            int value = editor->map[y][x];
            if (value / 1000 == 2) {
                int enemy_type = value % 1000;
                fprintf(file, "%d,%d,%d\n", x * TILE_SIZE + TILE_SIZE/2, y * TILE_SIZE + TILE_SIZE/2, enemy_type);
            }
        }
    }
    
    fprintf(file, "\nObject positions (x,y,type)\n");
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            int value = editor->map[y][x];
            if (value / 1000 == 4) {
                int obj_index = value % 1000;
                fprintf(file, "%d,%d,%d\n", x * TILE_SIZE + TILE_SIZE/2, y * TILE_SIZE + TILE_SIZE/2, obj_index);
            }
        }
    }
    
    fprintf(file, "\nItem positions (x,y,type)\n");
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            int value = editor->map[y][x];
            if (value / 1000 == 5) {
                int item_index = value % 1000;
                fprintf(file, "%d,%d,%d\n", x * TILE_SIZE + TILE_SIZE/2, y * TILE_SIZE + TILE_SIZE/2, item_index);
            }
        }
    }
    fclose(file);
    printf("Map saved to %s\n", filename);
}

void clean_up(editor_t* editor)
{
    for (int i = 0; i < editor->palette_count; i++) {
        if (editor->palette[i].sprite)
            sfSprite_destroy(editor->palette[i].sprite);
        if (editor->palette[i].texture)
            sfTexture_destroy(editor->palette[i].texture);
    }
    
    sfFont_destroy(editor->font);
    sfRenderWindow_destroy(editor->window);
    free(editor->palette);
}
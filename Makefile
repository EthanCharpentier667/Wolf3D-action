##
## EPITECH PROJECT, 2025
## BASE
## File description:
## Makefile
##

NAME	=	wolf3d

CC	=	gcc

SRC_DIR	=	src/
COMMON_DIR=	$(SRC_DIR)common/
INIT_DIR=	$(SRC_DIR)init/
SCENES_DIR=	$(SRC_DIR)scenes/
CREATE_DIR=	Create/
FRAME_DIR=	Frame/
RAYCAST_DIR=	$(SRC_DIR)raycast/
PLAYER_DIR=	$(SRC_DIR)player/
ENEMY_DIR=	$(SRC_DIR)enemy/
ACTION_DIR=	$(SRC_DIR)actions/
GAME_DIR=	$(SRC_DIR)game/
INVENTORY_DIR=	$(SRC_DIR)inventory/
WEAPON_DIR=	$(SRC_DIR)weapon/
VFX_DIR=	$(SRC_DIR)vfx/
SOUND_DIR=	$(SRC_DIR)sounds/

SRC	=	includes/inititliser.c          \
        $(INIT_DIR)init_game.c                  \
        $(INIT_DIR)init_ambiant.c               \
        $(INIT_DIR)init_ui.c                    \
        $(INIT_DIR)init_player.c                \
        $(INIT_DIR)init.c                       \
        $(INIT_DIR)init_minimap.c               \
        $(INIT_DIR)init_settings.c             \
        $(INIT_DIR)init_objects.c             \
        $(SCENES_DIR)mainmenu.c                 \
        $(SCENES_DIR)game.c                     \
        $(SCENES_DIR)settings.c                    \
        $(SCENES_DIR)scenes_manager.c           \
        $(SCENES_DIR)loads_scene.c                    \
        $(SCENES_DIR)victory.c                \
        $(SCENES_DIR)gameover.c                    \
        $(CREATE_DIR)button.c                   \
        $(CREATE_DIR)clocks.c                   \
        $(CREATE_DIR)sound.c                    \
        $(CREATE_DIR)sprite.c                   \
        $(CREATE_DIR)text.c                     \
        $(CREATE_DIR)variables.c                \
        $(CREATE_DIR)window.c                   \
        $(CREATE_DIR)item.c \
        $(CREATE_DIR)enemy.c \
        $(CREATE_DIR)slider.c                 \
        $(CREATE_DIR)environment.c         \
        $(CREATE_DIR)weapon.c         \
        $(CREATE_DIR)hud.c         \
        $(CREATE_DIR)fixed_objects.c         \
        $(FRAME_DIR)buttons_events.c            \
        $(FRAME_DIR)destroy.c                   \
        $(FRAME_DIR)draw.c                      \
        $(FRAME_DIR)handle_event.c              \
        $(FRAME_DIR)inventory_events.c                 \
        $(FRAME_DIR)sliders_events.c                 \
        $(FRAME_DIR)mousepos.c                  \
        $(FRAME_DIR)resize_event.c              \
        $(RAYCAST_DIR)obstacle.c                \
        $(RAYCAST_DIR)drawer.c                  \
        $(RAYCAST_DIR)raycasting.c              \
        $(RAYCAST_DIR)item.c                    \
        $(RAYCAST_DIR)enemy.c                \
        $(RAYCAST_DIR)ray_cast_floor_and_ceiling.c \
        $(RAYCAST_DIR)draw_hud.c        \
        $(RAYCAST_DIR)ray_text.c             \
        $(RAYCAST_DIR)healthbar.c             \
        $(RAYCAST_DIR)flashlight.c             \
        $(RAYCAST_DIR)update_door.c             \
        $(RAYCAST_DIR)fixed_object.c             \
        $(PLAYER_DIR)move.c                     \
        $(PLAYER_DIR)cam.c                      \
        $(ACTION_DIR)change_scene.c                  \
        $(ACTION_DIR)save.c                  \
        $(ACTION_DIR)play.c                     \
        $(ACTION_DIR)settings.c                   \
        $(ACTION_DIR)quit.c                  \
        $(ACTION_DIR)load.c                 \
        $(ACTION_DIR)resolution.c                   \
        $(ACTION_DIR)keybinds.c                      \
        $(ACTION_DIR)sliders.c                   \
        $(COMMON_DIR)math.c                     \
        $(GAME_DIR)load.c       \
        $(GAME_DIR)load_frame.c       \
        $(GAME_DIR)load_map_data.c       \
        $(GAME_DIR)load_inventory_data.c       \
        $(GAME_DIR)load_objects_data.c       \
        $(GAME_DIR)load_items_data.c       \
        $(GAME_DIR)load_enemies_data.c       \
        $(GAME_DIR)timer.c       \
        $(GAME_DIR)update_windows.c       \
        $(GAME_DIR)game_status.c       \
        $(GAME_DIR)levels/parse_levels.c       \
        $(INVENTORY_DIR)init_inventory.c       \
        $(INVENTORY_DIR)inventory.c       \
        $(INVENTORY_DIR)draw_inventory.c       \
        $(INVENTORY_DIR)draw_item_details.c       \
        $(INVENTORY_DIR)inventory_actions.c       \
        $(INVENTORY_DIR)handle_button_inventory_event.c       \
        $(INVENTORY_DIR)draw_inv_bg.c       \
        $(INVENTORY_DIR)inventory_use_item_actions.c       \
        $(ENEMY_DIR)pathfinding.c       \
        $(ENEMY_DIR)update_ennemies.c       \
        $(ENEMY_DIR)damage_player.c       \
        $(ENEMY_DIR)basic_enemy.c       \
        $(ENEMY_DIR)hitler_enemy.c       \
        $(ENEMY_DIR)wolf_enemies.c       \
        $(ENEMY_DIR)miniboss_enemy.c       \
        $(WEAPON_DIR)update_weapon.c       \
        $(WEAPON_DIR)find_enemy_in_range.c       \
        $(VFX_DIR)draw_vfx.c       \
        $(VFX_DIR)create_vfx.c       \
        $(VFX_DIR)linked_list_mana.c       \
        $(VFX_DIR)vfx_info.c       \
        $(VFX_DIR)fb_mana.c       \
        $(VFX_DIR)init_vfx.c       \
        $(VFX_DIR)emit.c       \
        $(VFX_DIR)emit_settings.c       \
        $(VFX_DIR)emit_functions.c       \
        $(VFX_DIR)special_vfx.c             \
        $(VFX_DIR)combat_vfx.c             \
        $(WEAPON_DIR)knife_behavior.c       \
        $(WEAPON_DIR)machine_gun.c       \
        $(WEAPON_DIR)pistol.c       \
        $(WEAPON_DIR)reload_weapons.c       \
        $(WEAPON_DIR)switch_weapons.c       \
        $(WEAPON_DIR)get_wall_impact.c       \
        $(WEAPON_DIR)weapon_sounds.c    \
        $(SOUND_DIR)play_sounds.c

OBJ	=	$(SRC:.c=.o)

INCLUDES	=	-I./includes

CFLAGS	=	-Wall -Wextra -I./includes -Wno-deprecated-declarations -g

LDFLAGS	=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio \
        -lm  -Wno-deprecated-declarations

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) main.c $(OBJ) $(LDFLAGS) $(INCLUDES)

tests_run:      $(OBJ)
	$(CC) -o unit_tests tests/tests_run.c $(SRC) $(LDFLAGS) $(INCLUDES) \
	-lcriterion --coverage
	./unit_tests

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug

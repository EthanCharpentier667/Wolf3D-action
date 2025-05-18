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

SRC	=	includes/inititliser.c          \
        $(INIT_DIR)init_game.c                  \
        $(INIT_DIR)init_ambiant.c               \
        $(INIT_DIR)init_ui.c                    \
        $(INIT_DIR)init_player.c                \
        $(INIT_DIR)init.c                       \
        $(INIT_DIR)init_minimap.c               \
        $(SCENES_DIR)mainmenu.c                 \
        $(SCENES_DIR)game.c                     \
        $(SCENES_DIR)settings.c                    \
        $(SCENES_DIR)scenes_manager.c           \
        $(SCENES_DIR)loads_scene.c                    \
        $(CREATE_DIR)button.c                   \
        $(CREATE_DIR)clocks.c                   \
        $(CREATE_DIR)framebuffer.c              \
        $(CREATE_DIR)sound.c                    \
        $(CREATE_DIR)sprite.c                   \
        $(CREATE_DIR)text.c                     \
        $(CREATE_DIR)variables.c                \
        $(CREATE_DIR)window.c                   \
        $(CREATE_DIR)item.c \
        $(CREATE_DIR)enemy.c \
        $(CREATE_DIR)slider.c                 \
        $(CREATE_DIR)environment.c         \
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
        $(PLAYER_DIR)move.c                     \
        $(PLAYER_DIR)cam.c                      \
        $(ACTION_DIR)play.c                     \
        $(ACTION_DIR)settings.c                   \
        $(ACTION_DIR)quit.c                  \
        $(ACTION_DIR)load.c                 \
        $(COMMON_DIR)math.c                     \
        $(GAME_DIR)load.c       \
        $(INVENTORY_DIR)init_inventory.c       \
        $(INVENTORY_DIR)inventory.c       \
        $(INVENTORY_DIR)draw_inventory.c       \
        $(INVENTORY_DIR)draw_item_details.c       \
        $(INVENTORY_DIR)inventory_actions.c       \
        $(INVENTORY_DIR)handle_button_inventory_event.c       \
        $(INVENTORY_DIR)draw_inv_bg.c       \
        $(ENEMY_DIR)pathfinding.c       \
        $(ENEMY_DIR)update_ennemies.c       \

OBJ	=	$(SRC:.c=.o)

INCLUDES	=	-I./includes

CFLAGS	=	-Wall -Wextra -I./includes -Wno-deprecated-declarations

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

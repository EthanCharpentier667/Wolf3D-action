##
## EPITECH PROJECT, 2025
## BASE
## File description:
## Makefile
##

NAME	=	wolf3d

CC	=	gcc

SRC_DIR	=	src/
INIT_DIR=	$(SRC_DIR)init/
SCENES_DIR=	$(SRC_DIR)scenes/
CREATE_DIR=	Create/
FRAME_DIR=	Frame/
RAYCAST_DIR=	$(SRC_DIR)raycast/
PLAYER_DIR=	$(SRC_DIR)player/
ACTION_DIR=	$(SRC_DIR)actions/

SRC	=	includes/inititliser.c \
        $(INIT_DIR)init_game.c \
        $(INIT_DIR)init_ambiant.c \
        $(INIT_DIR)init_ui.c \
        $(INIT_DIR)init_player.c \
        $(INIT_DIR)init.c \
        $(SCENES_DIR)mainmenu.c \
        $(SCENES_DIR)game.c \
        $(SCENES_DIR)scenes_manager.c \
        $(CREATE_DIR)button.c \
        $(CREATE_DIR)clocks.c \
        $(CREATE_DIR)framebuffer.c \
        $(CREATE_DIR)sound.c \
        $(CREATE_DIR)sprite.c \
        $(CREATE_DIR)text.c \
        $(CREATE_DIR)variables.c \
        $(CREATE_DIR)window.c \
        $(FRAME_DIR)buttons_events.c \
        $(FRAME_DIR)destroy.c \
        $(FRAME_DIR)draw.c \
        $(FRAME_DIR)handle_event.c \
        $(FRAME_DIR)mousepos.c \
        $(FRAME_DIR)resize_event.c \
        $(RAYCAST_DIR)wall.c \
        $(RAYCAST_DIR)drawer.c \
        $(RAYCAST_DIR)raycasting.c \
        $(PLAYER_DIR)player.c \
        $(ACTION_DIR)play.c \

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

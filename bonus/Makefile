##
## EPITECH PROJECT, 2025
## Wolf3D
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -I../includes

LIBS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lm

TARGET = map_editor

SRC = map_editor.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET)

re: clean all

run: $(TARGET)
	mkdir -p levels
	./$(TARGET)

.PHONY: all clean re run
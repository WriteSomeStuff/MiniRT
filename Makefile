# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cschabra <cschabra@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/05 17:27:05 by cschabra      #+#    #+#                  #
#    Updated: 2024/08/20 13:12:50 by cschabra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT
T_EXEC	= tester
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread -Ofast -flto $(HEADERS) -g #-fsanitize=address
LFLAGS	= -lm -ldl -lglfw
OS		= $(shell uname)

LIBFT	= 42lib/libft
LIBMLX	= 42lib/MLX42

HEADERS	= -I include -I $(LIBFT)/include -I $(LIBMLX)/include
MLXOUT 	= $(LIBMLX)/build/libmlx42.a
LIBS	= $(LIBFT)/libft.a $(MLXOUT)

CFILES	=	alloc.c \
			a_to_float.c \
			cast_rays.c \
			collisions.c \
			collisions2.c \
			colours.c \
			clean_up.c \
			draw.c \
			exit.c \
			free.c \
			get_next_line_rt.c \
			get_next_line_utils_rt.c \
			hit_cone.c \
			hit_cylinder.c \
			hit_disc.c \
			hit_plane.c \
			hit_sphere.c \
			hit_torus.c \
			keyboard.c \
			init_objects.c \
			init_objects2.c \
			intersect.c \
			list_adding.c \
			list_navigation.c \
			maths.c \
			maximum_thread.c \
			mouse.c \
			normalize_scene.c \
			parsing.c \
			parsing_utils.c \
			quaternions_utils.c \
			quaternions.c \
			reflect.c \
			rotate_objects.c \
			textures.c \
			textures2.c \
			trace.c \
			translate_objects.c \
			translate_objects2.c \
			utils.c \
			vectors.c \
			vectors2.c \
			vector_utils.c \

TFILES	=	colour_tests.cpp \
			intersection_tests.cpp \
			light_tests.cpp \
			quat_test.cpp \
			vector_tests.cpp \
			tests.cpp \
			parser_test.cpp \

MAIN	= 	main.c	

SRC_DIR	= src
T_DIR	= tests
OBJ_DIR	= obj
OBJECTS	= $(addprefix $(OBJ_DIR)/,$(notdir $(CFILES:%.c=%.o)))

M_OBJ	= $(addprefix $(OBJ_DIR)/,$(notdir $(MAIN:%.c=%.o)))
T_OBJ	= $(addprefix $(OBJ_DIR)/,$(notdir $(TFILES:%.cpp=%.o)))

ifeq ($(OS), Darwin)
LFLAGS	+= -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" -framework OpenGL -framework Cocoa -framework IOKit
# LFLAGS	+= -lm -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

all: $(NAME)

test: $(T_EXEC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MLXOUT):
	cmake $(LIBMLX) -B $(LIBMLX)/build
	cmake --build $(LIBMLX)/build -j4

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

$(NAME): $(LIBS) $(OBJ_DIR) $(OBJECTS) $(M_OBJ)
	$(CC) $(CFLAGS) $(OBJECTS) $(M_OBJ) $(LFLAGS) $(LIBS) -o $(NAME) 

$(T_EXEC): $(LIBS) $(OBJ_DIR) $(OBJECTS) $(T_OBJ)
	c++ $(CFLAGS) -I $(T_DIR) -std=c++11 $(OBJECTS) $(T_OBJ) $(LFLAGS) $(LIBS) -o $(T_EXEC)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/colours/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/hooks/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/initialisation/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/math/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/utils/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(T_DIR)/%.cpp
	c++ -c $(CFLAGS) -std=c++11 -o $@ $^

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -rf $(LIBMLX)/build
	rm -f $(NAME)
	rm -f $(T_EXEC)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all
retest: fclean test

debug: CFLAGS += -fsanitize=address
debug: re

.PHONY: all clean fclean re debug test retest
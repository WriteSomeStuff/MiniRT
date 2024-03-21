# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cschabra <cschabra@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/05 17:27:05 by cschabra      #+#    #+#                  #
#    Updated: 2024/03/21 17:02:05 by cschabra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g $(HEADERS)

LIBFT	= 42lib/libft
LIBMLX	= 42lib/MLX42

HEADERS	= -I include -I $(LIBFT)/include -I $(LIBMLX)/include
MLXOUT 	= $(LIBMLX)/build/libmlx42.a
LIBS	= $(LIBFT)/libft.a $(MLXOUT)

CFILES	=	alloc.c \
			a_to_float.c \
			cast_rays.c \
			colours.c \
			cube.c \
			clean_up.c \
			get_next_line_rt.c \
			get_next_line_utils_rt.c \
			init_lights.c \
			init_objects.c \
			intersect.c \
			list_adding.c \
			list_navigation.c \
			main.c \
			maths.c \
			parsing.c \
			quaternions.c \
			rasterise.c \
			utils.c \
			vectors.c \
			vector_utils.c \

SRC_DIR	= src
OBJ_DIR	= $(SRC_DIR)/obj
OBJECTS	= $(addprefix $(OBJ_DIR)/,$(notdir $(CFILES:%.c=%.o)))

all: $(LIBS) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MLXOUT):
	cmake $(LIBMLX) -B $(LIBMLX)/build
	cmake --build $(LIBMLX)/build -j4

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

$(NAME): $(OBJ_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lm -ldl -lglfw $(LIBS) -o $(NAME) 

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/colours/%.c
	$(CC) -c $(CFLAGS) -o $@ $^
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/initialisation/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/math/%.c
	$(CC) -c $(CFLAGS) -o $@ $^
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/utils/%.c
	$(CC) -c $(CFLAGS) -o $@ $^


clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -rf $(LIBMLX)/build
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

debug: CFLAGS += -fsanitize=address
debug: re

.PHONY: all clean fclean re debug
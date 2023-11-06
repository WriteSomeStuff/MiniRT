# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cschabra <cschabra@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/05 17:27:05 by cschabra      #+#    #+#                  #
#    Updated: 2023/11/06 16:36:06 by cschabra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= miniRT
CC= cc
CFLAGS= -Wall -Wextra -Werror $(HEADERS)

LIBFT= 42lib/libft
LIBMLX= 42lib/MLX42

HEADERS= -I include -I $(LIBFT)/include -I $(LIBMLX)/include
MLXOUT = $(LIBMLX)/build/libmlx42.a
LIBS= $(LIBFT)/libft.a $(MLXOUT)

CFILES= main.c

SRC_DIR= src
OBJ_DIR= obj
OBJECTS= $(SRC_DIR)/$(CFILES:%.c=$(OBJ_DIR)/%.o)

all: $(MLXOUT) $(NAME)

$(SRC_DIR)/$(OBJ_DIR):
	mkdir -p $(SRC_DIR)/$(OBJ_DIR)

$(MLXOUT):
	cmake $(LIBMLX) -B $(LIBMLX)/build
	cmake --build $(LIBMLX)/build -j4

$(NAME): $(SRC_DIR)/$(OBJ_DIR) $(OBJECTS)
	$(MAKE) -C $(LIBFT)
	$(CC) -o $(NAME) -lm $(CFLAGS) $(SRC_DIR)/$(CFILES) $(LIBS) -ldl -lglfw -pthread

$(SRC_DIR)/$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(SRC_DIR)/$(OBJ_DIR)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -rf $(LIBMLX)/build
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

debug: CFLAGS += -g -fsanitize=address
debug: re

.PHONY: all clean fclean re debug
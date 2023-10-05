# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cschabra <cschabra@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/05 17:27:05 by cschabra      #+#    #+#                  #
#    Updated: 2023/10/05 17:58:42 by cschabra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= miniRT
CFLAGS= -Wall -Wextra -Werror $(HEADERS) #-Ofast

LIBFT= 42lib/libft
LIBMLX= 42lib/MLX42

HEADERS= -I include -I $(LIBFT)/include -I $(LIBMLX)/include
LIBS= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a

CFILES= ${shell find src -iname "*.c"}

OBJECTS= $(CFILES:.c=.o)

all: $(NAME)

mlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@cmake --build $(LIBMLX)/build -j4

$(NAME): mlx $(OBJECTS)
	@$(MAKE) -C $(LIBFT)
	@$(CC) -o $(NAME) -lm $(CFLAGS) $(CFILES) $(LIBS) -ldl -lglfw -pthread

clean:
	rm  -f $(OBJECTS)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

debug: CFLAGS += -g -fsanitize=address
debug: re

.PHONY: all clean fclean re debug
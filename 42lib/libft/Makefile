# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cschabra <cschabra@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/13 18:15:02 by cschabra      #+#    #+#                  #
#    Updated: 2024/08/13 14:22:53 by vvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
CFLAGS= -Wall -Wextra -Werror -I include

CFILES= 	./src/io/ft_putchar_fd.c \
			./src/io/ft_putendl_fd.c \
			./src/io/ft_putnbr_fd.c \
			./src/io/ft_putstr_fd.c \
			./src/io/gnl/get_next_line_utils.c \
			./src/io/gnl/get_next_line.c \
			./src/io/printf/ft_hex.c \
			./src/io/printf/ft_io.c \
			./src/io/printf/ft_printf.c \
			./src/io/printf/ft_ptr.c \
			./src/io/printf/ft_unsign.c \
			./src/lst/ft_lstadd_back.c \
			./src/lst/ft_lstadd_front.c \
			./src/lst/ft_lstclear.c \
			./src/lst/ft_lstdelone.c \
			./src/lst/ft_lstiter.c \
			./src/lst/ft_lstlast.c \
			./src/lst/ft_lstmap.c \
			./src/lst/ft_lstnew.c \
			./src/lst/ft_lstsize.c \
			./src/memory/ft_bzero.c \
			./src/memory/ft_calloc.c \
			./src/memory/ft_memchr.c \
			./src/memory/ft_memcmp.c \
			./src/memory/ft_memcpy.c \
			./src/memory/ft_memmove.c \
			./src/memory/ft_memset.c \
			./src/other/ft_atoi.c \
			./src/other/ft_isalnum.c \
			./src/other/ft_isalpha.c \
			./src/other/ft_isascii.c \
			./src/other/ft_isdigit.c \
			./src/other/ft_isprint.c \
			./src/other/ft_itoa.c \
			./src/other/ft_tolower.c \
			./src/other/ft_toupper.c \
			./src/string/ft_split.c \
			./src/string/ft_strchr.c \
			./src/string/ft_strdup.c \
			./src/string/ft_striteri.c \
			./src/string/ft_strjoin.c \
			./src/string/ft_strlcat.c \
			./src/string/ft_strlcpy.c \
			./src/string/ft_strlen.c \
			./src/string/ft_strmapi.c \
			./src/string/ft_strncmp.c \
			./src/string/ft_strnstr.c \
			./src/string/ft_strrchr.c \
			./src/string/ft_strtrim.c \
			./src/string/ft_substr.c \

OBJECTS= $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar -rcs $(NAME) $(OBJECTS)

clean:
	@rm  -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
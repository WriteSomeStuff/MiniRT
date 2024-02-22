/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_rt.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 17:29:13 by vincent       #+#    #+#                 */
/*   Updated: 2024/02/22 17:23:39 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_RT_H
# define GET_NEXT_LINE_RT_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "miniRT.h"

# define NOT_FOUND -1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

typedef struct s_data	t_data;

typedef struct s_gnldata
{
	char	*line;
	size_t	size;
	size_t	len;
}	t_gnldata;

char	*combine_strings(t_data *rt, t_gnldata *data, char *str1, char *str2);
void	copy_paste(char *dest, char *src);
int		find_newl(char *str);
char	*ft_realloc(t_data *rt, char *old, size_t size);
size_t	get_length(char *str);
char	*get_next_line_rt(t_data *rt, int fd);

#endif
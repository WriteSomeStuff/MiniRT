/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_rt.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 17:28:35 by vincent       #+#    #+#                 */
/*   Updated: 2024/03/05 17:35:44 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	manage_buffer(char *dest, char *src)
{
	size_t	i;

	i = 0;
	if (find_newl(dest) == NOT_FOUND)
	{
		dest[0] = '\0';
		return ;
	}
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static char	*read_stuff(t_data *rt, t_gnldata *data, int fd, char *buffer)
{
	int		bytes_read;
	char	*line;

	line = NULL;
	bytes_read = 1;
	line = combine_strings(rt, data, line, buffer);
	data->len = get_length(line);
	while (find_newl(buffer) == NOT_FOUND && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(line);
			exit_error(rt, ": read failed");
		}
		buffer[bytes_read] = '\0';
		line = combine_strings(rt, data, line, buffer);
	}
	return (line);
}

char	*get_next_line_rt(t_data *rt, int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	t_gnldata	data;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	data.size = BUFFER_SIZE + 1;
	data.len = BUFFER_SIZE;
	data.line = read_stuff(rt, &data, fd, buffer);
	manage_buffer(buffer, &buffer[find_newl(buffer) + 1]);
	data.line = ft_realloc(rt, data.line, get_length(data.line) + 1);
	if (*data.line == '\0')
		return (free(data.line), NULL);
	if (find_newl(data.line) != NOT_FOUND)
		data.line[ft_strlen(data.line) - 1] = '\0';
	return (data.line);
}

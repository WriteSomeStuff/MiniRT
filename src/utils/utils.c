/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:25:10 by cschabra      #+#    #+#                 */
/*   Updated: 2024/05/28 14:45:28 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_vec	create_vector(t_data *data, char *info)
{
	t_vec	vector;
	char	**vec;

	vec = ft_split(info, ',');
	if (vec == NULL)
		exit_error(data, ": split failed");
	vector.x = a_to_float(data, vec[0]);
	vector.y = a_to_float(data, vec[1]);
	vector.z = a_to_float(data, vec[2]);
	free_2d((void ***)&vec);
	return (vector);
}

void	check_split(t_data *data, char **info, int32_t num)
{
	int32_t	i;

	i = 0;
	while (i < num)
	{
		if (info[i] == NULL)
			exit_error(data, ": insufficient input");
		i++;
	}
	if (info[i] != NULL && ft_strncmp(info[i], "t:", 2) == 0)
		i++;
	if (info[i] != NULL)
		exit_error(data, ": invalid input");
}

bool	is_white_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	return (false);
}

static void	check_texture(t_data *data, char *str)
{
	int32_t		fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_error(data, ": could not open texture file");
	close(fd);
}

static void	tex_and_reflect_check(t_data *data, char **info, int32_t x)
{
	if (ft_strncmp("r:", info[x], 2) == 0 && (info[x + 1] == NULL || ft_strncmp("t:", info[x + 1], 2)))
		return ;
	if (info[x + 1] == NULL && ft_strncmp("t:", info[x], 2) == 0)
		check_texture(data, &info[x][2]);
}

void	verify_info(t_data *data, char **info)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	while (info[x] != NULL)
	{
		y = 0;
		while (info[x][y] != '\0' && info[x][y] != 'r' && info[x][y] != 't')
		{
			if (info[x][y] == '-' && ft_isdigit(info[x][y + 1]) == false)
				exit_error(data, ": no digit after \"-\" sign");
			while (ft_isdigit(info[x][y]) == true)
				y++;
			if (info[x][y] == '\0')
				break ;
			else if (ft_strchr(".,-", info[x][y]) != NULL)
				y++;
			else
				exit_error(data, ": invalid character in input");
		}
		x++;
	}
	tex_and_reflect_check(data, info, --x);
}

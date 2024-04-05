/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:25:10 by cschabra      #+#    #+#                 */
/*   Updated: 2024/04/05 18:26:13 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	print_vector(t_vec vector)
{
	printf("%lf %lf %lf\n", vector.x, vector.y, vector.z);
}

void	print_2d_charray(char **array)
{
	int	i;

	i = 0;
	printf("args: ");
	if (array == NULL)
	{
		printf("%p\n", array);
		return ;
	}
	printf("\n");
	while (array[i] != NULL)
	{
		printf("String [%d]: %s\n", i, array[i]);
		i++;
	}
	printf("String [%d]: %s\n", i, array[i]);
}

void	rgb_to_floats(t_vec *rgb)
{
	rgb->r /= 255;
	rgb->g /= 255;
	rgb->b /= 255;
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

void	verify_info(t_data *data, char **info)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	while (info[x] != NULL)
	{
		y = 0;
		if (info[x + 1] == NULL && ft_strncmp("t:", info[x], 2) == 0)
		{
			check_texture(data, &info[x][2]);
			break ;
		}
		while (info[x][y] != '\0')
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
}

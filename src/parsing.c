/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:52:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/08 15:08:56 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	is_empty_str(char *str)
{
	while (*str != '\0')
	{
		if (is_white_space(*str) == false)
			return (false);
		str++;
	}
	return (true);
}

static t_token	determine_object(char *str)
{
	if (ft_strncmp(str, "A ", 2) == 0)
		return (AMBIENT);
	if (ft_strncmp(str, "C ", 2) == 0)
		return (CAMERA);
	if (ft_strncmp(str, "cy ", 3) == 0)
		return (CYLINDER);
	if (ft_strncmp(str, "L ", 2) == 0)
		return (LIGHT);
	if (ft_strncmp(str, "pl ", 3) == 0)
		return (PLANE);
	if (ft_strncmp(str, "sp ", 3) == 0)
		return (SPHERE);
	else
		return (INVALID);
}

static void	alloc_objects(t_data *data, t_input *input)
{
	int32_t	obj[SPHERE + 1];
	int32_t	i;

	i = 0;
	while (i < SPHERE)
	{
		obj[i] = count_objects(input, i);
		i++;
	}
	if (obj[AMBIENT] != 1 || obj[CAMERA] != 1 || obj[LIGHT] != 1)
		exit_error(data, ": incompatible file input");
	data->ambient = rt_calloc(data, obj[AMBIENT] * sizeof(t_ambient));
	data->cam = rt_calloc(data, obj[CAMERA] * sizeof(t_camera));
	data->cyls = rt_calloc(data, obj[CYLINDER] * sizeof(t_cylinder));
	data->light = rt_calloc(data, obj[LIGHT] * sizeof(t_light));
	data->planes = rt_calloc(data, obj[PLANE] * sizeof(t_plane));
	data->spheres = rt_calloc(data, obj[SPHERE] * sizeof(t_sphere));
	init_objects(data, input);
}

static void	assign_function_pointers(t_data *data)
{
	data->f[AMBIENT] = &init_ambient;
	data->f[CAMERA] = &init_camera;
	data->f[CYLINDER] = &init_cylinder;
	data->f[LIGHT] = &init_light;
	data->f[PLANE] = &init_plane;
	data->f[SPHERE] = &init_sphere;
}

void	read_file(t_data *data, char *location)
{
	t_input	*input;

	input = NULL;
	data->fd = open(location, O_RDONLY);
	if (data->fd == -1)
		exit_error(data, ": could not open file");
	while (FOREVER)
	{
		data->line = get_next_line_rt(data, data->fd);
		if (data->line == NULL)
			break ;
		if (is_empty_str(data->line) == false)
		{
			node_add_back(&input, \
				new_node(data, data->line, determine_object(data->line)));
			if (data->input == NULL)
				data->input = input;
		}
		free_and_null((void **)&data->line);
	}
	close(data->fd);
	assign_function_pointers(data);
	alloc_objects(data, input);
}

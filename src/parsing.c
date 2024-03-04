/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:52:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/04 18:39:10 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	assign_function_pointers(t_data *data)
{
	data->f[AMBIENT] = &init_ambient;
	data->f[CAMERA] = &init_camera;
	data->f[CYLINDER] = &init_cylinder;
	data->f[LIGHT] = &init_light;
	data->f[PLANE] = &init_plane;
	data->f[SPHERE] = &init_sphere;
}

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

static t_input	*node_last(t_input *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	node_add_back(t_input **lst, t_input *new)
{
	t_input	*t;

	t = node_last(*lst);
	if (t == NULL)
		*lst = new;
	else
		t->next = new;
}

static t_input	*new_node(t_data *data, char *line, t_token token)
{
	t_input	*node;

	if (token == INVALID)
		exit_error(data, ": invalid input");
	node = rt_calloc(data, sizeof(t_input));
	node->info = ft_split(&line[2], ' ');
	if (node->info == NULL)
		exit_error(data, ": split failed");
	node->token = token;
	return (node);
}

void	read_file(t_data *data, char *location)
{
	t_input	*input;
	char	*next_line;

	input = NULL;
	data->fd = open(location, O_RDONLY);
	if (data->fd == -1)
		exit_error(data, ": could not open file");
	while (FOREVER)
	{
		next_line = get_next_line_rt(data, data->fd);
		if (next_line == NULL)
			break ;
		if (is_empty_str(next_line) == true)
			free(next_line);
		else
			node_add_back(&input, new_node(data, next_line, determine_object(next_line)));
	}
	data->input = input;
	close(data->fd);
	init_camera(data, input->next->info);
}

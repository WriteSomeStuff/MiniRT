/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:42:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/26 16:20:07 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_and_null(void **variable)
{
	free(*variable);
	*variable = NULL;
}

void	free_2d(void ***input)
{
	int		i;
	void	**array;

	if (*input == NULL)
		return ;
	array = *input;
	i = 0;
	while (array[i] != NULL)
	{
		free_and_null(&array[i]);
		i++;
	}
	free(array);
	*input = NULL;
}

void	exit_error(t_data *data, char *msg)
{
	clean_up(data);
	ft_putstr_fd("Error", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	exit_success(t_data *data)
{
	clean_up(data);
	exit(EXIT_SUCCESS);
}

void	clear_list(t_input **input)
{
	t_input	*p;

	if (input == NULL)
		return ;
	while (*input)
	{
		p = (*input)->next;
		free_2d((void ***)&(*input)->info);
		free(*input);
		*input = p;
	}
	*input = NULL;
}

static void	free_spheres(t_sphere **spheres, uint32_t amount)
{
	uint32_t	i;

	i = 0;
	while (i < amount)
	{
		free((*spheres)[i].tex);
		i++;
	}
	free(*spheres);
	*spheres = NULL;
}

void	clean_up(t_data *data)
{
	clear_list(&data->input);
	free(data->ambient);
	free(data->cam);
	free(data->cyls);
	free(data->light);
	free(data->planes);
	free_spheres(&data->spheres, data->sphere_count);
	free(data->window);
	free(data->line);
	close(data->fd);
	// mlx_free_image(data->image);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
}

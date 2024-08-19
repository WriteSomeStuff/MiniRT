/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:42:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/08/19 17:06:40 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	free_planes(t_plane **planes, uint32_t amount)
{
	uint32_t	i;

	i = 0;
	while (i < amount)
	{
		if ((*planes)[i].tex != NULL)
			mlx_delete_texture((*planes)[i].tex);
		i++;
	}
	free_and_null((void **)planes);
}

static void	free_spheres(t_sphere **spheres, uint32_t amount)
{
	uint32_t	i;

	i = 0;
	while (i < amount)
	{
		if ((*spheres)[i].tex != NULL)
			mlx_delete_texture((*spheres)[i].tex);
		i++;
	}
	free_and_null((void **)spheres);
}

void	clean_up(t_data *data)
{
	clear_list(&data->input);
	free(data->cam);
	free_and_null((void **)&data->cones);
	free_and_null((void **)&data->cyls);
	free_and_null((void **)&data->discs);
	free_planes(&data->planes, data->plane_count);
	free_spheres(&data->spheres, data->sphere_count);
	free_2d((void ***)&data->pix);
	free(data->window);
	free(data->line);
	free(data->threads);
	if (data->fd != -1)
		close(data->fd);
	if (data->made_mutex == true)
		pthread_mutex_destroy(&data->mutex);
	if (data->mlx != NULL)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
}

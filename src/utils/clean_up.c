/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:42:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/06/26 18:33:11 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	free_cones(t_cone **cones, uint32_t amount)
{
	free(*cones);
	*cones = NULL;
}

static void	free_cylinders(t_cylinder **cylinders, uint32_t amount)
{
	uint32_t	i;

	i = 0;
	while (i < amount)
	{
		if ((*cylinders)[i].tex != NULL)
			mlx_delete_texture((*cylinders)[i].tex);
		i++;
	}
	free(*cylinders);
	*cylinders = NULL;
}

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
	free(*planes);
	*planes = NULL;
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
	free(*spheres);
	*spheres = NULL;
}

void	clean_up(t_data *data)
{
	clear_list(&data->input);
	free(data->cam);
	free_cones(&data->cones, data->cone_count);
	free_cylinders(&data->cyls, data->cyl_count);
	free_planes(&data->planes, data->plane_count);
	free_spheres(&data->spheres, data->sphere_count);
	free_2d((void ***)&data->pix);
	free(data->window);
	free(data->line);
	free(data->threads);
	close(data->fd);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_destroy(&data->mutex);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
}

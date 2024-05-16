/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 16:25:25 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/16 17:47:30 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	single_ray(t_data *data, float x, float y)
{
	t_vec	t;

	t.x = (2 * ((x + 0.5f) / data->mlx->width) - 1);
	t.y = (1 - (2 * ((y + 0.5f) / data->mlx->height))) * data->window->aspect_ratio;
	t.z = 1;
	t.x *= data->cam->fov_correction;
	t.y *= data->cam->fov_correction;
	return (normalize_vector(t));
}

static void	allocate_directions(t_data *data)
{
	t_vec	**dirs;
	int		i;
	int		j;

	i = 0;
	dirs = rt_malloc(data, 361 * sizeof(t_vec *));
	while (i < 360)
	{
		j = 0;
		dirs[i] = rt_malloc(data, 360 * sizeof(t_vec));
		while (j < 360)
		{
			dirs[i][j] = vec(0, 0, 1);
			rotate(&dirs[i][j], quat());
		}
		i++;
	}
	dirs[i] = NULL;
	data->directions = dirs;
}

static void	allocate_rays(t_data *data, int32_t width, int32_t height)
{
	t_pixel	**pixels;
	int32_t	i;

	i = 0;
	if (data->pix != NULL)
	{
		free_2d((void ***)&data->pix);
	}
	pixels = rt_calloc(data, (height + 1) * sizeof(t_pixel *));
	while (i < height)
	{
		pixels[i] = rt_malloc(data, width * sizeof(t_pixel));
		i++;
	}
	data->pix = pixels;
}

void	cast_rays(t_data *data)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	allocate_rays(data, data->window->width, data->window->height);
	if (data->directions == NULL)
		allocate_directions(data);
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			data->pix[y][x].ray_direction = single_ray(data, x, y);
			x++;
		}
		y++;
	}
}

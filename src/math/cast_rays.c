/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 16:25:25 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/07/04 14:43:21 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	single_ray(t_data *d, float x, float y)
{
	t_vec	t;

	t.x = (2 * ((x + 0.5f) / d->mlx->width) - 1);
	t.y = (1 - (2 * ((y + 0.5f) / d->mlx->height))) * d->window->aspect_ratio;
	t.z = 1;
	t.x *= d->cam->fov_correction;
	t.y *= d->cam->fov_correction;
	return (normalize_vector(t));
}

static void	allocate_rays(t_data *data, int32_t width, int32_t height)
{
	t_pixel	**pixels;
	int32_t	i;

	i = 0;
	// if (data->mlx->width == data->window->width && data->mlx->height == data->window->height && data->pix != NULL)
	// 	return ;
	if (data->pix != NULL)
	{
		free_2d((void ***)&data->pix);
	}
	pixels = rt_malloc(data, (height + 1) * sizeof(t_pixel *));
	while (i < height)
	{
		pixels[i] = rt_calloc(data, width * sizeof(t_pixel));
		i++;
	}
	pixels[i] = NULL;
	data->pix = pixels;
}

void	cast_rays(t_data *data)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	allocate_rays(data, data->window->width, data->window->height);
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

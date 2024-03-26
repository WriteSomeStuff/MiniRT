/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/26 16:59:09 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	lights_out(t_data *data)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
}

void	draw_something(t_data *data, uint32_t x, uint32_t y)
{
	t_ray	ray;
	t_hit	col;

	ray.col = &col;
	ray.origin.vec3 = data->cam->viewpoint.vec3;
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			ray.direction = direction_to_xy(data, (float)x, (float)y);
			find_closest_object(data, ray.col, &ray);
			if (ray.col->inside_object == true)
			{
				ft_putendl_fd("Warning: camera is inside an object", STDERR_FILENO);
				lights_out(data);
				return ;
			}
			if (ray.col->hit == true)
				draw_collision(data, ray.col, x, y);
			else
				mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
}

/* while (luminosity > threshhold)
{
	luminosity *= distance_thingy();
	luminosity *= object_colour();
	ray.origin = col.location;
	ray.direction = surface_norm;
	find_closest_object()
} */

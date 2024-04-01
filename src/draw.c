/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/31 22:55:28 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	lights_out(t_data *data)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
	mlx_put_string(data->mlx, "Warning: camera is inside object", 50, 50);
}

void	draw_something(t_data *data, uint32_t x, uint32_t y)
{
	t_ray	ray;
	t_hit	col;

	ray.col = &col;
	ray.origin.vec3 = data->cam->viewpoint.vec3;
	init_map(data);
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			data->map[y][x] = -1;
			ray.direction = direction_to_xy(data, (float)x, (float)y);
			find_closest_object(data, ray.col, &ray);
			if (ray.col->inside_object == true)
			{
				ft_putendl_fd("Warning: camera is inside an object", STDERR_FILENO);
				lights_out(data);
				return ;
			}
			if (ray.col->hit == true)
			{
				draw_collision(data, ray.col, x, y);
			}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/07 18:11:19 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define THRESHHOLD 0.1
#define NUM_RAYS 10

static float	sum(t_vec vector)
{
	return (vector.x + vector.y + vector.z);
}

/* void	draw_something(t_data *data, uint32_t x, uint32_t y)
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
			ray.direction = data->ray_directions[y][x];
			find_closest_object(data, ray.col, &ray);
			if (ray.col->hit == true)
			{
				draw_collision(data, ray.col, x, y);
			}
			else
				mlx_put_pixel(data->scene, x, y, ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
} */

bool	bouncy_castle(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	t_vec	first_hit;
	t_vec	dir;
	float	product;
	int		i;

	i = 0;
	ft_bzero(ray->col, sizeof(t_hit));
	ray->col->colour = vec(1, 1, 1);
	ray->col->type = INVALID;
	ray->col->distance = FLT_MAX;
	while (sum(ray->col->colour) > THRESHHOLD)
	{
		product = -1;
		find_closest_object(data, ray->col, ray);
		if (i == 0)
		{
			if (ray->col->hit == false)
				return (false);
			first_hit = reflection_result(ray->col->colour, data->ambient->colour, 1);
			i++;
		}
		if (ray->col->hit == false || ray->col->type == LIGHT)
			break ;
		draw_collision(data, ray->col, x, y);
		while (product < 0)
		{
			dir = random_vector();
			product = dot(dir, ray->col->surface_norm);
		}
		ray->direction = dir;
		ray->origin = ray->col->location;
		print_vector(ray->direction);
		print_vector(dir);
	}
	if (ray->col->hit == false)
	{
		ray->col->colour = first_hit;
	}
	return (true);
}

void	draw_something(t_data *data, uint32_t x, uint32_t y)
{
	t_ray	ray;
	t_hit	col;
	int		i;

	ft_bzero(&ray, sizeof(t_ray));
	ray.col = &col;
	ft_bzero(&col, sizeof(t_hit));
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			i = 0;
			ray.origin.vec3 = data->cam->viewpoint.vec3;
			ray.direction = data->pix[y][x].ray_direction;
			while (i < NUM_RAYS)
			{
				if (bouncy_castle(data, &ray, x, y) == false)
				{
					data->pix[y][x].colour = vec(0, 0, 0);
					break ;
				}
				data->pix[y][x].colour.vec3 += col.colour.vec3;
				i++;
			}
			data->pix[y][x].colour.vec3 /= NUM_RAYS;
			mlx_put_pixel(data->scene, x, y, percentage_to_rgba(data->pix[y][x].colour));
			x++;
		}
		y++;
	}
	puts("DONE BITCHES");
}

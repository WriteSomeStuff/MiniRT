/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/13 18:16:55 by vvan-der      ########   odam.nl         */
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
	int		i;

	i = 0;
	while (sum(ray->col->colour) > THRESHHOLD)
	{
		ray->col->hit = false;
		find_closest_object(data, ray->col, ray);
		if (i == 0)
		{
			if (ray->col->hit == false)
				return (false);
			draw_collision(data, ray->col, x, y);
			first_hit = reflection_result(ray->col->colour, data->ambient->colour, 1);
			i++;
		}
		else if (ray->col->hit == false)
			break ;
		else
			draw_collision(data, ray->col, x, y);
		if (ray->col->type == LIGHT)
			break ;
		dir = random_vector();
		while (radian_to_degree(angle(dir, ray->col->surface_norm)) > 90)
		{
			dir = random_vector();
		}
		ray->direction = dir;
		ray->origin = ray->col->location;
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
	ft_bzero(&col, sizeof(t_hit));
	ray.col = &col;
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			i = 0;
			ray.origin.vec3 = data->cam->viewpoint.vec3;
			ray.direction = data->pix[y][x].ray_direction;
			col.colour = vec(1, 1, 1);
			while (i < NUM_RAYS && bouncy_castle(data, &ray, x, y) == true)
			{
				ray.origin.vec3 = data->cam->viewpoint.vec3;
				ray.direction = data->pix[y][x].ray_direction;
				data->pix[y][x].colour.vec3 += col.colour.vec3;
				col.colour = vec(1, 1, 1);
				i++;
			}
			// data->pix[y][x].colour.vec3 += col.colour.vec3;
			if (i > 0)
				data->pix[y][x].colour.vec3 /= (float)i;
			mlx_put_pixel(data->scene, x, y, percentage_to_rgba(data->pix[y][x].colour));
			x++;
		}
		y++;
	}
	puts("DONE BITCHES");
}

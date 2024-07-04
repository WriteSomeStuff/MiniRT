/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/07/04 15:31:19 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float		max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

static void	initial_hit(t_data *data, t_ray *ray, int32_t x, int32_t y)
{
	find_closest_object(data, ray->col, ray, y % data->num_threads);
	draw_collision(ray->col, ray->direction);
	data->pix[y][x].obj_num = ray->col->obj_num;
	if (ray->col->type == LIGHT)
	{
		data->pix[y][x].pix_clr.vec3 = ray->col->colour.vec3 * max(dot(ray->direction, inverted(ray->col->surface_norm)), 0.1f);
		gamma_adjust(&data->pix[y][x].pix_clr);
	}
	else if (ray->col->hit == true)
	{
		data->pix[y][x].obj_clr = ray->col->objclr;
		data->pix[y][x].specular = ray->col->specular;
		data->pix[y][x].glossiness = ray->col->glossiness;
		data->pix[y][x].location = ray->col->location;
		data->pix[y][x].incoming = ray->direction;
		data->pix[y][x].surface_norm = ray->col->surface_norm;
		data->pix[y][x].ambient = reflection_result(ray->col->colour, \
			data->ambient, 1 - ray->col->glossiness);
	}
}

static void	reset_ray(t_data *data, t_ray *ray, int32_t x, int32_t y)
{
	ft_bzero(ray->col, sizeof(t_hit));
	ray->origin = data->cam->viewpoint;
	ray->direction = data->pix[y][x].ray_direction;
	ray->col->obj_num = -1;
	ray->col->colour = vec(1, 1, 1);
}

static bool	keep_going(t_data *data)
{
	bool	tmp;
	pthread_mutex_lock(&data->mutex);
	tmp = data->go;
	pthread_mutex_unlock(&data->mutex);
	return (tmp);
}

void	render(t_data *data, int32_t x, int32_t y)
{
	t_ray		ray;
	t_hit		col;

	ray.col = &col;
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			reset_ray(data, &ray, x, y);
			initial_hit(data, &ray, x, y);
			trace(data, &ray, x, y);
			mlx_put_pixel(data->scene, x, y, percentage_to_rgba(data->pix[y][x].pix_clr));
			x++;
			if (keep_going(data) == false)
				break ;
		}
		y += data->num_threads;
	}
	pthread_mutex_lock(&data->mutex);
	data->threads_absorbed++;
	pthread_mutex_unlock(&data->mutex);
}

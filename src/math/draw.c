/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/24 21:34:41 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "miniRT.h"
#include "pthread.h"
#define THRESHHOLD 0.1
#define NUM_RAYS 10

static float	sum(t_vec vector)
{
	return (vector.x + vector.y + vector.z);
}

static void	clamp(t_vec *colour)
{
	if (colour->x > NUM_RAYS)
		colour->x = NUM_RAYS;
	if (colour->y > NUM_RAYS)
		colour->y = NUM_RAYS;
	if (colour->z > NUM_RAYS)
		colour->z = NUM_RAYS;
}

static void	multi_bounce(t_data *data, t_ray *ray, uint32_t x, uint32_t y, uint32_t tmp)
{
	while (sum(ray->col->colour) > THRESHHOLD)
	{
		ray->col->hit = false;
		ray->direction = random_vector(data, tmp);
		if (dot(ray->direction, ray->col->surface_norm) < 0)
			ray->direction.vec3 *= -1;
		find_closest_object(data, ray->col, ray);
		if (ray->col->hit == false)
		{
			ray->col->colour = vec(0, 0, 0);
			break ;
		}
		draw_collision(ray->col);
		if (ray->col->type == LIGHT)
			break ;
		ray->origin = ray->col->location;
		ray->col->colour.vec3 *= 0.98f;
	}
	data->pix[y][x].diffuse.vec3 += ray->col->colour.vec3;
	ray->col->colour = vec(1, 1, 1);
}

void	specular_light(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	find_closest_object(data, ray->col, ray);
	if (ray->col->hit == false)
	{
		data->pix[y][x].obj_num = -1;
		data->pix[y][x].colour = vec(0, 0, 0);
		return ;
	}
	data->pix[y][x].obj_num = ray->col->obj_num;
	data->pix[y][x].location = ray->col->location;
	data->pix[y][x].surface_norm = ray->col->surface_norm;
	data->pix[y][x].colour = ray->col->colour;
	// printf("%d\n", ray->col->type);
	draw_collision(ray->col);
	data->pix[y][x].ambient = reflection_result(ray->col->colour, data->ambient->colour, 1);
	while (sum(ray->col->colour) > THRESHHOLD)
	{
		ray->origin = ray->col->location;
		ray->direction = reflect(ray->direction, ray->col->surface_norm);
		find_closest_object(data, ray->col, ray);
		if (ray->col->hit == false)
		{
			data->pix[y][x].specular = vec(0, 0, 0);
			break ;
		}
		draw_collision(ray->col);
		if (ray->col->type == LIGHT)
			break ;
		ray->col->colour.vec3 *= 0.99f;
	}
	ray->col->reflectivity = 1 - ray->col->reflectivity;
	data->pix[y][x].ambient.vec3 *= ray->col->reflectivity;
	ray->origin = data->cam->viewpoint;
	ray->direction = data->pix[y][x].ray_direction;
	ray->col->colour = vec(1, 1, 1);
}

static uint32_t	total(t_vec c1, t_vec c2, t_vec c3)
{
	t_vec	res;

	res = combine_colours(c1, c2);
	res = combine_colours(res, c3);
	return (percentage_to_rgba(res));
}

void	render(t_data *data, uint32_t x, uint32_t y)
{
	t_ray		ray;
	t_hit		col;
	uint32_t	i;
	uint32_t	tmp;

	tmp = y;
	ft_bzero(&ray, sizeof(t_ray));
	ft_bzero(&col, sizeof(t_hit));
	ray.col = &col;
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			i = 0;
			ray.origin = data->cam->viewpoint;
			ray.direction = data->pix[y][x].ray_direction;
			col.colour = vec(1, 1, 1);
			specular_light(data, &ray, x, y);
			if (data->pix[y][x].obj_num != -1)
			{
				while (i < NUM_RAYS)
				{
					ray.direction = data->pix[y][x].ray_direction;
					multi_bounce(data, &ray, x, y, tmp);
					i++;
				}
				data->pix[y][x].diffuse.vec3 *= 4;
				clamp(&data->pix[y][x].diffuse);
				data->pix[y][x].diffuse.vec3 /= NUM_RAYS;
			}
			mlx_put_pixel(data->scene, x, y, total(data->pix[y][x].diffuse, data->pix[y][x].specular, data->pix[y][x].ambient));
			x++;
		}
		y += data->num_threads;
	}
}

// void	test_multiple_renders(t_data *data, uint32_t x, uint32_t y)
// {
// 	uint32_t	i = 0;

// 	while (i < 10)
// 	{	render(data, 0, y);
// 		add_arrays(data, 0, y);
// 		i++;
// 	}
// 	while (y < data->window->height)
// 	{
// 		x = 0;
// 		while (x < data->window->width)
// 		{
// 			mlx_put_pixel(data->scene, x, y, percentage_to_rgba(data->pix[y][x].colour));
// 			data->pix[y][x].colour.vec3 *= 0;
// 			x++;
// 		}
// 		y += ts;
// 	}
// }

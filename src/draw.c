/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/21 16:37:20 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "miniRT.h"
#include "pthread.h"
#define THRESHHOLD 0.1
#define NUM_RAYS 100

static float	sum(t_vec vector)
{
	return (vector.x + vector.y + vector.z);
}

static void		clamp(t_vec *colour)
{
	if (colour->x > NUM_RAYS)
		colour->x = NUM_RAYS;
	if (colour->y > NUM_RAYS)
		colour->y = NUM_RAYS;
	if (colour->z > NUM_RAYS)
		colour->z = NUM_RAYS;
}

static bool	multi_bounce(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	t_vec	first_hit;
	int		i;

	i = 0;
	while (sum(ray->col->colour) > THRESHHOLD)
	{
		ray->col->hit = false;
		find_closest_object(data, ray->col, ray);
		if (i == 0)
		{
			if (ray->col->hit == false)
			{
				data->pix[y][x].obj_num = -1;
				return (false);
			}
			draw_collision(ray->col);
			first_hit = ray->col->colour;
			data->pix[y][x].obj_num = ray->col->obj_num;
			i++;
		}
		else if (ray->col->hit == false)
		{
			ray->col->colour = vec(0, 0, 0);
			// return (true);
		}
		else
			draw_collision(ray->col);
		if (ray->col->type == LIGHT)
			break ;
		// if (ray->col->type == PLANE)
		// 	ray->direction = reflect(ray->direction, ray->col->surface_norm);
		// else
		ray->direction = random_vector();
		if (dot(ray->direction, ray->col->surface_norm) < 0)
			ray->direction.vec3 *= -1;
		ray->origin = ray->col->location;
		// ray->col->colour.vec3 *= 0.95f;
	}
	// clamp(&ray->col->colour);
	ray->col->colour = combine_colours(reflection_result(first_hit, data->ambient->colour, 1), ray->col->colour);
	return (true);
}

void	render(t_data *data, uint32_t x, uint32_t y)
{
	t_ray		ray;
	t_hit		col;
	float		i;

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
			while (i < NUM_RAYS && multi_bounce(data, &ray, x, y) == true)
			{
				col.type = INVALID;
				ray.origin.vec3 = data->cam->viewpoint.vec3;
				ray.direction = data->pix[y][x].ray_direction;
				data->pix[y][x].colour.vec3 += col.colour.vec3;
				col.colour = vec(1, 1, 1);
				i++;
			}
			if (i >= 1)
			{
				data->pix[y][x].colour.vec3 *= 4;
				clamp(&data->pix[y][x].colour);
				data->pix[y][x].colour.vec3 /= i;
			}
			mlx_put_pixel(data->scene, x, y, percentage_to_rgba(data->pix[y][x].colour));
			data->pix[y][x].colour.vec3 *= 0;
			x++;
		}
		y += ts;
	}
}

// void	add_arrays(t_data *data, uint32_t x, uint32_t y)
// {
// 	while (y < data->window->height)
// 	{
// 		x = 0;
// 		while (x < data->window->width)
// 		{
// 			data->pix[y][x].colour.vec3 += data->pix[y][x].colour.vec3;
// 			clamp(&data->pix[y][x].colour);
// 			x++;
// 		}
// 		y += ts;
// 	}
// }

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

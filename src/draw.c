/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/19 16:11:54 by vincent       ########   odam.nl         */
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
			data->pix[y][x].obj_num = ray->col->obj_num;
			first_hit = reflection_result(ray->col->colour, data->ambient->colour, 0.2);
			i++;
		}
		else if (ray->col->hit == false)
			break ;
		else
			draw_collision(ray->col);
		if (ray->col->type == LIGHT)
			return (true);
		if (ray->col->type == PLANE)
			ray->direction = reflect(ray->direction, ray->col->surface_norm);
		else
			ray->direction = random_vector();
		if (dot(ray->direction, ray->col->surface_norm) < 0)
			ray->direction.vec3 *= -1;
		ray->origin = ray->col->location;
		ray->col->colour.vec3 *= 0.95f;
	}
	if (ray->col->hit == false)
		ray->col->colour = first_hit;
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
				data->pix[y][x].colour.vec3 /= i;
			mlx_put_pixel(data->scene, x, y, percentage_to_rgba(data->pix[y][x].colour));
			data->pix[y][x].colour.vec3 *= 0;
			x++;
		}
		y += ts;
	}
}

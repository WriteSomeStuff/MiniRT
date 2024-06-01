/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/06/01 15:39:51 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "miniRT.h"
#include "pthread.h"

static void	initial_hit(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	find_closest_object(data, ray->col, ray);
	draw_collision(ray->col, ray->col->absorption, ray->col->reflectivity);
	data->pix[y][x].obj_num = ray->col->obj_num;
	if (ray->col->type == LIGHT)
		data->pix[y][x].pix_clr = ray->col->colour;
	else if (ray->col->hit == true)
	{
		data->pix[y][x].obj_clr = ray->col->colour;
		data->pix[y][x].reflectivity = ray->col->reflectivity;
		data->pix[y][x].absorption = ray->col->absorption;
		data->pix[y][x].location = ray->col->location;
		data->pix[y][x].surface_norm = ray->col->surface_norm;
		data->pix[y][x].ambient = reflection_result(ray->col->colour, \
			data->ambient->colour, ray->col->absorption);
		data->pix[y][x].ambient.vec3 += data->ambient->colour.vec3 * ray->col->reflectivity;
	}
}

static void	reset_ray(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	ft_bzero(ray->col, sizeof(t_hit));
	ray->origin = data->cam->viewpoint;
	ray->direction = data->pix[y][x].ray_direction;
	ray->col->obj_num = -1;
	ray->col->colour = vec(1, 1, 1);
}

void	render(t_data *data, uint32_t x, uint32_t y)
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
			if (col.hit == true && col.type != LIGHT)
			{
				trace(data, &ray, x, y);
			}
			mlx_put_pixel(data->scene, x, y, percentage_to_rgba(data->pix[y][x].pix_clr));
			data->pix[y][x].pix_clr.vec3 *= 0;
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

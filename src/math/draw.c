/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/26 12:00:52 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "miniRT.h"
#include "pthread.h"

static void	clamp(t_vec *colour)
{
	if (colour->x > NUM_RAYS)
		colour->x = NUM_RAYS;
	if (colour->y > NUM_RAYS)
		colour->y = NUM_RAYS;
	if (colour->z > NUM_RAYS)
		colour->z = NUM_RAYS;
}

static void	initial_hit(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	find_closest_object(data, ray->col, ray);
	if (ray->col->hit == true)
	{
		ray->col->colour = vec(1, 1, 1);
		draw_collision(ray->col);
		data->pix[y][x].location = ray->col->location;
		data->pix[y][x].surface_norm = ray->col->surface_norm;
		data->pix[y][x].ambient = reflection_result(ray->col->colour, \
			data->ambient->colour, 1 - ray->col->reflectivity);
	}
	data->pix[y][x].obj_num = ray->col->obj_num;
	data->pix[y][x].obj_clr = ray->col->colour;
}

void	specular_light(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	initial_hit(data, ray, x, y);
	while (sum(ray->col->colour) > THRESHHOLD && ray->col->type != LIGHT)
	{
		ray->col->hit = false;
		ray->origin = ray->col->location;
		ray->direction = reflect(ray->direction, ray->col->surface_norm);
		find_closest_object(data, ray->col, ray);
		if (ray->col->hit == true)
			draw_collision(ray->col);
		else
			ray->col->colour = vec(0, 0, 0);
	}
	data->pix[y][x].specular.vec3 = ray->col->colour.vec3 * ray->col->reflectivity;
	ray->col->reflectivity = 1 - ray->col->reflectivity;
	data->pix[y][x].ambient.vec3 *= ray->col->reflectivity;
}

static t_vec	total(t_vec c1, t_vec c2, t_vec c3)
{
	t_vec	res;

	res = combine_colours(c1, c2);
	res = combine_colours(res, c3);
	return (res);
}

static void	reset_ray(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	ft_bzero(ray->col, sizeof(t_hit));
	ray->origin = data->cam->viewpoint;
	ray->direction = data->pix[y][x].ray_direction;
	ray->col->type = INVALID;
	ray->col->obj_num = -1;
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
			specular_light(data, &ray, x, y);
			if (data->pix[y][x].obj_num != -1 && col.type != LIGHT)
			{
				multi_bounce(data, &ray, x, y);
				clamp(&data->pix[y][x].diffuse);
			}
			data->pix[y][x].pix_clr.vec3 += total(data->pix[y][x].diffuse, \
				data->pix[y][x].specular, data->pix[y][x].ambient).vec3;
			mlx_put_pixel(data->scene, x, y, percentage_to_rgba(data->pix[y][x].pix_clr));
			if (x == y && x == 5)
			{
				puts("colour");
				print_vector(data->pix[y][x].pix_clr);
				puts("specular");
				print_vector(data->pix[y][x].specular);
				puts("diffuse");
				print_vector(data->pix[y][x].diffuse);
				puts("ambient");
				print_vector(data->pix[y][x].ambient);
			}
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

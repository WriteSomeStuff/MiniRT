/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/27 17:36:30 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "miniRT.h"
#include "pthread.h"

static void	clamp(t_vec *colour)
{
	if (colour->x > 1.0f)
	{
		colour->y *= 1.0f / colour->x;
		colour->z *= 1.0f / colour->x;
		colour->x = 1.0f;
	}
	if (colour->y > 1.0f)
	{
		colour->x *= 1.0f / colour->x;
		colour->z *= 1.0f / colour->x;
		colour->y = 1.0f;
	}
	if (colour->z > 1.0f)
	{
		colour->x *= 1.0f / colour->x;
		colour->y *= 1.0f / colour->x;
		colour->z = 1.0f;
	}
}

static void	initial_hit(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	find_closest_object(data, ray->col, ray);
	if (ray->col->hit == true)
	{
		draw_collision(ray->col, 1);
		data->pix[y][x].obj_clr = ray->col->colour;
		data->pix[y][x].location = ray->col->location;
		data->pix[y][x].surface_norm = ray->col->surface_norm;
		data->pix[y][x].ambient = reflection_result(ray->col->colour, \
			data->ambient->colour, ray->col->absorption);
		if (ray->col->type == LIGHT)
			data->pix[y][x].pix_clr = ray->col->colour;
	}
	data->pix[y][x].obj_num = ray->col->obj_num;
}

void	specular_light(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	uint32_t	bounces;

	data->pix[y][x].specular = vec(0, 0, 0);
	return ;
	bounces = 0;
	ray->col->colour.vec3 = vec(1, 1, 1).vec3 * ray->col->reflectivity;
	while (bounces < MAX_BOUNCES && ray->col->hit == true && ray->col->type != LIGHT)
	{
		ray->col->hit = false;
		ray->origin = ray->col->location;
		ray->direction = reflect(ray->direction, ray->col->surface_norm);
		if (dot(ray->direction, ray->col->surface_norm) < 0)
			ray->direction.vec3 *= -1;
		find_closest_object(data, ray->col, ray);
		if (ray->col->hit == false)
			ray->col->colour = vec(0, 0, 0);
		else
			draw_collision(ray->col, ray->col->reflectivity);
		bounces++;
	}
	if (bounces == MAX_BOUNCES)
		ray->col->colour = vec(0, 0, 0);
	data->pix[y][x].specular = ray->col->colour;
	clamp(&data->pix[y][x].specular);
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
			if (col.obj_num != -1 && col.type != LIGHT)
			{
				specular_light(data, &ray, x, y);
				multi_bounce(data, &ray, x, y);
				clamp(&data->pix[y][x].diffuse);
				data->pix[y][x].pix_clr = total(data->pix[y][x].diffuse, \
					data->pix[y][x].specular, data->pix[y][x].ambient);
				// if (y % data->num_threads == 0)
				// {
				// 	static int i = 0;
				// 	puts("diffuse");
				// 	print_vector(data->pix[y][x].diffuse);
				// 	puts("colour");
				// 	print_vector(data->pix[y][x].pix_clr);
				// 	puts("specular");
				// 	print_vector(data->pix[y][x].specular);
				// 	puts("ambient");
				// 	print_vector(data->pix[y][x].ambient);
				// 	i++;
				// 	if (i == 10)
				// 		exit(0);
				// }
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

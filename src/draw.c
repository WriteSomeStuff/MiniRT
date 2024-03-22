/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/22 16:56:24 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	lights_out(t_data *data)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
}

void	draw_something(t_data *data)
{
	float	x;
	float	y;
	float	dot;
	// t_vec3	luminosity;
	t_ray	ray;
	t_hit	col;
	t_vec	surface_norm;
	t_vec	light_dir;
	t_vec	light;
	t_vec	light_colour;
	light_colour = data->light->colour;
	t_sphere	*sphere;
	t_vec	ambiance;
	ambiance = data->ambient->colour;
	
	light.x = 25000;
	light.y = 4;
	light.z = 0;

	ray.origin.vec3 = data->cam->viewpoint.vec3;
	y = 0;
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			ray.direction = direction_to_xy(data, x, y);
			find_closest_object(data, &col, &ray);
			if (col.inside_object == true)
			{
				ft_putendl_fd("Warning: camera is inside an object", STDERR_FILENO);
				lights_out(data);
				return ;
			}
			sphere = (t_sphere *)col.obj;
			if (col.hit == true)
			{
				surface_norm.vec3 = col.location.vec3 - sphere->center.vec3;
				surface_norm = normalize_vector(&surface_norm);
				light_dir.vec3 = light.vec3 - col.location.vec3;
				light_dir = normalize_vector(&light_dir);
				dot = dot_product(&light_dir, &surface_norm);
				t_vec	ambsphere = reflection_result(&sphere->colour, &ambiance, 1);
				if (dot < 0)
				{
					mlx_put_pixel(data->image, x, y, sphere->amb_colour);
				}
				else
				{
					t_vec	result = reflection_result(&sphere->colour, &light_colour, dot);
					result = combine_colours(&ambsphere, &result);
					percentage_to_rgba(&result);
					mlx_put_pixel(data->image, x, y, percentage_to_rgba(&result));
				}
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

/* void	draw_something(t_data *data)
{
	float	x;
	float	y;
	float	dot;
	t_ray	ray;
	t_hit	col;
	t_vec	surface_norm;
	t_vec	light_dir;
	t_vec	light;
	t_vec	light_colour;
	light_colour = data->light[0].colour;
	t_vec	sphere;
	sphere = data->spheres[0].colour;
	t_vec	ambiance;
	ambiance = data->ambient->colour;
	
	light.x = 25000;
	light.y = 4;
	light.z = 0;

	ray.origin.vec3 = data->cam->viewpoint.vec3;
	y = 0;
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			ray.direction = direction_to_xy(data, x, y);
			col = intersect_sphere(&ray, &data->spheres[0]);
			if (col.inside_object == true)
			{
				ft_putendl_fd("Warning: camera is inside an object", STDERR_FILENO);
				lights_out(data);
				return ;
			}
			if (col.hit == true)
			{
				surface_norm.vec3 = col.location.vec3 - data->spheres->center.vec3;
				surface_norm = normalize_vector(&surface_norm);
				light_dir.vec3 = light.vec3 - col.location.vec3;
				light_dir = normalize_vector(&light_dir);
				dot = dot_product(&light_dir, &surface_norm);
				t_vec	ambsphere = reflection_result(&sphere, &ambiance, 1);
				if (dot < 0)
				{
					mlx_put_pixel(data->image, x, y, data->spheres->amb_colour);
				}
				else
				{
					t_vec	result = reflection_result(&sphere, &light_colour, dot);
					result = combine_colours(&ambsphere, &result);
					percentage_to_rgba(&result);
					mlx_put_pixel(data->image, x, y, percentage_to_rgba(&result));
				}
			}
			else
				mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
} */
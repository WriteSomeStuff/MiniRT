/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/21 18:05:01 by vvan-der      ########   odam.nl         */
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
	t_ray	ray;
	t_hit	col;
	t_vec	surface_norm;
	t_vec	light_dir;
	t_vec	light;
	t_vec	light_colour;
	light_colour = data->light->colour;
	t_vec	sphere;
	sphere = data->spheres->colour;
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
}

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:23:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/24 17:54:02 by vincent       ########   odam.nl         */
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

static t_vec	get_texture_colour(t_texture *texture, t_vec *surface, t_vec *center, float radius)
{
	t_vec	colour;
	t_vec	dir;
	
	dir.vec3 = surface->vec3 - center->vec3;
	float	x;
	float	y;

	// print_vector(dir);
	// printf("width: %d, height: %d\n", texture->width, texture->height);
	x = texture->width / 2 + ((dir.x / 2 / radius) * (texture->width / 2));
	y = texture->height - (texture->height / 2 + ((dir.y / radius) * (texture->height / 2)));
	// printf("x: %f, y: %f\n", x, y);
	// exit(0);
	colour = texture->px[(int)y][(int)x];
	return (colour);
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
	t_vec	clr;
	
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
			if (col.hit == true)
			{
				sphere = (t_sphere *)col.obj;
				surface_norm.vec3 = col.location.vec3 - sphere->center.vec3;
				surface_norm = normalize_vector(&surface_norm);
				light_dir.vec3 = light.vec3 - col.location.vec3;
				light_dir = normalize_vector(&light_dir);

				// printf("texture: %p\n", data->textures);
				// printf("col: %p\n", &col.location);
				// printf("center: %p\n", &sphere->center);
				// printf("radius: %f\n", sphere->radius);
				dot = dot_product(&light_dir, &surface_norm);
				clr = get_texture_colour(&data->textures[0], &col.location, &sphere->center, sphere->radius);
				t_vec	ambsphere = reflection_result(&clr, &ambiance, 1);
				if (dot < 0)
				{
					// t_vec night = get_texture_colour(&data->textures[0], &col.location, &sphere->center, sphere->radius);
					// ambsphere = reflection_result(&night, &ambiance, 1);
					mlx_put_pixel(data->image, x, y, percentage_to_rgba(&ambsphere));
				}
				else
				{
					t_vec	result = reflection_result(&clr, &light_colour, dot);
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
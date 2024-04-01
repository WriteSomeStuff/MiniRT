/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/31 22:55:22 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	cylinder(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	(void)data;
	(void)col;
	(void)x;
	(void)y;
}

static void	plane(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	float	dot;
	t_plane	*plane;
	t_vec	ambplane;
	t_vec	light_dir;
	t_vec	result;
	t_vec	clr;

	plane = (t_plane *)col->obj;
	set_vector(&light_dir, &col->location, &data->light->source);
	dot = dot_product(&light_dir, &plane->orientation);
	clr = plane_texture(plane, &col->location);
	ambplane = reflection_result(&clr, &data->ambient->colour, 1);
	if (dot < 0)
	{
		mlx_put_pixel(data->image, x, y, percentage_to_rgba(&ambplane));
	}
	else
	{
		result = reflection_result(&clr, &data->light->colour, dot);
		result = combine_colours(&ambplane, &result);
		percentage_to_rgba(&result);
		mlx_put_pixel(data->image, x, y, percentage_to_rgba(&result));
	}
}

static void	sphere(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	float	dot;
	t_sphere	*sphere;
	t_vec	ambsphere;
	t_vec	light_dir;
	t_vec	clr;
	
	// puts("HI4");
	sphere = (t_sphere *)col->obj;
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	set_vector(&light_dir, &col->location, &data->light->source);
	dot = dot_product(&light_dir, &col->surface_norm);
	clr = sphere_texture(sphere, &col->surface_norm);
	ambsphere = reflection_result(&clr, &data->ambient->colour, 1);
	if (dot < 0)
	{
		mlx_put_pixel(data->image, x, y, percentage_to_rgba(&ambsphere));
	}
	else
	{
		clr = reflection_result(&clr, &data->light->colour, dot);
		clr = combine_colours(&ambsphere, &clr);
		percentage_to_rgba(&clr);
		mlx_put_pixel(data->image, x, y, percentage_to_rgba(&clr));
	}
	data->map[y][x] = SPHERE;
	// printf("%p %p\n", sphere, data->spheres);
	// printf("map[x]: %d, map[y]: %d, value: %d\n", x, y, data->map[y][x]);
}

void	draw_collision(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	static void	(*ptr[3])(t_data *, t_hit *, uint32_t, uint32_t) = \
		{&cylinder, &plane, &sphere};

	ptr[col->type](data, col, x, y);
}

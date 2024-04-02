/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/02 18:00:45 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	cylinder(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	(void)data;
	(void)col;
	mlx_put_pixel(data->image, x, y, 0xFFFFFFFF);
	data->map[y][x] = CYLINDER;
}

static void	plane(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	float	product;
	t_plane	*plane;
	t_vec	ambplane;
	t_vec	light_dir;
	t_vec	result;
	t_vec	clr;

	plane = (t_plane *)col->obj;
	set_vector(&light_dir, &col->location, &data->light->source);
	product = dot(&light_dir, &plane->orientation);
	clr = plane_texture(plane, &col->location);
	ambplane = reflection_result(&clr, &data->ambient->colour, 1);
	if (product < 0)
	{
		mlx_put_pixel(data->image, x, y, percentage_to_rgba(&ambplane));
	}
	else
	{
		result = reflection_result(&clr, &data->light->colour, product);
		result = combine_colours(&ambplane, &result);
		percentage_to_rgba(&result);
		mlx_put_pixel(data->image, x, y, percentage_to_rgba(&result));
	}
	data->map[y][x] = PLANE;
}

static void	sphere(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	float	product;
	t_sphere	*sphere;
	t_vec	ambsphere;
	t_vec	light_dir;
	t_vec	clr;
	
	sphere = (t_sphere *)col->obj;
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	set_vector(&light_dir, &col->location, &data->light->source);
	product = dot(&light_dir, &col->surface_norm);
	clr = sphere_texture(sphere, &col->surface_norm);
	ambsphere = reflection_result(&clr, &data->ambient->colour, 1);
	if (product < 0)
	{
		mlx_put_pixel(data->image, x, y, percentage_to_rgba(&ambsphere));
	}
	else
	{
		clr = reflection_result(&clr, &data->light->colour, product);
		clr = combine_colours(&ambsphere, &clr);
		percentage_to_rgba(&clr);
		mlx_put_pixel(data->image, x, y, percentage_to_rgba(&clr));
	}
	data->map[y][x] = SPHERE;
}

void	draw_collision(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	static void	(*ptr[3])(t_data *, t_hit *, uint32_t, uint32_t) = \
		{&cylinder, &plane, &sphere};

	ptr[col->type](data, col, x, y);
}

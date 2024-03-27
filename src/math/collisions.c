/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/27 17:41:33 by vincent       ########   odam.nl         */
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
	// printf("dot: %f\n", dot);
	dot *= -1;
	clr = plane_texture(plane, &plane->orientation);
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
	
	sphere = (t_sphere *)col->obj;
	sphere->tex = data->textures[0];
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
}

void	draw_collision(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	static void	(*ptr[3])(t_data *, t_hit *, uint32_t, uint32_t) = \
		{&cylinder, &plane, &sphere};

	ptr[col->type](data, col, x, y);
}

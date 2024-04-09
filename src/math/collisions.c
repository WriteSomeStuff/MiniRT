/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/09 18:25:02 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	checkerboard_tex(t_sphere *sphere, t_vec *loc);

static uint32_t	pixel_colour(t_data *data, t_vec *clr, float product)
{
	t_vec	amb;

	amb = reflection_result(clr, &data->ambient->colour, 1);
	if (product < 0)
	{
		return (percentage_to_rgba(&amb));
	}
	else
	{
		*clr = reflection_result(clr, &data->light->colour, product);
		*clr = combine_colours(&amb, clr);
		percentage_to_rgba(clr);
		return (percentage_to_rgba(clr));
	}
}

static void	cylinder(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	t_cylinder	*cyl;
	t_vec		light_dir;
	t_vec		clr;
	float		product;
	t_vec		to_center;
	t_vec		to_new;

	cyl = (t_cylinder *)col->obj;
	to_center.vec3 = col->location.vec3 - cyl->center.vec3;
	product = dot(&to_center, &cyl->orientation);
	if (fabs(product) > fabs(vector_length(&cyl->center, &cyl->base)))
	{
		mlx_put_pixel(data->image, x, y, 0x000000ff);
		return ;
	}
	to_new.vec3 = cyl->center.vec3 + product * cyl->orientation.vec3;
	set_vector(&col->surface_norm, &to_new, &col->location);
	set_vector(&light_dir, &col->location, &data->light->source);
	product = dot(&light_dir, &col->surface_norm);
	clr = cylinder_texture(cyl, &col->location);
	mlx_put_pixel(data->image, x, y, pixel_colour(data, &clr, product));
	data->map[y][x] = cyl->instance;
}

static void	plane(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	float	product;
	t_plane	*plane;
	t_vec	light_dir;
	t_vec	clr;

	plane = (t_plane *)col->obj;
	set_vector(&light_dir, &col->location, &data->light->source);
	product = dot(&light_dir, &plane->orientation);
	clr = plane_texture(plane, &col->location);
	mlx_put_pixel(data->image, x, y, pixel_colour(data, &clr, product));
	data->map[y][x] = plane->instance;
}

static void	sphere(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	float	product;
	t_sphere	*sphere;
	t_vec	light_dir;
	t_vec	clr;
	
	sphere = (t_sphere *)col->obj;
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	set_vector(&light_dir, &col->location, &data->light->source);
	product = dot(&light_dir, &col->surface_norm);
	// if (checkerboard_tex(sphere, &col->location) == true)
	// 	mlx_put_pixel(data->image, x, y, 0xffffffff);
	// else
	// 	mlx_put_pixel(data->image, x, y, 0x0);
	// return ;
	clr = sphere_texture(sphere, &col->surface_norm);
	mlx_put_pixel(data->image, x, y, pixel_colour(data, &clr, product));
	data->map[y][x] = sphere->instance;
}

void	draw_collision(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	static void	(*ptr[3])(t_data *, t_hit *, uint32_t, uint32_t) = \
		{&cylinder, &plane, &sphere};

	ptr[col->type](data, col, x, y);
}

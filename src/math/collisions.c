/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/16 17:26:19 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	checkerboard_tex(t_data *data, t_sphere *sphere, t_hit *col);

/* uint32_t	pixel_colour(t_data *data, t_vec clr, float product)
{
	t_vec	amb;

	amb = reflection_result(clr, data->ambient->colour, 1);
	if (product < 0)
	{
		return (percentage_to_rgba(amb));
	}
	else
	{
		clr = reflection_result(clr, data->light->colour, product);
		clr = combine_colours(amb, clr);
		return (percentage_to_rgba(clr));
	}
} */

static void	cylinder(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	t_cylinder	*cyl;
	// t_vec		light_dir;
	t_vec		clr;
	float		product;
	t_vec		to_center;
	t_vec		to_new;

	cyl = (t_cylinder *)col->obj;
	if (col->caps == false)
	{
		to_center.vec3 = col->location.vec3 - cyl->center.vec3;
		product = dot(to_center, cyl->orientation);
		to_new.vec3 = cyl->center.vec3 + product * cyl->orientation.vec3;
		set_vector(&col->surface_norm, &to_new, &col->location);
	}
	// set_vector(&light_dir, &col->location, &data->light->source);
	// product = dot(light_dir, col->surface_norm);
	clr = cylinder_texture(cyl, &col->location);
	// mlx_put_pixel(data->scene, x, y, pixel_colour(data, clr, product));
	data->pix[y][x].obj_num = cyl->instance;
	col->colour = reflection_result(col->colour, clr, 1);
}

static void	plane(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	// float	product;
	t_plane	*plane;
	// t_vec	light_dir;
	t_vec	clr;

	plane = (t_plane *)col->obj;
	// set_vector(&light_dir, &col->location, &data->light->source);
	// product = dot(light_dir, col->surface_norm);
	clr = plane_texture(plane, &col->surface_norm);
	// mlx_put_pixel(data->scene, x, y, pixel_colour(data, clr, product));
	data->pix[y][x].obj_num = plane->instance;
	col->colour = reflection_result(col->colour, clr, 1);
}

static void	sphere(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	// float	product;
	t_sphere	*sphere;
	// t_vec	light_dir;
	t_vec	clr;
	
	sphere = (t_sphere *)col->obj;
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	// set_vector(&light_dir, &col->location, &data->light->source);
	// product = dot(light_dir, col->surface_norm);
	// if (checkerboard_tex(data, sphere, col) == true)
	// 	mlx_put_pixel(data->scene, x, y, 0xffffffff);
	// else
	// 	mlx_put_pixel(data->scene, x, y, 0xff);
	// return ;
	data->pix[y][x].obj_num = sphere->instance;
	clr = sphere_texture(sphere, &col->surface_norm);
	// mlx_put_pixel(data->scene, x, y, pixel_colour(data, clr, product));
	col->colour = reflection_result(col->colour, clr, 1);
}

void	draw_collision(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	static void	(*ptr[4])(t_data *, t_hit *, uint32_t, uint32_t) = \
		{&cylinder, &plane, &sphere, &sphere};

	ptr[col->type](data, col, x, y);
	col->location.vec3 += OFFSET * col->surface_norm.vec3;
}

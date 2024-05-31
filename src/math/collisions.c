/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/30 18:04:33 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	checkerboard_tex(t_data *data, t_sphere *sphere, t_hit *col);

static void	cylinder(t_hit *col, float absorption, float reflectivity)
{
	t_cylinder	*cyl;
	t_vec		clr;
	float		product;
	t_vec		to_center;
	t_vec		to_new;
	t_vec		diffuse;
	t_vec		specular;

	cyl = (t_cylinder *)col->obj;
	if (col->caps == false)
	{
		to_center.vec3 = col->location.vec3 - cyl->center.vec3;
		product = dot(to_center, cyl->orientation);
		to_new.vec3 = cyl->center.vec3 + product * cyl->orientation.vec3;
		set_vector(&col->surface_norm, &to_new, &col->location);
	}
	clr = cylinder_texture(cyl, &col->location);
	specular = reflection_result(col->colour, vec(1, 1, 1), reflectivity);
	diffuse = reflection_result(col->colour, clr, absorption);
	if (col->type == LIGHT)
		col->colour = reflection_result(col->colour, clr, 1);
	else
		col->colour = combine_colours(specular, diffuse);
}

static void	plane(t_hit *col, float absorption, float reflectivity)
{
	t_plane	*plane;
	t_vec	clr;
	t_vec	diffuse;
	t_vec	specular;

	plane = (t_plane *)col->obj;
	clr = plane_texture(plane, col->location);
	col->obj_num = plane->instance;
	specular = reflection_result(col->colour, vec(1, 1, 1), reflectivity);
	diffuse = reflection_result(col->colour, clr, absorption);
	if (col->type == LIGHT)
		col->colour = reflection_result(col->colour, clr, 1);
	else
		col->colour = combine_colours(specular, diffuse);
}

static void	sphere(t_hit *col, float absorption, float reflectivity)
{
	t_sphere	*sphere;
	t_vec		clr;
	t_vec		diffuse;
	t_vec		specular;

	sphere = (t_sphere *)col->obj;
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	col->obj_num = sphere->instance;
	clr = sphere_texture(sphere, &col->surface_norm);
	specular = reflection_result(col->colour, vec(1, 1, 1), reflectivity);
	// puts("Specular");
	// print_vector(specular);
	diffuse = reflection_result(col->colour, clr, absorption);
	// puts("Diffuse");
	// print_vector(specular);
	if (col->type == LIGHT)
		col->colour = reflection_result(col->colour, clr, 1);
	else
		col->colour = combine_colours(specular, diffuse);
	// puts("Result");
	// print_vector(col->colour);
}

void	draw_collision(t_hit *col, float absorption, float reflectivity)
{
	static void	(*ptr[4])(t_hit *, float, float) = \
		{&cylinder, &plane, &sphere, &sphere};

	if (col->hit == false)
	{
		col->colour = vec(0, 0, 0);
		return ;
	}
	ptr[col->type](col, absorption, reflectivity);
	col->location.vec3 += OFFSET * col->surface_norm.vec3;
}

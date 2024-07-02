/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/07/01 13:55:34 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	cylinder(t_hit *col, t_vec incoming, float diffuse, float specular)
{
	t_cylinder	*cyl;
	t_vec		clr;
	float		product;
	t_vec		to_center;
	t_vec		to_new;
	t_vec		diff;
	t_vec		spec;

	(void)incoming;
	cyl = (t_cylinder *)col->obj;
	if (col->caps == false)
	{
		to_center.vec3 = col->location.vec3 - cyl->center.vec3;
		product = dot(to_center, cyl->orientation);
		to_new.vec3 = cyl->center.vec3 + product * cyl->orientation.vec3;
		set_vector(&col->surface_norm, &to_new, &col->location);
	}
	if (col->inside_obj == true)
		col->surface_norm.vec3 *= -1;
	clr = cylinder_texture(cyl, &col->location);
	diff = reflection_result(clr, col->colour, diffuse);
	spec.vec3 = col->colour.vec3 * specular;
	col->colour.vec3 = diff.vec3 + spec.vec3;
}

static void	disc(t_hit *col, t_vec incoming, float diffuse, float specular)
{
	t_disc	*disc;
	t_vec	clr;
	t_vec	diff;
	t_vec	spec;

	(void)incoming;
	disc = (t_disc *)col->obj;
	clr = disc->colour;
	col->obj_num = disc->instance;
	diff = reflection_result(clr, col->colour, diffuse);
	spec.vec3 = col->colour.vec3 * specular;
	col->colour.vec3 = diff.vec3 + spec.vec3;
}

static void	plane(t_hit *col, t_vec incoming, float diffuse, float specular)
{
	t_plane	*plane;
	t_vec	clr;
	t_vec	diff;
	t_vec	spec;

	(void)incoming;
	plane = (t_plane *)col->obj;
	clr = plane_texture(plane, col->location);
	col->obj_num = plane->instance;
	diff = reflection_result(clr, col->colour, diffuse);
	spec.vec3 = col->colour.vec3 * specular;
	col->colour.vec3 = diff.vec3 + spec.vec3;
}

static void	sphere(t_hit *col, t_vec incoming, float diffuse, float specular)
{
	t_sphere	*sphere;
	t_vec		clr;
	// t_vec		diff;
	// t_vec		spec;
	(void)specular;
	(void)diffuse;
	sphere = (t_sphere *)col->obj;
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	col->obj_num = sphere->instance;
	if (col->inside_obj == true)
		col->surface_norm.vec3 *= -1;
	clr = sphere_texture(sphere, col->surface_norm);
	if (col->glossy_bounce == true)
		return ;
	col->colour = reflection_result(clr, col->colour, 1);
	if (sphere->object == LIGHT)
	{
		col->surface_norm.vec3 *= -1;
		col->colour.vec3 *= dot(incoming, col->surface_norm);
		return ;
	}
	// spec.vec3 = col->colour.vec3 * specular;
	// diff = reflection_result(clr, col->colour, diffuse);
	// col->colour.vec3 = diff.vec3 + spec.vec3;
}

void	draw_collision(t_hit *col, t_vec incoming, float diffuse, float specular)
{
	static void	(*ptr[5])(t_hit *, t_vec, float, float) = {&cylinder, &disc, &plane, &sphere, &sphere};

	if (col->hit == false)
	{
		col->colour = vec(0, 0, 0);
		return ;
	}
	// if (col->glossy_bounce == true)
	// 	return ;
	ptr[col->type](col, incoming, diffuse, specular);
	col->location.vec3 += OFFSET * col->surface_norm.vec3;
}

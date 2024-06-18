/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/06/18 18:23:12 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	cylinder(t_hit *col, float absorption, float reflectivity)
{
	t_cylinder	*cyl;
	t_vec		clr;
	float		product;
	t_vec		to_center;
	t_vec		to_new;

	(void)absorption;
	(void)reflectivity;
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
	col->colour = reflection_result(clr, col->colour, 1);
}

static void	plane(t_hit *col, float absorption, float reflectivity)
{
	t_plane	*plane;
	t_vec	clr;
	t_vec		diffuse;
	t_vec		specular;

	plane = (t_plane *)col->obj;
	clr = plane_texture(plane, col->location);
	col->obj_num = plane->instance;
	diffuse = reflection_result(clr, col->colour, absorption);
	specular.vec3 = col->colour.vec3 * reflectivity;
	col->colour.vec3 = diffuse.vec3 + specular.vec3;
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
	if (col->inside_obj == true)
		col->surface_norm.vec3 *= -1;
	clr = sphere_texture(sphere, col->surface_norm);
	diffuse = reflection_result(clr, col->colour, absorption);
	specular.vec3 = col->colour.vec3 * reflectivity;
	col->colour.vec3 = diffuse.vec3 + specular.vec3;
}

void	draw_collision(t_hit *col, float absorption, float reflectivity)
{
	static void	(*ptr[4])(t_hit *, float, float) = {&cylinder, &plane, &sphere, &sphere};

	if (col->hit == false)
	{
		col->colour = vec(0, 0, 0);
		return ;
	}
	ptr[col->type](col, absorption, reflectivity);
	col->location.vec3 += OFFSET * col->surface_norm.vec3;
}

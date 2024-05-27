/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/27 17:39:27 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	checkerboard_tex(t_data *data, t_sphere *sphere, t_hit *col);

static void	cylinder(t_hit *col, float reflection)
{
	t_cylinder	*cyl;
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
	clr = cylinder_texture(cyl, &col->location);
	col->obj_num = cyl->instance;
	col->colour = reflection_result(col->colour, clr, reflection);
}

static void	plane(t_hit *col, float reflection)
{
	t_plane	*plane;
	t_vec	clr;

	plane = (t_plane *)col->obj;
	clr = plane_texture(plane, &col->surface_norm);
	col->obj_num = plane->instance;
	col->colour = reflection_result(col->colour, clr, reflection);
}

static void	sphere(t_hit *col, float reflection)
{
	t_sphere	*sphere;
	t_vec		clr;

	sphere = (t_sphere *)col->obj;
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	col->obj_num = sphere->instance;
	clr = sphere_texture(sphere, &col->surface_norm);
	if (col->type == LIGHT)
		col->colour = reflection_result(col->colour, clr, 1);
	else
		col->colour = reflection_result(col->colour, clr, reflection);
}

void	draw_collision(t_hit *col, float reflection)
{
	static void	(*ptr[4])(t_hit *, float) = \
		{&cylinder, &plane, &sphere, &sphere};

	if (col->hit == false)
	{
		col->colour = vec(0, 0, 0);
		return ;
	}
	ptr[col->type](col, reflection);
	col->location.vec3 += OFFSET * col->surface_norm.vec3;
}

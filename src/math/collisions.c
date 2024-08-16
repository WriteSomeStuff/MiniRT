/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/08/16 13:14:01 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	cylinder(t_hit *col, t_vec incoming)
{
	t_cylinder	*cyl;
	t_vec		clr;
	float		product;
	t_vec		to_center;
	t_vec		to_new;

	(void)incoming;
	cyl = (t_cylinder *)col->obj;
	col->obj_num = cyl->instance;
	if (col->caps == false)
	{
		to_center.vec3 = col->location.vec3 - cyl->center.vec3;
		product = dot(to_center, cyl->orientation);
		to_new.vec3 = cyl->center.vec3 + product * cyl->orientation.vec3;
		set_vector(&col->surface_norm, &to_new, &col->location);
		if (col->inside_obj == true)
			col->surface_norm = inverted(col->surface_norm);
	}
	clr = get_object_colour(col);
	if (col->glossy_bounce == false)
		col->colour = reflection_result(clr, col->colour, 1);
}

static void	disc(t_hit *col, t_vec incoming)
{
	t_disc	*disc;
	t_vec	clr;

	(void)incoming;
	disc = (t_disc *)col->obj;
	clr = disc->colour;
	col->obj_num = disc->instance;
	if (col->glossy_bounce == false)
		col->colour = reflection_result(clr, col->colour, 1);
}

static void	plane(t_hit *col, t_vec incoming)
{
	t_plane	*plane;
	t_vec	clr;

	(void)incoming;
	plane = (t_plane *)col->obj;
	clr = get_object_colour(col);
	col->obj_num = plane->instance;
	if (col->glossy_bounce == false)
		col->colour = reflection_result(clr, col->colour, 1);
}

static void	sphere(t_hit *col, t_vec incoming)
{
	t_sphere	*sphere;
	t_vec		clr;

	sphere = (t_sphere *)col->obj;
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	col->obj_num = sphere->instance;
	if (col->inside_obj == true)
		col->surface_norm = inverted(col->surface_norm);
	clr = get_object_colour(col);
	if (col->type == LIGHT)
	{
		col->colour = reflection_result(clr, col->colour, 1);
		col->colour.vec3 *= max(dot(incoming, inverted(col->surface_norm)), \
			0.1f);
		return ;
	}
	if (col->glossy_bounce == false)
		col->colour = reflection_result(clr, col->colour, 1);
}

void	draw_collision(t_hit *col, t_vec incoming)
{
	static void	(*ptr[6])(t_hit *, t_vec) = {&cone, &cylinder, &disc, &plane, \
		&sphere, &sphere};

	if (col->hit == false)
	{
		col->colour = vec(0, 0, 0);
		return ;
	}
	ptr[col->type](col, incoming);
	col->location.vec3 += OFFSET * col->surface_norm.vec3;
}

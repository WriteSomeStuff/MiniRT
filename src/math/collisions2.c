/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:13:29 by cschabra      #+#    #+#                 */
/*   Updated: 2024/08/16 13:15:14 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	cone_normal(t_hit *col, t_cone *cone)
{
	t_vec	apex_to_point;
	t_vec	projection;
	t_vec	radial;
	t_vec	normal;
	float	projection_length;

	apex_to_point.vec3 = col->location.vec3 - cone->apex.vec3;
	projection_length = dot(apex_to_point, cone->orientation);
	projection.vec3 = cone->orientation.vec3 * projection_length;
	radial.vec3 = apex_to_point.vec3 - projection.vec3;
	normal.vec3 = radial.vec3 * (float)cos(cone->angle) + \
		cone->orientation.vec3 * (float)sin(cone->angle);
	return (normalize_vector(normal));
}

void	cone(t_hit *col, t_vec incoming)
{
	t_cone	*cone;
	t_vec	clr;

	(void)incoming;
	cone = (t_cone *)col->obj;
	col->obj_num = cone->instance;
	if (col->caps == false)
	{
		col->surface_norm = cone_normal(col, cone);
		if (col->inside_obj == true)
			col->surface_norm = inverted(col->surface_norm);
	}
	clr = get_object_colour(col);
	if (col->glossy_bounce == false)
		col->colour = reflection_result(clr, col->colour, 1);
}

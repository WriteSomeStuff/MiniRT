/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cone.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 13:39:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/08/01 14:29:14 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	get_quad_coeff(t_vec dir, t_vec origin, float tan2, const t_cone *c)
{
	t_vec	quad_coeff;
	t_vec	to_cone;

	to_cone.vec3 = c->apex.vec3 - origin.vec3;	
	quad_coeff.x = dir.x * dir.x + dir.z * dir.z - tan2 * dir.y * dir.y;
	quad_coeff.y = 2.0f * (to_cone.x * dir.x + to_cone.z * dir.z - tan2 * to_cone.y * dir.y);
	quad_coeff.z = to_cone.x * to_cone.x + to_cone.z * to_cone.z - tan2 * to_cone.y * to_cone.y;
	return (quad_coeff);
}

void	intersect_cones(t_hit *col, t_ray *ray, const t_cone *c)
{
	t_vec	to_cone;
	t_vec	quad_coeff;
	t_vec	intersection;
	t_vec	to_apex;
	float	res[2];

	while (c->object != INVALID)
	{
		quad_coeff = get_quad_coeff(ray->direction, \
			ray->origin, pow(tan(c->angle), 2), c);
		if (quadratic_equation(&quad_coeff, &res[0], &res[1]) == true && \
			analyze_intersection(&res[0], &res[1]) == true && \
			res[0] < col->distance)
		{
			to_apex.vec3 = ray->direction.vec3 * res[0] \
				+ ray->origin.vec3 - c->apex.vec3;
			if (fabs(dot(to_apex, c->orientation) <= c->height))
			{
				update(ray, CONE, (void *)c, res[0]);
				col->specular = c->specular;
				col->glossiness = c->glossiness;
				if (res[1] <= 0.0f)
					col->inside_obj = true;
				else
					col->inside_obj = false;
			}
		}
		c++;
	}
}
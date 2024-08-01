/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 11:57:27 by vincent       #+#    #+#                 */
/*   Updated: 2024/08/01 13:50:50 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	intersect_spheres(t_hit *col, t_ray *ray, const t_sphere *s)
{
	t_vec	to_sphere;
	t_vec	quad_coeff;
	float	res[2];

	quad_coeff.x = 1.0f;
	while (s->object != INVALID)
	{
		to_sphere.vec3 = s->center.vec3 - ray->origin.vec3;
		quad_coeff.y = 2.0f * -dot(to_sphere, ray->direction);
		quad_coeff.z = dot(to_sphere, to_sphere) - pow(s->radius, 2);
		if (quadratic_equation(&quad_coeff, &res[0], &res[1]) == true && \
			analyze_intersection(&res[0], &res[1]) == true && \
			res[0] < col->distance)
		{
			update(ray, s->object, (void *)s, res[0]);
			col->specular = s->specular;
			col->glossiness = s->glossiness;
			if (res[1] <= 0.0f)
				col->inside_obj = true;
			else
				col->inside_obj = false;
		}
		s++;
	}
}

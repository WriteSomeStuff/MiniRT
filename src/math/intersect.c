/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 16:29:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/21 16:55:04 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	intersect_sphere(t_ray *ray, const t_sphere *sphere)
{
	t_hit	collision;
	t_vec	dir_to_sphere_center;
	t_vec	tmp;
	float	res_a;
	float	res_b;

	dir_to_sphere_center.vec3 = ray->origin.vec3 - sphere->center.vec3;
	ft_bzero(&collision, sizeof(t_hit));
	tmp.x = 1.0f;
	tmp.y = 2.0f * dot_product(&dir_to_sphere_center, &ray->direction);
	tmp.z = dot_product(&dir_to_sphere_center, &dir_to_sphere_center) - sphere->radius * sphere->radius;
	if (quadratic_equation(&tmp, &res_a, &res_b) == true)
	{
		if ((res_a < 0 && res_b >= 0) || (res_b < 0 && res_a >= 0))
		{
			collision.inside_object = true;
			return (collision);
		}
		if (res_a < 0 && res_b < 0)
			return (collision);
		collision.hit = true;
		if (res_a <= res_b && res_a >= 0)
			collision.distance = res_a;
		else
			collision.distance = res_b;
		collision.location = scale_vector(&ray->direction, collision.distance);
		collision.location.vec3 = collision.location.vec3 + ray->origin.vec3;
	}
	return (collision);
}

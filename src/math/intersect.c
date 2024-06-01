/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 16:29:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/06/01 12:58:50 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	als we binnenin objects willen wordt de surface normal andersom	*/

bool	analyze_intersection(float *a, float *b)
{
	float	tmp;

	if (*b < 0)
		return (false);
	if (*a < 0 && *b > OFFSET)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
	return (true);
}

void	update(t_ray *ray, t_token type, void *obj, float distance)
{
	ray->col->hit = true;
	ray->col->distance = distance;
	ray->col->location.vec3 = ray->direction.vec3 * distance;
	ray->col->location.vec3 += ray->origin.vec3;
	ray->col->obj = obj;
	ray->col->type = type;
}

void find_closest_object(t_data *data, t_hit *col, t_ray *ray)
{
	col->type = INVALID;
	col->hit = false;
	col->distance = FLT_MAX;
	intersect_cylinders(col, ray, data->cyls);
	intersect_planes(col, ray, data->planes);
	intersect_spheres(col, ray, data->spheres);
	col->absorption = 1 - col->reflectivity;
}

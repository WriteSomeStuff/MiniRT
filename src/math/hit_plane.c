/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_plane.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 11:57:24 by vincent       #+#    #+#                 */
/*   Updated: 2024/07/01 12:14:19 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	hit_flat_surface(float *distance, t_ray *ray, t_vec point, t_vec orientation)
{
	t_vec	to_plane;
	float	denom;

	denom = dot(ray->direction, orientation);
	to_plane.vec3 = point.vec3 - ray->origin.vec3;
	if (fabs(denom) < OFFSET)
		return (0.0f);
	*distance = dot(to_plane, orientation) / denom;
	return (denom);
}

void	intersect_planes(t_hit *col, t_ray *ray, const t_plane *p)
{
	float	denom;
	float	distance;

	while (p->object != INVALID)
	{
		denom = hit_flat_surface(&distance, ray, p->location, p->orientation);
		if (denom != 0.0f && distance > 0 && distance < col->distance)
		{
			update(ray, PLANE, (void *)p, distance);
			col->specular = p->specular;
			col->glossiness = p->glossiness;
			if (denom > 0)
				col->surface_norm = p->rev_norm;
			else
				col->surface_norm = p->orientation;
		}
		p++;
	}
}

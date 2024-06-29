/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_disc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 11:57:24 by vincent       #+#    #+#                 */
/*   Updated: 2024/06/29 15:44:09 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	intersect_discs(t_hit *col, t_ray *ray, const t_disc *d)
{
	float	denom;
	float	distance;
	float	distance_to_center;
	t_vec	intersection;

	while (d->object != INVALID)
	{
		denom = hit_flat_surface(&distance, ray, d->center, d->orientation);
		if (denom != 0.0f && distance > 0 && distance < col->distance)
		{
			intersection.vec3 = ray->direction.vec3 * distance + ray->origin.vec3;
			distance_to_center = vector_length(d->center, intersection);
			if (distance_to_center >= d->hole_radius && distance_to_center <= d->radius)
			{
				update(ray, DISC, (void *)d, distance);
				col->reflectivity = d->reflectivity;
				if (denom > 0)
					col->surface_norm = d->rev_norm;
				else
					col->surface_norm = d->orientation;
			}
		}
		d++;
	}
}

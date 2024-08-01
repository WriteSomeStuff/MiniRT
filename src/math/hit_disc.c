/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_disc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 11:57:24 by vincent       #+#    #+#                 */
/*   Updated: 2024/07/30 13:30:57 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	intersect_discs(t_hit *col, t_ray *ray, const t_disc *d)
{
	float	denom;
	float	distance;
	t_vec	intersection;

	while (d->object != INVALID)
	{
		denom = hit_flat_surface(&distance, ray, d->center, d->orientation);
		if (denom != 0.0f && distance > 0 && distance < col->distance)
		{
			intersection.vec3 = ray->direction.vec3 * distance \
				+ ray->origin.vec3;
			if (vector_length(d->center, intersection) >= d->hole_radius && \
				vector_length(d->center, intersection) <= d->radius)
			{
				update(ray, DISC, (void *)d, distance);
				col->specular = d->specular;
				col->glossiness = d->glossiness;
				if (denom > 0)
					col->surface_norm = d->rev_norm;
				else
					col->surface_norm = d->orientation;
			}
		}
		d++;
	}
}

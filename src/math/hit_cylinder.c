/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 11:57:22 by vincent       #+#    #+#                 */
/*   Updated: 2024/06/01 13:44:45 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	hit_bot_cap(t_hit *col, t_ray *ray, const t_cylinder *c, float *hits)
{
	t_vec	intersection;
	float	denom;
	float	distance;

	denom = hit_flat_surface(&distance, ray, c->base, c->orientation);
	hits[0] = distance;
	if (denom != 0.0f)
	{
		intersection.vec3 = ray->direction.vec3 * distance + ray->origin.vec3;
		if (vector_length(intersection, c->base) <= c->radius)
		{
			if (distance > 0 && distance < col->distance)
			{
				update(ray, CYLINDER, (void *)c, distance);
				col->reflectivity = c->reflectivity;
				col->surface_norm.vec3 = c->orientation.vec3 * -1;
				col->caps = true;
			}
		}
	}
}

static void	hit_top_cap(t_hit *col, t_ray *ray, const t_cylinder *c, float *hits)
{
	t_vec	intersection;
	float	denom;
	float	distance;

	denom = hit_flat_surface(&distance, ray, c->top, c->orientation);
	hits[1] = distance;
	if (denom != 0.0f)
	{
		intersection.vec3 = ray->direction.vec3 * distance + ray->origin.vec3;
		if (vector_length(intersection, c->top) <= c->radius)
		{
			if (distance > 0 && distance < col->distance)
			{
				update(ray, CYLINDER, (void *)c, distance);
				col->reflectivity = c->reflectivity;
				col->surface_norm.vec3 = c->orientation.vec3 * -1;
				col->caps = true;
			}
		}
	}
}

static void	hit_body(t_hit *col, t_ray *ray, const t_cylinder *c, float *hits)
{
	t_vec	rc_cross;
	t_vec	cyl_cross;
	t_vec	to_center;
	t_vec	tmp;

	rc_cross = cross(c->orientation, ray->direction);
	cyl_cross.vec3 = c->center.vec3 - ray->origin.vec3;
	cyl_cross = cross(cyl_cross, c->orientation);
	tmp.x = dot(rc_cross, rc_cross);
	tmp.y = 2.0f * dot(rc_cross, cyl_cross);
	tmp.z = dot(cyl_cross, cyl_cross) - pow(c->radius, 2);
	if (quadratic_equation(&tmp, &hits[2], &hits[3]) == true)
	{
		if (analyze_intersection(&hits[2], &hits[3]) == true)
		{
			to_center.vec3 = ray->direction.vec3 * hits[2] + ray->origin.vec3 - c->center.vec3;
			if (fabs(dot(to_center, c->orientation)) <= c->height / 2)
			{
				update(ray, CYLINDER, (void *)c, hits[2]);
				col->reflectivity = c->reflectivity;
				col->caps = false;
			}
		}
	}
}

void	intersect_cylinders(t_hit *col, t_ray *ray, const t_cylinder *c)
{
	float	hits[4];

	while (c->object != INVALID)
	{
		ft_bzero(&hits[0], 4 * sizeof(float));
		hit_bot_cap(col, ray, c, &hits[0]);
		hit_top_cap(col, ray, c, &hits[0]);
		hit_body(col, ray, c, &hits[0]);
		if ((t_cylinder *)ray->col->obj == c)
		{
			if (hits[0] < 0 || hits[1] < 0 || hits[2] < 0 || hits[3] < 0)
				col->inside_obj = true;
		}
		c++;
	}
}
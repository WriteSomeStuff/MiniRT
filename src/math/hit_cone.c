/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cone.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 13:39:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/08/13 17:34:52 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	get_quad_coeff(t_vec dir, t_vec origin, const t_cone *c)
{
	float	adjustment;
	float	dot_wh;
	float	dottydot;
	t_vec	quad_coeff;
	t_vec	to_cone;

	adjustment = pow(c->radius, 2) / pow(c->height, 2);
	to_cone.vec3 = origin.vec3 - c->apex.vec3;
	dottydot = dot(dir, c->orientation);
	dot_wh = dot(to_cone, c->orientation);
	quad_coeff.x = 1 - adjustment * pow(dottydot, 2) - pow(dottydot, 2);
	quad_coeff.y = 2.0f * (dot(dir, to_cone) - adjustment * dottydot * \
		dot_wh - dottydot * dot_wh);
	quad_coeff.z = dot(to_cone, to_cone) - adjustment * pow(dot_wh, 2) - \
		pow(dot_wh, 2);
	return (quad_coeff);
}

static void	hit_body(t_hit *col, t_ray *ray, const t_cone *c, float *hits)
{
	t_vec	quad_coeff;
	t_vec	to_center;

	quad_coeff = get_quad_coeff(ray->direction, \
		ray->origin, c);
	if (quadratic_equation(&quad_coeff, &hits[1], &hits[2]) == true && \
		analyze_intersection(&hits[1], &hits[2]) == true && \
		hits[1] < col->distance)
	{
		to_center.vec3 = ray->direction.vec3 * hits[1] + \
			ray->origin.vec3 - c->apex.vec3 + (c->orientation.vec3 * c->height \
			/ 2);
		if (fabs(dot(to_center, c->orientation)) <= c->height / 2)
		{
			update(ray, CONE, (void *)c, hits[1]);
			col->specular = c->specular;
			col->glossiness = c->glossiness;
			col->caps = false;
		}
	}
}

static void	hit_base(t_hit *col, t_ray *ray, const t_cone *c, float *hits)
{
	t_vec	intersection;
	float	denom;
	float	distance;

	denom = hit_flat_surface(&distance, ray, c->base, c->orientation);
	if (fabs(denom) > OFFSET)
	{
		intersection.vec3 = ray->direction.vec3 * distance + ray->origin.vec3;
		if (vector_length(intersection, c->base) <= c->radius)
		{
			hits[0] = distance;
			if (distance > 0 && distance < col->distance)
			{
				update(ray, CONE, (void *)c, distance);
				col->specular = c->specular;
				col->glossiness = c->glossiness;
				if (denom > 0)
					col->surface_norm = inverted(c->orientation);
				else
					col->surface_norm = c->orientation;
				col->caps = true;
			}
		}
	}
}

void	intersect_cones(t_hit *col, t_ray *ray, const t_cone *c)
{
	float	hits[3];

	while (c->object != INVALID)
	{
		ft_bzero(&hits[0], 3 * sizeof(float));
		hit_body(col, ray, c, hits);
		hit_base(col, ray, c, hits);
		if ((t_cone *)ray->col->obj == c)
		{
			if (hits[0] < 0 || hits[1] < 0 || hits[2] < 0)
			{
				printf("0: %f\n1: %f\n2: %f\n", hits[0], hits[1], hits[2]);
				col->inside_obj = true;
			}
			else
				col->inside_obj = false;
		}
		c++;
	}
}

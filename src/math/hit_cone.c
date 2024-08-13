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

/* int	intersect_entire_cone(t_ray *ray, t_cone *cone, t_quadratic *f)
{
	t_vec	w;
	double	m;
	double	dot_ray_dir_h;
	double	dot_w_h;
	double	dot_w_h_squared;

	// m = pow2(cone->radius) / pow2(cone->height);
	// w = sub(ray->origin, cone->top);
	// dot_ray_dir_h = dot(&(ray->dir), &(cone->dir));
	// dot_w_h = dot(&w, &(cone->dir));
	// dot_w_h_squared = pow2(dot_w_h);
	f->a = 1 - m * pow2(dot_ray_dir_h) - pow2(dot_ray_dir_h);
	f->b = 2 * (dot(&(ray->dir), &w) - m
			* dot_ray_dir_h * dot_w_h - dot_ray_dir_h * dot_w_h);
	f->c = dot(&w, &w) - m * dot_w_h_squared - dot_w_h_squared;
	return (solve_quadratic(f));
}

int	intersect_cone(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_quadratic	f;
	t_cone		*cone;
	double		t_base;

	cone = (t_cone *)shape;
	if (!intersect_entire_cone(ray, cone, &f))
		return (0);
	if (dot(&(cone->dir), &(ray->dir)) >= 0)
	{
		*t = get_closest_intersection(f.t_1, f.t_2);
		cut_cone_surface(cone, get_ray_point(*ray, *t), t);
	}
	else
	{
		cut_cone_surface(cone, get_ray_point(*ray, f.t_1), &f.t_1);
		cut_cone_surface(cone, get_ray_point(*ray, f.t_2), &f.t_2);
		*t = get_closest_intersection(f.t_1, f.t_2);
	}
	intersect_circle(ray, (void *)&(cone->base), &t_base, NULL);
	*t = get_closest_intersection(*t, t_base);
	if (is_surface_hit != NULL)
		*is_surface_hit = *t != t_base;
	return (*t > 0.0);
} */

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
	
	quad_coeff.y = 2.0f * (dot(dir, to_cone) - adjustment * dottydot * dot_wh - dottydot * dot_wh);
	
	quad_coeff.z = dot(to_cone, to_cone) - adjustment * pow(dot_wh, 2) - pow(dot_wh, 2);
	return (quad_coeff);
}

static void	hit_body(t_hit *col, t_ray *ray, const t_cone *c, float *hits)
{
	t_vec	quad_coeff;
	t_vec	to_center;

	quad_coeff = get_quad_coeff(ray->direction, \
		ray->origin, c);
	if (quadratic_equation(&quad_coeff, &hits[0], &hits[1]) == true && \
		analyze_intersection(&hits[0], &hits[1]) == true && \
		hits[0] < col->distance)
	{
		to_center.vec3 = ray->direction.vec3 * hits[0] \
			+ ray->origin.vec3 - c->apex.vec3 + (c->orientation.vec3 * c->height / 2);
		if (fabs(dot(to_center, c->orientation)) <= c->height / 2)
		{
			update(ray, CONE, (void *)c, hits[0]);
			col->specular = c->specular;
			col->glossiness = c->glossiness;
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
			hits[2] = distance;
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
				col->inside_obj = true;
			else
				col->inside_obj = false;
		}
		c++;
	}
}

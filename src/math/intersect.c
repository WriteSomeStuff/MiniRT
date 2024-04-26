/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 16:29:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/26 15:15:55 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	als we binnenin objects willen wordt de surface normal andersom	*/

static bool	analyze_intersection(t_hit *col, float *a, float *b)
{
	if (*b < 0)
		return (false);
	if (*a < 0 && *b > 0.0001)
	{
		col->inside_obj = true;
		*a = *b;
	}
	return (true);
}

static void	update(t_ray *ray, t_token type, void *obj, float distance)
{
	ray->col->hit = true;
	ray->col->distance = distance;
	ray->col->location.vec3 = ray->direction.vec3 * distance;
	ray->col->location.vec3 += ray->origin.vec3;
	ray->col->obj = obj;
	ray->col->type = type;
}

static void	hit_body(t_hit *col, t_ray *ray, const t_cylinder *c)
{
	t_vec	rc_cross;
	t_vec	cyl_cross;
	t_vec	to_center;
	t_vec	tmp;
	float	res[2];

	rc_cross = cross_product(&c->orientation, &ray->direction);
	cyl_cross.vec3 = c->center.vec3 - ray->origin.vec3;
	cyl_cross = cross_product(&cyl_cross, &c->orientation);
	tmp.x = dot(&rc_cross, &rc_cross);
	tmp.y = 2.0f * dot(&rc_cross, &cyl_cross);
	tmp.z = dot(&cyl_cross, &cyl_cross) - pow(c->radius, 2);
	if (quadratic_equation(&tmp, &res[0], &res[1]) == true)
	{
		if (analyze_intersection(col, &res[0], &res[1]) == true)
		{
			to_center.vec3 = ray->direction.vec3 * res[0] + ray->origin.vec3 - c->center.vec3;
			if (fabs(dot(&to_center, &c->orientation)) <= c->height)
				update(ray, CYLINDER, (void *)c, res[0]);
		}
	}
}

// static void	hit_caps(t_hit *col, t_ray *ray, const t_cylinder *c)
// {
	
// }

void	intersect_cylinders(t_hit *col, t_ray *ray, const t_cylinder *c)
{
	while (c->object != INVALID)
	{
		hit_body(col, ray, c);
		// hit_caps(col, ray, c);
		c++;
	}
}

static void	intersect_planes(t_hit *col, t_ray *ray, const t_plane *p)
{
	t_vec	tmp;
	float	distance;
	float	denom;

	while (p->object != INVALID)
	{
		denom = dot(&ray->direction, &p->orientation);
		tmp.vec3 = p->location.vec3 - ray->origin.vec3;
		if (fabs(denom) > 0.0001)
		{
			distance = dot(&tmp, &p->orientation) / denom;
			if (distance > 0 && distance < col->distance)
			{
				update(ray, PLANE, (void *)p, distance);
				if (denom > 0)
					col->surface_norm = p->rev_norm;
				else
					col->surface_norm = p->orientation;
			}
		}
		p++;
	}
}


static void	intersect_spheres(t_hit *col, t_ray *ray, const t_sphere *s)
{
	t_vec	to_sphere;
	t_vec	tmp;
	float	res[2];

	tmp.x = 1.0f;
	while (s->object != INVALID)
	{
		to_sphere.vec3 = ray->origin.vec3 - s->center.vec3;
		tmp.y = 2.0f * dot(&to_sphere, &ray->direction);
		tmp.z = dot(&to_sphere, &to_sphere) - pow(s->radius, 2);
		if (quadratic_equation(&tmp, &res[0], &res[1]) == true)
		{
			if (analyze_intersection(col, &res[0], &res[1]) == true)
				update(ray, SPHERE, (void *)s, res[0]);
		}
		s++;
	}
}

void find_closest_object(t_data *data, t_hit *col, t_ray *ray)
{
	ft_bzero(col, sizeof(t_hit));
	col->type = INVALID;
	col->distance = FLT_MAX;
	intersect_cylinders(col, ray, data->cyls);
	intersect_planes(col, ray, data->planes);
	intersect_spheres(col, ray, data->spheres);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 16:29:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/15 18:55:36 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	als we binnenin objects willen wordt de surface normal andersom	*/

static void	update(t_ray *ray, t_token type, void *obj, float distance)
{
	ray->col->hit = true;
	ray->col->distance = distance;
	ray->col->location = scale_vector(&ray->direction, distance);
	ray->col->location.vec3 += ray->origin.vec3;
	ray->col->obj = obj;
	ray->col->type = type;
}

static void	hit_body(t_hit *col, t_ray *ray, const t_cylinder *c)
{
	t_vec	rc_cross;
	t_vec	cyl_cross;
	t_vec	tmp;
	float	res;

	rc_cross = cross_product(&c->orientation, &ray->direction);
	cyl_cross.vec3 = c->center.vec3 - ray->origin.vec3;
	cyl_cross = cross_product(&cyl_cross, &c->orientation);
	tmp.x = dot(&rc_cross, &rc_cross);
	tmp.y = 2.0f * dot(&rc_cross, &cyl_cross);
	tmp.z = dot(&cyl_cross, &cyl_cross) - pow(c->radius, 2);
	if (quadratic_equation(&tmp, &res) == true)
	{
		if (res > 0.0001 && res < col->distance)
		{
			t_vec to_center;

			to_center = scale_vector(&ray->direction, res);
			to_center.vec3 += ray->origin.vec3;
			to_center.vec3 = to_center.vec3 - c->center.vec3;
			// puts("to center");
			// print_vector(to_center);
			t_vec tmp;

			tmp.vec3 = c->orientation.vec3;
			float product = dot(&to_center, &c->orientation);
			if (fabs(product) <= c->height)
				update(ray, CYLINDER, (void *)c, res);
			// if (dot(&col->location, &c->base) <= c->height / 2)
			// check voor lengte van cylinder
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
	float	res;

	tmp.x = 1.0f;
	while (s->object != INVALID)
	{
		to_sphere.vec3 = ray->origin.vec3 - s->center.vec3;
		tmp.y = 2.0f * dot(&to_sphere, &ray->direction);
		tmp.z = dot(&to_sphere, &to_sphere) - pow(s->radius, 2);
		if (quadratic_equation(&tmp, &res) == true)
		{
			if (res > 0.0001 && res < col->distance)
				update(ray, SPHERE, (void *)s, res);
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

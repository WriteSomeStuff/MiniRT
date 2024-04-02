/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 16:29:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/02 18:02:54 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update(t_ray *ray, t_token type, void *obj, float distance)
{
	ray->col->hit = true;
	ray->col->distance = distance;
	ray->col->location = scale_vector(&ray->direction, distance);
	ray->col->location.vec3 += ray->origin.vec3;
	ray->col->obj = obj;
	ray->col->type = type;
}

void	intersect_cylinders(t_hit *col, t_ray *ray, const t_cylinder *c)
{
	t_vec	og_to_cyl;
	t_vec	tmp;
	t_vec	tmp2;
	float	res;
	float	m;

	while (c->object != INVALID)
	{
		og_to_cyl.vec3 = ray->origin.vec3 - c->center.vec3;
		tmp.x = dot(&ray->direction, &ray->direction) - pow(dot(&ray->direction, &c->orientation), 2);
		tmp.y = 2 * dot(&ray->direction, &og_to_cyl) - pow(dot(&ray->direction, &c->orientation), 2);
		tmp.z = dot(&og_to_cyl, &og_to_cyl) - pow(dot(&og_to_cyl, &c->orientation), 2) - pow(c->radius, 2);
		if (quadratic_equation(&tmp, &res) == true)
		{
			if (res < col->distance && res > 0.0001)
			{
				tmp2.vec3 = c->orientation.vec3 * res;
				m = dot(&ray->direction, &tmp2) + dot(&og_to_cyl, &c->orientation);
				if (fabs(m) < c->height)
					update(ray, CYLINDER, (void *)c, res);
			}
		}
		c++;
	}
}

static void	intersect_planes(t_hit *col, t_ray *ray, const t_plane *p)
{
	t_vec	tmp;
	float	distance;
	float	denominator;

	while (p->object != INVALID)
	{
		denominator = dot(&ray->direction, &p->orientation);
		if (denominator > 0.0001)
		{
			tmp.vec3 = p->location.vec3 - ray->origin.vec3;
			distance = dot(&tmp, &p->orientation);
			distance /= denominator;
			if (distance < col->distance)
			{
				update(ray, PLANE, (void *)p, distance);
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

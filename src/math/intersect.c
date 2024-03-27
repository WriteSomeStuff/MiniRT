/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 16:29:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/27 17:19:46 by vincent       ########   odam.nl         */
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

static void	intersect_cylinders(t_hit *col, t_ray *ray, const t_cylinder *cyl)
{
	(void)col;
	(void)ray;
	(void)cyl;
}

static void	intersect_planes(t_hit *col, t_ray *ray, const t_plane *p)
{
	t_vec	tmp;
	float	distance;
	float	denominator;

	while (p->object != INVALID)
	{
		denominator = dot_product(&ray->direction, &p->orientation);
		if (denominator > 0.01)
		{
			tmp.vec3 = p->location.vec3 - ray->origin.vec3;
			// print_vector(tmp);
			distance = dot_product(&tmp, &p->orientation) / denominator;
			// printf("distance: %f denominator: %f\n", distance, denominator);
			if (distance >= 0 && distance < col->distance)
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
	float	res_a;
	float	res_b;

	tmp.x = 1.0f;
	while (s->object != INVALID)
	{
		to_sphere.vec3 = ray->origin.vec3 - s->center.vec3;
		tmp.y = 2.0f * dot_product(&to_sphere, &ray->direction);
		tmp.z = dot_product(&to_sphere, &to_sphere) - s->radius * s->radius;
		if (quadratic_equation(&tmp, &res_a, &res_b) == true)
		{
			if ((res_a < 0 && res_b >= 0) || (res_b < 0 && res_a >= 0))
				col->inside_object = true;
			if (res_a < col->distance && res_a > 0)
				update(ray, SPHERE, (void *)s, res_a);
			if (res_b < col->distance && res_b > 0)
				update(ray, SPHERE, (void *)s, res_b);
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

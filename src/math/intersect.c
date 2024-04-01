/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 16:29:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/01 21:25:06 by vincent       ########   odam.nl         */
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

static void	check(float *min, float *max, float base, float top)
{
	if (base < top)
	{
		*min = base;
		*max = top;
	}
	else
	{
		*min = top;
		*max = base;
	}
}

static bool	initial_checks(t_ray *ray, const t_cylinder *c)
{
	t_vec	min;
	t_vec	max;

	check(&min.x, &max.x, c->base.x, c->top.x);
	check(&min.y, &max.y, c->base.y, c->top.y);
	check(&min.z, &max.z, c->base.z, c->top.z);
	min.vec3 -= c->radius;
	max.vec3 += c->radius;
}

static void	intersect_spheres(t_hit *col, t_ray *ray, const t_cylinder *c)
{
	if (c->base.z < c->top.z)
}

static void	intersect_cylinders(const Ogre::Vector3& start, const Ogre::Vector3& dir, const Ogre::Vector3& A, const Ogre::Vector3& B, const double r,
             const bool optimize, double& t, Ogre::Vector3& normal) {
  t = NaN;

  // Solution : http://www.gamedev.net/community/forums/topic.asp?topic_id=467789
  double cxmin, cymin, czmin, cxmax, cymax, czmax;
  if (A.z < B.z) { czmin = A.z - r; czmax = B.z + r; } else { czmin = B.z - r; czmax = A.z + r; }
  if (A.y < B.y) { cymin = A.y - r; cymax = B.y + r; } else { cymin = B.y - r; cymax = A.y + r; }
  if (A.x < B.x) { cxmin = A.x - r; cxmax = B.x + r; } else { cxmin = B.x - r; cxmax = A.x + r; }
  if (optimize) {
   if (start.z >= czmax && (start.z + dir.z) > czmax) return;
   if (start.z <= czmin && (start.z + dir.z) < czmin) return;
   if (start.y >= cymax && (start.y + dir.y) > cymax) return;
   if (start.y <= cymin && (start.y + dir.y) < cymin) return;
   if (start.x >= cxmax && (start.x + dir.x) > cxmax) return;
   if (start.x <= cxmin && (start.x + dir.x) < cxmin) return;
  }

  Ogre::Vector3 AB = B - A;
  Ogre::Vector3 AO = start - A;
  Ogre::Vector3 AOxAB = AO.crossProduct(AB);
  Ogre::Vector3 VxAB  = dir.crossProduct(AB);
  double ab2 = AB.dotProduct(AB);
  double a = VxAB.dotProduct(VxAB);
  double b = 2 * VxAB.dotProduct(AOxAB);
  double c = AOxAB.dotProduct(AOxAB) - (r*r * ab2);
  double d = b * b - 4 * a * c;
  if (d < 0) return;
  double time = (-b - sqrt(d)) / (2 * a);
  if (time < 0) return;

  Ogre::Vector3 intersection = start + dir * time;        /// intersection point
  Ogre::Vector3 projection = A + (AB.dotProduct(intersection - A) / ab2) * AB; /// intersection projected onto cylinder axis
  if ((projection - A).length() + (B - projection).length() > AB.length()) return; /// THIS IS THE SLOW SAFE WAY
  //if (projection.z > czmax - r || projection.z < czmin + r ||
  // projection.y > cymax - r || projection.y < cymin + r ||
  // projection.x > cxmax - r || projection.x < cxmin + r ) return; /// THIS IS THE FASTER BUGGY WAY

  normal = (intersection - projection);
  normal.normalise();
  t = time; /// at last
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
		// if negative then object is behind camera
		if (denominator > 0.0001)
		{
			tmp.vec3 = p->location.vec3 - ray->origin.vec3;
			distance = dot_product(&tmp, &p->orientation);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 16:29:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/13 18:30:14 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	calc_a(const t_vec *b)
{
	return (b->x * b->x + b->y * b->y + b->z * b->z);
}

static double	calc_b(const t_vec *a, const t_vec *b)
{
	return (2 * a->x * b->x + 2 * a->y * b->y + 2 * a->z * b->z);
}

static double	calc_c(const t_vec *a, const double radius)
{
	return (a->x * a->x + a->y * a->y + a->z * a->z - radius * radius);
}

// static double	calc_a(const t_vec *b)
// {
// 	return (b->x * b->x + b->y * b->y);
// }

// static double	calc_b(const t_vec *a, const t_vec *b)
// {
// 	return (2 * a->x * b->x + 2 * a->y * b->y);
// }

// static double	calc_c(const t_vec *a, const double radius)
// {
// 	return (a->x * a->x + a->y * a->y - radius * radius);
// }

t_hit	intersect_sphere(t_ray *ray, const t_sphere *sphere)
{
	t_hit	collision;
	t_vec	new_origin;
	t_vec	tmp;
	double	solution_a;
	double	solution_b;
	
	new_origin = subtract_vectors(&ray->origin, &sphere->center);
	ft_bzero(&collision, sizeof(t_hit));
	tmp.a = calc_a(&ray->direction);
	tmp.b = calc_b(&new_origin, &ray->direction);
	tmp.c = calc_c(&new_origin, sphere->radius);
	if (quadratic_equation(&tmp, &solution_a, &solution_b) == true)
	{
		collision.hit = true;
		printf("a: %lf, b: %lf\n", solution_a, solution_b);
		if (solution_a <= solution_b)
			collision.distance = solution_a;
		else
			collision.distance = solution_b;
		collision.location = scale_vector(&ray->direction, collision.distance);
		collision.location = add_vectors(&collision.location, &ray->origin);
	}
	return (collision);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maths.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 17:28:37 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/15 18:06:36 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	degree_to_radian(const float degree)
{
	return (degree * PI / 180);
}

float	radian_to_degree(const float radian)
{
	return (radian * 180 / PI);
}

float	pythagoras(const float a, const float b)
{
	return (sqrt(a * a + b * b));
}

float	pytha_inverse(const float c, const float a)
{
	return (sqrt(c * c - a * a));
}

bool	quadratic_equation(const t_vec *vec, float *a, float *b)
{
	float	root_abc;

	root_abc = vec->y * vec->y - 4 * vec->x * vec->z;
	if (root_abc < 0)
		return (false);
	root_abc = sqrt(root_abc);
	*a = (-vec->y + root_abc) / (2 * vec->x);
	*b = (-vec->y - root_abc) / (2 * vec->x);
	return (true);
}

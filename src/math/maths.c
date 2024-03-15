/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maths.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 17:28:37 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/15 17:35:01 by vvan-der      ########   odam.nl         */
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

bool	quadratic_equation(const t_vec *yo, float *a, float *b)
{
	float	thingy;

	thingy = yo->y * yo->y - 4 * yo->x * yo->z;
	if (thingy < 0)
		return (false);
	thingy = sqrt(thingy);
	*a = (-yo->y + thingy) / (2 * yo->x);
	*b = (-yo->y - thingy) / (2 * yo->x);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maths.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 17:28:37 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/13 15:48:40 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	radian_to_degree(const double radian)
{
	return (radian * 180 / PI);
}

double	degree_to_radian(const double degree)
{
	return (degree * PI / 180);
}

double	pythagoras(const double a, const double b)
{
	return (sqrt(a * a + b * b));
}

double	pytha_inverse(const double c, const double a)
{
	return (sqrt(c * c - a * a));
}

bool	quadratic_equation(const t_vec *yo, double *a, double *b)
{
	double	thingy;

	thingy = yo->y * yo->y - 4 * yo->x * yo->z;
	if (thingy < 0)
		return (false);
	thingy = sqrt(thingy);
	*a = (-yo->y + thingy) / (2 * yo->x);
	*b = (-yo->y - thingy) / (2 * yo->x);
	return (true);
}

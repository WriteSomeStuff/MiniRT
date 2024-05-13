/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maths.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 17:28:37 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/13 18:19:40 by vvan-der      ########   odam.nl         */
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

/*	Returns R.A.D.I.A.N.S	*/

float	angle(const t_vec a, const t_vec b)
{
	return (acos(dot(a, b)));
}

bool	quadratic_equation(const t_vec *vec, float *low, float *high)
{
	float	b_4ac;
	float	tmp;

	if (vec->x == 0)
		return (false);
	b_4ac = vec->y * vec->y - 4 * vec->x * vec->z;
	if (b_4ac < 0)
		return (false);
	b_4ac = sqrt(b_4ac);
	*low = (-vec->y + b_4ac) / (2 * vec->x);
	*high = (-vec->y - b_4ac) / (2 * vec->x);
	if (*high < *low)
	{
		tmp = *high;
		*high = *low;
		*low = tmp;
	}
	return (true);
}

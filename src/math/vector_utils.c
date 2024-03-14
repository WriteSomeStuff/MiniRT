/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 11:09:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/14 14:24:29 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	length(const float x, const float y)
{
	return (fabs(x - y));
}

float	vector_length(const t_vec *origin, const t_vec *vector)
{
	float	c;

	c = pythagoras(length(origin->x, vector->x), length(origin->y, vector->y));
	return (pythagoras(c, length(origin->z, vector->z)));
}

t_vec	normalize_vector(const t_vec *vector)
{
	float	len;
	t_vec	norm;
	t_vec	dummy;

	ft_bzero(&dummy, sizeof(t_vec));
	len = vector_length(&dummy, vector);
	if (len == 0)
		return (dummy);
	norm.x = vector->x / len;
	norm.y = vector->y / len;
	norm.z = vector->z / len;
	return (norm);
}

float	q_sqrt(float num)
{
	union
	{
		int32_t	i;
		float	y;
	}	magic;
	
	magic.y = num;
	magic.i = 0x5f3759df - (magic.i >> 1);
	magic.y *= 1.5f - (num * 0.5f * magic.y * magic.y);
	return (magic.y);
}

t_vec	scale_vector(const t_vec *vector, const float scalar)
{
	t_vec	size;

	size.x = vector->x * scalar;
	size.y = vector->y * scalar;
	size.z = vector->z * scalar;
	return (size);
}

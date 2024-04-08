/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 11:09:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/08 16:15:17 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	vector_length(const t_vec *a, const t_vec *b)
{
	float	c;
	t_vec	new;

	if (a == NULL)
	{
		a = &new;
		new.x = 0;
		new.y = 0;
		new.z = 0;
	}
	c = pythagoras(a->x - b->x, a->y - b->y);
	return (pythagoras(c, a->z - b->z));
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
	t_magic	magic;

	magic.y = num;
	magic.i = 0x5F375A86 - (magic.i >> 1);
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

void	set_vector(t_vec *vector, const t_vec *location1, const t_vec *location2)
{
	vector->vec3 = location2->vec3 - location1->vec3;
	*vector = normalize_vector(vector);
}

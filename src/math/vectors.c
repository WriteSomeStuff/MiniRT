/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 11:09:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/23 17:56:40 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	vector_length(const t_vec a, const t_vec b)
{
	float	c;

	c = pythagoras(a.x - b.x, a.y - b.y);
	return (pythagoras(c, a.z - b.z));
}

t_vec	normalize_vector(const t_vec vector)
{
	float	len;
	t_vec	norm;

	len = vector_length(vec(0, 0, 0), vector);
	if (len == 0)
		return (vec(0, 0, 0));
	norm.vec3 = vector.vec3 / len;
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

void	set_vector(t_vec *vector, const t_vec *location1, const t_vec *location2)
{
	vector->vec3 = location2->vec3 - location1->vec3;
	*vector = normalize_vector(*vector);
}

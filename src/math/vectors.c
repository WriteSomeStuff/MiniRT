/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 11:09:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/07/30 13:21:28 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	inv_sqrt(float num)
{
	t_magic	magic;

	magic.y = num;
	magic.i = 0x5F375A86 - (magic.i >> 1);
	magic.y *= 1.5f - (num * 0.5f * magic.y * magic.y);
	return (magic.y);
}

t_vec	norm_vec(t_vec vec)
{
	vec.vec3 *= inv_sqrt(dot(vec, vec));
	return (vec);
}

void	set_vector(t_vec *vector, const t_vec *location1, \
	const t_vec *location2)
{
	vector->vec3 = location2->vec3 - location1->vec3;
	*vector = normalize_vector(*vector);
}

t_vec	vec(float x, float y, float z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

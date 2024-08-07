/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/29 17:52:17 by cschabra      #+#    #+#                 */
/*   Updated: 2024/07/30 13:22:10 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	sum(t_vec vector)
{
	return (vector.x + vector.y + vector.z);
}

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

t_vec	lerp(t_vec vec1, t_vec vec2, float fraction)
{
	t_vec	res;

	res.vec3 = vec1.vec3 * (1 - fraction) + vec2.vec3 * fraction;
	return (res);
}

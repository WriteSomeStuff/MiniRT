/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 11:09:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/13 18:48:40 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	length(const double x, const double y)
{
	return (fabs(x - y));
}

double	vector_length(const t_vec *origin, const t_vec *vector)
{
	double	c;

	c = pythagoras(length(origin->x, vector->x), length(origin->y, vector->y));
	return (pythagoras(c, length(origin->z, vector->z)));
}

t_vec	normalize_vector(const t_vec *origin, const t_vec *vector)
{
	double	len;
	t_vec	norm;

	len = vector_length(origin, vector);
	if (len == 0)
		return (ft_bzero(&norm, sizeof(t_vec)), norm);
	// norm.x = (vector->x - origin->x) / len;
	// norm.y = (vector->y - origin->y) / len;
	// norm.z = (vector->z - origin->z) / len;
	norm.x = vector->x / len;
	norm.y = vector->y / len;
	norm.z = vector->z / len;
	return (norm);
}

t_vec	scale_vector(const t_vec *vector, const double scalar)
{
	t_vec	size;

	size.x = vector->x * scalar;
	size.y = vector->y * scalar;
	size.z = vector->z * scalar;
	return (size);
}

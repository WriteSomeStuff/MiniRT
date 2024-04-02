/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/06 15:04:00 by cschabra      #+#    #+#                 */
/*   Updated: 2024/04/02 17:41:49 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	quaternion_math(const t_vec *a, const t_vec *b, float distance)
{
	t_vec	new;

	new.vec3 = a->vec3 + b->vec3 * distance + cross_product(a, b).vec3;
	scale_vector(&new, distance - dot(a, b));
	return (new);
}

t_vec	rotate(const t_vec *origin, const t_vec *point, const t_vec *angle)
{
	t_vec	new_point;

	new_point.vec3 = point->vec3 - origin->vec3;
	new_point = quaternion_math(&new_point, angle, vector_length(origin, point));
	return (new_point);
}
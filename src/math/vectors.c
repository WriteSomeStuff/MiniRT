/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 13:11:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/15 17:27:30 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	dot_product(const t_vec *a, const t_vec *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vec	cross_product(const t_vec *a, const t_vec *b)
{
	t_vec	cross;

	cross.x = a->y * b->z - a->z * b->y;
	cross.y = a->z * b->x - a->x * b->z;
	cross.z = a->x * b->y - a->y * b->x;
	return (cross);
}

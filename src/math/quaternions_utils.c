/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quater_pounder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 11:38:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/09 13:05:18 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vectorsRT.h"

void	print_quat(t_quat quat)
{
	printf("scalar: %f, i: %f, j: %f, k: %f\n", quat.scalar, quat.i, quat.j, quat.k);
}

t_vec	quat_to_vector(t_quat quat)
{
	t_vec	vec;

	vec.x = quat.i;
	vec.y = quat.j;
	vec.z = quat.k;
	return (vec);
}

t_quat	vector_to_quat(t_vec vector)
{
	t_quat	quat;

	quat.scalar = 0;
	quat.i = vector.x;
	quat.j = vector.y;
	quat.k = vector.z;
	return (quat);
}
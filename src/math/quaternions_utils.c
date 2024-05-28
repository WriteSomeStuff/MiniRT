/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternions_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 11:38:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/28 14:26:18 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vectorsRT.h"

void	print_quat(t_quat quat)
{
	printf("scalar: %f, i: %f, j: %f, k: %f\n", quat.scalar, quat.i, quat.j, quat.k);
}

t_quat	quat(float real, t_vec vec)
{
	t_quat	quat;

	quat.real = real;
	quat.x = vec.x;
	quat.y = vec.y;
	quat.z = vec.z;
	return (quat);
}

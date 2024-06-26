/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternions_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 11:38:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/06/01 11:22:28 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vectorsRT.h"

t_quat	quat(float real, t_vec vec)
{
	t_quat	quat;

	quat.real = real;
	quat.x = vec.x;
	quat.y = vec.y;
	quat.z = vec.z;
	return (quat);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/06 15:04:00 by cschabra      #+#    #+#                 */
/*   Updated: 2024/05/01 17:49:29 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	angle_to_vec(t_quat *quat, float angle)
{
	quat->scalar = cos(angle / 2);
	quat->i *= sin(angle / 2);
	quat->j *= sin(angle / 2);
	quat->k *= sin(angle / 2);
}

static t_quat	quaternion_product(const t_quat *a, const t_quat *b)
{
	t_quat	res;

	res.real = a->real * b->real - a->i * b->i - a->j * b->j - a->k * b->k;
	res.i = a->real * b->i + a->i * b->real - a->j * b->k + a->k * b->j;
	res.j = a->real * b->j + a->i * b->k + a->j * b->real - a->k * b->i;
	res.k = a->real * b->k - a->i * b->j + a->j * b->i + a->k * b->real;
	return (res);
}

static void	invert_quat(t_quat *quat)
{
	quat->i *= -1;
	quat->k *= -1;
	quat->j *= -1;
}

static t_vec	turn(const t_quat *point, const t_quat *angle)
{
	t_quat	result;
	t_quat	inv_angle;

	inv_angle.vec4 = angle->vec4;
	invert_quat(&inv_angle);
	result = quaternion_product(&inv_angle, point);
	result = quaternion_product(&result, angle);
	return (vec(result.x, result.y, result.z));
}

void	rotate(t_vec *point, t_quat rotation)
{
	t_quat	pt;

	angle_to_vec(&rotation, rotation.scalar);
	pt = quat(1, point->x, point->y, point->z);
	*point = turn(&pt, &rotation);
}

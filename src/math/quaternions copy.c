/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternions copy.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/06 15:04:00 by cschabra      #+#    #+#                 */
/*   Updated: 2024/04/08 18:22:01 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	angle_to_vec(t_quat *quat, float angle)
{
	quat->scalar = cos(angle / 2);
	quat->i *= sin(angle / 2);
	quat->j *= sin(angle / 2);
	quat->k *= sin(angle / 2);
}

t_quat	zero_quat()
{
	t_quat	quat;

	quat.i = 0;
	quat.j = 0;
	quat.k = 0;
	quat.scalar = 0;
	return (quat);
}

static t_quat	quaternion_product(const t_quat *a, const t_quat *b)
{
	t_quat	res;

	res.scalar = a->scalar * b->scalar - a->i * b->i - a->j * b->j - a->k * b->k;
	res.i = a->scalar * b->i + a->i * b->scalar - a->j * b->k + a->k * b->j;
	res.j = a->scalar * b->j + a->i * b->k + a->j * b->scalar - a->k * b->i;
	res.k =	a->scalar * b->k - a->i * b->j + a->j * b->i + a->k * b->scalar;
	return (res);
}

static void	invert_quat(t_quat *quat)
{
	quat->i *= -1;
	quat->k *= -1;
	quat->j *= -1;
}

t_quat	rotate(const t_quat *point, const t_quat *angle)
{
	t_quat	result;
	t_quat	inv_angle;

	inv_angle.vec4 = angle->vec4;
	invert_quat(&inv_angle);
	result = quaternion_product(&inv_angle, point);
	return (quaternion_product(&result, angle));
}

static void	print_quat(t_quat quat)
{
	printf("scalar: %f, i: %f, j: %f, k: %f\n", quat.scalar, quat.i, quat.j, quat.k);
}

static t_vec	quat_to_vector(t_vec *quat)
{
	t_vec	vec;

	vec.x = quat->i;
	vec.x = quat->i;
	vec.x = quat->i;
	return (vec);
}

static t_quat	vector_to_quat(t_vec *vector)
{
	t_quat	quat;

	quat.scalar = 0;
	quat.i = vector->x;
	quat.j = vector->y;
	quat.k = vector->z;
	return (quat);
}

void	rotate_point(t_vec *pt, const t_vec *ang)
{
	// t_quat	origin = zero_quat();
	t_quat	point;
	t_quat	angle;


	point = vector_to_quat(pt);
	angle = vector_to_quat(ang);
	t_quat res = rotate(&point, &angle);
	print_quat(res);
	t_vec	check;

	check.x = res.i;
	check.y = res.j;
	check.z = res.k;
	printf("length: %f\n", vector_length(NULL, &check));
}
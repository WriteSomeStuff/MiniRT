/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 13:11:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/06 17:00:33 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "time.h"

t_vec	vec(float x, float y, float z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float	dot(const t_vec a, const t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	cross(const t_vec a, const t_vec b)
{
	t_vec	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}

t_vec	random_vector()
{
	t_vec	random;

	srand((int)clock());
	random = vec(rand() % 2000 - 1000, rand() % 2000 - 1000, rand() % 1000);
	return (norm_vec(random));
}
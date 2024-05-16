/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 13:11:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/16 22:39:16 by vvan-der      ########   odam.nl         */
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

static long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000000 + time.tv_usec);
}


int	r_num()
{
	return (((int)get_time() * 747796405) % (360 * 360));
}

t_vec	random_vector()
{
	t_vec	random;

	srand((int)clock());
	random = vec(rand() % 2000 - 1000, rand() % 2000 - 1000, rand() % 2000 - 1000);
	return (norm_vec(random));
}

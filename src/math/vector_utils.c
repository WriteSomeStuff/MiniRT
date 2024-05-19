/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 13:11:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/19 13:59:31 by vincent       ########   odam.nl         */
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

/*	Generates a pseudo-random number without using too much computational power	*/

float	prn(uint32_t seed)
{
	uint32_t	result;

	seed = seed * 747796405 + 2891336453;
	result = ((seed >> ((seed >> 28) + 4)) ^ seed) * 277803737;
	result = (result >> 22) ^ result;
	return (((float)result / 4294967295.0) * 2.0 - 1.0);
}

static uint32_t	generate_seed(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint32_t)time.tv_usec);
}

t_vec	random_vector()
{
	t_vec		random;
	static uint32_t	seed = 0;

	seed += generate_seed();
	random = vec(prn(seed), prn(seed * 2), prn(seed * 3));
	return (norm_vec(random));
}

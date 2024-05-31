/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 13:11:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/31 17:17:57 by vincent       ########   odam.nl         */
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
float	prn(uint32_t *id)
{
	uint32_t		result;

	*id = *id * 747796405 + 2891336453;
	result = ((*id >> ((*id >> 28) + 4)) ^ *id) * 277803737;
	result = (result >> 22) ^ result;
	*id = result;
	// printf("%f\n", ((float)(result / 4294967295.0)) * 2.0 - 1.0);
	return (((float)(result / 4294967295.0)) * 2.0 - 1.0);
}

// float	normal_distribution(uint32_t *id)
// {
// 	float theta = 2 * 3.1415926 * prn(id);
// 	float rho = sqrt(-2 * log(prn(id)));
// 	return (rho * cos(theta));
// }

t_vec	random_vector(t_data *data, uint32_t id)
{
	t_vec		random;
	uint32_t	*tmp;

	tmp = &data->seed[id];
	random = vec(prn(tmp), prn(tmp), prn(tmp));
	return (norm_vec(random));
}

// t_vec	random_vector(t_data *data, uint32_t id)
// {
// 	t_vec		random;
// 	uint32_t	*tmp;

// 	tmp = &data->seed[id];
// 	random = vec(normal_distribution(tmp), normal_distribution(tmp), normal_distribution(tmp));
// 	return (norm_vec(random));
// }

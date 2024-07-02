/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 13:11:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/07/02 18:54:40 by vvan-der      ########   odam.nl         */
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

static float	prn(uint32_t *id)
{
	uint32_t		result;

	*id = *id * 747796405 + 2891336453;
	result = ((*id >> ((*id >> 28) + 4)) ^ *id) * 277803737;
	result = (result >> 22) ^ result;
	return (((float)(result / 4294967295.0)));
}

static float	norm_dist(uint32_t *id)
{
	float rho;
	float theta;
	
	rho = sqrt(-2 * log(prn(id)));
	theta = 2 * PI * prn(id);
	return (rho * cos(theta));
}

t_vec	random_vector(t_data *data, uint32_t id)
{
	t_vec		random;
	uint32_t	*tmp;

	tmp = &data->seed[id];
	random = vec(norm_dist(tmp), norm_dist(tmp), norm_dist(tmp));
	return (normalize_vector(random));
}

bool	is_glossy(t_data *data, uint32_t id, float glossiness)
{
	float	random;

	random = prn(&data->seed[id]);
	if (glossiness >= random)
		return (true);
	// printf("random: %f glossiness: %f\n", random, glossiness);
	return (false);
}

t_vec	lerp(t_vec vec1, t_vec vec2, float fraction)
{
	t_vec	res;

	res.vec3 = vec1.vec3 * (1 - fraction) + vec2.vec3 * fraction;
	return (res);
}

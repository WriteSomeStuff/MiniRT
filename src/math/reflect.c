/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reflect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 11:10:15 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/07/30 13:22:14 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	inverted(t_vec vector)
{
	t_vec	inverted;

	inverted.vec3 = vector.vec3 * -1.0f;
	return (inverted);
}

t_vec	reflect(const t_vec incoming, const t_vec normal)
{
	t_vec	outgoing;

	outgoing.vec3 = incoming.vec3 - 2.0f * dot(incoming, normal) * normal.vec3;
	return (outgoing);
}

bool	is_glossy(t_data *data, uint32_t id, float glossiness)
{
	float	random;

	random = prn(&data->seed[id]);
	if (glossiness >= random)
		return (true);
	return (false);
}

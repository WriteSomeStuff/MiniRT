/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reflect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 11:10:15 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/31 16:25:15 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	reflect(const t_vec incoming, const t_vec normal)
{
	t_vec	outgoing;

	outgoing.vec3 = incoming.vec3 - 2 * dot(incoming, normal) * normal.vec3;
	return (outgoing);
}

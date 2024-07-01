/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reflect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 11:10:15 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/07/01 17:22:20 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	reflect(const t_vec incoming, const t_vec normal)
{
	t_vec	outgoing;

	outgoing.vec3 = incoming.vec3 - 2.0f * dot(incoming, normal) * normal.vec3;
	return (outgoing);
}

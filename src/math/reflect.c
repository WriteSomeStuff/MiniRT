/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reflect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 11:10:15 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/18 11:18:51 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	reflect(const t_vec *incoming, const t_vec *normal)
{
	t_vec	outgoing;
	t_quat	rotation;

	outgoing.vec3 = incoming->vec3;
	rotation = vector_to_quat(*normal);
	rotation.real = angle(incoming, normal);
	rotate_point(&outgoing, &rotation);
	return (outgoing);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translate_objects2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:07:53 by cschabra      #+#    #+#                 */
/*   Updated: 2024/08/16 13:08:27 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translate_cones(t_cone *c, t_vec t)
{
	while (c->object != INVALID)
	{
		c->apex.vec3 -= t.vec3;
		c->base.vec3 -= t.vec3;
		c++;
	}
}

void	translate_cylinders(t_cylinder *c, t_vec t)
{
	while (c->object != INVALID)
	{
		c->center.vec3 -= t.vec3;
		c->base.vec3 -= t.vec3;
		c->top.vec3 -= t.vec3;
		c++;
	}
}

void	translate_discs(t_disc *d, t_vec t)
{
	while (d->object != INVALID)
	{
		d->center.vec3 -= t.vec3;
		d++;
	}
}

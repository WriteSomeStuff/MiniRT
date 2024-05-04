/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translate_objects.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/04 13:51:55 by vincent       #+#    #+#                 */
/*   Updated: 2024/05/04 14:26:39 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	translate_cylinders(t_cylinder *c, t_vec t)
{
	while (c->object != INVALID)
	{
		c->center.vec3 -= t.vec3;
		c->base.vec3 -= t.vec3;
		c->top.vec3 -= t.vec3;
		c++;
	}
}

static void	translate_planes(t_plane *p, t_vec t)
{
	while (p->object != INVALID)
	{
		p->location.vec3 -= t.vec3;
		p++;
	}
}

static void	translate_spheres(t_sphere *s, t_vec t)
{
	while (s->object != INVALID)
	{
		s->center.vec3 -= t.vec3;
		s++;
	}
}

void	translate_objects(t_data *data, t_vec amount)
{
	translate_cylinders(data->cyls, amount);
	translate_planes(data->planes, amount);
	translate_spheres(data->spheres, amount);
	data->light->source.vec3 -= amount.vec3;
}